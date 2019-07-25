#include <string.h>
#include <stdlib.h>

#define MAX 100
#define STACK_UNDERFLOW -101
#define STACK_OVERFLOW -100

typedef struct Stack{
	double data[MAX];
	char c;
	size_t size;
	struct Stack *next;
}stack_t;

void init(stack_t* s){
	s->size=0;
	s=NULL;
}

void push(stack_t *s, double val){
	
	if (s->size >= MAX) {
        	exit(STACK_OVERFLOW);
    	} 
	
	s->data[s->size] = val;
	s->size++;
}

double pop(stack_t* s){

	if(s->size==0){
		exit(STACK_UNDERFLOW);
	}
	s->size--;
	return s->data[s->size];
}

stack_t* push_c(stack_t* head, char s){
	stack_t* stc=(stack_t*)malloc(sizeof(stack_t));
	stc->c=s;
	stc->next=head;

	return stc;
}

char pop_c(stack_t** head){
	stack_t* stc=(stack_t*)malloc(sizeof(stack_t));
	char a;
	if(*head==NULL){
		return '\0';
	}
	stc=*head;
	a=stc->c;
	*head=stc->next;
	
	free(stc);
	return a;
}

void free_s(stack_t* s_d){
	free(s_d->data);
	free(s_d);
	free(s_d->next);
}

