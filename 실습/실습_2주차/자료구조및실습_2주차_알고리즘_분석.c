#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// 문제 1

// int modulo(int, int); // 함수 원형

// int main()
// {
//     int a, b;
//     scanf("%d %d", &a, &b); // a, b 입력

//     printf("%d", modulo(a, b)); // 나머지 출력
//     return 0;
// }

// int modulo(int a, int b)
// {
//     // a가 b보다 같거나 큰 경우에만 뺄셈을 통한 나머지 연산
//     while (a >= b)
//     {
//         a -= b;
//     }

//     return a; // 나머지 반환
// }

// 문제 2

// int mostOnes(int **, int); // 함수 원형 선언

// int main()
// {
//     int N;
//     scanf("%d", &N); // 정수 n 입략

//     int **ar; // 2차원 배열을 위한 이중 포인터

//     // 동적 메모리 할당 및 메모리 할당 여부 검사
//     ar = (int **)malloc(sizeof(int *) * N);
//     if (ar == NULL)
//     {
//         return -1;
//     }
//     // 동적 메모리 할당 및 메모리 할당 여부 검사
//     for (int i = 0; i < N; i++)
//     {
//         ar[i] = (int *)malloc(sizeof(int) * N);
//         if (ar[i] == NULL)
//         {
//             return -1;
//         }
//     }

//     // n x n 행렬 입력
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             scanf("%d", &ar[i][j]);
//         }
//     }

//     printf("%d", mostOnes(ar, N)); // 1이 가장 많은 행 번호 출력

//     // 동적 메모리 해제
//     for (int i = 0; i < N; i++)
//     {
//         free(ar[i]);
//     }
//     free(ar);
//     return 0;
// }

// int mostOnes(int **ar, int n)
// {
//     int pos = 0;
//     int row = 0, col = 0;

//     // 행렬의 종착점에 도착할 때까지
//     while (row < n && col < n)
//     {
//         // 현재 원소가 1일 경우
//         if (ar[row][col] == 1)
//         {
//             col++;     // 다음 원소로 넘어갑니다
//             pos = row; // 현재 1이 가장 많은 행 번호 업데이트
//         }
//         // 현재 원소가 0일 경우
//         else
//         {
//             row++; // 다음 열로 이동
//         }
//     }
//     return pos; // 1이 가장 많은 행 번호 반환
// }

// 문제 3

// int *prefixAverages1(int *, int);   // 함수 원형
// int *prefixAverages2(int *, int);   // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N);    // 배열 X의 크기 입력

//     int *ar;
//     ar = (int *)malloc(sizeof(int) * N);    // ar배열 동적 할당
//     // 메모리 할당 여부 검사
//     if (ar == NULL)
//     {
//         printf("Not enough memory");
//     }

//     // 배열 X 입력
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar[i]);
//     }

//     int *X;
//     X = prefixAverages1(ar, N);
//     // prefixAverages1 출력
//     for (int i = 0; i < N; i++)
//     {
//         printf("%d ", X[i]);
//     }
//     printf("\n");
//     X = prefixAverages2(ar, N);
//     // prefixAverages2 출력
//     for (int i = 0; i < N; i++)
//     {
//         printf("%d ", X[i]);
//     }

//     // 메모리 해제
//     free(ar);
//     free(X);
//     return 0;
// }

// int *prefixAverages1(int *ar, int N)
// {
//     int *A;
//     A = (int *)malloc(sizeof(int) * N); // 배열 A 동적 할당
//     // 메모리 할당 여부 검사
//     if (A == NULL)
//     {
//         printf("Not enough memory");
//     }

//     for (int i = 0; i < N; i++)
//     {
//         double sum = 0;
//         // 현재 원소까지의 합 구하기
//         for (int j = 0; j <= i; j++)
//         {
//             sum += ar[j];
//         }
//         A[i] = (int)(sum / (i + 1) + 0.5); // 현재까지의 누적 평균
//     }
//     return A;
// }

// int *prefixAverages2(int *ar, int N)
// {
//     int *A;
//     A = (int *)malloc(sizeof(int) * N); // 배열 A 동적 할당
//     // 메모리 할당 여부 검사
//     if (A == NULL)
//     {
//         printf("Not enough memory");
//     }

//     double sum = 0;
//     for (int i = 0; i < N; i++)
//     {
//         sum += ar[i];   // 현재 원소까지의 합
//         A[i] = (int)(sum / (i + 1) + 0.5);  // 현재까지의 누적 평균
//     }
//     return A;
// }

// 문제 3-2

int *prefixAverages1(int *, int); // 함수 원형
int *prefixAverages2(int *, int); // 함수 원형

int main()
{
    int N;
    scanf("%d", &N); // 배열 X의 크기 입력

    int *ar;
    ar = (int *)malloc(sizeof(int) * N); // ar배열 동적 할당
    // 메모리 할당 여부 검사
    if (ar == NULL)
    {
        printf("Not enough memory");
    }
    for (int i = 0; i < N; i++)
    {
        ar[i] = rand() % 10001;
    }

    int *X;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    X = prefixAverages1(ar, N);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

    QueryPerformanceFrequency(&ticksPerSec);
    QueryPerformanceCounter(&start);
    X = prefixAverages2(ar, N);
    QueryPerformanceCounter(&end);

    diff.QuadPart = end.QuadPart - start.QuadPart;
    printf("time: %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

    // 메모리 해제
    free(ar);
    free(X);
    return 0;
}

int *prefixAverages1(int *ar, int N)
{
    int *A;
    A = (int *)malloc(sizeof(int) * N); // 배열 A 동적 할당
    // 메모리 할당 여부 검사
    if (A == NULL)
    {
        printf("Not enough memory");
    }

    for (int i = 0; i < N; i++)
    {
        double sum = 0;
        // 현재 원소까지의 합 구하기
        for (int j = 0; j <= i; j++)
        {
            sum += ar[j];
        }
        A[i] = (int)(sum / (i + 1) + 0.5); // 현재까지의 누적 평균
    }
    return A;
}

int *prefixAverages2(int *ar, int N)
{
    int *A;
    A = (int *)malloc(sizeof(int) * N); // 배열 A 동적 할당
    // 메모리 할당 여부 검사
    if (A == NULL)
    {
        printf("Not enough memory");
    }

    double sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += ar[i];                      // 현재 원소까지의 합
        A[i] = (int)(sum / (i + 1) + 0.5); // 현재까지의 누적 평균
    }
    return A;
}