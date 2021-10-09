#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BTnode {
	int key;
	int height;
	struct BTnode *parent;
	struct BTnode *left;
	struct BTnode *right;
}BTnode;//����Ʈ�� ��� ����ü

typedef struct BinarySearchTree {
	BTnode *root;
}BST;//����Ž��Ʈ�� ����ü

BST *tree;//���������� Ʈ�� ����

void Init_BST() {
	tree = (BST *)malloc(sizeof(BST));
	tree->root = NULL;
}//Ʈ�� �ʱ�ȭ �Լ�

int Max(int a, int b) {
	return a > b ? a : b;
}//�ִ� ���ϴ� �Լ�

int Abs(int a) {
	return a > 0 ? a : (-1) * a;
}//���� ���ϴ� �Լ�

bool UpdateHeightAndBalance(BTnode *v) {
	if (v == NULL) {
		return true;
	}
	BTnode *l = v->left;
	BTnode *r = v->right;
	v->height = Max(l->height, r->height) + 1;
	return Abs(l->height - r->height) < 2;
}//���� ���� �� avlƮ�� ���� �����ϴ��� Ȯ��

bool isExternal(BTnode *v) {
	return v->left == NULL && v->right == NULL;
}//�ܺγ�� Ȯ�� �Լ�

bool isInternal(BTnode *v) {
	return v->left != NULL || v->right != NULL;
}//���γ�� Ȯ�� �Լ�

BTnode *getBTnode(BTnode *Parent) {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->key = 0;
	newnode->height = 0;
	newnode->parent = Parent;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}//�� ��� ���� �� �θ�� �������ִ� �Լ�

BTnode *search(BTnode *v, int k) {
	if (isExternal(v)) {
		return v;
	}
	if (v->key == k) {
		return v;
	}
	else if (v->key > k) {
		return search(v->left, k);
	}
	else {
		return search(v->right, k);
	}
}//Ʈ�� ���ο� Ű ���� ���� ��尡 �����ϴ��� �˷��ִ� �Լ�

void SearchKey(int k) {
	BTnode *w = search(tree->root, k);
	if (isInternal(w)) {
		printf("%d\n", k);
	}
	else {
		printf("X\n");
	}
}//Ű �˻��ؼ� ������ Ű ���� ������ x ���

BTnode *restructure(BTnode *x) {
	BTnode *y = x->parent, *z = y->parent;
	BTnode *a, *b, *c;
	BTnode *T0, *T1, *T2, *T3;
	if (z->key > y->key && y->key > x->key) {
		b = y, a = x, c = z;
		T0 = x->left, T1 = x->right, T2 = y->right, T3 = z->right;
	}//z>y>x : LL
	else if (z->key > x->key && x->key > y->key) {
		b = x, a = y, c = z;
		T0 = y->left, T1 = x->left, T2 = x->right, T3 = z->right;
	}//z>x>y : LR
	else if (x->key > y->key && y->key > z->key) {
		b = y, a = z, c = x;
		T0 = z->left, T1 = y->left, T2 = x->left, T3 = x->right;
	}//x>y>z : RR
	else {
		b = x, a = z, c = y;
		T0 = z->left, T1 = x->left, T2 = x->right, T3 = y->right;
	}//y>x>z : RL

	if (z == tree->root) {
		tree->root = b;
		b->parent = NULL;
	}
	else if (z->parent->left == z) {
		z->parent->left = b;
		b->parent = z->parent;
	}
	else {
		z->parent->right = b;
		b->parent = z->parent;
	}//����

	a->left = T0;
	T0->parent = a;
	a->right = T1;
	T1->parent = a;
	a->height = Max(T0->height, T1->height) + 1;

	c->left = T2;
	T2->parent = c;
	c->right = T3;
	T3->parent = c;
	c->height = Max(T2->height, T3->height) + 1;

	b->left = a;
	a->parent = b;
	b->right = c;
	c->parent = b;
	b->height = Max(a->height, c->height) + 1;
	//���� �� Ʈ�� ����
	return b;//�߰� ��� ��ȯ
}

void UpdateAfterInsertion(BTnode *w) {
	BTnode *x, *y, *z = w;
	while (UpdateHeightAndBalance(z)) {
		if (z == NULL) {
			return;
		}
		z = z->parent;
	}//�̻��� �ִ� �κ� Ȯ��
	if (z->left->height > z->right->height) {
		y = z->left;
	}
	else {
		y = z->right;
	}
	if (y->left->height > y->right->height) {
		x = y->left;
	}
	else if (y->left->height < y->right->height) {
		x = y->right;
	}
	else {
		if (y == z->left) {
			x = y->left;
		}
		else {
			x = y->right;
		}
	}
	//x,y,z��� ����
	restructure(x);
}

