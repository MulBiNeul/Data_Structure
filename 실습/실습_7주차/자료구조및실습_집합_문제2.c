#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// 집합 구조체
typedef struct Set
{
    int elem;
    struct Set *next;
} Set;

// 리스트 구조체
typedef struct List
{
    Set *head;
} List;

// 함수 원형
List *__init__();
Set *getnode(int elem);
List *makeset(List *, int);
List *_union(List *, List *);
List *_interact(List *, List *);
void free_list(List *);

int main()
{
    int A_size, B_size, elem;
    // 집합 A, 집합 B 초기화
    List *A = __init__();
    List *B = __init__();

    // 집합 A

    scanf("%d", &A_size); // 집합 A의 크기 입력
    // 집합 A의 원소를 입력 받아 집합 생성
    for (int i = 0; i < A_size; i++)
    {
        scanf("%d", &elem);
        makeset(A, elem);
    }

    // 집합 B

    scanf("%d", &B_size); // 집합 B의 크기 입력
    // 집합 B의 원소를 입력 받아 집합 생성
    for (int i = 0; i < B_size; i++)
    {
        scanf("%d", &elem);
        makeset(B, elem);
    }

    // 합집합

    List *res_union = __init__(); // 합집합 리스트
    res_union = _union(A, B);     // 합집합 실행

    // 합집합 출력
    Set *curr = res_union->head->next;
    while (curr != NULL)
    {
        printf(" %d", curr->elem);
        curr = curr->next;
    }
    // 합집합이 공집합일 경우 0 출력
    if (res_union->head->next == NULL)
    {
        printf(" 0");
    }
    printf("\n");

    // 교집합

    List *res_interact = __init__(); // 교집합 리스트
    res_interact = _interact(A, B);  // 교집합 실행

    // 교집합 출력
    Set *curr2 = res_interact->head->next;
    while (curr2 != NULL)
    {
        printf(" %d", curr2->elem);
        curr2 = curr2->next;
    }
    // 교집합이 공집합일 경우 0 출력
    if (res_interact->head->next == NULL)
    {
        printf(" 0");
    }

    // 메모리 해제
    free_list(A);
    free_list(B);
    free_list(res_union);
    free_list(res_interact);

    return 0;
}

// 리스트 초기화
List *__init__()
{
    // 리스트 동적 할당
    List *L = (List *)malloc(sizeof(List));
    // 메모리 할당 여부 검사
    if (L == NULL)
    {
        printf("Memory Allocation Failed!\n");
    }

    // 더미 노드 생성
    Set *dummy = (Set *)malloc(sizeof(Set));
    if (dummy == NULL)
    {
        printf("Memory Allocation Failed!\n");
    }

    L->head = dummy;    // 리스트의 헤드를 더미 노드 설정
    dummy->next = NULL; // 더미 노드의 next 포인터 초기화

    return L;
}

// 집합의 원소 노드 생성 함수
Set *getnode(int elem)
{ // 집합의 원소를 전달 받아 저장
    Set *newset = (Set *)malloc(sizeof(Set));
    newset->elem = elem;
    newset->next = NULL;

    return newset; // 저장된 원소 노드 반환
}

// 집합 생성 함수
List *makeset(List *L, int elem)
{
    Set *newset = getnode(elem); // 집합의 원소 노드 생성
    Set *curr = L->head;         // 더미 노드로 시작

    // 집합의 마지막 원소로 이동
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = newset; // 새 원소를 마지막에 연결

    return L;
}

// 합집합 함수
List *_union(List *A, List *B)
{
    List *res = __init__(); // 결과 리스트 초기화

    // 집합 A와 집합 B를 순회할 노드 생성
    Set *i = A->head->next;
    Set *j = B->head->next;

    // 하나의 집합 끝에 도달할 때까지 반복
    while (i != NULL || j != NULL)
    {
        // 집합 A의 원소가 없을 경우 집합 B의 원소 추가
        if (i == NULL)
        {
            makeset(res, j->elem);
            j = j->next;
        }
        // 집합 B의 원소가 없을 경우 집합 A의 원소 추가
        else if (j == NULL)
        {
            makeset(res, i->elem);
            i = i->next;
        }
        // 두 집합 모두 원소가 존재할 경우
        else
        {
            // 집합 A의 원소가 더 작은 경우 집합 A의 원소 추가
            if (i->elem < j->elem)
            {
                makeset(res, i->elem);
                i = i->next;
            }
            // 집합 B의 원소가 더 작은 경우 집합 B의 원소 추가
            else if (i->elem > j->elem)
            {
                makeset(res, j->elem);
                j = j->next;
            }
            // 두 집합의 원소가 같을 경우
            else
            {
                // 원소 추가 후 두 집합 모두 다음으로 이동
                makeset(res, i->elem);
                i = i->next;
                j = j->next;
            }
        }
    }

    return res;
}

// 교집합 함수
List *_interact(List *A, List *B)
{
    List *res = __init__(); // 결과 리스트 초기화

    // 집합 A와 집합 B를 순회할 노드 생성
    Set *i = A->head->next;
    Set *j = B->head->next;

    // 두 집합 모두 끝에 도달할 때까지 반복
    while (i != NULL && j != NULL)
    {
        // 집합 A의 원소가 집합 B의 원소보다 작을 경우
        if (i->elem < j->elem)
        {
            i = i->next; // 집합 A의 다음 원소로 이동
        }
        // 집합 B의 원소가 집합 A의 원소보다 작을 경우
        else if (i->elem > j->elem)
        {
            j = j->next; // 집합 B의 다음 원소로 이동
        }
        // 두 집합의 원소가 같을 경우
        else
        {
            // 원소 추가 이후 두 집합 모두 다음 원소로 이동
            makeset(res, i->elem);
            i = i->next;
            j = j->next;
        }
    }

    return res;
}

// 메모리 해제 함수
void free_list(List *L)
{
    // 모든 노드를 순회하여 메모리 해제
    Set *current = L->head;
    while (current != NULL)
    {
        Set *temp = current;
        current = current->next;
        free(temp);
    }
    free(L);
}