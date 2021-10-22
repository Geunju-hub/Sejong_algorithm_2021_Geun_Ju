#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int M;//해시테이블의 크기

typedef struct Node {
	int element;
	struct Node *next;
}node;//노드 구조체

typedef struct Hash {
	node **BUCKET;
}hash;//해시테이블 구조체

hash *H;//전역변수로 선언

node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//노드 생성함수

void Init_Hash() {
	scanf("%d", &M), getchar();
	H = (hash *)malloc(sizeof(hash));
	H->BUCKET = (node **)malloc(sizeof(node*) * M);
	for (int i = 0; i < M; i++) {
		H->BUCKET[i] = getnode(i);
	}//버켓은 헤더노드 인덱스 설정
	return;
}//해시테이블 초기화

int hashfunction(int k) {
	return k % M;
}

void InsertKey(int k) {
	int R = hashfunction(k);
	node *newnode = getnode(k);
	newnode->next = H->BUCKET[R]->next;
	H->BUCKET[R]->next = newnode;
}//키 값을 넣어주는 함수

void SearchKey(int k) {
	int R = hashfunction(k);
	node *S = H->BUCKET[R]->next;
	int cnt = 1;
	while (S != NULL) {
		if (S->element == k) {
			printf("%d\n", cnt);
			return;
		}
		S = S->next;
		cnt++;
	}
	printf("0\n");
}//키 값을 찾아 있으면 해당 인덱스를 없으면 0을 출력하는 함수

void RemoveKey(int k) {
	int R = hashfunction(k);
	node *S = H->BUCKET[R];
	int cnt = 0;
	while (S!= NULL) {
		node *search = S->next;
		cnt++;
		if (search != NULL) {
			if (search->element == k) {
				node *F = search;
				S->next = search->next;
				free(F);
				printf("%d\n",cnt);
				return;
			}
		}
		S = S->next;
	}
	printf("0\n");
}//없앨 때 있으면 해당 위치를 없으면 0 출력

void Print() {
	for (int i = 0; i < M; i++) {
		node *P = H->BUCKET[i]->next;//헤더 노드 이후부터
		while (P != NULL) {
			printf(" %d", P->element);
			P = P->next;
		}
	}
	printf("\n");
}//출력함수

int main(void) {
	Init_Hash();
	char ch;
	int x;
	do {
		scanf("%c", &ch), getchar();
		switch (ch) {
		case'i':
			scanf("%d", &x), getchar();
			InsertKey(x);
			break;
		case's':
			scanf("%d", &x), getchar();
			SearchKey(x);
			break;
		case'd':
			scanf("%d", &x), getchar();
			RemoveKey(x);
			break;
		case'p':
			Print();
			break;
		}
	} while (ch != 'e');
	return 0;
}