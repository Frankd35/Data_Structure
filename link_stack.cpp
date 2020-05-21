#include<stdlib.h>
#include<stdio.h>



// link stack



typedef int elemtype;	//��������Ԫ������elemtype



//��ջ���
typedef struct SNode {	
	elemtype data;	//����Ԫ��
	struct SNode* next;	//��һ������ָ��
}SNode;



typedef SNode* lstack;	//���ָ��



//ջ�ṹ����
//��ջջ��������ͷ��ջ������������
typedef struct LinkStack {
	lstack top;	//ջ��ָ��
	lstack base;	//ջ��ָ��
	int size = 0;	//ջ�Ĵ�С
} linkstack;



//��ʼ��ջ
//����ֵ����ʼ���ɹ� 1��ʧ�� -2
int init_lstack(lstack* ls, LinkStack linkstack) {
	*ls = (lstack)malloc(sizeof SNode);
	if (*ls == NULL)	exit(-2);
	(**ls).next = NULL;

	//��ջͷָ�����βָ��
	linkstack.top = *ls;
	linkstack.base = *ls;
	return 1;
}



//����ջ
void destroy_lstack(LinkStack* ls) {
	
	//��ͷ�ڵ��ͷ����нڵ㴢��ռ�
	lstack pnt;
	while (ls->top != ls->base)
	{
		pnt = ls->top;
		ls->top = ls->top->next;
		free(pnt);
	}
	free(ls->top);
}



//����ջ
void clear_lstack(LinkStack* ls)
{
	destroy_lstack(ls);
	init_lstack(&ls->base, *ls);
}



//ȡ��ջ��Ԫ�ظ�ֵ�� e ����
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int get_top_lstack(LinkStack ls, elemtype* e) {
	if (ls.base == ls.top) return 0;
	*e = ls.top->next->data;
	return 1;
}



//ջ�ĳ���
//����ֵ��ջ�ĳ���
int lenof_lstack(LinkStack ls) {

	int length = 0;	//ջ�ĳ���
	lstack node = ls.top;	//���̽��

	//��̽��δ�ﵽջ��ʱ��̽��ǰ��һ�������ȼ� 1
	while (node != ls.base)
	{
		length++;
		node = node->next;
	}
	return length;
}



//ջ�Ƿ�Ϊ��
//����ֵ����ջ���� 1�� �ǿ� 0
int isempty_lstack(LinkStack ls) {
	return ls.base == ls.top ? 1 : 0;
}



//ѹջ
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� -2
int push_lstack(LinkStack* ls, elemtype e) {

	//Ϊ�½ڵ�����ռ䣬ʧ�ܷ��� -2
	lstack new_node;
	new_node =(lstack)malloc(sizeof SNode);
	if (new_node == NULL)	exit(-2);

	//���½ڵ���뵽����ͷ��ͷ�ڵ����
	new_node->next = ls->top->next;
	new_node->data = e;
	ls->top->next = new_node;

	//��ѹջ֮ǰ�ǿ�ջ������baseָ��
	if (ls->base == ls->top)
		ls->base = new_node;

	ls->size++;
	return 1;
}



//��ջ��ջ��Ԫ�ظ�ֵ�� e
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
void pop_lstack(LinkStack* ls, elemtype* e) {

	//����ջ֮ǰ�ǿ�ջ������ 0
	if (ls->base == ls->top)
		return 0;

	lstack pnt;	//���潫���ͷŵĽ��
	pnt = ls->top;

	//ͷָ�����һ��Ԫ�أ�ͷָ��������ָ��Ԫ�ؼ�ջ��Ԫ�أ���ֵ�� e
	ls->top = ls->top->next;
	*e = ls->top->next->data;

	//�ͷŶ�����ԭͷ�ڵ㣩
	free(pnt);

	ls->size--;
	return 1;
}