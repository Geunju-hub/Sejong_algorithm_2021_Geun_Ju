#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int M;//�ؽ����̺��� ũ��

typedef struct Node {
	int element;
	struct Node *next;
}node;//��� ����ü

typedef struct Hash {
	node **BUCKET;
}hash;//�ؽ����̺� ����ü

hash *H;//���������� ����

node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//��� �����Լ�

void Init_Hash() {
	scanf("%d", &M), getchar();
	H = (hash *)malloc(sizeof(hash));
	H->BUCKET = (node **)malloc(sizeof(node*) * M);
	for (int i = 0; i < M; i++) {
		H->BUCKET[i] = getnode(i);
	}//������ ������ �ε��� ����
	return;
}//�ؽ����̺� �ʱ�ȭ

int hashfunction(int k) {
	return k % M;
}

void InsertKey(int k) {
	int R = hashfunction(k);
	node *newnode = getnode(k);
	newnode->next = H->BUCKET[R]->next;
	H->BUCKET[R]->next = newnode;
}//Ű ���� �־��ִ� �Լ�

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
}//Ű ���� ã�� ������ �ش� �ε����� ������ 0�� ����ϴ� �Լ�

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
}//���� �� ������ �ش� ��ġ�� ������ 0 ���

void Print() {
	for (int i = 0; i < M; i++) {
		node *P = H->BUCKET[i]->next;//��� ��� ���ĺ���
		while (P != NULL) {
			printf(" %d", P->element);
			P = P->next;
		}
	}
	printf("\n");
}//����Լ�

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