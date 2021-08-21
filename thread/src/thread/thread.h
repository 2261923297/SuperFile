#pragma once
#include <iostream> 
#include <memory>
#include <string>
#include <functional>
#include <process.h>
#include <windows.h>
#include <stdint.h>
#include <functional>

/**/

class ThreadStatus {
public:
	enum Status {
		NOINIT, READY, RUNNING, HANGUP, FINISH, DESTORIED
	};

};

static std::ostream& operator<<(std::ostream& os, ThreadStatus::Status status) {
	switch(status) {
#define xx(statu) \
		case (ThreadStatus::Status)statu : \
			os << #statu; \
			break;
		xx(ThreadStatus::Status::NOINIT)
		xx(ThreadStatus::Status::READY)
		xx(ThreadStatus::Status::RUNNING)
		xx(ThreadStatus::Status::HANGUP)
		xx(ThreadStatus::Status::FINISH)
		xx(ThreadStatus::Status::DESTORIED)
	}

	return os;
}
	
class thread {
public: 
    typedef std::shared_ptr<thread> ptr; 
    
	thread() ;
	
	thread(const std::string& threadName) {
		m_threadName = threadName;
		m_status = ThreadStatus::Status::NOINIT;
		m_threadId = 0;
	}

    virtual ~thread();
   
	uint64_t getThreadId() { return m_threadId; }

	const std::string& getThreadName() { return m_threadName; }
	
	void setThreadName(const std::string& name) { m_threadName = name; }

	virtual int start() = 0;

	virtual int hangup() = 0;

	virtual int resume() = 0;

	virtual int destory() = 0;
	
protected: 
	std::string				m_threadName;
	unsigned int			m_threadId;
	ThreadStatus::Status	m_status;
}; // thread



class win_thread : public thread {
public:
	typedef std::shared_ptr<win_thread> ptr;
	typedef unsigned int (__attribute__((__stdcall__))*Cb_t)(void*);
	win_thread();

	win_thread(const std::string& name) : thread(name) {

	}
	win_thread(const std::string& name, Cb_t cb, void* argList);

	virtual ~win_thread();
	
	HANDLE getThreadHandle() { return m_threadHandle; }

	void init();
	
	int start() override;

	int hangup() override;

	int resume() override;

	int destory() override;

	void resetFunction(Cb_t cb, void* argList);

	void setCb(Cb_t cb) { m_cb = cb; } 

	void setArgList(void* args) { m_funcArgs = args;	}
public:
	void showData() {
		std::cout << "thread_name = " << m_threadName << " >> datas: " 
				<< "\n\thandle_int: " << (unsigned int)m_threadHandle
				<< ", handle_ptr: " << m_threadHandle
				<< "\n\tthread_id: " << m_threadId
				<< "\n\tthread_status: " << m_status
				<< std::endl;
	}

private:
	HANDLE m_threadHandle;
	Cb_t m_cb;
	void* m_funcArgs;
	int m_stackSize = 0;

}; // win_thread

/**      _beginthreadex()
 * HANDLE hThread = _beginthreadex {
 *	NULL,							//线程安全属性， 为零默认
 *	0，								//线程所用堆栈大小置零为默认（1M ）
 *	(_beginthreadex_proc_type) cb,	//线程回调函数,
 *	void* NULL,						//线程回调函数的参数
 *	0,								//线程的初始状态，
 *									//	0: run when create; CREATE_SUSPENDED:挂起
 *	(unsigned int*) threadId		//返回线程的ID
 * }
 *
 * */

/**
 * _endThreadEx(int exit);
 *
 * */

/**
 * SuspendThread(uint64_t threadId);  //挂起线程
 *
 * */

/**
 *
 * ResumeThread(uint64_t threadId);  //恢复线程
 *
 * */
