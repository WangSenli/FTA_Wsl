#include <stdio.h>
#include <windows.h>   			  //ͼ�ν���ӿڣ�
#include <stdlib.h>     		  //standard library��׼��ͷ�ļ���
#include <string.h>     		  //�ַ������� 
#include <time.h>      			  //�������ʱ��ĺ��� 
#define N 3            			  //�����˶����ѧԺ��Ŀ
typedef struct project    		  //����һ���ṹ��
{
    char xiangmu[40];     
	//������Ŀ����
    char name[N][40];     
	//ѧԺ����
    float score[N];       
	//����ɼ�
    int no[N];            
	//��������
    struct project *next;    
	//ָ����һ�ڵ��ָ��
} Proj;

typedef struct sumno              //ͳ���ۼ��� 
{
    char name[40];
    float sum;   
} SumNo;

typedef struct tm timeinfo;       //ʱ��Ľṹ��

//ȫ�ֱ������� 
char reg_name[30]="",reg_pwd[10]="";
char on_name[30],on_pwd[10];

//��������
void logtime(char c, int n);      //�����������С����� 
void logtime1(char c, int n);     //��ʱ�������� 
void ListCreate(Proj *L, int n);  //��������ڵ�
void ListSearch(Proj *L);         //����ĳ���˶�����Ŀ��Ϣ
void ListModify(Proj *L);         //�޸�ĳ���˶�����Ŀ��Ϣ
void ListDelete(Proj *L);         //ɾ��ĳ���˶�����Ŀ��Ϣ
void Input(Proj *p, int i);       //�����˶�����Ŀ��Ϣ
void Output(Proj *L);             //���ÿ���˶�����Ŀ��ѧԺ�ɼ�������Ϣ
void PerRank(Proj *L);            //����ÿ���˶�����Ŀ��ѧԺ�ɼ����������
void SumRank(Proj *L);            //������Ŀÿ��ѧԺ���ܳɼ�������
void Menu();                      //У�˶�����Ŀ����ϵͳ�Ĳ˵�            
void dl();   					  //�û���¼
int judge();  				      //�ж��Ƿ�ע��
void regist(); 					  //�û�ע��ϵͳ

