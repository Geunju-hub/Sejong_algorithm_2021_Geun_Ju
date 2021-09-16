#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findPivot(int *L, int l, int r) {
	return (l+r)/2;
}

int inPlacePartition(int *arr, int l, int r, int k) {
	int p = arr[k];
	int tmp = arr[k];
	arr[k] = arr[r];
	arr[r] = tmp;
	int i = l, j = r - 1;
	while (i <= j) {
		while (i <= j && arr[i] <= p) {
			i++;
		}
		while (j >= i && arr[j] >= p) {
			j--;
		}
		if (i < j) {
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	tmp = arr[i];
	arr[i] = arr[r];
	arr[r] = arr[i];
	return i;
}

void inPlaceQuickSort(int *arr, int l, int r) {
	if (l >= r) {
		return;
	}
	int k = findPivot(arr, l, r);
	int x= inPlacePartition(arr, l, r, k);
	inPlaceQuickSort(arr, l, x - 1);
	inPlaceQuickSort(arr, x + 1, r);
}

int main(void) {
	int n,*arr;
	scanf("%d", &n);
	arr = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	inPlaceQuickSort(arr, 0, n - 1);
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
	free(arr);
	return 0;
}