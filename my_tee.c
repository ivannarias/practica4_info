#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char* nom_arxiu (int n_arg, char *arguments[]){
	return arguments[1];
}

int main (int n_arg, char *arg[]){
if (n_arg != 2){
	perror("Error al obrir el fitxer"); //En cas de no tenir cap argument, no podem obrir un fitxer amb un nom entrat per teclat
	return -1;
}

const char *arxiu = nom_arxiu(n_arg, arg); //Assignar un nom constant al nostre arxiu

int fd = open(arxiu, O_CREAT | O_WRONLY | O_TRUNC, 0644); //Obrim un arxiu amb el nom de l'arxiu que volem, i li donem els permissos

if (fd == -1) {
        perror("Error al crear el archivo");
        return -1;
}

close(fd);

printf("L'arxiu s'ha creat correctament");
return 0;

}
