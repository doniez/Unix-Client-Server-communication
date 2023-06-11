#include "serv_cli_fifo.h"

#include "Handlers_Serv.h"

#include <signal.h>

int main() {


  /*declaration*/
  int pipe1, pipe2;

  struct Reponse rep;
  struct Question quest;
  
int i;
/*identifying the server*/
 printf("this is the server %d interacting with : \n", getpid());
 
  /* creation des tubes*/

  pipe1 = mkfifo(fifo1, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
  
  
  pipe2 = mkfifo(fifo2, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP | S_IWOTH);
  
  /*in case of failing to create the pipes the program exists*/

  if (pipe1 < 0 || pipe2 < 0) {
    printf("pipe creation failed!");
    exit(1);
  }

/*initialisation du générateur de nombres aléatoires*/
  srand(getpid());
/* Ouverture des tubes nommés */
  int one = open(fifo1, O_RDONLY);
  int two = open(fifo2, O_WRONLY);

/* Installation des Handlers */

  signal(SIGUSR1, hand_reveil);
  for ( i = 0; i < NSIG; i++) {
    if (i != 10 && i != 16 && i != 30) {
      signal(i, fin_serveur);
    }
  }
 
 

  while (1) {
  

/* lecture d’une question */
  int pipe=read(one, &quest, sizeof(struct Question));
  
  
if(pipe!=0){
    /* construction de la réponse */
    for ( i = 0; i < quest.n; i++) {
      rep.res[i] = rand();
    }
    rep.serveurPid = getpid();

    /* envoi de la réponse */

    write(two, &rep, sizeof(struct Reponse));

    /* envoi du signal SIGUSR1 au client concerné */

    kill(quest.clientPid, SIGUSR1);
    
    /* Traitement local de la réponse */

printf(" client %d", quest.clientPid);

}
  }
  
  
}


