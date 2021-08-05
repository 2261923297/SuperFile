#include <iostream>
#include "../stack.h"


int test_base() {
	Stack<int> stk;

	int need_push[] = {
		1, 2, 3
	};

	for(int i = 0; i < 3; i++) {
		stk.push(need_push[i]);
	}

	for(int i = 0; i < 3; i++) {
		std::cout << stk.pop() << '\t';
	}
	std::cout << std::endl;
}

void test_stress() {
	Stack<int> stk;
	int nums[33];
	for(int i = 0; i < 32; i++) {
		nums[i] = i;
	}

	for(int i = 0; i < 33; i++) {
		stk.push(nums[i]);
	}

	for(int i = 0; i < 33; i++) {
		std::cout << "stack[" << i << "] = " << stk.pop() << "\t";
		if((i + 1) % 5) std::cout << std::endl;

	}
}

int main() {
	//test_base();
	test_stress();
	//std::cout << "hello stack" << std::endl;
	return 0;
}
