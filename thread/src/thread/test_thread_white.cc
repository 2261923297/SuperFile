#include "thread.h"
    
void test_shared_ptr() {
    
}

struct PrintThreadArg_t {
	std::string* str;
	unsigned int threadId;
};

void printThread(const std::string& str) {
	DWORD threadId = GetCurrentThreadId();

//	std::cout << "str = " << str << std::endl;
	for(int i = 0; i < 10; i++) {
		std::cout << "thead_id = " << threadId 
				<< ": " << i << ". " << str 
				<< std::endl;
	}
}

unsigned int __stdcall test_thread_fun(void* args) {
	std::string str = *((std::string*)args);

	printThread(str);

	return 0;
}


void PrintThreadMaker(int n)
{
	const int threadNum = n;
	HANDLE handle[threadNum] =  { 0 };
	unsigned int threadId = 0;
	
	std::string str = "print_thread ";	
	for(int i = 0; i < threadNum; i++) {
		//std::cout << "第" << i << "个线程被创建！" << std::endl;
		handle[i] = (HANDLE)_beginthreadex(nullptr, 0, test_thread_fun, (void*)&str, 0, &threadId);
		//std::cout << "thread id = " << threadId << " is start!" << std::endl;
	} 

	for(int i = 0; i < threadNum; i++) {
		WaitForSingleObject(handle[i], INFINITE);
	}
}
void CPP_PrintThreadMaker(int n) {
	const int threadNum = n;
	thread::ptr threads[threadNum] = { 0 };
	std::string printStr = "test_cpp_style";
	for(int i = 0; i < threadNum; i++) {
		std::string threadName = "test_cpp_style_thread";
		threadName += i;
		threads[i] = win_thread::ptr(new win_thread(threadName.c_str(), test_thread_fun, (void*)&printStr));
	}

	for(int i = 0; i < threadNum; i++) {
		threads[i]->start();
	}

}
void test_cpp11_thread() {
	HANDLE handle;
	unsigned int threadId = 0;
	std::cout << "test_cpp11_thread " << std::endl;
	std::string str = "Hello win_thread!";

	handle = (HANDLE)_beginthreadex(nullptr, 0, test_thread_fun, (void*)&str, 0, &threadId);

	
	std::cout << "内核线程句柄 = " << handle << std::endl << "thead id = " << threadId << std::endl;
	if(WAIT_OBJECT_0 == WaitForSingleObject(handle, INFINITE)) {
	
		std::cout << "thread excute end!" << std::endl;

	}
}

void test_win_thread() {
	std::string printStr = "test_win_thread";
	win_thread::ptr wtp = win_thread::ptr(new win_thread("test_thread", test_thread_fun, (void*)&printStr));

	wtp->start();
}

void test_cpp_style_thread() {
	CPP_PrintThreadMaker(5);
}

void test_thread_status() {
	std::string print_str = "status";
	win_thread::ptr wtp = win_thread::ptr(new win_thread("test_status_thread", test_thread_fun, (void*)&print_str));
	wtp->showData();

	wtp->start();

	int i = 20;
	while(i--) {
		wtp->showData();
	}
}
int main() {
    std::cout << "Hello, test thread base!" << std::endl;
//	test_shared_ptr();
    
//	
//	test_cpp11_thread();
//	PrintThreadMaker(5);
//	test_win_thread();
//
//	test_cpp_style_thread();
	test_thread_status();
	return 0;
}
    
