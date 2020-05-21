#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10



/* sequence stack */



typedef int elemtype;	//��������Ԫ������elemtype



typedef struct SeqStack {	//����˳��ջ�ṹ��
	elemtype* top;	//ͷָ��
	elemtype* base;	//βָ��
	int size;	//ջ�Ĵ�С
} sqstack;



//��ʼ��ջ
//����ֵ����ʼ���ɹ� 1��ʧ�� -2
int init_sqstack(sqstack* stack) {
	stack->base = (elemtype*)malloc(STACK_INIT_SIZE * sizeof(sqstack));
	if (stack->base == NULL) exit(-2);

	//��ջͷָ�����βָ��
	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;
	return 1;
}



//����ջ
void destroy_sqstack(sqstack* stack) {
	free(stack->base);
	stack->size = STACK_INIT_SIZE;
}



//����ջ
void clear_sqstack(sqstack* stack)
{
	free(stack->base);
	init_sqstack(stack);
}



//ջ�Ƿ�Ϊ��
//����ֵ����ջ���� 1�� �ǿ� 0
int is_empty_sqstack(sqstack stack) {
	return stack.base == stack.top ? 1 : 0;
}



//ջ�ĳ���
//����ֵ��ջ�ĳ���
int lenof_sqstack(sqstack stack) {
	int count = 0;
	while (stack.base + count != stack.top)
		count++;
	return count;
}



//ȡ��ջ��Ԫ�ظ�ֵ�� top ����
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int get_top_sqstack(sqstack stack, elemtype* top) {
	if (stack.base == stack.top)	//��ջû��ջ��Ԫ�أ����� 0
		return 0;
	*top = *stack.top;
	return 1;
}



//ѹջ
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� -2
int push_sqstack(sqstack* stack, elemtype elem) {

	//��ջ������������Ŀռ�
	if (lenof_sqstack(*stack) >= stack->size)
	{
		stack->base = (elemtype*)realloc(stack->base, (STACKINCREMENT + stack->size) * sizeof(sqstack));
		if (stack->base == NULL) exit(-2);

		//��������ͷָ�룬����ջ�ռ�
		stack->top = &(stack->base[stack->size]);
		stack->size += STACKINCREMENT;
	}
	//��ֵ���ƶ�ͷָ��
	*stack->top = elem;
	stack->top++;
	return 1;
}



//��ջ��ջ��Ԫ�ظ�ֵ�� e
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int pop_sqstack(sqstack* stack, elemtype* e) {
	if (stack->base == stack->top)	//��ջ���� 0
		return 0;

	//ͷָ�����һ��Ԫ�أ�ͷָ��������ָ��Ԫ�ؼ�ջ��Ԫ�أ���ֵ�� e
	stack->top--;
	*e = *stack->top;
}
