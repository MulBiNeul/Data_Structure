#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// 문제 1

// int main()
// {
//     int N;
//     scanf("%d", &N); // 수열의 길이 N 입력

//     int ar[100];
//     // 수열 X 입력
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar[i]);
//     }

//     int info;
//     scanf("%d", &info); // 뒤집기 정보의 개수 입력

//     int *info_ar;
//     info_ar = (int *)malloc(sizeof(int) * (info * 2)); // 뒤집기 정보 배열 동적 할당
//     // 메모리 할당 여부 검사
//     if (info_ar == NULL)
//     {
//         return -1;
//     }
//     // 뒤집기 구간 정보 입력
//     for (int i = 0; i < 2 * info; i++)
//     {
//         scanf("%d", &info_ar[i]);
//     }

//     int pos = 0;
//     // 뒤집기 정보 개수만큼 반복
//     for (int i = 0; i < info; i++)
//     {
//         int start_idx = info_ar[pos];
//         int end_idx = info_ar[pos + 1];
//         // 해당 뒤집기 정보 구간의 중앙에 도달할 때까지 반복
//         while (start_idx < (double)(start_idx + end_idx) / 2)
//         {
//             // 원소 교환
//             int tmp = ar[start_idx];
//             ar[start_idx] = ar[end_idx];
//             ar[end_idx] = tmp;
//             // start_idx, end_idx 위치 업데이트
//             start_idx++;
//             end_idx--;
//         }
//         pos += 2; // 다음 뒤집기 구간으로 이동
//     }

//     // 최종 수열 출력
//     for (int i = 0; i < N; i++)
//     {
//         printf(" %d", ar[i]);
//     }

//     // 메모리 해제
//     free(info_ar);
//     return 0;
// }

// 문제 2

// int main()
// {
//     int N;
//     scanf("%d", &N); // 수열의 길이 입력

//     int *ar;
//     ar = (int *)malloc(sizeof(int) * N); // 수열 ar 동적 할당
//     // 메모리 할당 여부 검사
//     if (ar == NULL)
//     {
//         return -1;
//     }
//     // 수열 ar 입력
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar[i]);
//     }

//     int change_len;
//     scanf("%d", &change_len); // 순서 바꿈 정보의 길이 입력

//     int *change_info;
//     change_info = (int *)malloc(sizeof(int) * change_len); // 순서 바꿈 정보 배열 동적 할당
//     // 메모리 할당 여부 검사
//     if (change_info == NULL)
//     {
//         return -1;
//     }

//     // 순서 바꿈 정보 배열 입력
//     for (int i = 0; i < change_len; i++)
//     {
//         scanf("%d", &change_info[i]);
//     }

//     int tmp;
//     // 순서 바꾸기 시작
//     // 처음과 마지막 위치는 항상 동일하기에 반복 횟수는 change_len - 2
//     for (int i = 0; i < change_len - 2; i++)
//     { // 순서 바꾸기 첫 숫자에 임시값을 넣어 위치를 변경
//         tmp = ar[change_info[0]];
//         ar[change_info[0]] = ar[change_info[i + 1]];
//         ar[change_info[i + 1]] = tmp;
//     }
//     // 변환 수열 출력
//     for (int i = 0; i < N; i++)
//     {
//         printf(" %d", ar[i]);
//     }
//     // 동적 메모리 해제
//     free(ar);
//     free(change_info);
//     return 0;
// }

// 문제 3

// int main()
// {
//     int N;
//     scanf("%d", &N); // 행렬 크기 N 입력

//     int **ar;
//     // N X N 행렬 동적 할당 및 메모리 할당 여부 확인
//     ar = (int **)malloc(sizeof(int *) * N);
//     if (ar == NULL)
//     {
//         return -1;
//     }

//     for (int i = 0; i < N; i++)
//     {
//         ar[i] = (int *)malloc(sizeof(int) * N);
//         if (ar[i] == NULL)
//         {
//             return -1;
//         }
//     }

