#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 구조체
typedef struct Node
{
    char elem[100];
    struct Node *left;
    struct Node *right;
} Node;

// 함수 원형
Node *getnode();
Node *makeExternalNode();
Node *makeInternalNode();
Node *buildDecisionTree();
void processNode(Node *);
void runDecisionTree(Node *);

int main()
{
    Node *v = buildDecisionTree(); // 의사 결정 트리 구축
    printf("Tree complete. Now Running!!\n");

    // 3회의 테스트 상담 수행
    for (int i = 0; i < 3; i++)
    {
        runDecisionTree(v);
    }

    return 0;
}

// getnode 함수
Node *getnode()
{
    // newnode 동적 할당 및 메모리 할당 여부 검사
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (newnode == NULL)
    {
        printf("Memory Allocation Failed");
    }

    newnode->left = newnode->right = NULL; // newnode 초기화

    return newnode;
}

// makeExternalNode 함수
Node *makeExternalNode()
{
    Node *v = getnode(); // 노드 생성

    // 결정 입력
    printf("Enter decision: ");
    gets(v->elem);

    return v;
}

// makeInternalNode 함수
Node *makeInternalNode()
{
    char answer[10];
    Node *v = getnode(); // 노드 생성

    // 질문 입력
    printf("Enter question: ");
    gets(v->elem);

    //////////////////////// 왼쪽 ////////////////////////

    // yes 선택에 대한 답 입력
    printf("Question if yes to '%s'? ", v->elem);
    gets(answer);

    // 답이 yes인 경우 내부 노드 재생성
    if (strcmp(answer, "yes") == 0)
    {
        v->left = makeInternalNode();
    }
    // 답이 no인 경우 외부 노드 생성
    else
    {
        v->left = makeExternalNode();
    }

    //////////////////////// 오른쪽 ////////////////////////

    // no 선택에 대한 답 입력
    printf("Question if no to '%s'? ", v->elem);
    gets(answer);

    // 답이 yes인 경우 내부 노드 생성
    if (strcmp(answer, "yes") == 0)
    {
        v->right = makeInternalNode();
    }
    // 답이 no인 경우 외부 노드 생성
    else
    {
        v->right = makeExternalNode();
    }

    return v;
}

// buildDecisionTree 함수
Node *buildDecisionTree()
{
    printf("***Let’s build a dichotomous QA system\n");
    return makeInternalNode(); // 내부 노드 함수를 반환 받아 결정 트리 구축 시작
}

// processNode 함수
void processNode(Node *v)
{
    printf("%s ", v->elem); // 의사 결정 입력

    // 부트리가 하나라도 NULL이 아닐 경우
    if (v->left != NULL || v->right != NULL)
    {
        char answer[10];
        gets(answer); // 대답 입력

        // 답이 yes인 경우 왼쪽으로 이동
        if (strcmp(answer, "yes") == 0)
        {
            processNode(v->left);
        }
        // 답이 no인 경우 오른쪽으로 이동
        else
        {
            processNode(v->right);
        }
    }
}

// 결정 트리 실행 함수
void runDecisionTree(Node *v)
{
    printf("\n***Please answer questions\n");
    processNode(v); // processNode 호출 하여 대답 입력
}