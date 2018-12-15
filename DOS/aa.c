#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
const int FDF=-2;
const int FFF=-1;
const int N=100;//存储空间(FAT表长度)
int filenumber;//文件数量
struct FILEINFO{
    char name[10];
    int start;
    int length;
};
FILEINFO file[10];
int FAT[N],freespace; //FAT表和剩余空间
void printfmenu()
{
    int i;
    printf("\t文件个数:%d \n",filenumber);
    printf("\t文件名  起始块号  文件长度\n");
    for(i=0;i<filenumber;i++){
        printf("   %s       %d       %d\n",file[i].name,file[i].start,file[i].length);
    }
}
void printFAT()
{
    int i;
    printf("\t空闲块数:%d\n",freespace);
    printf("\t-2代表FDF,-1代表FFF\n");
    for(i=0;i<N;i++){
        printf(" No.%d    %d\n",i,FAT[i]);
    }
}
void search(char *tmpname){
    int i;
    for(i=0;i<filenumber;i++)
    {
        if(strcmp(file[i].name,tmpname)==0)//比较插入文件名与已存在文件名是否相同
        {
            printf("\t找到了!\n");
            printf("\t文件名  起始块号  文件长度\n");
            printf("   %s       %d       %d\n",file[i].name,file[i].start,file[i].length);
        }
    }
}
void search2(int searchpoint)
{
    int i;
    int m;
    if(FAT[searchpoint]==0){
        printf("\t该点空缺,没有文件!");
        printf("%d", i);
    }
    else if(FAT[searchpoint]==-1&&FAT[searchpoint-1]==-2||FAT[searchpoint]==-2&&FAT[searchpoint+1]==-1)
    {
        printf("\t此处为系统空间!");

        printf("%d", i);
    }
    else if(FAT[searchpoint]==-1&&FAT[searchpoint+1]==0)
    {
        printf("\t找到了!此处的文件名为:%s",file[i].name);

        printf("%d", i);
    }
    else if(FAT[searchpoint]!=0&&FAT[searchpoint+1]!=-1)
    {
        for(m=searchpoint;;m++)
        {
            if(FAT[m]==-1)
                printf("\t找到了!此处的文件名为:%s",file[i].name);

            printf("%d", i);

            break;
        }
    }
    else if(FAT[searchpoint]!=0&&FAT[searchpoint+1]==-1)
    {
        printf("找到了!此处的文件名为:%s",file[i].name);

        printf("%d", i);
    }
}
void write(char *tmpname,int tmplength)
{
    int last,i,j;
    strcpy(file[filenumber].name,tmpname);//复制文件名和文件块个数
    file[filenumber].length=tmplength;
    for(i=2;i<N;i++){	//存文件
        if(FAT[i]==0){
            file[filenumber].start=i;//首个空闲块为文件开始块
            last=i;
            FAT[last]=FFF;
            break;
        }
    }
    for(i=1;i<tmplength;i++){	//last为上个记录的位置
        for(j=2;j<N;j++)
            if(FAT[j]==0){
                FAT[last]=j;
                last=j;
                FAT[last]=FFF;
                break;
            }
    }
    FAT[last]=FFF;//文件末存结束标记
    freespace-=tmplength;//改变空闲块个数
    filenumber++;
    printf("文件名和长度:%s    %d\n",tmpname,tmplength);
}
void insert(char *tmpname,int insertpoint)
{
    int i;
    int last,brpoint;
    for(i=0;i<filenumber;i++)//寻找要执行插入操作的文件，将其数组下标存入last
    {
        if(strcmp(file[i].name,tmpname)==0)//比较插入文件名与已存在文件名是否相同
        {
            last=i;
            break;
        }
    }
    brpoint=file[last].start;	//brpoint记录当前文件扫描到的位置
    for(i=0;i<insertpoint-1;i++)
    {
        brpoint=FAT[brpoint]; //扫描直到找到插入位置
    }
    for(i=0;i<N;i++)//寻找一个空闲块插入
    {
        if(FAT[i]==0)
        {
            FAT[i]=FAT[brpoint];
            FAT[brpoint]=i;
            break;
        }
    }
    file[last].length++;	//改变空闲块个数与文件长度
    freespace--;
    printf("\t文件名和长度:%s    %d\n",tmpname,file[last].length);
}
int main()
{
    int i;
    char tmpname[10];
    int tmplength;//要写入文件长度
    int m;//命令
    filenumber=0;
    for(i=0;i<N;i++){  //初始化FAT表
        FAT[i]=0;
    }
    FAT[0]=FDF;
    FAT[1]=FFF;
    //FAT[3]=999;
    freespace=98;
    while(true){
        printf("\n");

        printf("      *********************************************************\n");
        printf("                ****欢 迎 进 入****         \n");
        printf("                                                          \n");
        printf("            <<<< 模拟DOS文件的建立和使用>>>>   \n");
        printf("                          0.退    出                       \n");
        printf("            1.写入文件    2.插入文件    3.显示文件目录     \n");
        printf("            4.显示FAT表   5.搜索文件    6.搜索索引点       \n");

        printf("      *********************************************************\n");

        printf("\n");
        printf("\t选择服务菜单：");
        scanf("%d",&m);
        switch(m){
            case 0: exit(0);
            case 1: printf("\t输入要写入的文件名：");
                scanf("%s",&tmpname);
                printf("\t输入要写入的文件长度：");
                scanf("%d",&tmplength);
                write(tmpname,tmplength);
                break;
            case 2: printf("\t输入要插入的文件名：");
                scanf("%s",&tmpname);
                int insertpoint;
                printf("\t输入要插入的点：");
                scanf("%d",&insertpoint);
                insert(tmpname,insertpoint);
                break;
            case 3: printfmenu();
                break;
            case 4: printFAT();
                break;
            case 5: printf("\t请输入要搜索的文件名:");

                scanf("%s",&tmpname);
                search(tmpname);
                break;
            case 6: printf("\t请输入要搜索的索引点：");
                int searchpoint;
                scanf("%d",&searchpoint);
                search2(searchpoint);
                break;
        }
    }
    printFAT();
}
