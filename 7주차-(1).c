#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //bool�ڷ��� ����� ���� stdbool ��� �߰�

typedef struct BTnode {
	int key;
	struct BTnode *parent;
	struct BTnode *left;
	struct BTnode *right;
}BTnode;//����Ʈ�� ��� ����ü

typedef struct BT {
	BTnode *root;
}BT;//����Ʈ�� ����ü 

BT *tree;//���������� ����

bool isInternal(BTnode *v) {
	return v->left != NULL || v->right != NULL;
}//���γ������ Ȯ���ϴ� �Լ�

bool isExternal(BTnode *v) {
	return v->left == NULL && v->right == NULL;
}//�ܺγ������ Ȯ���ϴ� �Լ�

BTnode *getBTnode(BTnode *P) {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->key = 0;
	newnode->parent = P;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}//����Ʈ����� ���� �� �θ���� ����

void Init_BTtree() {
	tree = (BT *)malloc(sizeof(BT));
	tree->root = NULL;
}//����Ž��Ʈ�� �ʱ�ȭ �Լ�

BTnode *search(BTnode *v, int k) {
	if (isExternal(v)) {
		return v;
	}//�ܺγ��� �ش� ��� ��ȯ -> ���⿡ Ű�� ���� ����
	if (v->key == k) {
		return v;
	}//�ش� Ű�� �ִٸ� ��� ��ȯ -> ���� ���� x
	else if (v->key > k) {
		return search(v->left, k);
	}//ũ�� ���������� ã�ư����ϹǷ� �������� ���
	else {
		return search(v->right, k);
	}//�ݴ�� ���������� ���
}//Ž�� �Լ�


void Insert(int k) {
	if (tree->root == NULL) {
		tree->root = getBTnode(NULL);
		tree->root->key = k;
		tree->root->left = getBTnode(tree->root);
		tree->root->right = getBTnode(tree->root);
	}//��Ʈ ��尡 ���̸� ����
	else {
		BTnode *tmp = search(tree->root, k);
		if (isInternal(tmp)) {
			return;
		}
		else {
			tmp->key = k;
			tmp->left = getBTnode(tmp);
			tmp->right = getBTnode(tmp);
		}
	}//��Ʈ ��尡 ���� �ƴϸ� ã�Ƽ� ����
}

void Search(int k) {
	BTnode *tmp = search(tree->root, k);
	if (isExternal(tmp)) {
		printf("X\n");
	}
	else {
		printf("%d\n", tmp->key);
	}
}//Ž�� �� ������ �� ���� ������ X��� �Լ�

BTnode *inordersucc(BTnode *v) {
	BTnode *z = v;
	while (isInternal(z->left)) {
		z = z->left;
	}
	return z;
}//������ȸ �İ��� ã�� (������ ��Ʈ�� �� ���� ���� ��)

void reduce(BTnode *z) {
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
}//�ڽĳ��� �θ��� ���� ���� �� �ڽ��� ������ �� �θ��� ����

void Remove(int k) {
	BTnode *tmp = search(tree->root, k);
	if (isExternal(tmp)) {
		printf("X\n");
		return;
	}
	else {
		printf("%d\n", tmp->key);
		BTnode *z = tmp->left;
		if (isInternal(z)) {
			z = tmp->right;
		}
		if (!isExternal(z)) {
			BTnode *y = inordersucc(z);
			BTnode *r=y->right;
			tmp->key = y->key;
			reduce(y->left);
		}
		else {
			reduce(z);
		}
	}
}//�����Լ�

void preorder(BTnode *v) {
	if (isInternal(v)) {
		printf(" %d", v->key);
		preorder(v->left);
		preorder(v->right);
	}
}//������ȸ �Լ�(��� �̿�)

void Print() {
	preorder(tree->root);
	printf("\n");
}//��� �� ����

int main(void) {
	BTnode *tmp=NULL;
	Init_BTtree();
	int k;
	char ch;
	do {
		scanf("%c", &ch), getchar();//�Է� �� ���ʹ� getchar�� �����
		switch (ch) {
		case'i':
			scanf("%d", &k), getchar();//Ű �Է� �� ���� ����
			Insert(k);//���� �Լ�
			break;
		case'd':
			scanf("%d", &k), getchar();//Ű �Է� �� ���� ����
			Remove(k);//���� �Լ�
			break;
		case's':
			scanf("%d", &k), getchar();//Ű �Է� �� ���� ����
			Search(k);//ã�� �Լ�
			break;
		case'p':
			Print();//��� �Լ�
			break;
		}//ch�� �ƽ�Ű�ڵ�(����)�� ǥ�� �����ϹǷ� switch�� ��� ����
	} while (ch != 'q');//���� ������ ���
	return 0;
}