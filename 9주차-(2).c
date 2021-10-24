#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int M,n;

typedef struct Node {
	int element;
	struct Node *next;
}node;//해시테이블에 사용할 노드 구조체

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

int hashfunction(int x) {
	return x % M;
}//해시함수 반환값

void Init_HashTable() {
	H = (hash *)malloc(sizeof(hash));
	scanf("%d %d", &M,&n), getchar();
	H->BUCKET = (node **)malloc(sizeof(node *) * M);
	for (int i = 0; i < M; i++) {
		H->BUCKET[i] = getnode(i);
	}//각 버킷의 헤드노드 초기화
}//해시테이블 초기화함수

void InsertKey(int x) {
	node *newnode = getnode(x);
	int r1 = hashfunction(x);
	for (int i = 0; i < M; i++) {
		int r = hashfunction(r1+i);
		if (H->BUCKET[r]->next == NULL) {
			H->BUCKET[r]->next = newnode;
			if (i != 0) {
				for (int j = 0; j < i; j++) {
					printf("C");
				}
			}
			printf("%d\n", r);
			return;
		}
	}//선형탐색을 하면서 공간이 비어있다면 추가 후 충돌횟수 확인 및 값 출력
}//키 값 넣기 : 선형조사법

void SearchKey(int x) {
	int r1 = hashfunction(x);
	for (int i = 0; i < M; i++) {
		int r = hashfunction(r1+i);
		if (H->BUCKET[r]->next != NULL) {
			if (H->BUCKET[r]->next->element == x) {
				printf("%d %d\n", r, x);
				return;
			}
		}
	}//선형으로 조사하면서 키 값이 있는 위치의 인덱스와 키 값 반환
	printf("-1\n");
}//키 값 찾기 : 선형조사법



void Print() {
	for (int i = 0; i < M; i++) {
		node *P = H->BUCKET[i]->next;
		while (P != NULL) {
			printf(" %d", P->element);
			P = P->next;
		}
	}
}//출력함수

int main(void) {
	Init_HashTable();
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
		}
	} while (ch != 'e');
}