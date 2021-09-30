#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *arr,n,k;
int maxindex;//전역변수 선언

void binarysearch(int start, int end) {
	if (start <= end) {
		int mid = (start + end) / 2;//중앙값 index찾기
		if (arr[mid] <= k) {
			if (maxindex < mid) {
				maxindex = mid;
			}//최댓값 인덱스 수정
			binarysearch(mid+1,end);//재귀적으로 함수 실행
		}//비교해서 조건 만족하면
		else {
			binarysearch(start, mid-1);//재귀적으로 함수 실행
		}
	}//시작점과 끝점 비교해서 조건 만족시 실행
}

int main(void) {
	scanf("%d %d", &n, &k);
	arr = (int *)calloc(n, sizeof(int));
	maxindex = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}//배열 입력받기
	binarysearch(0, n - 1);
	printf("%d", maxindex);//maxindex출력
	return 0;
}