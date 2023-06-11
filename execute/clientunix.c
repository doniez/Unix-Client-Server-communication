#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"
#include <signal.h>

int main(){

/* Déclarations */
struct Question quest;
struct Reponse rep;
int i;
/* Ouverture des tubes nommés */
int fone=open(fifo1,O_WRONLY);
int ftwo=open(fifo2,O_RDONLY);

/*initialisation du générateur de nombres aléatoires*/
       srand(getpid());
/* Installation des Handlers */

        signal(SIGUSR1,hand_reveil);


/* Construction et envoi d’une question */

        quest.n= rand() % NMAX + 1;
        quest.clientPid=getpid();

write(fone,&quest,sizeof(struct Question));

/* Attente de la réponse */
pause();

/* Lecture de la réponse */

read(ftwo,&rep,sizeof(struct Reponse));


/* Envoi du signal SIGUSR1 au serveur */

kill(rep.serveurPid,SIGUSR1);


/* Traitement local de la réponse */

printf("this is the client %d \n", quest.clientPid);
printf("interecting with the server %d\n",rep.serveurPid);
printf("the response is : \n");

for(i=0;i<quest.n;i++){
	printf("%d\n",rep.res[i]);
}

}
