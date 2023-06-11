#define HEADER_FILE


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*declaration of the constant*/
#define NMAX 20
/*declaration of the named pipes*/
char fifo1[10]="./fifo1";
char fifo2[10]="./fifo2";

/*declaration of the question struct*/
struct Question{
/*the pid of the client*/
int clientPid;
/*the number to send to the server*/
int n;

} ;
/*declaration of the response struct*/
struct Reponse{
/*pid of the server*/
int serveurPid;
/*the response*/
int res[NMAX];

} ;

 
