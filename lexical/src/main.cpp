//src/main.cpp

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/unordered_map.hpp>
#include <map>

#define MAX_PATH_LEN 512


#include "tok.h"

using namespace std;

extern FILE *yyin;  // file pointer used in lexer
extern int yylex(); // lexer function provided by lexer.l
extern char * yytext;
void print_token(int arg_token, FILE * arg_file);


// Calculate the relative displacement of a specifiic token.
static int token_num;
int qline = 0; 	//wpc
int pline = 0;	//pc
int ppline = 0;	//}
int flline1,flline2=0;//for,num of ';'
int lpc,rpc = 0;// (,)
int mline = 0;	//wpc
int rline = 9999999;
int rline_max = 9999999;
map<string, int> * id_map;
map<string, int> :: iterator id_map_iter;
extern int nline;
int count =0;
char dirPath[MAX_PATH_LEN];
char dirPath1[MAX_PATH_LEN];
char dirPath2[MAX_PATH_LEN];
/*
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
   //printf("%d. %s\n",++count,filename->d_name);
   char readInfilename[MAX_PATH_LEN];
   char outputfilename[MAX_PATH_LEN];
   strcpy(readInfilename, dirname);
   strcat(readInfilename, "/");
   strcat(readInfilename, filename->d_name);
   strcpy(outputfilename, "../token");
   strcat(outputfilename, dirname);
   strcat(outputfilename, "/");
   strcat(outputfilename, filename->d_name);
   //strcat(outputfilename, "_token.txt");
   //printf("***In  : %s\n", readInfilename);
   //printf("***Out : %s\n", outputfilename);
   
   token_num = 0;
   id_map = new map<string, int>;
   nline = 1;
   string readtmp = readInfilename;
   string readtt = readtmp.substr(readtmp.rfind(".")+1,readtmp.length()-readtmp.rfind("."));
   if(readtt == "c" || readtt == "java" || readtt == "cpp" || readtt == "cs"){
	   FILE *fp = fopen(readInfilename,"r");
	   //printf("***In  : %s\n", readInfilename);
	   //printf("***Out : %s\n", outputfilename);
	   FILE *fpw = fopen(outputfilename, "w");
	   yyin = fp;
	   while (int token =  yylex()){
	       print_token(token, fpw);
	   }
	   fclose(fpw);
	   fclose(fp);

	   ifstream in;
	   in.open(outputfilename);
	   string buffer;
	   while(getline(in,buffer)){	
	   }
	   in.close();
	  // printf("%s\n",buffer.c_str());
	   if(buffer != "" && buffer.find(",") == buffer.npos){
	       FILE *fpw2 = fopen(outputfilename, "a");
	       fprintf(fpw2, ",%d\n",nline-1);
	       fclose(fpw2);
	   }
	   
	   
   }
   delete id_map;
   
  }
 }
 closedir(dir);
}

*/
int str2int(string string_temp)  
{  
       int int_temp;
       stringstream stream;  
       stream<<string_temp;  
       stream>>int_temp;   
       return int_temp;
}

