#include <stdio.h>
#include <stdlib.h>

struct stack {
	int* stack_room;
	int top;
	int len;
};

bool isEmpty(struct stack* s) {
	bool ans = false;
	if(s->top == 0) { return true; }
	return ans;

}

bool isFull(struct stack* s) {
	bool ans = false;
	if(s->top >= s->len) { return true; }	
	return ans;
	
}


int pop(struct stack* s) {
	if(isEmpty(s)) { 
		printf("stack is empty, can^t pop\n");
		return -1; 
	}
	s->top--;
	return s->stack_room[s->top];
}


struct stack* InitStack(int stack_size) {
	struct stack* s = (struct stack*)malloc(sizeof(struct stack));
	s->len = stack_size;
	s->stack_room = (int*)malloc(sizeof(int) * s->len);
	s->top = 0;

	return s;
}
int push(struct stack* s, int data) {
	int ans = 0;
	
	if(isFull(s)) { 
		printf("stack is full, can^t push");
		return -1; 
	}

	s->stack_room[s->top] = data;
	s->top++;

	return ans;
}

void func() {
	int nums[3] = { 1, 2, 3 };
	struct stack* s = InitStack(32);
	for(int i = 0; i < 3; i++) {
		push(s, nums[i]);
	}

	for(int i = 0; i < 3; i++) {	
		printf("%d, ", pop(s));
	}
}







int main() {
	func();
	printf("Hello kkStack!");
	
	return 0;
}