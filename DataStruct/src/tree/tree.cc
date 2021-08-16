#include "tree.h"
#include <string>

tree::tree() {
	m_root = nullptr;
	
	m_leafNum = 0;
	m_nodeNum = 0;
	m_depth = 0;
}
    
tree::~tree() {
    
}
int tree::compare(const Node& n1, const Node& n2) {
	if(n1.data >= n2.data) {
		return 1;
	} 

	return 0;
}

void tree::insert(Node* tree, Node* node) {
	if(compare(*tree, *node)) {
		if(tree->left == nullptr) {
			tree->left = node;
		} else {
			insert(tree->left, node);
		}
	} else {
		if(tree->right == nullptr) {
			tree->right = node;
		} else {
			insert(tree->right, node);
		}
	}
}

void tree::addNode(Node::data_t val) {
	Node* node = new Node(val);
	addNode(node);
}

void tree::addNode(Node* node) {
	Node* tmpNode = m_root;
	insert(tmpNode, node);
}

void tree::postorder(const Node* node) {
	if(node->left) {
		postorder(node->left);
	} 
	if(node->right) {
		postorder(node->right);
	}
	std::cout << node->data << ", ";
}//后续遍历

void tree::inorder(const Node* node) {
	if(node->left) {
		inorder(node->left);
	}
	std::cout << node->data << ", ";
	if(node->right) {
		inorder(node->right);
	}
}//中序遍历

void tree::preorder(const Node* node) {
	std::cout << node->data << ", ";
	
	if(node->left) {
		postorder(node->left);
	} 
	if(node->right) {
		postorder(node->right);
	}

}//前序遍历
   