/*
//声明语义值如下
extern std::string* var_val;
extern int yylval;
*/
//定义print_token
void print_token(int arg_token, FILE * arg_file)
{
	token_num ++;
	//wpc
	/*if(flline1 == 1 && flline2 != 2){	//one for & two ; -> else if
		
	}	
	else if(mline < nline && qline > 0 && pline >0){
		//fprintf(arg_file, ",%d",mline);
		fprintf(arg_file, ",%d\n",mline);
		qline = 0;
		pline = 0;
		flline1 = 0;
		flline2 = 0;
	}*/
	/*if(flline1 == 1 && flline2 < 2){	//one for & less two ; -> keep print // only num for == flline1
		
	}else if(flline1 == 1 && flline2 == 2){	//one for & two ; -> keep print
		flline1 = 0;
		flline2 = 0;
		pline = 0;
	}
	else if(pline >0){	//;or{or}
		//fprintf(arg_file, ",%d",mline);
		if(qline > 0){
		fprintf(arg_file, ",%d\n",mline);}
		qline = 0;
		pline = 0;
		flline1 = 0;
		flline2 = 0;
	}*/	
	if(flline1 == 1 && lpc != rpc){	//num for,if,while == flline1
		
	}else if(flline1 == 1 && lpc == rpc && lpc > 0){	//
		//fprintf(arg_file, ",%d\n",rline);
		fprintf(arg_file, "\n");
		rline=rline_max;
		flline1=0;
		lpc=0;
		rpc=0;
		pline=0;
		ppline=0;
		qline=0;
	}
	else if(pline >0){	//;
		//fprintf(arg_file, ",%d",mline);
		if(qline > 0){
		//fprintf(arg_file, ",%d\n",rline);
		fprintf(arg_file, "\n");
		rline=rline_max;
		lpc=0;
		rpc=0;}
		qline = 0;
		pline = 0;
		ppline=0;
		flline1 = 0;
		flline2 = 0;
	}else if(ppline > 0){// }
		if(mline<nline){
			//fprintf(arg_file, ",%d\n",mline);
			fprintf(arg_file, "\n");
		//rline=rline_max;
		flline1=0;
		lpc=0;
		rpc=0;
		pline=0;
		ppline=0;
		qline=0;
		}
		else if(qline ==0){
			//fprintf(arg_file, ",%d\n",mline);
			fprintf(arg_file, "\n");
		//rline=rline_max;
		flline1=0;
		lpc=0;
		rpc=0;
		pline=0;
		ppline=0;
		qline=0;
		}
	}		
	//
	switch(arg_token)
	{
		case AS:
		{
			qline ++;
			fprintf(arg_file, "AS");
			break;
		}
		case BASE:
		{
			qline ++;
			fprintf(arg_file, "BASE");
			break;
		}
		case CHECKED:
		{
			qline ++;
			fprintf(arg_file, "CHECKED");
			break;
		}
		case DECIMAL:
		{
			qline ++;
			fprintf(arg_file, "DECIMAL");
			break;
		}
		case DELEGATE:
		{
			qline ++;
			fprintf(arg_file, "DELEGATE");
			break;
		}
		case EVENT:
		{
			qline ++;
			fprintf(arg_file, "EVENT");
			break;
		}
		case EXPLICIT:
		{
			qline ++;
			fprintf(arg_file, "EXPLICIT");
			break;
		}
		case FALS:
		{
			qline ++;
			fprintf(arg_file, "FALS");
			break;
		}
		case FIXED:
		{
			qline ++;
			fprintf(arg_file, "FIXED");
			break;
		}
		case FEACH:
		{
			qline ++;
			fprintf(arg_file, "FEACH");
			break;
		}
		case IMPLICIT:
		{
			qline ++;
			fprintf(arg_file, "IMPLICIT");
			break;
		}
		case INTERNAL:
		{
			qline ++;
			fprintf(arg_file, "INTERNAL");
			break;
		}
		case LOCK:
		{
			qline ++;
			fprintf(arg_file, "LOCK");
			break;
		}
		case NSPA:
		{
			qline ++;
			fprintf(arg_file, "NSPA");
			break;
		}
		case NUL:
		{
			qline ++;
			fprintf(arg_file, "NUL");
			break;
		}
		case OBJECT:
		{
			qline ++;
			fprintf(arg_file, "OBJECT");
			break;
		}
		case OPRT:
		{
			qline ++;
			fprintf(arg_file, "OPRT");
			break;
		}
		case OVRD:
		{
			qline ++;
			fprintf(arg_file, "OVRD");
			break;
		}
		case PARAMS:
		{
			qline ++;
			fprintf(arg_file, "PARAMS");
			break;
		}
		case USHORT:
		{
			qline ++;
			fprintf(arg_file, "USHORT");
			break;
		}
		case USING:
		{
			qline ++;
			fprintf(arg_file, "USING");
			break;
		}
		case REDY:
		{
			qline ++;
			fprintf(arg_file, "REDY");
			break;
		}
		case REF:
		{
			qline ++;
			fprintf(arg_file, "REF");
			break;
		}
		case SBYTE:
		{
			qline ++;
			fprintf(arg_file, "SBYTE");
			break;
		}
		case SEALED:
		{
			qline ++;
			fprintf(arg_file, "SEALED");
			break;
		}
		case STALLC:
		{
			qline ++;
			fprintf(arg_file, "STALLC");
			break;
		}
		case STRING:
		{
			qline ++;
			fprintf(arg_file, "STRING");
			break;
		}
		case TRU:
		{
			qline ++;
			fprintf(arg_file, "TRU");
			break;
		}
		case TYPEOF:
		{
			qline ++;
			fprintf(arg_file, "TYPEOF");
			break;
		}
		case UINT:
		{
			qline ++;
			fprintf(arg_file, "UINT");
			break;
		}
		case ULONG:
		{
			qline ++;
			fprintf(arg_file, "ULONG");
			break;
		}
		case UCEKD:
		{
			qline ++;
			fprintf(arg_file, "UCEKD");
			break;
		}
		case USFE:
		{
			qline ++;
			fprintf(arg_file, "USFE");
			break;
		}
		case VIR:
		{
			qline ++;
			fprintf(arg_file, "VIR");
			break;
		}
		case BREAK:
		{
			qline ++;
			fprintf(arg_file, "BREAK");
			break;
		}
		case CASE:
		{
			qline ++;
			fprintf(arg_file, "CASE");
			break;	
		}
		case CHAR:
		{
			qline ++;
			fprintf(arg_file, "CHAR");
			break;	
		}
		case CONST:
		{
			qline ++;
			fprintf(arg_file, "CONST");
			break;	
		}
		case CONTINUE:
		{
			qline ++;
			fprintf(arg_file, "CONTINUE");
			break;	
		}
		case DEFAULT:
		{
			qline ++;
			fprintf(arg_file, "DEFAULT");
			break;	
		}
		case DO:
		{
			qline ++;
			fprintf(arg_file, "DO");
			break;	
		}
		case DOUBLE:
		{
			qline ++;
			fprintf(arg_file, "DOUBLE");
			break;	
		}
		case ELSE:
		{
			qline ++;
			fprintf(arg_file, "ELSE");
			break;	
		}
		case ENUM:
		{
			qline ++;
			fprintf(arg_file, "ENUM");
			break;	
		}
		case EXTERN:
		{
			qline ++;
			fprintf(arg_file, "EXTERN");
			break;	
		}
		case BYTE:
		{
			qline ++;
			fprintf(arg_file, "BYTE");
			break;	
		}/*
		case IMPORT:
		{
			qline ++;
			fprintf(arg_file, "IMPORT");
			break;	
		}*/
		case PUBLIC:
		{
			qline ++;
			fprintf(arg_file, "PUBLIC");
			break;	
		}
		case THROWS:
		{
			qline ++;
			fprintf(arg_file, "THROWS");
			break;	
		}
		case INSOF:
		{
			qline ++;
			fprintf(arg_file, "INSOF");
			break;	
		}
		case TRANS:
		{
			qline ++;
			fprintf(arg_file, "TRANS");
			break;	
		}
		case EXTENDS:
		{
			qline ++;
			fprintf(arg_file, "EXTENDS");
			break;	
		}
		case TRY:
		{
			qline ++;
			fprintf(arg_file, "TRY");
			break;	
		}
		case INTER:
		{
			qline ++;
			fprintf(arg_file, "INTER");
			break;	
		}
		case CLASS:
		{
			qline ++;
			fprintf(arg_file, "CLASS");
			break;	
		}
		case FINALLY:
		{
			qline ++;
			fprintf(arg_file, "FINALLY");
			break;	
		}
		case STRICT:
		{
			qline ++;
			fprintf(arg_file, "STRICT");
			break;	
		}
		case NATIVE:
		{
			qline ++;
			fprintf(arg_file, "NATIVE");
			break;	
		}
		case SUPER:
		{
			qline ++;
			fprintf(arg_file, "SUPER");
			break;	
		}
		case FINAL:
		{
			qline ++;
			fprintf(arg_file, "FINAL");
			break;	
		}
		case CATCH:
		{
			qline ++;
			fprintf(arg_file, "CATCH");
			break;	
		}
		case FLOAT:
		{
			qline ++;
			fprintf(arg_file, "FLOAT");
			break;	
		}
		case PROT:
		{
			qline ++;
			fprintf(arg_file, "PROT");
			break;	
		}
		case THROW:
		{
			qline ++;
			fprintf(arg_file, "THROW");
			break;	
		}
		case IMP:
		{
			qline ++;
			fprintf(arg_file, "IMP");
			break;	
		}
		case BOOLEAN:
		{
			qline ++;
			fprintf(arg_file, "BOOLEAN");
			break;	
		}
		case THIS:
		{
			qline ++;
			fprintf(arg_file, "THIS");
			break;	
		}
		case PRI:
		{
			qline ++;
			fprintf(arg_file, "PRI");
			break;	
		}
		case FOR:
		{
			qline ++;
			flline1 ++;
			lpc=0;rpc=0;
			fprintf(arg_file, "FOR");
			break;	
		}
		case SYN:
		{
			qline ++;
			fprintf(arg_file, "SYN");
			break;	
		}
		case GOTO:
		{
			qline ++;
			fprintf(arg_file, "GOTO");
			break;	
		}
		case IF:
		{
			qline ++;
			flline1 ++;
			lpc=0;rpc=0;
			fprintf(arg_file, "IF");
			break;	
		}
		case ABS:
		{
			qline ++;
			fprintf(arg_file, "ABS");
			break;	
		}
		case ASSERT:
		{
			qline ++;
			fprintf(arg_file, "ASSERT");
			break;	
		}
		case PACK:
		{
			qline ++;
			fprintf(arg_file, "PACK");
			break;	
		}
		case NEW:
		{
			qline ++;
			fprintf(arg_file, "NEW");
			break;	
		}
		case INLINE:
		{
			qline ++;
			fprintf(arg_file, "INLINE");
			break;	
		}
		case INT:
		{
			qline ++;
			fprintf(arg_file, "INT");
			break;	
		}
		case LONG:
		{
			qline ++;
			fprintf(arg_file, "LONG");
			break;	
		}
		case REGISTER:
		{
			qline ++;
			fprintf(arg_file, "REGISTER");
			break;	
		}
		case RESTRICT:
		{
			qline ++;
			fprintf(arg_file, "RESTRICT");
			break;	
		}
		case RETURN:
		{
			qline ++;
			fprintf(arg_file, "RETURN");
			break;	
		}
		case SHORT:
		{
			qline ++;
			fprintf(arg_file, "SHORT");
			break;	
		}
		case SIGNED:
		{
			qline ++;
			fprintf(arg_file, "SIGNED");
			break;	
		}
		case SIZEOF:
		{
			qline ++;
			fprintf(arg_file, "SIZEOF");
			break;	
		}
		case STATIC:
		{
			qline ++;
			fprintf(arg_file, "STATIC");
			break;	
		}
		case STRUCT:
		{
			qline ++;
			fprintf(arg_file, "STRUCT");
			break;	
		}
		case SWITCH:
		{
			qline ++;
			fprintf(arg_file, "SWITCH");
			break;	
		}
		case TYPEDEF:
		{
			qline ++;
			fprintf(arg_file, "TYPEDEF");
			break;	
		}
		case UNION:
		{
			qline ++;
			fprintf(arg_file, "UNION");
			break;	
		}
		case UNSIGNED:
		{
			qline ++;
			fprintf(arg_file, "UNSIGNED");
			break;	
		}
		case VOID:
		{
			qline ++;
			fprintf(arg_file, "VOID");
			break;	
		}
		case VOLATILE:
		{
			qline ++;
			fprintf(arg_file, "VOLATILE");
			break;	
		}
		case WHILE:
		{
			qline ++;
			flline1 ++;
			lpc=0;rpc=0;
			fprintf(arg_file, "WHILE");
			break;	
		}
		case ALIGNAS:
		{
			qline ++;
			fprintf(arg_file, "ALIGNAS");
			break;	
		}
		case ALIGNOF:
		{
			qline ++;
			fprintf(arg_file, "ALIGNOF");
			break;	
		}
		case ATOMIC:
		{
			qline ++;
			fprintf(arg_file, "ATOMIC");
			break;	
		}
		case BOOL:
		{
			qline ++;
			fprintf(arg_file, "BOOL");
			break;	
		}
		case COMPLEX:
		{
			qline ++;
			fprintf(arg_file, "COMPLEX");
			break;	
		}
		case GENERIC:
		{
			qline ++;
			fprintf(arg_file, "GENERIC");
			break;	
		}
		case IMAGINARY:
		{
			qline ++;
			fprintf(arg_file, "IMAGINARY");
			break;	
		}
		case NORETURN:
		{
			qline ++;
			fprintf(arg_file, "NORETURN");
			break;	
		}
		case STATIC_ASSERT:
		{
			qline ++;
			fprintf(arg_file, "STATIC_ASSERT");
			break;	
		}
		case THREAD_LOCAL:
		{
			qline ++;
			fprintf(arg_file, "THREAD_LOCAL");
			break;	
		}
		case FUNC_NAME:
		{
			qline ++;
			fprintf(arg_file, "FUNC_NAME");
			break;	
		}
		case IDENTIFIER:
		{
			/*string * tmpS = new string(yytext);	//case 1
			int loc;
			// Judge whether it exists?
			id_map_iter = id_map -> find(*tmpS);
			
			if(id_map_iter == id_map -> end())
			{
				(*id_map)[*tmpS] = token_num;
				loc = 0;
			}
			else
			{
				loc = token_num - (*id_map)[*tmpS];
				(*id_map)[*tmpS] ++;
			}*/
			qline ++;
			//fprintf(arg_file, "id|%d", loc);
			fprintf(arg_file,"id");
			//delete tmpS;
			
			break;
		}
		case I_CONSTANT:
		{
			qline ++;
			fprintf(arg_file, "CONSTANT");//I_CONSTANT
			break;	
		}
		case F_CONSTANT:
		{
			qline ++;
			fprintf(arg_file, "CONSTANT");//F_CONSTANT
			break;	
		}
		case STRING_LITERAL:
		{
			qline ++;
			fprintf(arg_file, "STRING_LITERAL");
			break;	
		}
		case ELLIPSIS:
		{
			qline ++;
			fprintf(arg_file, "ELLIPSIS");
			break;	
		}
		case RIGHT_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "RIGHT_ASSIGN");
			break;	
		}
		case LEFT_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "LEFT_ASSIGN");
			break;	
		}
		case ADD_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "ADD_ASSIGN");
			break;	
		}
		case SUB_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "SUB_ASSIGN");
			break;	
		}
		case MUL_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "MUL_ASSIGN");
			break;	
		}
		case DIV_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "DIV_ASSIGN");
			break;	
		}
		case MOD_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "MOD_ASSIGN");
			break;	
		}
		case AND_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "AND_ASSIGN");
			break;	
		}
		case XOR_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "XOR_ASSIGN");
			break;	
		}
		case OR_ASSIGN:
		{
			qline ++;
			fprintf(arg_file, "OR_ASSIGN");
			break;	
		}
		case RIGHT_OP:
		{
			qline ++;
			fprintf(arg_file, "RIGHT_OP");
			break;	
		}
		case LEFT_OP:
		{
			qline ++;
			fprintf(arg_file, "LEFT_OP");
			break;	
		}
		case INC_OP:
		{
			qline ++;
			fprintf(arg_file, "INC_OP");
			break;	
		}
		case DEC_OP:
		{
			qline ++;
			fprintf(arg_file, "DEC_OP");
			break;	
		}
		case PTR_OP:
		{
			qline ++;
			fprintf(arg_file, "PTR_OP");
			break;	
		}
		case AND_OP:
		{
			qline ++;
			fprintf(arg_file, "AND_OP");
			break;	
		}
		case OR_OP:
		{
			qline ++;
			fprintf(arg_file, "OR_OP");
			break;	
		}
		case LE_OP:
		{
			qline ++;
			fprintf(arg_file, "LE_OP");
			break;	
		}
		case GE_OP:
		{
			qline ++;
			fprintf(arg_file, "GE_OP");
			break;	
		}
		case EQ_OP:
		{
			qline ++;
			fprintf(arg_file, "EQ_OP");
			break;	
		}
		case NE_OP:
		{
			qline ++;
			fprintf(arg_file, "NE_OP");
			break;	
		}
		case ';':
		{
			qline ++;
			pline ++;
			flline2 ++;
			fprintf(arg_file, "semi");
			break;	
		}
		/*case '{':			//case 1
			fprintf(arg_file, "LB,%d",nline);
			break;
		case '}':
			fprintf(arg_file, "RB,%d",nline);
			break;*/
		//case 2
		case '{':
		{
			fprintf(arg_file, "");
			//pline ++;
			break;
		}
		case '}':
		{
			fprintf(arg_file, "RB");
			//qline ++;
			ppline ++;
			break;	
		}
		case ',':
		{
			qline ++;
			fprintf(arg_file, "comma");
			break;	
		}
		case ':':
		{
			qline ++;
			fprintf(arg_file, "colon");
			break;	
		}
		case '=':
		{
			qline ++;
			fprintf(arg_file, "op_assign");
			break;	
		}
		case '(':
		{
			qline ++;
			lpc++;
			fprintf(arg_file, "LP");
			break;	
		}
		case ')':
		{
			qline ++;
			rpc++;
			fprintf(arg_file, "RP");
			break;	
		}
		case '[':
		{
			qline ++;
			fprintf(arg_file, "LK");
			break;	
		}
		case ']':
		{
			qline ++;
			fprintf(arg_file, "RK");
			break;	
		}
		case '.':
		{
			qline ++;
			fprintf(arg_file, "dot");
			break;	
		}
		case '&':
		{
			qline ++;
			fprintf(arg_file, "op_and");
			break;	
		}
		case '!':
		{
			qline ++;
			fprintf(arg_file, "op_logical_neg");
			break;	
		}
		case '~':
		{
			qline ++;
			fprintf(arg_file, "op_complement");
			break;	
		}
		case '-':
		{
			qline ++;
			fprintf(arg_file, "op_minus");
			break;	
		}
		case '+':
		{
			qline ++;
			fprintf(arg_file, "op_plus");
			break;	
		}
		case '*':
		{
			qline ++;
			fprintf(arg_file, "op_star");
			break;	
		}
		case '/':
		{
			qline ++;
			fprintf(arg_file, "op_div");
			break;	
		}
		case '%':
		{
			qline ++;
			fprintf(arg_file, "op_mod");
			break;	
		}
		case '<':
		{
			qline ++;
			fprintf(arg_file, "OL");
			break;	
		}
		case '>':
		{
			qline ++;
			fprintf(arg_file, "OG");
			break;	
		}
		case '^':
		{
			qline ++;
			fprintf(arg_file, "op_xor");
			break;	
		}
		case '|':
		{
			qline ++;
			fprintf(arg_file, "op_or");
			break;	
		}
		case '?':
		{
			qline ++;
			fprintf(arg_file, "ques");
			break;	
		}
	}
	//wpc
	mline = nline;
	if(qline > 0){
		if(nline<rline){
			rline=nline;
		}
	}
	//

}

