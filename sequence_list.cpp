#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10


/* sequence list */


// ˳���ṹ����
typedef struct {
	int* elem;		//����Ԫ������
	int length;		//˳�����
	int list_size;	//˳�������Ԫ����ռ�ռ�
}SqList;



//��ʼ��˳���
int init_sql(SqList* sql) {
	//Ϊ˳���������Ԫ�����붯̬����ռ�
	sql->elem = (int*)malloc(LIST_INIT_SIZE * (sizeof(int)));	
	if (sql->elem == NULL)
		exit(-2);

	//��ʼ��˳����ȡ�����Ԫ��ռ�ÿռ�
	sql->length = 0;
	sql->list_size = LIST_INIT_SIZE;
	return 1;
}



//����˳���
void destroy_sql(SqList * sql) {
	if (sql->elem == NULL)
		return;
	free((*sql).elem);
	printf("sequence list destroyed\n");
}



//����˳���
void clear_sql(SqList* sql) {
	if (sql->elem != NULL)
		free((*sql).elem);
	init_sql(sql);
	sql->length = 0;	
	sql->list_size = LIST_INIT_SIZE;
	printf("sequence list cleared\n");
}



//˳����Ƿ�Ϊ��
//����ֵ��˳���Ϊ���򷵻� 1 ���򷵻� 0
int is_empty_sql(SqList sql) {
	return sql.length ? 1 :0;
}



//˳�����
//����ֵ��˳�����
int lenof_sql(SqList sql) {
	return sql.length;
}



//ȡ��˳����i��Ԫ�ص�ֵ����ֵ�� result
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int get_elem_sql(SqList sql, int i,int* result) {
	if ((1 <= i) && (i <= sql.length)) {  //i ֵ�Ƿ�Ϸ�
		*result = sql.elem[i - 1];
		return 1;
	}
	return 0;
}



//�Ƿ���ں�e�Ĺ�ϵ���� compare() ������Ԫ��
//����ֵ����Ԫ�ش����򷵻� 1 ���򷵻� 0
int locate_elem_sql(SqList sql, int e, int(compare)(int, int)) {
	int i;
	for (i = 0; i < sql.length; i++){
		//
		if (compare(e, sql.elem[i]))
			return i;
	}
	return 0;
}



//Ѱ�� cur_e ��ǰ��Ԫ�ز���ֵ�� prior
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int prior_elem_sql(SqList sql, int cur_e,int* prior) {

	//��� cur_e ���ǵ�һ��Ԫ��
	if (!(cur_e == sql.elem[0])) {

		// �ҵ� cur_e ����ǰ����ֵ�� prior
		for (int i = 0; i < sql.length; i++) {
			if (cur_e == sql.elem[i]) {
				*prior = sql.elem[i - 1];
				return 1;
			}
		}	//��˳����в����� cur_e ���� 0
		return 0;
	}	//�� cur_e �ǵ�һ��Ԫ��
	return 0;
}



//Ѱ�� cur_e �ĺ��Ԫ�ز���ֵ�� next
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int next_elem_sql(SqList sql, int cur_e, int* next) {

	// �ҵ� cur_e ���Ѻ�̸�ֵ�� next
	for (int i = 0; i < sql.length - 1; i++)
	{
		if (cur_e == sql.elem[i])
		{
			*next = sql.elem[i + 1];
			return 1;
		}
	}
	return 0;
}



//�ڵ�iλ���� e
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int insert_sql(SqList* sql, int i, int e) {
	int index;
	int* newbase;
	if (!((1 <= i) && (i <= (sql->length + 1))))	//i�Ƿ�Ϸ�
	{
		printf("insert failed");
		return 0;
	}

	sql->length++;	//������
	
	if (sql->length  >= sql->list_size)	//���ռ䲻�������µ�ַ
	{
		newbase = (int*)realloc(sql->elem,(sql->list_size + LISTINCREMENT) * (sizeof(int)));
		if (!(newbase)) return 0;
		sql->elem = newbase;
		sql->list_size += LISTINCREMENT;
	}

	//�ƶ�Ԫ�ز����� e
	for (index = sql->length; index > i - 1; index--)
		sql->elem[index] = (int)sql->elem[index - 1];
	sql->elem[i - 1] = e;

	return 1;
}



//ɾ���� i ��Ԫ�ز���ֵ���� elem_i
//����ֵ�������ɹ����� 1 ��ʧ�ܷ��� 0
int delete_sql(SqList* sql, int i, int* elem_i) {
	int index;
	if (!((1 <= i) && (i <= sql->length)))	//i�Ƿ�Ϸ�
		return 0;

	*elem_i = sql->elem[i - 1];	// ��ɾȥԪ�ظ�ֵ�� elem_i
	
	//�ƶ�Ԫ��
	for (index = i - 1; index + 1 < sql->length; index++)
		sql->elem[index] = sql->elem[index + 1];
	sql->length--;

	return 1;
}



//��������Ԫ��
void traverse_sql(SqList sql, void(Visit)(int)) {
	int i;
	for (i = 0; i < sql.length; i++)
	{
		Visit(sql.elem[i]);
	}
	printf("traversed\n");
}



//Ϊ��˳���ֵ������
int create_sql(SqList* sql)	 
{
	int e;

	if (sql->length != 0)  return 0;
	printf("please enter integer\n");
	scanf_s("%d", &sql->elem[0]);
	sql->length++;
	printf("please enter integer\n");
	printf("enter q to quit\n");
	while (scanf_s("%d", &e) == 1)
	{
		insert_sql(sql, sql->length + 1, e);
		printf("please enter integer\n");
		printf("enter q to quit\n");
	}
	printf("sequence list : ");
	for (int i = 0; i < sql->length; i++)
		printf("%d ", sql->elem[i]);
	putchar('\n');
	return 1;
}



/*
�ṩ�������������ϲ����µĽ����б�����
���Ӷȷ�����o( lenof(l1)+lenof(l2) )
*/
SqList merge_sql(SqList l1, SqList l2) {
	// ����˳���
	SqList new_sql;
	init_sql(&new_sql);

	int i = l1.length - 1;	//l1 ������Ԫ�ص�λ��
	int	j = l2.length - 1;	//l2 ������Ԫ�ص�λ��

	//���������
	while (i >= 0 && j >= 0)
	{

		if (l1.elem[i] >= l2.elem[j])
		{
			insert_sql(&new_sql, new_sql.length + 1, l1.elem[i]);
			i--;
		}
		else
		{
			insert_sql(&new_sql, new_sql.length + 1, l2.elem[j]);
			j--;
		}
	}
	while (i >= 0)
	{
		insert_sql(&new_sql, new_sql.length + 1, l1.elem[i]);
		i--;
	}
	while (j >= 0)
	{
		insert_sql(&new_sql, new_sql.length + 1, l2.elem[j]);
		j--;
	}
	return new_sql;
}



//���Դ��룺����һ�����ݴ����1���Զ����ɱ�2������
/*
int main()
{
	SqList sql1, sql2;
	init_sql(&sql1);
	init_sql(&sql2);
	create_sql(&sql1);	//˳���1
	for (int e = 0; e < 20; e++)	//˳���2
		insert_sql(&sql2, sql2.length + 1, 2 * e - 3);
	printf("sequence list2 : ");
	for (int i = 0; i < sql2.length; i++)
		printf("%d ", sql2.elem[i]);
	SqList new_sql = merge_sql(sql1, sql2);
	printf("\n new sequence list : ");
	for (int i = 0; i < new_sql.length; i++)
		printf("%d ", new_sql.elem[i]);
}
*/
