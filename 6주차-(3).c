#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int a, b, k;
char *str;

int main(void) {
	scanf("%d %d %d", &a, &b, &k);//a,b,k�Է�
	str = (char *)malloc((k + 1) * sizeof(char));//�ι��� ������ ���ڿ� ����
	scanf("%s", str);
	int start=a,end=b,size = strlen(str);//a�� ������ , b�� ����, size�� ���ڿ� str�� ����
	for (int i = 0; i < size; i++) {
		int mid = (start + end) / 2;//�߾Ӱ� ã��
		if (str[i] == 'Y') {
			start = mid + 1;
		}//�߾Ӱ����� ũ�ٸ� start�� ����
		else {
			end = mid;
		}//�߾Ӱ����� �۰ų� ���ٸ� end�� ����
	}//���ڿ� ���̸�ŭ �ݺ� : ������� �׻� �����̱� ����
	printf("%d", start);
	free(str);//�޸� ����
	return 0;
}