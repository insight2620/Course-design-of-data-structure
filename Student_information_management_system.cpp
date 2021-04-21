#define _CRT_SECURE_NO_DEPRECATE //������ڵ�һ�У���������scanf��printfֱ�ӿ���
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>


//�ṹ�嶨��
typedef struct BSTree
{
	long long num; //ѧ��
	char name[20];
	char sex[5];//�Ա�(��ֵ)
	int age;//����(�Ǹ�)
	char major[30];
	struct BSTree *lchild, *rchild;
}BSTree;

//��������
int Get_int(void);//��ȡ����
long long Get_int1(void);//��ȡlonglong����,��֤ѧ�ų���

BSTree *InsertBSTree(BSTree *T);//�������������
BSTree *FindBSTreeinsert(long long num, BSTree *T, int *flag);//�������һ���Ӻ���

int EditBSTree(BSTree *T);//�༭����������

BSTree *DeleteBSTree(BSTree *T);//ɾ������������
BSTree *DelBSTree(long long num,BSTree *T,int *flag);//ɾ������һ���Ӻ���
BSTree *Del(BSTree *T);//ɾ�����������Ӻ���

int SearchBSTree(BSTree *T);//���Ҳ���������
BSTree *FindBSTreeequal(long long num, BSTree *T, int *flag);//���Ҳ���һ���Ӻ���

int PrintBSTree(BSTree *T);//�������������
int Print(BSTree *T);//�������һ���Ӻ���

int main( )
{	int flag = 0, m = 0;

	//�ṹ���ʼ��
	BSTree *T = 0;
	while(!(T=(BSTree *)malloc(sizeof(BSTree))))
	continue;
	T->num = 0;
	strcpy_s(T->name, "��");
	strcpy_s(T->sex, "��");
	T->age = 0;
	strcpy_s(T->major, "��");
	T->lchild = T->rchild = 0;

	//������
	printf(" ---------------------------------------------------------\n");
	printf(" |************** ��ӭʹ��ѧ����Ϣ����ϵͳ ***************|\n");
	printf(" |*******ÿ��ѧ����Ϣ������ѧ��,����,�Ա�,����,רҵ******|\n");
	printf(" ---------------------------------------------------------\n");
	do
	{	printf("\n1,���� | 2,�༭ | 3,ɾ�� | 4,����(��ѧ��)| 5,�������(��ѧ��) | 0,�˳�\n����=");
		scanf("%d", &flag); //����scanf�Ƿ�ֱ�ӿ���
		switch(flag)
		{	 case 1: T = InsertBSTree(T); PrintBSTree(T); break;
			 case 2: EditBSTree(T); PrintBSTree(T); break;
			 case 3: T=DeleteBSTree(T); PrintBSTree(T);break;
			 case 4: SearchBSTree(T); break;
			 case 5: PrintBSTree(T);break;
			 case 0: break;
			 default : printf("\n*********�Բ���ѡ����Ч��*********\n");
		}
	}while(flag);

	printf("\nллʹ�ã������������\n");
	getchar();
}

BSTree *InsertBSTree(BSTree *T)//�������������
{
	BSTree *S = 0, *t = 0;
	int flag = 0;
	while (!(t = (BSTree *)malloc(sizeof(BSTree))))
		continue;
	printf("������ѧ��\nѧ��:");
	t->num = Get_int1();
	if (t->num < 0)
	{
		printf("\n����ʧ��!!!,ѧ�Ų���С��0!!!");
		return 0;
	}
	printf("����������\n����:");
	gets_s(t->name);
	printf("��ѡ���Ա�1.��  2.Ů\n�Ա�:");
	flag= Get_int();
	while (flag != 1 && flag != 2)
	{ printf("ѡ����Ч�����������룺"); flag = Get_int();}
	if (flag == 1) strcpy_s(t->sex, "��");
	else if (flag == 2) strcpy_s(t->sex, "Ů");
	printf("����������\n����:");
	t->age = Get_int();
	while (t->age < 0)
	{   printf("���䲻��Ϊ����������������:");
		t->age = Get_int();  }
	printf("������רҵ\nרҵ:");
	gets_s(t->major);
	t->lchild = t->rchild = 0;

	if (T->num == 0)
	{
		T = t;
		//PrintBSTree(t);
		return T;
	}
	else
	{
		S = FindBSTreeinsert(t->num, T, &flag);
		if (flag == 1)
			S->lchild = t;
		else if (flag == 3)
			S->rchild = t;
		else printf("\n����ʧ�ܣ����ܲ����ѧ����Ϣ�Ѿ�����\n");
	}
	//PrintBSTree(t);
	return T;
	}

BSTree *FindBSTreeinsert(long long number,BSTree *T,int *flag)//�������һ���Ӻ���
{
	if(T)
	{
	 if(number<T->num&&!T->lchild)
	 { *flag=1;
	   return T;
	 }
	else if(number<T->num&&T->lchild)
	 FindBSTreeinsert(number,T->lchild,flag);
	else if(number>T->num&&!T->rchild)
	 { *flag=3;
	   return T;
	 }
	else if(number>T->num&&T->rchild)
	 FindBSTreeinsert(number,T->rchild,flag);
	}
}