int main()//ע���½ϵͳ   ��������� 
{
 //�������
 int id;
 while(1)
 {
 system("pause");  //��ͣ��Ļ 
 system("cls");    //�����Ļ 
 time_t rawtime; 
	//ʱ������
	timeinfo *timeinfos;
	//ʱ��ṹ�� ָ�����
	time(&rawtime); 
	 //��ȡʱ���������
	 //��1970��1��1�տ�ʼ������rawtime	 
	timeinfos = localtime(&rawtime);  
	//������תΪ����ʱ��
	
	printf("\t\t\t                  %s\n", 
	asctime(timeinfos));
	 //תΪascii��ʽ���
	printf("\t\t\t*------------------------------------------------------ *\n");

 printf("\n\n\t\t\t                �˶������ϵͳ\n\n");
//���湦��  
printf("\t\t\t*------------------------------------------------------ *\n");
 printf("\t\t\t|                       1:ע��                         |\n");  //����1�������û�ע��
 printf("\t\t\t*------------------------------------------------------ *\n"); 
 printf("\t\t\t|                       2:��¼                         |\n" ); //����2�������û���¼
 printf("\t\t\t*------------------------------------------------------ *\n");
 printf("\t\t\t|                       0:�˳�                         |\n\n");// ����3���˳� 
 printf("\t\t\t*------------------------------------------------------ *\n");
 printf("\t\t��ѡ���ܱ�ţ�");
 scanf("%d",&id);
 
 //�ж�
 switch(id)
 {
 case 1:regist();break;
 //���������1��ִ��ע�Ṧ�� 
 case 2:
 	//�����������2.���ж��û��Ƿ�ע�� 
 if(judge()==1)
 {
 	//����û��Ѿ�ע�ᣬ��ִ�е�¼���� 
 dl();
  int item, n;   //item���ڽ������������    //n���ڽ����������Ŀ��              
    Proj *L = NULL;         	         //��ʼ��һ��ͷ�ڵ�          
    L = (Proj *)malloc(sizeof(Proj));  	 //Ϊͷ�ڵ㿪���ڴ�ռ�
    L->next = NULL;     	             //��ͷ�ڵ��ָ�����ÿ�               
    do
    {	
        Menu();	 //�˵�
        printf("��������Ӧ�����֣�������Ӧ�Ĳ���:\n");
        scanf("%d", &item);
        system("cls");	//����	
        switch (item)
        {
        case 1:
	        printf("\t\t\t                  ¼���˶�����Ŀ��Ϣ\n");
	        printf("------------------------------------------------------ \n");
			printf("\n\n");		
            printf("��������Ҫ¼�����Ŀ��Ŀ:");
            scanf("%d", &n);
            ListCreate(L, n);   	//������Ŀ����ڵ�
            getchar(); 
            printf("\n�밴������������˵�\n");
            getchar();
            //�����ַ� 
            system("cls");
            break;
        case 2:
        	printf("\t\t\t                  �����˶�����Ŀ��Ϣ\n");
	        printf("------------------------------------------------------ \n");
            ListSearch(L); 
			//������Ŀ�������Ϣ
            getchar();
            
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 3:

        	printf("\t\t\t                  �޸��˶�����Ŀ��Ϣ\n");
	        printf("------------------------------------------------------ \n");
            ListModify(L); 
			//�޸���Ŀ��Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 4:   						 //������4��ʱ��ɾ��ĳ���˶�����Ŀ��Ϣ 
        	printf("\t\t\t                  ɾ���˶�����Ŀ��Ϣ\n");
	        printf("------------------------------------------------------ \n");
            ListDelete(L);
			 //ɾ����Ŀ����Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            getchar();
            system("cls");
            break;
        case 5: 							//������5��ʱ�򣬶�ÿ���˶����ѧԺ�ɼ�����
        	printf("\t\t\t                  ÿ���˶�����ĿѧԱ����\n");
	        printf("------------------------------------------------------ \n");
            PerRank(L); 
			//����ÿ���˶�����Ŀ��ѧԺ�ɼ�����
            Output(L);  
			//���ÿ���˶�����Ŀ��ѧԺ�ɼ�������Ϣ
            getchar();
            printf("\n�밴������������˵�\n");
            printf("��л���ʹ�ã�\n");
            getchar();
            system("cls");
            break;
        case 6: 							//������6��ʱ��������Ŀÿ��ѧԺ���ܳɼ������� 
        	printf("\t\t\t                  �����˶�����Ŀ��Ϣ\n");
	        printf("------------------------------------------------------ \n");
            SumRank(L);    //������Ŀÿ��ѧԺ���ܳɼ�������
            getchar();
            printf("\n�밴������������˵�\n");
            printf("��л���ʹ�ã�\n");
            getchar();
            system("cls");
            break;
        case 0:  							//������Ϊ0��ʱ���˳�����ϵͳ 
            printf("�����˳�У�˶�����Ŀ����ϵͳ.....\n");  
            exit(0);  						//�˳�У�˶�����Ŀ����ϵͳ
        default:
            printf("�������ָ���ȷ��");
            printf("----------------------------------\n"); 
        }
        printf("\n\n");
    } while (item);
    return 0;
 }
 break;
 case 0:exit(1);break;
 //����0��ʱ���˳�ϵͳ 
 default:
 printf("\n\t\t������Ĺ��ܱ���������������룡\n");
 }
  
 }
  
}

void ListCreate(Proj *L, int n)  //�������� 
{
    int i;
    for (i = 0; i < n; i++)
    {
        Proj *p;
        //�������ɵĽڵ���뵽������
        p = NULL;
        //ָ�붨��Ϊ�� 
        p = (Proj *)malloc(sizeof(Proj));  //malloc����̬�ڴ���亯��
		Input(p, i);
		//���� 
        p->next = L->next;
        L->next = p;
    }
}

