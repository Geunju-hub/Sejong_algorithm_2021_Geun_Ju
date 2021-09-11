#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n, idx;
	scanf("%d", &n);
	int *arr = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = n - 1; i > 0; i--) {
		idx = i;
		for (int j = i - 1; j >= 0; j--) {
			if (arr[idx] < arr[j]) {
				idx = j;
			}
		}
		int tmp = arr[i];
		arr[i] = arr[idx];
		arr[idx] = tmp;
	}
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
	return 0;
}