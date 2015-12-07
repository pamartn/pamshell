#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

int compter_commande(char *cmd){
	int length = strlen(cmd);
	int i = 0;
	int cpt = 0;
	while(i < length){
		if(cmd[i] == '|')
			cpt++;
		i++;
	}
	return cpt+1;
}

int compter_mot(char *cmd){
	int length = strlen(cmd);
        int i = 0;
        int cpt = 0;
        while(i < length){
		if(cmd[i] == ' ')
                       cpt++;
                i++;
        }
        return cpt+1;
}

void separer_mots(char** result, char *phrase){
	int i = 0;
	int j = strlen(phrase)-1;
	int cpt = 0;
	int last_i = 0;
	
	while(phrase[i] != '\0' && (isspace(phrase[i]) || phrase[i] == '|' || phrase[i] == '&'))
		i++;
	while(j > 0 && (isspace(phrase[j]) || phrase[j] == '|' || phrase[j] == '&'))
		j--;
	
	last_i = i;
	while(i <= j){
		if(phrase[i] == ' ' || i == j){
			result[cpt] = malloc((i - last_i+2) * sizeof(char));
                        strncpy(result[cpt], &phrase[last_i], i-last_i+1);
                        result[cpt][i-last_i+1] = '\0';
			last_i = i;

			cpt++;
		}
		i++;
	}
	result[cpt] = NULL;
}

int separer_commande(char *cmd, char ***result, int *nb){
	int i = 0;
	int last_i = 0;
	int cpt = 0;
	int length = strlen(cmd);
	int size = 0;
	int flag = 0;	
	while (i < length){
		if(cmd[i] == '&'){
			int tmp = i+1;
			while(tmp < length)
				if(isspace(cmd[tmp]))
					tmp++;
				else{
					result[cpt] = NULL;
					return -1;
				}
			flag = 1;
		}
		if(cmd[i] == '|' || i == length-1){
			char *tmp = malloc(i-last_i+2);
			strncpy(tmp, &cmd[last_i], i-last_i+1);
			tmp[i-last_i+1] = '\0';
			result[cpt] = malloc((compter_mot(cmd)+1)* sizeof(char*));
			size += i-last_i+3;
			separer_mots(result[cpt], tmp);
			cpt++;
			free(tmp);
			last_i = i;
		}
		i++;
	}	
	result[cpt] = NULL;
	*nb = cpt;
	return flag;
}


char ***ligne_commande(int *flag, int *nb){
	char *cmd = readline(NULL);
	char *** result = malloc((compter_commande(cmd)+1) * sizeof(char**));
	int f = separer_commande(cmd, result, nb);
	*flag = f;
	return result;
}

int main(void){
	int flag;
	int nb;
	char ***cmdline = ligne_commande(&flag,&nb);
        
	int i = 0;
        int j = 0;
        while(cmdline[i] != NULL){
            printf("Commande n°%d\n", i);
            
		while(cmdline[i][j] != NULL){
                	printf("Mot : %s\n", cmdline[i][j]);
                	j++;
            	}
            j = 0;
	
            i++;
        }
        printf("FLAG : %d NB : %d\n", flag, nb);
	return 0;
}
