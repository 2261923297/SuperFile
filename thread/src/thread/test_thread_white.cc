#include "thread.h"
    
void test_shared_ptr() {
    
}

unsigned int __stdcall test_thread_fun(void*) {
	for(int i = 0; i < 20; i++) {

		std::cout << i << ". hello, tt_thread!" << std::endl;
	}


	return 0;
}

void test_cpp11_thread() {
	HANDLE handle;
	unsigned int threadId = 0;
	handle = (HANDLE)_beginthreadex(nullptr, 0, test_thread_fun, nullptr, 0, &threadId);
	
	if(WAIT_OBJECT_0 == WaitForSingleObject(handle, INFINITE)) {
	
		std::cout << "thread excute end!" << std::endl;

	}
	std::cout << "内核线程句柄 = " << handle << std::endl
			<< "thead id = " << threadId << std::endl;
}
int main() {
    std::cout << "Hello, test thread base!" << std::endl;
    test_shared_ptr();
    
	test_cpp11_thread();

    return 0;
}
    
