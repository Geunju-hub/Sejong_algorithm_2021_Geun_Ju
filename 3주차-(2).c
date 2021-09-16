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

void BuildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
}

int main(void) {
	int size;
	scanf("%d", &size);
	n = size;
	for (int i = 1; i <= size; i++) {
		scanf("%d", &heap[i]);
	}
	BuildHeap();
	printHeap();
	return 0;
}