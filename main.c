#include "tree.c"
#include <stdio.h> 

#define TREELEN 6 

int main()
{
//	BiTree tree = NULL ; 
//	//创建二叉树
//	create_BiTree(&tree) ; 
//	//先序遍历二叉树
//	preOrderTraverse(tree) ;
//	printf("\n") ; 
//	printf("中序非递归遍历二叉树:\n") ;
//	inOrderTraverse(tree) ;
//    printf("先序非递归遍历二叉树:\n") ;
//	preOrderTraverse1(tree) ;
//	printf("后序遍历二叉树:\n") ;
//	postOrderTraverse(tree) ; 

	/*先序序列*/
	char preOrderData[TREELEN] = {'a' ,'b' ,'d' ,'c' ,'e' ,'f'} ;  
	
	/*中序序列*/
	char inOrderData[TREELEN]  = {'d' ,'b' ,'a' ,'e' ,'c' ,'f'} ;  
	
	BiTNode *pNode = NULL ; 
	/*由中序序列和先序序列重建二叉树*/
	Rebuild(preOrderData ,inOrderData ,TREELEN ,&pNode) ;
	/*重建的二叉树的后序遍历*/
	printf("重建的二叉树的后序遍历:\n") ;
	postOrderTraverse(pNode) ; 

	printf("分层遍历二叉树：\n") ;
	printTreeAtLevel(pNode) ;
	return 0; 
}

