#include <io.h>
#include <fstream>
#include <string>
#include <vector>
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;


void getFilesAll( string path, vector<string>& files) 
{ 
	//文件句柄 
	long hFile  =  0; 
	//文件信息 
	struct _finddata_t fileinfo; 
	string p; 
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1) 
	{ 
		do
		{  
			if((fileinfo.attrib & _A_SUBDIR)) 
			{ 
				if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0) 
				{
					//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					getFilesAll( p.assign(path).append("\\").append(fileinfo.name), files ); 
				}
			} 
			else
			{ 
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) ); 
			} 
		}while(_findnext(hFile, &fileinfo) == 0); 
		_findclose(hFile); 
	} 
}
void getAllFiles(string path, vector<string>& files)
{
	//文件句柄 
	long hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)
	{
		do
		{
			if((fileinfo.attrib & _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					getFilesAll( p.assign(path).append("\\").append(fileinfo.name), files );
				}
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
int main(void){
	char * filePath = "D:\\ccfxprepdir"; 
	vector<string> files; 
	char * distAll = "E:\\AllFiles.txt";
	getFilesAll(filePath, files);
	ofstream ofn(distAll);
	int size = files.size(); 
	printf("%d\n",size);
	//ofn<<size<<endl;
	for (int j = 0;j<size;j++) 
	{ 
		ofn<<files[j]<<endl;
		//这边是读一个个文件
		
	}
	ofn.close();
	return 0;
}
