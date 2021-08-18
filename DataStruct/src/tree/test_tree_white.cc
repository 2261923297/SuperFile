#include "tree.h"
#include <iostream>
tree* initTree(Node::data_t* datas, int size) {
	tree* ans = new tree;
	for(int i = 0; i < size; i++) {
		ans->addNode(datas[i]);
	}
	std::cout << "InitTree: size = " << ans->size() << std::endl;

	
	return ans;
}
Node::data_t* initDatas(int& size) {
	size = 8;
	static Node::data_t datas[8];
	for(int i = 0; i < size; i++) {
		datas[i] = i;
	}
	return datas;
}

Node::data_t* initComplexDatas(int& size) {
	size = 10;
	static Node::data_t ans[10] = { 20, 11, 30, 22, 43, 55, 78, 13, 15, 98 };
	
	return ans;
}


void test_framework(tree* _t) {
	
	tree* t = _t;

	std::cout << "\tpostorder: ";
	t->postorder(t->getRoot());
	std::cout << std::endl;

	std::cout << "\tinorder: " ;
	t->inorder(t->getRoot());
	std::cout << std::endl;

	std::cout << "\tpreorder: ";
	t->preorder(t->getRoot());
	std::cout << std::endl;
	
}
    
int main() {
    	std::cout << "Hello, test tree base!" << std::endl;
    	int size = 0;
    	Node::data_t* datas;
	tree* t = nullptr;
	std::cout << "order array: " << std::endl;
	datas = initDatas(size);
	t = initTree(datas, size);
	test_framework(t);

	std::cout << "complex array" << std::endl;
	datas = initComplexDatas(size);
	delete t;
	t = nullptr;
	t = initTree(datas, size);
	test_framework(t);
	

	delete t;
	t = nullptr;
    	return 0;
}
    
