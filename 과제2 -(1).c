#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int *arr, n, k1, k2;//전역변수 선언

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
}//상한 구하기

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
}//하한 구하기

int main(void) {
    scanf("%d %d %d", &n, &k1, &k2);
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }//입력
    int a = lowerbound(0, n - 1, k1);//k1의 하한 인덱스 구하기
    int b = upperbound(0, n - 1, k2);//k2의 상한 인덱스 구하기
    if (a > b) {
        printf(" -1");
    }//범위 밖이면 -1출력
    for (int i = a; i <= b; i++) {
        printf(" %d", i);
    }//범위 안이면 범위 출력
    free(arr); //메모리 해제
    return 0;
}