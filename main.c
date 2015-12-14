#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "parser.h"
#include <unistd.h>

int lance_commande( int in, int out, char *com, char ** argv){
        int pid = fork();
        if(pid == 0){
                if(in != 0){
                        close(0);
                        dup(in);
			close(in);
                }
                if(out != 1){
                        close(1);
                        dup(out);
			close(out);
                }
                execvp(com, argv);
                perror(com);
                exit(1);
        } else {
		if(in != 0){
			close(in);
		} 
		if(out != 1){
			close(out);
		}
	}
        return pid;
}


void execute_ligne_commande(){
	int flag;
        int nb;
        char ***cmdline = ligne_commande(&flag,&nb);
	int status[1];

	int i = 0;
	int pipes[2];
	
	int in = 0;
	int out = 1;

	for(i = 0; i < nb; i++){
		if(strcmp(cmdline[i][0], "exit") == 0)
			exit(0);
		if(i == nb-1){
			out = 1;
		} else {
			pipe(pipes);
			out = pipes[1];
		}
		int pid = lance_commande(in, out, cmdline[i][0], cmdline[i]);
		in = pipes[0];
		if(pid != 0){
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
	printf("%s@%s:%s\n--> ", getenv("USER"), host, pwd);
}

int main(void){
	while(1){
		affiche_prompt();
        	execute_ligne_commande();
	}
	return 0;
}

