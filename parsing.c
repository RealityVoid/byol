#include <stdio.h>
#include <stdlib.h>

#include "mpc.h"

#ifdef _WIN32
#include <string.h>

static char buffer[2048];

/* Fake readline function */
char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1);
	strcpy(cpy, buffer);
	cpyp[strlen(cpy)-1] = '\0';
	return cpy;
}

void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#endif

int main(int argc, char** argv) {
	mpc_parser_t* Number = mpc_new("number");
	mpc_parser_t* Operator = mpc_new("operator");
	mpc_parser_t* Expr = mpc_new("expr");
	mpc_parser_t* Lispy = mpc_new("lispy");
	
	/* Define them with the following language */
	mpca_lang(MPCA_LANG_DEFAULT,
		"	\
		number: /-?[0-9]+/ ;\
		operator: '+' | '-' | '*' | '/' ; \
		epxr: <number> | '(' <operator> <expr>+ ')' ; \
		lispy: /^/<operator> <expr>+ /$/ ; \
		",Number, Operator, Expr, Lispy);
	mpc_cleanup(4, Number, Operator, Expr, Lispy);
		
	puts("Lispy Version 0.0.0.0.1");
	puts("Press Ctrl+C to Exit\n");
	while(1){
	
		/* Output our prompt and get input */
		char* input = readline("lispy> "); 
		
		/* Add input to history */
		add_history(input);
		
		/* Echo input back to user */
		printf("No you're a %s \n", input);
		
		/* Free retrieved input */
		free(input);
	}
	return 0;
}

