#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *arr,n,k;
int maxindex;//�������� ����

void binarysearch(int start, int end) {
	if (start <= end) {
		int mid = (start + end) / 2;//�߾Ӱ� indexã��
		if (arr[mid] <= k) {
			if (maxindex < mid) {
				maxindex = mid;
			}//�ִ� �ε��� ����
			binarysearch(mid+1,end);//��������� �Լ� ����
		}//���ؼ� ���� �����ϸ�
		else {
			binarysearch(start, mid-1);//��������� �Լ� ����
		}
	}//�������� ���� ���ؼ� ���� ������ ����
}

int main(void) {
	scanf("%d %d", &n, &k);
	arr = (int *)calloc(n, sizeof(int));
	maxindex = -1;
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}//�迭 �Է¹ޱ�
	binarysearch(0, n - 1);
	printf("%d", maxindex);//maxindex���
	return 0;
}