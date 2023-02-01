#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
 
typedef struct infor{
	char* isim;
	int ID;
	char* uyelik;
}infor;
infor* NewPerson(char *name, int ID, char* uyelikT){
	infor* person= (infor*)malloc(1*sizeof(infor));
	person->isim=(char*)malloc(15*sizeof(char));
	person->uyelik=(char*)malloc(sizeof(char));
	//newJob->Name=(char*) malloc((strlen(jobName)+1)*sizeof(char));
	strcpy(person->isim,name);
	//person->isim=name;
	strcpy(person->uyelik,uyelikT);
	person->ID=ID;
//	person->uyelik=uyelikT;
	return person;
}
void printDataBase(infor **dataBase, int n){
	int i;
	for(i=0; i < n; i++){
		printf("\nIsim: %s\nID: %d\nUyelik tipi: %s\n", dataBase[i]->isim, dataBase[i]->ID, dataBase[i]->uyelik);
	}
}

void bubbleSortArtan(infor **dataBase, int n){
	
	int i, j;
	infor tmp;
	
	for(i = 0; i < n-1; i++){
		
		for(j = 0; j < n-i-1; j++){
			
			if(dataBase[j]->ID >dataBase[j+1]->ID){
				
				tmp = *dataBase[j];
				*dataBase[j] = *dataBase[j+1];
				*dataBase[j+1] = tmp;
			}
		}
	}
}
void freeArac(infor *arac){
	
	free(arac->isim);
	free(arac->uyelik);
	free(arac);
}

void freeDataBase(infor **dataBase, int n){
	
	int i;
	
	for(i = 0; i < n; i++){
		
		freeArac(dataBase[i]);
	}
	
	free(dataBase);
}
int main(){
	infor** database;
	int n,i,ID;
	char isim[15];
	char uyelik[1];
	printf("Kullanici sayisini giriniz:");
	scanf("%d",&n);
	database=(infor**)malloc(sizeof(infor*)*n);
/*	for(i=0;i<n;i++){
		database[i]= (infor*)malloc(sizeof(infor)*3);
	}*/
	for(i=0;i<n;i++){
		printf("\nKullanici ismini giriniz: ");
		scanf("%s",isim);
		printf("\nID: ");
		scanf("%d",&ID);
		printf("\nKullanici tipi: ");
		scanf("%s",&uyelik);
		database[i] = NewPerson(isim,ID,uyelik);
	}	
	for(i=0;i<n;i++){
		printf("\nIsim: %s\nID: %d\nUyelik tipi: %s\n", database[i]->isim, database[i]->ID, database[i]->uyelik);	
	}

	bubbleSortArtan(database,n);
	for(i=0;i<n;i++){
		printf("\nIsim: %s\nID: %d\nUyelik tipi: %s\n", database[i]->isim, database[i]->ID, database[i]->uyelik);	
	}	
	freeDataBase(database,n);
	//freeArac(person);

	return 0;
}