int EditBSTree(BSTree *T)//�༭����������
{
	BSTree *S = 0, *t = 0;
	int flag = 0;
	long long number = 0;
	if (!T)
	{
		printf("\n**********�Բ���û�������ܹ��༭�����������룡***********\n");
		return 0;
	}
	printf("������Ҫ�༭ѧ����ѧ�ţ�\nѧ��:");
	number = Get_int1();
	S = FindBSTreeequal(number, T, &flag);
	if (flag == 2)
	{
		printf("\n********************** ѧ����%lld��ѧ������Ϣ���£�*********************\n", number);
		printf("\nѧ��%lld ����%s �Ա�%s ����%d רҵ%s\n", S->num, S->name, S->sex, S->age, S->major);
		printf("\n************************************************************************\n");
		printf("\n����������\n����:");
		gets_s(S->name);
		printf("��ѡ���Ա�1.��  2.Ů\n�Ա�:");
		flag = Get_int();
		while (flag != 1 && flag != 2)
		{
			printf("ѡ����Ч�����������룺"); flag = Get_int();
		}
		if (flag == 1) strcpy_s(S->sex, "��");
		else if (flag == 2) strcpy_s(S->sex, "Ů");
		printf("����������\n����:");
		S->age = Get_int();
		printf("������רҵ\nרҵ:");
		gets_s(S->major);
		return 1;
	}
	else
	{
		printf("***********�Բ���û��ѧ����%lld��ѧ��************", number);
		printf("\n�������������Ϣ�𣿣�1����ӣ�0����ӣ�\nѡ��:");
		flag = Get_int();
		if (flag)
		{
			T = InsertBSTree(T);
			return 1;
		}
		else return 0;
	}
}

BSTree *DeleteBSTree(BSTree *T) //ɾ������������
{ 
	int flag=0;
	long long number;
	BSTree *S=0;
	printf("������Ҫɾ��ѧ����ѧ�ţ�\nѧ��:");
	number=Get_int1();
	S=DelBSTree(number,T,&flag);
	if(flag==0)
	printf("\n*******ɾ��ʧ�ܣ�û��ѧ����%lld��ѧ������Ϣ********\n",number);
	return S;
}

BSTree *DelBSTree(long long number, BSTree *T, int *flag)//ɾ������һ���Ӻ���
{ 
	int m;
	if(!T)
	*flag=0;
	else if(number==T->num)
	{ 
		printf("********ѧ��Ϊ%lldѧ������Ϣ���£�ȷ��Ҫɾ����********\n",number);
		printf("\nѧ��=%lld, ����=%s, �Ա�=%s,����=%d, רҵ=%s, \n",T->num,T->name,T->sex,T->age,T->major);
		printf("\n******************************************************\n");
		printf("\nȷ��Ҫɾ����\n 1��ɾ�� || 0��ȡ��ɾ��\nѡ��:");
		m=Get_int();
		if(m==0)
		{ *flag=1;
		 return T;
		}
		T=Del(T);
		*flag=1;
	}
	else if(number<T->num)
	T->lchild=DelBSTree(number,T->lchild,flag);
	else T->rchild=DelBSTree(number,T->rchild,flag);
	return T;
}

BSTree *Del(BSTree *T) //ɾ�����������Ӻ���
{ 
	BSTree *S=0,*Q;
	if(T->lchild)
	{ S=T->lchild;
	 while(S->rchild)
	S=S->rchild;
	S->rchild=T->rchild;
	Q=T->lchild;
	free(T);
	return Q;
	}
	else
	{ Q=T->rchild;
	 free(T);
	return Q;
	}
}

int SearchBSTree(BSTree *T)//���Ҳ���������
{ 
	long long number;
	int flag = 0;
	BSTree *S=0;
	printf("������Ҫ����ѧ����ѧ��\nѧ��=");
	number=Get_int1();
	S=FindBSTreeequal(number,T,&flag);
	if(flag==2)
	{ printf("\n***************ѧ����%lld��ѧ������Ϣ���£�*****************\n",number);
	  printf("\nѧ��=%lld\t����=%s\t�Ա�=%s\t����=%d\tרҵ=%s\t\n",S->num,S->name,S->sex,S->age ,S->major);
	  printf("\n**********************************************************\n");
	  return 1;
	}
	printf("\n******����ʧ�ܣ�û�� ѧ��=%d ѧ������Ϣ*******\n",number);
	return 0;
}

BSTree *FindBSTreeequal(long long number, BSTree *T, int *flag)//���Ҳ���һ���Ӻ���
{
	if (T)
	{
		if (number == T->num)
		{
			*flag = 2;
			return T;
		}
		else if (number < T->num&&T->lchild)
			FindBSTreeequal(number, T->lchild, flag);
		else if (number > T->num&&T->rchild)
			FindBSTreeequal(number, T->rchild, flag);
	}
}

int PrintBSTree(BSTree *T)//�������������
{ 
	if(!T)
	{ printf("\n***********************û��ѧ����Ϣ*************************\n");
	return 0;
	}
	printf("\n***************************ѧ����Ϣ���£�***************************\n");
	Print(T);
	printf("\n********************************************************************\n");
	return 1;
}

int Print(BSTree *T)//�������һ���Ӻ���
{
	if(T)
	{ Print(T->lchild);
	  printf("\nѧ��=%lld\t����=%s\t�Ա�=%s\t����=%d\tרҵ=%s\t",T->num,T->name,T->sex,T->age ,T->major);
	  Print(T->rchild);
	  return 1;
	}
	return 0;
}

int Get_int(void)//��ȡ����
{ 
	int m=0;
	while(scanf_s("%d",&m)!=1)//���û����������������
	{	 while(getchar()!='\n')
		 continue;
		 printf("\n������һ������!\n����:");
	}
	while(getchar()!='\n')
	continue;
	return m;
}

long long Get_int1(void)//��ȡlonglong����,��֤ѧ�ų���
{
	long long m = 0;
	while (scanf_s("%lld", &m) != 1)//���û����������������
	{
		while (getchar() != '\n')
			continue;
		printf("\n������һ������!\n����:");
	}
	while (getchar() != '\n')
		continue;
	return m;
}