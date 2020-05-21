#include<stdlib.h>
#include<stdio.h>
#include "Stack.h"



//int 型数据结点
typedef struct iSNode {
	int data;
	void* next = NULL;
}iSNode;



//char 型数据结点
typedef struct cSNode {
	char data;
	void* next = NULL;
}cSNode;



Stack_i::Stack_i(void)
	:Stack::Stack() {
	iSNode* snode;

	//链栈的头节点
	snode = (iSNode*)malloc(sizeof iSNode);
	if (snode == NULL)	exit(-2);
	base = top = snode;
	size = 0;
}



Stack_c::Stack_c(void)
	:Stack::Stack(){
	cSNode* snode;

	//链栈的头节点
	snode = (cSNode*)malloc(sizeof cSNode);
	if (snode == NULL)	exit(-2);
	base = top = snode;
	size = 0;
}



void Stack_i::push(void* pnt) {

	// 获取要储存的值
	int i = *(int*)pnt;

	// 申请新节点的空间，赋值
	iSNode* snode;
	snode = (iSNode*)malloc(sizeof iSNode);
	if (snode == NULL)	exit(-2);
	snode->data = i;

	//将新节点插入到链表头的头节点后面
	snode->next = ((iSNode*)top)->next;
	((iSNode*)top)->next = snode;

	//若压栈之前是空栈，更新base指针
	if (top == base)
		base = snode;

	size++;
}



void Stack_i::get_top(void* pnt) {
	*(int*)pnt = ((iSNode*)((iSNode*)top)->next)->data;
}



void Stack_i::pop(void* pnt) {

	//储存将被释放的结点
	iSNode* snode= (iSNode*)top;

	//头指针后移一个元素，头指针现在所指的元素即栈顶元素，赋值
	top = ((iSNode*)top)->next;
	*(int*)pnt = ((iSNode*)((iSNode*)top))->data;

	free(snode);
	size--;
}



Stack_i::~Stack_i(void){
	printf("Stack_i::~Stack_i\n");
}




void Stack_c::push(void* pnt) {

	// 获取要储存的值
	char c = *(char*)pnt;

	// 申请新节点的空间，赋值
	cSNode* snode;
	snode = (cSNode*)malloc(sizeof cSNode);
	if (snode == NULL)	exit(-2);
	snode->data = c;

	//将新节点插入到链表头的头节点后面
	snode->next = ((cSNode*)top)->next;
	((cSNode*)top)->next = snode;

	//若压栈之前是空栈，更新base指针
	if (top == base)
		base = snode;

	size++;
}



void Stack_c::pop(void* pnt) {

	//储存将被释放的结点
	cSNode* snode = (cSNode*)top;

	//头指针后移一个元素，头指针现在所指的元素即栈顶元素，赋值
	top = ((cSNode*)top)->next;
	*(char*)pnt = ((cSNode*)((cSNode*)top))->data;

	free(snode);
	size--;
}


void Stack_c::get_top(void* pnt) {
	*(char*)pnt = ((cSNode*)((iSNode*)top)->next)->data;
}

Stack_c::~Stack_c(void) {
	printf("Stack_c::~Stack_c\n");
}



int Stack::get_size(void) {
	return size;
}

Stack::Stack() { }

Stack::~Stack(){ }