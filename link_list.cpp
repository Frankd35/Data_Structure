#include<stdio.h>
#include<stdlib.h>


/* link list*/


// 链表结点结构定义
typedef struct LNode{
	int data;				//数据
	struct LNode* next ;	//下一个结点指针
}LNode;

typedef LNode* LinkList;	//头结点



//初始化链表结点
//返回值：初始化成功 1 ，失败 -2
int init_linklist(LinkList* ll) {
	*ll = (LinkList)malloc(sizeof(LNode));
	if (*ll == NULL)	exit(-2);
	(**ll).next = NULL;
	return 1;
}



//链表长度
//返回值：链表长度
int lenof_linklist(LinkList ll) {
	int index = 0;
	
	//若为空表
	if (ll == 0x0)
		return index;
	
	//不是空表
	while (ll->next != 0x0)
	{
		index++; 
		ll = ll->next;
	}
	return index;
}



//返回第i个节点的指针
//教材没有要求该函数，但是实现过程中需要多次用到这样的功能
//返回值：规定i = 0返回头指针，i 合法时返回对应结点地址，i 不合法返回 NULL
 LinkList get_elem_pnt_linklist(LinkList ll, int i) {
	int index = 0;
	LinkList ll_node;
	ll_node = ll->next;
	if (i == 0)
		return ll;
	while (ll_node != NULL)
	{
		index++;
		if (i == index)
			return ll_node;
		ll_node = ll_node->next;	//查找下一个节点
	}
	return NULL;
}



//销毁链表
void destory_linklist(LinkList* ll) {
	if (ll == NULL)		//头节点为空则是空链表
		return;

	//依次释放结点占用内存
	for (int i = lenof_linklist(*ll); i > 0; i--)
		free(get_elem_pnt_linklist(*ll, i));
	free(*ll);
	*ll = NULL;
}



//重置链表
void clear_ll(LinkList* ll) {
	// 空链表只有头节点，所以重置操作与销毁操作相同
	destory_linklist(ll);
}



//链表是否为空
//返回值：链表为空返回 1 ，否则 0
int is_empty_linklist(LinkList ll) {
	return ll->next == NULL ? 1 : 0;
}



//取得链表第i个元素的值并赋值给 result
//返回值：操作成功返回 1 ，失败返回 0
int get_elem_linklist(LinkList ll, int i,int* elem)
{
	int index = 0;
	LinkList ll_node;
	ll_node = ll->next;
	while (ll_node != NULL)
	{
		index++;
		if (i == index)
		{
			*elem = ll_node->data;
			return 1;
		}
		ll_node = ll_node->next;	//查找下一个节点
	}
	return 0;
}



//是否存在和e的关系满足 compare() 函数的元素
//返回值：若元素存在则返回 1 否则返回 0
int locate_elem_linklist(LinkList ll, int e, int(compare)(int, int)) {
	int index = 0;
	LinkList ll_node;
	ll_node = ll->next;
	while (ll_node != NULL)
	{
		index++;
		if (compare(e, ll_node->data))
			return index;
		ll_node = ll_node->next;	//查找下一个节点
	}
	return 0;
}



//寻找 cur_e 的前驱元素并赋值给 prior
//返回值：操作成功返回 1 ，失败返回 0
int prior_elem_linklist(LinkList ll, int cur_e, int* prior) {
	LinkList ll_node;

	//从第一个结点开始往后查找
	ll_node = ll->next;
	while ((ll_node != NULL) &&(ll_node->next != NULL) )
	{
		if (ll_node->next->data == cur_e)
		{
			*prior = ll_node->data;
			return 1;
		}
		ll_node = ll_node->next;	//查找下一个节点
	}
	return 0;
}



//寻找 cur_e 的后继元素并赋值给 next
//返回值：操作成功返回 1 ，失败返回 0
int next_elem_linklist(LinkList ll, int current, int* next) {
	LinkList ll_node;

	//从第一个结点开始往后查找
	ll_node = ll->next;
	while ((ll_node != NULL) && (ll_node->next != NULL))
	{
		if (ll_node->data == current)
		{
			*next = ll_node->next->data;
			return 1;
		}
		ll_node = ll_node->next;	//查找下一个节点
	}
	return 0;
}



