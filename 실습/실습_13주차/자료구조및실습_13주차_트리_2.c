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
int preorder(Node *root, int sum);

int main()
{
    // 각 폴더 id 초기화
    Node *id_8 = initNode(80, NULL, NULL);
    Node *id_7 = initNode(130, NULL, NULL);
    Node *id_6 = initNode(120, id_7, id_8);
    Node *id_5 = initNode(90, NULL, NULL);
    Node *id_4 = initNode(70, NULL, NULL);
    Node *id_3 = initNode(50, NULL, id_6);
    Node *id_2 = initNode(30, id_4, id_5);
    Node *id_1 = initNode(20, id_2, id_3);

    int id_num;
    scanf("%d", &id_num); // 노드 id 입력

    int sum = 0;
    // 폴더 id가 유효한 경우
    if (id_num <= 8)
    {
        if (id_num == 1)
        {
            printf("%d", preorder(id_1, sum));
        }
        else if (id_num == 2)
        {
            printf("%d", preorder(id_2, sum));
        }
        else if (id_num == 3)
        {
            printf("%d", preorder(id_3, sum));
        }
        else if (id_num == 4)
        {
            printf("%d", preorder(id_4, sum));
        }
        else if (id_num == 5)
        {
            printf("%d", preorder(id_5, sum));
        }
        else if (id_num == 6)
        {
            printf("%d", preorder(id_6, sum));
        }
        else if (id_num == 7)
        {
            printf("%d", preorder(id_7, sum));
        }
        else if (id_num == 8)
        {
            printf("%d", preorder(id_8, sum));
        }
    }
    // 노드 id가 유효하지 않은 경우
    else
    {
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

// 선위 순회 함수
int preorder(Node *root, int sum)
{
    sum += root->elem; // 폴더 부트리의 용량의 합 업데이트
    if (root->leftchild != NULL)
    {
        sum = preorder(root->leftchild, sum);
    }
    if (root->rightchild != NULL)
    {
        sum = preorder(root->rightchild, sum);
    }
    return sum;
}