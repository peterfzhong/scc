#include "timer.hpp"
#include "server.hpp"

// int client()
// {
// 	// build the message to be sent  
// 	int length = 800; // the size of message  
// 	char* mesg = (char*)malloc((length + 1) * sizeof(char)); // Look out the end mark '/0' of a C string  
// 	if (mesg == NULL)
// 		exit(1);
// 	int i;
// 	for (i = 0; i<length; i++)
// 		strcat(mesg, "a");
// 
// 	printf("%s\n", mesg);
// 	printf("%d\n", (int)strlen(mesg));
// 
// 	// build socket  
// 	int port = 10000;
// 	struct sockaddr_in my_address;
// 	memset(&my_address, 0, sizeof(my_address));
// 	my_address.sin_family = AF_INET;
// 	my_address.sin_addr.s_addr = htonl(0x7f000001); // 127.0.0.1  
// 	my_address.sin_port = htons(port);
// 
// 	// build event base  
// 	struct event_base* base = event_base_new();
// 
// 	// set TCP_NODELAY to let data arrive at the server side quickly  
// 	evutil_socket_t fd;
// 	fd = socket(AF_INET, SOCK_STREAM, 0);
// 	struct bufferevent* conn = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
// 	int enable = 1;
// 	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable)) < 0)
// 		printf("ERROR: TCP_NODELAY SETTING ERROR!\n");
// 	//bufferevent_setcb(conn, NULL, NULL, NULL, NULL); // For client, we don't need callback function  
// 	bufferevent_enable(conn, EV_WRITE);
// 	if (bufferevent_socket_connect(conn, (struct sockaddr*)&my_address, sizeof(my_address)) == 0)
// 		printf("connect success\n");
// 
// 	// start to send data  
// 	bufferevent_write(conn, mesg, length);
// 	// check the output evbuffer  
// 	struct evbuffer* output = bufferevent_get_output(conn);
// 	int len = 0;
// 	len = evbuffer_get_length(output);
// 	printf("output buffer has %d bytes left\n", len);
// 
// 	event_base_dispatch(base);
// 
// 	free(mesg);
// 	mesg = NULL;
// 
// 	bufferevent_free(conn);
// 	event_base_free(base);
// 
// 	printf("Client program is over\n");
// 
// 	return 0;
// }

int client()
{
	return 0;
}

int main(int argc, char** argv)
{
	//Timer timer;
	//timer.run();

	string cmd = argv[1];
	if (cmd == "svr")
	{
		Server server;
		server.run();
	}
	else {
		client();
	}

	return 0;
}