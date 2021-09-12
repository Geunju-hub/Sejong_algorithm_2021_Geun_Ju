#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

int N, M;

typedef struct vnode {
	char vertex;
	int indegree;
	struct vnode *next;
}vnode;

typedef struct Graph {
	vnode *adj_list[MAX_VERTEX];
}graph;

graph *G;
vnode *queue[MAX_VERTEX + 1];
int front = 0, rear = 0;

void enqueue(vnode *V) {
	rear = (rear + 1) % (N + 1);
	queue[rear] = V;
}

vnode *dequeue() {
	front = (front + 1) % (N + 1);
	return queue[front];
}

vnode *getVnode(char v) {
	vnode *newnode = (vnode *)malloc(sizeof(vnode));
	newnode->indegree = 0;
	newnode->vertex = v;
	newnode->next = NULL;
	return newnode;
}

void addEdge(char u, char v) {
	for (int i = 0; i < N; i++) {
		if (G->adj_list[i]->vertex == v) {
			G->adj_list[i]->indegree++;
		}
		if (G->adj_list[i]->vertex == u) {
			vnode *newnode = getVnode(v);
			newnode->next = G->adj_list[i]->next;
			G->adj_list[i]->next = newnode;
		}
	}
}

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	scanf("%d", &N), getchar();
	for (int i = 0; i < N; i++) {
		char v;
		scanf("%c", &v), getchar();
		G->adj_list[i] = getVnode(v);
	}
}

void Make_Graph() {
	scanf("%d", &M), getchar();
	for (int i = 0; i < M; i++) {
		char u, v;
		scanf("%c %c", &u, &v), getchar();
		addEdge(u, v);
	}
}

int find(char v) {
	for (int i = 0; i < N; i++) {
		if (G->adj_list[i]->vertex == v) {
			return i;
		}
	}
}

void topologicalsort() {
	char res[100+1] = { 0, };
	int cnt = 0;
	for (int i = 0; i < N; i++) {
		if (G->adj_list[i]->indegree == 0) {
			enqueue(G->adj_list[i]);
		}
	}
	while (front != rear) {
		vnode *tmp = dequeue();
		res[cnt++] = tmp->vertex;
		vnode *traverse = tmp->next;
		while (traverse != NULL) {
			int idx = find(traverse->vertex);
			G->adj_list[idx]->indegree--;
			if (G->adj_list[idx]->indegree == 0) {
				enqueue(G->adj_list[idx]);
			}
			traverse = traverse->next;
		}
	}
	if (cnt != N) {
		printf("0");
	}
	else {
		for (int i = 0; i < cnt; i++) {
			printf("%c ", res[i]);
		}
	}
}

int main(void) {
	Init_Graph();
	Make_Graph();
	topologicalsort();
	return 0;
}