int main(int argc, char ** argv) {
	clock_t start, end;
	if(argc != 4)
	{
		printf("one dir required!(for eample: ./a.out /home/myFolder/headers.file /home/outputtoken/ /home/output_CG)\n");
		exit(1);
	}
	strcpy(dirPath,argv[1]);
	strcpy(dirPath1,argv[2]);
	strcpy(dirPath2,argv[3]);
	start = clock();
	//listAllFiles(dirPath);
	//update 11.3
	//ifstream in;
	//in.open(dirPath);
	string buf;
	buf = dirPath;
	//while(getline(in,buf)){
		vector<string> v;
		boost::split(v, buf, boost::is_any_of( "," ), boost::token_compress_on );
		//cout << v[1] << endl;//code block
		nline = 1;
		FILE *fp = fopen(v[1].c_str(),"r");
		//printf("***In  : %s\n", readInfilename);
		//printf("***Out : %s\n", outputfilename);
		string outp=dirPath1;
		outp.append("/").append(v[0]);
		int start_line = str2int(v[2]);
		int end_line = str2int(v[3]);
		//cout << start_line << "," << end_line << endl;
		FILE *fpw = fopen(outp.c_str(), "w");
		yyin = fp;
		while (int token =  yylex()){
			if(nline >= start_line && nline <= end_line)
				print_token(token, fpw);
		}
		fclose(fpw);
		fclose(fp);
		
		ifstream ou;
		ou.open(outp.c_str());
		string outpp=outp;
		outpp.append(".txt");
		//cout << outpp << endl;
		FILE *fpw1 = fopen(outpp.c_str(), "w");
		string buf1;
		int tok_l = 0;
		while(getline(ou,buf1)){
			if(buf1 != "")
			{
				fprintf(fpw1,"%s\n",buf1.c_str());
				//tok_l ++;	// line of tokenized functions
			}
		}
		remove(outp.c_str());

		//string uful = dirPath2;
		//uful.append("/tokenline_num");
		//FILE *fpw2 = fopen(uful.c_str(), "a");
		//fprintf(fpw2,"%d\n",tok_l);
		//cout << v[0] << ":" << tok_l << endl; 
		ou.close();
		fclose(fpw1);
		//fclose(fpw2);

		v.clear();
		vector<string>(v).swap(v);
	//}
	//in.close();
	//update 11.3
    end = clock();
	
	//printf("Using Time: %f\n", (double)(end - start)/ CLOCKS_PER_SEC);
    return 0;
}
