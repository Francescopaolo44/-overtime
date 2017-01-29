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

//---------------------------constant--------------------------
const int number_of_workers = 10;
const int days_of_works = 28;

//---------------------------structure--------------------------
typedef struct{
	int id; /*AUTO INCREMENT */
	char name[100],surname[100],date_of_birth[100],residence[100];
}worker;

//-------------------------function-----------------------------------------

//-------------------------DBMS---------------------------------------------
//function that add a new workers to "database"
void DBMS_add(FILE *config){
	worker database;
	
	//worker's database file 
	FILE *workers_list;
	
	//worker's badge file
	FILE *workers_badge;
	
	char data[100],complex_path[100];
	int i=0,check_load=0,check_exit=0;
	int workers=0,response=1;
	long int position=0;
	
	
	//open in "a" mode to add workers
	workers_list=fopen("workers_database/workers_list/workers_list.txt","a");
	
	//open config.ini
	config=fopen("settings/config.ini","r");

	//read number of workers from setting
	while(fscanf(config,"%s",data) > 0){
		if(strcmp("workers:",data) == 0){
			fscanf(config,"%d",&workers);
			position=ftell(config);
		}
	}
	
	//set autoincrement id to default value of settings.ini
	database.id = workers;
	
	//close config
	fclose(config);
	
	do{
		if(workers < number_of_workers){
			check_load=1;
		}else{
			printf("You have reached max number of workers.");
		}
		if(check_load==1){
			//divider
			fprintf(workers_list,"---------------------------------------\n");
			
			//id
			fprintf(workers_list,"%d\n",database.id);
			
			//------------create badge file for all workers in DB by ID--------
			//create file path with string concatenation of int and string
			sprintf(complex_path,"workers_database/work_hours/%d.txt",database.id);
			workers_badge=fopen(complex_path,"w");
			//initialize worker's day;
			fprintf(workers_badge,"Worker's day: 1");
			fclose(workers_badge);
			//-------------------------------------------------------------------
			 
			printf("Insert worker's surname: ");
			scanf("%s",database.surname);
			//surname	
			fprintf(workers_list,"%s\n",database.surname);
			
			printf("Insert worker's name: ");
			scanf("%s",database.name);
			//name	
			fprintf(workers_list,"%s\n",database.name);
				
			printf("Insert worker's date of birth: [gg mm aa] ");
			
			//empty get for send button
			getchar();
			
			gets(database.date_of_birth);
			//date of birthday	
			fprintf(workers_list,"%s\n",database.date_of_birth);
				
			printf("Insert workers' residence: ");
			scanf("%s",database.residence);
			//residence	
			fprintf(workers_list,"%s\n",database.residence);
				
			workers++;
			check_load=0;
			database.id++;
		}	
		printf("Add another workers?:(S=1/N=0) ");
		scanf("%d",&response);
	}while(response!=0);
	
	//open config.ini
	config=fopen("settings/config.ini","r+");
	//move near number
	fseek(config,93,0);
	//update
	fprintf(config,"%d\b",workers);
	fprintf(config,"\n");
	//close config && workers_list
	fclose(config);
	fclose(workers_list);
}

//function that search a user
void DBMS_search(){
	char surname[100],read_from[100];
	int i,check_workers=0;
	FILE *workers_list;
	
	//open in "r" mode to read workers
	workers_list=fopen("workers_database/workers_list/workers_list.txt","r");
	
	if(workers_list == NULL){
		printf("You have never added a workers to database");
	}else{
		printf("Insert workers surname: ");
		scanf("%s",surname);
		while(fscanf(workers_list,"%s",read_from) > 0){
			if(strcmp(surname,read_from) == 0){
				printf("\nWorker's data\n");
				for(i=0;i<5;i++){
					fscanf(workers_list,"%s",read_from);
					printf("\n%s\n",read_from);
					check_workers=1;
				}
			}
		}
		if(check_workers==0){
			printf("\nThere'isnt workers with this surname");
		}
	}
	//close file
	fclose(workers_list);
}

//function that print all workers
void DBMS_print(){
	FILE *workers_list;
	char workers[100];
	
	//open in "r" mode to read workers
	workers_list=fopen("workers_database/workers_list/workers_list.txt","r");
	
	if(workers_list == NULL){
		printf("You have never added a workers to database");
	}else{
		while(fscanf(workers_list,"%s",workers) > 0){
			printf("%s\n",workers);
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
				for(i=0;i<3;i++){
					fscanf(config,"%s",read_file);
					if(strcmp(password,read_file) == 0){
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
					
					case 2: DBMS_search();
					break;
					
					case 3: DBMS_print();
					break;
					
					default: "wrong action";
				}
				printf("\n\nContinue with DBMS?:(S=1/N=0) ");
				scanf("%d",&scelta);
			}
		}
	}
}
//-------------------------END DBMS-----------------------------------------------

