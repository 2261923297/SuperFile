#pragma once
#include <iostream> 
#include <memory>
#include <sstream>
typedef int NodeDataType;

class Node {
public:
	typedef NodeDataType data_t;
	Node(data_t val) { m_data = val; m_left = m_right = nullptr; }	
	virtual ~Node() { }
	
	const data_t& getData() const { return m_data; }
	Node* getLeft() const { return m_left; }
	Node* getRight() const { return m_right; }

	void setData(const data_t& val) { m_data = val;	}
	void setLeft(Node* const val)  { m_left = val; }
	void setRight(Node* const val) { m_right = val; }
private:
	data_t m_data;

	Node* m_left;
	Node* m_right;
public:
	virtual std::string toString() const { std::stringstream ss; ss << m_data; return ss.str(); }
};// class_node;



class tree {
public: 
    typedef std::shared_ptr<tree> ptr; 
    
    tree(); 
    virtual ~tree();

	void addNode(Node::data_t val);
	virtual void addNode(Node* node);
	
	int size() { return m_nodeNum; }
	int compare(const Node& n1, const Node& n2);
	
	void postorder(const Node* node);//后续遍历

	void inorder(const Node* node); //中序遍历

	void preorder(const Node* node);//前序遍历

	const Node* getRoot() { return m_root; }

	void delTree(Node* root);
protected:
	void insert(Node* tree, Node* node);
private: 
    Node* m_root;
	
	int m_leafNum;
	int m_nodeNum;
	int m_depth;


}; // tree
    
