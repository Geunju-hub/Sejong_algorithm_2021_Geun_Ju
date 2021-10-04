#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *arr, n, k1, k2;//�������� ����

int upperbound(int start, int end, int k) {
    if (start <= end) {
        int mid = (start + end) / 2;
        if (arr[mid] <= k) {
            return upperbound(mid + 1, end, k);
        }
        else {
            return upperbound(start, mid - 1, k);
        }
    }
    return end;
}//���� ���ϱ�

int lowerbound(int start, int end, int k) {
    if (start <= end) {
        int mid = (start + end) / 2;
        if (arr[mid] < k) {
            return lowerbound(mid + 1, end, k);
        }
        else {
            return lowerbound(start, mid - 1, k);
        }
    }
    return start;
}//���� ���ϱ�

int main(void) {
    scanf("%d %d %d", &n, &k1, &k2);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }//�Է�
    int a = lowerbound(0, n - 1, k1);//k1�� ���� �ε��� ���ϱ�
    int b = upperbound(0, n - 1, k2);//k2�� ���� �ε��� ���ϱ�
    if (a > b) {
        printf(" -1");
    }//���� ���̸� -1���
    for (int i = a; i <= b; i++) {
        printf(" %d", i);
    }//���� ���̸� ���� ���
    free(arr); //�޸� ����
    return 0;
}