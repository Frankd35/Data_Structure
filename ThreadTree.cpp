#include<stdio.h>
#include<stdlib.h>


typedef char elemtype;	//������������Ԫ������elemtype



elemtype getElem(void) {
	return getchar();
}



enum tag {link, thread};	//��־ָ��Ϊ�ӽڵ㻹������

typedef struct ThreadTreeNode {
	elemtype data;	//����Ԫ��
	ThreadTreeNode* left_child;	 //���ӽڵ�ָ��
	ThreadTreeNode* right_child;	//���ӽڵ�ָ��
	tag ltag = link;	//���־��Ĭ��Ϊ����
	tag rtag = link;	//�ұ�־��Ĭ��Ϊ����
};



typedef ThreadTreeNode* ThreadTree;


//����������
/*
* ����˵����
* ��������˳����������������ȫ������ȫ������˳�����г����룬
* ����ȫ��������' '������ȫ����������
*/
ThreadTree createBiTree(void) {	
	elemtype elem;
	ThreadTree tree;
	elem = getElem();
	if (elem == ' ')
		return NULL;
	tree = (ThreadTree)malloc(sizeof(ThreadTreeNode));
	if (tree == NULL)
		exit(-2);
	tree->data = elem;
	tree->ltag = link;
	tree->rtag = link;
	tree->left_child = createBiTree();
	tree->right_child = createBiTree();
	return tree;
}



//��������
void inThread(ThreadTree tree, ThreadTree& pre) {
	
	//���������������
	if (tree->left_child != NULL)
		inThread(tree->left_child, pre);
	else {

		//���û������������ָ����ָ��ǰһ�������ʽ��
		tree->ltag = thread;
		tree->left_child = pre;
	}
	//���ǰһ�����û����������ǰһ�������ָ����ָ�����ڱ����ʵĽ��
	if (pre->right_child == NULL) {
		pre->right_child = tree;
		pre->rtag = thread;
	}
	//����preΪ���ڱ����ʵĽ�㲢��������
	pre = tree;
	
	if (tree->right_child != 0)
		inThread(tree->right_child, pre);
}



//�������齨������
ThreadTree inOrderThreading(ThreadTree tree) {

	//����ͷ�ڵ㣬Ĭ�����ֽ�ָ����ָ�����ĸ��ڵ㣬���ӽڵ�ָ����ָ���Լ�
	ThreadTree head = (ThreadTree)malloc(sizeof(ThreadTreeNode));
	if (head == NULL)	exit(-2);
	*head = { 0,tree,head,link,thread };
	//���ǿ�������ָ���ָ
	if (tree == NULL)
		head->left_child = head;
	else {
		//pre ��һ�����޸ĵ�ֵ
		ThreadTree pre = tree;
		inThread(tree, pre);
		//����������pre�����һ����㣬���һ��������ָ��ָ��head
		pre->right_child = head;
		pre->rtag = thread;
	}

	return head;
}



//���������������������飨����
void inOrderTraversal_thread(ThreadTree head) {
	ThreadTree pnt = head;	//����ָ��
	do {
		//��pnt����������ӽڵ��򲻷��ʣ�pnt����Ϊ���ӽڵ�
		if (pnt->ltag == link) {
			pnt = pnt->left_child;
			continue;
		}
		//���ӽڵ㲻Ϊ�������
		putchar(pnt->data);

		//���ӽڵ�Ϊ���������һ�����
		if (pnt->rtag == thread)
			pnt = pnt->right_child;
		putchar(pnt->data);

		//���ӽڵ㲻Ϊ�������pnt�����ӽڵ㵫������
		if (pnt->rtag == link)
			pnt = pnt->right_child;
		
	} while (pnt != head);
}



//�������鲢���ֵ
void inOrderTraversal(ThreadTree tree) {

	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	putchar(tree->data);
	if (tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
}



//���Դ���
/*
int main(void) {
	//����һ�Ŷ�����
	ThreadTree tree = createBiTree();
	printf("\n tree builded\n");
	inOrderTraversal(tree);
	putchar('\n');
	ThreadTree head = inOrderThreading(tree);
	inOrderTraversal_thread(head);
	return 0;
}
*/