//在第i位插入 e
//返回值：操作成功返回 1 ，失败返回 0
int insert_linklist(LinkList ll, int i, int e)
{
	LinkList node;

	if (!((1 <= i) && (i <= lenof_linklist(ll) + 1)))	//i 是否合法
		return 0;
	
	if (init_linklist(&node))							//若初始化成功则对新结点赋值
		node->data = e;
	else
		return 0;										//若初始化失败返回 0

	node->next = get_elem_pnt_linklist(ll, i);			//新节点指针域存放原来第 i 个结点地址
	get_elem_pnt_linklist(ll, i - 1)->next = node;		//原来第 i-1 个结点指针域存放新节点地址
	return 1;
}



//删除第 i 个元素并把值赋给 e
//返回值：操作成功返回 1 ，失败返回 0
int delete_linklist(LinkList ll, int i, int* e) {
	if ((1 <= i) && (i <= lenof_linklist(ll)))			// i 是否合法
	{
		LinkList tab;									// 该变量暂时储存指针
	
		get_elem_linklist(ll, i, e);					//第 i 个元素并把值赋给 e
		tab = get_elem_pnt_linklist(ll, i + 1);			//储存第 i+1 个元素地址
		free(get_elem_pnt_linklist(ll, i));				//释放第 i 个元素结点空间
		get_elem_pnt_linklist(ll, i - 1)->next = tab;	//原来第 i-1 个结点指针域存放第 i+1 个元素地址

		return 1;
	}
	return 0;
}



//历遍所有元素
void traverse_linlist(LinkList ll, void(visit)(int)) {
	int i,a = 0;
	for (i = 0; i < lenof_linklist(ll); i++)
		get_elem_linklist(ll, i, &a);
		visit(a);
}



//为空链表赋值，正序
int create_ll(LinkList* ll)
{
	int data;
	init_linklist(ll);
	printf("please enter integer\n");
	while (scanf_s("%d", &data) == 1)
	{
		if (!(insert_linklist(*ll, lenof_linklist(*ll) + 1, data)))	return 0;
		printf("please enter integer\n");
		printf("enter q to quit\n");
	}
	printf("link list:");
	LinkList pnt = *ll;	
	while (pnt->next != NULL)
	{
		printf("%d ", pnt->next->data);
		pnt = pnt->next;
	}
	return 1;
}



/*
提供两个升序链表，合并成新的降序列表并返回
复杂度分析：lenof(l1)+lenof(l2)
*/
LinkList merge_ll(LinkList a, LinkList b)
{
	LinkList new_ll;
	init_linklist(&new_ll);
	a = a->next;
	b = b->next;
	while (a != NULL && b != NULL)
	{
		if (a->data <= b->data)
		{
			insert_linklist(new_ll, 1, a->data);
			a = a->next;
		}
		else
		{
			insert_linklist(new_ll, 1, b->data);
			b = b->next;
		}
	}
	while (a != NULL)
	{
		insert_linklist(new_ll, 1, a->data);
		a = a->next;
	}
	while (b != NULL)
	{
		insert_linklist(new_ll, 1, b->data);
		b = b->next;
	}
	return new_ll;
}



//测试代码：输入一组数据存入表1，自动生成表2，排序
/*
int main() {
	LinkList l1, l2;
	create_ll(&l1);		//链表1
	init_linklist(&l2);		//链表2
	for (int i = 1; i < 12; i++)
		insert_linklist(l2, i, i);
	LinkList pnt = l2;
	printf("\nl2:");
	while (pnt->next != NULL)
	{
		printf("%d ", pnt->next->data);
		pnt = pnt->next;
	}
	pnt = merge_ll(l1, l2);
	printf("\nnew link list:");
	while (pnt->next != NULL)
	{
		printf("%d ", pnt->next->data);
		pnt = pnt->next;
	}
	return 0;
}
*/