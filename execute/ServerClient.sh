#!/bin/bash

#set -x 

error1() {
	echo "Missing Client files!" >/dev/stderr
	exit 1
}

error2() {
	echo "Missing Server files!" >/dev/stderr
	exit 1
}

server_source="serveurunix.c"
server_header="Handlers_Serv.h"
server_third_party="serv_cli_fifo.h"
server_executable="serveur"

client_source="clientunix.c"
client_header="Handlers_Cli.h"
client_executable="client"


if [ ! -f "$server_source" ] || [ ! -f "$server_header" ] || [ ! -f "$server_third_party" ]; then
	error2
fi

if [ ! -f "$client_source" ] || [ ! -f "$client_header" ] ; then
        error1
fi
 
Build_server(){
	gcc $server_source -o $server_executable
}

Build_client(){
	gcc $client_source -o $client_executable
}

Build_server
Build_client

clear 

echo "Running server!"
gnome-terminal -- /bin/sh -c './serveur; bash'
sleep 1
for i in 1 2 3 4 5
do
./$client_executable
sleep .5
done
pid_server=$(pidof ./serveur)

sleep 5

kill -2 $pid_server

echo "Script has been succefully executed!"

exit 0

