#include<stdio.h>
#include<stdlib.h>


typedef struct SplayNode *SplayTree, *Position;
struct SplayNode{
    int data;
    SplayTree p_left;
    SplayTree p_right;
};

SplayTree Splay( SplayTree T, int data );    //from up to down
SplayTree SingleRotateLeft( SplayTree T );
SplayTree SingleRotateRight( SplayTree T );
void InorderPrint( SplayTree T );


int main(void)
{
    SplayTree T = (SplayTree)malloc(sizeof(struct SplayNode));
    SplayTree R = (SplayTree)malloc(sizeof(struct SplayNode));
    T->data = 2;
    R->data = 3;
    T->p_left = NULL;
    T->p_right = R;
    R->p_left = R->p_right = NULL;
    InorderPrint(T); printf("\n");
    T = Splay(T,3);
    InorderPrint(T); printf("\n");
    system("pause"); 
}

SplayTree Splay( SplayTree T, int data )
{
    struct SplayNode Head;
    Position LeftTreeMax, RightTreeMin;
    Head.p_left = Head.p_right = NULL;
    LeftTreeMax = RightTreeMin = &Head;

    while( T->data != data )
    {
        if( data < T->data )
        {
            if( data < T->p_left->data )
                T = SingleRotateLeft(T);
            if( T->p_left == NULL )
                break;
            RightTreeMin->p_left = T;
            RightTreeMin = T;
            T = T->p_left;
        }
        else
        {
            if( data > T->p_right->data )
                T = SingleRotateRight(T);
            if( T->p_right == NULL )
                break;
            LeftTreeMax->p_right = T;
            LeftTreeMax =  T;
            T = T->p_right;
        }
    }
    LeftTreeMax->p_right = T->p_left;
    RightTreeMin->p_left = T->p_right;
    T->p_left = Head.p_right;
    T->p_right = Head.p_left;
    return T;
}

SplayTree SingleRotateLeft( SplayTree T )
{
    SplayTree L = T->p_left;
    SplayTree B = L->p_right;
    L->p_right = T;
    T->p_left = B;
    return L;
}

SplayTree SingleRotateRight( SplayTree T )
{
    SplayTree R = T->p_right;
    SplayTree B = R->p_left;
    R->p_left = T;
    T->p_right = B;
    return R;
}

void InorderPrint( SplayTree T )
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