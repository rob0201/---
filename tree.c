#include "tree.h"
#include <stdio.h> 
#include <malloc.h> 

#define NODE_NUMBER 100 //树的节点

/*创建二叉树*/
BiTree createBiTree()
{
	char ch ;
	printf("input data<0:NULL>: ") ; 
//	ch = getchar() ; 
	scanf(" %c",&ch ) ;
	//构造二叉树
	BiTNode *node ;  
	if(ch != '0')
	{
		//putchar(ch) ;
		node = (BiTNode *) malloc(sizeof(BiTNode)) ; 
		if(node == NULL)
		{
			printf("申请节点失败\n") ;
			return NULL ; 
		}

		node->data = ch ; 
		node->lchild = createBiTree() ; 
		node->rchild = createBiTree() ; 

	}
	else
	{
		node = NULL ;
	}
	return  node ; 
}


void preOrderTraverse(BiTree root)
{

	if(root)
	{
		printf("%c\t" ,root->data) ;
		preOrderTraverse(root->lchild) ;
		preOrderTraverse(root->rchild) ; 
	}
//	printf("\n") ;
}


/*创建二叉树
 *参数是一个指针的指针，因为创建二叉树的过程中要不断改变这个指针
 *C++中可以用引用实现
 */
void create_BiTree(BiTree *tree)
{
	//动态分配空间
	
	*tree = (BiTree)malloc(sizeof(BiTNode)) ;

	if(*tree == NULL )
	{
		printf("malloc error\n") ;
		return ; 
	}

	char ch ; 
	printf("input data:") ;
	scanf(" %c" ,&ch) ;

	if(ch == '0')
	{
		return ; 
	}
	else
	{
		(*tree)->data = ch ;  //填充data 
		//创建左子树
		create_BiTree(&((*tree)->lchild)) ;
		//创建右子树
		create_BiTree(&((*tree)->rchild)) ; 
	}
	
}

/*中序遍历二叉树*/
/*
 *中序非递归遍历的思想：
 *根节点首先入栈，然后将根节点的所有左子树的左节点入栈，直至左节点为空
 *此时弹出栈顶元素，并将该节点的右孩子入栈，且将该右孩子节点的所有的左
 *孩子也入栈，如此循环，直至遍历所有的节点
 */

void inOrderTraverse(BiTree root)
{
	/*定义个顺序栈*/
	BiTNode* stack[NODE_NUMBER] = {0} ; 
	int top = -1 ; 
	BiTNode* current_node = NULL; 

	if(root)
	{
		BiTree child_root = root ; 
		//直到该节点没有左孩子节点，停止入栈
		while(top > -1 || child_root)
		{
			while(child_root)
			{
				top++ ;
				stack[top] = child_root ;  //首先根节点入栈
				child_root = child_root->lchild ;  //将该节点的所有左孩子节点入栈
			}
		
			//打印栈顶元素
			if(top > -1)
			{

				current_node = stack[top] ;//获取栈顶节点 
				top-- ; 
				printf("%c\t",current_node->data) ; 
				child_root = current_node->rchild ;  //右孩子节点入栈
			}
		}
		printf("\n") ; 
	}
	else
	{
		printf("树为空\n") ;
		return ; 
	}
}


/*先序非递归遍历二叉树
 *思想：先将根节点入栈，只要栈不为空，就弹出栈顶节点，
 *再将根节点的左右孩子入栈，但是先将右孩子入栈，这样
 *保证了右孩子在左孩子遍历之后再遍历。
 */
void preOrderTraverse1(BiTree root) 
{
	if(root)
	{
		BiTNode *stack[NODE_NUMBER] = {0} ; 
		int top = -1 ;  //初始时栈为空，即top=-1
		top++ ; 
		stack[top] = root ;  //根节点入栈
		
		//栈不为空就弹出栈顶元素
		while(top > -1)
		{
			BiTNode *node ; 
			node = stack[top] ; 
			top-- ; 
			printf("%c\t",node->data) ;

			//右孩子先入栈
			if(node->rchild)
			{
				top++ ; //[]优先级高于++
				stack[top] = node->rchild ; 
			}

			//左孩子再入栈
			if(node->lchild)
			{
				top++ ;
				stack[top] = node->lchild ; 
			}
		}
		printf("\n") ; 
	}
	else
	{
		printf("树为空\n") ; 
		return ; 
	}
}

