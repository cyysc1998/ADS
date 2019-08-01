#include "SplayTree.h"
 
PSplay InitTree()						//初始化树，将NullNode看做NULL指针，避免了检测空树
{
	if (NullNode == NULL)
	{
		NullNode = (PSplay)malloc(sizeof(SplayNode));
		if (NULL == NullNode)
		{
			printf("error,memery is full");
		}
		//该节点的左子树和右子树指向该节点本身。
		NullNode->left = NullNode->right = NullNode;
	}
	return NullNode;
}
 
PSplay Splaying(PSplay T, ElementType x)
{
	//带有左指针和右指针的头结点包含了左子树和右子树的根
	struct SplayNode Header;
	Header.left = Header.right = NullNode;
 
	Position LeftTreeMax, RightTreeMin;
	LeftTreeMax = RightTreeMin = &Header;
 
	NullNode->data = x;		//这里NullNode的数据域是x
	//当查找到NullNode时或者是找到了x时，循环结束
	while (x != T->data)
	{
		if (x < T->data)
		{
			if (x < T->left->data)
			{
				T = LLRotate(T);
			}
			if (NullNode == T->left)		//左子树为空
			{
				break;
			}
			RightTreeMin->left = T;
			RightTreeMin = T;
			//只要第一次左子树变为非空，那么T = T->left将会使LeftTreeMax在初始化后不再改变
			T = T->left;
			//这样的话LeftTreeMax将仍然指向Header，它将包含右子树的根
		}
		else
		{
			if (x > T->right->data)
			{
				T = RRRotate(T);
			}
			if (NullNode == T->right)		//右子树为空
			{
				break;
			}
			LeftTreeMax->right = T;
			LeftTreeMax = T;
			//只要第一次右子树变为非空，那么T = T->right将会使RightTreeMin在初始化后不再改变
			T = T->right;
		}
	}
	//连接
	LeftTreeMax->right = T->left;		
	RightTreeMin->left = T->right;		
	T->left = Header.right;		
	T->right = Header.left;
 
	return T;
}
 
PSplay LLRotate(PSplay K)
{
	Position M;
	M = K->left;
	K->left = M->right;
	M->right = K;
 
	return M;
}
 
PSplay RRRotate(PSplay K)
{
	Position M;
	M = K->right;
	K->right = M->left;
	M->left = K;
 
	return M;
}
 
PSplay FindMax(PSplay T)
{
	T = Splaying(T, INT_MAX);	//最大值处展开
	return T;
}
 
PSplay FindMin(PSplay T)
{
	T = Splaying(T, INT_MIN);	//最小值处展开
	return T;
}
 
PSplay Insert(ElementType x, PSplay T)
{
	PSplay NewNode;
	NewNode = (PSplay)malloc(sizeof(SplayNode));
	if (NewNode == NULL)
		printf("error ,memory is full");
	NewNode->data = x;
 
	if (T == NullNode)		//T是空的情形
	{
		NewNode->left = NewNode->right = NullNode;
		T = NewNode;
	}
	else 
	{
		T = Splaying(T, x);		//伸展
 
		if (x < T->data) 
		{
			NewNode->left = T->left;
			NewNode->right = T;
			T->left = NullNode;
			T = NewNode;
		}
		else if (x > T->data)
		{
			NewNode->right = T->right;
			NewNode->left = T;
			T->right = NullNode;
			T = NewNode;
		}
		else if (x == T->data) 
		{
			/* 重复值不做插入 */
			free(NewNode);
		}
	}
	return T;
}
 
PSplay Delete(ElementType x, PSplay T)
{
	Position newnode;
	if (T != NullNode)
	{
		T = Splaying(T, x);
		if (x == T->data)	//找得到该元素
		{
			if (T->left == NullNode)		//左子树为空
			{
				newnode = T->right;			//根就是该节点的右子树
			}
			else
			{
				newnode = T->left;			//该节点的左子树成为新根
				newnode = Splaying(newnode, x);	//x作为展开点，那么这个伸展操作将会把最大的节点提升至根处
				//那么这个根节点没有右子树(右子树为空)  
				newnode->right = T->right;	//将原来的右子树挂上
			}
			free(T);
			T = newnode;	//newnode作为新的根节点
		}
	}
	return T;
}
 
void Traversal(PSplay T)		//中序遍历
{
	if (NullNode != T)
	{
		Traversal(T->left);
		printf("%d ", T->data);
		Traversal(T->right);
	}
}
 
void Traversal(PSplay T, int i)	//前序遍历
{
	if (NullNode != T)
	{
		printf("%d ", T->data);
		Traversal(T->left, 1);
		Traversal(T->right, 1);
	}
}

//   https://blog.csdn.net/zy010101/article/details/83089068