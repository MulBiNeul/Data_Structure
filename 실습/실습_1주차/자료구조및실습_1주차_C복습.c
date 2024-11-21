#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 문제 1

// int sum(int); // sum 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N); // 정수 N 입력

//     int res = 0;
//     // N번만큼 반복하여 합 계산
//     for (int i = 1; i <= N; i++)
//     {
//         res += sum(i);
//     }
//     printf("%d", res); // 합의 값 출력
//     return 0;
// }

// int sum(int n)
// {
//     int res = 0;
//     // 1부터 n까지의 합
//     for (int i = 1; i <= n; i++)
//     {
//         res += i;
//     }
//     return res;
// }

// 문제 2

// void ABC(int[], int); // ABC 함수 원형

// int main()
// {
//     int ar[10];
//     // 10개의 정수 입력
//     for (int i = 0; i < 10; i++)
//     {
//         scanf("%d", &ar[i]);
//     }

//     // ABC 함수 반복 호출
//     for (int i = 0; i < 10; i++)
//     {
//         ABC(ar, i);
//     }

//     // 내림차순 정렬된 배열 출력
//     for (int i = 0; i < 10; i++)
//     {
//         printf(" %d", ar[i]);
//     }

//     return 0;
// }

// void ABC(int ar[], int k)
// {
//     int max = -9999;
//     int check = 0;
//     // k번째 정수부터 마지막 정수 중 가장 큰 정수 찾기
//     for (int i = k; i < 10; i++)
//     {
//         if (ar[i] > max) // 기존 max값보다 클 경우
//         {
//             max = ar[i]; // max값 update
//             check = i;   // max값의 위치 확인
//         }
//     }
//     // max의 위치와 k번째 위치의 정수 교환
//     int tmp = ar[k];
//     ar[k] = max;
//     ar[check] = tmp;
// }

// 문제 3

// void swap(int *, int *);    // 함수 원형

// int main()
// {
//     int N;
//     scanf("%d", &N);        // 정수 N 입력

//     int ar[50];
//     // N개의 정수 입력
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar[i]);
//     }

//     int a, b;
//     scanf("%d %d", &a, &b);     // 인덱스 a와 b 입력

//     int *p = ar + a;    // 인덱스 a의 포인터
//     int *q = ar + b;    // 인덱스 b의 포인터
//     swap(p, q);         // swap 실행

//     // 교환된 배열 출력
//     for (int i = 0; i < N; i++)
//     {
//         printf(" %d", ar[i]);
//     }

//     return 0;
// }

// void swap(int *pa, int *pb)
// {
//     // 서로의 위치 교환
//     int tmp = *pa;
//     *pa = *pb;
//     *pb = tmp;
// }

// 문제 4

// int main()
// {
//     char ch[100];
//     scanf("%s", ch); // 공백을 포함하지 않는 문자열 입력

//     int len = strlen(ch); // 문자열의 길이 저장
//     for (int i = 0; i < len; i++)
//     {
//         printf("%s\n", ch); // 현재 문자열 출력
//         char tmp = ch[0];   // 첫 문자 저장
//         // 한 칸씩 shift
//         for (int j = 0; j < len; j++)
//         {
//             ch[j] = ch[j + 1];
//         }
//         ch[len - 1] = tmp; // 저장했던 첫 문자가 마지막 문자가 됩니다.
//     }

//     return 0;
// }

// 문제 5

// typedef struct time
// {
//     int h, min, sec; // 순서대로 시, 분, 초
// } Time;

// int main()
// {
//     Time t1, t2, t3;
//     scanf("%d %d %d", &t1.h, &t1.min, &t1.sec); // 첫 번째 시각 입력
//     scanf("%d %d %d", &t2.h, &t2.min, &t2.sec); // 두 번째 시각 입력

//     // 두 번째 시각의 초가 첫 번째 시각의 초보다 작은 경우
//     if (t2.sec < t1.sec)
//     {
//         t3.sec = t2.sec + 60 - t1.sec;
//         t2.min -= 1;
//     }
//     // 그 외
//     else
//     {
//         t3.sec = t2.sec - t1.sec;
//     }

