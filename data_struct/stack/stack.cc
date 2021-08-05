#include "stack.h"
#include <iostream>

template<class _DataType>   
Stack<_DataType>::Stack(int stackLen) {
	m_stackLen = stackLen;
	m_pStackRoom = (_DataType*)malloc(sizeof(_DataType) * m_stackLen);
	m_stackTop = 0;
}


template<class _DataType>  
Stack<_DataType>::~Stack() { 
	if(nullptr != m_pStackRoom) {
		free(m_pStackRoom);
	}
}

template<class _DataType>  
int Stack<_DataType>::push(Stack::DataType_t data) {
	if(isFull()) {
		std::cout << "stack is full, can^t push data = " << data << std::endl; 
		return -1;
	}

	m_pStackRoom[m_stackTop] = data;
	m_stackTop++;

	return 0;
}

template<class _DataType>  
_DataType Stack<_DataType>::pop() {
	if(isEmpty()) {
		std::cout << "stack is empty" << std::endl;
		return -1;
	}
	m_stackTop--;
	return m_pStackRoom[m_stackTop];
}

template<class _DataType>  
bool Stack<_DataType>::isEmpty() {
	return m_stackTop == 0;
}

template<class _DataType>  
bool Stack<_DataType>::isFull() {
	return m_stackTop == m_stackLen;
}

int test_base() {
	Stack<int> stk;

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

	return 0;
}

void test_stress() {
	Stack<int> stk;
	int nums[33];
	for(int i = 0; i < 32; i++) {
		nums[i] = i;
	}

	for(int i = 0; i < 33; i++) {
		stk.push(nums[i]);
	}

	for(int i = 0; i < 33; i++) {
		std::cout << "stack[" << i << "] = " << stk.pop() << "\t";
		if(0 != ((i + 1) % 5)) std::cout << std::endl;

	}
}

int main() {
	//test_base();
	test_stress();
	//std::cout << "hello stack" << std::endl;
	return 0;
}
