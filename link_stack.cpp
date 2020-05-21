#include<stdlib.h>
#include<stdio.h>



// link stack



typedef int elemtype;	//定义数据元素类型elemtype



//链栈结点
typedef struct SNode {	
	elemtype data;	//数据元素
	struct SNode* next;	//下一个结点的指针
}SNode;



typedef SNode* lstack;	//结点指针



//栈结构定义
//链栈栈顶在链表头，栈顶不储存数据
typedef struct LinkStack {
	lstack top;	//栈顶指针
	lstack base;	//栈底指针
	int size = 0;	//栈的大小
} linkstack;



//初始化栈
//返回值：初始化成功 1，失败 -2
int init_lstack(lstack* ls, LinkStack linkstack) {
	*ls = (lstack)malloc(sizeof SNode);
	if (*ls == NULL)	exit(-2);
	(**ls).next = NULL;

	//空栈头指针等于尾指针
	linkstack.top = *ls;
	linkstack.base = *ls;
	return 1;
}



//销毁栈
void destroy_lstack(LinkStack* ls) {
	
	//延头节点释放所有节点储存空间
	lstack pnt;
	while (ls->top != ls->base)
	{
		pnt = ls->top;
		ls->top = ls->top->next;
		free(pnt);
	}
	free(ls->top);
}



//重置栈
void clear_lstack(LinkStack* ls)
{
	destroy_lstack(ls);
	init_lstack(&ls->base, *ls);
}



//取得栈顶元素赋值给 e 返回
//返回值：操作成功返回 1 ，失败返回 0
int get_top_lstack(LinkStack ls, elemtype* e) {
	if (ls.base == ls.top) return 0;
	*e = ls.top->next->data;
	return 1;
}



//栈的长度
//返回值：栈的长度
int lenof_lstack(LinkStack ls) {

	int length = 0;	//栈的长度
	lstack node = ls.top;	//检测探针

	//当探针未达到栈底时，探针前进一步，长度加 1
	while (node != ls.base)
	{
		length++;
		node = node->next;
	}
	return length;
}



//栈是否为空
//返回值：空栈返回 1， 非空 0
int isempty_lstack(LinkStack ls) {
	return ls.base == ls.top ? 1 : 0;
}



//压栈
//返回值：操作成功返回 1 ，失败返回 -2
int push_lstack(LinkStack* ls, elemtype e) {

	//为新节点申请空间，失败返回 -2
	lstack new_node;
	new_node =(lstack)malloc(sizeof SNode);
	if (new_node == NULL)	exit(-2);

	//将新节点插入到链表头的头节点后面
	new_node->next = ls->top->next;
	new_node->data = e;
	ls->top->next = new_node;

	//若压栈之前是空栈，更新base指针
	if (ls->base == ls->top)
		ls->base = new_node;

	ls->size++;
	return 1;
}



//弹栈，栈顶元素赋值给 e
//返回值：操作成功返回 1 ，失败返回 0
void pop_lstack(LinkStack* ls, elemtype* e) {

	//若弹栈之前是空栈，返回 0
	if (ls->base == ls->top)
		return 0;

	lstack pnt;	//储存将被释放的结点
	pnt = ls->top;

	//头指针后移一个元素，头指针现在所指的元素即栈顶元素，赋值给 e
	ls->top = ls->top->next;
	*e = ls->top->next->data;

	//释放多余结点原头节点）
	free(pnt);

	ls->size--;
	return 1;
}