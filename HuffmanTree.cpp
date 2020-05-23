#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR 30


typedef char elemtype;	//定义树的数据元素类型elemtype



typedef struct HFTreeNode {	//Huffman树结点
	HFTreeNode* parent;	//父节点指针
	elemtype key;	//结点对应字符
	int value;	//权值
	HFTreeNode* left_child;	//左子节点指针
	HFTreeNode* right_child;	//右子节点指针
	char code[MAX_CHAR];	//Huffman编码
};



typedef HFTreeNode* HFTree;	//定义Huffman树是结点的指针



//中序历遍并输出值
void ::inOrderTraversal(HFTree tree) {

	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	putchar(tree->key);
	if (tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
}



//先序历遍并输出值
void preOrderTraversal(HFTree tree) {
	putchar(tree->key);
	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	if (tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
}



//后序序历遍并输出值
void pastOrderTraversal(HFTree tree) {
	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	if(tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
	putchar(tree->key);
}



//中序历遍并输出Huffman编码
void inOrderTraversal(HFTree tree) {	
	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	if (tree->key != ' ') {
		putchar(tree->key);
		printf("\thuffman code %s\n", tree->code);
	}
	if (tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
}



//输入一串字符，统计字符出现次数作为权值，以字符和权值构造结点
//返回一个Huffman树组成的森林
HFTree* getCharWeighted(void) {	//设字符种类不超过MAX_CHAR
	typedef struct key_value {
		elemtype key;
		int value;
	};	//字符和其出现次数是一个键值对
	key_value array[MAX_CHAR];
	int count = 0;	//字符种类个数
	elemtype elem;
	printf("please enter a string, end with \';\'");

	//对字符加权赋值
	while ((elem = getchar()) != ';') {	
		bool isExist = false;	//该字符是否已经存在

		//历遍键值对数组，若存在则该字符值+1并退出历遍
		for (int i = 0; i < count; i++) {
			if (array[i].key == elem)
			{
				isExist = true;
				array[i].value++;
				break;
			}
		}

		//若历遍完成该字符不存在键值对数组中，写入数组
		if (!isExist) {
			array[count] = { elem, 1 };
			count++;
		}
	}
	//Huffman树数组是一个森林
	static HFTree forest[MAX_CHAR] = { NULL };
	for (int i = 0; i < count; i++) {
		HFTree tree = (HFTree)malloc(sizeof(HFTreeNode));
		if (tree == NULL)
			exit(-2);

		//
		*tree = { NULL,array[i].key,array[i].value,NULL,NULL,{0} };
		forest[i] = tree;
	}
	return forest;
}




void swap(HFTree* a, HFTree* b) {
	HFTree pointer = *a;
	*a = *b;
	*b = pointer;
}



//将森林由大到小排序，Huffman树数组forest的最后是NULL
HFTree* sort(HFTree* forest) {	
	int index = 0;
	while (forest[index] != NULL || index < MAX_CHAR)
		index++;
	for (int i = 0; i < index; i++) {
		for (int j = 0; j + 1 < index; j++) {
			if (forest[j]->value < forest[j + 1]->value)
				swap(&forest[j], &forest[j + 1]);
		}
	}
	return forest;
}



//递归地建立Huffman树
HFTree buildHuffmanTree(HFTree* forest) {
	if (forest[1] == NULL)
		return forest[0];
	HFTree root;
	root = (HFTree)malloc(sizeof(HFTreeNode));
	if (root == NULL)
		exit(-2);
	forest = sort(forest);
	int index = 0;
	while (forest[index] != NULL)
		index++;
	*root = {
		NULL,
		' ',
		forest[index - 1]->value + forest[index - 2]->value,
		forest[index - 1],
		forest[index - 2],
	{0}
	};
	forest[index - 1]->parent = root;
	forest[index - 2]->parent = root;
	forest[index - 1] = NULL;
	forest[index - 2] = root;
	return buildHuffmanTree(forest);
}



//对一颗Huffman树上所有节点求Huffman编码
/*函数说明：参数是一颗Huffman树，从根节点开始对每一个结点递归地中序历遍
* 每经过一个结点就对其左右子树（如果存在）对应位置的Huffman编码赋值（根
* 据其深度），每访问一个结点依次拷贝父节点的Huffman编码到该节点 Huffman
* 编码上，递归结束后所有结点的Huffman编码完成赋值
* 根节点没有Huffman编码
*/
void createHuffmanCode(HFTree tree) {	// 参数是一颗Huffman树
	int degree = 0;		// 该节点在Huffman树中的深度
	HFTree a = tree;
	while (a->parent != NULL) {	//求该节点的深度
		degree++;
		a = a->parent;
	}
	// 对当前结点的左右孩子Huffman编码赋值
	if (tree->left_child != NULL)
		tree->left_child->code[degree] = '0';
	if (tree->right_child != NULL)
		tree->right_child->code[degree] = '1';

	//递归
	if (tree->left_child != NULL)
		createHuffmanCode(tree->left_child);
	//依次拷贝父节点的Huffman编码
	a = tree;
	while (degree > 1) {
		degree--;
		a = a->parent;
		tree->code[degree - 1] = a->code[degree - 1];
	}
	
	//递归
	if (tree->right_child != NULL)
		createHuffmanCode(tree->right_child);
}
//
int main(void) {
	HFTree* forest = getCharWeighted();
	HFTree huffman_tree = buildHuffmanTree(forest);
	inOrderTraversal(huffman_tree);
	createHuffmanCode(huffman_tree);
	inOrderTraversal(huffman_tree);
}