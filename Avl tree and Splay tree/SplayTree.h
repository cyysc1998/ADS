#ifndef SPLAYTREE
#define SPLAYTREE
 
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
 
typedef struct SplayNode *PSplay;
typedef PSplay Position;
typedef int ElementType;
 
struct SplayNode
{
	ElementType data;
	Position left;
	Position right;
};
static Position NullNode;
 
PSplay InitTree();
PSplay Splaying(PSplay T, ElementType x);
PSplay LLRotate(PSplay K);
PSplay RRRotate(PSplay K);
PSplay FindMax(PSplay T);
PSplay FindMin(PSplay T);
PSplay Insert(ElementType x, PSplay T);
PSplay Delete(ElementType x, PSplay T);
void Traversal(PSplay T);
void Traversal(PSplay T,int i);
 
#endif // !SPLAYTREE
 