#pragma once

#include <iostream>
#include <stdio.h>

template<class _DataType>
class Stack {
public:
	using DataType_t = _DataType;
	Stack(int stackLen = 32);
	~Stack();

	//data: push to stack, return err -1, sucess 0
	int push(_DataType data);

	//reutrn -1 stack is empty, > -1 stack pop data
	_DataType pop();

	bool isEmpty();
	
	bool isFull();
private:
	_DataType* m_pStackRoom;
	int m_stackLen;
	int m_stackTop;
};
