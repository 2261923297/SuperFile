#include "stack.h"
#include <iostream>
int Stack::push(int data) {
	if(isFull()) {
		std::cout << "stack is full, can^t push data = " << data << std::endl; 
		return -1;
	}

	m_stackRoom[m_stackTop] = data;
	m_stackTop++;

	return 0;
}

template<class _DataType>   
_DataType Stack::pop() {
	if(isEmpty()) {
		std::cout << "stack is empty" << std::endl;
		return -1;
	}
	m_stackTop--;
	return m_stackRoom[m_stackTop];
}

bool Stack::isEmpty() {
	return m_stackTop == 0;
}

bool Stack::isFull() {
	return m_stackTop == 32;
}

int test_base() {
	Stack stk;

	int need_push[] = {
		1, 2, 3
	};

	for(int i = 0; i < 3; i++) {
		stk.push(need_push[i]);
	}

	for(int i = 0; i < 3; i++) {
		std::cout << stk.pop() << '\t';
	}
	std::cout << std::endl;
}
int main() {
	test_base();
	std::cout << "hello stack" << std::endl;
	return 0;
}
