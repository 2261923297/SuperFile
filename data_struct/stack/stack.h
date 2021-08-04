#pragma once

#include <iostream>

template<class _DataType>
class Stack {
public:
	Stack(int stackLen = 32) {
		m_stackLen = stackLen;
		m_pStackRoom = (_DataType*)mallco(sizeof(_DataType) * m_stackLen);
		m_stackTop = 0;
	}
	~Stack() { 
		if(nullptr != m_pStackRoom) {
			free(m_pStackRoom);
		}
	}

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
