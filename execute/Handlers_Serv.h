#define HEADER_FILE
/*Handler sent while waking the client to read response with a the SIGUSR1 signal*/
hand_reveil(int sig){

printf(" the response was sent!\n");

}

/*Execution in case of interuption to end the program*/
fin_serveur(int sig){
/*distruction of the pipes*/
unlink(fifo1);

unlink(fifo2);

printf("\n exit server \n");
exit(0);
}
