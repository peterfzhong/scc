#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <event.h>

#include <iostream>


#define BACKLOG     5
#define MEM_SIZE    1024

using namespace std;


struct sock_ev {
	struct event* read_ev;
	struct event* write_ev;
	char* buffer;
};



class BaseHandler
{
public:
	BaseHandler(struct event_base* base)
	{
		this->base = base;
		ev = (struct sock_ev*)malloc(sizeof(struct sock_ev));
		ev->read_ev = (struct event*)malloc(sizeof(struct event));
		ev->write_ev = (struct event*)malloc(sizeof(struct event));
	}
	
	~BaseHandler()
	{
		release_sock_event(ev);
	}

public:
	struct event* get_read_event()
	{
		return ev->read_ev;
	}

	struct event* get_write_event()
	{
		return ev->write_ev;
	}
	
	struct sock_ev* get_sock_ev()
	{
		return ev;
	}



protected:
	void release_sock_event(struct sock_ev* ev)
	{
		event_del(ev->read_ev);
		free(ev->read_ev);
		free(ev->write_ev);
		free(ev->buffer);
		free(ev);
	}

public:
	static void s_on_write(int sock_fd, short event, void* arg)
	{
		BaseHandler* server = (BaseHandler *)arg;
		server->on_write(sock_fd, event);
	}

	static void s_on_read(int sock_fd, short event, void* arg)
	{
		BaseHandler* server = (BaseHandler *)arg;
		server->on_read(sock_fd, event);
	}


public:
	virtual void on_write(int sock_fd, short event)
	{
		cout<<"enter on_writer"<<endl;
		char* buffer = this->ev->buffer;
		send(sock_fd, buffer, strlen(buffer), 0);

		free(buffer);
	}

	virtual void on_read(int sock_fd, short event)
	{
		struct event* write_ev;
		int size;

		ev->buffer = (char*)malloc(MEM_SIZE);
		bzero(ev->buffer, MEM_SIZE);
		size = recv(sock_fd, ev->buffer, MEM_SIZE, 0);
		printf("receive data:%s, size:%d\n", ev->buffer, size);
		if (size == 0) 
		{
			release_sock_event(ev);
			close(sock_fd);
			return;
		}

		bzero(ev->buffer, MEM_SIZE);
		event_set(ev->write_ev, sock_fd, EV_WRITE, BaseHandler::s_on_write, this);
		event_base_set(base, ev->write_ev);
		event_add(ev->write_ev, NULL);

		this->handle_process(ev->buffer);

	}

	virtual int handle_process(string input)
	{
		//string content = "Hello World!!!!";
		//memcpy(ev->buffer, content.c_str(), content.length() + 1);

		return 0;
	}


protected:
	struct sock_ev* ev;
	struct event_base* base;
};