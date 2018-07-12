#include <stdio.h>
#include <stdlib.h>

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

