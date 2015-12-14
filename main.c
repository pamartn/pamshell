#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "parser.h"
#include <unistd.h>

void execute_ligne_commande(){
	int flag;
        int nb;
        char ***cmdline = ligne_commande(&flag,&nb);
	int status[1];
	if(cmdline[0] != NULL){
		if(strcmp(cmdline[0][0], "exit") == 0)
			exit(0);
		int pid = fork();
		if(pid == 0){
			execvp(cmdline[0][0], cmdline[0]);
			perror("execvp");
			exit(1);
		} else {
			if(!flag){
				waitpid(pid, status, 0);	
			}
		}	
	}
	libere(cmdline);
}

void affiche_prompt(){
	char host[32], pwd[1024];
	gethostname(host, 32);
	getcwd(pwd, 1024);
	printf("%s@%s:%s\niutsh$ ", getenv("USER"), host, pwd);
}

int main(void){
	while(1){
		affiche_prompt();
        	execute_ligne_commande();
	}
	return 0;
}

