#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define chsemaph *(intPt+1)
#define fasemaph *(intPt+2)

	int intShmemget,intBufsize=4096; 
	int intShmid;
	char *charPt=0;
	char str[32];
	int *intPt;
	int p1entra,p2entra;
	int turno;
	pid_t pid;

void Proceso1(){
	if(pid==0){
	while(!0){
		p1entra=1;

		while(p2entra==1){
			if(turno==2){
				p1entra=0;
				while(turno==2){}
				p1entra=1;
			}
		}

		printf("CHILD before scanf! *intPt=%d\n",*intPt);
		while(!chsemaph);
		scanf("%c",str);
		fasemaph=1;
		chsemaph=0;
		printf("CHILD %c\n",str[0]);

		if(str[0]=='w'){
			*intPt=*intPt+1;
		}

		printf("CHILD after scanf! *intPt=%d\n",*intPt);
		turno=2;
		p1entra=0;
		}
	}
}
		
void Proceso2(){
	if(pid!=0){
	while(!0){
		p2entra=1;

		while(p1entra==1){
			if(turno==1){
				p2entra=0;
				while(turno==1){}
				p2entra=1;
			}
		}
		
		printf("FATHER --> Pulse una tecla!!!\n",*intPt);
		sleep(1);
		while(!fasemaph);
		scanf("%c",str);
		fasemaph=0;
		chsemaph=1;
		printf("FATHER %c\n",str[0]);

		if(str[0]=='q'){
			*intPt=*intPt+1;
		}

		printf("FATHER -->*intPt=%d\n",*intPt);
		turno=1;
		p2entra=0;
	}
	}
}

int main(int argc, char *argv[])
{
	if((intShmemget=shmget(IPC_PRIVATE,intBufsize,0777))==-1){
		perror(str);
		exit(EXIT_FAILURE);
	}
	intShmid=intShmemget;
	sprintf(str,"ipcs -m --id %d",intShmid);
	system(str);

	if((charPt=shmat(intShmid,NULL,0777))<0){
		sprintf(str,"shmat FAILURE!, %d\n",intShmid);
		perror(str);
		exit(EXIT_FAILURE);
	}
	sprintf(str,"ipcs -m --id %d",intShmid);
	system(str);	
	printf("Shared memory attached at %p\n",charPt);
	intPt=(int*)charPt;
	chsemaph=0;
	fasemaph=1;
	*intPt=0;
	printf("*intPt=%d\n",*intPt);
	pid=fork();
	p1entra=0;
	p2entra=0;
	turno=1;
	Proceso1();
	Proceso2();		
	exit(EXIT_SUCCESS);

}//end main()
