#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int *arr, n,midx;

int Increase() {
	int fidx = n - 1;
	for (int i = 1; i < n; i++) {
		if (arr[i] < arr[i - 1]) {//���簡 ������ ������ ����
			midx = i-1;
			break;
		}
	}//���� -> ���� ���� check
	for (int i = midx+1; i < n; i++) {
		if (arr[i] > arr[i - 1]) {
			fidx = i-1;
			break;
		}
	}//����->���� ���� Ȯ��
	if (midx == n - 1) {
		return 0;
	}//�� �����ϴ� ������� 0 ��ȯ
	else {
		return (fidx == n - 1 && midx!=0) ? 1 : 0;
	}//�װ� �ƴϰ� ���߳����ϸ� 0 �ƴϸ�(���� -> ���� ���� 1����)
}

int Decrease() {
	int fidx = n - 1;
	for (int i = 1; i < n; i++) {
		if (arr[i] > arr[i - 1]) {
			midx = i-1;
			break;
		}
	}
	for (int i = midx+1; i < n; i++) {
		if (arr[i] < arr[i - 1]) {
			fidx = i-1;
			break;
		}
	}
	if (midx == n - 1) {
		return 0;
	}
	else {
		return (fidx == n - 1 && midx!=0) ? 1 : 0;
	}
}

int findMode() {
	if (Increase()) {
		return 1;
	}
	else if (Decrease()) {
		return -1;
	}
	else {
		return 0;
	}
}

int lowerbound(int start, int end, int k) {
	if (start <= end) {
		int mid = (start + end) / 2;
		if (arr[mid] >= arr[start]) {
			return lowerbound(start, mid-1, k);
		}
		else {
			return lowerbound(mid+1, end, k);
		}
	}
	return start;
}

int upperbound(int start, int end, int k) {
	if (start <= end) {
		int mid = (start + end) / 2;
		if (arr[mid] >= arr[start]) {
			return upperbound(mid + 1, end, k);
		}
		else {
			return upperbound(start, mid - 1, k);
		}
	}
	return end;
}

void binarysearch(int start, int end) {
	int mode = findMode(),idx;
	if (mode == 0) {
		printf(" 0");
		return;
	}//���� ��尡 �ƴ϶�� 0���
	else if (mode == 1) {
		idx = upperbound(0, midx,arr[midx]);
	}
	else {
		idx = lowerbound(midx, end, arr[midx]);
	}
	printf(" %d %d", mode, arr[idx]);
}

int main(void) {
	scanf("%d", &n);
	arr = (int *)calloc(n, sizeof(int));//ũ�⸸ŭ �迭 �����Ҵ�
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}//�Է�
	binarysearch(0, n - 1);
	free(arr);//�޸� ����
	return 0;
}