//     // 두 번째 시각의 분이 첫 번째 시각의 분보다 작은 경우
//     if (t2.min < t1.min)
//     {
//         t3.min = t2.min + 60 - t1.min;
//         t2.h -= 1;
//     }
//     // 그 외
//     else
//     {
//         t3.min = t2.min - t1.min;
//     }

//     t3.h = t2.h - t1.h;     // 두 번째 시각의 시간이 첫 번째 시각의 시간보다 작은 경우는 X

//     printf("%d %d %d", t3.h, t3.min, t3.sec);   // 두 시각의 차이 출력
//     return 0;
// }

// 문제 6

// typedef struct student
// {
//     char name[10]; // 학생의 이름
//     int score;     // 학생의 기말고사 점수
// } ST;

// int main()
// {
//     ST st[5];
//     double avg, sum = 0;

//     for (int i = 0; i < 5; i++)
//     {
//         scanf("%s %d", st[i].name, &st[i].score); // 각 학생의 정보 입력
//         sum += st[i].score;                       // 기말고사 점수의 총합 업데이트
//     }

//     avg = sum / 5; // 기말고사 점수의 평균

//     for (int i = 0; i < 5; i++)
//     {
//         if (st[i].score < avg) // 기말고사 평균보다 해당 학생의 점수가 낮은 경우
//         {
//             printf("%s\n", st[i].name); // 학생의 이름 출력
//         }
//     }

//     return 0;
// }

// 문제 7

// int main()
// {
//     int N;
//     scanf("%d", &N);    // 정수 N 입력

//     int *ar1, *ar2;
//     // 두 개의 배열 동적 할당
//     ar1 = (int *)malloc(sizeof(int) * N);
//     ar2 = (int *)malloc(sizeof(int) * N);

//     // 메모리 할당 여부 검사
//     if (ar1 == NULL)
//     {
//         return -1;
//     }
//     if (ar2 == NULL)
//     {
//         return -1;
//     }

//     // 두 개의 배열 입력
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar1[i]);
//     }
//     for (int i = 0; i < N; i++)
//     {
//         scanf("%d", &ar2[i]);
//     }

//     // 역방향으로 더하여 출력
//     for (int i = 0; i < N; i++)
//     {
//         printf(" %d", ar1[i] + ar2[N - i - 1]);
//     }

//     // 동적 메모리 해제
//     free(ar1);
//     free(ar2);
//     return 0;
// }

// 문제 8

typedef struct student
{
    char name[8];       // 학생의 이름
    int kor, eng, math; // 학생의 과목별 성적
    double avg;         // 학생의 평균
} ST;

int main()
{
    int N;
    scanf("%d", &N); // 정수 N 입력

    ST *st;
    // st 구조체 동적할당
    st = (ST *)malloc(sizeof(ST) * N);
    // 메모리 할당 여부 확인
    if (st == NULL)
    {
        return -1;
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%s %d %d %d", st[i].name, &st[i].kor, &st[i].eng, &st[i].math); // 학생의 정보 입력
        st[i].avg = (double)(st[i].kor + st[i].eng + st[i].math) / 3;          // 학생의 평균 계산
    }

    for (int i = 0; i < N; i++)
    {
        printf("%s %.1f", st[i].name, st[i].avg); // 학생의 이름과 평균 출력
        // 어느 한 과목이라도 90점 이상일 경우 GREAT 출력
        if (st[i].kor >= 90 || st[i].eng >= 90 || st[i].math >= 90)
        {
            printf(" GREAT");
        }
        // 어느 한 과목이라도 70점 미만일 경우 BAD 출력
        if (st[i].kor < 70 || st[i].eng < 70 || st[i].math < 70)
        {
            printf(" BAD");
        }
        printf("\n");
    }

    free(st); // 동적 메모리 해제
    return 0;
}