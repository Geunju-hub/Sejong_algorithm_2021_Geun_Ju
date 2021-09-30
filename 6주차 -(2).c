#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *arr, n, k;
int minindex;//�ּڰ� ã�� �ε���

void binarysearch(int start, int end) {
	while (start <= end) {
		int mid = (start + end) / 2;
		if (arr[mid] >= k) {
			if (minindex > mid) {
				minindex = mid;
			}
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
	}
}//����Ž�� ����͹���

int main(void) {
	scanf("%d %d", &n, &k);
	arr = (int *)calloc(n, sizeof(int));//arr�迭 ũ�� n��ŭ �����Ҵ�
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}//�Է�
	minindex = n;//�ּ� �ε��� ����
	binarysearch(0, n - 1);
	free(arr);//�޸� ����
	printf("%d", minindex);
	return 0;
}