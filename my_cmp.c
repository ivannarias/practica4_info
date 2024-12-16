#include <stdio.h>
#include <stdlib.h>

int main(int n_arg, char *arg[]) {
	if (n_arg != 3){
		perror("Error al obrir el fitxer\n")
		return -1
	}

	int fd1 = open(arg[1],O_RDONLY)
	if (fd1 == -1){
		perror(arg[1])
		exit (-1)
	}


	int fd2 = open(arg[2],O_RDONLY);
   	if (fd2 == -1) {
       		int close(fd1)
		perror(arg[2])
		exit(-1)
	}

}