/*
 *非递归后序遍历二叉树
 *思想：
 *
 */
void postOrderTraverse(BiTree root)
{
	BiTNode *stack[NODE_NUMBER]= {0} ; 
	int top = -1 ; 
	
	BiTNode *preVisited = NULL ;  //已经访问过的节点
	BiTNode *current    = root ;  //当前节点
	//树非空
	while(top != -1 || current )
	{
		//根节点和它的左子树的所有左孩子节点入栈
		while(current)
		{
			top++ ; 
			stack[top] = current ; 
			current = current->lchild ; 
		}

		//获取栈顶节点
		current = stack[top] ;

		//处理该节点的右孩子节点，右孩子节点要么是已经访问了的，要么不存在
		if(current->rchild == preVisited || current->rchild == NULL)
		{
			printf("%c\t",current->data) ;
			preVisited = current ; 
			top-- ; 
			current = NULL ;
		}
		else//有右孩子
		{
			//右孩子入栈
			current = current->rchild ; 
		}
	}
	printf("\n") ;
}

/*功能：
		重建二叉树
 *参数: 
		pPreOrder 指向二叉树的线序遍历序列
		pInOrder  指向二叉树的中序遍历序列
		nTreeLenght 二叉树的节点数目
		pRoot     指向二叉树根节点的双指针
 */
void Rebuild(char *pPreOrder ,char *pInOrder ,int nTreeLenght ,BiTNode **pRoot) 
{
	/*边界条件检查*/
	if(pPreOrder == NULL || pInOrder == NULL )
	{
		return ; 
	}

	/*申请一个新节点，存储子树的根节点*/
	BiTNode *tree_root = (BiTNode*)malloc(sizeof(BiTNode)) ; 
	tree_root->data    = *pPreOrder; 
	tree_root->lchild  = NULL ; 
	tree_root->rchild  = NULL ; 

	if(*pRoot == NULL )
	{
		*pRoot = tree_root ; 
	}

	char *p = pInOrder ; 
	int tempLen  = 0 ; 
	int rightLen = 0 ; 
	int leftLen  = 0 ;

	/*在中序序列中寻找当前根节点的位置*/
	while(*p != *pPreOrder )
	{
		tempLen++ ; 

		if(tempLen > nTreeLenght)
		{
			break ; 
		}

		if( p == NULL || pPreOrder == NULL ) 
		{
			break ; 
		}

		p++ ;    //p指向序列的下一个字符
	}
	
	/*计算左子树的长度*/
	leftLen  = tempLen ; 
	
	/*计算右子树的长度*/
	rightLen = nTreeLenght - leftLen - 1 ; 
	

	/*重建左子树*/
	if( leftLen > 0)
	{
		Rebuild( pPreOrder + 1 ,pInOrder ,leftLen ,&( ( *pRoot )->lchild ) ) ; 
	}

	/*重建右子树*/
	if(rightLen > 0)
	{
		Rebuild(pPreOrder + leftLen + 1 ,pInOrder + leftLen + 1 ,rightLen ,&( ( *pRoot )->rchild ) ) ; 
	}


}

/*分层遍历二叉树
 *
 *现将根节点入队，出队，若节点有左右孩子，则
 *将左右孩子节点入队。
 */

void printTreeAtLevel(BiTree tree)
{
	/*定义一个队列,用数组来实现
	 *假设 first = last = 0 队列空
	 *first = end  ; 队满
	 */

	BiTNode *queue[NODE_NUMBER] = {0} ; 
	BiTNode *root = tree ;
	BiTNode *queue_node ; 

	int first = 0 ; //队首
	int end   = 0 ; //队尾

	/*边界条件检测*/
	if( tree == NULL)
	{
		return ; 
	}

	/*将根节点入队*/
	queue[end] = root ;
	end++ ; 

	//while( end != 0 && first != 0 && root != NULL)
	do
	{
		queue_node = queue[first] ; 
		/*队首节点的左孩子存在，则入队*/
		if( queue_node->lchild != NULL)
		{
			queue[end] = queue_node->lchild ; 
			end++ ;
		}

		/*队首节点的右孩子存在，则入队*/
		if( queue_node->rchild != NULL )
		{
			queue[end] = queue_node->rchild ; 
			end++ ; 
		}

		printf("%c\t" ,queue_node->data) ; 
		first++ ; 

	}while( end != 0 && first != 0 && root != NULL && end != first) ;
	printf("\n") ; 
}
