#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int M, n,q;

typedef struct Node {
	int element;
	struct Node *next;
}node;//노드 구조체

typedef struct Hash {
	node **BUCKET;
}hash;//해시테이블 구조체

hash *H;//전역변수 설정

int hashfunction1(int x) {
	return x % M;
}//첫 번째 해시함수

int hashfunction2(int x) {
	return q - (x % q);
}//두 번째 해시함수

node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//노드생성함수

void Init_HashTable() {
	scanf("%d %d %d", &M, &n,&q), getchar();
	H = (hash *)malloc(sizeof(hash));
	H->BUCKET = (node **)malloc(sizeof(node) * M);
	for (int i = 0; i < M; i++) {
		H->BUCKET[i] = getnode(i);
	}//헤더노드 초기화
}//해시테이블 초기화

void InsertKey(int x) {
	for (int i = 0; i < M; i++) {
		int r = hashfunction1(hashfunction1(x) + i * hashfunction2(x));
		//이중 해싱
		if (H->BUCKET[r]->next == NULL) {
			node *newnode = getnode(x);
			H->BUCKET[r]->next = newnode;
			if (i != 0) {
				for (int j = 0; j < i; j++) {
					printf("C");
				}
			}
			printf("%d\n", r);
			return;
		}
	}
}//해시테이블에 키 값을 넣는 함수

void SearchKey(int x) {
	int r = hashfunction1(x);
	for (int i = r; i < M; i++) {
		if (H->BUCKET[i]->next != NULL) {
			if (H->BUCKET[i]->next->element == x) {
				printf("%d %d\n", i, x);
				return;
			}
		}
	}
	printf("-1\n");
}//해시테이블의 키 값 찾는 함수

void Print() {
	for (int i = 0; i < M; i++) {
		node *P = H->BUCKET[i]->next;
		if (P == NULL) {
			printf(" 0");
			continue;
		}
		while (P != NULL) {
			printf(" %d", P->element);
			P = P->next;
		}
	}
	printf("\n");
}//해시테이블 원소 출력 함수

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
		case'p':
			Print();
			break;
		}
	} while (ch != 'e');
	Print();
	return 0;
}