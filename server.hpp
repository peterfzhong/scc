#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <event.h>

#include <iostream>

#include "base_handler.hpp"


#define PORT        10000
#define BACKLOG     5
#define MEM_SIZE    1024

using namespace std;


class Server
{
protected:
	struct event_base* base;

public:
	Server()
	{
	}

	~Server()
	{
	}



protected:
	static void s_on_accept(int sock, short event, void* arg)
	{
		Server* server = (Server *)arg;
		server->on_accept(sock, event, arg);
	}

	void on_accept(int sock, short event, void* arg)
	{
		struct sockaddr_in cli_addr;
		int newfd, sin_size;

		BaseHandler *handler = new BaseHandler(base);
		sin_size = sizeof(struct sockaddr_in);
		newfd = accept(sock, (struct sockaddr*)&cli_addr, (socklen_t*)&sin_size);
		
		struct event *read_event = handler->get_read_event();
		event_set(read_event, newfd, EV_READ | EV_PERSIST, BaseHandler::s_on_read, handler);
		event_base_set(base, read_event);
		event_add(read_event, NULL);
	}

public:
	int run()
	{
		struct sockaddr_in my_addr;
		int sock;

		sock = socket(AF_INET, SOCK_STREAM, 0);
		int yes = 1;
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
		memset(&my_addr, 0, sizeof(my_addr));
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(PORT);
		my_addr.sin_addr.s_addr = INADDR_ANY;
		bind(sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
		listen(sock, BACKLOG);

		struct event listen_ev;
		base = event_base_new();
		event_set(&listen_ev, sock, EV_READ | EV_PERSIST, Server::s_on_accept, this);
		event_base_set(base, &listen_ev);
		event_add(&listen_ev, NULL);
		event_base_dispatch(base);

		return 0;
	}
};
