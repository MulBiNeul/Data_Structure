#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 원형 큐 구조체
typedef struct QueueType
{
	int front, rear;
	int max;
	int *data;
} QueueType;

// 함수 원형
void init_queue(QueueType *q, int);
void enqueue(QueueType *q, int elem);
int dequeue(QueueType *q);
void print_queue(QueueType *q);

int main()
{

	int que_size;
	int n;

	scanf("%d", &que_size); // 원형 큐의 크기
	scanf("%d", &n);		// 명령의 개수
	getchar();

	// 원형 큐 동적 할당, 메모리 할당 여부 검사, 초기화
	QueueType *q = (QueueType *)malloc(sizeof(QueueType));
	if (q == NULL)
	{
		return -1;
	}
	init_queue(q, que_size);

	char command;
	int num, cnt = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &command); // 명령 입력

		// 삽입 연산
		if (command == 'I')
		{
			cnt++;
			// 포화 상태에서 삽입을 시도한 경우
			if (cnt >= q->max)
			{
				printf("overflow");
				print_queue(q);
				break;
			}

			getchar();
			scanf("%d", &num); // 삽입할 숫자 입력
			getchar();
			enqueue(q, num); // 숫자 삽입
		}
		// 삭제 연산
		else if (command == 'D')
		{
			getchar();
			dequeue(q); // 원소 삭제
			cnt--;
			// 공백 상테에서 삭제를 시도한 경우
			if (cnt < 0)
			{
				printf("underflow");
				break;
			}
		}
		// 배열 원소 전체 출력
		else if (command == 'P')
		{
			getchar();
			print_queue(q); // 원소 출력
		}
	}

	// 메모리 해제
	free(q->data);
	free(q);

	return 0;
}

// 원형 큐 초기화
void init_queue(QueueType *q, int que_size)
{
	q->front = q->rear = 0;
	q->max = que_size;
	q->data = (int *)malloc(sizeof(int) * (q->max));
	if (q->data == NULL)
	{
		return;
	}
	for (int i = 0; i < q->max; i++)
	{
		q->data[i] = 0;
	}
}

// 공백 상태 확인 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}

// 포화 상태 확인 함수
int is_full(QueueType *q)
{
	return (q->front == (q->rear + 1) % q->max);
}

// 원소 삽입 함수
void enqueue(QueueType *q, int elem)
{
	q->rear = (q->rear + 1) % q->max;
	q->data[q->rear] = elem;
}

// 원소 삭제 함수
int dequeue(QueueType *q)
{
	q->front = (q->front + 1) % q->max;
	return q->data[q->front] = 0;
}

// 전체 원소 출력 함수
void print_queue(QueueType *q)
{
	int cnt = 0;
	while (cnt < q->max)
	{
		printf(" %d", q->data[cnt]);
		cnt++;
	}
	printf("\n");
}

/*

6
10
I 10
I 20
P
I 30
I 40
D
P
I 50
I 60
I 70

*/