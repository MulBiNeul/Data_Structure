#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TreeNode 구조체
typedef struct TreeNode
{
    int id;
    struct TreeNode *leftchild;
    struct TreeNode *rightchild;
} TreeNode;

// 함수 원형
TreeNode *rootnode(TreeNode *root, int id);
void leftnode(TreeNode *leftnode, int id);
void rightnode(TreeNode *right, int id);
void makeBinaryTree(TreeNode *root, int left_id, int right_id);
TreeNode *search(TreeNode *root, int id);

int main()
{
    int node_num;
    scanf("%d", &node_num); // 노드 개수 입력

    int root_id, left_id, right_id;
    TreeNode *root = NULL;
    TreeNode *ptr = NULL;

    // 노드 개수만큼 반복
    for (int i = 0; i < node_num; i++)
    {
        scanf("%d %d %d", &root_id, &left_id, &right_id); // 노드 정보 입력
        // 첫 번째 실행의 경우 루트 노드가 설정 이후 트리 형성
        if (i == 0)
        {
            root = rootnode(root, root_id);
            makeBinaryTree(root, left_id, right_id);
        }
        // 그 외의 경우 루트 노드를 탐색 이후 트리 형성
        else
        {
            ptr = search(root, root_id);
            makeBinaryTree(ptr, left_id, right_id);
        }
    }

    int search_time;
    scanf("%d", &search_time); // 탐색 횟수

    // 탐색 횟수만큼 반복
    while (search_time > 0)
    {
        TreeNode *tmp = root;
        char command[100];

        scanf("%s", command);   // 탐색 정보 입력
        printf(" %d", tmp->id); // 루트 노드 정보 출력
        // 명령의 길이만큼 실행
        for (int i = 0; i < strlen(command); i++)
        {
            // 텀색 정보가 L인 경우
            if (command[i] == 'L')
            {
                tmp = tmp->leftchild;   // 왼쪽 자식 노드로 이동
                printf(" %d", tmp->id); // 노드 정보 출력
            }
            // 탐색 정보가 R인 경우
            else if (command[i] == 'R')
            {
                tmp = tmp->rightchild;  // 오른쪽 자식 노드로 이동
                printf(" %d", tmp->id); // 노드 정보 출력
            }
        }
        search_time--; // 탐색 횟수 업데이트
        printf("\n");
    }

    return 0;
}

// rootnode 함수
TreeNode *rootnode(TreeNode *root, int id)
{ // newnode 동적 할당 및 메모리 할당 여부 검사
    TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    // newnode 초기화 이후 반환
    newnode->id = id;
    newnode->leftchild = NULL;
    newnode->rightchild = NULL;
    return newnode;
}

// leftnode 함수
void leftnode(TreeNode *upper, int id)
{
    // newnode 동적 할당 및 메모리 할당 여부 검사
    TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    // newnode 초기화
    newnode->id = id;
    newnode->leftchild = NULL;
    newnode->rightchild = NULL;
    upper->leftchild = newnode; // 생성된 newnode는 상위 노드의 좌측 자식 노드
}

// rightnode 함수
void rightnode(TreeNode *upper, int id)
{
    // newnode 동적 할당 및 메모리 할당 여부 검사
    TreeNode *newnode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    // newnode 초기화
    newnode->id = id;
    newnode->leftchild = NULL;
    newnode->rightchild = NULL;
    upper->rightchild = newnode; // 생성된 newnode는 상위 노드의 우측 자식 노드
}

// makeBinaryTree 함수
void makeBinaryTree(TreeNode *root, int left_id, int right_id)
{
    // 좌측 노드 정보가 0이 아니면 노드 생성
    if (left_id != 0)
    {
        leftnode(root, left_id);
    }
    // 우측 노드 정보가 0이 아니면 노드 생성
    if (right_id != 0)
    {
        rightnode(root, right_id);
    }
}

// search 함수
TreeNode *search(TreeNode *root, int id)
{
    // 정보가 없으면 NULL 반환
    if (root == NULL)
    {
        return NULL;
    }

    // 노드의 정보가 일치하면 해당 노드 반환
    if (root->id == id)
    {
        return root;
    }
    // 노드의 정보가 일치하지 않으면
    else
    {
        TreeNode *leftResult = search(root->leftchild, id);   // 좌측 노드 탐색
        TreeNode *rightResult = search(root->rightchild, id); // 우측 노드 탐색

        // 좌측 노드 탐색에 정보가 존재하면 좌측 노드 정보 반환
        if (leftResult != NULL)
        {
            return leftResult;
        }
        // 우측 노드 탐색에 정보가 존재하면 우측 노드 정보 반환
        if (rightResult != NULL)
        {
            return rightResult;
        }
        return NULL;
    }
}

/*

9
5 3 9
3 8 15
8 0 2
2 0 0
15 0 0
9 7 10
7 12 0
12 0 0
10 0 0
3
RLL
LL
LR

*/