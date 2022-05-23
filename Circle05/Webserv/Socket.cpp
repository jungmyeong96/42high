#include <sys/socket.h>
#include <arpa/inet.h> //htnol, htons, INADDR_ANY, sockaddr_in etc
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int	serv_sock;
	int	clnt_sock;

	//sockaddr_in은 소켓 주소의 틀을 형성해주는 구조체로 AF_INET일 경우 사용
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr; //accept에서 받는역할
	socklen_t clnt_addr_size;

	//TCP연결지향형이고 ipv4 도메인을 위한 소켓 생성
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		printf("Socket error\n");

	//주소를 초기화한 후 IP주소와 포트 지정
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET; //타입:ipv4
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);//ip //컴퓨터에 존재하는 랜카드 중 사용가능한 랜카드의 IP주소를 사용하라
	serv_addr.sin_port=htons(atoi(argv[1])); //port

	//소켓과 서버 주소를 바인딩
	if (bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
		printf("bind error\n");

	//연결 대기열 5개 생성 //backlog : sockfd의 커넥션 중, 허용가능한 pending된 커넥션 큐의 최대길이
	if (listen(serv_sock, 5) == -1)
		printf("listen error\n");

	//클라이언트로부터 요청이 오면 연결 수락
	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if (clnt_sock == -1)
		printf("accept error\n");
	
	//데이터 전송
	char msg[] = "Hello this is server!\n";
	write(clnt_sock, msg, sizeof(msg));

	//소켓들 닫기
	close(clnt_sock);
	close(serv_sock);

	return 0;
}
