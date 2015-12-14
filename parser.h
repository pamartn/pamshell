int compter_commande(char *cmd);
int compter_mot(char *cmd);
int separer_mots(char** result, char *phrase);
int separer_commande(char *cmd, char ***result, int *nb);
char ***ligne_commande(int *flag, int *nb);
void libere(char ***t);
void affiche(char ***t);

