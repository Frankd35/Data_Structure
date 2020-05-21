#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10



/* sequence stack */



typedef int elemtype;	//定义数据元素类型elemtype



typedef struct SeqStack {	//定义顺序栈结构体
	elemtype* top;	//头指针
	elemtype* base;	//尾指针
	int size;	//栈的大小
} sqstack;



//初始化栈
//返回值：初始化成功 1，失败 -2
int init_sqstack(sqstack* stack) {
	stack->base = (elemtype*)malloc(STACK_INIT_SIZE * sizeof(sqstack));
	if (stack->base == NULL) exit(-2);

	//空栈头指针等于尾指针
	stack->top = stack->base;
	stack->size = STACK_INIT_SIZE;
	return 1;
}



//销毁栈
void destroy_sqstack(sqstack* stack) {
	free(stack->base);
	stack->size = STACK_INIT_SIZE;
}



//重置栈
void clear_sqstack(sqstack* stack)
{
	free(stack->base);
	init_sqstack(stack);
}



//栈是否为空
//返回值：空栈返回 1， 非空 0
int is_empty_sqstack(sqstack stack) {
	return stack.base == stack.top ? 1 : 0;
}



//栈的长度
//返回值：栈的长度
int lenof_sqstack(sqstack stack) {
	int count = 0;
	while (stack.base + count != stack.top)
		count++;
	return count;
}



//取得栈顶元素赋值给 top 返回
//返回值：操作成功返回 1 ，失败返回 0
int get_top_sqstack(sqstack stack, elemtype* top) {
	if (stack.base == stack.top)	//空栈没有栈顶元素，返回 0
		return 0;
	*top = *stack.top;
	return 1;
}



//压栈
//返回值：操作成功返回 1 ，失败返回 -2
int push_sqstack(sqstack* stack, elemtype elem) {

	//若栈满则需分配更大的空间
	if (lenof_sqstack(*stack) >= stack->size)
	{
		stack->base = (elemtype*)realloc(stack->base, (STACKINCREMENT + stack->size) * sizeof(sqstack));
		if (stack->base == NULL) exit(-2);

		//重新设置头指针，增加栈空间
		stack->top = &(stack->base[stack->size]);
		stack->size += STACKINCREMENT;
	}
	//赋值并移动头指针
	*stack->top = elem;
	stack->top++;
	return 1;
}



//弹栈，栈顶元素赋值给 e
//返回值：操作成功返回 1 ，失败返回 0
int pop_sqstack(sqstack* stack, elemtype* e) {
	if (stack->base == stack->top)	//空栈返回 0
		return 0;

	//头指针后移一个元素，头指针现在所指的元素即栈顶元素，赋值给 e
	stack->top--;
	*e = *stack->top;
}
