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

int fd = open(arxiu, O_CREAT | O_WRONLY | O_TRUNC, 0644); //Obrim un arxiu amb el nom de l'arxiu que volem, i li donem els permissos

if (fd == -1) {
        perror("Error al crear el archivo\n");
        return -1;
}


printf("L'arxiu s'ha creat correctament\n");

char buffer[1];
int bytes_llegits;
										//EXPLICACIÓ WHILE:
while	((bytes_llegits = read(STDIN_FILENO, buffer, 1)) > 0) {			// Mentre no hi hagi errors (read retorna -1) continuem llegint.
	if (bytes_llegits == -1){						// "read" llegeix de l'entrada estàndard (descriptor 0).
            perror("Error al llegir l'entrada\n");				// El primer paràmetre és "STDIN_FILENO" (entrada estàndard).
            close(fd);								// El segon és "buffer", on es guarda el caràcter llegit.
            return -1;								// El tercer és 1, indicant que volem llegir un sol byte.
	}

	if (write(fd, buffer, 1) == -1) { 		// Controlem en cas que hi hagi algun error al escriure ("write" retorna -1 en cas d'error)
            perror("Error al escriure al fitxer\n");
            close(fd);
            return -1;
        }
						     	// Controlem en cas que hi hagi algun error al escriure a la consola.
        if (write(STDOUT_FILENO, buffer, 1) == -1) { 	// "STDOUT_FILENO" és la sortida estàndard (descriptor 1)
            perror("Error al escriure a la consola\n");
            close(fd);
            return -1;
	}
							//SEMPRE TANCAR L'ARXIU ABANS DE SORTIR
}

close(fd);
printf("Has escrit a l'arxiu correctament\n");
return 0;
}
