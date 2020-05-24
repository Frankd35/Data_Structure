#include<stdio.h>
#include<stdlib.h>

#define MAX_CHAR 30


typedef char elemtype;	//������������Ԫ������elemtype



typedef struct HFTreeNode {	//Huffman�����
	HFTreeNode* parent;	//���ڵ�ָ��
	elemtype key;	//����Ӧ�ַ�
	int value;	//Ȩֵ
	HFTreeNode* left_child;	//���ӽڵ�ָ��
	HFTreeNode* right_child;	//���ӽڵ�ָ��
	char* code;	//Huffman����
};



typedef HFTreeNode* HFTree;	//����Huffman���ǽ���ָ��



/* 
//�������鲢���ֵ
void inOrderTraversal(HFTree tree) {

	if (tree->left_child != NULL)
		inOrderTraversal(tree->left_child);
	putchar(tree->key);
	if (tree->right_child != NULL)
		inOrderTraversal(tree->right_child);
}



//�������鲢���ֵ
void preOrderTraversal(HFTree tree) {
	putchar(tree->key);
	if (tree->left_child != NULL)
		preOrderTraversal(tree->left_child);
	if (tree->right_child != NULL)
		preOrderTraversal(tree->right_child);
}



//���������鲢���ֵ
void pastOrderTraversal(HFTree tree) {
	if (tree->left_child != NULL)
		pastOrderTraversal(tree->left_child);
	if(tree->right_child != NULL)
		pastOrderTraversal(tree->right_child);
	putchar(tree->key);
}
*/



//�������鲢���Huffman����
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



//����һ���ַ���ͳ���ַ����ִ�����ΪȨֵ�����ַ���Ȩֵ������
//����һ��Huffman����ɵ�ɭ��
HFTree* getCharWeighted(void) {	//���ַ����಻����MAX_CHAR
	typedef struct key_value {
		elemtype key;
		int value;
	};	//�ַ�������ִ�����һ����ֵ��
	key_value array[MAX_CHAR];
	int count = 0;	//�ַ��������
	elemtype elem;
	printf("please enter a string, end with \';\'");

	//���ַ���Ȩ��ֵ
	while ((elem = getchar()) != ';') {	
		bool isExist = false;	//���ַ��Ƿ��Ѿ�����

		//�����ֵ�����飬����������ַ�ֵ+1���˳�����
		for (int i = 0; i < count; i++) {
			if (array[i].key == elem)
			{
				isExist = true;
				array[i].value++;
				break;
			}
		}

		//��������ɸ��ַ������ڼ�ֵ�������У�д������
		if (!isExist) {
			array[count] = { elem, 1 };
			count++;
		}
	}
	//Huffuman��������һ��ɭ��
	HFTree* forest = (HFTree*)malloc((count + 1) * sizeof(HFTree));
	if (forest == NULL) exit(-2);
	for (int i = 0; i < count; i++) {
		HFTree tree = (HFTree)malloc(sizeof(HFTreeNode));
		if (tree == NULL)
			exit(-2);

		//����Huffman�����
		*tree = { NULL,array[i].key,array[i].value,NULL,NULL,{0} };
		forest[i] = tree;
	}
	forest[count] = NULL;
	return forest;
}



//����
void swap(HFTree* a, HFTree* b) {
	HFTree pointer = *a;
	*a = *b;
	*b = pointer;
}



//��ɭ���ɴ�С����Huffman������forest�������NULL
HFTree* sort(HFTree* forest) {	
	int index = 0;
	while (forest[index] != NULL)
		index++;
	//ð��
	for (int i = 0; i < index; i++) {
		for (int j = 0; j + 1 < index; j++) {
			if (forest[j]->value < forest[j + 1]->value)
				swap(&forest[j], &forest[j + 1]);
		}
	}
	return forest;
}



//����һ��Huffman������forest���ݹ�ؽ���Huffman��������һ��Huffman��
HFTree buildHuffmanTree(HFTree* forest) {
	//��forestֻʣ��һ����ʱ�˳�
	if (forest[1] == NULL)
		return forest[0];

	//Ϊ�¶���������ռ�
	HFTree root;
	root = (HFTree)malloc(sizeof(HFTreeNode));
	if (root == NULL)
		exit(-2);
	//ɭ����Huffman����㵹������
	forest = sort(forest);

	int index = 0;	//Ȩֵ��С�����forest��λ��
	while (forest[index] != NULL)
		index++;

	//������Ȩֵ��С�Ľ�㹹���һ���¶�������������forest��
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

	//�ݹ�
	return buildHuffmanTree(forest);
}



//��һ��Huffman�������нڵ���Huffman����
/*
* ����˵����
* ������һ��Huffman�����Ӹ��ڵ㿪ʼ��ÿһ�����ݹ����������ÿ����һ��
* ���Ͷ�������������������ڣ���Ӧλ�õ�Huffman���븳ֵ��������ȣ���
* ÿ����һ��������ο������ڵ��Huffman���뵽�ýڵ� Huffman�����ϣ��ݹ�
* ���������н���Huffman������ɸ�ֵ,���ڵ�û��Huffman����
*/
void createHuffmanCode(HFTree tree) {	// ������һ��Huffman��
	int degree = 0;		// �ýڵ���Huffman���е����
	HFTree a = tree;
	while (a->parent != NULL) {	//��ýڵ�����
		degree++;
		a = a->parent;
	}
	
	// Ϊ��ǰ�������Һ���Huffman��������ռ䲢��ֵ
	if (tree->left_child != NULL) {
		tree->left_child->code = (char*)malloc((degree + 2) * sizeof(char));
		if (tree->left_child->code == NULL) exit(-2);
		tree->left_child->code[degree] = '0';
		tree->left_child->code[degree + 1] = '\0';
	}
	if (tree->right_child != NULL) {
		tree->right_child->code = (char*)malloc((degree + 2) * sizeof(char));
		if (tree->right_child->code == NULL) exit(-2);
		tree->right_child->code[degree] = '1';
		tree->right_child->code[degree + 1] = '\0';
	}
	//�ݹ�
	if (tree->left_child != NULL)
		createHuffmanCode(tree->left_child);
	//���ο������ڵ��Huffman����
	a = tree;
	while (degree > 1) {
		degree--;
		a = a->parent;
		tree->code[degree - 1] = a->code[degree - 1];
	}
	//�ݹ�
	if (tree->right_child != NULL)
		createHuffmanCode(tree->right_child);
}

//int main(void) {
//	HFTree* forest = getCharWeighted();
//	HFTree huffman_tree = buildHuffmanTree(forest);
//	inOrderTraversal(huffman_tree);
//	createHuffmanCode(huffman_tree);
//	inOrderTraversal(huffman_tree);
//}