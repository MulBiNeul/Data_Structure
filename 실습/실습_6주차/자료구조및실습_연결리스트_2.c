#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// Node의 정보
typedef struct Node
{
    int coef;
    int exp;
    struct Node *next;
} Node;

// List의 정보
typedef struct List
{
    struct Node *head;
} List;

// 함수 원형
List *__init__(List *);
Node *makeNode(int, int);
void appendTerm(List *, int, int);
List *addPoly(List *, List *);
void NODE_FREE(List *);

int main()
{
    int coef, exp;

    int LENGTH_OF_FIRST_POLYNOMIAL;
    scanf("%d", &LENGTH_OF_FIRST_POLYNOMIAL); // 첫 번째 다항식 항의 개수

    // 첫 번째 다항식 동적 할당
    List *FIRST_POLYNOMIAL = (List *)malloc(sizeof(List));
    // 메모리 할당 여부 확인
    if (FIRST_POLYNOMIAL == NULL)
    {
        printf("MEMORY ALLOCATION FAILED!\n");
    }
    __init__(FIRST_POLYNOMIAL); // 첫 번째 다항식 초기화

    // 첫 번째 다항식 입력
    for (int i = 0; i < LENGTH_OF_FIRST_POLYNOMIAL; i++)
    {
        scanf("%d %d", &coef, &exp);             // 계수와 지수 입력
        appendTerm(FIRST_POLYNOMIAL, coef, exp); // 항 추가 함수 호출
    }

    int LENGTH_OF_SECOND_POLYNOMIAL;
    scanf("%d", &LENGTH_OF_SECOND_POLYNOMIAL); // 두 번째 다항식 항의 개수

    // 두 번째 다항식 동적 할당
    List *SECOND_POLYNOMIAL = (List *)malloc(sizeof(List));
    // 메모리 동적 할당 여부 확인
    if (SECOND_POLYNOMIAL == NULL)
    {
        printf("MEMORY ALLOCATION FAILED!\n");
    }
    __init__(SECOND_POLYNOMIAL); // 두 번째 다항식 초기화

    // 두 번째 다항식 입력
    for (int i = 0; i < LENGTH_OF_SECOND_POLYNOMIAL; i++)
    {
        scanf("%d %d", &coef, &exp);              // 계수와 지수 입력
        appendTerm(SECOND_POLYNOMIAL, coef, exp); // 항 추가 함수 호출
    }

    List *result = addPoly(FIRST_POLYNOMIAL, SECOND_POLYNOMIAL); // 다항식 덧셈 함수 호출

    Node *curr = result->head;
    // result에 담긴 다항식의 계수와 지수 출력
    while (curr->next != NULL)
    {
        curr = curr->next;
        printf(" %d %d", curr->coef, curr->exp);
    }

    // 메모리 해제
    NODE_FREE(FIRST_POLYNOMIAL);
    NODE_FREE(SECOND_POLYNOMIAL);
    free(FIRST_POLYNOMIAL);
    free(SECOND_POLYNOMIAL);
    free(result);
    return 0;
}

// List 초기화 함수
List *__init__(List *L)
{
    Node *header = (Node *)malloc(sizeof(Node)); // 다항식의 맨 앞을 의미하는 header

    // 헤더 연결 및 초기화
    L->head = header;
    header->next = NULL;
    return L;
}

// Node 정보 입력 함수
Node *makeNode(int coef, int exp)
{
    // newnode 동적 할당
    Node *newnode = (Node *)malloc(sizeof(Node));
    // 메모리 할당 여부 검사
    if (newnode == NULL)
    {
        printf("MEMORY ALLOCATION FAILED!\n");
    }

    // newnode에 정보 저장 후 반환
    newnode->coef = coef;
    newnode->exp = exp;
    newnode->next = NULL;
    return newnode;
}

// 항 추가 함수
void appendTerm(List *L, int coef, int exp)
{
    Node *newnode = makeNode(coef, exp); // 추가할 정보 받기

    // 현재 리스트에 정보의 끝까지 이동
    Node *curr = L->head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = newnode; // 항 추가
}

// 다항식 덧셈 함수
List *addPoly(List *FIRST_POLYNOMIAL, List *SECOND_POLYNOMIAL)
{
    // result 리스트 동적할당
    List *result = (List *)malloc(sizeof(List));
    // 메모리 할당 여부 검사
    if (result == NULL)
    {
        printf("MEMORY ALLOCATION FAILED!\n");
    }
    __init__(result); // result 리스트 초기화

    // 각각의 다항식의 위치를 확인할 노드 생성
    Node *curr_i = FIRST_POLYNOMIAL->head->next;
    Node *curr_j = SECOND_POLYNOMIAL->head->next;

    // 하나의 다항식이 끝날 때까지 연산
    while ((curr_i != NULL) && (curr_j != NULL))
    {
        // curr_i의 차수가 더 높을 경우
        if (curr_i->exp > curr_j->exp)
        { // result 리스트에 해당 항의 정보 전달
            appendTerm(result, curr_i->coef, curr_i->exp);
            curr_i = curr_i->next; // 다음 위치로 이동
        }
        // curr_j의 차수가 더 높을 경우
        else if (curr_i->exp < curr_j->exp)
        { // result 리스트에 해당 항의 정보 전달
            appendTerm(result, curr_j->coef, curr_j->exp);
            curr_j = curr_j->next; // 다음 위치로 이동
        }
        // 차수가 동일할 경우
        else
        {
            int sum = curr_i->coef + curr_j->coef; // 계수의 합 저장
            // 합이 0이 아니라면
            if (sum != 0)
            { // result 리스트에 항의 정보 전달
                appendTerm(result, sum, curr_i->exp);
            }
            // 두 개 모두 다음 위치로 이동
            curr_i = curr_i->next;
            curr_j = curr_j->next;
        }
    }

    // curr_i가 끝까지 도달하지 않았을 경우
    while (curr_i != NULL)
    { // 나머지를 모두 항에 추가
        appendTerm(result, curr_i->coef, curr_i->exp);
        curr_i = curr_i->next;
    }
    // curr_j가 끝까지 도달하지 않았을 경우
    while (curr_j != NULL)
    { // 나머지를 모두 항에 추가
        appendTerm(result, curr_j->coef, curr_j->exp);
        curr_j = curr_j->next;
    }

    return result; // result 리스트 반환
}

void NODE_FREE(List *L)
{
    Node *curr = L->head;
    Node *next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}