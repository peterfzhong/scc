#include <sys/signal.h>
#include <event.h>



class Timer 
{
public:
	Timer()
	{
		base = event_init();//����Reactorʵ��
	}

	~Timer()
	{

	}


protected:
	void static s_timeout_cb(int fd, short event, void* argc)//�źŻص�����
	{
		Timer* timer = (Timer *)argc;
		timer->timeout_cb(fd, event, argc);
	}

protected:
	void signal_cb(int fd, short event, void* argc)//�źŻص�����
	{
		struct event_base* base = (event_base*)argc;//��ȡ���ݽ�����Reactor����
		struct timeval delay = { 2,0 };//������ʱ�ṹ�壬��ʱʱ��2s
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
		//signal_event = evsignal_new(base, SIGINT, signal_cb, base);//����SIGINT�źŵ��¼�������
		//event_add(signal_event, NULL);//���¼����������뵽ע���¼�����

		timeout_event = evtimer_new(base, Timer::s_timeout_cb, this);//���ɶ�ʱ��������
		event_add(timeout_event, &tv);//����ʱ������������ע���¼�����

		event_base_dispatch(base);//�ַ��¼�

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
