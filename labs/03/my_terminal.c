//Omar Alejandro Balboa Lara
//A00825034
//Shell in C for Operating Systems

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

void type_prompt(){
	static int first=1;
	if(first){
		/* limpia la pantalla y formatea el color
		el output se interpreta como comandos, no como caracteres */
		const char* CLEAR_SCREEN_ANSI = "e\[1:1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEN_ANSI,12);
		first=0; //evita que se vuelva a repetir
	}
	//imprime el directorio actual
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("# %s $ ", cwd); //hace display del prompt
}

void read_command(char command[], char *param[]){
	char line[1024];
	int count=0;
	int i=0;
	int j=0;
	char *array[120], *pch;
	
	//Read one line
	for(;;){
		int c=fgetc(stdin);	//obtiene lo que pone el usario, parece getline()
		line[count++]=(char) c;
		//checa que al haya un enter al final
		if(c=='\n'){
			break;
		}
	}
	
	if(count==1){
		return;
	}
	
	//separa por palabras
	pch=strtok(line, "\n");
	
	//checa las palabras
	while(pch!=NULL){
		//separa palabras por array
		array[i++]=strdup(pch);
		pch=strtok(NULL,"\n");
	}
	/*
	//posible linea para implementar el change directory
	if(strcmp(*command,  "cd") == 0){
		chdir(*arrray[0]);
	}
	*/
	
	//array[0] contiene la primera palabra
	strcpy(command, array[0]);
	
	//otros parámetros
	for(; j<i; j++){
		param[j]=array[j];
	}
	param[i] = NULL; //termina con la lista de parámetros
}

int main(){
	//cmd y command se usan para almacenar los comandos
	//par se usa para almacenar los parámetros
	char cmd[120], command[120], *par[50];
	//define las variables de entorno
	char *envp[]={(char *) "PATH=/bin", 0};	//obtiene los comandos del directorio bin
	while(1){	//ciclo principal
		type_prompt();	//hace display del prompt
		read_command(command, par);	//lee la linea de la termimal
		
		if(fork() != 0){
			wait(NULL);
		}
		//crea al child
		else{
		//ejecuta al child
			strcpy(cmd, "/bin/");	//copia el directorio bin en cmp
			strcat(cmd, command);	//concatena el comando en cmp
			execve(cmd, par, envp);	//ejecuta los parámetros
		}
		if(strcmp(command,"exit") == 0){
			//termina el proceso con un exit
			break;
		}
	}
	
	return 0;
}
