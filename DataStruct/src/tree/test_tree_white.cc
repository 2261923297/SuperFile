#include "tree.h"

tree* initTree(Node::data_t* datas, int size) {
	tree* ans = new tree;
	for(int i = 0; i < size; i++) {
		ans->addNode(datas[i]);
	}
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
void test_shared_ptr() {
	int data_size;
	Node::data_t* datas = initDatas(data_size);

	tree* t = initTree(datas, data_size);

	t->postorder(t->getRoot());
	std::cout << std::endl;

	t->inorder(t->getRoot());
	std::cout << std::endl;

	t->preorder(t->getRoot());
	std::cout << std::endl;
	
}
    
int main() {
    std::cout << "Hello, test tree base!" << std::endl;
    test_shared_ptr();
    
    return 0;
}
    