void ListSearch(Proj *L)   //������Ŀ��Ϣ
{
    int k;
    char n[40];
    Proj *p = L->next;
    if (p == NULL)
        printf("����Ϊ�գ��޷����ң�");
    else
    {
        printf("��������Ҫ���ҵ���Ŀ����:");
        scanf("%s", n);
        while (strcmp(p->xiangmu, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            //����ָ��Ϊ������������ֶ� 
            {
                printf("û���ҵ������Ϣ\n");
                return;
            }
        }
        PerRank(L);
        printf("����Ŀ�������Ϣ����:\n");
        printf("-----------------------------------"); 
        printf("ѧԺ����\t����ɼ�\t��������\n\n");
        for (k = 0; k < N; k++)
        {
            printf("%s\t\t", *((p->name) + k));
            printf("%.2f\t\t", *((p->score) + k));
            printf("%d\t\n", *((p->no) + k));
        }
        printf("\n\n");
    }
}

void ListModify(Proj *L)  //�޸���Ŀ�������Ϣ
{
    int item, k, a;
    //������� 
    char n[40], m[40];
    Proj *p = L->next;
    if (p == NULL)
        printf("����Ϊ�գ��޷��޸ģ�");
    else
    
    {
        printf("��������Ҫ�޸ĵ���Ŀ����:");
        scanf("%s", n);
        //����Ҫ�޸ĵ���Ŀ���� 
        while (strcmp(p->xiangmu, n) != 0)
        //����������Ŀ���Ƹ�����Ĳ�ͬ 
        /*
        int strcmp(char *str1,char * str2);

        ����strcmp�Ĺ����ǱȽ������ַ����Ĵ�С��
        ���ַ���1�����ַ���2�����ؽ�������㣻
		���ַ���1С���ַ���2�����ؽ��С���㣻
		���ַ���1�����ַ���2�����ؽ�������㡣
        */
        {
        	
            p = p->next;
            //ѭ�������������Ŀ���� 
            if (p == NULL)
            {
            	//���û���ҵ���Ŀ����һ��
				//���û���ҵ������Ϣ 
                printf("û���ҵ������Ϣ\n");
                return;
           
		    }
       
	    }
        printf("���Ƿ���Ҫ�޸���Ŀ����(������1����������0):");
        scanf("%d", &a);
        if (a == 1)
        {
        	
            printf("���������޸ĺ����Ŀ����:");
            scanf("%s", m);
            //��������Ҫ�޸ĺ����Ŀ���� 
            
            strcpy(p->xiangmu, m);
            //��Ҫ�޸ĵ���Ŀ���ƽ��иı� 
            printf("�޸ĳɹ���");
            
        }
        else if (a == 0)
        {
        	
            printf("��������Ҫ�޸ĵ�ѧԺ:");
            scanf("%s", n);
            for (k = 0; k < N; k++)
            {
            	
                if (strcmp(*((p->name) + k), n) == 0)
                //�Ƚ������ַ��������ݱȽϽ����������
                    break;
                    
            }
            printf("��������Ҫ�޸ĵ���Ŀ��Ϣ����:\n");
            printf("1��ѧԺ����\n2����ѧԺ����Ŀ�ĳɼ�\n");
            scanf("%d", &item);
            switch (item)
            
            {
            case 1:
                printf("�������޸ĺ��ѧԺ����:");
                scanf("%s", m);
                strcpy(*((p->name) + k), m);
                //strcpy��C++���Ե�һ����׼���� 
				//strcpy�Ѻ���'\0'���������ַ������Ƶ���һ����ַ�ռ䣬����ֵ������Ϊchar*��
				
                printf("�޸ĳɹ�");
                break;
                
            case 2:
                printf("���������޸ĺ�ĸ�ѧԺ����Ŀ�ĳɼ�:");
                scanf("%f", (p->score) + k);
                printf("�޸ĳɹ�");
                break;
                
            default:
            	/*
            	һ���ǽ�default����case��������ڽ��Ƿ������ʾ������
				����Ҳ�������䴩����case����е����
				����������������switchʱ�Ҳ������Ӧ��case��ǩ��
				�����default��䣬�����ʱ��default���û��break��
				��Ὣ��Ϊ��㰴�������µ�˳����case��䡣
				*/
                printf("�������ָ�����!");
                break;
                
            }
            
        }
        
        else
            printf("���������");
            
    }
    
}

void ListDelete(Proj *L)   //ɾ����Ŀ�������Ϣ
{
	
    char n[40];
    Proj *p = L->next, *pre = L; 
    if (p == NULL)
        printf("����Ϊ�գ��޷�ɾ����");
    else
    {
        printf("��������Ҫɾ������Ŀ����:");
        scanf("%s", n);     //������Ŀ 
        while (strcmp(p->xiangmu, n) != 0)   //�Ƚ������ַ��������ݱȽϽ����������
        {	
            pre = p;
            p = pre->next;
            if (p == NULL)
            {
                printf("û���ҵ������Ϣ���޷�ɾ��\n");
                return;
            }
        }
        pre->next = p->next;
        free(p);
        printf("ɾ���ɹ�"); 
    }
}

void PerRank(Proj *L)  //����ÿ���˶�����Ŀ��ѧԺ�ɼ�����
{
    int i, j, k;
    float t;
    char na[40] = {' '};    //���������	 
    Proj *p = L->next;      //����һ�����飬���������洢�ɼ� 
    if (p == NULL)          //����洢������Ϊ�գ���ֱ�ӽ������� 
        printf("����Ϊ�գ��޷�����");
    else
    {	
        while (p != NULL)
       {   	
            for (i = 0; i < N; i++)
            {      	
                for (j = 0; j < N - i - 1; j++)
                {   	
                    if (*((p->score) + j) < *((p->score) + j + 1))
                    /*�˴�����ð������
					�����㷨�� 
                    ����һ��Ԫ�غ͵ڶ���Ԫ�ؽ��бȽϣ�
					��Ϊ����������Ԫ�ؽ�����Ȼ��Ƚϵڶ���Ԫ�غ͵�����Ԫ�ء�
					�������ƣ�ֱ���� n-1��Ԫ�غ͵� n��Ԫ�ؽ��бȽ�Ϊֹ��
					�������̳�Ϊ��һ��ð������
					����ʹ���ֵԪ�ر����������һ��λ�ã��� n��λ�ã���
					Ȼ����еڶ���ð������
					��ǰ n-1��Ԫ�ؽ���ͬ��������
					������ʹ�ڶ���Ԫ�ر������ڵ����ڶ���λ���ϣ��� n-1��λ�ã���
                    */
                    {	
                        t = *((p->score) + j);
                        *((p->score) + j) = *((p->score) + j + 1);
                        *((p->score) + j + 1) = t;
                        strcpy(na, *((p->name) + j));
                        strcpy(*((p->name) + j), *((p->name) + j + 1));
                        strcpy(*((p->name) + j + 1), na);
					}
                }   
            }
            for (k = 0; k < N; k++)
            {
            *((p->no) + k) = k + 1;	
			}    
            p = p->next;
        }
    }
}

void SumRank(Proj *L)  //������Ŀÿ��ѧԺ���ܳɼ�������;
{
    int i, j, k;
    float t;
    SumNo s[N],s0;
    Proj *p = L->next;
    for (i = 0; i < N; i++)
    {
        strcpy(s[i].name, *((p->name) + N - i - 1));      
        s[i].sum = 0;
    }
    if (p == NULL)    //���Ϊ0�����ٽ������� 
        printf("����Ϊ�գ�");
    else
    {
        while (p != NULL)
        {
            for(i=0;i<N;i++)
                s[i].sum += *((p->score) + i);
            p = p->next;
        }
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N - j - 1; k++)
            {
            	//ð������
                if(s[k].sum>s[k+1].sum)  	//��� s[k].sum���ݴ��� s[k+1].sum
				{
                    s0 = s[k];              //s0��Ϊһ���м�ֵ 
                    s[k] = s[k + 1];
                    s[k + 1]= s0;           //�� s[k].sum�� s[k+1].sum���ݽ��н��� 
                }
            }
        }
        p = L->next;
        printf("ѧԺ����\t�ܳɼ�\t\t������\n");
        for (i = N - 1; i >= 0; i--)
        {
            printf("%s\t\t", s[i].name);
            printf("%.2f\t\t", s[i].sum);
            printf("%d\t\t", N - i);
            printf("\n");
        }
    }
}

