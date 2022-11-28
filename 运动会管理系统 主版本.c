#include <stdio.h>
#include <windows.h>   			  //图形界面接口，
#include <stdlib.h>     		  //standard library标准库头文件，
#include <string.h>     		  //字符串处理 
#include <time.h>      			  //定义关于时间的函数 
#define N 3            			  //参与运动会的学院数目
typedef struct project    		  //定义一个结构体
{
    char xiangmu[40];     
	//比赛项目名称
    char name[N][40];     
	//学院名称
    float score[N];       
	//单项成绩
    int no[N];            
	//单项名次
    struct project *next;    
	//指向下一节点的指针
} Proj;

typedef struct sumno              //统计累计量 
{
    char name[40];
    float sum;   
} SumNo;

typedef struct tm timeinfo;       //时间的结构体

//全局变量声明 
char reg_name[30]="",reg_pwd[10]="";
char on_name[30],on_pwd[10];

//函数声明
void logtime(char c, int n);      //动画“加载中”函数 
void logtime1(char c, int n);     //延时动画函数 
void ListCreate(Proj *L, int n);  //创建链表节点
void ListSearch(Proj *L);         //查找某个运动会项目信息
void ListModify(Proj *L);         //修改某个运动会项目信息
void ListDelete(Proj *L);         //删除某个运动会项目信息
void Input(Proj *p, int i);       //输入运动会项目信息
void Output(Proj *L);             //输出每个运动会项目的学院成绩排名信息
void PerRank(Proj *L);            //计算每个运动会项目的学院成绩排名并输出
void SumRank(Proj *L);            //所有项目每个学院的总成绩和排名
void Menu();                      //校运动会项目管理系统的菜单            
void dl();   					  //用户登录
int judge();  				      //判断是否注册
void regist(); 					  //用户注册系统

