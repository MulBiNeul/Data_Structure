#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

// Node 구조체 선언
typedef struct Node
{
    int element;              // 쿠폰 번호
    char group;               // 가입자 명
    struct Node *nextgroup;   // 다음 가입자 명을 가리키는 포인터 노드
    struct Node *nextelement; // 다음 쿠폰 번호를 가리키는 포인터 노드
} Node;

// CouponSite 구조체 선언
typedef struct CouponSite
{
    Node *header; // 연결리스트의 헤더
} CouponSite;

CouponSite Groups[5];   // 가입자 배열
CouponSite Elements[4]; // 쿠폰 배열

// 함수 원형
Node *getnode(int, char);
void initShare();
void addShare(int, char);
void removeShare(int, char);
void traverseShareElements(char);
void traverseShareGroups(int);
void freeList(Node *);

int main()
{
    initShare(); // 다중연결리스트 초기화
    char command;
    int elem;
    char name;

    while (1)
    {
        scanf("%c", &command); // 명령어 입력

        // a 입력 시 가입자 및 쿠폰 추가
        if (command == 'a')
        {
            scanf(" %d %c", &elem, &name);
            getchar();
            addShare(elem, name);
        }
        // r 입력 시 가입자 및 쿠폰 삭제
        else if (command == 'r')
        {
            scanf(" %d %c", &elem, &name);
            getchar();
            removeShare(elem, name);
        }
        // e 입력 시 해당 가입자가 보유한 쿠폰 조회
        else if (command == 'e')
        {
            scanf(" %c", &name);
            getchar();
            traverseShareElements(name);
        }
        // g 입력 시 해당 쿠폰을 보유한 가입자 조회
        else if (command == 'g')
        {
            scanf("%d", &elem);
            traverseShareGroups(elem);
        }
        // q 입력 시 프로그램 종료
        else if (command == 'q')
        {
            break;
        }
    }

    // 메모리 해제
    for (int i = 0; i < 5; i++)
    {
        freeList(Groups[i].header);
    }
    for (int i = 0; i < 4; i++)
    {
        freeList(Elements[i].header);
    }

    return 0;
}

// Node 생성 함수
Node *getnode(int elem, char group)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // newNode 동적 할당
    // 메모리 할당 여부 검사
    if (!newNode)
    {
        printf("Memory allocation failed!\n");
    }
    // newnode에 가입자 명과 쿠폰 명 전달
    newNode->element = elem;
    newNode->group = group;
    newNode->nextgroup = newNode->nextelement = NULL;
    return newNode; // newnode 반환
}

// 초기화 함수
void initShare()
{
    // 쿠폰 명 배열을 NE만큼 초기화
    for (int i = 0; i < 4; ++i)
    { // 노드 동적 할당
        Node *H = (Node *)malloc(sizeof(Node));
        // 메모리 할당 여부 검사
        if (!H)
        {
            printf("Memory Allocation Failed!\n");
            return;
        }
        H->nextgroup = H;       // 원형 리스트
        Elements[i].header = H; // 쿠폰 명 배열 헤더 초기화
    }

    // 가입자 명 배열을 NG만큼 초기화
    for (int i = 0; i < 5; ++i)
    { // 노드 동적 할당
        Node *H = (Node *)malloc(sizeof(Node));
        // 메모리 할당 여부 검사
        if (!H)
        {
            printf("Memory Allocation Failed!\n");
            return;
        }
        H->nextelement = H;   // 원형 리스트
        Groups[i].header = H; // 가입자 명 배열 헤더 초기화
    }
}

// 가입자 명, 쿠폰 명 추가 함수
void addShare(int elem, char name)
{
    Node *newnode = getnode(elem, name); // 추가할 쿠폰, 가입자

    // 가입자 리스트에 추가
    Node *HG = Groups[name - 'A'].header;
    newnode->nextelement = HG->nextelement;
    HG->nextelement = newnode;

    // 쿠폰 리스트에 추가
    Node *HE = Elements[elem - 1].header;
    newnode->nextgroup = HE->nextgroup;
    HE->nextgroup = newnode;

    printf("OK\n"); // 추가 완료 후 OK 출력
}

// 가입자 명, 쿠폰 명 삭제 함수
void removeShare(int elem, char name)
{
    Node *Gstart, *Gcurr, *Estart, *Ecurr;

    // 가입자 리스트에서 삭제

    Gstart = Groups[name - 'A'].header; // 가입자 리스트의 헤더 노드로 시작
    Gcurr = Gstart->nextelement;        // 가입자 리스트의 첫 번째 노드부터 탐색 시작

    // 삭제할 쿠폰 명을 찾을 때까지 이동
    while (Gcurr != Gstart && Gcurr->element != elem)
    {
        Gstart = Gcurr;
        Gcurr = Gcurr->nextelement;
    }
    if (Gcurr != Gstart)
    {
        Gstart->nextelement = Gcurr->nextelement; // 쿠폰 명 삭제
    }

    // 쿠폰 리스트에서 삭제

    Estart = Elements[elem - 1].header; // 쿠폰 리스트의 헤더 노드로 시작
    Ecurr = Estart->nextgroup;          // 쿠폰 리스트의 첫 번째 노드에서부터 탐색 시작

    // 삭제할 쿠폰 명을 찾을 때까지 이동
    while (Ecurr != Estart && Ecurr->group != name)
    {
        Estart = Ecurr;
        Ecurr = Ecurr->nextgroup;
    }
    if (Estart != Ecurr)
    {
        Estart->nextgroup = Ecurr->nextgroup; // 가입자 명 삭제
    }

    printf("OK\n"); // 삭제 완료 후 OK 출력
}

// 가입자가 보유한 쿠폰 조회
void traverseShareElements(char name)
{
    // 원하는 가입자 배열의 헤더 노드 이후에서 시작
    Node *curr = Groups[name - 'A'].header->nextelement;

    // 조회할 쿠폰이 하나도 없는 경우
    if (curr == Groups[name - 'A'].header)
    { // 0 출력 후 종료
        printf("0\n");
        return;
    }

    // 조회할 쿠폰이 없을 때까지 이동하며 출력
    while (curr != Groups[name - 'A'].header)
    {
        printf("%d ", curr->element);
        curr = curr->nextelement;
    }

    printf("\n");
}

// 쿠폰을 보유한 가입자 조회
void traverseShareGroups(int elem)
{
    // 원하는 쿠폰 배열의 헤더 노드 이후에서 시작
    Node *curr = Elements[elem - 1].header->nextgroup;

    // 조회할 가입자가 한 명도 없는 경우
    if (curr == Elements[elem - 1].header)
    { // 0 출력 후 종료
        printf("0\n");
        return;
    }

    // 조회할 가입자가 없을 때까지 이동하며 출력
    while (curr != Elements[elem - 1].header)
    {
        printf("%c ", curr->group);
        curr = curr->nextgroup;
    }

    printf("\n");
}

// 메모리 해제 함수
void freeList(Node *header)
{
    Node *curr;
    // 헤더 노드로 돌아오기 전까지 이동하며 메모리 해제
    while (header->nextelement != header)
    {
        curr = header->nextelement;
        header->nextelement = curr->nextelement;
        free(curr);
    }
    free(header); // 헤더 노드 해제
}

/*

a 1 C
a 4 A
a 4 E
a 4 D
e A
g 4
a 2 A
e A
r 4 A
g 4
e A
g 1
r 1 C
e C
g 1
g 3

*/