#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int a, b, k;
char *str;

int main(void) {
	scanf("%d %d %d", &a, &b, &k);//a,b,k입력
	str = (char *)malloc((k + 1) * sizeof(char));//널문자 포함한 문자열 생성
	scanf("%s", str);
	int start=a,end=b,size = strlen(str);//a는 시작점 , b는 끝점, size는 문자열 str의 길이
	for (int i = 0; i < size; i++) {
		int mid = (start + end) / 2;//중앙값 찾기
		if (str[i] == 'Y') {
			start = mid + 1;
		}//중앙값보다 크다면 start값 변경
		else {
			end = mid;
		}//중앙값보다 작거나 같다면 end값 변경
	}//문자열 길이만큼 반복 : 결과값은 항상 고정이기 때문
	printf("%d", start);
	free(str);//메모리 해제
	return 0;
}