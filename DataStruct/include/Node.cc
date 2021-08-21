#include <iostream>
#include <memory>

template<class _DataType>
class Node {
public:
	typedef std::shared_ptr<Node> ptr;
	typedef _DataType data_t;
	
	virtual const data_t& getData() { return m_data; }
	virtual void setData(const data_t& val) { m_data = val;	}


protected:
	data_t m_data;
}; // Node

template<class _DataType>
class SinglyLinkNode : public Node<_DataType> {
public:
	typedef std::shared_ptr<data_t> data_ptr;
	
	const data_ptr& getDataPtr() { return m_next; }

	void setDataPtr(const data_ptr& ptr) { m_next = ptr; }

	void setDataPtr(data_t* val) { m_next.reset(val); }

	

protected:
	data_ptr m_next;
}; // SinglyLinkNode


int main() {
	std::cout << "Hello, Node!" << std::endl;

	return 0;
}
