#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int element;
	struct Node *next;
}node;//노드 구조체

node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//새 노드 생성

void addLast(node **L,int e) {
	node *newnode = getnode(e);
	if (*L == NULL) {
		*L = newnode;
	}
	else {
		node *tmp = *L;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = newnode;
	}
}//마지막에 넣어주기

void partition(node **L, node **L1, node **L2, int N) {
	int k = N / 2;
	*L1 = *L;
	node *tmp = *L;
	for (int i = 1; i < k; i++) {
		tmp = tmp->next;
	}
	*L2 = tmp->next;
	tmp->next = NULL;
	*L = NULL;
}//부분 쪼개기

void merge(node **L, node **L1, node **L2) {
	while (*L1 != NULL && *L2 != NULL) {
		int e1 = (*L1)->element;
		int e2 = (*L2)->element;
		if (e1 > e2) {
			addLast(L, e2);
			node *F = (*L2);
			(*L2) = (*L2)->next;
			free(F);
		}
		else {
			addLast(L, e1);
			node *F = (*L1);
			(*L1) = (*L1)->next;
			free(F);
		}
	}
	while (*L1 != NULL) {
		int e1 = (*L1)->element;
		addLast(L, e1);
		node *F = (*L1);
		(*L1) = (*L1)->next;
		free(F);
	}
	while (*L2 != NULL) {
		int e2 = (*L2)->element;
		addLast(L, e2);
		node *F = (*L2);
		(*L2) = (*L2)->next;
		free(F);
	}
}//합치기(자료구조 합집합과 비슷한 과정)

void mergesort(node **L, int N) {
	if (N > 1) {
		node *L1 = NULL, *L2 = NULL;
		partition(L, &L1, &L2, N);
		mergesort(&L1, N / 2);
		mergesort(&L2, N - (N / 2));
		merge(L, &L1, &L2);
	}
}

void print(node *L) {
	node *tmp = L;
	while (tmp != NULL) {
		printf("%d ", tmp->element);
		tmp = tmp->next;
	}
}


int main(void) {
	node *L = NULL;
	int N,e;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &e);
		addLast(&L,e);
	}//무순 리스트 생성
	mergesort(&L, N);//병합정렬
	print(L);//정렬된 리스트 출력
	return 0;
}