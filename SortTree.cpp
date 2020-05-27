#include<stdio.h>
#include<stdlib.h>



// binary sort tree



typedef int elemtype;	//定义二叉排序树数据元素类型

//定义一个接口
int getElemKey(elemtype e) {
	return e;
}

int getElem(elemtype* pnt ) {
	return scanf_s("%d", pnt) ? 1 : 0;
	
}



typedef struct BSTreeNode {	//定义二叉排序树结点
	elemtype elem;
	BSTreeNode* left_child;
	BSTreeNode* right_child;
};



typedef BSTreeNode* BSTree;	//定义二叉搜索树



//查找，当元素存在时向参数 node 返回该元素地址，元素不存在时向参数 node 返回最后一次查找结点地址
//返回值：若数据元素存在返回 1，不存在返回 0
int searchBST(BSTree tree, elemtype e, BSTree* node) {

	//当前节点不为空
	if (tree == NULL)
		return 0;

	if (getElemKey(tree->elem) == getElemKey(e)) {
		*node = tree;
		return 1;
	}
	//查找元素顺序小于当前节点元素
	else if (getElemKey(tree->elem) > getElemKey(e)) {
		//若有左子树则查找左子树
		if (tree->left_child != NULL)
			return searchBST(tree->left_child, e, node);
		//若无左子树则元素不存在
		else {
			*node = tree;
			return 0;
		}
	}
	//查找元素顺序大于当前节点元素
	else if (getElemKey(tree->elem) < getElemKey(e)) {
		//若有右子树则查找右子树
		if (tree->right_child != NULL)
			return searchBST(tree->right_child, e, node);
		//若无右子树则元素不存在
		else {
			*node = tree;
			return 0;
		}
	}
}



//向二叉排序树中插入结点
//返回值：若树存在且该元素不在树中且插入成功则返回 1，否则返回 0
int insertBST(BSTree tree, elemtype e) {
	BSTree node;

	//当前节点不为空
	if (tree == NULL)
		return 0;
	//插入元素存在则不插入
	if (searchBST(tree, e, &node))
		return 0;
	//插入元素顺序小于当前节点元素,在左子树中进行插入
	else if (getElemKey(node->elem) > getElemKey(e)) {
			node->left_child = (BSTree)malloc(sizeof(BSTreeNode));
			node->left_child->elem = e;
			node->left_child->left_child = node->left_child->right_child = NULL;
			return 1;
	}
	//插入元素顺序大于当前节点元素,在右子树中进行插入
	else if (getElemKey(node->elem) < getElemKey(e)) {
			node->right_child = (BSTree)malloc(sizeof(BSTreeNode));
			node->right_child->elem = e;
			node->right_child->left_child = node->right_child->right_child = NULL;

			return 1;
	}
}



//建立一颗二叉排序树并返回
BSTree buildBSTree(void) {
	elemtype e;
	getElem(&e);
	BSTree tree = (BSTree)malloc(sizeof(BSTreeNode));
	if (tree == NULL) exit(-2);
	tree->elem = getElemKey(e);	
	tree->left_child = tree->right_child = NULL;
	if (tree == NULL)
		exit(-2);
	//输入待插入序列
	while (getElem(&e))
		insertBST(tree, e);
	return tree;
}



//删除节点
void deleteBSTNode(BSTree* pnt) {
	//pnt是二级指针，直接修改父节点内数据

	BSTree tree;
	if ((*pnt)->left_child == NULL) {

		//左子节点为空且右子节点不为空
		if ((*pnt)->right_child != NULL) {
			tree = *pnt;
			*pnt = (*pnt)->right_child;
			free(tree);
		}
		//左右子节点都为空
		else {
			free(*pnt);
			pnt = NULL;
		}
	}
	//右子节点为空且左子节点不为空
	else if((*pnt)->right_child == NULL) {
		tree = *pnt;	//暂时储存需要的结点地址
		*pnt = (*pnt)->left_child;
		free(tree);
	}
	//左右子节点都不为空
	//删除该结点并以顺序小于该节点元素中选取最大的来代替该节点
	else {

		BSTree* parent = &(*pnt)->left_child;	//parent 是父节点 right_child 地址

		//找到顺序小于该节点的最大的结点并让tree 指向该节点
		tree = (*pnt)->left_child;
		while (tree->right_child != NULL) {
			parent = &tree->right_child;
			tree = tree->right_child;
		}
		//重新链接树
		//顺序小于该节点的最大的结点没有左子节点
		if (tree->left_child == NULL) {
			*parent = NULL;
			tree->left_child = (*pnt)->left_child;
			tree->right_child = (*pnt)->right_child;
			free(*pnt);
			*pnt = tree;
			
		}
		//顺序小于该节点的最大的结点有左子节点
		else {
			BSTree lchild = tree->left_child;	//暂时储存其左子节点地址
			*parent = lchild;
			tree->left_child = (*pnt)->left_child;
			tree->right_child = (*pnt)->right_child;
			free(*pnt);
			*pnt = tree;
			
		}
	}
}



//删除结点
//返回值：若树存在且该元素删除成功则返回 1，否则返回 0
int deleteBST(BSTree* pnt, elemtype e) {
	BSTree tree = *pnt;
	//当前节点不为空
	if (tree == NULL)
		return 0;

	if (getElemKey(tree->elem) == getElemKey(e)) {
		deleteBSTNode(pnt);
		return 1;
	}
	//删除元素顺序小于当前节点元素
	else if (getElemKey(tree->elem) > getElemKey(e)) {
		//若有左子树则查找左子树
		if (tree->left_child != NULL)
			deleteBST(&tree->left_child, e);
		//若无左子树则元素不存在
		else 
			return 0;
	}
	//删除元素顺序大于当前节点元素
	else if (getElemKey(tree->elem) < getElemKey(e)) {
		//若有右子树则查找右子树
		if (tree->right_child != NULL)
			deleteBST(&tree->right_child, e);
		//若无右子树则元素不存在
		else 
			return 0;
	}

}


