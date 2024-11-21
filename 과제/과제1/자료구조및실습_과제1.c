#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// 문제 1-1

int countOnesButSlow(int **, int); // 함수 원형
int countOnes(int **, int);        // 함수 원형

int main()
{
    int N;
    scanf("%d", &N); // 정수 N 입력

    int **ar;
    ar = (int **)malloc(sizeof(int *) * N); // 2차원 배열 ar 동적할당
    // 메모리 할당 여부 확인
    if (ar == NULL)
    {
        return -1;
    }
    // 각 행마다 동적 할당
    for (int i = 0; i < N; i++)
    {
        ar[i] = (int *)malloc(sizeof(int) * N);
    }
    // 메모리 할당 여부 확인
    for (int i = 0; i < N; i++)
    {
        if (ar[i] == NULL)
        {
            return -1;
        }
    }

    // N x N 배열 A 입력
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            scanf("%d", &ar[i][j]);
        }
    }

    // 느린 버전, 빠른 버전 출력
    printf("%d\n", countOnesButSlow(ar, N));
    printf("%d", countOnes(ar, N));

    // 메모리 할당 해제
    for (int i = 0; i < N; i++)
    {
        free(ar[i]);
    }
    free(ar);
    return 0;
}

int countOnesButSlow(int **ar, int n)
{
    int count = 0;
    // 현재 행에서
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        // 원소가 1인 경우
        while ((j < n) && (ar[i][j] == 1))
        {
            count++; // count 업데이트
            j++;     // 다음 열로 이동
        }
    }
    return count; // 1의 총 개수 반환
}

int countOnes(int **ar, int N)
{
    int count = 0;
    int row = 0;
    int col = N - 1; // 행의 끝에서부터 시작

    while (row < N && col >= 0)
    {
        // 현재 원소가 1일 경우
        if (ar[row][col] == 1)
        {
            count += (col + 1); // 이전 원소가 모두 1
            row++;              // 다음 행으로 이동
        }
        else
        {
            col--; // 이전 열로 이동
        }
    }

    return count; // 1의 총 개수 반환
}

/*
8
1 1 1 1 1 1 1 1
1 1 1 1 1 1 0 0
1 1 1 1 1 1 0 0
1 1 1 1 1 0 0 0
1 1 1 1 1 0 0 0
1 1 1 1 1 0 0 0
1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0
*/

// 문제 1-2

int countOnesButSlow(int **, int); // 함수 원형
int countOnes(int **, int);        // 함수 원형
int BitArray(int **, int);         // 함수 원형

int main()
{
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;
    int n_values[3] = {3000, 1000, 2000}; // 세 가지 n값

    srand(time(NULL)); // seed 초기화

    int **ar;
    ar = (int **)malloc(sizeof(int *) * n_values[0]); // 2차원 배열 ar 동적 할당
    // 메모리 할당 여부 검사
    if (ar == NULL)
    {
        return -1;
    }
    // 각 행마다 동적 할당
    for (int i = 0; i < n_values[0]; i++)
    {
        ar[i] = (int *)malloc(sizeof(int) * n_values[0]);
    }
    // 메모리 할당 여부 확인
    for (int i = 0; i < n_values[0]; i++)
    {
        if (ar[i] == NULL)
        {
            return -1;
        }
    }

    // 빠른 버전
    printf("빠른 버전을 출력합니다\n");
    for (int i = 0; i < 3; i++)
    {
        // 비트 행렬 생성
        int kTotal = BitArray(ar, n_values[i]);
        // 시간 측정 시작
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int ones = countOnes(ar, n_values[i]); // 프로그램이 계산한 1의 총 수
        QueryPerformanceCounter(&end);
        // 시간 측정 종료

        diff.QuadPart = end.QuadPart - start.QuadPart; // CPU Time
        printf("%d %d %.12fsec\n\n", kTotal, ones, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
    }

    // 느린 버전
    printf("느린 버전을 출력합니다\n");
    for (int i = 0; i < 3; i++)
    {
        // 비트 행렬 생성
        int kTotal = BitArray(ar, n_values[i]);
        // 시간 측정 시작
        QueryPerformanceFrequency(&ticksPerSec);
        QueryPerformanceCounter(&start);
        int ones = countOnesButSlow(ar, n_values[i]); // 프로그램이 계산한 1의 총 수
        QueryPerformanceCounter(&end);
        // 시간 측정 종료

        diff.QuadPart = end.QuadPart - start.QuadPart; // CPU Time
        printf("%d %d %.12fsec\n\n", kTotal, ones, ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));
    }

    // 메모리 해제
    for (int j = 0; j < n_values[0]; j++)
    {
        free(ar[j]);
    }
    free(ar);

    return 0;
}

//  비트 행렬 생성
int BitArray(int **ar, int n_values)
{
    int *one_count = (int *)malloc(sizeof(int) * n_values); // 각 행의 1의 갯수를 담을 배열
    // 메모리 할당 여부 검사
    if (one_count == NULL)
    {
        return -1;
    }

    one_count[0] = rand() % (n_values / 10 + 1) + (n_values * 9 / 10); // 첫 행은 0.9n 이상 n 이하
    // 1행부터는 직전 행의 1의 갯수의 0.9배 이상 1배 이하
    for (int i = 1; i < n_values; i++)
    {

        one_count[i] = rand() % (one_count[i - 1] / 10 + 1) + (one_count[i - 1] * 9 / 10);
    }

    // 모든 비트 0으로 초기화
    for (int i = 0; i < n_values; i++)
    {
        for (int j = 0; j < n_values; j++)
        {
            ar[i][j] = 0;
        }
    }

    int kTotal = 0;
    // 각 행을 해당 행의 1의 개수만큼으로 채우기
    for (int i = 0; i < n_values; i++)
    {
        for (int j = 0; j < one_count[i]; j++)
        {
            ar[i][j] = 1;
            kTotal++; // 실제 1의 총 수
        }
    }

    // 메모리 해제
    free(one_count);
    return kTotal; // 실제 1의 총 수 반환
}

int countOnesButSlow(int **ar, int n)
{
    int count = 0;
    // 현재 행에서
    for (int i = 0; i < n; i++)
    {
        int j = 0;
        // 원소가 1인 경우
        while ((j < n) && (ar[i][j] == 1))
        {
            count++; // count 업데이트
            j++;     // 다음 열로 이동
        }
    }
    return count; // 1의 총 개수 반환
}

int countOnes(int **ar, int N)
{
    int count = 0;
    int row = 0;
    int col = N - 1; // 행의 끝에서부터 시작

    while (row < N && col >= 0)
    {
        // 현재 원소가 1일 경우
        if (ar[row][col] == 1)
        {
            count += (col + 1); // 이전 원소가 모두 1
            row++;              // 다음 행으로 이동
        }
        else
        {
            col--; // 이전 열로 이동
        }
    }

    return count; // 1의 총 개수 반환
}