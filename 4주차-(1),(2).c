#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int N;

typedef struct Node {
	int element;
	struct Node *next;
}node;

typedef struct List {
	node *Head;
}list;

typedef struct BTnode {
	int key;
	struct BTnode *parent;
	struct BTnode *left;
	struct BTnode *right;
}BTnode;

BTnode *root,*last;
list *L;

bool isExternal(BTnode *v) {
	return v->left == NULL && v->right == NULL;
}

bool isInternal(BTnode *v) {
	return v->left != NULL || v->right != NULL;
}

node *getnode(int e) {
	node *newnode = (node *)malloc(sizeof(node));
	newnode->element = e;
	newnode->next = NULL;
	return newnode;
}

BTnode *getBTnode(BTnode *P) {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->parent = P;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->key = 0;
	return newnode;
}

void Init_List() {
	L = (list *)malloc(sizeof(list));
	L->Head = NULL;
}

void addLast(int e) {
	node *newnode = getnode(e);
	if (L->Head == NULL) {
		L->Head = newnode;
	}
	else {
		node *tmp = L->Head;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = newnode;
	}
}


void Make_List() {
	Init_List();
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		int e;
		scanf("%d", &e);
		addLast(e);
	}
}

void Make_Heap() {
	root = getBTnode(NULL), last = root;
}

void renewLast() {
	BTnode *z = last;
	while (z->parent != NULL && z->parent->right == z) {
		z = z->parent;
	}
	if (z->parent != NULL && z->parent->left == z) {
		z = z->parent->right;
	}
	while (z->left != NULL) {
		z = z->left;
	}
	last = z;
}

void upHeap(BTnode *v) {
	if (v == root) {
		return;
	}
	else {
		if (v->key < v->parent->key) {
			int tmp = v->key;
			v->key = v->parent->key;
			v->parent->key = tmp;
		}
		upHeap(v->parent);
	}
}

void downHeap(BTnode *v) {
	if (v->key == 0) {
		return;
	}
	if (isExternal(v->left)&&isExternal(v->right)) {
		return;
	}
	else {
		BTnode *child = v->left;
		if (isInternal(v->right) && v->right->key < child->key) {
			child = v->right;
		}
		if (child->key < v->key) {
			int tmp = child->key;
			child->key = v->key;
			v->key = tmp;
		}
		downHeap(child);
	}
}

void InsertKey(node *N) {
	int k = N->element;
	node *F = L->Head;
	L->Head = L->Head->next;
	free(F);
	renewLast();
	last->key = k;
	last->left = getBTnode(last);
	last->right = getBTnode(last);
	upHeap(last);
}

void retreatLast() {
	BTnode *z = last;
	while (z->parent != NULL && z->parent->left == z) {
		z = z->parent;
	}
	if (z->parent != NULL && z->parent->right == z) {
		z = z->parent->left;
	}
	while (isInternal(z->left) && isInternal(z->right)) {
		z = z->right;
	}
	last = z;
}

void reduce(BTnode *z) {
	BTnode *w = z->parent;
	BTnode *zs = w->left == z ? w->right : w->left;
	if (w == root) {
		root = zs;
		zs->parent = NULL;
		last = zs;
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
	free(w);
}

int removeMin() {
	int res = root->key;
	root->key = last->key;
	BTnode *z = last->right;
	retreatLast();
	reduce(z);
	downHeap(root);
	return res;
}

void Heapsort() {
	Make_Heap();
	for (int i = 0; i < N; i++) {
		InsertKey(L->Head);
	}//리스트 원소 제거 및 힙에 원소 추가
	for (int i = 0; i < N; i++) {
		int e = removeMin();
		addLast(e);
	}
}

void printList() {
	for (node *tmp = L->Head; tmp != NULL; tmp = tmp->next) {
		printf(" %d", tmp->element);
	}
}

int main(void) {
	Make_List();
	Heapsort();
	printList();
	return 0;
}