int main()//注册登陆系统   主函数入口 
{
 //定义变量
 int id;
 while(1)
 {
 system("pause");  //暂停屏幕 
 system("cls");    //清空屏幕 
 time_t rawtime; 
	//时间类型
	timeinfo *timeinfos;
	//时间结构体 指针变量
	time(&rawtime); 
	 //获取时间的秒数，
	 //从1970年1月1日开始，存入rawtime	 
	timeinfos = localtime(&rawtime);  
	//将秒数转为当地时间
	
	printf("\t\t\t                  %s\n", 
	asctime(timeinfos));
	 //转为ascii格式输出
	printf("\t\t\t*------------------------------------------------------ *\n");

 printf("\n\n\t\t\t                运动会管理系统\n\n");
//界面功能  
printf("\t\t\t*------------------------------------------------------ *\n");
 printf("\t\t\t|                       1:注册                         |\n");  //输入1、进行用户注册
 printf("\t\t\t*------------------------------------------------------ *\n"); 
 printf("\t\t\t|                       2:登录                         |\n" ); //输入2、进行用户登录
 printf("\t\t\t*------------------------------------------------------ *\n");
 printf("\t\t\t|                       0:退出                         |\n\n");// 输入3、退出 
 printf("\t\t\t*------------------------------------------------------ *\n");
 printf("\t\t请选择功能编号：");
 scanf("%d",&id);
 
 //判断
 switch(id)
 {
 case 1:regist();break;
 //当你输入的1、执行注册功能 
 case 2:
 	//当你输入的是2.先判断用户是否注册 
 if(judge()==1)
 {
 	//如果用户已经注册，则执行登录功能 
 dl();
  int item, n;   //item用于接收输入的命令    //n用于接收输入的项目数              
    Proj *L = NULL;         	         //初始化一个头节点          
    L = (Proj *)malloc(sizeof(Proj));  	 //为头节点开辟内存空间
    L->next = NULL;     	             //将头节点的指针域置空               
    do
    {	
        Menu();	 //菜单
        printf("请输入相应的数字，进行相应的操作:\n");
        scanf("%d", &item);
        system("cls");	//清屏	
        switch (item)
        {
        case 1:
	        printf("\t\t\t                  录入运动会项目信息\n");
	        printf("------------------------------------------------------ \n");
			printf("\n\n");		
            printf("请输入您要录入的项目数目:");
            scanf("%d", &n);
            ListCreate(L, n);   	//创建项目链表节点
            getchar(); 
            printf("\n请按任意键返回主菜单\n");
            getchar();
            //输入字符 
            system("cls");
            break;
        case 2:
        	printf("\t\t\t                  查找运动会项目信息\n");
	        printf("------------------------------------------------------ \n");
            ListSearch(L); 
			//查找项目的相关信息
            getchar();
            
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 3:

        	printf("\t\t\t                  修改运动会项目信息\n");
	        printf("------------------------------------------------------ \n");
            ListModify(L); 
			//修改项目信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 4:   						 //当输入4的时候，删除某个运动会项目信息 
        	printf("\t\t\t                  删除运动会项目信息\n");
	        printf("------------------------------------------------------ \n");
            ListDelete(L);
			 //删除项目的信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 5: 							//当输入5的时候，对每个运动会的学院成绩排名
        	printf("\t\t\t                  每个运动会项目学员排名\n");
	        printf("------------------------------------------------------ \n");
            PerRank(L); 
			//计算每个运动会项目的学院成绩排名
            Output(L);  
			//输出每个运动会项目的学院成绩排名信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            printf("感谢你的使用！\n");
            getchar();
            system("cls");
            break;
        case 6: 							//当输入6的时候，所有项目每个学院的总成绩和排名 
        	printf("\t\t\t                  所有运动会项目信息\n");
	        printf("------------------------------------------------------ \n");
            SumRank(L);    //所有项目每个学院的总成绩和排名
            getchar();
            printf("\n请按任意键返回主菜单\n");
            printf("感谢你的使用！\n");
            getchar();
            system("cls");
            break;
        case 0:  							//当输入为0的时候，退出管理系统 
            printf("即将退出校运动会项目管理系统.....\n");  
            exit(0);  						//退出校运动会项目管理系统
        default:
            printf("您输入的指令不正确！");
            printf("----------------------------------\n"); 
        }
        printf("\n\n");
    } while (item);
    return 0;
 }
 break;
 case 0:exit(1);break;
 //输入0的时候，退出系统 
 default:
 printf("\n\t\t您输入的功能编号有误，请重新输入！\n");
 }
  
 }
  
}

void ListCreate(Proj *L, int n)  //创建链表 
{
    int i;
    for (i = 0; i < n; i++)
    {
        Proj *p;
        //将新生成的节点插入到链表中
        p = NULL;
        //指针定义为空 
        p = (Proj *)malloc(sizeof(Proj));  //malloc：动态内存分配函数
		Input(p, i);
		//输入 
        p->next = L->next;
        L->next = p;
    }
}

