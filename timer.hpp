#include <sys/signal.h>
#include <event.h>



class Timer 
{
public:
	Timer()
	{
		base = event_init();//生成Reactor实例
	}

	~Timer()
	{

	}


protected:
	void static s_timeout_cb(int fd, short event, void* argc)//信号回调函数
	{
		Timer* timer = (Timer *)argc;
		timer->timeout_cb(fd, event, argc);
	}

protected:
	void signal_cb(int fd, short event, void* argc)//信号回调函数
	{
		struct event_base* base = (event_base*)argc;//获取传递进来的Reactor对象
		struct timeval delay = { 2,0 };//设置延时结构体，延时时间2s
		printf("Caught an interrupt signal; exciting cleanly in two seconds...\n");
		event_base_loopexit(base, &delay);
	}

public:
	virtual void timeout_cb(int fd, short event, void* argc)
	{
		printf("Hello Libevent %d!\n", data++);
		event_add(timeout_event, &tv);
	}

public:
	void run()
	{
		//signal_event = evsignal_new(base, SIGINT, signal_cb, base);//生成SIGINT信号的事件处理器
		//event_add(signal_event, NULL);//将事件处理器加入到注册事件队列

		timeout_event = evtimer_new(base, Timer::s_timeout_cb, this);//生成定时器处理器
		event_add(timeout_event, &tv);//将定时器处理器加入注册事件队列

		event_base_dispatch(base);//分发事件

		event_free(timeout_event);
		//event_free(signal_event);
		event_base_free(base);
	}

protected:
	struct event_base* base = NULL;
	//struct event* signal_event = NULL;
	struct event* timeout_event = NULL;
	timeval tv = { 1,0 };

	int data = 0;

};
