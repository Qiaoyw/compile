#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char txt[1000];  //先全部都进来 
int now;  //txt的指针
 
char token[300];
int array;//token的指针 

int num;//读入的整型数字 

char recent;  //刚读到的字符 

int type;


//清空字符数组
void clearToken(){
	memset(token,'\0',sizeof(token));
	array=0;
} 

//读字符
void getchar1(){
	recent=txt[now];
	now++; 
} 
//后退一格 
void retract(){
	now--;
} 

//把recent的字符放进数组
void catToken(){
	token[array]=recent;
	array++;
} 

//判断字符是否是空格、换行符、Tab
int isSpace(){
	if(recent==' '||recent=='\t'||recent=='\n'){
		return 1;
	}
	else return 0;
} 

//判断是否是字母
int isLetter(){
	if(isupper(recent)||islower(recent)) return 1;
	return 0;
} 
//判断是否是数字
int isDigit(){
	if(isdigit(recent)) return 1;
	return 0;
} 

//查找保留字
int reserver(){
	if(strcmp(token,"BEGIN")) return 1;
	else if(strcmp(token,"END")) return 2;
	else if(strcmp(token,"FOR")) return 3;
	else if(strcmp(token,"IF")) return 4;
	else if(strcmp(token,"THEN")) return 5;
	else if(strcmp(token,"ELSE")) return 6;
	else return 0;
} 

//转化为整数
int transNum(){
	int number=0;
	int i=0;
	for(i=0;i<array;i++){
		number*=10;
		number+=token[i];
	}
	return number;
} 

//错误处理
void error(){
	printf("Unknown\n");
}

void chu(){
	switch(type){
		case 1:
			printf("Begin\n");
			break;
		case 2:
			printf("End\n");
			break;
		case 3:
			printf("For\n");
			break;
		case 4:
			printf("If\n");
			break;
		case 5:
			printf("Then\n");
			break;
		case 6:
			printf("Else\n");
			break;	
		case 7:
			printf("Ident(%s)\n",token);
			break;	
		case 8:
			printf("Int(%d)\n",num);
			break;	
		case 9:
			printf("Colon\n");
			break;
		case 10:
			printf("Plus\n");
			break;
		case 11:
			printf("Star\n");
			break;
		case 12:
			printf("Comma\n");
			break;
		case 13:
			printf("LParenthesis\n");
			break;
		case 14:
			printf("RParenthesis\n");
			break;
		case 15:
			printf("Assign\n");
			break;
		default:
			break;	
	}
}

void getsym(){
	while(token[now]!='\0'){
		clearToken();
    	while(isSpace()) getchar();
    	if(isLetter){                          //字母 
    		while(isLetter()||isDigit()){
	    		catToken();
		    	getchar1();
	    	}
	    	retract();
	    	int end=reserver();  //查保留字
	    	if(end==0) {
	    		type=7;  //标识符
	    	}
	    	else type=end; 
    	} 
    	else if(isDigit){
    		while(isDigit()){
    			catToken();
    			getchar1();
    		}
	    	retract();
	    	num=transNum();
		
    		type=8;
    	}
    	else if(recent==':'){
    		getchar();
    		if(recent=='=') type=15;   //赋值符号，：=
    		else{
	           type=9; 	
	           retract();
    		} 
		
    	}
     	else if(recent=='+') type=10;
    	else if(recent=='*') type=11;
    	else if(recent==',') type=12;
    	else if(recent=='(') type=13;
    	else if(recent==')') type=14;
      	else error();
    	chu();
	}

}
 

int main(int argc, char *argv[]){
	//输入，看看形式
	FILE *fp = NULL;
	fp=fopen("argv[1]","r");
	while(fgets(txt,997,fp)!=NULL){
		now=0;
		memset(txt,'\0',sizeof(txt));
	}
	fclose(fp);
	return 0;
}
