#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

char ch;
int heap[101] = { 0, };
int n = 0, k;

void upHeap(int n) {
	if (n <= 1) {
		return;
	}
	if (heap[n] > heap[n / 2]) {
		int tmp = heap[n];
		heap[n] = heap[n / 2];
		heap[n / 2] = tmp;
	}
	upHeap(n / 2);
}

void downHeap(int i) {
	if (2 * i <= n) {
		int child = 2 * i;
		if (child + 1 <= n && heap[child] < heap[child + 1]) {
			child++;
		}
		if (heap[i] < heap[child]) {
			int tmp = heap[i];
			heap[i] = heap[child];
			heap[child] = tmp;
		}
		downHeap(child);
	}
}

void insertItem() {
	heap[++n] = k;
	upHeap(n);
	printf("0\n");
}

void removeItem() {
	printf("%d\n", heap[1]);
	heap[1] = heap[n];
	heap[n--] = 0;
	downHeap(1);
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", heap[i]);
	}
	printf("\n");
}

int main(void) {
	do {
		scanf("%c", &ch), getchar();
		switch (ch) {
		case'i':
			scanf("%d", &k), getchar();
			insertItem();
			break;
		case'd':
			removeItem();
			break;
		case'p':
			printHeap();
			break;
		}
	} while (ch != 'q');
	return 0;
}