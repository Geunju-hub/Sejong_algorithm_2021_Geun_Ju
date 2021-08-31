#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int element;
	struct Node *prev;
	struct Node *next;
}node;

typedef struct List {
	int cnt;
	node *Header;
	node *Trailer;
}list;

list *L;

node *getnode(int E) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = E;
	newnode->prev = NULL;
	newnode->next = NULL;
	return newnode;
}//리스트 내부의 노드 생성 및 초기화 함수

void Init_List() {
	L = (list *)malloc(sizeof(list));
	L->Header = getnode(0);
	L->Trailer = getnode(0);
	L->Header->next = L->Trailer;
	L->Trailer->prev = L->Header;
	L->cnt = 0;
}//리스트 구조체 생성 및 초기화 함수

void Insert(int r, char e) {
	if (r < 0 || L->cnt + 1 < r) {
		printf("invalid position\n");
		return;
	}//올바르지 않은 위치라면 오류 메시지 출력
	else {
		node *newnode = getnode(e);
		node *p = L->Header;
		for (int i = 1; i < r; i++) {
			p = p->next;
		}//새로 들어갈 위치 찾기
		newnode->prev = p;
		newnode->next = p->next;
		p->next->prev = newnode;
		p->next = newnode;
		L->cnt++;//연결 및 개수 증가 시키기
	}
}

void Delete(int r) {
	node *p = L->Header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}//지울 위치 탐색
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	L->cnt--;//연결 끊기 및 개수 줄이기
}

char Get(int r) {
	node *p = L->Header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	return p->element;
}//해당 위치 찾아서 원소 반환

void print(list *L) {
	node *p = L->Header->next;
	while (p != L->Trailer) {
		printf("%c", p->element);
		p = p->next;
	}
	printf("\n");
}//모두 출력

int main(void) {
	Init_List();
	int N;
	scanf("%d", &N), getchar();
	for (int i = 0; i < N; i++) {
		char ch, e;
		int r;
		scanf("%c", &ch), getchar();
		switch (ch) {
		case'A':
			scanf("%d %c", &r, &e), getchar();
			Insert(r, e);
			break;
		case'D':
			scanf("%d", &r), getchar();
			if (r < 0 || L->cnt < r) {
				printf("invalid position\n");
			}
			else {
				Delete(r);
			}
			break;
		case'G':
			scanf("%d", &r), getchar();
			if (r < 0 || L->cnt < r) {
				printf("invalid position\n");
			}
			else {
				printf("%c\n", Get(r));
			}
			break;
		case'P':
			print(L);
			break;
		}
	}
	return 0;
}