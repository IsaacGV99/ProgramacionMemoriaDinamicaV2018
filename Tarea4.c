#include <stdio.h>
#include <stdlib.h>
#include "StackQueue.h"
typedef enum{higher, lower, equal}Precedence;
Bool balancedBrackets(char*);
char* InfixToPosfix(char*);
Bool hasHigherPrecedence(char* top, char *operator);


int main(){
	setvbuf(stderr, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	char *posfija;
	char s[100];
	gets(s);
	Bool comprobar;
	comprobar=balancedBrackets(s);
	if(comprobar){
		posfija=InfixToPosfix(s);
		printf("%s",posfija);
	}
	else
		printf("No estan balanceados los braquets");
	free(posfija);
	return 0;
}
Bool balancedBrackets(char* exp){
	char *c;
	Stack expresion;
	expresion=createStack();

	//Ciclo que recorre la cadena
	for(int i=0; exp[i]!='\0';i++){
		if(exp[i]=='('||exp[i]=='[')
			push(expresion,(exp+i));
		else if(exp[i]==')'||exp[i]==']'){
			if(StackisEmpty(expresion))
				return false;
			c=pop(expresion);
			if((exp[i]==')'&&*c!='(')||(exp[i]==']'&&*c!='['))
				return false;
		}
	}
	if(StackisEmpty(expresion))
		return true;
	return false;
}
char* InfixToPosfix(char* exp){
	Stack operadores;
	Queue infija,posfija;
	char *c, *operador, *expfinal;
	operadores=createStack();
	infija=queue_create();
	posfija=queue_create();

	//LLenado de la fila inicial con exp
	for(int i=0; exp[i]!='\0';i++)
		offer(infija,(exp+i));

	//Ciclo que extrae los elementos de la fila inical
	while((c=poll(infija))!=NULL){
		if(*c=='('||*c=='[')
			push(operadores,c);
		else if(*c=='+'||*c=='-'||*c=='*'||*c=='/'){
			//Ciclo se repite mientras sea de mayor precedencia
			while(!hasHigherPrecedence(top(operadores),c)){
				operador=pop(operadores);
				offer(posfija,operador);
			}
			push(operadores,c);
		}
		else if(*c==')'||*c==']'){
			//Vacia la pila hasta encontrar parentesis
			do{
				operador=pop(operadores);
				if(*operador!='('&&*operador!='[')
					offer(posfija,operador);
			}while(*operador!='('&&*operador!='[');
		}
		else if(*c=='='){
			//Ciclo que vacia la pila
			while(!StackisEmpty(operadores)){
				operador=pop(operadores);
				offer(posfija,operador);
			}
			offer(posfija,c);
		}
		else
			offer(posfija,c);
	}
	//Ciclo que vacia la pila
	while(!StackisEmpty(operadores)){
		operador=pop(operadores);
		offer(posfija,operador);
	}
	expfinal=(char*)calloc(size(posfija)*2,sizeof(char));

	//Ciclo que llena la nueva cadena
	for(int i=0;!QueueisEmpty(posfija);i+=2){
		c=poll(posfija);
		expfinal[i]=*c;
		expfinal[i+1]=' ';
	}
	return expfinal;
}
Bool hasHigherPrecedence(char* top, char *operator){
	if(top==NULL||operator==NULL)
		return true;
	int precedence_top, precedence_operator;
	if(*top=='('||*top=='[')
		precedence_top=0;
	if(*top=='+'||*top=='-')
		precedence_top=1;
	else if(*top=='*'||*top=='/')
		precedence_top=2;

	if(*operator=='+'||*operator=='-')
			precedence_operator=1;
	else if(*operator=='*'||*operator=='/')
			precedence_operator=2;

	if(precedence_operator>precedence_top)
		return true;
	return false;

}
