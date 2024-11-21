#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 데크 노드 구조체
typedef struct DequeNodeType
{
    struct DequeNodeType *prev;
    int elem;
    struct DequeNodeType *next;
} DequeNodeType;

// 데크 연결리스트 구조체
typedef struct LinkedDequeType
{
    DequeNodeType *front;
    DequeNodeType *rear;
} LinkedDequeType;

// 함수 원형
DequeNodeType *newdeque(int);
LinkedDequeType *init_DeqQue();
int isEmptyDeque(LinkedDequeType *Ld);
void add_front(LinkedDequeType *Ld, int elem);
void add_rear(LinkedDequeType *Ld, int elem);
int delete_front(LinkedDequeType *Ld);
int delete_rear(LinkedDequeType *Ld);
void print_deque(LinkedDequeType *Ld);

int main()
{
    int num;
    scanf("%d", &num); // 명령의 개수

    LinkedDequeType *Ld = init_DeqQue(); // 이중연결리스트 데크 초기화

    int cnt = 0;
    int elem;
    char command[2];

    // 명령의 개수만큼 반복
    for (int i = 0; i < num; i++)
    {
        scanf("%s", command); // 명령 입력
        getchar();

        // add_front 연산
        if (strcmp(command, "AF") == 0)
        {
            scanf("%d", &elem); // 삽입 원소 입력
            getchar();
            add_front(Ld, elem); // add_front 연산 실행
            cnt++;
        }
        // add_rear 연산
        else if (strcmp(command, "AR") == 0)
        {
            scanf("%d", &elem); // 삽입 원소 입력
            getchar();
            add_rear(Ld, elem); // add_rear 연산 실행
            cnt++;
        }
        // delete_front 연산
        else if (strcmp(command, "DF") == 0)
        {
            // 공백일 경우
            if (cnt == 0)
            {
                printf("underflow\n");
                break;
            }
            delete_front(Ld); // delete_front 연산 실행
            cnt--;
        }
        // delete_rear 연산
        else if (strcmp(command, "DR") == 0)
        {
            // 공백일 경우
            if (cnt == 0)
            {
                printf("underflow\n");
                break;
            }
            delete_rear(Ld); // delete_rear 연산 실행
            cnt--;
        }
        // print 연산
        else if (strcmp(command, "P") == 0)
        {
            print_deque(Ld); // print 연산 실행
        }
    }

    // 메모리 해제
    free(Ld);

    return 0;
}

// 데크 노드 초기화 함수
DequeNodeType *newdeque(int elem)
{
    DequeNodeType *dn = (DequeNodeType *)malloc(sizeof(DequeNodeType));
    if (dn == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    dn->elem = elem;
    dn->prev = NULL;
    dn->next = NULL;
    return dn;
}

// 데크 연결리스트 초기화 함수
LinkedDequeType *init_DeqQue()
{
    LinkedDequeType *dq = (LinkedDequeType *)malloc(sizeof(LinkedDequeType));
    if (dq == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    dq->front = NULL;
    dq->rear = NULL;
    return dq;
}

// 데크 공백 확인 함수
int isEmptyDeque(LinkedDequeType *Ld)
{
    if (Ld->front == NULL)
    {
        return 1;
    }
    else
        return 0;
}

// add_front 연산 함수
void add_front(LinkedDequeType *Ld, int elem)
{
    DequeNodeType *dn = newdeque(elem);

    if (isEmptyDeque(Ld) == 1)
    {
        Ld->front = dn;
        Ld->rear = dn;
        dn->prev = NULL;
        dn->next = NULL;
    }

    else
    {
        dn->next = Ld->front;
        Ld->front->prev = dn;
        dn->prev = NULL;
        Ld->front = dn;
    }
}

// add_rear 연산 함수
void add_rear(LinkedDequeType *Ld, int elem)
{
    DequeNodeType *dn = newdeque(elem);

    if (isEmptyDeque(Ld) == 1)
    {
        Ld->front = dn;
        Ld->rear = dn;
        dn->prev = NULL;
        dn->next = NULL;
    }

    else
    {
        dn->prev = Ld->rear;
        Ld->rear->next = dn;
        dn->next = NULL;
        Ld->rear = dn;
    }
}

// delete_front 연산 함수
int delete_front(LinkedDequeType *Ld)
{
    if (isEmptyDeque(Ld) == 1)
    {
        return -1;
    }

    DequeNodeType *curr = Ld->front;
    int elem = curr->elem;

    if (Ld->front->next == NULL)
    {
        Ld->front = NULL;
        Ld->rear = NULL;
    }
    else
    {
        Ld->front = curr->next;
        curr->next->prev = NULL;
    }

    return elem;
}

// delete_rear 연산 함수
int delete_rear(LinkedDequeType *Ld)
{
    if (isEmptyDeque(Ld) == 1)
    {
        return -1;
    }

    DequeNodeType *curr = Ld->rear;
    int elem = curr->elem;

    if (Ld->rear->prev == NULL)
    {
        Ld->front = NULL;
        Ld->rear = NULL;
    }
    else
    {
        Ld->rear = curr->prev;
        curr->prev->next = NULL;
    }

    return elem;
}

// print_deque 연산 함수
void print_deque(LinkedDequeType *Ld)
{
    DequeNodeType *curr = Ld->front;

    while (curr != NULL)
    {
        printf(" %d", curr->elem);
        curr = curr->next;
    }
    printf("\n");
}

/*

7
AF 10
AF 20
AR 30
P
DF
DR
P

*/

/*

15
AF 10
AF 20
AF 30
AR 40
AR 50
P
DF
DF
DR
P
DF
DR
DR

*/