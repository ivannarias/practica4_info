#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int n_arg, char *arg[]) {
	if (n_arg != 3){
		perror("Error al obrir el fitxer");
		return -1;
	}

	int fd1 = open(arg[1],O_RDONLY);
	if (fd1 == -1){
		perror(arg[1]);
		exit (-1);
	}

	int fd2 = open(arg[2],O_RDONLY);
   	if (fd2 == -1) {
       		close(fd1);
		perror(arg[2]);
		exit(-1);
	}

	char buff1, buff2;
        ssize_t bytes1, bytes2;
        int byte_posicio = 1; 		//Posició actual del byte (comença en 1)
        int linia = 1;    		//Número de línia (comença en 1)

	while (1) {
	    	//Llegeix un byte de cada fitxer
    		bytes1 = read(fd1, &buff1, 1);
    		bytes2 = read(fd2, &buff2, 1);

    		//Comprovar si hi ha hagut errors en la lectura
    		if (bytes1 == -1) {
        	    perror("Error al llegir el fitxer1");
        	    close(fd1); //Es tanquen els dos arxius després de donar la sortida de l'error.
        	    close(fd2);
        	    return -1;
    		}

    		if (bytes2 == -1) {
            	    perror("Error al llegir el fitxer2");
        	    close(fd1);
        	    close(fd2);
        	    return -1;
    		}

    		//Si arribem al final dels dos fitxers, sortim del bucle. Determinem que no hem trobat cap diferència.
    		if (bytes1 == 0 && bytes2 == 0) {
        	    break;
    		}

    		//Si un fitxer acaba abans o si els bytes no coincideixen. Bàsicament si es troba alguna diferència acaba el codi.
    		if (bytes1 == 0 || bytes2 == 0 || buff1 != buff2) {
        	    printf("Diferència trobada al byte %d, línia %d\n", byte_posicio, linia);
        	    close(fd1);
        	    close(fd2);
        	    return 0;
    		}

    		//Actualitzar la posició del byte i la línia en cas de que s'acabi aquesta.
    		if (buff1 == '\n' || buff2 == '\n') {
 		   linia++;
		}
    		byte_posicio++;
	}

	//Si arribem aquí, els fitxers són iguals
	close(fd1);
	close(fd2);
	return 0;

}
