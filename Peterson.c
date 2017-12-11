#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FALSE 	0
#define TRUE 	1
#define N	2

int turn;
int interested[N];
int *dato=0;

void enter_region(int process)
{
	int other;

	other=1-process;
	interested[process]=TRUE;
	turn=process;
	while(turn==process && interested[other]==TRUE);
}

void leave_region(int process)
{
	interested[process]=FALSE;
}

void region_critica(int entrada)
{
	*dato=entrada;
	printf("*dato es igual %d\n",*dato);
}

void Proceso0(){
		enter_region(0);
		region_critica(0);
		leave_region(0);
}

void Proceso1(){
		enter_region(1);
		region_critica(1);
		leave_region(1);
}


int main(int argc, char *argv[])
{
	
	int shmg,bsize=4096;
	int shmid;
	char datos[32];

	if((shmg=shmget(IPC_PRIVATE,bsize,0777))==-1){
		sprintf(datos,"shmget FAILURE!, %d\n",shmg);
		perror(datos);
		exit(EXIT_FAILURE);
	}

	shmid=shmg;

	if((dato=shmat(shmid,NULL,0777))<0){
		sprintf(datos,"shmat FAILURE!, %d\n",shmid);
		perror(datos);
		exit(EXIT_FAILURE);
	}
	
	while(!0){
	Proceso0();
	Proceso1();
	}
	exit(EXIT_SUCCESS);

}