void Input(Proj *p, int i)  //������Ŀ�������Ϣ
{
    int j;
    printf("�������%d��������Ŀ����:", i + 1);
    scanf("%s", p->xiangmu);
	//������Ŀ���� 
    for (j = 0; j < N; j++)
    
    {
        printf("�������%d��ѧԺ������:", j + 1);
        scanf("%s", (p->name) + j);
        //����ѧԺ���� 
        printf("�������ѧԺ�ĸ���Ŀ�ĳɼ�:");
        
        scanf("%f", (p->score) + j);
        //�������Ŀ��ѧԺ��ȡ�ĳɼ� 
        
    }
    
    //���ļ��ж�ȡ���� 
    /*
    FILE*fp=NULL;
    //��ʼ��ָ�� 
    int buff[255];
    char c;
    int i=0;
    fp=fopen("D:/Data_Structure/test.txt","r");
    
    //�Ӹ�·�����ҵ���Ӧ�ļ����Ϳ��Զ�ȡ 
    while(1)
    {
        fscanf(fp,"%d", &buff[i]);
        
        c=fgetc(fp);
        if(c=='\n'|| c == EOF)
        {
            break;
        }
        i++;
    }
    printf("%d\n", i);
    for(int j=0;j<=i;j++)
    {
        printf("%d ", buff[j]);
    }
    return 0;

    */
}

