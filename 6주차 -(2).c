#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *arr, n, k;
int minindex;//최솟값 찾는 인덱스

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
}//이진탐색 비재귀버전

int main(void) {
	scanf("%d %d", &n, &k);
	arr = (int *)calloc(n, sizeof(int));//arr배열 크기 n만큼 동적할당
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}//입력
	minindex = n;//최소 인덱스 설정
	binarysearch(0, n - 1);
	free(arr);//메모리 해제
	printf("%d", minindex);
	return 0;
}