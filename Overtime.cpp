//Informatic project Dellaquila #1

/*realizzare un porgramma che:
calcoli le ore di straordinario effettuate dai 10 dipendenti dell'azienda Creasis.
I dipendenti sono tenuti a lavorare 40 ore settimanali in 5 giorni (DA LUNEDI A VENERDI) e ogni giorno badgiano all'entrata e all'uscita.
Alla fine del mese(di 30 giorni)l'ufficio delle risorse umane, deve sapere quanto ore di straordinario deve pagare a ciascun dipendente.

Tesina

-traccia
-analisi dei dati
-definizione delle strutture dati
-strategia risolutiva
-codice 
-output(videata)

Termine:Mercoledì 2
Linguaggio:C*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//---------------------------structure--------------------------
typedef struct{
	char name[100],surname[100],date_of_birth[100],residence[100];
}worker;




//-------------------------function------------------------------

void DBMS_add(FILE *config){
	worker database;
	FILE *workers_list;
	char data[100];
	int i=0,check_load=0,check_exit=0,workers=0,response=1;
	
	//open in "a" mode to add workers
	workers_list=fopen("workers_database/workers_list/workers_list.txt","a");
	
	//open config.ini
	config=fopen("settings/config.ini","r");

	//read number of workers from setting
	while(fscanf(config,"%s",data) > 0){
		if(strcmp("workers:",data) == 0){
			fscanf(config,"%d",&workers);
		}
	}
	
	do{
		if(workers<10){
			check_load=1;
		}else{
			printf("You have reached max number of workers.");
		}
		if(check_load==1){
			fprintf(workers_list,"---------------------------------------\n");
			
			printf("Insert worker's name: ");
			scanf("%s",database.name);
				
			fprintf(workers_list,"%s\n",database.name);
				
			printf("Insert worker's surname: ");
			scanf("%s",database.surname);
				
			fprintf(workers_list,"%s\n",database.surname);
				
			printf("Insert worker's date of birth: ");
			scanf("%s",database.date_of_birth);
				
			fprintf(workers_list,"%s\n",database.date_of_birth);
				
			printf("Insert workers' residence: ");
			scanf("%s",database.residence);
				
			fprintf(workers_list,"%s\n",database.residence);
				
			workers++;
			check_load=0;
		}	
		printf("Add another workers?:(S=1/N=0) ");
		scanf("%d",&response);
	}while(response!=0);
	
	//update number of workers 
	while(fscanf(config,"%s",data) > 0){
		if(strcmp(data,"workers:") == 0){
			fprintf(config,"%d",workers);
		}
	}
}

//function that simulate a DBMS (Database Management System) to manage all workers in industry
void DBMS_menu(){
	
	int risposta,scelta=1,check_data=0,i;
	char username[100],password[100],read_file[100];
	
	//load config.ini
	FILE *config;
	
	//open config.ini
	config = fopen("settings/config.ini","r");
			
	if(config == NULL){
		printf("\nOps....you delete or move config.ini file. Please restart the program in the same folder of settings/config.ini");
	}else{
		//check if user is admin
		printf("\nInsert admin Username: ");
		scanf("%s",username);
		printf("\nInsert admin Password: ");
		scanf("%s",password);
		while(fscanf(config,"%s",read_file) > 0){
			if(strcmp(username,read_file) == 0){
				printf("\n\nUsername found\n\n");
				for(i=0;i<3;i++){
					fscanf(config,"%s",read_file);
					if(strcmp(password,read_file) == 0){
						printf("\n\nPassword found\n\n");
						check_data=1;
					}
				}
			}
		}
		
		//close config.ini
		fclose(config);
			
		if(check_data!=1){
			printf("\nUsername or password is incorrect.");
		}else{
			while(scelta!=0){
				//clean screen
				system("cls");
				printf("\nWelcome Admin\n\n");
				printf("\nChoose an action: \n");
				printf("|1)Add Workers      |\n");
				printf("|2)Search Workers   |\n");
				printf("|3)Print  Workers   |\n");	
				printf("\nInsert action: ");
				scanf("%d",&risposta);
				
				switch (risposta){
				
					case 1: DBMS_add(config);
					break;
					
					
					default: "wrong action";
				}
				printf("\n\nContinue with DBMS?:(S=1/N=0) ");
				scanf("%d",&scelta);
				system("cls");
			}
		}
	}
}

void menu (){
	
	int risposta,scelta=1;
	
	while(scelta!=0){
		//clean screen
		system("cls");
		
		printf("\n\nChoose an action: \n");
		printf("---------------------|\n");
		printf("|1)DBMS              |\n");
		printf("|2)BADGE             |\n");
		printf("---------------------|\n");
		printf("|3)OVERTIME          |\n");
		printf("\nInsert action: ");
		scanf("%d",&risposta);
		
		switch (risposta){
		
			case 1: DBMS_menu();
			break;
			
			default: "wrong action";
		}
		printf("\n\nContinue with Menu?:(S=1/N=0) ");
		scanf("%d",&scelta);
	}
}
//---------------------------main--------------------------------
int main(){
	
	//initialize design
	system("color 3F");
	system("title Overtime Project by D.F.P");
	printf("Welcome to Overtime Software");
	
	//call menu
	menu();
	
}
