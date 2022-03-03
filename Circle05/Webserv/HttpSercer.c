
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdbool.h>

#define BUF_SIZE 1024
#define SMALL_BUF 100

void* request_handler(void* arg);
void send_data(FILE* fp, char* ct, char* file_name);
char* content_type(char* file);
void send_error(FILE* fp);
void error_handling(char* message);

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_size;
	char buf[BUF_SIZE];
	pthread_t t_id;	

	if(argc!=2) // 실행파일 경로/PORT번호 를 입력으로 받아야함
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0); // TCP 소켓 생성

	/* 서버 주소정보 초기화 */
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	/* 서버 주소정보를 기반으로 주소할당 */
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	/*
	서버소켓(리스닝 소켓)이 됨
	연결요청 대기큐가 생성되며,
	이 함수호출 이후로부터 클라이언트의 연결요청이 가능함.
	 */
	if(listen(serv_sock, 20)==-1)
		error_handling("listen() error");

	/* 요청 및 응답 */
	while(1)
	{
		clnt_adr_size=sizeof(clnt_adr);

		/* 
		클라이언트의 연결요청을 수락
		클라이언트와의 송수신을 위해 새로운 소켓 생성
		*/
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);

		printf("Connection Request : %s:%d\n", 
			inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));

		pthread_create(&t_id, NULL, request_handler, &clnt_sock); // 쓰레드 생성 및 실행
		pthread_detach(t_id); // 종료된 쓰레드의 리소스 소멸
	}
	close(serv_sock); // 서버소켓 연결종료
	return 0;
}

void* request_handler(void *arg)
{
	int clnt_sock=*((int*)arg);
	char req_line[SMALL_BUF];
	FILE* clnt_read;
	FILE* clnt_write;
	
	char method[10];
	char ct[15];
	char file_name[30];
  
    /* 입출력 분할 */
	clnt_read=fdopen(clnt_sock, "r");
	clnt_write=fdopen(dup(clnt_sock), "w");

	fgets(req_line, SMALL_BUF, clnt_read); // 클라이언트로부터 데이터 수신
	if(strstr(req_line, "HTTP/")==NULL) // HTTP에 의한 요청인지 확인
	{
		send_error(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return NULL;
	}
	
	strcpy(method, strtok(req_line, " /"));
	if(strcmp(method, "GET")!=0) // GET 방식 요청인지 확인
	{
		send_error(clnt_write);
		fclose(clnt_read);
		fclose(clnt_write);
		return NULL;
	}

	strcpy(file_name, strtok(NULL, " /"));
	strcpy(ct, content_type(file_name));
	fclose(clnt_read); // 클라이언트로부터 데이터 수신을 완료했으므로 입력을 위한 스트림 종료

	send_data(clnt_write, ct, file_name); // 클라이언트에게 데이터 송신
}

void send_data(FILE* fp, char* ct, char* file_name)
{
	char protocol[]="HTTP/1.0 200 OK\r\n";
	char server[]="Server:Linux Web Server\r\n";
	char cnt_len[]="Content-length:2048\r\n";
	char cnt_type[SMALL_BUF];
	char buf[BUF_SIZE];
	FILE* send_file;
	
	sprintf(cnt_type, "Content-type:%s\r\n\r\n", ct);
	send_file=fopen(file_name, "r"); // 클라이언트가 요청한 파일 열기
	if(send_file==NULL)
	{
		send_error(fp);
		fclose(fp);
		return;
	}

	/* 헤더 정보 전송 */
	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_len, fp);
	fputs(cnt_type, fp);

	/* 요청 데이터 전송 */
	while(fgets(buf, BUF_SIZE, send_file)!=NULL) 
	{
		fputs(buf, fp);
		fflush(fp);
	}
	fflush(fp);
	fclose(fp); // HTTP 프로토콜에 의해서 응답 후 종료
}

char* content_type(char* file) // Content-Type 구분
{
	char extension[SMALL_BUF];
	char file_name[SMALL_BUF];

	strcpy(file_name, file);
	strtok(file_name, ".");
	strcpy(extension, strtok(NULL, "."));
	
	if(!strcmp(extension, "html")||!strcmp(extension, "htm")) 
		return "text/html";
	else
		return "text/plain";
}

void send_error(FILE* fp) // 오류 발생시 메시지 전달
{	
	char protocol[]="HTTP/1.0 400 Bad Request\r\n";
	char server[]="Server:Linux Web Server\r\n";
	char cnt_len[]="Content-length:2048\r\n";
	char cnt_type[]="Content-type:text/html\r\n\r\n";
	char content[]="<html><head><title>NETWORK</title></head>"
	       "<body><font size=+5><br>오류 발생! 요청 파일명 및 요청 방식 확인!"
		   "</font></body></html>";

	/* 헤더 정보 전송 */
	fputs(protocol, fp);
	fputs(server, fp);
	fputs(cnt_len, fp);
	fputs(cnt_type, fp);
	fflush(fp);
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}