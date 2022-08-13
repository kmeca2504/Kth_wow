/*
작성일 : 2022.05.28 - 2022.05.30
학과 : 컴퓨터 소프트웨어공학과
이름 : 김태헌
-----------------------------------------
프로그램명: 연결리스트를 이용한 다항식의 곱셈 프로그램
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996) //fscanf 사용시 오류 발생 -> 이를 무시하기 위한 구문

typedef struct ListNode{//노드 타입
    int coef; //계수
    int expon; //지수
    struct ListNode* link;
}ListNode;

typedef struct  ListType //리스트 헤더 타입
{
    int size; //헤더 타입의 사이즈
    ListNode* llink; //헤드 왼
    ListNode* rlink; //헤드 오
}ListType;

//error fuction
void error(char* message)
{
    fprintf(stderr,"%s\n",message); //error 발생 -> message 호출
    exit(1); //강제 종료
}

//리스트 헤더 생성 함수
ListType* create()
{
    ListType* plist = (ListType*)malloc(sizeof(ListType)); //동적 할당 plist를 ListType크기만큼 할당한다.
    plist->size = 0; //size를 0으로 잡아준다.
    plist->llink = plist->rlink = NULL; //생성이기 때문에 llink와 rllink를 NULL값으로 잡아준다.
    return plist; // 반환
}

//plist는 연결 리스트를 가르키는 포인터이며, coef: 계수, expon: 지수
void insert_last(ListType* plist, int coef, int expon)
{
    ListNode* temp = (ListNode*)malloc(sizeof(ListNode)); //동적할당 temp를 ListNode크기만큼 할당한다.
    if(temp == NULL) error("메모리 할당 에러");

    temp->coef = coef; //temp의 계수 : coef 
    temp->expon = expon; //temp의 지수 : expon
    temp->link =NULL; // temp의 링크는 -> Null를 가르킴
    if(plist->llink==NULL) //만약 plist llink가 null이면
    {
        plist->llink = plist->rlink = temp; // llink와 rlink를 temp를 가르키게 함.
    }
    else
    {
        plist->rlink->link = temp; //rlink의 링크를 temp를 가르키게 한다.
        plist->rlink = temp; //rlink를 temp fh tjfwjd
    }
     plist->size++; //사이즈 증가
}

//list3 = list1 + list 2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)// 덧셈 함수
{
    ListNode* a = plist1->llink; // a node를 만들고 plist1의 llink를 가르킴.
    ListNode* b = plist2->llink; // b node를 만들고 plist2의 llink를 가르킴.
    int sum;

    while(a && b) //a와 b가 마지막까지 반복
    {
        if(a->expon == b->expon)//a의 지수 == b의 지수 일때,
        {
            sum = a->coef + b-> coef; //a와 b의 계수를 더해준다.
            insert_last(plist3,sum,a->expon); //plist3에 더한 계수와 plist 1의 지수를 삽입한다.
            a = a->link; b= b->link;// a와 b를 옮긴다.
        }
        else if(a->expon > b->expon)//a의 지수가 b의 지수보다 클 경우
        {
            insert_last(plist3,a->coef,a->expon); //plist3에 a계수와 a지수를 삽입한다.
            a = a->link; //a를 옮긴다.
        }
        else //b의 지수가 클경우
        {
            insert_last(plist3,b->coef,b->expon);//plist3에 b계수와 b지수를 삽입한다.
            b = b->link; //b를 옮긴다.
        }
    }

    //a나 b중의 하나가 먼저 끝나게 되면 남아 있는 항들을 모두 결과 다항식으로 복사
    for(; a!=NULL; a=a->link)//a가 null이 될때까지 a를 옮김.
    {
        insert_last(plist3,a->coef,a->expon); //남아있는 항을 모두 다항식으로 넣어줌.
    }
    for(; b!=NULL; b=b->link)//b가 null이 될때까지 a를 옮김.
    {
        insert_last(plist3,b->coef,b->expon); //남아있는 항을 모두 다항식으로 넣어줌.
    }
}

ListType* poly_mul_cal(ListType* plist, int a, int b)//plist에 지수와 계수를 받아 반환하는 함수 -> 실질적인 계산 부분이다.
{
    ListNode* p = plist->llink; //리스트 노드를 p를 plist의 llink를 가르킴.
    ListType* ret; //리스트 타입 반환
    int mul_coef,sum_expon; //다항식의 곱은 계수끼리 곱하게 되고 지수끼리는 더하게 된다.

    ret = create(); //리스트 타입을 만듦.

    while (p)
    {
        mul_coef = p->coef * a;// 계수끼리 곱.
        sum_expon = p->expon + b; //지수끼리 덧셈.
        insert_last(ret,mul_coef,sum_expon); //값을 삽입.
        p = p->link; //p를 옮김.
    }

    return ret; //반환
}

//리스트 clear함수
void clear(ListType* plist)//리스트를 초기화 하는 함수.
{
    ListNode* a;//리스트 노드 a생성

    while(plist->llink !=NULL)//plist의 llink가 NULL일때까지 반복
    {
        a = plist->llink; // a가plist의 llink를 가르키게 함.
        plist->llink = plist->llink->link; //plist의 llink가 가르키는 곳을 plist->head의 링크가 가르키는곳으로 변경
        free(a); //plist의 llink를 가르키고 있던 a를 해제해줌
        a=NULL; // a를 NULL 로 변경
    }//plist가 전부 메모리를 해제하면서 초기화 하는 과정을 반복하게 된다.
}

void poly_mul(ListType* plist1,ListType* plist2,ListType* plist3)//곱셈 함수
{
    int co,ex;
    ListNode* a = plist1->llink; //리스트 노드 a를 plist1의 llink를 가르킴
    ListNode* b = plist2->llink; //리스트 노드 b를 plist2의 llink를 가르킴

    ListType* result_in; //a다항식에 b의 항을 곱한 결과를 저장하기 위한 리스트타입
    ListType* accumulate; //누적시키면서 곱한 값을 더해줘야 하기 때문에 누적시키는 타입 이다. -> poly_add에서 같은 리스트 타입을 2번 쓰면 프로그램 오류가남.

    accumulate = create();

    while(b) // b가 끝날 때까지
    {
        co = b->coef;
        ex = b->expon;
        result_in = poly_mul_cal(plist1,co,ex);//pllist1의 각 항에 b의 첫번째 계수와 지수를 다항식 곱을 하기 위해 poly_mul_cal 계산 함수로 보냄.

        accumulate->llink = plist3->llink; //accumlate의 llink를 plist3의 llink를 가르키게함.
        plist3->llink =NULL; //plist3은 NULL를 가르키도록 함. why? 계속해서 추가해야하기 때문.

        poly_add(result_in,accumulate,plist3); //덧셈 함수를 통해 누적값과 곱 계산이 완료된 함수를 더해준후, plist3에 저장함.

        b = b->link;//b가 다음 항을 가르키게 옮김.

        clear(accumulate);// accumulate를 초기화 시킴.

    }
    free(accumulate);
}

void poly_print(ListType* plist)//출력 함수
{
    ListNode* p = plist->llink;//p리스트 노드를 생성하고 plist의 llink를 가르킴.
    int cnt = 0 ;
    for(;p;p=p->link)
    {
        if(p->coef < 0)//만약 p의 계수가 0보다 작으면
        {
            if(p->expon !=0 )//p의 지수가 0이 아니면
                printf("- %dX^%d ",-(p->coef),p->expon);//계수에 -를 붙여 출력
            else
                printf("- %d",-(p->coef)); //지수가 0이므로 계수만 출력함.
            cnt++;
        }
        else if(cnt == 0)//처음 시작을 판단하는 조건문
        {
            printf(" %dX^%d ",p->coef,p->expon);//처음에는 부호를 붙이지 않음.
            cnt++;
        }
        else
        {
            if(p->expon !=0 )//p의 지수가 0이 아니면
                printf("+ %d^%d ",p->coef,p->expon);//계수에 +를 붙여 출력함.
            else
                printf("+ %d ",p->coef);//지수가 0이므로 계수만 출력함.
            cnt++;
        }
    }
    printf("\n");
}

int main()
{
    ListType* list1,* list2,* list3;//리스트 타입 3개
    FILE* fp;//파일 포인터 선언
    char name[1000]; //poly를 읽기 위한 char형 변수 선언
    int num,num1;

    //연결 리스트 헤더 생성
    list1=create();
    list2=create();
    list3=create();

    //파일 읽는 부분
    fp = fopen("data.txt","r"); //읽기 형식으로  open

    if(fp == NULL) //파일이 오픈 되어있는지 확인
    {
        printf("file not found \n");
        return 0;
    }

    fscanf(fp,"%s\n",name); //이름을 읽는다.
    while (!feof(fp))//파일이 끝날때까지 반복
    {
        fscanf(fp,"%d %d",&num,&num1);//계수는 num지수는 num1변수에 저장함.
        insert_last(list1, num, num1);//list1 삽입

        fscanf(fp,"%s",name);//이름을 읽음
        if(strcmp(name, "poly2") == 0)//poly2가 나오게 되면 다음 다항식이기 때문에
            break;
        else 
            fseek(fp,-2,SEEK_CUR); //아닐경우는 파일 포인터를 현재 위치에서 2칸 뒤로 보냄.
    }
    while (!feof(fp))//파일이 끝날때까지 반복
    {
        fscanf(fp,"%d %d",&num,&num1); //계수는 num지수를 num1변수에 저장.
        insert_last(list2,num,num1);//list2에 삽입
    }

    printf("Poly 1 = ");
    poly_print(list1); //list1의 식을 출력
    printf("Poly 2 = ");
    poly_print(list2); //list2의 식을 출력

    poly_mul(list1, list2, list3); //곱셈 진행
    printf("Poly 1 * Poly 2 = ");
    poly_print(list3); //결과 출력
    free(list1); free(list2);free(list3); //메모리 해제
    fclose(fp);// 프로그램을 닫음
    return 0; 
}
