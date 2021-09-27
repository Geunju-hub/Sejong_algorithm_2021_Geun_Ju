#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int *B;//���� ���Ŀ� ���� �ӽ� �迭

int findPivot(int *arr, int left, int right) {
	return rand() % (right - left + 1) + left;
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

void Tquicksort(int *arr, int left, int right) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	quicksort(arr, left, right);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("time: %.09fms\n", (1000*(double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}//������ �ð����� �Լ�

void merge(int *arr, int left, int mid, int right) {
	int i = left, j = mid+1;
	int k = left;
	while (i <= mid && j<=right) {
		if (arr[i] <= arr[j]) {
			B[k++] = arr[i++];
		}
		else {
			B[k++] = arr[j++];
		}
	}
	while (i <= mid) {
		B[k++] = arr[i++];
	}
	while (j <= right) {
		B[k++] = arr[j++];
	}
	for (int k = left; k <= right; k++) {
		arr[k] = B[k];
	}
}//���� ����

void mergesort(int *arr, int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		mergesort(arr, left, mid);
		mergesort(arr, mid + 1, right);
		merge(arr, left, mid,right);
	}
}//�������� 

void Tmergesort(int *arr, int left, int right) {
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;

	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	mergesort(arr, left, right);
	QueryPerformanceCounter(&end);

	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("time: %.09fms\n", (1000*(double)diff.QuadPart / (double)ticksPerSec.QuadPart));
}//�������� �ð������Լ�

int main(void) {
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	int *q_arr = (int *)calloc(n, sizeof(int));
	int *m_arr = (int *)calloc(n, sizeof(int));
	B = (int *)calloc(n, sizeof(int));
	//�����Ŀ� �̿��� q_arr �迭, �������Ŀ� �̿��� m_arr,B�迭 �����Ҵ�
	for (int i = 0; i < n; i++) {
		unsigned int e = rand()%n;
		q_arr[i] = e;
		m_arr[i] = e;
	}
	//�����Լ� �̿��Ͽ� �� �迭�� ������ ������ �ֱ�
	Tmergesort(m_arr, 0, n - 1);
	Tquicksort(q_arr, 0, n - 1);
	//�����İ� �������� ����
	free(q_arr);
	free(m_arr);
	free(B);//�� �迭 �޸� ����
	return 0;
}