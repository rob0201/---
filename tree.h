#ifndef _TREE_H_
#define _TREE_H_ 

typedef struct BiTNode
{
	char data ; 
	struct BiTNode *lchild ;  //左孩子
	struct BiTNode *rchild ;  //右孩子
}BiTNode ,*BiTree ;

/*创建二叉树*/
BiTree createBiTree() ;

/*创建二叉树*/
void create_BiTree(BiTree *tree) ; 

/*先序打印二叉树*/
void preOrderTraverse(BiTree root) ;

/*中序递归遍历二叉树*/
void inOrderTraverse(BiTree root) ; 

/*先序非递归遍历二叉树*/
void preOrderTraverse1(BiTree root) ;

/*后序非递归遍历二叉树*/
void postOrderTravese() ;

/*重建二叉树*/
void Rebuild(char *pPreOrder ,char *pInOrder ,int nTreeLenght ,BiTNode **pRoot) ; 


/*分层遍历二叉树*/
void printTreeAtLevel(BiTree tree) ;

#endif 
