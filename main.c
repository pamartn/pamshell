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
	printf("Commande : %s\n", phrase);
	for(i = 0; i < strlen(phrase) && phrase[i] != '|'; i++){
		if(phrase[i] == ' ' || i == strlen(phrase)-1){
			result[j] = malloc(i - last_i+2);
			strncpy(result[j], &phrase[last_i], i-last_i+1);
			result[j][i-last_i+1] = '\0';
			printf("Mot : %s\n", result[j]);
			last_i = i; 
			j++;
		}
	}	
}



char ***ligne_commande(int *flag, int *nb){
	char *cmd = readline(NULL);
	int nb_cmd = compter_commande(cmd)+1;
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
	while(i < strlen(cmd) && *flag != -1){
			if((cmd[i] == '|' || i== strlen(cmd)-1) && cmd[i] != '&'){
				while((cmd[i] == '|' || cmd[i] == ' ') && i < strlen(cmd)-2){
					i++;
				}		
				char *phrase = malloc(i-last_i+2);
				strncpy(phrase, &cmd[last_i], i-last_i+1);
				phrase[i-last_i+1] = '\0'; 
				result[cmd_id] = malloc(compter_mot(phrase));
				separer_mots(result[cmd_id], phrase);		

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
	if(*flag >= 0){
		*nb = nb_cmd;
		return result;
	} else		
		return NULL;
}

int main(void){
	int flag;
	int nb;
	ligne_commande(&flag,&nb);
	printf("FLAG : %d NB : %d\n", flag, nb);
	return 0;
}
