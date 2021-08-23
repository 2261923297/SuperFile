#pragma once
#include <iostream> 
#include <memory>
#include "../../include/Node.h"



template<class _DataType>
class link {
public: 
    typedef std::shared_ptr<link> ptr; 
	using node_t = SinglyLinkNode<_DataType>;
	using node_p = SinglyLinkNode<_DataType>*;
    using data_t = _DataType;
	
	link(); 
    virtual ~link();
    
	void push_back(const data_t& val);
	void push_front(const data_t& val);

	data_t pop_front();
	data_t pop_back();
    
private: 
    size_t m_size;
	
	node_p m_head;

	node_p m_front;
	node_p m_back;
	node_p m_proBack;


}; // link
    
