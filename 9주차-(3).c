#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int M, n,q;

typedef struct Node {
	int element;
	struct Node *next;
}node;//��� ����ü

typedef struct Hash {
	node **BUCKET;
}hash;//�ؽ����̺� ����ü

hash *H;//�������� ����

int hashfunction1(int x) {
	return x % M;
}//ù ��° �ؽ��Լ�

int hashfunction2(int x) {
	return q - (x % q);
}//�� ��° �ؽ��Լ�

node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}//�������Լ�

void Init_HashTable() {
	scanf("%d %d %d", &M, &n,&q), getchar();
	H = (hash *)malloc(sizeof(hash));
	H->BUCKET = (node **)malloc(sizeof(node) * M);
	for (int i = 0; i < M; i++) {
		H->BUCKET[i] = getnode(i);
	}//������ �ʱ�ȭ
}//�ؽ����̺� �ʱ�ȭ

void InsertKey(int x) {
	for (int i = 0; i < M; i++) {
		int r = hashfunction1(hashfunction1(x) + i * hashfunction2(x));
		//���� �ؽ�
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
}//�ؽ����̺� Ű ���� �ִ� �Լ�

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
}//�ؽ����̺��� Ű �� ã�� �Լ�

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
}//�ؽ����̺� ���� ��� �Լ�

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