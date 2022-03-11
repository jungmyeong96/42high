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

#define HEADER_FMT "HTTP/1.1 %d %s\nContent-Length: %ld\nContent-Type: %s\n\n"

using namespace std;

typedef struct s_header
{
    char*	method;
    char*	uri;
    char*	host;
	char*	version;
	char*	local_uri;
	char ct_type[40];
	int		cgi;
    int		fd;
}               t_header;

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
    else if (!strcmp(ext, ".php") || !strcmp(ext, ".py"))
		header->cgi = 1;
    else strcpy(header->ct_type, "text/plain");
    }
}

void fill_header(char *header, int status, long len, char *type) {
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
    sprintf(header, HEADER_FMT, status, status_text, len, type);
}

int main()
{
    /* init server socket and listen */
    int server_socket;
    struct sockaddr_in server_addr;

    if ((server_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        exit_with_perror("socket() error\n" + string(strerror(errno)));

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(2050);
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
        exit_with_perror("bind() error\n" + string(strerror(errno)));

    if (listen(server_socket, 5) == -1)
        exit_with_perror("listen() error\n" + string(strerror(errno)));
    fcntl(server_socket, F_SETFL, O_NONBLOCK);
    
    /* init kqueue */
    int kq;
    if ((kq = kqueue()) == -1)
        exit_with_perror("kqueue() error\n" + string(strerror(errno)));


    map<int, string> clients; // map for client socket:data
    vector<struct kevent> change_list; // kevent vector for changelist
    struct kevent event_list[8]; // kevent array for eventlist

    /* add event for server socket */
    change_events(change_list, server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    cout << "echo server started" << endl;

    /* main loop */
    int new_events;
    struct kevent* curr_event;
    t_header	*header;
    header = 0;
    char		r_header[1024];
    while (1)
    {
        /*  apply changes and return new events(pending events) */
        new_events = kevent(kq, &change_list[0], change_list.size(), event_list, 8, NULL);
        if (new_events == -1)
            exit_with_perror("kevent() error\n" + string(strerror(errno)));

        change_list.clear(); // clear change_list for new changes

        for (int i = 0; i < new_events; ++i)
        {
            curr_event = &event_list[i];
          //      cout << "for " << i << endl;

            /* check error event return */
            if (curr_event->flags & EV_ERROR)
            {
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
                    clients[client_socket] = "";

                }
                else if (clients.find(curr_event->ident)!= clients.end())
                {
                    /* read data from client */
                    char buf[1024];
                    int n = read(curr_event->ident, buf, sizeof(buf));

					printf("buf\n%s\nThe end\n", buf);
                    if (n <= 0)
                    {
                        if (n < 0)
                            cerr << "client read error!" << endl;
                        disconnect_client(curr_event->ident, clients);
                    }
                    else
                    {
						char** result = ft_split(buf, '\n');
						char tmp[1024];
						for (int i = 1; result[i] != NULL; i++)
						{
							strcpy(tmp, result[i]);
							if (!strncmp(strtok(tmp, ": "), "Host", 4))
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
                /* send data to client */
                if (header->method)
                {
				struct stat st;
                //cout << "here 123" << endl;
                
                if (!strncmp(header->method, "GET", 3))
                {
                    header->local_uri = header->uri + 1;
                    find_mime(header);
					if (header->cgi == 1)
					{
						system("export REQUEST_METHOD=\"GET\"");
						system("export SERVER_PROTOCOL=\"HTTP/1.1\"");
						system("export PATH_INFO=\"/Users/daekim/subject/cadet/web/test.php\"");
						system("./tester/cgi_tester");
					}
					else
	                {
						stat(header->local_uri, &st);
						int ct_len = st.st_size;
                    	fill_header(r_header, 200, ct_len, header->ct_type);
					}
                }
                // else if (!strcmp(header->method, "POST"))
                // {
                //     ;
                // }
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
                    if (clients[curr_event->ident] != "")
                    {
                        int n;
                        if ((n = write(curr_event->ident, clients[curr_event->ident].c_str(),
                                        clients[curr_event->ident].size()) == -1))
                        {
                            cerr << "client write error!" << endl;
                            disconnect_client(curr_event->ident, clients);  
                        }
                        else
                            clients[curr_event->ident].clear();
                    }
                }
            }
            }
        }

    }
    return (0);
}