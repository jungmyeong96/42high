#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define RESPONSE_FMT "HTTP/1.1 %d %s\nContent-Length: %ld\nContent-Type: %s\n%s"

using namespace std;
/*
HTTP/1.1 %d %s\n
Content-Length: %ld\n
Content-Type: %s\n
\n
body
*/

static const char *basic_env[] = {
	"AUTH_TYPE",
	"CONTENT_LENGTH",
	"CONTENT_TYPE",
	"GATEWAY_INTERFACE",
	"PATH_INFO",
	"PATH_TRANSLATED",
	"QUERY_STRING",
	"REMOTE_ADDR",
	"REMOTE_IDENT",
	"REMOTE_USER",
	"REQUEST_METHOD",
	"REQUEST_URI",
	"SCRIPT_NAME",
	"SERVER_NAME",
	"SERVER_PORT",
	"SERVER_PROTOCOL",
	"SERVER_SOFTWARE",
	"REDIRECT_STATUS",
	NULL
	};

typedef struct s_header {
	char*	method;
	char*	uri;
	char*	host;
	char*	version;
	char*	local_uri;
	char ct_type[40];
	int		cgi;
	int		fd;
}               t_header;

char **setEnviron(std::map<std::string, std::string> env) {
  char **return_value;
  std::string temp;

  return_value = (char **)malloc(sizeof(char *) * (env.size() + 1));
  int i = 0;
  std::map<std::string, std::string>::iterator it;
  for (it = env.begin(); it != env.end(); it++) {
	temp = (*it).first + "=" + (*it).second;
	char *p = (char *)malloc(temp.size() + 1);
	strcpy(p, temp.c_str());
	return_value[i] = p;
	i++;
  }
  return_value[i] = NULL;
  return (return_value);
}

static void		scpy(char *new2, char const *s, size_t i, size_t start)
{
	size_t		j;

	j = 0;
	while (start < i)
	{
		new2[j] = s[start];
		start++;
		j++;
	}
}

static char		ft_free(char **new2, size_t num)
{
	size_t		i;

	i = 0;
	while (i < num)
		free(new2[i++]);
	free(new2);
	return (0);
}

static void		spliting(char const *s, char c, char **new2)
{
	size_t		i;
	size_t		count;
	size_t		start;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			if (!(new2[count] = (char *)calloc((i - start + 1),
							sizeof(char))))
			{
				ft_free(new2, count);
				return ;
			}
			scpy(new2[count], s, i, start);
			count++;
		}
		else if (s[i] == c)
			i++;
	}
}

static size_t	countc(char const *s, char c)
{
	size_t		i;
	size_t		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	char		**new2;
	size_t		num;

	if (s == 0)
		return (0);
	num = countc(s, c);
	if (!(new2 = (char **)calloc((num + 1), sizeof(char *))))
		return (0);
	spliting(s, c, new2);
	return (new2);
}

void exit_with_perror(const string& msg)
{
	cerr << msg << endl;
	exit(EXIT_FAILURE);
}

