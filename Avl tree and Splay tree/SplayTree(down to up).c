#include<stdio.h>
#include<stdlib.h>
//伸展树的实现 
typedef struct splayNode {
	int element;
	struct splayNode* left;
	struct splayNode* right;
}*SplayTree;
SplayTree SingleTotateWithLeft(SplayTree T);
SplayTree SingleTotateWithRight(SplayTree T);
SplayTree DoubleTotateWithLeft(SplayTree T);
SplayTree DoubleTotateWithRight(SplayTree T);
SplayTree splaying(SplayTree Root, SplayTree T, SplayTree P);
void print(SplayTree T);
 
void print(SplayTree T) {
	//中序 
	if (T->left != NULL) {
		print(T->left);
	}
	printf("%d ", T->element);
	if (T->right != NULL) {
		print(T->right);
	}
}
void print2(SplayTree T) {
	//前序 根左右
	printf("%d ", T->element);
	if (T->left != NULL) {
		print2(T->left);
	}
	if (T->right != NULL) {
		print2(T->right);
	}
}
 
 
SplayTree insert(int X, SplayTree T) {
	if (T == NULL) {
		//树为空
		T = (SplayTree)malloc(sizeof(struct splayNode));
		T->element = X;
		T->left = T->right = NULL;
	}
	else {
		//不空
		if (X > T->element) {
			//往右子树走
			T->right = insert(X, T->right);
		}
		else if (X < T->element) {
			//往左子树走
			T->left = insert(X, T->left);
		}
	}
	return T;
}
//查找
SplayTree find(int X, SplayTree T) {
	if (T == NULL) {
		printf("tree is NULL");
		return NULL;
	}
	else {
		SplayTree P = T;
		while (P) {
			if (X > P->element) {
				//在右子树中
				P = P->right;
			}
			else if (X < P->element) {
				//在左子树中
				P = P->left;
			}
			else if (X == P->element) {
				//找到了
				//开始调整伸展树
				T = splaying(T, T, P);
				return T;
			}
		}
		return NULL;
	}
}
SplayTree splaying(SplayTree Root, SplayTree T, SplayTree P) {
	if (P->element > T->element) {
		//比T大 往右走
		T->right = splaying(Root, T->right, P);
	}
	else if (P->element < T->element) {
		//比T小 往左走
		T->left = splaying(Root, T->left, P);
	}
 
 
	//三种情况
	//1要查找的结点为根结点的左右孩子 zig 
	if (Root->left != NULL && Root->left == P) {
		//是根的左孩子，实行左旋
		Root = SingleTotateWithLeft(Root);
		return Root;
	}
	else if (Root->right != NULL && Root->right == P) {
		//是根的右孩子，实行右旋
		Root = SingleTotateWithRight(Root);
		return Root;
	}
	//第二种情况  zig-zag
	if (T->left != NULL && T->left != P && T->left->right != NULL && T->left->right == P) {
		//先右旋 后左旋 即左双旋
		T = DoubleTotateWithLeft(T);
	}
	else if (T->right != NULL && T->right != P && T->right->left != NULL && T->right->left == P) {
		//先左旋 后右旋 即右双旋
		T = DoubleTotateWithRight(T);
	}
	//第三种情况 zig-zig
	if (T->left != NULL && T->left != P && T->left->left != NULL && T->left->left == P) {
		//先左旋 再左旋
		T = SingleTotateWithLeft(T);
		T = SingleTotateWithLeft(T);
	}
	else if (T->right != NULL && T->right != P && T->right->right != NULL && T->right->right == P) {
		//先右旋 再右旋
		T = SingleTotateWithRight(T);
		T = SingleTotateWithRight(T);
	}
 
	return T;
}
//左单旋
SplayTree SingleTotateWithLeft(SplayTree T) {
	SplayTree M;
	M = T->left;
	T->left = M->right;
	M->right = T;
 
	return M;
}
//右单旋
SplayTree SingleTotateWithRight(SplayTree T) {
	SplayTree M;
	M = T->right;
	T->right = M->left;
	M->left = T;
 
	return M;
}
//左双旋
SplayTree  DoubleTotateWithLeft(SplayTree T) {
	//先进行右旋 再进行左旋
	T->left = SingleTotateWithRight(T->left);
	return SingleTotateWithLeft(T);
}
//右双旋
SplayTree DoubleTotateWithRight(SplayTree T) {
	//先进行左旋，再进行右旋
	T->right = SingleTotateWithLeft(T->right);
	return SingleTotateWithRight(T);
}
 
 
int main() {
	//测试
	SplayTree T = NULL;
	T = insert(7, T);
	T = insert(6, T);
	T = insert(5, T);
	T = insert(4, T);
	T = insert(3, T);
	T = insert(2, T);
	T = insert(1, T);
 
	print2(T);
 
	T = find(1, T);
	printf("查找后：");
	print2(T);
	T = find(2, T);
	T = find(5, T);
	printf("再次查找后：");
	print2(T);
 
	system("pause");
	return 0;
}