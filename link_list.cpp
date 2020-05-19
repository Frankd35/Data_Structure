#include<stdio.h>
#include<stdlib.h>


/* link list*/


// ������ṹ����
typedef struct LNode{
	int data;				//����
	struct LNode* next ;	//��һ�����ָ��
}LNode;

typedef LNode* LinkList;	//ͷ���



//��ʼ��������
//����ֵ����ʼ���ɹ� 1 ��ʧ�� -2
int init_linklist(LinkList* ll) {
	*ll = (LinkList)malloc(sizeof(LNode));
	if (*ll == NULL)	exit(-2);
	(**ll).next = NULL;
	return 1;
}



//������
//����ֵ��������
int lenof_linklist(LinkList ll) {
	int index = 0;
	
	//��Ϊ�ձ�
	if (ll == 0x0)
		return index;
	
	//���ǿձ�
	while (ll->next != 0x0)
	{
		index++; 
		ll = ll->next;
	}
	return index;
}



//���ص�i���ڵ��ָ��
//�̲�û��Ҫ��ú���������ʵ�ֹ�������Ҫ����õ������Ĺ���
//����ֵ���涨i = 0����ͷָ�룬i �Ϸ�ʱ���ض�Ӧ����ַ��i ���Ϸ����� NULL
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
		ll_node = ll_node->next;	//������һ���ڵ�
	}
	return NULL;
}



//��������
void destory_linklist(LinkList* ll) {
	if (ll == NULL)		//ͷ�ڵ�Ϊ�����ǿ�����
		return;

	//�����ͷŽ��ռ���ڴ�
	for (int i = lenof_linklist(*ll); i > 0; i--)
		free(get_elem_pnt_linklist(*ll, i));
	free(*ll);
	*ll = NULL;
}



//��������
void clear_ll(LinkList* ll) {
	// ������ֻ��ͷ�ڵ㣬�������ò��������ٲ�����ͬ
	destory_linklist(ll);
}



//�����Ƿ�Ϊ��
//����ֵ������Ϊ�շ��� 1 ������ 0
int is_empty_linklist(LinkList ll) {
	return ll->next == NULL ? 1 : 0;
}



//ȡ�������i��Ԫ�ص�ֵ����ֵ�� result
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
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
		ll_node = ll_node->next;	//������һ���ڵ�
	}
	return 0;
}



//�Ƿ���ں�e�Ĺ�ϵ���� compare() ������Ԫ��
//����ֵ����Ԫ�ش����򷵻� 1 ���򷵻� 0
int locate_elem_linklist(LinkList ll, int e, int(compare)(int, int)) {
	int index = 0;
	LinkList ll_node;
	ll_node = ll->next;
	while (ll_node != NULL)
	{
		index++;
		if (compare(e, ll_node->data))
			return index;
		ll_node = ll_node->next;	//������һ���ڵ�
	}
	return 0;
}



//Ѱ�� cur_e ��ǰ��Ԫ�ز���ֵ�� prior
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int prior_elem_linklist(LinkList ll, int cur_e, int* prior) {
	LinkList ll_node;

	//�ӵ�һ����㿪ʼ�������
	ll_node = ll->next;
	while ((ll_node != NULL) &&(ll_node->next != NULL) )
	{
		if (ll_node->next->data == cur_e)
		{
			*prior = ll_node->data;
			return 1;
		}
		ll_node = ll_node->next;	//������һ���ڵ�
	}
	return 0;
}



//Ѱ�� cur_e �ĺ��Ԫ�ز���ֵ�� next
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int next_elem_linklist(LinkList ll, int current, int* next) {
	LinkList ll_node;

	//�ӵ�һ����㿪ʼ�������
	ll_node = ll->next;
	while ((ll_node != NULL) && (ll_node->next != NULL))
	{
		if (ll_node->data == current)
		{
			*next = ll_node->next->data;
			return 1;
		}
		ll_node = ll_node->next;	//������һ���ڵ�
	}
	return 0;
}



//�ڵ�iλ���� e
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int insert_linklist(LinkList ll, int i, int e)
{
	LinkList node;

	if (!((1 <= i) && (i <= lenof_linklist(ll) + 1)))	//i �Ƿ�Ϸ�
		return 0;
	
	if (init_linklist(&node))							//����ʼ���ɹ�����½�㸳ֵ
		node->data = e;
	else
		return 0;										//����ʼ��ʧ�ܷ��� 0

	node->next = get_elem_pnt_linklist(ll, i);			//�½ڵ�ָ������ԭ���� i ������ַ
	get_elem_pnt_linklist(ll, i - 1)->next = node;		//ԭ���� i-1 �����ָ�������½ڵ��ַ
	return 1;
}



//ɾ���� i ��Ԫ�ز���ֵ���� e
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int delete_linklist(LinkList ll, int i, int* e) {
	if ((1 <= i) && (i <= lenof_linklist(ll)))			// i �Ƿ�Ϸ�
	{
		LinkList tab;									// �ñ�����ʱ����ָ��
	
		get_elem_linklist(ll, i, e);					//�� i ��Ԫ�ز���ֵ���� e
		tab = get_elem_pnt_linklist(ll, i + 1);			//����� i+1 ��Ԫ�ص�ַ
		free(get_elem_pnt_linklist(ll, i));				//�ͷŵ� i ��Ԫ�ؽ��ռ�
		get_elem_pnt_linklist(ll, i - 1)->next = tab;	//ԭ���� i-1 �����ָ�����ŵ� i+1 ��Ԫ�ص�ַ

		return 1;
	}
	return 0;
}



//��������Ԫ��
void traverse_linlist(LinkList ll, void(visit)(int)) {
	int i,a = 0;
	for (i = 0; i < lenof_linklist(ll); i++)
		get_elem_linklist(ll, i, &a);
		visit(a);
}



//Ϊ������ֵ������
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
�ṩ�������������ϲ����µĽ����б�����
���Ӷȷ�����lenof(l1)+lenof(l2)
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



//���Դ��룺����һ�����ݴ����1���Զ����ɱ�2������
/*
int main() {
	LinkList l1, l2;
	create_ll(&l1);		//����1
	init_linklist(&l2);		//����2
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