void ListSearch(Proj *L)   //查找项目信息
{
    int k;
    char n[40];
    Proj *p = L->next;
    if (p == NULL)
        printf("数据为空，无法查找！");
    else
    {
        printf("请输入您要查找的项目名称:");
        scanf("%s", n);
        while (strcmp(p->xiangmu, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            //输入指针为空是输出下面字段 
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        PerRank(L);
        printf("该项目的相关信息如下:\n");
        printf("-----------------------------------"); 
        printf("学院名称\t单项成绩\t单项名次\n\n");
        for (k = 0; k < N; k++)
        {
            printf("%s\t\t", *((p->name) + k));
            printf("%.2f\t\t", *((p->score) + k));
            printf("%d\t\n", *((p->no) + k));
        }
        printf("\n\n");
    }
}

void ListModify(Proj *L)  //修改项目的相关信息
{
    int item, k, a;
    //定义变量 
    char n[40], m[40];
    Proj *p = L->next;
    if (p == NULL)
        printf("数据为空，无法修改！");
    else
    
    {
        printf("请输入您要修改的项目名称:");
        scanf("%s", n);
        //输入要修改的项目名称 
        while (strcmp(p->xiangmu, n) != 0)
        //如果输入的项目名称跟输入的不同 
        /*
        int strcmp(char *str1,char * str2);

        函数strcmp的功能是比较两个字符串的大小。
        若字符串1大于字符串2，返回结果大于零；
		若字符串1小于字符串2，返回结果小于零；
		若字符串1等于字符串2，返回结果等于零。
        */
        {
        	
            p = p->next;
            //循环遍历存入的项目名称 
            if (p == NULL)
            {
            	//如果没有找到项目名称一样
				//输出没有找到相关信息 
                printf("没有找到相关信息\n");
                return;
           
		    }
       
	    }
        printf("您是否需要修改项目名称(是输入1，不是输入0):");
        scanf("%d", &a);
        if (a == 1)
        {
        	
            printf("请输入您修改后的项目名称:");
            scanf("%s", m);
            //东输入你要修改后的项目名称 
            
            strcpy(p->xiangmu, m);
            //需要修改的项目名称进行改变 
            printf("修改成功！");
            
        }
        else if (a == 0)
        {
        	
            printf("请输入您要修改的学院:");
            scanf("%s", n);
            for (k = 0; k < N; k++)
            {
            	
                if (strcmp(*((p->name) + k), n) == 0)
                //比较两个字符串并根据比较结果返回整数
                    break;
                    
            }
            printf("请输入你要修改的项目信息类型:\n");
            printf("1、学院名称\n2、该学院该项目的成绩\n");
            scanf("%d", &item);
            switch (item)
            
            {
            case 1:
                printf("请输入修改后的学院名称:");
                scanf("%s", m);
                strcpy(*((p->name) + k), m);
                //strcpy是C++语言的一个标准函数 
				//strcpy把含有'\0'结束符的字符串复制到另一个地址空间，返回值的类型为char*。
				
                printf("修改成功");
                break;
                
            case 2:
                printf("请输入您修改后的该学院该项目的成绩:");
                scanf("%f", (p->score) + k);
                printf("修改成功");
                break;
                
            default:
            	/*
            	一般是将default放在case的最后，用于将非法输出显示出来。
				但是也不乏将其穿插在case语句中的情况
				在这情况下如果进入switch时找不到相对应的case标签，
				则会跑default语句，如果此时的default语句没有break，
				则会将它为起点按自上往下的顺序跑case语句。
				*/
                printf("您输入的指令错误!");
                break;
                
            }
            
        }
        
        else
            printf("您输入错误！");
            
    }
    
}

void ListDelete(Proj *L)   //删除项目的相关信息
{
	
    char n[40];
    Proj *p = L->next, *pre = L; 
    if (p == NULL)
        printf("数据为空，无法删除！");
    else
    {
        printf("请输入您要删除的项目名称:");
        scanf("%s", n);     //输入项目 
        while (strcmp(p->xiangmu, n) != 0)   //比较两个字符串并根据比较结果返回整数
        {	
            pre = p;
            p = pre->next;
            if (p == NULL)
            {
                printf("没有找到相关信息，无法删除\n");
                return;
            }
        }
        pre->next = p->next;
        free(p);
        printf("删除成功"); 
    }
}

void PerRank(Proj *L)  //计算每个运动会项目的学院成绩排名
{
    int i, j, k;
    float t;
    char na[40] = {' '};    //定义空数组	 
    Proj *p = L->next;      //定义一个数组，数组用来存储成绩 
    if (p == NULL)          //如果存储的数据为空，则直接结束排序 
        printf("数据为空，无法排序！");
    else
    {	
        while (p != NULL)
       {   	
            for (i = 0; i < N; i++)
            {      	
                for (j = 0; j < N - i - 1; j++)
                {   	
                    if (*((p->score) + j) < *((p->score) + j + 1))
                    /*此处试用冒泡排序
					基本算法： 
                    将第一个元素和第二个元素进行比较，
					若为逆序则将两个元素交换，然后比较第二个元素和第三个元素。
					依次类推，直至第 n-1个元素和第 n个元素进行比较为止。
					上述过程称为第一趟冒泡排序，
					其结果使最大值元素被放置在最后一个位置（第 n个位置）。
					然后进行第二趟冒泡排序，
					对前 n-1个元素进行同样操作，
					其结果是使第二大元素被放置在倒数第二个位置上（第 n-1个位置）。
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

void SumRank(Proj *L)  //所有项目每个学院的总成绩和排名;
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
    if (p == NULL)    //如果为0，不再进行排序 
        printf("数据为空！");
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
            	//冒泡排序
                if(s[k].sum>s[k+1].sum)  	//如果 s[k].sum数据大于 s[k+1].sum
				{
                    s0 = s[k];              //s0作为一个中间值 
                    s[k] = s[k + 1];
                    s[k + 1]= s0;           //将 s[k].sum， s[k+1].sum数据进行交换 
                }
            }
        }
        p = L->next;
        printf("学院名称\t总成绩\t\t总排名\n");
        for (i = N - 1; i >= 0; i--)
        {
            printf("%s\t\t", s[i].name);
            printf("%.2f\t\t", s[i].sum);
            printf("%d\t\t", N - i);
            printf("\n");
        }
    }
}

void Input(Proj *p, int i)  //输入项目的相关信息
{
    int j;
    printf("请输入第%d个比赛项目名称:", i + 1);
    scanf("%s", p->xiangmu);
	//输入项目名称 
    for (j = 0; j < N; j++)
    
    {
        printf("请输入第%d个学院的名称:", j + 1);
        scanf("%s", (p->name) + j);
        //输入学院名称 
        printf("请输入该学院的该项目的成绩:");
        
        scanf("%f", (p->score) + j);
        //输入该项目该学院获取的成绩 
        
    }
    
    //从文件中读取数据 
    /*
    FILE*fp=NULL;
    //初始化指针 
    int buff[255];
    char c;
    int i=0;
    fp=fopen("D:/Data_Structure/test.txt","r");
    
    //从该路径中找到相应文件，就可以读取 
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

void Output(Proj *L)  //输出全部项目信息
{
    int k;
    Proj *p = L->next;
    
    while (p != NULL)
    {
        printf("\t\t项目:%s\n\n", p->xiangmu);
        printf("学院名称\t单项成绩\t单项名次\n\n");
        for (k = 0; k < N;k++)
        {
            printf("%s\t\t", *((p->name) + k));             //输出姓名           
            printf("%.2f\t\t", *((p->score) + k));          //输出分数 
            printf("%d\t\n", *((p->no) + k));               //输出名次  
        }
        printf("\n\n");         //输出空格 
        p = p->next;            //当不满足条件后 ，指针指向下一个 
    }
}

void Menu()   //校运动会项目管理系统的菜单

{
	time_t rawtime;   	    //时间类型
	timeinfo *timeinfos;  	//时间结构体 指针变量
	time(&rawtime);  	    //获取时间的秒数，
	timeinfos = localtime(&rawtime);  	//将秒数转为当地时间	
	printf("\t\t\t                  %s\n", 
	asctime(timeinfos));
	 //转为ascii格式输出
	printf("\t\t\t*------------------------------------------------------ *\n");
	printf("\t\t\t*|                   学生运动会管理系统                |*\n");
	printf("\t\t\t*------------------------------------------------------ *\n");
	printf("\t\t\t                 %d年%d月%d日 %d时%d分%d秒",
			timeinfos->tm_year+1900,    	//年是从1900开始的，要加1900			 
			timeinfos->tm_mon+1,    	    //月是从0开始的，要加1		    			
			timeinfos->tm_mday,		    	//天数 			
			timeinfos->tm_hour,		    	//小时 			
			timeinfos->tm_min,	        	//分 				
			timeinfos->tm_sec);	            //秒 							
	printf("\n\n");	
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          1>. 录入运动会项目信息                       *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          2>. 查找某个运动会项目信息                   *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          3>. 修改某个运动会项目信息                   *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          4>. 删除某个运动会项目信息                   *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          5>. 每个运动会项目的学院成绩排名             *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          6>. 所有项目每个学院的总成绩和排名           *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          0>. 退出管理系统                             *\n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t*          欢迎使用本系统!*                              \n");
    printf("\t\t\t*------------------------------------------------------ *\n");
    printf("\t\t\t           输入选项，按回车进入选项:                     \n");
}

void regist()   //用户注册系统
{
 //清屏
 system("pause");
 system("cls");  
 printf("\n\n\t\t\t欢迎使用运动会管理系统\n\n");
 while(1)   //1永远为真，该循环为无限死循环
	{
 		printf("\t\t请输入用户名[不能大于10个字符]：");
 		scanf("%s",reg_name);		//输入用户名
 		
	if(strlen(reg_name)<=10)        //判断用户
		{	
 		while(1)
			{	
 				printf("\n\t\t请输入密码[密码长度为八位]：");  
			    scanf("%s",reg_pwd);   //输入密码
 			if(strlen(reg_pwd)==8)     //判断密码  	//如果用户密码满足8位，则表示注册成功
 				{	
 					printf("\n\n\t\t注册成功，您的用户名是%s,密码是%s\n\n",reg_name,reg_pwd);
 					break;
 				}
 			else
 				{	
 				 printf("\n\t\t密码的长度为%d，请重新输入\n",strlen(reg_pwd));
 				}
 			}
 			break;    //跳出while（1） 无限死循环 
		 }
 	else
 		{	
 			printf("\n\t\t用户名的长度为%d，请重新输入\n\n",strlen(reg_name));
 		}
	 }
}
int judge()  //判断是否注册
{
			/*
			strcmp函数是string compare(字符串比较)的缩写，
			用于比较两个字符串并根据比较结果返回整数。
			基本形式为strcmp(str1,str2)，
			若str1=str2，则返回零；
			若str1<str2，则返回负数；
			若str1>str2，则返回正数。 [1-2] 
			*/
 		if(strcmp(reg_name,"")==0&&strcmp(reg_pwd,"")==0) //此处即比较账户和密码是否为0，若为0则不返回0，判断为未注册 
 			{
				 printf("\n\n\t\t您尚未注册，请先注册！\n\n");   //判断出用户尚未注册，重新注册
				 return 0;
 			}
		else
 			{
 				 return 1;
 			}
}  
void dl()  //用户登录
{	
 int i;
 //定义局部变量 
 system("pause");

 system("cls");
 printf("\n\n\t\t\t欢迎使用运动会管理系统\n\n");
 printf("\n\n\t\t\t----------------------\n\n");
 //三次登录验证
 for(i=1;i<=3;i++)
 {
 //3次登录机会用for循环	
 printf("\t\t请输入用户名:");
 scanf("%s",on_name);
 //输入用户名 
 printf("\n\t\t请输入密 码:");
 scanf("%s",on_pwd);
 //输入密码 
 if(strcmp(reg_name,on_name)==0&&strcmp(reg_pwd,on_pwd)==0)
// 判断输入的用户名和密码是否相同 
//如果相同则执行登录成功
//如果不相同，显示登录失败 
 {
    printf("用户登陆成功!\n将自动跳转至用户界面");
    logtime('.', 12);
 break;
 //登录成功，则跳出循环执行下一步 
 }
 else
 {
 printf("\n\n\t\t登录失败，请重新登录！",3-i);
 printf("\n\n\t\t您还有%d次机会\n\n",3-i);
 }
 }
}
void logtime(char c, int n)  //加载进度函数 
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
        printf("                   载入进度%d%%，请稍等", j);
        printf("\n\n\n");
        Sleep(20);
    }
    printf("\n");
}

void logtime1(char c, int n) //加载动画函数
{
    int i, j;
    for (i = 0; i < n; i++) {
        printf("%c", c);
        Sleep(500);
    }
    printf("\n");
}
