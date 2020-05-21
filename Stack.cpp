#include<stdlib.h>
#include<stdio.h>
#include "Stack.h"



//int �����ݽ��
typedef struct iSNode {
	int data;
	void* next = NULL;
}iSNode;



//char �����ݽ��
typedef struct cSNode {
	char data;
	void* next = NULL;
}cSNode;



Stack_i::Stack_i(void)
	:Stack::Stack() {
	iSNode* snode;

	//��ջ��ͷ�ڵ�
	snode = (iSNode*)malloc(sizeof iSNode);
	if (snode == NULL)	exit(-2);
	base = top = snode;
	size = 0;
}



Stack_c::Stack_c(void)
	:Stack::Stack(){
	cSNode* snode;

	//��ջ��ͷ�ڵ�
	snode = (cSNode*)malloc(sizeof cSNode);
	if (snode == NULL)	exit(-2);
	base = top = snode;
	size = 0;
}



void Stack_i::push(void* pnt) {

	// ��ȡҪ�����ֵ
	int i = *(int*)pnt;

	// �����½ڵ�Ŀռ䣬��ֵ
	iSNode* snode;
	snode = (iSNode*)malloc(sizeof iSNode);
	if (snode == NULL)	exit(-2);
	snode->data = i;

	//���½ڵ���뵽����ͷ��ͷ�ڵ����
	snode->next = ((iSNode*)top)->next;
	((iSNode*)top)->next = snode;

	//��ѹջ֮ǰ�ǿ�ջ������baseָ��
	if (top == base)
		base = snode;

	size++;
}



void Stack_i::get_top(void* pnt) {
	*(int*)pnt = ((iSNode*)((iSNode*)top)->next)->data;
}



void Stack_i::pop(void* pnt) {

	//���潫���ͷŵĽ��
	iSNode* snode= (iSNode*)top;

	//ͷָ�����һ��Ԫ�أ�ͷָ��������ָ��Ԫ�ؼ�ջ��Ԫ�أ���ֵ
	top = ((iSNode*)top)->next;
	*(int*)pnt = ((iSNode*)((iSNode*)top))->data;

	free(snode);
	size--;
}



Stack_i::~Stack_i(void){
	printf("Stack_i::~Stack_i\n");
}




void Stack_c::push(void* pnt) {

	// ��ȡҪ�����ֵ
	char c = *(char*)pnt;

	// �����½ڵ�Ŀռ䣬��ֵ
	cSNode* snode;
	snode = (cSNode*)malloc(sizeof cSNode);
	if (snode == NULL)	exit(-2);
	snode->data = c;

	//���½ڵ���뵽����ͷ��ͷ�ڵ����
	snode->next = ((cSNode*)top)->next;
	((cSNode*)top)->next = snode;

	//��ѹջ֮ǰ�ǿ�ջ������baseָ��
	if (top == base)
		base = snode;

	size++;
}



void Stack_c::pop(void* pnt) {

	//���潫���ͷŵĽ��
	cSNode* snode = (cSNode*)top;

	//ͷָ�����һ��Ԫ�أ�ͷָ��������ָ��Ԫ�ؼ�ջ��Ԫ�أ���ֵ
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