#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 노드 구조체
typedef struct Node
{
    int id, elem;
    struct Node *leftchild;
    struct Node *rightchild;
} Node;

// 함수 원형
Node *initNode(int id, int elem, Node *leftchild, Node *rightchild);
void preorder(Node *root);
void inorder(Node *root);
void postorder(Node *root);

int main()
{
    // 각 폴더 id 초기화
    Node *id_8 = initNode(8, 80, NULL, NULL);
    Node *id_7 = initNode(7, 130, NULL, NULL);
    Node *id_6 = initNode(6, 120, id_7, id_8);
    Node *id_5 = initNode(5, 90, NULL, NULL);
    Node *id_4 = initNode(4, 70, NULL, NULL);
    Node *id_3 = initNode(3, 50, NULL, id_6);
    Node *id_2 = initNode(2, 30, id_4, id_5);
    Node *id_1 = initNode(1, 20, id_2, id_3);

    int order_num, id_num;
    scanf("%d %d", &order_num, &id_num); // 순회 방법과 폴더 이름 입력

    switch (order_num)
    {
    // 선위 순회
    case 1:
        switch (id_num)
        {
        case 1:
            preorder(id_1);
            break;
        case 2:
            preorder(id_2);
            break;
        case 3:
            preorder(id_3);
            break;
        case 4:
            preorder(id_4);
            break;
        case 5:
            preorder(id_5);
            break;
        case 6:
            preorder(id_6);
            break;
        case 7:
            preorder(id_7);
            break;
        case 8:
            preorder(id_8);
            break;
        default:
            printf("-1");
        }
        break;
    // 중위 순회
    case 2:
        switch (id_num)
        {
        case 1:
            inorder(id_1);
            break;
        case 2:
            inorder(id_2);
            break;
        case 3:
            inorder(id_3);
            break;
        case 4:
            inorder(id_4);
            break;
        case 5:
            inorder(id_5);
            break;
        case 6:
            inorder(id_6);
            break;
        case 7:
            inorder(id_7);
            break;
        case 8:
            inorder(id_8);
            break;
        default:
            printf("-1");
        }
        break;
    // 후위 순회
    case 3:
        switch (id_num)
        {
        case 1:
            postorder(id_1);
            break;
        case 2:
            postorder(id_2);
            break;
        case 3:
            postorder(id_3);
            break;
        case 4:
            postorder(id_4);
            break;
        case 5:
            postorder(id_5);
            break;
        case 6:
            postorder(id_6);
            break;
        case 7:
            postorder(id_7);
            break;
        case 8:
            postorder(id_8);
            break;
        default:
            printf("-1");
        }
        break;
    }

    return 0;
}

// 노드 초기화 함수
Node *initNode(int id, int elem, Node *leftchild, Node *rightchild)
{
    // newnode 동적 할당 및 메모리 할당 여부 검사
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    // newnode 초기화
    newnode->id = id;
    newnode->elem = elem;
    newnode->leftchild = leftchild;
    newnode->rightchild = rightchild;
    return newnode;
}

// 선위 순회 함수
void preorder(Node *root)
{
    printf(" %d", root->elem);
    if (root->leftchild != NULL)
    {
        preorder(root->leftchild);
    }
    if (root->rightchild != NULL)
    {
        preorder(root->rightchild);
    }
}

// 중위 순회 함수
void inorder(Node *root)
{
    if (root->leftchild != NULL)
    {
        inorder(root->leftchild);
    }
    printf(" %d", root->elem);
    if (root->rightchild != NULL)
    {
        inorder(root->rightchild);
    }
}

// 후위 순회 함수
void postorder(Node *root)
{
    if (root->leftchild != NULL)
    {
        postorder(root->leftchild);
    }
    if (root->rightchild != NULL)
    {
        postorder(root->rightchild);
    }
    printf(" %d", root->elem);
}