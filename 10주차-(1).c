#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
	int start_vertex;
	int end_vertex;
	int weight;
}edge;
/*
typedef struct incident {
	edge *E;
	struct incident *next;
}incident;*/

typedef struct Vnode {
	int vertex;
	//incident *Head;
}vnode;

typedef struct Graph {
	vnode *Vertex[7];//index의 효율성을 위해 7로 설정
	edge *Edge[21];
	int Edgesize;
	int adj_matrix[7][7];
}graph;

graph *G;

edge *getenode(int u, int v, int w) {
	edge *newnode = (edge *)malloc(sizeof(edge));
	newnode->start_vertex = u;
	newnode->end_vertex = v;
	newnode->weight = w;
	return newnode;
}

/*
incident *getinode() {
	incident *newnode = (incident *)malloc(sizeof(incident));
	newnode->next = NULL;
	return newnode;
}*/

void Init_Graph() {
	G = (graph *)malloc(sizeof(graph));
	G->Edgesize = 0;
	for (int i = 1; i <= 6; i++) {
		G->Vertex[i] = (vnode *)malloc(sizeof(vnode));
		G->Vertex[i]->vertex = i;
		for (int j = 1; j <= 6; j++) {
			G->adj_matrix[i][j] = 0;
		}
		//G->Vertex[i]->Head = getinode();
		//G->Vertex[i]->Head->E = getenode(i, i, 0);//헤더노드 설정
	}
}

void Add_Edge(int u, int v, int w) {
	G->Edge[G->Edgesize] = getenode(u, v, w);
	G->adj_matrix[u][v] = G->Edge[G->Edgesize]->weight;
	G->adj_matrix[v][u] = G->Edge[G->Edgesize]->weight;
	G->Edgesize++;
}

void Modify_Edge(int u, int v, int w) {
	int flag = 0;
	for (int i = 0; i < G->Edgesize; i++) {
		if (G->Edge[i]->start_vertex == u && G->Edge[i]->end_vertex == v) {
			G->Edge[i]->weight = w;
			G->adj_matrix[u][v] = w;
			G->adj_matrix[v][u] = w;
			flag = 1;
			break;
		}
		else if (G->Edge[i]->start_vertex == v && G->Edge[i]->end_vertex == u) {
			G->Edge[i]->weight = w;
			G->adj_matrix[u][v] = w;
			G->adj_matrix[v][u] = w;
			flag = 1;
			break;
		}
	}//이미 edge가 있는 경우
	if (flag == 1) {
		return;
	}
	else {
		Add_Edge(u, v, w);
	}//없는경우
}

void Print(int n) {
	//incident *traverse = G->Vertex[n]->Head->next;
	for (int i = 1; i <= 6; i++) {
		if (G->adj_matrix[n][i] != 0) {
			printf(" %d %d", i, G->adj_matrix[n][i]);
		}
	}
	printf("\n");
}

void Make_Graph() {
	Add_Edge(1, 2, 1);
	Add_Edge(1, 3, 1);
	Add_Edge(1, 4, 1);
	Add_Edge(1, 6, 2);
	Add_Edge(2, 3, 1);
	Add_Edge(3, 5, 4);
	Add_Edge(5, 5, 4);
	Add_Edge(5, 6, 3);
	//for (int i = 1; i <= 6; i++) {
		//Print(i);
	//}
}

int FindVertex(int n) {
	for (int i = 1; i <= 6; i++) {
		if (G->Vertex[i]->vertex == n) {
			return 1;
		}
	}
	return 0;
}

int main(void) {
	Init_Graph();
	Make_Graph();
	char ch;
	int a, b, w, n;
	do {
		scanf("%c", &ch), getchar();
		switch (ch) {
		case'a':
			scanf("%d", &n), getchar();
			if (FindVertex(n)) {
				Print(n);
			}//정점 찾아서 있는 경우 출력
			else {
				printf("-1\n");
			}//없으면 -1출력
			break;
		case'm':
			scanf("%d %d %d", &a, &b, &w), getchar();
			if (FindVertex(a) && FindVertex(b)) {
				Modify_Edge(a, b, w);
			}//a,b정점이 모두 있는 경우
			else {
				printf("-1\n");
			}//없으면 -1출력
			break;
		}
	} while (ch != 'q');
	return 0;
}