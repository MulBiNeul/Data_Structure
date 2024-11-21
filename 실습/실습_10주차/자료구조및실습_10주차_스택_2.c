#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 구조체
typedef struct Stack
{
    int top;
    char *items;
} Stack;

// 함수 원형
void push(Stack *s, char elem);
char pop(Stack *s);
void calculate(Stack *s, char mathematical_expression[]);

int main()
{
    int exp_num;
    char mathematical_expression[100];

    scanf("%d", &exp_num); // 수식의 개수 입력

    // 스택 동적 할당 및 메모리 할당 여부 검사
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        return -1;
    }
    // 스택 초기화 및 동적 배열 할당 및 메모리 할당 여부 검사
    s->top = -1;
    s->items = (char *)malloc(sizeof(char) * 100);
    if (s->items == NULL)
    {
        return -1;
    }

    // 수식 입력 및 평가
    for (int i = 0; i < exp_num; i++)
    {
        scanf("%s", mathematical_expression);
        getchar();
        calculate(s, mathematical_expression);
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

// 수식 평가 함수
void calculate(Stack *s, char mathematical_expression[])
{
    int result = 0;
    char ch1, ch2;
    int len = strlen(mathematical_expression);

    // 길이만큼 반복
    for (int i = 0; i < len; i++)
    {
        char symbol = mathematical_expression[i];

        // 현재 문자가 숫자일 경우 int형으로 변환하여 push
        if (symbol >= '0' && symbol <= '9')
        {
            push(s, symbol - '0');
        }
        else
        {
            // 스택에 원소가 1개 이상 있는 경우
            if (s->top >= 1)
            {
                // 덧셈 연산
                if (symbol == '+')
                {
                    ch2 = pop(s);
                    ch1 = pop(s);
                    result = ch1 + ch2;
                }
                // 뺄셈 연산
                else if (symbol == '-')
                {
                    ch2 = pop(s);
                    ch1 = pop(s);
                    result = ch1 - ch2;
                }
                // 곱셈 연산
                else if (symbol == '*')
                {
                    ch2 = pop(s);
                    ch1 = pop(s);
                    result = ch1 * ch2;
                }
                // 나눗셈 연산
                else if (symbol == '/')
                {
                    ch2 = pop(s);
                    ch1 = pop(s);
                    result = ch1 / ch2;
                }
                push(s, result); // 결과값을 push
            }
            // 스택에 원소가 1개 뿐일 경우
            else
            {
                // 덧셈 연산
                if (symbol == '+')
                {
                    result = result + pop(s);
                }
                // 뺄셈 연산
                else if (symbol == '-')
                {
                    result = result - pop(s);
                }
                // 곱셈 연산
                else if (symbol == '*')
                {
                    result = result * pop(s);
                }
                // 나눗셈 연산
                else if (symbol == '/')
                {
                    result = result / pop(s);
                }
            }
        }
    }
    printf("%d\n", result); // 평가 결과 출력
}

/*

4
53*2+63+2*+
234*+
72/3-42*+21*-
923*1+2*+

*/