#pragma once
#include <iostream> 
#include <memory>
#include <string>
#include <functional>
#include <process.h>
#include <windows.h>


class thread {
public: 
    typedef std::shared_ptr<thread> ptr; 
    
    thread(); 
    virtual ~thread();
    
		
	
private: 



}; // thread



class win_thread : public thread {
public:
	typedef std::shared_ptr<win_thread> ptr;
	win_thread();
	virtual ~win_thread();

	void init();


private:
	HANDLE m_handle;

}; // win_thread
