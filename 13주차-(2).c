#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define INF 100*1000+1
int n, m;//정점 수, 간선 수 전역변수 설정
int dist[101];//가중치 배열 선언
int parent[101];//분리집합에 이용할 전역변수 배열

typedef struct edge {
	int start_vertex;
	int end_vertex;
	int weight;
}edge;//간선 구조체

typedef struct vertex {
	int vertex;
}vertex;//정점 구조체

typedef struct graph {
	vertex V[101];
	edge E[1000];
	int edgesize;
}graph;//그래프 구조체

typedef struct Heap {
	edge heap[1000];
	int heapsize;
}heap;

graph *G;
heap *H;

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	G->edgesize = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		G->V[i].vertex = i;
	}
}//그래프 초기화 함수

void addEdge(int u, int v, int w) {
	G->E[G->edgesize].start_vertex = u;
	G->E[G->edgesize].end_vertex = v;
	G->E[G->edgesize].weight = w;
	//1. 간선리스트에 추가
	G->edgesize++;
}//무방향 간선 추가

void Make_Graph() {
	int u, v, w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v, &w);
		addEdge(u, v, w);
	}
}//그래프 생성 함수

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->heapsize = 0;
}

void upHeap(int i) {
	while (i > 1) {
		if (H->heap[i].weight < H->heap[i / 2].weight) {
			edge tmp = H->heap[i];
			H->heap[i] = H->heap[i / 2];
			H->heap[i / 2] = tmp;
		}
		i /= 2;
	}
}

void downHeap(int i) {
	while (2 * i <= H->heapsize) {
		int child = 2 * i;
		if (child + 1 <= H->heapsize && H->heap[child].weight > H->heap[child + 1].weight) {
			child++;
		}
		if (H->heap[i].weight > H->heap[child].weight) {
			edge tmp = H->heap[i];
			H->heap[i] = H->heap[child];
			H->heap[child] = tmp;
		}
		i = child;
	}
}

void addHeap(edge *E) {
	H->heapsize++;
	H->heap[H->heapsize] = *E;
	upHeap(H->heapsize);
}

edge removeMin() {
	edge res = H->heap[1];
	H->heap[1] = H->heap[H->heapsize--];
	downHeap(1);
	return res;
}

int find(int a) {
	if (parent[a] == a) {
		return a;
	}
	else {
		return parent[a] = find(parent[a]);
	}
}

void Kruskal_algorithm() {
	Init_Heap();
	for (int i = 1; i <= n; i++) {
		parent[i] = i;
	}
	for (int i = 0; i < m; i++) {
		addHeap(G->E+i);
	}
	int T = 0,sum=0;
	while (T != n - 1) {
		edge Min = removeMin();
		int S = find(Min.start_vertex);
		int E = find(Min.end_vertex);
		if (S != E) {
			printf(" %d", Min.weight);
			parent[E] = Min.start_vertex;
			sum += Min.weight;
			T++;
		}
	}
	printf("\n%d", sum);
	free(H);
}//크루스칼 알고리즘 함수

int main(void) {
	Init_Graph();
	Make_Graph();
	Kruskal_algorithm();
	return 0;
}