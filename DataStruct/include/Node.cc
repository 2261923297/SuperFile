#include "Node.h"


#define NODE_TYPE double

int main() {
	NODE_TYPE node_size = 10.1 ;
	LinkNode<NODE_TYPE>* head = LinkNode<NODE_TYPE>::NewNode(0);
	LinkNode<NODE_TYPE>* tmp = head, *newNode = nullptr;
	while(node_size-- > 0) {
		newNode = LinkNode<NODE_TYPE>::NewNode(node_size);
		tmp->setNext(newNode);
		tmp = newNode;
	}
	std::cout << "init end" << std::endl;
	tmp = head;
	for(; node_size <10; node_size++) {
		std::cout << tmp->getData() << ",";
		tmp = tmp->getNext();
	}
	return 0;
}



