#pragma once
#include <iostream> 
#include <memory>

typedef int NodeDataType;
typedef struct Node {
public:
	typedef NodeDataType data_t;
	Node(data_t val) {
		data = val;
		left = right = nullptr;
	}
	
	~Node() {
		
	}

	data_t data;
	Node* left;
	Node* right;
public:
	const data_t& getData() { return data; }
} Node;

class tree {
public: 
    typedef std::shared_ptr<tree> ptr; 
    
    tree(); 
    virtual ~tree();

	void addNode(Node::data_t val);
	void addNode(Node* node);
	

	int compare(const Node& n1, const Node& n2);
	
	void postorder(const Node* node);//后续遍历

	void inorder(const Node* node); //中序遍历

	void preorder(const Node* node);//前序遍历

	const Node* getRoot() { return m_root; }
protected:
	void insert(Node* tree, Node* node);
private: 
    Node* m_root;
	
	int m_leafNum;
	int m_nodeNum;
	int m_depth;


}; // tree
    
