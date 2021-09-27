#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <time.h>

int findPivot(int *arr, int left, int right) {
	srand(time(NULL));
	return rand() % (right-left + 1) + left;
}//random���� pivot �̱� (���� left~right) �����ϱ�

int partition(int *arr, int left, int right, int k) {
	int p = arr[k];
	int tmp = arr[k];
	arr[k] = arr[right];
	arr[right] = tmp;
	int i = left, j = right - 1;
	while (i <= j) {
		while (i <= j && arr[i] <= p) {
			i++;
		}
		while (j >= i && arr[j] >= p) {
			j--;
		}
		if (i < j) {
			int tmp2 = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp2;
		}
	}
	tmp = arr[i];
	arr[i] = arr[right];
	arr[right] = tmp;
	return i;
}//�հ� �ں��� index�̵��ϸ� ����(�ߺ�Ű ���)

void quicksort(int *arr, int left, int right) {
	if (left < right) {
		int k = findPivot(arr, left, right);
		int a = partition(arr, left, right, k);
		quicksort(arr, left, a - 1);
		quicksort(arr, a + 1, right);
	}
}//������

int main(void) {
	int n;
	scanf("%d", &n);
	int *arr = (int *)calloc(n, sizeof(int));
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	quicksort(arr, 0, n - 1);
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}