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
	return cpt;
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
        return cpt;
}

void separer_mots(char** result, char *phrase){
	unsigned int i = 0;
	int j = 0;
	int last_i = 0;
	//printf("Commande : %s\n", phrase);
	for(i = 0; i < strlen(phrase) && phrase[i] != '|'; i++){
		if((phrase[i] == ' ' && phrase[i+1] != ' ') || i == strlen(phrase)-1){
			while(isspace(phrase[i]))
                            i++;
                        
                        result[j] = malloc(i - last_i+2);
			strncpy(result[j], &phrase[last_i], i-last_i+1);
			result[j][i-last_i+1] = '\0';
			//printf("Mot : %s\n", result[j]);
			last_i = i; 
			j++;
		}
	}
}



char ***ligne_commande(int *flag, int *nb){
	char *cmd = readline(NULL);
	int nb_cmd = compter_commande(cmd)+2;
        char *** result = malloc(nb_cmd);
	unsigned int i = 0;
	int last_i = 0;
	int cmd_id = 0;

	*flag = 0;
	while(i < strlen(cmd) && (cmd[i] == ' ' || cmd[i] == '|')){
		if(cmd[i] == ' ' || cmd[i] == '|')
			*flag = -1;
		i++;
	}
	while(i < strlen(cmd) && *flag != -1 && cmd_id < nb_cmd){
			if((cmd[i] == '|' || i== strlen(cmd)-1) && cmd[i] != '&'){
                                while((cmd[i] == '|' || cmd[i] == ' ') && i < strlen(cmd)-2){
					i++;
				}		
				char *phrase = malloc(i-last_i+2);
				strncpy(phrase, &cmd[last_i], i-last_i+1);
				phrase[i-last_i+1] = '\0'; 
				result[cmd_id] = malloc(compter_mot(phrase)+2);
				separer_mots(result[cmd_id], phrase);		
                                free(phrase);
				last_i = i;
				cmd_id++;	
			} else if (cmd[i] == '&'){
				i++;
				while(i < strlen(cmd) && cmd[i] == ' ')
					i++;
				if(i >= strlen(cmd)-1)
					*flag = 1;
				else
					*flag = -1;
			}
			i++;
		}
        result[cmd_id] = NULL;
	if(*flag >= 0){
		*nb = nb_cmd-1;
		return result;
	} else		
		return NULL;
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
