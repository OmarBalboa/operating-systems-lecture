#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>

//Pasamos los dos valores
int main(int argc, char const *argv[]){
	long rc = -1;
	uid_t uid = -1;
	struct passwd *pwd;
	//Funcion que encuentra el usuario
	pwd = getpwnam(argv[2]);
	//Si el usuario es invalido
	if(pwd == NULL){
		fprintf(stderr, "Error: User not found\n");
	} else {
		uid = pwd->pw_uid;
		rc = chown(argv[1], uid, -1);
	}
	//Codigo de comando (-1, 0, 1, 2)
	if(rc == -1){
		fprintf(stderr, "Error: Something went wrong\n");
		exit(0);
	}
	
	return 0;
}
