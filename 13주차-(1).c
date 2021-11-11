#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m;//���� ��, ���� �� �������� ����
#define INF 100*1000+1

typedef struct inform {
	int v;
	int weight;
}inform;

typedef struct Heap {
	inform heap[1001];
	int heapsize;
}heap;

typedef struct edge {
	int start_vertex;
	int end_vertex;
	int weight;
}edge;//���� ����ü

typedef struct incident {
	edge *E;
	struct incident *next;
}incident;//��������Ʈ ����ü

typedef struct vertex {
	int vertex;
	incident *Head;
}vertex;//���� ����ü

typedef struct Graph {
	vertex V[101];
	edge E[1000];
	int edgesize;
}graph;//�׷��� ����ü

graph *G;
heap *H;//�������� ����

incident *getinode() {
	incident *newnode = (incident *)malloc(sizeof(incident));
	newnode->next = NULL;
	return newnode;
}//��������Ʈ �� ��� ���� �Լ�

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	G->edgesize = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		G->V[i].vertex = i;
		G->V[i].Head = getinode();
	}
}//�׷��� �ʱ�ȭ �Լ�

int opposite(int v, edge *E) {
	if (E->start_vertex == v) {
		return E->end_vertex;
	}
	else {
		return E->start_vertex;
	}
}//������ �ݴ��� ���� ���ϴ� �Լ�

void addEdge(int u, int v,int w) {
	G->E[G->edgesize].start_vertex = u;
	G->E[G->edgesize].end_vertex = v;
	G->E[G->edgesize].weight = w;
	incident *newnode = getinode();
	newnode->E = G->E + G->edgesize;
	newnode->next = G->V[u].Head->next;
	G->V[u].Head->next = newnode;
	if (u != v) {
		incident *newnode2 = getinode();
		newnode2->E = G->E + G->edgesize;
		newnode2->next = G->V[v].Head->next;
		G->V[v].Head->next = newnode2;
	}
	G->edgesize++;
}//������ ���� �߰� �Լ�

void Make_Graph() {
	int u, v,w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v,&w);
		addEdge(u, v,w);
	}
}//�׷��� ���� �Լ�

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->heapsize = 0;
}//�� �ʱ�ȭ �Լ�

void upHeap(int i) {
	while (i > 1) {
		if (H->heap[i].weight < H->heap[i / 2].weight) {
			inform tmp = H->heap[i];
			H->heap[i] = H->heap[i / 2];
			H->heap[i / 2] = tmp;
		}
		i /= 2;
	}
}//�켱���� 1 ����ġ

void addHeap(int v, int weight) {
	H->heapsize++;
	H->heap[H->heapsize].v = v;
	H->heap[H->heapsize].weight = weight;
	upHeap(H->heapsize);
}//upHeap �Լ�

void downHeap(int i) {
	while (2 * i <= H->heapsize) {
		int child = 2 * i;
		if (child + 1 <= H->heapsize && H->heap[child].weight>H->heap[child+1].weight) {
			child++;
		}
		if (H->heap[i].weight > H->heap[child].weight) {
			inform tmp = H->heap[i];
			H->heap[i] = H->heap[child];
			H->heap[child] = tmp;
		}
		i = child;
	}
}//downHeap �Լ�

inform removeMin() {
	inform res = H->heap[1];
	H->heap[1] = H->heap[H->heapsize--];
	downHeap(1);
	return res;
}//������ ���� ���� �� ���ְ� ����

int iscontained(int z) {
	for (int i = 1; i <= H->heapsize; i++) {
		if (H->heap[i].v == z) {
			return 1;
		}
	}
	return 0;
}//���� ���ԵǾ��ִ��� Ȯ���ϴ� �Լ�

void replaceKey(int z, int w) {
	for (int i = 1; i <= H->heapsize; i++) {
		if (H->heap[i].v == z) {
			H->heap[i].weight = w;
			upHeap(i);
			break;
		}
	}
}//�ش� ������ ����ġ �� ���� �� �� ����

void Prim_algorithm() {
	Init_Heap();//�� ����ü �ʱ�ȭ
	int *dist = (int *)calloc(n + 1, sizeof(int));
	edge *parent = (edge *)calloc(n + 1, sizeof(edge));
	int total=0;//��¹迭�� ��¹迭 �ε���
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}//1. ��� �ʱ�ȭ + �湮���� 0���� �ʱ�ȭ
	dist[1] = 0;
	//2. ����� �ּҺ�� �ʱ�ȭ
	for (int i = 1; i <= n; i++) {
		addHeap(i, dist[i]);
	}
	//2. ���� �� ������� 
	while (H->heapsize!=0) {
		inform Min = removeMin();//����ġ ���� ���� �� ����
		printf(" %d", Min.v);
		for (incident *traverse = G->V[Min.v].Head->next; traverse != NULL; traverse = traverse->next) {
			int z = opposite(Min.v, traverse->E);//������ �ݴ��� ���Ҹ� ã��
			if (iscontained(z) && traverse->E->weight < dist[z]) {
				dist[z] = traverse->E->weight;
				parent[z] = *(traverse->E);
				replaceKey(z, dist[z]);
			}//����ġ�� �� �۰� �������� ��, ť�� �� ������ �������ش�
		}//Min.v�� ��������Ʈ�� ��� �湮�ϸ鼭
	}//���� ���Ұ� ���� ������
	for (int i = 1; i <= n; i++) {
		total += dist[i];
	}//����ġ�� �� �� ���
	printf("\n%d", total);//���
	free(dist);
	free(parent);
	free(H);//�޸� ����
}

int main(void) {
	Init_Graph();
	Make_Graph();
	Prim_algorithm();
	return 0;
}