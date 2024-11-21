#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MILLION 1000000
#define MIN_CAPACITY 10000

// 스택 구조체
typedef struct Stack
{
    int *elements;
    int *minValues;
    int top;
    int minTop;
    int capacity;
} Stack;

// 함수 원형
void initStack(Stack *, int);
void push(Stack *, int);
int pop(Stack *);
int findMin(Stack *);
void pushMillion(Stack *);
void popMillion(Stack *);

int main()
{
    // 스택 동적 할당 및 메모리 할당 여부 검사
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        return -1;
    }

    char command[20];

    initStack(s, MILLION + 100); // 100만 정도의 크기로 스택을 초기화

    // q 입력 시까지 명령을 반복
    while (scanf("%s", command) && strcmp(command, "q") != 0)
    {
        clock_t start, end;
        double cpu_time_used;
        int data;

        // 시간 측정 시작
        start = clock();

        // push 연산
        if (strcmp(command, "p") == 0)
        {
            scanf(" %d", &data); // 원소 입력
            push(s, data);       // 원소 push
            printf("push %d (%d), ", data, s->top + 1);
        }
        // pushMillion 연산
        else if (strcmp(command, "P") == 0)
        {
            getchar();
            pushMillion(s); // 100만개의 원소 push
            printf("pushMillion (%d), ", s->top + 1);
        }
        // pop 연산
        else if (strcmp(command, "o") == 0)
        {
            getchar();
            data = pop(s); // 원소 pop
            printf("pop %d (%d), ", data, s->top + 1);
        }
        // popMillion 연산
        else if (strcmp(command, "O") == 0)
        {
            getchar();
            popMillion(s); // 원소 100만개 pop
            printf("popMillion (%d), ", s->top + 1);
        }
        // findMin 연산
        else if (strcmp(command, "f") == 0)
        {
            getchar();
            data = findMin(s); // 스택의 원소 중 최소값 찾기
            printf("min %d (%d), ", data, s->top + 1);
        }
        end = clock();
        // 시간 측정 종료

        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000.0; // ms 단위로 변환
        printf("cputime = %f\n", cpu_time_used);                           // cputime 출력
    }

    // 메모리 해체
    free(s->elements);
    free(s->minValues);
    free(s);
    return 0;
}

// 스택 초기화 함수
void initStack(Stack *s, int capacity)
{
    // 원소 배열 동적 할당 및 메모리 할당 여부 검사
    s->elements = (int *)malloc(sizeof(int) * capacity);
    if (s->elements == NULL)
    {
        printf("Memory Allocation Failed!");
    }

    // 최소값 저장 배열 동적 할당 및 메모리 할당 여부 검사
    s->minValues = (int *)malloc(sizeof(int) * MIN_CAPACITY);
    if (s->minValues == NULL)
    {
        printf("Memory Allocation Failed!");
    }
    s->capacity = capacity;
    s->top = -1;
    s->minTop = -1;
}

// push 연산 함수
void push(Stack *s, int element)
{
    // 용량이 다 차지 않았을 경우
    if (s->top < s->capacity - 1)
    {
        s->elements[++s->top] = element; // 원소 추가 및 top 업데이트

        // 원소를 push할 때 s가 비어 있거나 minValues의 top보다 작거나 같은 경우
        if (s->minTop == -1 || element <= s->minValues[s->minTop])
        {
            s->minValues[++s->minTop] = element;
        }
    }
}

// pop 연산 함수
int pop(Stack *s)
{
    // 원소가 존재할 경우
    if (s->top >= 0)
    {
        int poppedElement = s->elements[s->top--]; // 최상단 원소 반환 및 top 업데이트
        if (poppedElement == s->minValues[s->minTop])
        {
            s->minTop--; // 최소값 스택의 top 업데이트
        }
        return poppedElement;
    }
    return -1;
}

// 최소값 찾기 함수
int findMin(Stack *s)
{
    if (s->minTop >= 0)
    {
        return s->minValues[s->minTop]; // minValues의 top 반환
    }
    return -1; // 스택이 비어있는 경우
}

// pushMillion 연산 함수
void pushMillion(Stack *s)
{
    // 100만번 push
    for (int i = 0; i < MILLION; i++)
    {
        push(s, rand() % 9000 + 1000); // 1000에서 9999 사이의 난수 생성
    }
}

// popMillion 연산 함수
void popMillion(Stack *s)
{
    // 100만번 pop
    for (int i = 0; i < MILLION; i++)
    {
        // 스택이 공백 상태일 경우 반복 종료
        if (s->top == -1)
        {
            break;
        }
        pop(s);
    }
}

/*

p 119
P
f
p 33
p 119
f
p 33
o
f
o
O
f
q

*/