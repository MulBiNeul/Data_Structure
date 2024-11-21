#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// 노드 구조체
typedef struct Node
{
    int elem;
    struct Node *leftchild;
    struct Node *rightchild;
} Node;

// 함수 원형
Node *initNode(int elem, Node *leftchild, Node *rightchild);
void preorder(Node *root);

int main()
{
    // 트리 구성
    Node *F8 = initNode(80, NULL, NULL);
    Node *F7 = initNode(130, NULL, NULL);
    Node *F6 = initNode(120, F7, F8);
    Node *F5 = initNode(90, NULL, NULL);
    Node *F4 = initNode(70, NULL, NULL);
    Node *F3 = initNode(50, NULL, F6);
    Node *F2 = initNode(30, F4, F5);
    Node *F1 = initNode(20, F2, F3);

    int node_num;
    scanf("%d", &node_num); // 노드 번호 입력

    // 노드 번호에 따른 명령 실행
    switch (node_num)
    {
    case 1:
        preorder(F1);
        break;
    case 2:
        preorder(F2);
        break;
    case 3:
        preorder(F3);
        break;
    case 4:
        preorder(F4);
        break;
    case 5:
        preorder(F5);
        break;
    case 6:
        preorder(F6);
        break;
    case 7:
        preorder(F7);
        break;
    case 8:
        preorder(F8);
        break;
    default:
        printf("-1");
    }

    return 0;
}

// 노드 초기화 함수
Node *initNode(int elem, Node *leftchild, Node *rightchild)
{
    // newnode 동적 할당 및 메모리 할당 여부 검사
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    // newnode 초기화
    newnode->elem = elem;
    newnode->leftchild = leftchild;
    newnode->rightchild = rightchild;
    return newnode;
}

// 전위 순회 함수
void preorder(Node *root)
{
    printf("%d ", root->elem); // 현재 위치의 폴더 용량 출력
    // 재귀 실행
    if (root->leftchild != NULL)
    {
        printf("%d ", root->leftchild->elem);
    }
    if (root->rightchild != NULL)
    {
        printf("%d ", root->rightchild->elem);
    }
}