void Output(Proj *L)  //���ȫ����Ŀ��Ϣ
{
    int k;
    Proj *p = L->next;
    
    while (p != NULL)
    {
        printf("\t\t��Ŀ:%s\n\n", p->xiangmu);
        printf("ѧԺ����\t����ɼ�\t��������\n\n");
        for (k = 0; k < N;k++)
        {
            printf("%s\t\t", *((p->name) + k));             //�������           
            printf("%.2f\t\t", *((p->score) + k));          //������� 
            printf("%d\t\n", *((p->no) + k));               //�������  
        }
        printf("\n\n");         //����ո� 
        p = p->next;            //�������������� ��ָ��ָ����һ�� 
    }
}

void Menu()   //У�˶�����Ŀ����ϵͳ�Ĳ˵�

{
	time_t rawtime;   	    //ʱ������
	timeinfo *timeinfos;  	//ʱ��ṹ�� ָ�����
	time(&rawtime);  	    //��ȡʱ���������
	timeinfos = localtime(&rawtime);  	//������תΪ����ʱ��	
	printf("\t\t\t                  %s\n", 
	asctime(timeinfos));
	 //תΪascii��ʽ���
	printf("\t\t\t*------------------------------------------------------ *\n");
	printf("\t\t\t*|                   ѧ���˶������ϵͳ                |*\n");
	printf("\t\t\t*------------------------------------------------------ *\n");
	printf("\t\t\t                 %d��%d��%d�� %dʱ%d��%d��",
			timeinfos->tm_year+1900,    	//���Ǵ�1900��ʼ�ģ�Ҫ��1900			 
			timeinfos->tm_mon+1,    	    //���Ǵ�0��ʼ�ģ�Ҫ��1		    			
			timeinfos->tm_mday,		    	//���� 			
			timeinfos->tm_hour,		    	//Сʱ 			
			timeinfos->tm_min,	        	//�� 				
			timeinfos->tm_sec);	            //�� 							
	printf("\n\n");	
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          1>. ¼���˶�����Ŀ��Ϣ                       *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          2>. ����ĳ���˶�����Ŀ��Ϣ                   *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          3>. �޸�ĳ���˶�����Ŀ��Ϣ                   *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          4>. ɾ��ĳ���˶�����Ŀ��Ϣ                   *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          5>. ÿ���˶�����Ŀ��ѧԺ�ɼ�����             *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          6>. ������Ŀÿ��ѧԺ���ܳɼ�������           *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          0>. �˳�����ϵͳ                             *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          ��ӭʹ�ñ�ϵͳ!*                              \n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t           ����ѡ����س�����ѡ��:                     \n");
}