//-------------------------BADGE--------------------------------------------------
void Badge(){
	int id,day=0,check_day=0;
	char complex_path[100],read_day[100];
	char check_entrance=0,check_exit=0;
	int entrance_H=0,entrance_M=0,exit_H=0,exit_M=0;
	
	FILE *workers_badge;
	
	printf("Insert badge ID: ");
	scanf("%d",&id);
	sprintf(complex_path,"workers_database/work_hours/%d.txt",id);
	
	//open badge file fo read
	workers_badge=fopen(complex_path,"r");
	
	//read worker's day
	fseek(workers_badge,14,0);
	fscanf(workers_badge,"%d",&day);
	
	if(workers_badge == NULL){
		printf("\nFile doesn't exist.Have you ever add this worker in the database?");
	}else{
		//close file in 'r' mode"
		fclose(workers_badge);
		
		//open file for appendin hour and update day
		workers_badge=fopen(complex_path,"a");
		
		if(day < days_of_works){
		
			//print day
			if(day == 1 || day == 8 || day == 15 || day == 22){
				fprintf(workers_badge,"\n\nLunedi: ");
				check_day=1;
			}else if(day == 2 || day == 9 || day == 16 || day == 23){
				fprintf(workers_badge,"\n\nMartedì: ");
				check_day=1;
			}else if(day == 3 || day == 10 || day == 17 || day == 24){
				fprintf(workers_badge,"\n\nMercoledì: ");
				check_day=1;
			}else if(day == 4 || day == 11 || day == 18 || day == 25){
				fprintf(workers_badge,"\n\nGiovedì: ");
				check_day=1;				
			}else if(day == 5 || day == 12 || day == 19 || day == 26){
				fprintf(workers_badge,"\n\nVenerdì: ");
				check_day=1;				
			}else if(day == 6 || day == 13 || day == 20 || day == 27){
				fprintf(workers_badge,"\n\nSabato:-");
			}else{
				fprintf(workers_badge,"\n\nDomenica:-");
			}
			if(check_day==1){
				
				//check correct hour for entrance and exit
				do{
					//set green				
					system("color 2F");
					
					//entrance hour
					printf("Insert Entrance Hour: [hh]");
					scanf("%d",&entrance_H);
					
					//entrance minute
					printf("Insert Entrance Minute: [mm]");
					scanf("%d",&entrance_M);
					
					//check right hour
					if(entrance_H>=0 && entrance_H<=23){
						check_entrance=1;
					}else{
						printf("Invalid hour");
					}
					
					//set red				
					system("color 4F");
					
					//exit hour
					printf("Insert Exit Hour: [hh]");
					scanf("%d",&exit_H);
					
					//exit minute
					printf("Insert Exit Hour: [mm]");
					scanf("%d",&exit_M);
					
					//check right hour
					if(exit_H>=0 && entrance_M<=59){
						check_exit=1;
					}else{
						printf("invalid minute");
					}
					
				}while(check_entrance!=1 && check_exit!=1);
				
				//print entrance
				fprintf(workers_badge,"%d",entrance_H);
				fprintf(workers_badge,".");
				fprintf(workers_badge,"%d",entrance_M);
				
				//space
				fprintf(workers_badge," ");
				fprintf(workers_badge,"/");
				fprintf(workers_badge," ");		
				
				//print exit
				fprintf(workers_badge,"%d",exit_H);
				fprintf(workers_badge,".");
				fprintf(workers_badge,"%d\n",exit_M);
				
				day++;
				
			}else{
				printf("Weekend man!");
				day++;
			}
		}else{
			printf("You have worked all 20 days.C'mon man take a little vacation. ");
		}
	}
	//close badge in append mode
	fclose(workers_badge);
	
	//update days of works
	workers_badge=fopen(complex_path,"r+");
	fseek(workers_badge,14,0);
	fprintf(workers_badge,"%d",day);
	
	//close badge in append mode
	fclose(workers_badge);
	
	//set default				
	system("color 3F");
}

//function that print all worker's hour
void Badge_print(){
	int id;
	char complex_path[100],read_hour[100];
	
	FILE *workers_badge;
	
	printf("Insert badge ID: ");
	scanf("%d",&id);
	sprintf(complex_path,"workers_database/work_hours/%d.txt",id);
	
	//open badge file fo read
	workers_badge=fopen(complex_path,"r");
	
	if(workers_badge == NULL){
		printf("\nFile doesn't exist.Have you ever add this worker in the database?");
	}else{
		while(fscanf(workers_badge,"%s",read_hour) > 0){
			printf("%s",read_hour);
		}
	}
	
}

//function that simulate a Electronic Badge
void Badge_menu(){
	int scelta=1,risposta;
	
	while(scelta!=0){
		//clean screen
		system("cls");
		printf("\nWelcome Worker\n\n");
		printf("\nChoose an action: \n");
		printf("|1)Badge                 |\n");
		printf("|2)Print Workers Badge   |\n");	
		printf("\nInsert action: ");
		scanf("%d",&risposta);
				
		switch (risposta){
				
			case 1: Badge();
					break;
			
			case 2: Badge_print();
					break;
					
			default: "wrong action";
		}
		printf("\n\nContinue with Badge?:(S=1/N=0) ");
		scanf("%d",&scelta);
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
			
			case 2: Badge_menu();
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
