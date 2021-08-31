#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num, left, right; // 전역변수로 설정함으로써 함수 깔끔하게 처리

typedef struct BTnode {
	int number;
	struct BTnode *left;
	struct BTnode *right;
}BTnode;//이진트리 구조체 

BTnode *root;//전역변수로 루트 노드 포인터 생성

BTnode *getnode() {
	BTnode *newnode = (BTnode *)malloc(sizeof(BTnode));
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}//노드 생성 함수

void find_and_insert(BTnode *p) {
	if (p != NULL) {
		if (p->number == num) {
			if (left != 0) {
				p->left = getnode();
				p->left->number = left;
			}
			if (right != 0) {
				p->right = getnode();
				p->right->number = right;
			}
		}
		find_and_insert(p->left);
		find_and_insert(p->right);
	}
}//찾아서 왼쪽 오른쪽 노드 생성 과정 : 못찾으면 재귀적으로 왼쪽 오른쪽 이동하며 찾음.

void search_and_print(BTnode *p, char *str) {
	for (int i = 0; i <= strlen(str); i++) {
		printf(" %d", p->number);
		if (str[i] == 'L') {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	printf("\n");
}//훑어가면서 출력

int main(void) {
	root = getnode();
	int N, SN;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &num, &left, &right);
		if (i == 0) {
			root->number = num;
			if (left != 0) {
				root->left = getnode();
				root->left->number = left;
			}
			if (right != 0) {
				root->right = getnode();
				root->right->number = right;
			}
		}
		else {
			find_and_insert(root);
		}
	}
	scanf("%d", &SN);
	for (int i = 0; i < SN; i++) {
		char str[101] = { '\0' };
		scanf("%s", str);
		search_and_print(root, str);
	}
	return 0;
}