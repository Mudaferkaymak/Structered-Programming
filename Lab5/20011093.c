#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct ogr{
	int  id;       
	char isim[10]; 
	char ders[10]; 
	int puan;	  
}OGR;

int main(){
	FILE *fp;
	int i,sayac=0,toplam = 0;
	OGR o1[4]={{1,"ali","mat1",100},{1,"veli","mat1",30},{1,"ayse","mat1",80},{1,"fatma","mat1",70}};		
	OGR o2[4];
	int N = sizeof(o1)/sizeof(OGR); 
	OGR *ptr = (OGR*) malloc(N*sizeof(OGR));
	fp = fopen("input.txt","w+");
	fwrite(&N,sizeof(int),1,fp);
	fwrite(o1,sizeof(OGR)*N,1,fp);
	fclose(fp);
	FILE *fp1 = fopen("input.txt","r");
	FILE *fp2 = fopen("rapor.txt","w");

	fread(&N,sizeof(int),1,fp1);
	fread(o2,sizeof(OGR)*N,1,fp1);
	char a[4] = ".txt";
	char temp[20];
	for(i=0;i<N;i++){
		strcpy(temp,o2[i].isim);
		strcat(temp,a);
		FILE *fp3 = fopen(temp,"w");	
		fprintf(fp3,"Merhaba %d numarali %s, %s dersinden aldiginiz puan %d\nBasasrilar. Lutfen bu maili yanitlamayiniz",o2[i].id,o2[i].isim,o2[i].ders,o2[i].puan);
		fclose(fp3);
	}


	for(i=0;i<N;i++){
		if(o2[i].puan > 40){
			sayac++;
		}
		toplam += o2[i].puan; 
	}
	toplam = toplam/N;
	fprintf(fp2,"%s dersinin ortalamasi %d basarili ogrenci sayisi %d",o2[0].ders,toplam,sayac);
	fclose(fp2);

}