//     int num = 1;
//     int row = 0, col = 0;
//     int line = 0;
//     // 행의 개수만큼 반복
//     while (line < N)
//     {
//         // 짝수 행일 경우
//         if (line % 2 == 0)
//         {
//             // 첫 열일 경우
//             if (col == 0)
//             { // 시작하는 수는 다음과 같습니다
//                 num = N * (line + 1) - N + 1;
//             }
//             // 다음 열로 이동
//             ar[row][col] = num++;
//             col++;
//             // 열의 끝에 도달하면
//             if (col == N)
//             { // 다음 행으로 이동, 열 초기화
//                 col = 0;
//                 row++;
//                 line++;
//             }
//         }
//         // 홀수 행일 경우
//         else
//         { // 첫 열일 경우
//             if (col == 0)
//             { // 시작하는 수는 다음과 같습니다
//                 num = N * (line + 1);
//             }
//             // 다음 열로 이동
//             ar[row][col] = num--;
//             col++;
//             // 열의 끝에 도달하면
//             if (col == N)
//             { // 다음 행으로 이동, 열 초기화
//                 col = 0;
//                 row++;
//                 line++;
//             }
//         }
//     }

//     // 완성된 행렬 출력
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             printf(" %d", ar[i][j]);
//         }
//         printf("\n");
//     }

//     // 메모리 해제
//     for (int i = 0; i < N; i++)
//     {
//         free(ar[i]);
//     }
//     free(ar);
//     return 0;
// }

// 문제 4

int main()
{
    int N, M;
    scanf("%d %d", &N, &M); // 정수 N, M 입력

    int ar[100][100];
    // 배열 초기화
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            ar[i][j] = 0;
        }
    }

    int row = 0, col = 0;
    int num = 1;
    ar[row][col] = 1; // 시작값은 1
    // 달팽이 배열 시작
    while (num + 1 <= N * M)
    {
        // 오른쪽 방향
        while (ar[row][col + 1] == 0 && col + 1 < M)
        {
            num++;
            col++;
            ar[row][col] = num;
        }
        // 아래 방향
        while (ar[row + 1][col] == 0 && row + 1 < N)
        {
            num++;
            row++;
            ar[row][col] = num;
        }
        // 왼쪽 방향
        while (ar[row][col - 1] == 0 && col - 1 >= 0)
        {
            num++;
            col--;
            ar[row][col] = num;
        }
        // 위쪽 방향
        while (ar[row - 1][col] == 0 && row - 1 >= 0)
        {
            num++;
            row--;
            ar[row][col] = num;
        }
    }

    // 달팽이 배열 출력
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf(" %d", ar[i][j]);
        }
        printf("\n");
    }

    return 0;
}

// 문제 5

// int main()
// {

//     int N, M;
//     scanf("%d %d", &N, &M); // 정수 N, M 입력

//     int arr[100][100];

//     int num = 1;
//     int row = 0, col = 0;
//     int cnt = 0;
//     int col_check = 0, row_check = 0;

//     arr[row][col] = 1; // 시작은 1

//     // 좌상단 부분
//     while (col < M && M > 1)
//     { // 행 업데이트
//         col_check++;
//         col = col_check;
//         // 수 업데이트
//         num++;
//         arr[row][col] = num;
//         // 좌측 아래로 이동
//         while (col < M && N > 1)
//         { // 행렬 업데이트
//             row++, col--;
//             // 수 업데이트
//             num++;
//             arr[row][col] = num;
//             // 더 이상 옆으로 갈 곳이 없다면 반복 종료
//             if (col == 0 || row == N - 1)
//             {
//                 row = 0;
//                 break;
//             }
//         }
//         // 행의 끝에 도달하면 반복 종료
//         if (col_check == M - 1)
//         {
//             break;
//         }
//     }

//     // 우하단 부분
//     while (row < N)
//     { // 열 업데이트
//         row_check++;
//         row = row_check;
//         // 시작은 한 칸 밑부터
//         col = M - 1;
//         // 수 업데이트
//         num++;
//         arr[row][col] = num;
//         // 좌측 아래로 이동
//         while (row < N - 1 && col > 0)
//         { // 행렬 업데이트
//             row++, col--;
//             // 수 업데이트
//             num++;
//             arr[row][col] = num;
//         }
//     }

//     // 좌하향 배열 출력
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < M; j++)
//         {
//             printf(" %d", arr[i][j]);
//         }
//         printf("\n");
//     }
//     return 0;
// }