#include <iostream>
#include <time.h>

#define CYCLE_SIZE 1000000

void test_array() {
	int array[1024] = {
		0
	};
	int array_size = 1024, cycle_size = CYCLE_SIZE;

	while(cycle_size--) {
		for(int i = 0; i < array_size; i++) {
			array[i] = i;
		}
	}
}

void test_malloc() {
	int array_size = 1024;
	int* array = (int*)malloc(sizeof(int) * array_size);
	int cycle_size = CYCLE_SIZE;

	while(cycle_size--) {
		for(int i = 0; i < array_size; i++) {
			array[i] = i;
		}
	}
}


int get_array_time() {
	clock_t start = 0, finish = 0;
	start = clock();
	test_array();
	finish = clock();

	double use_time = (double)(finish - start) / CLOCKS_PER_SEC;

	std::cout << "array_time = " << use_time << std::endl;
	return 0;
}

int get_malloc_time() {
	clock_t start = 0, finish = 0;
	start = clock();
	test_malloc();
	finish = clock();

	double use_time = (double)(finish - start) / CLOCKS_PER_SEC;

	std::cout << "malloc_time = " << use_time << std::endl;

	return 0;
}

int main() {
	std::cout << "begin test" << std::endl;
//	get_array_time();
	get_malloc_time();

	std::cout << "end test" << std::endl;
	return 0;
}
