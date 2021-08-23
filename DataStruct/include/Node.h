#include <iostream>
#include <memory>

template<class _DataType>
class Node {
public:
	typedef std::shared_ptr<Node> ptr;
	typedef _DataType data_t;
	
	virtual const data_t& getData() const { return m_data; }
	virtual void setData(const data_t& val) { m_data = val;	}


protected:
	data_t m_data;
}; // Node

template<class _DataType>
class LinkNode : public Node<_DataType> {
public:
	using ptr = std::shared_ptr<LinkNode<_DataType> >;
	using type_t = LinkNode;
	using pType_t = LinkNode*;
	using data_t = _DataType;
public:
	static LinkNode* NewNode(const data_t& val = { 0 }) { return new LinkNode(val); }

public:
	LinkNode(const data_t& val) {
		this->setData(val);
		m_next = nullptr;
	}
	~LinkNode() {
		
	}
	const pType_t getNext() const { return m_next; }

	void setNext(const pType_t pVal) { m_next = pVal; }

	pType_t getRealNext() const { return m_next; }

	
protected:
	LinkNode* m_next;
	LinkNode* m_prov;
}; // LinkNode

