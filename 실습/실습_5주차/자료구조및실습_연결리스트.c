#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 선언
typedef struct Node
{
    struct Node *prev; // 이전 노드를 가리키는 링크
    char elem;         // 원소
    struct Node *next; // 다음 노드를 가리키는 링크
} Node;

// 리스트 구조체 선언
typedef struct List
{
    struct Node *head; // 노드의 머리
    struct Node *tail; // 노드의 꼬리
    int size;          // 리스트의 크기
} List;

// 함수 원형
Node *makeNode(char);
List *__initList__(List *);
void add(List *, int, char);
void delete(List *, int);
char get(List *, int);
void print(List *);
void NODE_FREE(List *);

int main()
{
    int N;
    scanf("%d", &N); // 연산의 개수 입력
    getchar();       // 엔터 제거

    // 이중연결리스트 선언 및 초기화
    List *DoubleConnectedList = (List *)malloc(sizeof(List));
    __initList__(DoubleConnectedList);

    char command, elem;
    int rank;
    // 연산의 개수만큼 반복
    for (int i = 0; i < N; i++)
    {
        scanf("%c", &command); // 연산의 종류 입력

        // 삽입 연산
        if (command == 'A')
        {
            scanf(" %d %c", &rank, &elem);        // 순위 rank와 원소 elem 입력
            getchar();                            // 엔터 입력 제거
            add(DoubleConnectedList, rank, elem); // 삽입 연산 함수 호출
        }
        // 삭제 연산
        else if (command == 'D')
        {
            scanf(" %d", &rank);                // 순위 rank 입력
            getchar();                          // 엔터 입력 제거
            delete (DoubleConnectedList, rank); // 삭제 연산 함수 호출
        }
        // 반환 연산
        else if (command == 'G')
        {
            scanf(" %d", &rank);                       // 순위 rank 입력
            getchar();                                 // 엔터 입력 제거
            char tmp = get(DoubleConnectedList, rank); // 반환 연산 함수 호출
            if (tmp != 0)
            {
                printf("%c\n", tmp);
            }
        }
        // 출력 연산
        else if (command == 'P')
        {
            getchar();                  // 엔터 입력 제거
            print(DoubleConnectedList); // 출력 연산 함수 호출
        }
    }

    NODE_FREE(DoubleConnectedList);
    free(DoubleConnectedList);

    return 0;
}

// 노드 생성 함수
Node *makeNode(char elem)
{
    // 노드 동적 할당
    Node *newnode = (Node *)malloc(sizeof(Node));
    newnode->elem = elem; // 원소 전달
    newnode->prev = NULL; // 이전 노드를 가리키는 링크 초기화
    newnode->next = NULL; // 다음 노드를 가리키는 링크 초기화
    return newnode;       // 노드의 정보 반환
}

// 리스트 초기화 함수
List *__initList__(List *L)
{
    Node *header = (Node *)malloc(sizeof(Node));  // header 노드 생성
    Node *trailer = (Node *)malloc(sizeof(Node)); // trailer 노드 생성

    L->head = header;       // 리스트의 머리는 header 노드
    header->prev = NULL;    // header의 이전 링크는 NULL
    header->next = trailer; // trailer의 다음 링크는 trailer

    L->tail = trailer;      // 리스트의 꼬리는 trailer 노드
    trailer->prev = header; // trailer의 이전 링크는 header
    trailer->next = NULL;   // trailer의 다음 링크는 NULL

    return L; // 리스트 반환
}

// 삽입 연산 함수
void add(List *L, int rank, char elem)
{
    // rank의 위치가 유효하지 않다면
    if (rank < 1 || rank > L->size + 1)
    {
        printf("invalid position\n"); // 에러 메세지 출력
        return;                       // 함수 종료
    }

    Node *newnode = makeNode(elem); // newnode 생성 및 원소 전달
    Node *curr = L->head->next;     // 데이터를 갖는 첫 노드에 연결
    // 원하는 위치까지 curr 노드 이동
    for (int i = 1; i < rank; i++)
    {
        curr = curr->next;
    }
    // 원하는 위치에 newnode 연결
    newnode->next = curr;
    newnode->prev = curr->prev;
    curr->prev->next = newnode;
    curr->prev = newnode;

    L->size++; // 리스트의 크기 업데이트
}

// 삭제 연산 함수
void delete(List *L, int rank)
{
    // rank의 위치가 유효하지 않다면
    if (rank < 1 || rank > L->size)
    {
        printf("invalid position\n"); // 에러 메세지 출력
        return;                       // 함수 종료
    }

    Node *curr = L->head->next; // 데이터를 갖는 첫 노드에 연결
    // 원하는 위치까지 curr 노드 이동
    for (int i = 1; i < rank; i++)
    {
        curr = curr->next;
    }
    // 해당 위치의 노드 연결 끊기
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    free(curr); // 메모리 해제

    L->size--; // 리스트의 크기 업데이트
}

// 반환 연산 함수
char get(List *L, int rank)
{
    // rank의 위치가 유효하지 않다면
    if (rank < 1 || rank > L->size)
    {
        printf("invalid position\n"); // 에러 메세지 출력
        return 0;                     // 함수 종료
    }

    else
    {
        Node *curr = L->head->next; // 데이터를 갖는 첫 노드에 연결
        // 원하는 위치까지 curr 노드 이동
        for (int i = 1; i < rank; i++)
        {
            curr = curr->next;
        }
        // printf("%c\n", curr->elem);
        return curr->elem; // curr 노드의 원소 반환
    }
}

// 출력 연산 함수
void print(List *L)
{
    Node *curr = L->head; // 데이터를 갖는 첫 노드에 연결
    // curr이 NULL이 아닐때까지
    for (int i = 0; i < L->size; i++)
    {
        curr = curr->next;
        printf("%c", curr->elem); // curr 노드의 원소 출력
    }
    printf("\n");
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

/*
9
A 1 D
A 2 a
A 3 y
D 1
P
G 3
A 1 S
P
G 3
*/