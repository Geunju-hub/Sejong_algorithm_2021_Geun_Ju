#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int n, m;//정점 수, 간선 수 전역변수 설정
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
}edge;//간선 구조체

typedef struct incident {
	edge *E;
	struct incident *next;
}incident;//인접리스트 구조체

typedef struct vertex {
	int vertex;
	incident *Head;
}vertex;//정점 구조체

typedef struct Graph {
	vertex V[101];
	edge E[1000];
	int edgesize;
}graph;//그래프 구조체

graph *G;
heap *H;//전역변수 선언

incident *getinode() {
	incident *newnode = (incident *)malloc(sizeof(incident));
	newnode->next = NULL;
	return newnode;
}//인접리스트 새 노드 갱신 함수

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	G->edgesize = 0;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		G->V[i].vertex = i;
		G->V[i].Head = getinode();
	}
}//그래프 초기화 함수

int opposite(int v, edge *E) {
	if (E->start_vertex == v) {
		return E->end_vertex;
	}
	else {
		return E->start_vertex;
	}
}//간선의 반대쪽 정점 구하는 함수

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
}//무방향 간선 추가 함수

void Make_Graph() {
	int u, v,w;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &u, &v,&w);
		addEdge(u, v,w);
	}
}//그래프 생성 함수

void Init_Heap() {
	H = (heap *)malloc(sizeof(heap));
	H->heapsize = 0;
}//힙 초기화 함수

void upHeap(int i) {
	while (i > 1) {
		if (H->heap[i].weight < H->heap[i / 2].weight) {
			inform tmp = H->heap[i];
			H->heap[i] = H->heap[i / 2];
			H->heap[i / 2] = tmp;
		}
		i /= 2;
	}
}//우선순위 1 가중치

void addHeap(int v, int weight) {
	H->heapsize++;
	H->heap[H->heapsize].v = v;
	H->heap[H->heapsize].weight = weight;
	upHeap(H->heapsize);
}//upHeap 함수

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
}//downHeap 함수

inform removeMin() {
	inform res = H->heap[1];
	H->heap[1] = H->heap[H->heapsize--];
	downHeap(1);
	return res;
}//힙에서 가장 작은 값 빼주고 갱신

int iscontained(int z) {
	for (int i = 1; i <= H->heapsize; i++) {
		if (H->heap[i].v == z) {
			return 1;
		}
	}
	return 0;
}//힙에 포함되어있는지 확인하는 함수

void replaceKey(int z, int w) {
	for (int i = 1; i <= H->heapsize; i++) {
		if (H->heap[i].v == z) {
			H->heap[i].weight = w;
			upHeap(i);
			break;
		}
	}
}//해당 원소의 가중치 값 갱신 후 힙 갱신

void Prim_algorithm() {
	Init_Heap();//힙 구조체 초기화
	int *dist = (int *)calloc(n + 1, sizeof(int));
	edge *parent = (edge *)calloc(n + 1, sizeof(edge));
	int total=0;//출력배열과 출력배열 인덱스
	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
	}//1. 비용 초기화 + 방문여부 0으로 초기화
	dist[1] = 0;
	//2. 출발점 최소비용 초기화
	for (int i = 1; i <= n; i++) {
		addHeap(i, dist[i]);
	}
	//2. 전부 다 집어넣음 
	while (H->heapsize!=0) {
		inform Min = removeMin();//가중치 제일 작은 값 빼줌
		printf(" %d", Min.v);
		for (incident *traverse = G->V[Min.v].Head->next; traverse != NULL; traverse = traverse->next) {
			int z = opposite(Min.v, traverse->E);//간선의 반대쪽 원소를 찾고
			if (iscontained(z) && traverse->E->weight < dist[z]) {
				dist[z] = traverse->E->weight;
				parent[z] = *(traverse->E);
				replaceKey(z, dist[z]);
			}//가중치가 더 작게 갱신해준 후, 큐에 그 값으로 갱신해준다
		}//Min.v의 인접리스트를 모두 방문하면서
	}//힙에 원소가 없을 때까지
	for (int i = 1; i <= n; i++) {
		total += dist[i];
	}//가중치의 총 합 계산
	printf("\n%d", total);//출력
	free(dist);
	free(parent);
	free(H);//메모리 해제
}

int main(void) {
	Init_Graph();
	Make_Graph();
	Prim_algorithm();
	return 0;
}