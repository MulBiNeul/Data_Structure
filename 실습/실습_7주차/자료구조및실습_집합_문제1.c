#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// 집합 구조체
typedef struct Set
{
    int elem;
    struct Set *next;
} Set;

// 함수 원형
Set *getnode(int elem);
Set *makeset(Set *, int);
int subset(Set *, Set *);
void freeSet(Set *);

int main()
{
    int A_size, B_size, elem;
    // 집합 A, 집합 B 동적할당
    Set *A = (Set *)malloc(sizeof(Set));
    Set *B = (Set *)malloc(sizeof(Set));

    // 집합 A
    scanf("%d", &A_size); // 집합 A의 크기
    for (int i = 0; i < A_size; i++)
    { // 집합 A의 크기만큼 원소를 입력 받아 집합 생성
        scanf("%d", &elem);
        makeset(A, elem);
    }

    // 집합 B
    scanf("%d", &B_size); // 집합 B의 크기
    for (int i = 0; i < B_size; i++)
    { // 집합 B의 크기만큼 원소를 입력 받아 집합 생성
        scanf("%d", &elem);
        makeset(B, elem);
    }

    // 부분 집합이면 0, 아니면 B에 속하지 않은 A의 가장 작은 원소 출력
    int res = subset(A, B);
    printf("%d\n", res);

    // 메모리 해제
    freeSet(A);
    freeSet(B);
    return 0;
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
Set *makeset(Set *set, int elem)
{
    Set *newset = getnode(elem); // 집합의 원소 노드 생성

    // 현재 집합의 끝으로 이동
    while (set->next != NULL)
    {
        set = set->next;
    }
    set->next = newset; // 생성한 집합의 원소 연결

    return set; // 생성한 집합 반환
}

// 부분 집합 검사
int subset(Set *A, Set *B)
{ // A가 공집합일 경우 0 반환
    if (A == NULL)
    {
        return 0;
    }

    // 집합 A의 끝에 도달할 때까지 반복
    while (A != NULL)
    { // 집합 B가 공집합일 경우
        if (B == NULL)
        {
            return A->elem; // 집합 A의 가장 작은 원소 반환
        }
        // 집합 B에 원소가 존재할 경우
        else
        { // 집합 A의 원소가 집합 B의 원소보다 작을 경우
            if (A->elem < B->elem)
            {
                return A->elem; // 집합 A의 가장 작은 원소 반환
            }
            // 집합 A의 원소가 집합 B의 원소보다 클 경우
            else if (A->elem > B->elem)
            {
                B = B->next; // 집합 B의 다음 원소로 이동
            }
            // 집합 A의 원소와 집합 B의 원소가 같을 경우
            else
            { // 집합 A, 집합 B 모두 다음 원소로 이동
                A = A->next;
                B = B->next;
            }
        }
    }
    return 0; // 부분 집합일 경우 0 반환
}

// 메모리 해제 함수
void freeSet(Set *set)
{
    Set *current = set;
    // 집합의 원소를 순회하며 메모리 해제
    while (current != NULL)
    {
        Set *next = current->next;
        free(current);
        current = next;
    }
}