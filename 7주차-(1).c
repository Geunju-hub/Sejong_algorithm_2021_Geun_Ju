#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //bool자료형 사용을 위한 stdbool 헤더 추가

typedef struct BTnode {
	int key;
	struct BTnode *parent;
	struct BTnode *left;
	struct BTnode *right;
}BTnode;//이진트리 노드 구조체

typedef struct BT {
	BTnode *root;
}BT;//이진트리 구조체 

BT *tree;//전역변수로 선언

bool isInternal(BTnode *v) {
	return v->left != NULL || v->right != NULL;
}//내부노드인지 확인하는 함수

bool isExternal(BTnode *v) {
	return v->left == NULL && v->right == NULL;
}//외부노드인지 확인하는 함수

BTnode *getBTnode(BTnode *P) {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->key = 0;
	newnode->parent = P;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}//이진트리노드 생성 후 부모노드와 연결

void Init_BTtree() {
	tree = (BT *)malloc(sizeof(BT));
	tree->root = NULL;
}//이진탐색트리 초기화 함수

BTnode *search(BTnode *v, int k) {
	if (isExternal(v)) {
		return v;
	}//외부노드면 해당 장소 반환 -> 여기에 키값 붙일 예정
	if (v->key == k) {
		return v;
	}//해당 키가 있다면 장소 반환 -> 새로 삽입 x
	else if (v->key > k) {
		return search(v->left, k);
	}//크면 작은쪽으로 찾아가야하므로 왼쪽으로 재귀
	else {
		return search(v->right, k);
	}//반대면 오른쪽으로 재귀
}//탐색 함수


void Insert(int k) {
	if (tree->root == NULL) {
		tree->root = getBTnode(NULL);
		tree->root->key = k;
		tree->root->left = getBTnode(tree->root);
		tree->root->right = getBTnode(tree->root);
	}//루트 노드가 널이면 갱신
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
	}//루트 노드가 널이 아니면 찾아서 갱신
}

void Search(int k) {
	BTnode *tmp = search(tree->root, k);
	if (isExternal(tmp)) {
		printf("X\n");
	}
	else {
		printf("%d\n", tmp->key);
	}
}//탐색 후 있으면 그 값을 없으면 X출력 함수

BTnode *inordersucc(BTnode *v) {
	BTnode *z = v;
	while (isInternal(z->left)) {
		z = z->left;
	}
	return z;
}//중위순회 후계자 찾기 (오른쪽 부트리 중 가장 작은 값)

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
}//자식노드와 부모노드 같이 삭제 후 자식의 형제와 새 부모노드 연결

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
}//삭제함수

void preorder(BTnode *v) {
	if (isInternal(v)) {
		printf(" %d", v->key);
		preorder(v->left);
		preorder(v->right);
	}
}//전위순회 함수(재귀 이용)

void Print() {
	preorder(tree->root);
	printf("\n");
}//출력 후 개행

int main(void) {
	BTnode *tmp=NULL;
	Init_BTtree();
	int k;
	char ch;
	do {
		scanf("%c", &ch), getchar();//입력 후 엔터는 getchar로 지우기
		switch (ch) {
		case'i':
			scanf("%d", &k), getchar();//키 입력 후 엔터 제거
			Insert(k);//삽입 함수
			break;
		case'd':
			scanf("%d", &k), getchar();//키 입력 후 엔터 제거
			Remove(k);//삭제 함수
			break;
		case's':
			scanf("%d", &k), getchar();//키 입력 후 엔터 제거
			Search(k);//찾기 함수
			break;
		case'p':
			Print();//출력 함수
			break;
		}//ch는 아스키코드(정수)로 표현 가능하므로 switch문 사용 가능
	} while (ch != 'q');//종료 전까지 계속
	return 0;
}