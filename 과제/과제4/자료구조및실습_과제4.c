#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MILLION 1000000

typedef struct Queue
{
    int *elements;
    int front, rear, size, capacity;
} Queue;

typedef struct Stack
{
    Queue *q1, *q2;
    int size;
} Stack;

// Queue 함수 원형
void initQueue(Queue *q, int capacity);
void enqueue(Queue *q, int element);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);

// Stack 함수 원형
void initStack(Stack *s, int capacity);
void push(Stack *s, int element);
int pop(Stack *s);
int top(Stack *s);
int isEmptyStack(Stack *s);
void pushMillion(Stack *s);
void printResult(char msg[], int size, clock_t start, clock_t end);

int main()
{
    Stack s;
    initStack(&s, MILLION + 100); // 100만 정도의 크기로 스택을 초기화

    char command[100];
    int num;

    // command 입력 시 반복 실행
    while (scanf("%s", command))
    {
        // 단, q 입력 시 종료
        if (strcmp(command, "q") == 0)
        {
            break;
        }

        // 시간 측정 시작
        clock_t start = clock();

        // S 입력 시
        if (strcmp(command, "S") == 0)
        {
            // 스택이 비어 있을 경우
            if (isEmptyStack(&s))
            { // printResult를 호출하며 스택이 비어 있음을 알립니다.
                printResult("Empty", s.size, start, clock());
            }
            // 스택이 비어 있지 않은 경우
            else
            { // printResult를 호출하며 스택이 비어 있지 않음을 알립니다.
                printResult("Nonempty", s.size, start, clock());
            }
        }
        // o 입력 시
        else if (strcmp(command, "o") == 0)
        {
            // 스택이 비어 있을 경우
            if (isEmptyStack(&s))
            { // printResult를 호출하며 스택이 비어 있음을 알립니다.
                printResult("Empty Stack Exception!!", s.size, start, clock());
            }
            // 스택이 비어 있지 않은 경우
            else
            {
                // pop하고 결과 출력
                int poppedValue = pop(&s);
                printf("%d (%d), ", poppedValue, s.size);
                printResult("", s.size, start, clock());
            }
        }
        // p 입력 시
        else if (strcmp(command, "p") == 0)
        {
            char input[1000];
            fgets(input, sizeof(input), stdin); // push할 숫자를 문자열로 입력

            char *token = strtok(input, " "); // 공백을 기준으로 토큰화
            while (token != NULL)
            {
                num = atoi(token);         // 토큰을 정수로 변경
                push(&s, num);             // push 실행
                token = strtok(NULL, " "); // 다음 토큰으로 이동
            }

            clock_t end = clock();                 // 시간 측정 종료
            printResult("OK", s.size, start, end); // printResult를 호출하며 push 성공을 알립니다.
        }
        // P 입력시
        else if (strcmp(command, "P") == 0)
        {
            pushMillion(&s);                           // pushMillion 실행
            printResult("OK", s.size, start, clock()); // printResult를 호출하며 pushMillion 성공을 알립니다.
        }
        // t 입력 시
        else if (strcmp(command, "t") == 0)
        {
            // 스택이 비어 있을 경우
            if (isEmptyStack(&s))
            { // printResult를 호출하며 스택이 비어 있음을 알립니다.
                printResult("Empty Stack Exception!!", s.size, start, clock());
            }
            // 스택이 비어 있지 않은 경우
            else
            {
                // top하고 결과 출력
                int topValue = top(&s);
                printf("%d (%d), ", topValue, s.size);
                printResult("", s.size, start, clock());
            }
        }
    }

    return 0;
}

// initQueue 함수
void initQueue(Queue *q, int capacity)
{
    // 큐 초기화
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    // elements 배열 동적 할당 및 메모리 할당 여부 검사
    q->elements = (int *)malloc(q->capacity * sizeof(int));
    if (q->elements == NULL)
    {
        printf("Memory Allocation Failed!");
    }
}

// enqueue 함수
void enqueue(Queue *q, int element)
{
    // rear와 elements 업데이트 후 size 증가
    q->rear = (q->rear + 1) % q->capacity;
    q->elements[q->rear] = element;
    q->size++;
}

// dequeue 함수
int dequeue(Queue *q)
{
    // 삭제 진행 후 size 업데이트
    int item = q->elements[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return item;
}

// isEmptyQueue 함수
int isEmptyQueue(Queue *q)
{
    return (q->size == 0); // size가 0이면 empty queue
}

// initStack 함수
void initStack(Stack *s, int capacity)
{
    // q1, q2 동적 할당 및 메모리 할당 여부 검사
    s->q1 = (Queue *)malloc(sizeof(Queue));
    s->q2 = (Queue *)malloc(sizeof(Queue));
    if (s->q1 == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    if (s->q2 == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    // queue 초기화
    initQueue(s->q1, capacity);
    initQueue(s->q2, capacity);
    s->size = 0;
}

// push 함수
void push(Stack *s, int element)
{
    // enqueue 실행 후 size 업데이트
    enqueue(s->q1, element);
    s->size++;
}

// pop 함수
int pop(Stack *s)
{
    // empty queue일 경우
    if (isEmptyQueue(s->q1))
    {
        return -1;
    }

    while (s->q1->size != 1)
    {
        enqueue(s->q2, dequeue(s->q1)); // q1의 요소를 q2로 이동
    }
    int popped = dequeue(s->q1); // 마지막 요소 제거

    // q1과 q2를 교환
    Queue *temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    s->size--;
    return popped;
}

// top 함수
int top(Stack *s)
{
    // empty queue일 경우
    if (isEmptyQueue(s->q1))
    {
        return -1;
    }

    while (s->q1->size != 1)
    {
        enqueue(s->q2, dequeue(s->q1)); // q1의 요소를 q2로 이동
    }
    // q1의 마지막 요소를 q2에 추가
    int topValue = dequeue(s->q1);
    enqueue(s->q2, topValue);

    // q1과 q2를 교환
    Queue *temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return topValue;
}

// isEmptyStack 함수
int isEmptyStack(Stack *s)
{
    return isEmptyQueue(s->q1); // q1이 비어있는지 확인
}

// pushMillion 함수
void pushMillion(Stack *s)
{
    for (int i = 0; i < MILLION; i++)
    {
        push(s, rand() % 90 + 10); // 10에서 99 사이의 난수 push
    }
}

// printResult 함수
void printResult(char msg[], int size, clock_t start, clock_t end)
{
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // ms 단위로 변환
    // 첫 문자가 문자열의 끝일 경우
    if (msg[0] != '\0')
    {
        printf("%s (%d), cputime = %f\n", msg, size, cpu_time_used); // 메세지, size, cpu time 출력
    }
    // 그 외의 경우
    else
    {
        printf("cputime = %f\n", cpu_time_used); // cpu time 출력
    }
}