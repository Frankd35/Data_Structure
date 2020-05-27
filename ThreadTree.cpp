#include<stdio.h>
#include<stdlib.h>


typedef char elemtype;	//定义树的数据元素类型elemtype



elemtype getElem(void) {
	return getchar();
}



enum tag {link, thread};	//标志指针为子节点还是线索

typedef struct ThreadTreeNode {
	elemtype data;	//数据元素
	ThreadTreeNode* left_child;	 //左子节点指针
	ThreadTreeNode* right_child;	//右子节点指针
	tag ltag = link;	//左标志域，默认为正常
	tag rtag = link;	//右标志域，默认为正常
};



typedef ThreadTreeNode* ThreadTree;


//创建二叉树
/*
* 函数说明：
* 先序历遍顺序建立二叉树，按完全二叉完全二叉树顺序序列出输入，
* 非完全二叉树用' '补成完全二叉树输入
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



//建立线索
void inThread(ThreadTree tree, ThreadTree& pre) {
	
	//中序历遍加入线索
	if (tree->left_child != NULL)
		inThread(tree->left_child, pre);
	else {

		//如果没有左子树则左指针域指向前一个被访问结点
		tree->ltag = thread;
		tree->left_child = pre;
	}
	//如果前一个结点没有右子树则前一个结点右指针域指向现在被访问的结点
	if (pre->right_child == NULL) {
		pre->right_child = tree;
		pre->rtag = thread;
	}
	//更新pre为正在被访问的结点并结束访问
	pre = tree;
	
	if (tree->right_child != 0)
		inThread(tree->right_child, pre);
}



//中序历遍建立线索
ThreadTree inOrderThreading(ThreadTree tree) {

	//建立头节点，默认左字节指针域指向树的根节点，右子节点指针域指向自己
	ThreadTree head = (ThreadTree)malloc(sizeof(ThreadTreeNode));
	if (head == NULL)	exit(-2);
	*head = { 0,tree,head,link,thread };
	//若是空树则做指针回指
	if (tree == NULL)
		head->left_child = head;
	else {
		//pre 是一个可修改的值
		ThreadTree pre = tree;
		inThread(tree, pre);
		//建立结束后pre是最后一个结点，最后一个结点的右指针指向head
		pre->right_child = head;
		pre->rtag = thread;
	}

	return head;
}



//二叉线索树利用线索历遍（中序）
void inOrderTraversal_thread(ThreadTree head) {
	ThreadTree pnt = head;	//搜索指针
	do {
		//若pnt处结点有左子节点则不访问，pnt更新为左子节点
		if (pnt->ltag == link) {
			pnt = pnt->left_child;
			continue;
		}
		//左子节点不为空则访问
		putchar(pnt->data);

		//右子节点为空则访问下一个结点
		if (pnt->rtag == thread)
			pnt = pnt->right_child;
		putchar(pnt->data);

		//右子节点不为空则更新pnt至右子节点但不访问
		if (pnt->rtag == link)
			pnt = pnt->right_child;
		
	} while (pnt != head);
}



//中序历遍并输出值
void inOrderTraversal(ThreadTree tree) {

	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	putchar(tree->data);
	if (tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
}



//测试代码
/*
int main(void) {
	//创建一颗二叉树
	ThreadTree tree = createBiTree();
	printf("\n tree builded\n");
	inOrderTraversal(tree);
	putchar('\n');
	ThreadTree head = inOrderThreading(tree);
	inOrderTraversal_thread(head);
	return 0;
}
*/