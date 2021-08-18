#include "tree.h"
#include <string>

tree::tree() {
	m_root = nullptr;
	
	m_leafNum = 0;
	m_nodeNum = 0;
	m_depth = 0;
}
    
tree::~tree() {
    delTree(m_root);
}
int tree::compare(const Node& n1, const Node& n2) {
	if(n1.getData() >= n2.getData()) {
		return 1;
	} 

	return 0;
}

void tree::delTree(Node* root) {
	if(root == nullptr) 
		return;
	if(root->getLeft() != nullptr) {
		delTree(root->getLeft());
	}
	if(root->getRight() != nullptr) {
		delTree(root->getRight());
	}
//	std::cout << "del node_data = " << root->getData() << std::endl;
	m_nodeNum--;
}

void tree::insert(Node* tree, Node* node) {
	
	if(compare(*tree, *node)) {
		if(tree->getLeft() == nullptr) {
/*
			std::cout << "node_data = " << tree->getData()
				<< ", left = " << node->getData()
				<< std::endl;
*/
			tree->setLeft(node);
		} else {
			insert(tree->getLeft(), node);
		}
	} else {
		if(tree->getRight() == nullptr) {
			tree->setRight(node);
/*
			std::cout << "node_data = " << tree->getData()
				<< ", right = " << node->getData()
				<< std::endl;
*/
		} else {
			insert(tree->getRight(), node);
		}
	}

}

void tree::addNode(Node::data_t val) {
	Node* node = new Node(val);
	addNode(node);
}

void tree::addNode(Node* node) {
	if(node == nullptr) 
		return;
	m_nodeNum++;
	if(m_root == nullptr) {
		m_root = node;
		return ;
	}
	Node* tmpNode = m_root;
	insert(tmpNode, node);
}

void tree::postorder(const Node* node) {
	if(node->getLeft()) {
		postorder(node->getLeft());
	} 
	if(node->getRight()) {
		postorder(node->getRight());
	}
	std::cout << node->toString() << ", ";
}//后续遍历

void tree::inorder(const Node* node) {
	if(node->getLeft() != nullptr) {
		inorder(node->getLeft());
	}
	std::cout << node->toString() << ", ";
	if(node->getRight() != nullptr) {
		inorder(node->getRight());
	}
}//中序遍历

void tree::preorder(const Node* node) {
	//std::cout << "preorder " << std::endl;
	std::cout << node->toString() << ", ";
	if(node == nullptr) {
		std::cout << "order is nullptr, cat^t oder" << std::endl;
	}
	if(node->getLeft() != nullptr) {
		preorder(node->getLeft());
	} 
	if(node->getRight() != nullptr) {
		preorder(node->getRight());
	}

}//前序遍历
   
