#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 스택 구조체
typedef struct Stack
{
    int capacity;
    int top;
    char *items;
} Stack;

// 함수 원형
void push(Stack *s, char elem);
char pop(Stack *s);
void peek(Stack *s);
void duplicate(Stack *s);
void upRotate(Stack *s, int n);
void downRotate(Stack *s, int n);
void print(Stack *s);

int main()
{
    // 스택의 크기 입력
    int stack_size;
    scanf("%d", &stack_size);

    // 연산의 개수 입력
    int operation_time;
    scanf("%d", &operation_time);

    // 스택 구조체 메모리 할당 및 메모리 할당 여부 검사
    Stack *stack_ADT = (Stack *)malloc(sizeof(Stack));
    if (stack_ADT == NULL)
    {
        return -1;
    }

    stack_ADT->capacity = stack_size;                             // 스택의 용량
    stack_ADT->top = -1;                                          // 스택 마지막 원소 idx
    stack_ADT->items = (char *)malloc(sizeof(char) * stack_size); // 스택 원소 배열 메모리 할당
    // 메모리 할당 여부 검사
    if (stack_ADT->items == NULL)
    {
        return -1;
    }

    int cnt = 0;
    int n;
    char command[10], elem;

    // 연산의 개수 만큼 반복
    while (cnt < operation_time)
    {
        scanf("%s", command); // 연산의 종류 입력

        // pop 연산
        if (strcmp(command, "POP") == 0)
        {
            getchar();
            pop(stack_ADT);
        }
        // push 연산
        else if (strcmp(command, "PUSH") == 0)
        {
            scanf(" %c", &elem); // 추가할 원소 입력
            getchar();
            push(stack_ADT, elem);
        }
        // peek 연산
        else if (strcmp(command, "PEEK") == 0)
        {
            peek(stack_ADT);
        }
        // duplicate 연산
        else if (strcmp(command, "DUP") == 0)
        {
            duplicate(stack_ADT);
        }
        // upRotate 연산
        else if (strcmp(command, "UpR") == 0)
        {
            scanf(" %d", &n); // 회전시킬 원소의 개수 입력
            getchar();
            upRotate(stack_ADT, n);
        }
        // downRotate 연산
        else if (strcmp(command, "DownR") == 0)
        {
            scanf(" %d", &n); // 회전시킬 원소의 개수 입력
            getchar();
            downRotate(stack_ADT, n);
        }
        // print 연산
        else if (strcmp(command, "PRINT") == 0)
        {
            getchar();
            print(stack_ADT);
            printf("\n");
        }
        cnt++;
    }

    // 메모리 해제
    free(stack_ADT->items);
    free(stack_ADT);
    return 0;
}

// push 함수
void push(Stack *s, char elem)
{
    // 스택의 용량이 가득 찬 경우
    if (s->top == s->capacity - 1)
    {
        printf("Stack FULL\n");
    }
    // 스택 용량이 가득 차지 않은 경우
    else
    {
        s->top += 1;
        s->items[s->top] = elem;
    }
}

// pop 함수
char pop(Stack *s)
{
    // 스택이 비어 있을 경우
    if (s->top == -1)
    {
        printf("Stack Empty\n");
        return -1;
    }
    // 스택이 비어 있지 않은 경우
    else
    {
        s->top -= 1;
        return s->items[s->top + 1];
    }
}

// peek 함수
void peek(Stack *s)
{
    // 스택이 비어 있을 경우
    if (s->top == -1)
    {
        printf("Stack Empty\n");
        return;
    }
    // 스택이 비어 있지 않은 경우
    else
    {
        printf("%c\n", s->items[s->top]);
    }
}

// duplicate 함수
void duplicate(Stack *s)
{
    // 스택의 용량이 가득 찬 경우
    if (s->top == s->capacity - 1)
    {
        printf("Stack FULL\n");
        return;
    }
    // 스택의 용량이 가득 차지 않은 경우
    else
    {
        char tmp = s->items[s->top];
        // pop 1회, push 2회
        pop(s);
        push(s, tmp);
        push(s, tmp);
    }
}

// upRotate 함수
void upRotate(Stack *s, int n)
{
    // 현재 원소의 개수보다 큰 입력이 들어온 경우
    if (n > s->top + 1)
    {
        return;
    }

    char tmp;
    int cnt = n;
    // n-1번 반복
    while (cnt > 1)
    {
        // 원소 교환
        for (int i = s->top - n + 1; i < s->top; i++)
        {
            tmp = s->items[i];
            s->items[i] = s->items[i + 1];
            s->items[i + 1] = tmp;
        }
        cnt--;
    }
}

// downRotate 함수
void downRotate(Stack *s, int n)
{
    // 현재 원소의 개수보다 큰 입력이 들어온 경우
    if (n > s->top + 1)
    {
        return;
    }

    char tmp;
    int cnt = n;
    // n-1번 반복
    while (cnt > 1)
    {
        // 원소 교환
        for (int i = s->top; i > s->top - n + 1; i--)
        {
            tmp = s->items[i];
            s->items[i] = s->items[i - 1];
            s->items[i - 1] = tmp;
        }
        cnt--;
    }
}

// print 함수
void print(Stack *s)
{
    // 모든 원소 출력
    for (int i = s->top; i >= 0; i--)
    {
        printf("%c", s->items[i]);
    }
}

/*

4
10
POP
PUSH s
PUSH t
PUSH a
PUSH r
PRINT
UpR 3
PRINT
PUSH s
PEEK

*/