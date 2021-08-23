
#define ENUM_CLASS_NAME ThreadStatus
#define ENUM_NAME		Status
#define ENUM_BODY \
	ENUM_MESSAGE(Status, IDLE, RUNNING, END)

#define ENUM_VALUES  \
	xx(ThreadStatus::Status::IDLE)			\
	xx(ThreadStatus::Status::RUNNING)       \
	xx(ThreadStatus::Status::END)			\
//

#include "EnumReflection.h"
#include <iostream>

    
void test_shared_ptr() {
    
}
    
int main() {
    std::cout << "Hello, test EnumReflection base!" << std::endl;
	std::cout << ThreadStatus::Status::RUNNING << std::endl;


	test_shared_ptr();
    
    return 0;
}
    
