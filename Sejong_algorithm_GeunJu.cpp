#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BTnode {
	int key;
	struct BTnode *parent;
	struct BTnode *left;
	struct BTnode *right;
}BTnode;

typedef struct Qnode {
	BTnode *element;
	struct Qnode *next;
}Qnode;

typedef struct Queue {
	Qnode *front;
	Qnode *rear;
}queue;

BTnode *root,*last;
queue *Q;

bool isExternal(BTnode *v) {
	return v->left == NULL && v->right == NULL;
}

bool isInternal(BTnode *v) {
	return v->left != NULL || v->right != NULL;
}

void Init_Queue() {
	Q = (queue *)malloc(sizeof(queue));
	Q->front = NULL;
	Q->rear = NULL;
}

Qnode *getQnode(BTnode *v) {
	Qnode *newnode = (Qnode *)malloc(sizeof(Qnode));
	newnode->element = v;
	newnode->next = NULL;
	return newnode;
}

BTnode *getBTnode(BTnode *P) {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->parent = P;
	newnode->key = 0;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

void enqueue(BTnode *v) {
	Qnode *newnode = getQnode(v);
	if (Q->front == NULL) {
		Q->front = newnode;
		Q->rear = newnode;
	}
	else {
		Q->rear->next = newnode;
		Q->rear = newnode;
	}
}

BTnode *dequeue() {
	BTnode *res;
	Qnode *F;
	if (Q->front == NULL) {
		return NULL;
	}
	res = Q->front->element;
	F = Q->front;
	Q->front = Q->front->next;
	free(F);
	return res;
}

void renewLast(BTnode *v) {
	while (v->parent != NULL && v->parent->right == v) {
		v = v->parent;
	}
	if (v->parent != NULL && v->parent->left == v) {
		v = v->parent->right;
	}
	while (isInternal(v)) {
		v = v->left;
	}
	last = v;
}

void upHeap(BTnode *v) {
	while (v != root) {
		if (v->key > v->parent->key) {
			int tmp = v->key;
			v->key = v->parent->key;
			v->parent->key = tmp;
		}
		v = v->parent;
	}
}

void downHeap(BTnode *v) {
	if (isExternal(v->left) && isExternal(v->right)) {
		return;
	}
	BTnode *child = v->left;
	if (isInternal(v->right) && child->key < v->right->key) {
		child = v->right;
	}
	if (child->key > v->key) {
		int tmp = v->key;
		v->key = child->key;
		child->key = tmp;
	}
	downHeap(child);
}

void insertItem(int K) {
	renewLast(last);
	last->key = K;
	last->left = getBTnode(last);
	last->right = getBTnode(last);
	upHeap(last);
	printf("0\n");
}

void reduce(BTnode *z) {
	BTnode *w = z->parent;
	BTnode *zs = w->left == z ? w->right : z->left;
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

void retreatLast(BTnode *v) {
	while (v->parent != NULL && v->parent->left == v) {
		v = v->parent;
	}
	if (v->parent != NULL && v->parent->right == v) {
		v = v->parent->left;
	}
	while (v->left!=NULL) {
		v = v->right;
	}
	last = v->parent;
}

void removeMAX() {
	if (root->key == 0) {
		return;
	}
	printf("%d\n", root->key);
	root->key = last->key;
	BTnode *z = last->left;
	retreatLast(last);
	reduce(z);
	downHeap(root);
	//줄이는 과정 + downHeap
}

void print_LevelOrder() {
	Init_Queue();
	enqueue(root);
	while (1) {
		BTnode *tmp = dequeue();
		if (tmp == NULL) {
			break;
		}
		else {
			if (tmp->key != 0) {
				printf(" %d", tmp->key);
			}
			if (tmp->left!=NULL && isInternal(tmp->left)) {
				enqueue(tmp->left);
			}
			if (tmp->left!=NULL &&isInternal(tmp->right)) {
				enqueue(tmp->right);
			}
		}
	}
	printf("\n");
	free(Q);
}

int main(void) {
	root = getBTnode(NULL), last = root;
	int K;
	char ch;
	do {
		scanf("%c", &ch), getchar();
		switch (ch) {
		case'i':
			scanf("%d", &K),getchar();
			insertItem(K);
			break;
		case'd':
			removeMAX();
			break;
		case'p':
			print_LevelOrder();
			break;
		}
	} while (ch != 'q');
	return 0;
}