void regist()   //�û�ע��ϵͳ
{
 //����
 system("pause");
 system("cls");  
 printf("\n\n\t\t\t��ӭʹ���˶������ϵͳ\n\n");
 while(1)   //1��ԶΪ�棬��ѭ��Ϊ������ѭ��
	{
 		printf("\t\t�������û���[���ܴ���10���ַ�]��");
 		scanf("%s",reg_name);		//�����û���
 		
	if(strlen(reg_name)<=10)        //�ж��û�
		{	
 		while(1)
			{	
 				printf("\n\t\t����������[���볤��Ϊ��λ]��");  
			    scanf("%s",reg_pwd);   //��������
 			if(strlen(reg_pwd)==8)     //�ж�����  	//����û���������8λ�����ʾע��ɹ�
 				{	
 					printf("\n\n\t\tע��ɹ��������û�����%s,������%s\n\n",reg_name,reg_pwd);
 					break;
 				}
 			else
 				{	
 				 printf("\n\t\t����ĳ���Ϊ%d������������\n",strlen(reg_pwd));
 				}
 			}
 			break;    //����while��1�� ������ѭ�� 
		 }
 	else
 		{	
 			printf("\n\t\t�û����ĳ���Ϊ%d������������\n\n",strlen(reg_name));
 		}
	 }
}
int judge()  //�ж��Ƿ�ע��
{
			/*
			strcmp������string compare(�ַ����Ƚ�)����д��
			���ڱȽ������ַ��������ݱȽϽ������������
			������ʽΪstrcmp(str1,str2)��
			��str1=str2���򷵻��㣻
			��str1<str2���򷵻ظ�����
			��str1>str2���򷵻������� [1-2] 
			*/
 		if(strcmp(reg_name,"")==0&&strcmp(reg_pwd,"")==0) //�˴����Ƚ��˻��������Ƿ�Ϊ0����Ϊ0�򲻷���0���ж�Ϊδע�� 
 			{
				 printf("\n\n\t\t����δע�ᣬ����ע�ᣡ\n\n");   //�жϳ��û���δע�ᣬ����ע��
				 return 0;
 			}
		else
 			{
 				 return 1;
 			}
}  
void dl()  //�û���¼
{	
 int i;
 //����ֲ����� 
 system("pause");

 system("cls");
 printf("\n\n\t\t\t��ӭʹ���˶������ϵͳ\n\n");
 printf("\n\n\t\t\t----------------------\n\n");
 //���ε�¼��֤
 for(i=1;i<=3;i++)
 {
 //3�ε�¼������forѭ��	
 printf("\t\t�������û���:");
 scanf("%s",on_name);
 //�����û��� 
 printf("\n\t\t�������� ��:");
 scanf("%s",on_pwd);
 //�������� 
 if(strcmp(reg_name,on_name)==0&&strcmp(reg_pwd,on_pwd)==0)
// �ж�������û����������Ƿ���ͬ 
//�����ͬ��ִ�е�¼�ɹ�
//�������ͬ����ʾ��¼ʧ�� 
 {
    printf("�û���½�ɹ�!\n���Զ���ת���û�����");
    logtime('.', 12);
 break;
 //��¼�ɹ���������ѭ��ִ����һ�� 
 }
 else
 {
 printf("\n\n\t\t��¼ʧ�ܣ������µ�¼��",3-i);
 printf("\n\n\t\t������%d�λ���\n\n",3-i);
 }
 }
}
void logtime(char c, int n)  //���ؽ��Ⱥ��� 
{
    int i, j;
    for (i = 0; i < n; i++) {
        printf("%c", c);
        Sleep(200);
    }
    for (j = 0; j < 101; j = j + 1) {
        system("cls");
        printf("\n\n\n");
        printf("\n\n\n");
        printf("                   �������%d%%�����Ե�", j);
        printf("\n\n\n");
        Sleep(20);
    }
    printf("\n");
}

void logtime1(char c, int n) //���ض�������
{
    int i, j;
    for (i = 0; i < n; i++) {
        printf("%c", c);
        Sleep(500);
    }
    printf("\n");
}
