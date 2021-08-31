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
}//����Ʈ ������ ��� ���� �� �ʱ�ȭ �Լ�

void Init_List() {
	L = (list *)malloc(sizeof(list));
	L->Header = getnode(0);
	L->Trailer = getnode(0);
	L->Header->next = L->Trailer;
	L->Trailer->prev = L->Header;
	L->cnt = 0;
}//����Ʈ ����ü ���� �� �ʱ�ȭ �Լ�

void Insert(int r, char e) {
	if (r < 0 || L->cnt + 1 < r) {
		printf("invalid position\n");
		return;
	}//�ùٸ��� ���� ��ġ��� ���� �޽��� ���
	else {
		node *newnode = getnode(e);
		node *p = L->Header;
		for (int i = 1; i < r; i++) {
			p = p->next;
		}//���� �� ��ġ ã��
		newnode->prev = p;
		newnode->next = p->next;
		p->next->prev = newnode;
		p->next = newnode;
		L->cnt++;//���� �� ���� ���� ��Ű��
	}
}

void Delete(int r) {
	node *p = L->Header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}//���� ��ġ Ž��
	p->prev->next = p->next;
	p->next->prev = p->prev;
	free(p);
	L->cnt--;//���� ���� �� ���� ���̱�
}

char Get(int r) {
	node *p = L->Header;
	for (int i = 0; i < r; i++) {
		p = p->next;
	}
	return p->element;
}//�ش� ��ġ ã�Ƽ� ���� ��ȯ

void print(list *L) {
	node *p = L->Header->next;
	while (p != L->Trailer) {
		printf("%c", p->element);
		p = p->next;
	}
	printf("\n");
}//��� ���

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