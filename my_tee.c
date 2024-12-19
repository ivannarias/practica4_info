#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

const char *nom_arxiu (int n_arg, char *arguments[]){
	return arguments[1];
}

int main (int n_arg, char *arg[]){
if (n_arg != 2){
	perror("Error al obrir el fitxer\n"); //En cas de no tenir cap argument, no podem obrir un fitxer amb un nom entrat per teclat
	return -1;
}

const char *arxiu = nom_arxiu(n_arg, arg); //Assignar un nom constant al nostre arxiu

int fd = open(arxiu, O_CREAT | O_WRONLY | O_TRUNC, 0644); 	//Obrim un arxiu amb el nom de l'arxiu que volem, i li donem els permissos
								//Les constants predefinides són codis numèrics que es refereixen al que volem.
if (fd == -1) {							//O_CREAT --> Crea el fitxer en cas que aquest no existeixi.
        perror("Error al crear l'arxiu");			//O_WRONLI --> Obre l'arxiu només en mode escriptura.
        return -1;						//O_TRUNC --> Si l'arxiu ja existeix, esborra tot el contingut (ho deixa buit).
}


printf("L'arxiu s'ha creat correctament\n");
printf("Entra pel teclat el que vulguis escriure a l'arxiu (per sortir pots fer servir ^C):\n");

char buffer[1];		//Creem la variable on guardarem el contingut que llegim, que posteriorment esciurem.
int bytes_llegits;	//Creem una variable int per controlar els errors de les funcions "read".
										//EXPLICACIÓ WHILE:
while	((bytes_llegits = read(STDIN_FILENO, buffer, 1)) > 0) {			// Mentre no hi hagi errors (read retorna -1) continuem llegint.
	if (bytes_llegits == -1){						// "read" llegeix de l'entrada estàndard (descriptor 0).
            perror("Error al llegir l'entrada");				// El primer paràmetre és "STDIN_FILENO" (entrada estàndard).
            close(fd);								// El segon és "buffer", on es guarda el caràcter llegit.
            return -1;								// El tercer és 1, indicant que volem llegir un sol byte.
	}

	if (write(fd, buffer, 1) == -1) { 		// Controlem en cas que hi hagi algun error al escriure ("write" retorna -1 en cas d'error)
            perror("Error al escriure al fitxer");
            close(fd);
            return -1;
        }
						     	// Controlem en cas que hi hagi algun error al escriure a la consola.
        if (write(STDOUT_FILENO, buffer, 1) == -1) { 	// "STDOUT_FILENO" és la sortida estàndard (descriptor 1).
            perror("Error al escriure a la consola");
            close(fd);
            return -1;
	}
							//SEMPRE TANCAR L'ARXIU ABANS DE SORTIR.
}
							//Les constants predefinides STDIN_FILENO i STDOUT_FILENO són els nombres que es refereixen a la barra de comandes (entrada estàndar) i la consola (sortida estàndar).
close(fd);
printf("Has escrit a l'arxiu correctament\n");
return 0;
}
