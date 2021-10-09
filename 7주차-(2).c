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
}BTnode;//이진트리 노드 구조체

typedef struct BinarySearchTree {
	BTnode *root;
}BST;//이진탐색트리 구조체

BST *tree;//전역변수로 트리 선언

void Init_BST() {
	tree = (BST *)malloc(sizeof(BST));
	tree->root = NULL;
}//트리 초기화 함수

int Max(int a, int b) {
	return a > b ? a : b;
}//최댓값 구하는 함수

int Abs(int a) {
	return a > 0 ? a : (-1) * a;
}//절댓값 구하는 함수

bool UpdateHeightAndBalance(BTnode *v) {
	if (v == NULL) {
		return true;
	}
	BTnode *l = v->left;
	BTnode *r = v->right;
	v->height = Max(l->height, r->height) + 1;
	return Abs(l->height - r->height) < 2;
}//높이 갱신 후 avl트리 조건 만족하는지 확인

bool isExternal(BTnode *v) {
	return v->left == NULL && v->right == NULL;
}//외부노드 확인 함수

bool isInternal(BTnode *v) {
	return v->left != NULL || v->right != NULL;
}//내부노드 확인 함수

BTnode *getBTnode(BTnode *Parent) {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->key = 0;
	newnode->height = 0;
	newnode->parent = Parent;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}//새 노드 생성 후 부모와 연결해주는 함수

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
}//트리 내부에 키 값을 가진 노드가 존재하는지 알려주는 함수

void SearchKey(int k) {
	BTnode *w = search(tree->root, k);
	if (isInternal(w)) {
		printf("%d\n", k);
	}
	else {
		printf("X\n");
	}
}//키 검색해서 있으면 키 값을 없으면 x 출력

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
	}//조정

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
	//높이 및 트리 갱신
	return b;//중간 노드 반환
}

void UpdateAfterInsertion(BTnode *w) {
	BTnode *x, *y, *z = w;
	while (UpdateHeightAndBalance(z)) {
		if (z == NULL) {
			return;
		}
		z = z->parent;
	}//이상이 있는 부분 확인
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
	//x,y,z노드 결정
	restructure(x);
}

void InsertKey(int k) {
	if (tree->root == NULL) {
		tree->root = getBTnode(NULL);
		tree->root->key = k;
		tree->root->left = getBTnode(tree->root);
		tree->root->right = getBTnode(tree->root);
	}//루트에 삽입하는 경우
	else {//루트에 삽입하지 않으면 탐색 후 삽입
		BTnode *w = search(tree->root, k);
		if (isInternal(w)) {
			return;
		}//키 값이 존재하면 삽입 x
		else {
			w->key = k;
			w->left = getBTnode(w);
			w->right = getBTnode(w);
			UpdateAfterInsertion(w);
		}//키 값이 존재하지 않으면 삽입 후 연결
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
	free(w);//메모리 해제
	return zs;
}//부모노드와 zs 연결 후 z와 w노드 제거, zs노드 반환

BTnode *inordersucc(BTnode *w) {
	BTnode *z = w->right;
	if (isExternal(z)) {
		return NULL;
	}
	while (isInternal(z->left)) {
		z = z->left;
	}
	return z;
}//오른쪽 부트리 중 가장 작은 값 선택

BTnode *inordersucc2(BTnode *w) {
	BTnode *z = w->left;
	if (isExternal(z)) {
		return NULL;
	}
	while (isInternal(z->right)) {
		z = z->right;
	}
	return z;
}//왼쪽 부트리 중 가장 큰 값 선택

BTnode *UpdateAfterRemoval(BTnode *w) {
	BTnode *x, *y, *z = w;
	while (UpdateHeightAndBalance(z)) {
		if (z == NULL) {
			return;
		}
		z = z->parent;
	}//이상이 있는 부분 확인
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
	//x,y,z노드 결정
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
		}//왼쪽 오른쪽으로 이동
		if (!isInternal(z)) {
			zs = reduce(z);
		}//z와 w노드 지우는 작업 개시
		else {
			BTnode *y = inordersucc(w);//중위순회 후계자 찾기
			if (y != NULL) {
				w->key = y->key;
				z = y->left;//y는 가장 작은 값이니까 오른쪽에 값이 남아있을 수 있기 때문에 왼쪽으로 지정
				zs = reduce(z);
			}//오른쪽 부트리에서 가장 작은 값을 찾았을 경우
			else {
				y = inordersucc2(w);
				w->key = y->key;
				z = y->right;
				zs = reduce(z);
			}//못 찾았을 경우 왼쪽 부트리 중 가장 큰 값 선택
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
}//내부노드면서 널 값이 아니면 전위순회로 출력

void Print() {
	preorder(tree->root);
	printf("\n");
}//출력 함수

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
			break;//i 입력 후 K값 입력 시 삽입 실행
		case'd':
			scanf("%d", &K), getchar();
			RemoveKey(K);
			break;//d와 K값 입력 시 삭제 실행
		case's':
			scanf("%d", &K), getchar();
			SearchKey(K);
			break;//s와 K값 입력 시 찾기 실행
		case'p':
			Print();
			break;//p 입력 시 전위순회 출력 실행
		}
	} while (ch != 'q');
	return 0;
}