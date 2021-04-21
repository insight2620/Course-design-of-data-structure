#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

typedef int Position;
#define NotFound -1

void BuildMatch(char *pattern, int *match)//�ؼ���Ԥ��������
{	
	//����pattern,��pattern��ÿһ���ַ��ó�����Ӧ��matchֵ
	Position i, j;
	int m = strlen(pattern); 
	match[0] = -1; //pattern�ĵ�һ���ַ�matchֵΪ-1

	for (j = 1; j < m; j++) 
	{
		i = match[j - 1];  //��i��� match[j - 1],��������ʾ
		while ((i >= 0) && (pattern[i + 1] != pattern[j]))
			i = match[i];  //�����ٱȽ�
		if (pattern[i + 1] == pattern[j])
			match[j] = i + 1;
		else match[j] = -1; 
	}
}

Position KMP(char *string, char *pattern) //�ַ���ģʽƥ�亯��
{
	int n = strlen(string);   //���ַ���string����
	int m = strlen(pattern);  //���ַ���pattern����
	Position s, p, *match;

	if (n < m) return NotFound;  //n < m ʱһ����ƥ��
	match = (Position *)malloc(sizeof(Position) * m);  //����m���������ݵĿռ�,�׵�ַǿ��ת��Ϊint��ָ��
	BuildMatch(pattern, match); //����BuildMatch��������pattern,��pattern��ÿһ���ַ��ó�����Ӧ��matchֵ
	s = p = 0; //������־��Ϊ0ʹ�����ַ�����ͷ��ʼƥ��(�����ַ���������±�)
	while (s < n && p < m) 
	{
		if (string[s] == pattern[p]) 
		{
			s++; p++; //���ǰ����ַ�ƥ��������������Ƚ�
		}
		else if (p > 0) p = match[p - 1] + 1; //ָ��P����,�ٿ�ʼ�Ƚ�(�൱��pattern���Ų��)
		else s++; //��p=0������ȵ�һ����ĸ��ƥ�䲻�ϣ���ʱָ��s���Ųһλ�ٱ�
	}
	return (p == m) ? (s - m) : NotFound; //pattern���ַ�ȫ��ƥ�����ʾƥ����,����string�ж�Ӧ���±�,���򷵻�NotFound
}

int main()
{
	char pattern1[100]; //�洢�ؼ��ʵ��ַ�������
	char pattern2[100]; 
	char pattern3[100]; 
	int a = 0;
	printf("������3�������ʼ����˹ؼ��ʣ�\n");
	printf("(�ո�ֿ��س�����)\n");
	scanf_s("%s", pattern1, 100); 
	scanf_s("%s", pattern2, 100);
	scanf_s("%s", pattern3, 100);
	printf("\n");
	while (a < 60) //���ò��Դ���
	{
		char string[9000]; //�洢�ʼ����ַ�������
		printf("�������ʼ�����,���س�����(֧����Ӣ��)��\n");
		scanf_s("%s", string, 9000);
		Position p1 = KMP(string, pattern1); //����ģʽƥ�亯��,�õ�pattern��string�е�λ��
		Position p2 = KMP(string, pattern2); //ͬ��,���������±긳ֵ��p2
		Position p3 = KMP(string, pattern3);
		if (p1 == NotFound && p2 == NotFound&& p3 == NotFound) //��ȫ���ؼ��ʶ�δƥ����Ϊ�����ʼ�����ֻҪ��һ��ƥ����Ϊ�����ʼ�
			 printf("\033[0;32;40m�����ʼ�,�ѽ��գ� \033[0m\n\n"); //��ʽ����ʾ��ӡ��ɫ����
		else printf("\033[0;31;40m�����ʼ�,�ѹ��ˣ� \033[0m\n\n"); //��ʽ����ʾ��ӡ��ɫ����
		a++;
	}
	return 0;
}