void InsertKey(int k) {
	if (tree->root == NULL) {
		tree->root = getBTnode(NULL);
		tree->root->key = k;
		tree->root->left = getBTnode(tree->root);
		tree->root->right = getBTnode(tree->root);
	}//��Ʈ�� �����ϴ� ���
	else {//��Ʈ�� �������� ������ Ž�� �� ����
		BTnode *w = search(tree->root, k);
		if (isInternal(w)) {
			return;
		}//Ű ���� �����ϸ� ���� x
		else {
			w->key = k;
			w->left = getBTnode(w);
			w->right = getBTnode(w);
			UpdateAfterInsertion(w);
		}//Ű ���� �������� ������ ���� �� ����
	}
}

BTnode *reduce(BTnode *z) {
	BTnode *w = z->parent;
	BTnode *zs = w->left == z ? w->right : w->left;
	if (w == tree->root) {
		tree->root = zs;
		zs->parent = NULL;
	}
	else {
		BTnode *g = w->parent;
		zs->parent = g;
		if (g->left == w) {
			g->left = zs;
		}
		else {
			g->right = zs;
		}
	}
	free(z);
	free(w);//�޸� ����
	return zs;
}//�θ���� zs ���� �� z�� w��� ����, zs��� ��ȯ

BTnode *inordersucc(BTnode *w) {
	BTnode *z = w->right;
	if (isExternal(z)) {
		return NULL;
	}
	while (isInternal(z->left)) {
		z = z->left;
	}
	return z;
}//������ ��Ʈ�� �� ���� ���� �� ����

BTnode *inordersucc2(BTnode *w) {
	BTnode *z = w->left;
	if (isExternal(z)) {
		return NULL;
	}
	while (isInternal(z->right)) {
		z = z->right;
	}
	return z;
}//���� ��Ʈ�� �� ���� ū �� ����

BTnode *UpdateAfterRemoval(BTnode *w) {
	BTnode *x, *y, *z = w;
	while (UpdateHeightAndBalance(z)) {
		if (z == NULL) {
			return;
		}
		z = z->parent;
	}//�̻��� �ִ� �κ� Ȯ��
	if (z->left->height > z->right->height) {
		y = z->left;
	}
	else {
		y = z->right;
	}
	if (y->left->height > y->right->height) {
		x = y->left;
	}
	else if (y->left->height < y->right->height) {
		x = y->right;
	}
	else {
		if (y == z->left) {
			x = y->left;
		}
		else {
			x = y->right;
		}
	}
	//x,y,z��� ����
	BTnode *b = restructure(x);
	UpdateAfterRemoval(b->parent);
}

void RemoveKey(int k) {
	if (tree->root == NULL) {
		printf("X\n");
		return;
	}
	BTnode *w = search(tree->root, k);
	BTnode *zs;
	if (isExternal(w)) {
		printf("X\n");
	}
	else {
		printf("%d\n", k);
		BTnode *z = w->left;
		if (!isExternal(z)) {
			z = w->right;
		}//���� ���������� �̵�
		if (!isInternal(z)) {
			zs = reduce(z);
		}//z�� w��� ����� �۾� ����
		else {
			BTnode *y = inordersucc(w);//������ȸ �İ��� ã��
			if (y != NULL) {
				w->key = y->key;
				z = y->left;//y�� ���� ���� ���̴ϱ� �����ʿ� ���� �������� �� �ֱ� ������ �������� ����
				zs = reduce(z);
			}//������ ��Ʈ������ ���� ���� ���� ã���� ���
			else {
				y = inordersucc2(w);
				w->key = y->key;
				z = y->right;
				zs = reduce(z);
			}//�� ã���� ��� ���� ��Ʈ�� �� ���� ū �� ����
		}
		UpdateAfterRemoval(zs->parent);
	}
}

void preorder(BTnode *v) {
	if (v != NULL) {
		if (isInternal(v)) {
			printf(" %d", v->key);
			preorder(v->left);
			preorder(v->right);
		}
	}
}//���γ��鼭 �� ���� �ƴϸ� ������ȸ�� ���

void Print() {
	preorder(tree->root);
	printf("\n");
}//��� �Լ�

int main(void) {
	Init_BST();
	int K;
	char ch;
	do {
		scanf("%c", &ch), getchar();
		switch (ch) {
		case'i':
			scanf("%d", &K), getchar();
			InsertKey(K);
			break;//i �Է� �� K�� �Է� �� ���� ����
		case'd':
			scanf("%d", &K), getchar();
			RemoveKey(K);
			break;//d�� K�� �Է� �� ���� ����
		case's':
			scanf("%d", &K), getchar();
			SearchKey(K);
			break;//s�� K�� �Է� �� ã�� ����
		case'p':
			Print();
			break;//p �Է� �� ������ȸ ��� ����
		}
	} while (ch != 'q');
	return 0;
}