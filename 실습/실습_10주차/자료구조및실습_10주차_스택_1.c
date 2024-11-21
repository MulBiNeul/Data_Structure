#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 구조체
typedef struct Stack
{
    int capacity;
    int top;
    char *items;
} Stack;

// 함수 원형
void push(Stack *, char);
char pop(Stack *);
int prec(char);
void convert(Stack *, char[]);

int main()
{
    int mathematical_expression_num;
    char mathematical_expression[101];

    scanf("%d", &mathematical_expression_num); // 수식의 길이 입력

    // 스택 동적 할당 및 메모리 할당 여부 검사
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if (s == NULL)
    {
        return -1;
    }
    // 스택 초기화 및 동적 배열 할당 및 메모리 할당 여부 검사
    s->top = -1;
    s->items = (char *)malloc(sizeof(char) * 101);
    if (s->items == NULL)
    {
        return -1;
    }

    // 수식의 개수만큼 입력 받고 후위수식으로 변환
    for (int i = 0; i < mathematical_expression_num; i++)
    {
        scanf("%s", mathematical_expression);
        convert(s, mathematical_expression);
        printf("\n");
    }

    // 메모리 해제
    free(s->items);
    free(s);
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

// 연산자 우선수위 판별 함수
int prec(char mathematical_expression)
{
    switch (mathematical_expression)
    {
    // 소괄호 우선순위
    case '(':
    case ')':
        return 0;
    case '|': // OR 우선순위
        return 1;
    case '&': // AND 우선순위
        return 2;
    // 관계연산자 우선순위
    case '<':
    case '>':
        return 3;
    // 덧셈, 뺄셈 우선순위
    case '+':
    case '-':
        return 4;
    // 곱셉, 나눗셈 우선순위
    case '*':
    case '/':
        return 5;
    // 단항연산자 우선순위
    case '!':
    case 'p':
    case 'm':
        return 6;
    }
    return -1;
}

// 후위수식 변환 함수
void convert(Stack *s, char mathematical_expression[])
{
    int len = strlen(mathematical_expression);

    // 현재 수식이 종료될까지 반복
    for (int i = 0; i < len; i++)
    {
        // 현재 기호와 이전 기호 저장
        char symbol = mathematical_expression[i];
        char symbol_prev = mathematical_expression[i - 1];

        // 덧셈, 뺄셈일 경우와 단항 연산자일 경우를 구분
        if (symbol == '+' || symbol == '-')
        {
            // 수식의 시작일 경우 +, -는 단항연산자
            if (i == 0)
            {
                if (symbol == '+')
                    symbol = 'p';
                else if (symbol == '-')
                    symbol = 'm';
            }
            // 이전 문자가 닫는 소괄호, 영문자가 아닐 경우 +,-는 단항연산자
            else if (symbol_prev != ')' && !(symbol_prev >= 'A' && symbol_prev <= 'Z'))
            {
                if (symbol == '+')
                    symbol = 'p';
                else if (symbol == '-')
                    symbol = 'm';
            }
        }

        // 현재 기호가 영문자이면 출력
        if (symbol >= 'A' && symbol <= 'Z')
        {
            printf("%c", symbol);
        }
        // 현재 기호가 여는 소괄호일 경우 push
        else if (symbol == '(')
        {
            push(s, symbol);
        }
        // 현재 기호가 닫는 소괄호일 경우
        else if (symbol == ')')
        {
            // 여는 소괄호가 등장할 때까지 모든 원소를 pop
            while (s->items[s->top] != '(')
            {
                printf("%c", pop(s));
            }
            pop(s); // 여는 소괄호를 pop하여 제거
        }
        // 나머지 연산자들의 경우
        else
        {
            // 현재 기호보다 스택의 마지막 원소의 우선순위가 높을 때
            while (s->top != -1 && (prec(symbol) <= prec(s->items[s->top])))
            {
                char tmp = pop(s);
                // pop한 원소가 단항연산자일 경우
                if (tmp == 'p')
                    tmp = '+';
                else if (tmp == 'm')
                    tmp = '-';
                printf("%c", tmp);
            }
            // 논리연산자일 경우 동일 원소를 한 개 더 넣어줍니다
            if (symbol == '&' || symbol == '|')
            {
                push(s, symbol);
                i++;
            }

            push(s, symbol); // 스택에 저장
        }
    }

    // 남아 있는 모든 원소 pop
    while (s->top != -1)
    {
        printf("%c", pop(s));
    }
}

/*

5
A*B+C+(D+E)*F
A+B*C
A/B-C+D*E-F*G
A+(B*C+D)*E
A&&B||C||!(E>F)

*/