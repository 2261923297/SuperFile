#include "thread.h"
#include <string>
    
thread::thread() {
	m_threadName = "UNKNOWN";
	m_status = ThreadStatus::Status::NOINIT;
	m_threadId = 0;
}

thread::~thread() {
	m_threadId = 0;
	m_status = ThreadStatus::Status::DESTORIED;

}
    
win_thread::win_thread() {
	m_threadHandle = 0;
}

win_thread::~win_thread() {
	if(WAIT_OBJECT_0 == WaitForSingleObject(m_threadHandle, INFINITE)) {
		std::cout << "thread: " << m_threadName 
			<< ", handle = " << m_threadHandle
			<< ", id = " << m_threadId << " is finished" 
			<< std::endl;
	}

	CloseHandle(m_threadHandle);

}

win_thread::win_thread(const std::string& name, win_thread::Cb_t cb, void* argList) : thread(name){
	setCb(cb);
	setArgList(argList);
	init();
	m_threadName = name;
	
}
void win_thread::init() {
	m_threadHandle = (HANDLE)_beginthreadex(nullptr, m_stackSize, m_cb, m_funcArgs, CREATE_SUSPENDED, &m_threadId);
	m_status = ThreadStatus::Status::READY;
}

int win_thread::start() {
	resume();
	
	return 0;
}


int win_thread::hangup() {
	m_status = ThreadStatus::Status::HANGUP;
	SuspendThread(m_threadHandle);

	return 0;
}

int win_thread::resume() {
	m_status = ThreadStatus::Status::RUNNING;
	ResumeThread(m_threadHandle);

	return 0;
}

int win_thread::destory() {

	return 0;
}
int win_thread::resetFunction(win_thread::Cb_t cb, void* argList) {
	setCb(cb);
	setArgList(argList);
	_endthreadex(1);
	return 0;
}
