#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

// 스택 구조체
typedef struct Stack
{
    int top;
    char *items;
} Stack;

// 함수 원형
void push(Stack *s, char elem);
char pop(Stack *s);
int isBalanced(Stack *s);

int main()
{
    // 스택 구조체 메모리 할당 및 메모리 할당 여부 검사
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        return -1;
    }

    s->top = -1;                                    // 스택 원소의 마지막 idx
    s->items = (char *)malloc(sizeof(char) * 1000); // 스택 원소 배열 메모리 할당
    // 메모리 할당 여부 검사
    if (s->items == NULL)
    {
        return -1;
    }

    gets(s->items); // 수식 문장 입력

    int cnt = 0;
    int len = strlen(s->items);
    // 문장에서 괄호의 개수 찾기
    for (int i = 0; i < len; i++)
    {
        if ((s->items[i] == '(') || (s->items[i] == ')') || (s->items[i] == '{') || (s->items[i] == '}') || (s->items[i] == '[') || (s->items[i] == ']'))
        {
            cnt++;
        }
    }

    int result = isBalanced(s); // 괄호 쌍의 대칭성 검사
    // 대칭일 경우
    if (result == 1)
    {
        printf("OK_%d", cnt);
    }
    // 비대칭일 경우
    else if (result == 0)
    {
        printf("Wrong_%d", cnt);
    }

    return 0;
}

// push 함수
void push(Stack *s, char elem)
{
    s->top += 1;
    s->items[s->top] = elem;
}

// pop 함수
char pop(Stack *s)
{
    s->top -= 1;
    return s->items[s->top + 1];
}

// 괄호 쌍의 대칭성 검사 함수
int isBalanced(Stack *s)
{
    int len = strlen(s->items);
    // 수식을 전부 검사
    for (int i = 0; i < len; i++)
    {
        char symbol = s->items[i];

        // 현재 원소가 여는 괄호일 경우
        if (symbol == '(' || symbol == '{' || symbol == '[')
        {
            push(s, symbol);
        }
        // 현재 원소가 닫는 괄호일 경우
        else if (symbol == ')' || symbol == '}' || symbol == ']')
        {
            // 마지막 원소였을 경우 비대칭
            if (s->top == -1)
            {
                return 0; // 비대칭
            }
            char tmp = pop(s);
            // pop한 원소가 현재 원소와 대칭이 아닐 경우
            if ((tmp == '(' && symbol != ')') || (tmp == '{' && symbol != '}') || (tmp == '[' && symbol != ']'))
            {
                return 0; // 비대칭
            }
        }
    }
    // 스택이 비어 있다면
    if (s->top == -1)
        return 1; // 대칭

    // 스택이 비어 있지 않다면
    else
        return 0; // 비대칭
}

/*

(3+40*(2+(30-7)*2133)

3*{4+(2-792)/1} + [3*{4-2* (100 -7)}]

301*{4+(2101-7)/1} + 9*{4-2* (10108-7)}}

(3*{4001+(2-7)/1} + [3*{4-2* (1-7)}])

*/