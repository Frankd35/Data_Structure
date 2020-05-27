#include<stdio.h>
#include<stdlib.h>



// binary sort tree



typedef int elemtype;	//�����������������Ԫ������

//����һ���ӿ�
int getElemKey(elemtype e) {
	return e;
}

int getElem(elemtype* pnt ) {
	return scanf_s("%d", pnt) ? 1 : 0;
	
}



typedef struct BSTreeNode {	//����������������
	elemtype elem;
	BSTreeNode* left_child;
	BSTreeNode* right_child;
};



typedef BSTreeNode* BSTree;	//�������������



//���ң���Ԫ�ش���ʱ����� node ���ظ�Ԫ�ص�ַ��Ԫ�ز�����ʱ����� node �������һ�β��ҽ���ַ
//����ֵ��������Ԫ�ش��ڷ��� 1�������ڷ��� 0
int searchBST(BSTree tree, elemtype e, BSTree* node) {

	//��ǰ�ڵ㲻Ϊ��
	if (tree == NULL)
		return 0;

	if (getElemKey(tree->elem) == getElemKey(e)) {
		*node = tree;
		return 1;
	}
	//����Ԫ��˳��С�ڵ�ǰ�ڵ�Ԫ��
	else if (getElemKey(tree->elem) > getElemKey(e)) {
		//���������������������
		if (tree->left_child != NULL)
			return searchBST(tree->left_child, e, node);
		//������������Ԫ�ز�����
		else {
			*node = tree;
			return 0;
		}
	}
	//����Ԫ��˳����ڵ�ǰ�ڵ�Ԫ��
	else if (getElemKey(tree->elem) < getElemKey(e)) {
		//���������������������
		if (tree->right_child != NULL)
			return searchBST(tree->right_child, e, node);
		//������������Ԫ�ز�����
		else {
			*node = tree;
			return 0;
		}
	}
}



//������������в�����
//����ֵ�����������Ҹ�Ԫ�ز��������Ҳ���ɹ��򷵻� 1�����򷵻� 0
int insertBST(BSTree tree, elemtype e) {
	BSTree node;

	//��ǰ�ڵ㲻Ϊ��
	if (tree == NULL)
		return 0;
	//����Ԫ�ش����򲻲���
	if (searchBST(tree, e, &node))
		return 0;
	//����Ԫ��˳��С�ڵ�ǰ�ڵ�Ԫ��,���������н��в���
	else if (getElemKey(node->elem) > getElemKey(e)) {
			node->left_child = (BSTree)malloc(sizeof(BSTreeNode));
			node->left_child->elem = e;
			node->left_child->left_child = node->left_child->right_child = NULL;
			return 1;
	}
	//����Ԫ��˳����ڵ�ǰ�ڵ�Ԫ��,���������н��в���
	else if (getElemKey(node->elem) < getElemKey(e)) {
			node->right_child = (BSTree)malloc(sizeof(BSTreeNode));
			node->right_child->elem = e;
			node->right_child->left_child = node->right_child->right_child = NULL;

			return 1;
	}
}



//����һ�Ŷ���������������
BSTree buildBSTree(void) {
	elemtype e;
	getElem(&e);
	BSTree tree = (BSTree)malloc(sizeof(BSTreeNode));
	if (tree == NULL) exit(-2);
	tree->elem = getElemKey(e);	
	tree->left_child = tree->right_child = NULL;
	if (tree == NULL)
		exit(-2);
	//�������������
	while (getElem(&e))
		insertBST(tree, e);
	return tree;
}



//ɾ���ڵ�
void deleteBSTNode(BSTree* pnt) {
	//pnt�Ƕ���ָ�룬ֱ���޸ĸ��ڵ�������

	BSTree tree;
	if ((*pnt)->left_child == NULL) {

		//���ӽڵ�Ϊ�������ӽڵ㲻Ϊ��
		if ((*pnt)->right_child != NULL) {
			tree = *pnt;
			*pnt = (*pnt)->right_child;
			free(tree);
		}
		//�����ӽڵ㶼Ϊ��
		else {
			free(*pnt);
			pnt = NULL;
		}
	}
	//���ӽڵ�Ϊ�������ӽڵ㲻Ϊ��
	else if((*pnt)->right_child == NULL) {
		tree = *pnt;	//��ʱ������Ҫ�Ľ���ַ
		*pnt = (*pnt)->left_child;
		free(tree);
	}
	//�����ӽڵ㶼��Ϊ��
	//ɾ���ý�㲢��˳��С�ڸýڵ�Ԫ����ѡȡ����������ýڵ�
	else {

		BSTree* parent = &(*pnt)->left_child;	//parent �Ǹ��ڵ� right_child ��ַ

		//�ҵ�˳��С�ڸýڵ�����Ľ�㲢��tree ָ��ýڵ�
		tree = (*pnt)->left_child;
		while (tree->right_child != NULL) {
			parent = &tree->right_child;
			tree = tree->right_child;
		}
		//����������
		//˳��С�ڸýڵ�����Ľ��û�����ӽڵ�
		if (tree->left_child == NULL) {
			*parent = NULL;
			tree->left_child = (*pnt)->left_child;
			tree->right_child = (*pnt)->right_child;
			free(*pnt);
			*pnt = tree;
			
		}
		//˳��С�ڸýڵ�����Ľ�������ӽڵ�
		else {
			BSTree lchild = tree->left_child;	//��ʱ���������ӽڵ��ַ
			*parent = lchild;
			tree->left_child = (*pnt)->left_child;
			tree->right_child = (*pnt)->right_child;
			free(*pnt);
			*pnt = tree;
			
		}
	}
}



//ɾ�����
//����ֵ�����������Ҹ�Ԫ��ɾ���ɹ��򷵻� 1�����򷵻� 0
int deleteBST(BSTree* pnt, elemtype e) {
	BSTree tree = *pnt;
	//��ǰ�ڵ㲻Ϊ��
	if (tree == NULL)
		return 0;

	if (getElemKey(tree->elem) == getElemKey(e)) {
		deleteBSTNode(pnt);
		return 1;
	}
	//ɾ��Ԫ��˳��С�ڵ�ǰ�ڵ�Ԫ��
	else if (getElemKey(tree->elem) > getElemKey(e)) {
		//���������������������
		if (tree->left_child != NULL)
			deleteBST(&tree->left_child, e);
		//������������Ԫ�ز�����
		else 
			return 0;
	}
	//ɾ��Ԫ��˳����ڵ�ǰ�ڵ�Ԫ��
	else if (getElemKey(tree->elem) < getElemKey(e)) {
		//���������������������
		if (tree->right_child != NULL)
			deleteBST(&tree->right_child, e);
		//������������Ԫ�ز�����
		else 
			return 0;
	}

}


