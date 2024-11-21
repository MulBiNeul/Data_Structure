#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 문제 1

// int sum(int); // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N); // 양의 정수 N 입력

//     printf("%d", sum(N)); // 1부터 N까지의 합 출력
//     return 0;
// }

// int sum(int n)
// {
//     // n이 1일 경우
//     if (n == 1)
//     {
//         return 1;
//     }
//     return sum(n - 1) + n; // N에 N-1을 더한 값...
// }

// 문제 2

// void print(int);    // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N);    // 양의 정수 N 입력
//     print(N);   // print 함수 호출
//     return 0;
// }

// void print(int N)
// {
//     // N이 0보다 크다면
//     if (N > 0)
//     {
//         print(N / 10);  // N / 10을 통해 높은 자릿수부터 출력
//         printf("%d\n", N % 10); // 현재 수의 단자릿수 출력
//     }
// }

// 문제 3

// void print(int); // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N); // 양의 정수 N 입력
//     print(N);        // print 함수 호출
//     return 0;
// }

// void print(int N)
// {
//     // N이 0보다 크다면
//     if (N > 0)
//     {
//         printf("%d\n", N % 10); // 현재 수의 단자릿수 출력
//         print(N / 10);          // N / 10을 통해 낮은 자릿수부터 출력
//     }
// }

// 문제 4

// int FindMAX(int *, int); // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N); // 정수 N 입력

//     int ar[20];
//     // N만큼 정수 입력
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar[i]);
//     }

//     printf("%d", FindMAX(ar, N)); // 최대값 출력
//     return 0;
// }

// int FindMAX(int *ar, int N)
// {
//     // N이 1일 경우는 예외 처리
//     if (N == 1)
//     {
//         return ar[N - 1]; // ar[0] 반환
//     }

//     //  마지막 수가 나머지 수 중의 최대값보다 큰 경우
//     if (FindMAX(ar, N - 1) < ar[N - 1])
//     {
//         return ar[N - 1]; // 마지막 수 반환
//     }
//     // 아니라면
//     else
//     {
//         return FindMAX(ar, N - 1); // 나머지 수 중의 최대값 반환
//     }
// }

// 문제 5

// void towers_of_Hanoi(int, char, char, char); // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N); // 원반의 개수 입력

//     towers_of_Hanoi(N, 'A', 'B', 'C'); // 하노이 탑 문제 실행

//     return 0;
// }

// void towers_of_Hanoi(int n, char from, char aux, char to)
// {
//     // 시행이 마지막인 경우
//     if (n == 1)
//     {
//         printf("%c %c\n", from, to); // 출발 말뚝과 목표 말뚝 출력
//         return;
//     }
//     towers_of_Hanoi(n - 1, from, to, aux);
//     printf("%c %c\n", from, to); // 출발 말뚝과 목표 말뚝 출력
//     towers_of_Hanoi(n - 1, aux, from, to);
// }

// 문제 6

// int FindGCD(int, int); // 함수 원형

// int main()
// {
//     int a, b;
//     scanf("%d %d", &a, &b); // 두 양의 정수 입력

//     printf("%d", FindGCD(a, b)); // a와 b의 최대공약수 출력
//     return 0;
// }

// int FindGCD(int a, int b)
// {
//     if (b == 0) // 한 수가 0이 되었을 때
//     {
//         return a; // 다른 수가 최대공약수
//     }
//     return FindGCD(b, a % b); // 유클리드 호제법 반복
// }

// 문제 7

int COUNTCHAR(char *, char); // 함수 원형

int main()
{
    char ch[101];
    scanf("%s", ch); // 최대 길이가 100인 문자열 입력
    getchar();       // 공백 제거

    char find_ch;
    scanf("%c", &find_ch); // 검사할 문자 입력

    printf("%d", COUNTCHAR(ch, find_ch)); // 검사 결과 출력
    return 0;
}

int COUNTCHAR(char *ch, char find_ch)
{
    // 문자열의 끝일 경우
    if (*ch == '\0')
    {
        return 0; // 함수 종료
    }
    // 현재 문자가 검사 문자와 동일할 경우
    if (*ch == find_ch)
    {
        return COUNTCHAR(ch + 1, find_ch) + 1; // 다음 문자로 넘어가고 cnt
    }
    // 현재 문자가 검사 문자와 다를 경우
    else
    {
        return COUNTCHAR(ch + 1, find_ch); // 다음 문자로 이동
    }
}