void change_events(vector<struct kevent>& change_list, uintptr_t ident, int16_t filter,
		uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
{
	struct kevent temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	change_list.push_back(temp_event);
}

void disconnect_client(int client_fd, map<int, string>& clients)
{
	cout << "client disconnected: " << client_fd << endl;
	close(client_fd);
	clients.erase(client_fd);
}

void find_mime(t_header *header) {
	char *ext = strrchr(header->uri, '.');
	if (ext)
	{
	if (!strcmp(ext, ".html"))
		strcpy(header->ct_type, "text/html");
	else if (!strcmp(ext, ".jpg") || !strcmp(ext, ".jpeg"))
		strcpy(header->ct_type, "image/jpeg");
	else if (!strcmp(ext, ".png"))
		strcpy(header->ct_type, "image/png");
	else if (!strcmp(ext, ".css"))
		strcpy(header->ct_type, "text/css");
	else if (!strcmp(ext, ".js"))
		strcpy(header->ct_type, "text/javascript");
	else if (!strcmp(ext, ".php") || !strcmp(ext, ".py"))
		header->cgi = 1;
	else strcpy(header->ct_type, "text/plain");
	}
}

void fill_response(char *header, int status, long len, std::string type, char *body) {
	char status_text[40];
	switch (status) {
		case 200:
			strcpy(status_text, "OK"); break;
		case 404:
			strcpy(status_text, "Not Found"); break;
		case 500:
		default:
			strcpy(status_text, "Internal Server Error"); break;
	}

	sprintf(header, RESPONSE_FMT, status, status_text, len, type.c_str(), body);

}

char **setCommand(std::string command, std::string path) {
  char **return_value;
  return_value = (char **)malloc(sizeof(char *) * (3));

  char *temp;

  temp = (char *)malloc(sizeof(char) * (command.size() + 1));
  strcpy(temp, command.c_str());
  return_value[0] = temp;

  temp = (char *)malloc(sizeof(char) * (path.size() + 1));
  strcpy(temp, path.c_str());
  return_value[1] = temp;
  return_value[2] = NULL;
  return (return_value);
}

int main()
{
	/* init server socket and listen */
	int server_socket;
	struct sockaddr_in server_addr;
	char **environ;
	char foo[4096];

	if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		exit_with_perror("socket() error\n" + string(strerror(errno)));

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(8030);
	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
		exit_with_perror("bind() error\n" + string(strerror(errno)));

	if (listen(server_socket, 5) == -1)
		exit_with_perror("listen() error\n" + string(strerror(errno)));
	fcntl(server_socket, F_SETFL, O_NONBLOCK);

	/* init kqueue */
	int kq;

	if ((kq = kqueue()) == -1)
		exit_with_perror("kqueue() error\n" + string(strerror(errno)));
//환경변수 설정
	std::map<std::string, std::string> env_set;

	for (int i = 0; basic_env[i] != NULL; i++)
	{
	  std::pair<std::string, std::string> env_temp;
	  env_temp.first = basic_env[i];
	  env_temp.second = "";
	  env_set.insert(env_temp);
	}
	env_set["QUERY_STRING"] = "color=black&sport=123";
	env_set["REQUEST_METHOD"] = "POST";
	env_set["REDIRECT_STATUS"] = "CGI";
	env_set["SCRIPT_FILENAME"] = "/Users/daekim/subject/cadet/DreamXWebserv/form_up.php";
	env_set["SERVER_PROTOCOL"] = "HTTP/1.1";
	env_set["PATH_INFO"] = "form_up.php";
	//env_set["CONTENT_TYPE"] = "application/x-www-form-urlencoded";
	env_set["CONTENT_TYPE"] = "text/plaine";
	env_set["GATEWAY_INTERFACE"] = "CGI/1.1";
	env_set["PATH_TRANSLATED"] = "form_up.php";
	env_set["REMOTE_ADDR"] = "127.0.0.1";
	env_set["REQUEST_URI"] = "form_up.php";
	env_set["SERVER_PORT"] = "8030";
	env_set["SERVER_PROTOCOL"] = "HTTP/1.1";
	env_set["SERVER_SOFTWARE"] = "versbew";

	// if (!strcmp(command[0], "php-cgi")) {
	  env_set["SCRIPT_NAME"] = "tester/php-cgi";

	// }
	// else if (!strcmp(command[0], "cgi_tester")) {
	//   env_set["SCRIPT_NAME"] = "/Users/doyun/Desktop/DreamXWebserv/tester/cgi_tester";
	// }

	environ = setEnviron(env_set);

	map<int, string> clients; // map for client socket:data
	vector<struct kevent> change_list; // kevent vector for changelist
	struct kevent event_list[8]; // kevent array for eventlist

	/* add event for server socket */
	change_events(change_list, server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	cout << "DreamX server started" << endl;

	/* main loop */
	int new_events;
	struct kevent* curr_event;
	t_header	*header = 0;
	char		r_header[1024];
	int idx = 0;
	while (1)
	{
		/*  apply changes and return new events(pending events) */
		//cout << "while Filter 1 " << event_list[i].filter << endl;
		new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
		// for(int i = 0; i < new_events; ++i)
		//     cout << "while Filter 2 " << event_list[i].filter << endl;
		printf("^^^^^start idx = %d, new_event = %d\n", ++idx, new_events);

		if (new_events == -1)
			exit_with_perror("kevent() error\n" + string(strerror(errno)));

		change_list.clear(); // clear change_list for new changes

		for (int i = 0; i < new_events; ++i)
		{
			curr_event = &event_list[i];
			//     cout << "for " << i << endl;
			cout << "for Filter " << curr_event->filter << endl;

			/* check error event return */
			if (curr_event->flags & EV_ERROR)
			{
				printf("@@@@@@@@@@@@@@1\n");
				if (curr_event->ident == server_socket)
					exit_with_perror("server socket error");
				else
				{
					cerr << "client socket error" << endl;
					disconnect_client(curr_event->ident, clients);
				}
			}
			else if (curr_event->filter == EVFILT_READ)
			{
				if (curr_event->ident == server_socket)
				{
	   				printf("@@@@@@@@@@@@@@2 읽기 1\n");

					/* accept new client */
					int client_socket;

					if (header)
						free(header);

					header = (t_header *)malloc(sizeof(t_header));
					header->fd = 0;
					header->cgi = 0;

					header->host = 0;
					header->local_uri = 0;
					header->method = 0;
					header->uri = 0;
					header->version = 0;

					if ((client_socket = accept(server_socket, NULL, NULL)) == -1)
						exit_with_perror("accept() error\n" + string(strerror(errno)));
					cout << "accept new client: " << client_socket << endl;
					fcntl(client_socket, F_SETFL, O_NONBLOCK);

					/* add event for client socket - add read && write event */
					change_events(change_list, client_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
					change_events(change_list, client_socket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
					// cout << "Filter " << curr_event->filter << endl;
					clients[client_socket] = "";
					header->fd = client_socket;
				}
				else if (clients.find(curr_event->ident)!= clients.end())
				{
					printf("@@@@@@@@@@@@@@3  읽기 2\n");
					/* read data from client */
					char buf[1024];
					int n = read(curr_event->ident, buf, sizeof(buf));

					//printf("buf\n%s\nThe end\n", buf);
					if (n <= 0)
					{
						if (n <= 0)
							cerr << "client read error!" << endl;
						disconnect_client(curr_event->ident, clients);
					}
					else
					{
					printf("@@@@@@@@@@@@@@3 else \n");
						char** result = ft_split(buf, '\n');
						char tmp[1024];
						for (int i = 1; result[i] != NULL; i++)
						{
							strcpy(tmp, result[i]);
							if (!strcmp(strtok(tmp, ": "), "Host"))
								header->host = strtok(NULL, "\n");
						}

						header->fd = curr_event->ident;
						header->method = strtok(result[0], " ");
						header->uri = strtok(NULL, " ");
						header->version = strtok(NULL, "\n");
						// buf[n] = '\0';
						// clients[curr_event->ident] += buf;
						// cout << "received data from " << curr_event->ident << ": " << clients[curr_event->ident] << endl;
					}
				}
			}
			else if (curr_event->filter == EVFILT_WRITE)
			{
				printf("@@@@@@@@@@@@@@4   쓰기\n");
				/* send data to client */
				if (header->method)
				{
				struct stat st;
				//cout << "here 123" << endl;

				if (!strcmp(header->method, "GET"))
				{
					printf("@@@@@@@@@@@@@@5\n");
					//cout << "here if" << endl;
					header->local_uri = header->uri + 1;
					find_mime(header);
					if (header->cgi == 1)
					{
						printf("*************1\n");
						// system("export REQUEST_METHOD=\"GET\"");
						// system("export SERVER_PROTOCOL=\"HTTP/1.1\"");
						// system("export PATH_INFO=\"/Users/doyun/Desktop/DreamXWebserv/test.php\"");
						// system("./tester/cgi_tester");
						int pipe_fd[2];
						pid_t pid;
						// char command1[3][100] = {"php", "/Users/doyun/Desktop/DreamXWebserv/test.php", NULL};
						// char command2[3][20] = {"cgi_tester", "GET", NULL};
						char **command1 = setCommand("php-cgi", "/Users/daekim/subject/cadet/DreamXWebserv/form_up.php");
						char **command2 = setCommand("cgi_tester", "GET");

						pipe(pipe_fd);
						pid = fork();
						if (!pid)
						{
							dup2(pipe_fd[1], STDOUT_FILENO);
							close(pipe_fd[0]);
							close(pipe_fd[1]);
							if (!strcmp(command1[0], "php-cgi"))
								execve("tester/php-cgi", command1, environ);
							else if (!strcmp(command2[0], "cgi_tester"))
								execve("./tester/cgi_tester", command2, NULL);
						}
						else
						{
							printf("*************2\n");
							int nbytes;
							int i = 0;

							read(pipe_fd[0], foo, sizeof(foo));
							printf("*************3\n");
							//printf("!!!! %s!!!!!\n", foo);
							fill_response(r_header, 200, strlen(foo), "text/html", foo);
							printf("*************4\n");
							close(pipe_fd[1]);
							printf("*************5\n");
							close(pipe_fd[0]);
							printf("*************6\n header->fd %d \nr_header %s\n strlen %lu \n", header->fd, r_header, strlen(r_header));
							write(header->fd, r_header, strlen(r_header));
							printf("*************7\n");
							wait(NULL);
							printf("*************8\n");
							
							header->fd = 0;
							header->cgi = 0;

							header->host = 0;
							header->local_uri = 0;
							header->method = 0;
							header->uri = 0;
							header->version = 0;
							close(curr_event->ident);
							clients.erase(curr_event->ident);
							sleep(5);
						}
					}
					else
					{
						printf("@@@@@@@@@@@@@@6\n");
						stat(header->local_uri, &st);
						int ct_len = st.st_size;
						char body[10000];
						int bodyfd;

						bodyfd = open(header->local_uri, O_RDONLY);

						if (read(bodyfd, body, 10000) < 0)
						{
							perror("[ERR] Failed to read request.\n");
						}
						fill_response(r_header, 200, ct_len, header->ct_type, body);
						write(header->fd, r_header, strlen(r_header));

					}
				}
				else if (!strcmp(header->method, "POST"))
				{
					printf("@@@@@@@@@@@@@@7\n");
					// header->local_uri = header->uri + 1;
					// find_mime(header);
					// system("export REQUEST_METHOD=\"GET\"");
					// system("export SERVER_PROTOCOL=\"HTTP/1.1\"");
					// system("export PATH_INFO=\"/Users/doyun/Desktop/DreamXWebserv/test.php\"");
					// system("./tester/cgi_tester");
					int pipe_fd[2];
					pid_t pid;
					// char command1[3][100] = {"php", "/Users/doyun/Desktop/DreamXWebserv/test.php", NULL};
					// char command2[3][20] = {"cgi_tester", "GET", NULL};
					char **command1 = setCommand("php-cgi", "/Users/daekim/subject/cadet/DreamXWebserv/form_up.php");
					char **command2 = setCommand("cgi_tester", "GET");

					pipe(pipe_fd);
					pid = fork();
					if (!pid)
					{
						dup2(pipe_fd[1], STDOUT_FILENO);
						close(pipe_fd[0]);
						close(pipe_fd[1]);
						if (!strcmp(command1[0], "php-cgi"))
							execve("./tester/php-cgi", command1, environ);
						else if (!strcmp(command2[0], "cgi_tester"))
							execve("./tester/cgi_tester", command2, NULL);
					}
					else
					{
						int nbytes;
						int i = 0;

						read(pipe_fd[0], foo, sizeof(foo));
						fill_response(r_header, 200, strlen(foo), "text/html", foo);
						close(pipe_fd[1]);
						close(pipe_fd[0]);
						write(header->fd, r_header, strlen(r_header));
						wait(NULL);

					}
				}
				// else if (!strcmp(header->method, "DELETE"))
				// {
				//     ;
				// }
				// else
				// {
				//     ;
				// }
				map<int, string>::iterator it = clients.find(curr_event->ident);
				if (it != clients.end())
				{
					printf("@@@@@@@@@@@@@@8\n");
					if (clients[curr_event->ident] != "")
					{
						// int n;
						// if ((n = write(curr_event->ident, clients[curr_event->ident].c_str(),
						// 				clients[curr_event->ident].size()) == -1))
						// {
						// 	cerr << "client write error!" << endl;
						// 	disconnect_client(curr_event->ident, clients);
						// }
						// else
							clients[curr_event->ident].clear();
					}
				}
				}
			}
		}
	}
	return (0);
}