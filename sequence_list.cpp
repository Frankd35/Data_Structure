#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10


/* sequence list */


// 顺序表结构定义
typedef struct {
	int* elem;		//数据元素数组
	int length;		//顺序表长度
	int list_size;	//顺序表数据元素所占空间
}SqList;



//初始化顺序表
int init_sql(SqList* sql) {
	//为顺序表中数据元素申请动态储存空间
	sql->elem = (int*)malloc(LIST_INIT_SIZE * (sizeof(int)));	
	if (sql->elem == NULL)
		exit(-2);

	//初始化顺序表长度、数据元素占用空间
	sql->length = 0;
	sql->list_size = LIST_INIT_SIZE;
	return 1;
}



//销毁顺序表
void destroy_sql(SqList * sql) {
	if (sql->elem == NULL)
		return;
	free((*sql).elem);
	printf("sequence list destroyed\n");
}



//重置顺序表
void clear_sql(SqList* sql) {
	if (sql->elem != NULL)
		free((*sql).elem);
	init_sql(sql);
	sql->length = 0;	
	sql->list_size = LIST_INIT_SIZE;
	printf("sequence list cleared\n");
}



//顺序表是否为空
//返回值：顺序表为空则返回 1 否则返回 0
int is_empty_sql(SqList sql) {
	return sql.length ? 1 :0;
}



//顺序表长度
//返回值：顺序表长度
int lenof_sql(SqList sql) {
	return sql.length;
}



//取得顺序表第i个元素的值并赋值给 result
//返回值：操作成功返回 1 ，失败返回 0
int get_elem_sql(SqList sql, int i,int* result) {
	if ((1 <= i) && (i <= sql.length)) {  //i 值是否合法
		*result = sql.elem[i - 1];
		return 1;
	}
	return 0;
}



//是否存在和e的关系满足 compare() 函数的元素
//返回值：若元素存在则返回 1 否则返回 0
int locate_elem_sql(SqList sql, int e, int(compare)(int, int)) {
	int i;
	for (i = 0; i < sql.length; i++){
		//
		if (compare(e, sql.elem[i]))
			return i;
	}
	return 0;
}



//寻找 cur_e 的前驱元素并赋值给 prior
//返回值：操作成功返回 1 ，失败返回 0
int prior_elem_sql(SqList sql, int cur_e,int* prior) {

	//如果 cur_e 不是第一个元素
	if (!(cur_e == sql.elem[0])) {

		// 找到 cur_e 并把前驱赋值给 prior
		for (int i = 0; i < sql.length; i++) {
			if (cur_e == sql.elem[i]) {
				*prior = sql.elem[i - 1];
				return 1;
			}
		}	//若顺序表中不存在 cur_e 返回 0
		return 0;
	}	//若 cur_e 是第一个元素
	return 0;
}



//寻找 cur_e 的后继元素并赋值给 next
//返回值：操作成功返回 1 ，失败返回 0
int next_elem_sql(SqList sql, int cur_e, int* next) {

	// 找到 cur_e 并把后继赋值给 next
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



//在第i位插入 e
//返回值：操作成功返回 1 ，失败返回 0
int insert_sql(SqList* sql, int i, int e) {
	int index;
	int* newbase;
	if (!((1 <= i) && (i <= (sql->length + 1))))	//i是否合法
	{
		printf("insert failed");
		return 0;
	}

	sql->length++;	//表长增加
	
	if (sql->length  >= sql->list_size)	//若空间不够分配新地址
	{
		newbase = (int*)realloc(sql->elem,(sql->list_size + LISTINCREMENT) * (sizeof(int)));
		if (!(newbase)) return 0;
		sql->elem = newbase;
		sql->list_size += LISTINCREMENT;
	}

	//移动元素并插入 e
	for (index = sql->length; index > i - 1; index--)
		sql->elem[index] = (int)sql->elem[index - 1];
	sql->elem[i - 1] = e;

	return 1;
}



//删除第 i 个元素并把值赋给 elem_i
//返回值：操作成功返回 1 ，失败返回 0
int delete_sql(SqList* sql, int i, int* elem_i) {
	int index;
	if (!((1 <= i) && (i <= sql->length)))	//i是否合法
		return 0;

	*elem_i = sql->elem[i - 1];	// 被删去元素赋值给 elem_i
	
	//移动元素
	for (index = i - 1; index + 1 < sql->length; index++)
		sql->elem[index] = sql->elem[index + 1];
	sql->length--;

	return 1;
}



//历遍所有元素
void traverse_sql(SqList sql, void(Visit)(int)) {
	int i;
	for (i = 0; i < sql.length; i++)
	{
		Visit(sql.elem[i]);
	}
	printf("traversed\n");
}



//为空顺序表赋值，正序
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
提供两个升序链表，合并成新的降序列表并返回
复杂度分析：o( lenof(l1)+lenof(l2) )
*/
SqList merge_sql(SqList l1, SqList l2) {
	// 建立顺序表
	SqList new_sql;
	init_sql(&new_sql);

	int i = l1.length - 1;	//l1 中最大的元素的位置
	int	j = l2.length - 1;	//l2 中最大的元素的位置

	//按降序插入
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



//测试代码：输入一组数据存入表1，自动生成表2，排序
/*
int main()
{
	SqList sql1, sql2;
	init_sql(&sql1);
	init_sql(&sql2);
	create_sql(&sql1);	//顺序表1
	for (int e = 0; e < 20; e++)	//顺序表2
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
