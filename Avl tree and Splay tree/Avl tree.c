#include<stdio.h>
#include<stdlib.h>

typedef struct AvlNode *AvlTree, *Position;
struct AvlNode{
    int height;
    AvlTree p_left;
    AvlTree p_right;
    int data;
}; 

AvlTree Insert( AvlTree T, int data );
AvlTree Delete( AvlTree T, int data );
AvlTree Find( AvlTree T, int data );
int Height( AvlTree T );
void InorderPrint( AvlTree T );

AvlTree SingleRotateLeft( AvlTree T );
AvlTree SingleRotateRight( AvlTree T );
AvlTree DoubleRotateLeft( AvlTree T );
AvlTree DoubleRotateRight( AvlTree T );

AvlTree FindMax( AvlTree T );
AvlTree FindMin( AvlTree T );

int main(void)
{
    AvlTree T = NULL;
    T = Insert(T,2);
    InorderPrint(T); printf("\n");
    T = Insert(T,5);
    InorderPrint(T); printf("\n");
    T = Insert(T,-1);
    InorderPrint(T); printf("\n");
    T = Insert(T,78);
    InorderPrint(T); printf("\n");
    T = Insert(T,4);
    InorderPrint(T); printf("\n");
    T = Insert(T,10);
    InorderPrint(T); printf("\n");
    T = Insert(T,3);
    InorderPrint(T); printf("\n");
    printf("%d %d\n",FindMax(T)->data,FindMin(T)->data);
    printf("%d\n",Find(T,3)->data);
    T = Delete(T,3);
    InorderPrint(T); printf("\n");
    T = Delete(T,10);
    InorderPrint(T); printf("\n");
    system("pause");
}

AvlTree Insert( AvlTree T, int data )
{
    if( T == NULL )
    {
        T = (AvlTree)malloc(sizeof(struct AvlNode));
        T->data = data;
        T->p_left = T->p_right = NULL;
        T->height = 0;
    }
    else if( T->data > data )
    {
        T->p_left = Insert(T->p_left,data);
        if( Height(T->p_left) - Height(T->p_right) == 2 )   //Just this case
        {
            if( T->p_left->data > data )
                T = SingleRotateLeft(T);
            else
                T = DoubleRotateLeft(T);
        }
    }
    else if( T->data < data )
    {
        T->p_right = Insert(T->p_right,data);
        if( Height(T->p_left) - Height(T->p_right) == -2 )   //Just this case
        {
            if( T->p_right->data < data )
                T = SingleRotateRight(T);
            else                                  // if T->p_right->data == data, then max of bf(T) is 1
                T = DoubleRotateRight(T);
        }
    }
    if( T != NULL )
        T->height = ( Height(T->p_left)>Height(T->p_right) ? Height(T->p_left):Height(T->p_right) ) + 1;
    return T;
}

int Height( AvlTree T )
{
    if( T == NULL )
        return -1;
    else
        return T->height;
}

void InorderPrint( AvlTree T )
{
    if( T == NULL )
        return;
    else 
    {
        InorderPrint( T->p_left );
        printf("%d ",T->data);
        InorderPrint( T->p_right );
    }
}

AvlTree SingleRotateLeft( AvlTree T )
{
    AvlTree L = T->p_left;
    AvlTree B = L->p_right;
    L->p_right = T;
    T->p_left = B;
    T->height = Height(T);
    L->height = Height(L);
    return L;
}

AvlTree SingleRotateRight( AvlTree T )
{
    AvlTree R = T->p_right;
    AvlTree B = R->p_left;
    R->p_left = T;
    T->p_right = B;
    T->height = Height(T);
    R->height = Height(R);
    return R;
}

AvlTree DoubleRotateLeft( AvlTree T )
{
    T->p_left = SingleRotateRight( T->p_left );
    return SingleRotateLeft(T);
}

AvlTree DoubleRotateRight( AvlTree T )
{
    T->p_right = SingleRotateLeft( T->p_right );
    return SingleRotateRight(T);
} 

AvlTree Delete( AvlTree T, int data )
{
    if( T == NULL )
    {
        printf("No such data!\n");
        return T;
    }
    else if( T->data > data )
    {
        T->p_left = Delete(T->p_left,data);
        if( Height(T->p_left) - Height(T->p_right) == -2 )
        {
            AvlTree pt_right = T->p_right;
            if( Height(pt_right->p_left) > Height(pt_right->p_right) )
                T = DoubleRotateRight(T);
            else
                T = SingleRotateRight(T);
        }
    }
    else if( T->data < data )
    {
        T->p_right = Delete(T->p_right,data);
        if( Height(T->p_left) - Height(T->p_right) == 2 )
        {
            AvlTree pt_left = T->p_left;
            if( Height(pt_left->p_left) < Height(pt_left->p_right) )
                T = DoubleRotateLeft(T);
            else
                T = SingleRotateLeft(T);
        }
    }
    else
    {
        if( T->p_left!=NULL && T->p_right!=NULL )      //T has both left subtree and  right subtree
        {
            if( Height(T->p_left) > Height(T->p_right) )   //In this case, we can find the max node in the left tree.
            {                                              //And we don't need to care if avl tree is balanced.
                AvlTree pmax = FindMax(T->p_left);
                T->data = pmax->data;    //In this way, we don't need to change the array.
                T->p_left = Delete(T->p_left,pmax->data);
            }
            else
            {
                AvlTree pmin = FindMin(T->p_right);
                T->data = pmin->data;
                T->p_right = Delete(T->p_right,pmin->data);
            }
        }
        else  //This case includes three small cases.
        {
            AvlTree ptr = T;
            T = T->p_left ? T->p_left:T->p_right;
            free(ptr);
        }
        
    }
    if( T != NULL )
        T->height = ( Height(T->p_left)>Height(T->p_right) ? Height(T->p_left):Height(T->p_right) ) + 1;
    return T;
}

AvlTree FindMax( AvlTree T )
{
    if( T->p_right == NULL )
        return T;
    else
        return FindMax(T->p_right);
}


AvlTree FindMin( AvlTree T )
{
    if( T->p_left == NULL )
        return T;
    else
        return FindMin(T->p_left);
}

AvlTree Find( AvlTree T, int data )
{
    if( T == NULL )
    {
        printf("No such data!\n");
        return NULL;
    }
    if( T->data == data )
        return T;
    else if( T->data > data )
        return Find(T->p_left,data);
    else
        return Find(T->p_right,data);
}
