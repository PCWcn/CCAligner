#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>

#define MAX_PATH_LEN 512

int count =0;
char dirPath[MAX_PATH_LEN];

void listAllFiles(char *dirname)
{
 assert(dirname != NULL);
 
 char path[512];
 struct dirent *filename;//readdir 的返回类型
 DIR *dir;//血的教训阿，不要随便把变量就设成全局变量。。。。
 
 dir = opendir(dirname);
 if(dir == NULL)
 {
  printf("open dir %s error!\n",dirname);
  exit(1);
 }
 
 while((filename = readdir(dir)) != NULL)
 {
  //目录结构下面问什么会有两个.和..的目录？ 跳过着两个目录
  if(!strcmp(filename->d_name,".")||!strcmp(filename->d_name,".."))
   continue;
   
  //非常好用的一个函数，比什么字符串拼接什么的来的快的多
  sprintf(path,"%s/%s",dirname,filename->d_name);
  
  struct stat s;
  lstat(path,&s);
  
  if(S_ISDIR(s.st_mode))
  {
   listAllFiles(path);//递归调用
  }
  else
  {
   printf("%d. %s\n",++count,filename->d_name);
  }
 }
 closedir(dir);
}


int main(int argc, char **argv)
{

 if(argc != 2)
 {
  printf("one dir required!(for eample: ./a.out /home/myFolder)\n");
  exit(1);
 }
 strcpy(dirPath,argv[1]);
 listAllFiles(dirPath);
 printf("total files:%d\n",count);
 return 0;
}