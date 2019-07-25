#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "stack.h"

int prior(char c);
char* exec_string(char* str);


int main(){
	
	stack_t s;
	char* str=(char*)malloc(256*sizeof(char));
	init(&s);
	char* end = NULL;
	char tmp[30];
	int i=0;
	while(1){
	double tmp1, tmp2;
	printf("\n>> ");

	fflush(stdin);
	if(!fgets(str,256,stdin)){
		return 1;
	}
		
		str=exec_string(str);
	
		while(*str!='\0'){
		
			switch(*str){

				case '+': 
					push(&s,pop(&s) + pop(&s));
					break;
				case '-':
				       	tmp1=pop(&s);
					tmp2=pop(&s);
					tmp2-=tmp1;
					push(&s,(tmp2));
					break;
				case '/': 
					tmp1=pop(&s);
					tmp2=pop(&s);
					tmp2/=tmp1;
					push(&s,(tmp2));
					break;
				case '*': 
					push(&s,pop(&s) * pop(&s));
					break;
				case ' ':
					break;
				case '\n':
					break;
				case '(':
					break;
				default:
					while(isdigit(*str)>0){
						tmp[i]=*str;
						str++; i++;
					}
					push(&s,strtod(tmp,&end));
					memset(tmp,' ',sizeof(char)*30);
					break;
		}
		str++;		
	}
	
	printf("%-8.4lf\n",pop(&s));
	
	}
	
	free(str);
	free_s(&s);
	return 0;
}

int prior(char c){
	
	switch(c){
		case '*':
		case '/':
			return 3;
		case '+':
		case '-':	
			return 2;
		case '(':
			return 1;
		default: 			
			return -1;
	}
}

char* exec_string(char* str){
	
	int len=strlen(str);
	
	if(len == 0){
		fprintf(stderr, "Ошибка: введена пустая строка\n");
	}

	char* outputstr= (char*) malloc(256*sizeof(char));
	int point=0;
	stack_t* s=NULL;

	while(*str!='\0'){
		
		if(*str>='1' && *str<='9'){
			while(*str>='1' && *str<='9'){
				outputstr[point++]=*str;
				str++;
			}
			outputstr[point++]=' ';
		}
				
		if(*str=='(')
			s=push_c(s,'(');
		if( (*str=='+') || (*str=='-') || (*str=='/') || (*str=='*')){
			if(s==NULL){
				s=push_c(s,*str);
			}else{
				if(prior(s->c)<prior(*str)){
					s=push_c(s,*str);	
				}else{
					while((s!=NULL)&&(prior(s->c)>=prior(*str))){
						outputstr[point++]=pop_c(&s);	
					}
					s=push_c(s,*str);	
				}
			}
		}
		if(*str==')'){
			while((s->c)!='('){
				outputstr[point++]=pop_c(&s);
			}
			pop_c(&s);
		}
		
		str++;
		
	}	
	while(s!=NULL)
		outputstr[point++]=pop_c(&s);
	outputstr[point++]='\0';
//	printf("\n%s\n",outputstr);	
	return outputstr;
}
