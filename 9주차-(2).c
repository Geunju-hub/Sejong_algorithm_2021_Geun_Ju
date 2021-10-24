#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int M,n;

typedef struct Node {
	int element;
	struct Node *next;
}node;//�ؽ����̺� ����� ��� ����ü

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

int hashfunction(int x) {
	return x % M;
}//�ؽ��Լ� ��ȯ��

void Init_HashTable() {
	H = (hash *)malloc(sizeof(hash));
	scanf("%d %d", &M,&n), getchar();
	H->BUCKET = (node **)malloc(sizeof(node *) * M);
	for (int i = 0; i < M; i++) {
		H->BUCKET[i] = getnode(i);
	}//�� ��Ŷ�� ����� �ʱ�ȭ
}//�ؽ����̺� �ʱ�ȭ�Լ�

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
	}//����Ž���� �ϸ鼭 ������ ����ִٸ� �߰� �� �浹Ƚ�� Ȯ�� �� �� ���
}//Ű �� �ֱ� : ���������

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
	}//�������� �����ϸ鼭 Ű ���� �ִ� ��ġ�� �ε����� Ű �� ��ȯ
	printf("-1\n");
}//Ű �� ã�� : ���������



void Print() {
	for (int i = 0; i < M; i++) {
		node *P = H->BUCKET[i]->next;
		while (P != NULL) {
			printf(" %d", P->element);
			P = P->next;
		}
	}
}//����Լ�

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