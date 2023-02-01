#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>

typedef struct Ogrenci { 
	char ogrID[9]; 
	char ad[30]; 
	char soyad[30]; 
	int puan; 
	struct Ogrenci *next; 
	struct Ogrenci *prev;
}OGRENCI;
typedef struct Yazar { 
	int yazarID; 
	char yazarAd[30]; 
	char yazarSoyad[30]; 
	struct Yazar *next;
}YAZAR;

typedef struct KitapOrnek {
 	char EtiketNo[20];
 	char Durum[8]; 
 	struct KitapOrnek *next ;
 }KITAPORNEK;
 
typedef struct Kitap {
	char kitapAdi[30]; 
	char ISBN[13]; 
	int adet;
	struct Kitap *next; 
	struct KitapOrnek *head; 
}KITAP;

typedef struct KitapYazar{ 
	char ISBN[13]; 
	int YazarID;
}KITAPYAZAR;

typedef struct Tarih{ 
	unsigned int gun:5; 
	unsigned int ay:4; 
	unsigned int yil:12;
}TARIH;

typedef struct KitapOdunc{
	char EtiketNo[20]; 
	char ogrID[9]; 
	unsigned int islemTipi:1; 
	struct Tarih islemTarihi;
}KITAPODUNC;
int ogrenciMenu();
int anaMenu();
int kitapMenu();
int yazarMenu();
int IDkontrol(char* IDgelen,OGRENCI* r);
void getCharMenu();
void ogrenciEkle(const char*, OGRENCI**);
void ogrenciYazdirma(OGRENCI* head);
void ogrenciSil(const char* fileName, OGRENCI** head);
void ogrenciDosyaOkuma(const char* fileName, OGRENCI** head);
void ogrenciDuzenle(const char*,OGRENCI**);
void ogrenciBilgiGoster(const char*,int,KITAPODUNC***,OGRENCI**);
void cezaliOgrenciListele(OGRENCI*);
void kitapTeslimEtmemis(KITAPODUNC***,OGRENCI**,int);
void yazarEkle(const char*,YAZAR**);
void yazarDosyaOkuma(const char* fileName, YAZAR**);
int yazarSil(const char* fileName,YAZAR**,const char*,KITAPYAZAR***,int);
void yazarYazdirma(YAZAR*);  
void yazarDuzenle(const char*,YAZAR**);
void kitapEkle(const char* fileName,KITAP**);
void kitapYazdirma(KITAP* head);
void kitapSil(const char* fileName, KITAP** head);
void kitapDosyaOkuma(const char* fileName, KITAP** head);
void kitapOrnekOlustur(KITAP** );
void kitapBilGoster(KITAP* head);
void kitapDuzenle(const char*,KITAP**);
void teslimEdilmeyenKitap(KITAP*);
int kitapYazarEsDosya(const char*,KITAPYAZAR***);
int kitapYazarEslestir(const char*,KITAPYAZAR***,int,KITAP*,YAZAR*);
int kitapOdunc(const char*,KITAPODUNC***,int,KITAP**, OGRENCI**, const char*);
int kitapYazarGuncelle(const char*,KITAPYAZAR***,int,KITAP*,YAZAR*);


int main(){
	int exitControl=1,secim,secim1,kitapYazarSayac=0,kitapOduncSayac=0;
	OGRENCI *head1 = NULL;
	YAZAR *head2 = NULL;
	KITAP *head3 = NULL;
	KITAPYAZAR** kitapYazarArr = (KITAPYAZAR**)malloc(sizeof(KITAPYAZAR*)*1);
	KITAPODUNC** kitapOduncArr = (KITAPODUNC**)malloc(sizeof(KITAPODUNC*)*1);
	ogrenciDosyaOkuma("Ogrenciler.csv",&head1);
	yazarDosyaOkuma("Yazarlar.csv",&head2);
	kitapDosyaOkuma("Kitaplar.csv",&head3);
	kitapYazarSayac = kitapYazarEsDosya("KitapYazar.csv",&kitapYazarArr);
		while(exitControl==1){
			secim = anaMenu();
			switch(secim){
				case 1: 
					system("cls");
					secim1 = ogrenciMenu(); //Ýlk menüde 1'e girerse ikinci menüde girdiði deðeri - ile toplayýp return yapýyorum
					if(secim1 == 0){
							ogrenciEkle("Ogrenciler.csv", &head1);
							printf("\nGUNCEL OGRENCI LISTESI\n\n");
							ogrenciYazdirma(head1);
							getCharMenu();

					}
					else if(secim1 == 5){
							ogrenciYazdirma(head1);	
							getCharMenu();
					}
					else if(secim1 == (-1)){
							ogrenciYazdirma(head1);
							ogrenciSil("Ogrenciler.csv",&head1);
							system("cls");
							printf("\nOgrenci Listesinin Guncel Hali\n");
							ogrenciYazdirma(head1);
							getCharMenu();
					}
					else if(secim1 == (-2)){
							ogrenciDuzenle("Ogrenciler.csv",&head1);
							system("cls");
							printf("\nOgrenci Listesinin Guncel Hali\n");
							ogrenciYazdirma(head1);
							getCharMenu();
					}
					else if(secim1 == 6){
							kitapOduncSayac = kitapOdunc("KitapOdunc.csv",&kitapOduncArr,kitapOduncSayac,&head3,&head1,"Ogrenciler.csv");
							getCharMenu();
					}
					else if(secim1 == 2){
							ogrenciBilgiGoster("KitapOdunc.csv",kitapOduncSayac,&kitapOduncArr,&head1);
							getCharMenu();
					}
					else if(secim1 == 3){
							kitapTeslimEtmemis(&kitapOduncArr,&head1,kitapOduncSayac);
							getCharMenu();
					}
					else if(secim1 == 4){
							cezaliOgrenciListele(head1);
							getCharMenu();
					}

					break;
				case 2:
					system("cls");
					secim1 = kitapMenu();
					if(secim1 == 3){
							kitapYazdirma(head3);
							getCharMenu();
					}
					else if(secim1 == (-1)){
							kitapYazdirma(head3);
							kitapSil("Kitaplar.csv",&head3);
							printf("Kitap Listesinin Guncel Hali\n");
							kitapYazdirma(head3);
							getCharMenu();
					}					
					else if(secim1 == (-2)){
							kitapDuzenle("Kitaplar.csv",&head3);
							printf("\nKitap Listesinin Guncel Hali\n");
							kitapYazdirma(head3);
							getCharMenu();
					}
					else if(secim1 == 0){
							kitapEkle("Kitaplar.csv",&head3);
							printf("\nKitap Listesinin Guncel Hali\n");
							kitapYazdirma(head3);
							getCharMenu();
					}
					else if(secim1 == 2){
							kitapYazdirma(head3);
						    kitapBilGoster(head3);
						    getCharMenu();
					}
					else if(secim1 == 4){
							teslimEdilmeyenKitap(head3);
							getCharMenu();		
					}
					else if(secim1 == 5){
							kitapYazarSayac = kitapYazarEslestir("KitapYazar.csv",&kitapYazarArr,kitapYazarSayac,head3,head2);
							kitapYazarSayac++;
							getCharMenu();
					}
					else if(secim1 == 6){
							kitapYazdirma(head3);
							kitapYazarSayac = kitapYazarGuncelle("KitapYazar.csv",&kitapYazarArr,kitapYazarSayac,head3,head2);
							getCharMenu();
					}
					break;
				case 3:
					system("cls");
					secim1 = yazarMenu();
					if(secim1 == 2){
							yazarYazdirma(head2);
							getCharMenu();

					}
					else if(secim1 == 0){
							yazarEkle("Yazarlar.csv",&head2);
							yazarYazdirma(head2);
							getCharMenu();

					}
					else if(secim1 == (-1)){
							yazarYazdirma(head2);
							kitapYazarSayac = yazarSil("Yazarlar.csv",&head2,"KitapYazar.csv",&kitapYazarArr,kitapYazarSayac);
					//		system("cls");
							printf("Guncel Yazar Listesi \n");
							yazarYazdirma(head2);
							getCharMenu();
					}
					else if(secim1 == (-2)){
							yazarYazdirma(head2);
							yazarDuzenle("Yazarlar.csv",&head2);
							printf("Guncel Yazar Listesi \n");
							yazarYazdirma(head2);
							getCharMenu();	
					}
					break;	
				case 0:
					exitControl=0;
					break;
			}
				
		
	}

	return 0;
}
int ogrenciMenu(){
	int secim,secim2;
	printf("\n-----OGRENCI MENU-----\n");
	printf("[1]-Ogrenci Bilgisi Guncelleme\n[2]-Ogrenci Bilgisi Gorunteleme\n[3]-Kitap Teslim Etmemis Ogrencileri Listele\n[4]-Cezali Ogrencileri Listele\n[5]-Tum Ogrencileri Listele\n[6]-Kitap Odunc Al/Teslim Et\n[7]-Ust Menu");
	scanf("%d",&secim);
	if(secim==1){
	    	system("cls");
	    	printf("[1]-Ogrenci Ekle\n[2]-Ogrenci Sil\n[3]-Ogrencinin Bilgisini Guncelle\n[4]-Ust Menu\n");
	    	scanf("%d",&secim2);
	    	if(secim2==0){
	    		secim2=4;
			}
	    	return secim-secim2;
		}else
			return secim;
			
}	
int anaMenu(){
	int secim;
	system("cls");
	printf("\t\t\t\t\t\tKUTUPHANE OTOMASYONU");
	printf("\n\n");
	printf("-----ANA MENU-----\n[1]-Ogrenci Islemleri\n[2]-Kitap Islemleri\n[3]-Yazar Islemleri\n[0]-Cikis\n");
	scanf("%d",&secim);
	return secim;
}
int kitapMenu(){
	int secim,secim2;
	printf("\n-----KITAP MENU-----\n");
	printf("[1]-Kitap Durumu guncelleme\n[2]-Kitap Bilgisi Gorunteleme\n[3]-Raftaki Kitaplari Listele\n[4]-Iade Edilmemis Kitaplari Listele\n[5]-Kitap-Yazar Eslestir\n[6]-Kitabin Yazarini Guncelle\n[7]-Ust Menu");
	scanf("%d",&secim);
	if(secim==1){
		system("cls");
	   	printf("[1]-Kitap Ekle\n[2]-Kitap Sil\n[3]-Kitap Bilgisini Guncelle\n[0]-Ust Menu\n");
	   	scanf("%d",&secim2);
	   	return secim-secim2;
	}else
		return secim;

}
int yazarMenu(){
	int secim,secim2;
	printf("\n-----YAZAR MENU-----\n");
	printf("[1]-Yazar Durumu Guncelleme\n[2]-Yazar Bilgisi Goruntuleme\n[3]-Ust Menu\n");
	scanf("%d",&secim);
	if(secim==1){
		system("cls");
	   	printf("[1]-Yazar Ekle\n[2]-Yazar Sil\n[3]-Yazar Bilgisini Guncelle\n[4]-Ust Menu\n");
	   	scanf("%d",&secim2);
	   	return secim-secim2;		
	}else
		return secim;	
}
void getCharMenu(){
	printf("\nAna menuye donmek icin bir tusa basiniz\n ");
	getch();
}
//OGRENCI ÝSLEMLERÝ
void ogrenciEkle(const char* fileName, OGRENCI** head){
	int puan;

	OGRENCI* yeniOgrenci;
	yeniOgrenci = (OGRENCI*)malloc(sizeof(OGRENCI));
	printf("\nOgrenci ismi = ");
	scanf("%29s",yeniOgrenci->ad);
	printf("\nOgrenci soyadi = ");
	scanf("%29s",yeniOgrenci->soyad);
	printf("\nOgrenci ID = ");
	scanf("%9s",yeniOgrenci->ogrID);

	yeniOgrenci->puan = 100;
	yeniOgrenci->next = *head;
	yeniOgrenci->prev = NULL;
	*head = yeniOgrenci;
	
	FILE *fp = fopen(fileName, "a");
	if(fp == NULL){
		printf("Dosya acilirken hata olustu\n");
		exit(1);
	}
	
	fprintf(fp, "\n%s,%s,%s,%d", yeniOgrenci->ogrID, yeniOgrenci->ad,yeniOgrenci->soyad, yeniOgrenci->puan);
	fclose(fp);

}
int IDkontrol(char* IDgelen,OGRENCI* r){
	while(strcmp(r->ogrID,IDgelen)!=0 && r->next!=NULL){
		r = r->next;
	}
	if(strcmp(r->ogrID,IDgelen)==0){
		return 1;	
	}
	else
		return 0;
}
void ogrenciYazdirma(OGRENCI* head){
	OGRENCI* current = head;
	while(current != NULL){
		printf("\nIsim = %s  Soyad = %s  ID = %s  Puan = %d\n",current->ad,current->soyad,current->ogrID,current->puan);
		current = current->next;
	}
}
void ogrenciSil(const char* fileName, OGRENCI** head){
	int kontrol = 1;
	char* ID = (char*)malloc(sizeof(char)*9);
	printf("Silmek istediginiz ogrencinin ID'sini giriniz\n");
	scanf("%8s",ID);
	
	OGRENCI* current = *head;
	while(current!=NULL&&kontrol){
		if(strcmp(current->ogrID,ID) == 0){
			kontrol=0;
		}else{
			current=current->next;
		}
	}
	if(kontrol){
		printf("\nGirdiginiz ID'ye sahip ogrenci bulunmamaktadir!\n");
		getCharMenu();
	}else{
	
	OGRENCI* temp = *head;
	while(strcmp(temp->ogrID,ID)!=0 && temp!=NULL){
		temp=temp->next;
	}
	if(temp->prev != NULL){
		temp->prev->next=temp->next;
	}
	if(temp->next != NULL){
		temp->next->prev=temp->prev;
	}
	if(temp == *head){
		*head =	temp->next; 
	}
	
	free(temp);
	
	FILE *fp = fopen(fileName, "w");
	if(fp ==NULL){
		printf("Dosya acilirken hata olustu!\n");
		exit(1);
	}
	
	temp = *head;
    while (temp != NULL) {
        fprintf(fp, "%s,%s,%s,%d\n", temp->ogrID, temp->ad, temp->soyad, temp->puan);
        temp = temp->next;
    }
    fclose(fp);
	}
	
}
void ogrenciDosyaOkuma(const char* fileName, OGRENCI** head){
	FILE *fp = fopen(fileName, "r");
	
	if(fp == NULL){
		printf("Dosya acilirken hata olustu!\n");
		exit(1);
	} 
	char line[1024];
	while(fgets(line,1024,fp) != NULL){
		OGRENCI* ogrenci = (OGRENCI*)malloc(sizeof(OGRENCI));
		if(ogrenci == NULL){
			printf("Error allocating memory!\n"); 
            exit(1);
		} 
        sscanf(line, "%8[^,], %29[^,], %29[^,],%d", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad,&ogrenci->puan);
        ogrenci->ogrID[8] = '\0';
        ogrenci->next = *head;
        ogrenci->prev = NULL;
        if (*head != NULL) {
            (*head)->prev = ogrenci;
        }
        *head = ogrenci;
		
	}
	fclose(fp);
}
void ogrenciDuzenle(const char* fileName,OGRENCI** head){
	char* ID = (char*)malloc(sizeof(char)*9);
	printf("\nGuncelleme yapmak istediginiz ogrencinin ID'sini giriniz = ");
	scanf("%8s",ID);
	OGRENCI* temp = *head;
	OGRENCI* bas  = *head;
	
	int kontrol = 1;
	while(temp!=NULL && kontrol){
		if(strcmp(temp->ogrID,ID) == 0){
			kontrol=0;
		}else{
			temp=temp->next;
		}
	}
	
	if(kontrol){
		printf("\nGirdiginiz ID'ye sahip ogrenci bulunamadi\n");
		printf("\nDevam etmek icin bir tusa basiniz\n");
		getch();
	}
	else{
		printf("\nOgrencinin bilgileri\nIsim = %s	Soyisim = %s	ID = %s		Puan = %d\n",temp->ad,temp->soyad,temp->ogrID,temp->puan);
		printf("\nOgrencinin yeni ismi = ");
		scanf("%30s",temp->ad);
		printf("\nOgrencinin yeni soyismi = ");
		scanf("%30s",temp->soyad);
		printf("\nOgrencinin yeni puani = ");
		scanf("%d",&temp->puan);
		
		FILE *fp = fopen(fileName,"w");
		
		if(fp == NULL){
			printf("\nDosya acilirken hata olustu\n");
		}

		while(bas){
        fprintf(fp, "%s,%s,%s,%d\n", bas->ogrID, bas->ad, bas->soyad, bas->puan);
        bas = bas->next;
		}
		
		fclose(fp);
	}
}
//YAZAR ÝSLEMLERÝ
void yazarDosyaOkuma(const char* fileName, YAZAR** head){
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL){
		printf("Dosya acilirken hata olustu!\n");
		exit(1);
	}
	char line[1024];
	while(fgets(line,1024,fp) != NULL){
		YAZAR* yazar=(YAZAR*)malloc(sizeof(YAZAR));
		if(yazar==NULL){
			printf("Error allocating memory!\n");
			exit(1);
		}
        sscanf(line, "%d, %29[^,], %29[^\n]",&yazar->yazarID,yazar->yazarAd,yazar->yazarSoyad);

		yazar->next = *head;
		*head = yazar;
	}
	fclose(fp);	
}
void yazarEkle(const char* fileName, YAZAR** head){
	int IDKontrol = 0;
	YAZAR* yeniYazar = (YAZAR*)malloc(sizeof(YAZAR));
	YAZAR* current = *head;
	YAZAR* enBuyukId = *head;
	printf("\nYazar ismi = ");
	scanf("%29s",yeniYazar->yazarAd);
	printf("\nYazar soyismi = ");
	scanf("%29s",yeniYazar->yazarSoyad);

	
	while(current->next != NULL){
		if(current->yazarID > IDKontrol){
		 	enBuyukId =	current;
		 	IDKontrol = current->yazarID;
		}
			current = current->next;
	}
	yeniYazar->yazarID = enBuyukId->yazarID + 1; 
	yeniYazar->next = *head;
	*head=yeniYazar;
	
	FILE *fp = fopen(fileName,"a");
	if(fp == NULL){
		printf("Dosya acilirken bir hata olustu!\n");
	}
	
	fprintf(fp, "\n%d,%s,%s",yeniYazar->yazarID,yeniYazar->yazarAd,yeniYazar->yazarSoyad);
	fclose(fp);
	
}
int yazarSil(const char* fileName,YAZAR** head,const char* fileName1,KITAPYAZAR*** arr,int n){
	int ID,kontrol=1;
	printf("\nSilmek istediginiz yazarin ID'sini giriniz = \n");
	scanf("%d",&ID);
	YAZAR* current = *head;

	while(current!=NULL&&kontrol){
		if(current->yazarID==ID){
			kontrol=0;
		}else{
			current=current->next;
		}
}
    if(kontrol){
        printf("Girdiginiz ID numarasina sahip yazar bulunmamaktadir!\n\n");
        return;
    }else{
	
	if(current == *head){
		*head=current->next;
		free(current);
	}else{
	YAZAR* prev = *head;
	while(prev->next != current){
		prev=prev->next;
	}
		prev->next=current->next;
		free(current);
	}
		FILE *fp=fopen(fileName,"w");
	if(fp == NULL){
		printf("\nDosya acilirken bir hata olustu.\n");
	}
	YAZAR* queu = *head;
	while(queu != NULL){
		fprintf(fp,"%d,%s,%s\n",queu->yazarID,queu->yazarAd,queu->yazarSoyad);
		queu=queu->next;	
	}
	
	fclose(fp);
	
	//KÝTAP YAZAR DOSYASINDA YAZARIN ESLESMELERÝNÝ -1 YAPMAK	
	FILE *fp1 = fopen(fileName1, "w");
	if(fp1 == NULL){
		printf("\nDosya acilirken bir hata olustu.\n");	
	}
	int i;
	for(i=0;i<(n);i++){
		if((*arr)[i]->YazarID == ID){
			(*arr)[i]->YazarID = -1;
		}
			fprintf(fp1,"%s,%d\n",(*arr)[i]->ISBN,(*arr)[i]->YazarID);
//			printf("%s,%d\n",(*arr)[i]->ISBN,(*arr)[i]->YazarID);
	}
	fclose(fp1);

	}
	return n;
}
void yazarYazdirma(YAZAR* head){
	YAZAR* current = head;
	while(current != NULL){
		printf("\nYazar ID = %d   Isim = %s    Soyisim = %s ",current->yazarID,current->yazarAd,current->yazarSoyad);
		current = current->next;
	}
}
void yazarDuzenle(const char* fileName,YAZAR** head){
	int ID;
	int kontrol = 1;
	YAZAR* current = *head;
	YAZAR* bas = *head;
	printf("\nDuzenlemek istediginiz yazarin ID'sini girin = ");
	scanf("%d",&ID);
	
	while(current!=NULL && kontrol){
		if(current->yazarID==ID){
			kontrol=0;
		}
		else{
			current=current->next;
		}
	}
	if(kontrol == 0){
	printf("\nYazarin bilgileri\nIsim = %s	Soyisim = %s	ID = %d \n",current->yazarAd,current->yazarSoyad,current->yazarID);
	printf("\nYeni yazar ismi = ");
	scanf("%29s",current->yazarAd);
	printf("\nYeni yazar soyismi = ");
	scanf("%29s",current->yazarSoyad);

	FILE *fp = fopen(fileName, "w");
	if(fp == NULL){
			printf("\nDosyayi acarken bir hata olustu!\n");
	}

	while(bas != NULL){
		fprintf(fp,"%d,%s,%s\n",bas->yazarID,bas->yazarAd,bas->yazarSoyad);
		bas = bas->next;	
	}
	
	fclose(fp);	
	}else{
		printf("\nGirdiginiz ID numarasina sahip yazar bulunamadi!\n");
		return;
	}
}
//KÝTAP ÝSLEMLERÝ
void kitapEkle(const char* fileName,KITAP** head){
	char isim[30];
	KITAP* yeniKitap = (KITAP*)malloc(sizeof(KITAP));
	printf("\nKitap ismi = ");
	fflush(stdin);
	scanf("%[^\n]s",yeniKitap->kitapAdi);
	printf("\nKitap ISBN = ");
	scanf("%13s",yeniKitap->ISBN);
	printf("\nAdet = ");
	scanf("%d",&yeniKitap->adet);
	yeniKitap->next = *head;
	kitapOrnekOlustur(&yeniKitap);
	*head=yeniKitap;
	
	FILE *fp = fopen(fileName,"a");
	if(fp == NULL){
		printf("Dosya acilirken bir hata olustu!\n");
	}
	
	fprintf(fp,"\n%s,%s,%d",yeniKitap->kitapAdi,yeniKitap->ISBN,yeniKitap->adet);
	fclose(fp);
	
}
void kitapYazdirma(KITAP* head){
		KITAP* current = head;
		while(current != NULL){
			printf("\nKitap Ad = %s   Kitap ISBN = %s    Kitap Adet = %d \n",current->kitapAdi,current->ISBN,current->adet);
			current = current->next;
		}
}
void kitapSil(const char* fileName, KITAP** head){
	char* ISBN=(char*)malloc(sizeof(char)*14);
	int kontrol =1;
	
	printf("\nSilmek istediginiz kitabin ISBN'ini giriniz = ");
	scanf("%13s",ISBN);
	
	KITAP* current = *head;
	while(current != NULL  && kontrol){
		if(strcmp(current->ISBN,ISBN) == 0){
			kontrol=0;
		}else{
			current=current->next;
		}
	}
	if(kontrol){
		printf("\nGirdiginiz ISBN koduna sahip kitap bulunamadi!\n\n");
	}
	else{
	system("cls");
	
	if(current == *head){
		*head=current->next;
		free(current);
	}else{
	KITAP* prev = *head;
	while(prev->next != current){
		prev=prev->next;
	}
	prev->next=current->next;
	free(current);
		
	}

	
	FILE *fp=fopen(fileName,"w");
	if(fp == NULL){
		printf("\nDosya acilirken bir hata olustu.\n");
	}
	KITAP* queu = *head;
	while(queu != NULL){
		fprintf(fp,"%s,%s,%d\n",queu->kitapAdi,queu->ISBN,queu->adet);
		queu=queu->next;	
	}
	
	fclose(fp);
	
	}
}
void kitapDosyaOkuma(const char* fileName, KITAP** head){
	
	FILE *fp = fopen(fileName, "r");
	if(fp == NULL){
		printf("Dosya acilirken hata olustu!\n");
		exit(1);
	}
	char line[1024];
	while(fgets(line,1024,fp) != NULL){
		KITAP* kitap=(KITAP*)malloc(sizeof(KITAP));
		if(kitap==NULL){
			printf("Error allocating memory!\n");
			exit(1);
		}
        sscanf(line, "%29[^,], %13[^,],%d",kitap->kitapAdi,kitap->ISBN,&kitap->adet);
		kitapOrnekOlustur(&kitap);
		kitap->next = *head;
		*head = kitap;
	}
	fclose(fp);	
}
void kitapOrnekOlustur(KITAP** kitap){
	int i;
	char str[10];
	KITAPORNEK* root;
	char *ISBN=(char*)malloc(sizeof(char)*14);
	char *temp=(char*)malloc(sizeof(char)*14);
//	char ISBN[14],temp[14];
	char a[2] = "_";
	char raf[6]="Rafta";
	root = (KITAPORNEK*)malloc(sizeof(KITAPORNEK));
	(*kitap)->head = root;
	strcpy(ISBN,(*kitap)->ISBN);
	
	for(i=0;i<(*kitap)->adet;i++){
		strcpy(root->Durum,raf);
		sprintf(str,"%d",i+1);
		strcpy(temp,ISBN);
		strcat(temp,a);
		strcat(temp,str);
		strcpy(root->EtiketNo,temp);
//		printf("%s %s\n",root->Durum,root->EtiketNo);	
		root->next = (*kitap)->head;
		(*kitap)->head=root;
		root = (KITAPORNEK*)malloc(sizeof(KITAPORNEK));
	//	root = root->next;
	}
}
void kitapBilGoster(KITAP* head){
	
	char* isim = (char*)malloc(sizeof(char)*14);
	int i;
	printf("\nBilgilerini gormek istediginiz kitabin ismini giriniz = ");
	fflush(stdin);
	scanf("%[^\n]s",isim);
	KITAP* check = head;
	while((strcmp(check->kitapAdi,isim) != 0) && (check != NULL) ){
		check = check->next;
	}
	system("cls");
	printf("\nKitap ismi = %s\n",check->kitapAdi);
	KITAPORNEK* current;
	current = check->head;
	for(i=check->adet;i>0;i--){
		printf("Numune %d\n->Etiket Numarasi = %s\n->Kitabin Durumu  = %s\n\n",i,current->EtiketNo,current->Durum);
		current = current->next;
	}
}
int kitapYazarEsDosya(const char* fileName,KITAPYAZAR*** arr){
	int sayac = 0, ID;
	char* ISBN = (char*)malloc(sizeof(char)*13);
	FILE *fp = fopen(fileName,"r");
	if(fp == NULL){
		printf("Dosya acilirken bir hata olustu!");
		exit(1);
	}
	char line[100];
	while(fgets(line,100,fp) != NULL){
		(*arr)=realloc((*arr),(sizeof(KITAPYAZAR*)*(sayac+1)));
		(*arr)[sayac] = (KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
		sscanf(line, "%13[^,], %d",ISBN,&ID);
		strcpy((*arr)[sayac]->ISBN,ISBN);
		(*arr)[sayac]->YazarID = ID;
//		printf("%s   %d\n",(*arr)[sayac]->ISBN,(*arr)[sayac]->YazarID);
		sayac++;
		fflush(stdin);
		}
	fclose(fp);	
	return sayac;
}
int kitapYazarEslestir(const char* fileName,KITAPYAZAR*** arr,int n,KITAP* kitapHead,YAZAR* yazarHead ){
	int kontrol=1,kontrol1=1;
	int ID,i;
	char* ISBN = (char*)malloc(sizeof(char));
	KITAP* currentKitap = kitapHead;
	YAZAR* currentYazar = yazarHead;
	printf("Eslestirme yapacaginiz yazarin ID'sini giriniz = ");
	scanf("%d",&ID);
	printf("\nEslestirme yapacaginiz Kitabin ISBN'ini giriniz = ");	
	scanf("%s",ISBN);
		
	while(currentYazar!=NULL && kontrol){
		if(currentYazar->yazarID==ID){
			kontrol=0;
		}else{
			currentYazar=currentYazar->next;
		}
	}
	while(currentKitap!=NULL && kontrol){
		if(strcmp(currentKitap->ISBN,ISBN) == 0 ){
			kontrol1=0;
		}else{
			currentKitap=currentKitap->next;
		}
	}
	if( !kontrol || !kontrol1 ){
	
	(*arr) = realloc((*arr),(n+1)*sizeof(KITAPYAZAR*));
	(*arr)[n] = (KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
	(*arr)[n]->YazarID = ID;
	strcpy((*arr)[n]->ISBN,ISBN);
	

	FILE *fp = fopen(fileName, "a");
	if(fp == NULL){
		printf("\nDosya acilirken bir hata olustu!\n");
	}

	fprintf(fp,"\n%s,%d",(*arr)[n]->ISBN,(*arr)[n]->YazarID);
	n++;
	fclose(fp);
	}
	else{
		printf("\nGirdiginiz Yazar ID'sine ve/veya kitap ISBN'ine ait bilgiler bulunamadi!\n");
	}
	return n;
}
void kitapDuzenle(const char* fileName, KITAP** head){
	
	char* ISBN=(char*)malloc(sizeof(char)*14);
	
	printf("\nGuncelleme yapmak istediginiz kitabin ISBN'ini giriniz = ");
	scanf("%13s",ISBN);
	
	KITAP* current = *head;
	KITAP* bas = *head;
	while(strcmp(ISBN,current->ISBN) != 0 && current != NULL ){
		current = current->next;
	}
	
	if(current == NULL){
		printf("Girdiginiz ISBN ile eslesen kitap bulunamadi!\n");
	}else{
		printf("\nKitap Bilgileri\nKitap adi = %s	Kitap ISBN = %s		Kitap Adet = %d\n",current->kitapAdi,current->ISBN,current->adet);
		printf("Yeni kitap ismi = ");
		fflush(stdin);
		scanf("%[^\n]s",current->kitapAdi);
	
	FILE *fp = fopen(fileName,"w");
	
	if(fp == NULL){
		printf("\nDosya acilirken bir hata olustu!\n");
	}
	while(bas){
		fprintf(fp,"%s,%s,%d\n",bas->kitapAdi,bas->ISBN,bas->adet);
		bas=bas->next;
	}
	
	fclose(fp);
	}
}
int kitapOdunc(const char* fileName,KITAPODUNC*** arr, int n,KITAP** kitapHead, OGRENCI** ogrenciHead,const char* ogrenciDosya){
	int i,kontrolID=1,kontrolISBN=1,tempS,cezaKontrol=0;
	unsigned int islem,ay,gun,yil;
	char* ID = (char*)malloc(sizeof(char)*9);
	char* ISBN = (char*)malloc(sizeof(char)*13);
	char* raf = (char*)malloc(sizeof(char)*6);
	strcpy(raf,"Rafta");

	KITAP* kitapCur = *kitapHead;
	OGRENCI* ogrCur = *ogrenciHead;
	
	(*arr) = realloc((*arr),sizeof(KITAPODUNC*)*(n+1)); 
	(*arr)[n] = (KITAPODUNC*)malloc(sizeof(KITAPODUNC));
	
	KITAPORNEK* gez ;
	KITAPORNEK* temp;
	printf("\nYapilacak islemi secin\n[0] Kitap odunc alma\n[1] Kitap iade etme\n");
	scanf("%u",&islem);
	(*arr)[n]->islemTipi = islem;
	
	printf("Ogrencinin ID'sini giriniz = ");
	scanf("%s",ID);
	
	while(ogrCur != NULL  && kontrolID){
		if(strcmp(ogrCur->ogrID,ID) == 0){
			kontrolID=0;
		}else{
			ogrCur=ogrCur->next;
		}
	}	
	if(kontrolID){
		printf("\nGirdiginiz ID'ye sahip ogrenci bulunamadi\n");
		return; 
	}
	if(ogrCur->puan<0){
		printf("\nOgrencinin puani negatif hanelere dustugu icin cezali durumdadir!\n");
		return;
	}
	strcpy((*arr)[n]->ogrID,ID);
		
	
	printf("\nKitap etiket numarasini giriniz = ");
	scanf("%s",ISBN);
	while(kitapCur != NULL  && kontrolISBN){
		gez = kitapCur->head;
		for(i=0;i<kitapCur->adet;i++){

			if(strcmp(gez->EtiketNo,ISBN) == 0 && !strcmp(gez->Durum,raf)){
				kontrolISBN=0;
				temp = gez;
			}
			else{
				gez = gez->next;
		    }		
		}
		kitapCur=kitapCur->next;
	}	
	if(kontrolISBN && islem == 0){
		printf("\nGirdiginiz etiket numarasina sahip kitap bulunamadi\n");
		return; 
	}
	int kontrolEtiket = 1;
	for(i=n-1;i>=0;i--){
			if(strcmp((*arr)[i]->EtiketNo,ISBN)==0){
				kontrolEtiket = 0;
			}
	}
	if(kontrolEtiket == 1 && islem == 1){
		printf("\nGirdiginiz etiket numarasina sahip kitap sizin elinizde degil!\n");
		getCharMenu();
		return;
	}
	
	strcpy((*arr)[n]->EtiketNo,ISBN);
	
	
	printf("\nTarihi bilgilerini giriniz\n");
	
	printf("Gun = ");
	scanf("%u",&gun);
	(*arr)[n]->islemTarihi.gun = gun;
	
	printf("\nAy = ");
	scanf("%u",&ay);
	(*arr)[n]->islemTarihi.ay = ay;
	
	printf("\nYil = ");
	scanf("%u",&yil);
	(*arr)[n]->islemTarihi.yil = yil;

	
	if(islem == 0){
		strcpy(gez->Durum,ID);
	}
	else if(islem == 1){
		strcpy(gez->Durum,"Rafta");
		for(i=n-1;i>=0;i--){
			if(((*arr)[i]->islemTipi == 0) && (strcmp((*arr)[i]->EtiketNo,(*arr)[n]->EtiketNo) == 0 )){
				tempS=i;
			}
		}

		if(((*arr)[n]->islemTarihi.yil-(*arr)[tempS]->islemTarihi.yil) > 0 ){
			cezaKontrol = 1;
			
		}
		else if(((*arr)[n]->islemTarihi.ay-(*arr)[tempS]->islemTarihi.ay) > 1 ){
			cezaKontrol = 1;
			
		}
		else if(((*arr)[n]->islemTarihi.gun-(*arr)[tempS]->islemTarihi.gun) > 15 && ((*arr)[n]->islemTarihi.ay-(*arr)[tempS]->islemTarihi.ay) == 0  ){
			cezaKontrol = 1;
			
		}
		else if(((*arr)[n]->islemTarihi.gun-(*arr)[tempS]->islemTarihi.gun)+30 > 15 && ((*arr)[n]->islemTarihi.ay-(*arr)[tempS]->islemTarihi.ay) == 1  ){
			cezaKontrol = 1;	
		}	
		
		if(cezaKontrol == 1){
			
			ogrCur->puan = ogrCur->puan - 10;
		
			OGRENCI* ogrYaz = *ogrenciHead;
			FILE *fp1 = fopen( ogrenciDosya , "w");
	
			if(fp1 == NULL){
				printf("\nDosya acilirken bir hata olustu!\n");
				}
			while(ogrYaz != NULL){
				fprintf(fp1, "%s,%s,%s,%d\n", ogrYaz->ogrID, ogrYaz->ad, ogrYaz->soyad, ogrYaz->puan);
        		ogrYaz = ogrYaz->next;
				}
	
				fclose(fp1);
		}

	}
		
	FILE *fp = fopen(fileName, "w");
	
	if(fp == NULL){
			printf("\nDosya acilirken bir hata olustu! \n");
	}	
	n++;
	for(i=0 ; i < (n) ; i++){
			fprintf(fp,"%s,%s,%u,%u.%u.%u\n",(*arr)[i]->EtiketNo,(*arr)[i]->ogrID,(*arr)[i]->islemTipi,(*arr)[i]->islemTarihi.gun,(*arr)[i]->islemTarihi.ay,(*arr)[i]->islemTarihi.yil);
	}
	
	fclose(fp);

	return n;
	
}
void ogrenciBilgiGoster(const char* fileName,int n,KITAPODUNC*** arr,OGRENCI** head){
	char* ID = (char*)malloc(sizeof(char));
	int i,exit=0,sayac=1;
	OGRENCI* temp = (*head);
	printf("\nHareket gecmisini gormek istediginiz ogrencinin ID'sini giriniz = ");
	scanf("%s",ID);
	
	while(temp && strcmp(temp->ogrID,ID) != 0){
		temp=temp->next;
	}
	printf("\nAd = %s	Soyad = %s	   Puan = %d",temp->ad,temp->soyad,temp->puan);
	
	for(i=0;i<n;i++){
		if(strcmp((*arr)[i]->ogrID,ID) == 0 ){
			printf("\n\nIslem Sirasi = %d\n",sayac);
			if((*arr)[i]->islemTipi == 0){
				printf("\n->Odunc Alinan Kitabin Etiket numarasi = %s\n",(*arr)[i]->EtiketNo);
			}
			else{
				printf("\n->Iade Edilen Kitabin Etiket numarasi  = %s\n",(*arr)[i]->EtiketNo);
			}
		    	printf("\n->Islem Tarihi  = %d.%d.%d\n",(*arr)[i]->islemTarihi.gun,(*arr)[i]->islemTarihi.ay,(*arr)[i]->islemTarihi.yil);
		    	sayac++;
		}	
	}
		
}
void kitapTeslimEtmemis(KITAPODUNC*** arr,OGRENCI** head,int n){
	int i,kontrol,sayac = 1,j;
	printf("\nKITABINI IADE ETMEMIS OGRENCILER\n\n");

	for(i=0 ; i<n;i++){

		if((*arr)[i]->islemTipi == 0){
			kontrol = 0;
			
				for(j=i+1;j<n;j++){
					if(strcmp((*arr)[i]->ogrID,(*arr)[j]->ogrID) == 0 && (*arr)[j]->islemTipi == 1 ){
						kontrol = 1;
					}
					
			}
			if(kontrol == 0){
					OGRENCI* temp = *head;
					while(temp && strcmp(temp->ogrID,(*arr)[i]->ogrID) != 0 ){
						temp = temp->next;
					}
	
					printf("OGRENCI %d\n",sayac);
					printf("-> Ad					: %s\n",temp->ad);
					printf("-> Soyad				: %s\n",temp->soyad);
					printf("-> Puan					: %d\n",temp->puan);
					printf("-> ID 					: %s\n",(*arr)[i]->ogrID);
					printf("-> Odunc alinan kitabin etiket numarasi : %s\n",(*arr)[i]->EtiketNo);
					printf("-> Odunc alma tarihi			: %d.%d.%d\n",(*arr)[i]->islemTarihi.gun,(*arr)[i]->islemTarihi.ay,(*arr)[i]->islemTarihi.yil);
					sayac++;
			}
			
		}

	}
}
void cezaliOgrenciListele(OGRENCI* head){
	OGRENCI* temp = head;
	int sayac = 1;
	printf("\n\nCEZALI OGRENCILER LISTESI\n\n");
	while(temp){
		if(temp->puan<0){
					printf("OGRENCI %d\n",sayac);
					printf("-> Ad					: %s\n",temp->ad);
					printf("-> Soyad				: %s\n",temp->soyad);
					printf("-> Puan					: %d\n",temp->puan);
					sayac++;			
		}
		temp = temp->next;
	}
}
void teslimEdilmeyenKitap(KITAP* head){
	KITAP* temp = head;
	KITAPORNEK* bas;
	char* raf = (char*)malloc(sizeof(char));
	strcpy(raf,"Rafta");

	int i, sayac = 1;
	printf("\nIADE EDILMEMIS KITAPLAR LISTESI\n\n");
	while(temp){
		bas = temp->head;
		
		for(i=0;i<temp->adet;i++){
			if(strcmp(bas->Durum,raf) != 0){
					printf("\nKITAP %d\n",sayac);
					printf("-> Ad				: %s\n",temp->kitapAdi);
					printf("-> Etiket numarasi		: %s\n",bas->EtiketNo);
					sayac++;	
			}
			bas = bas->next;
		}
		
		temp = temp->next;
		
	}
}
int kitapYazarGuncelle(const char* fileName,KITAPYAZAR*** arr,int n,KITAP* head,YAZAR* yazarHead){
	char* isim = (char*)malloc(sizeof(char)*14);
	int i,sayac = 1,secim,ID,swapKontrol=0;
	printf("\nYazarini guncellemek istediginiz kitabin ismini giriniz = ");
	fflush(stdin);
	scanf("%[^\n]s",isim);
	KITAP* check = head;
	while((strcmp(check->kitapAdi,isim) != 0) && (check != NULL) ){
		check = check->next;
	}
	printf("\nKitap ismi = %s\n",check->kitapAdi);
	printf("\nYapacaginiz islemi secin\n[1] Yazar Ekle\n[2] Yazar sil");
	scanf("%d",&secim);
	if(secim == 2){
			printf("\nYAZARLAR\n");
			//printf("isbn:%s",check->ISBN);
			for(i=0;i<n;i++){

					if(strcmp((*arr)[i]->ISBN,check->ISBN) == 0){
							printf("\n-> Yazar %d ID : %d\n",sayac,(*arr)[i]->YazarID);
							sayac++;
					}
		
			}	
			printf("\nSilmek istediginiz yazarin ID'sini giriniz = ");
			scanf("%d",&ID);
			for(i=0;i<n;i++){
					if(strcmp((*arr)[i]->ISBN,check->ISBN) == 0 && ID == (*arr)[i]->YazarID && swapKontrol == 0){
						swapKontrol = 1;
						n--;
						strcpy((*arr)[i]->ISBN,(*arr)[i+1]->ISBN);
						(*arr)[i]->YazarID=(*arr)[i+1]->YazarID;
					}
					if(swapKontrol==1){
						strcpy((*arr)[i]->ISBN,(*arr)[i+1]->ISBN);
						(*arr)[i]->YazarID=(*arr)[i+1]->YazarID;
					}
		
			}
			
			FILE *fp1 = fopen(fileName, "w");
			if(fp1 == NULL){
				printf("\nDosya acilirken bir hata olustu.\n");	
			}
			int i;
			for(i=0;i<n;i++){
			
			fprintf(fp1,"%s,%d\n",(*arr)[i]->ISBN,(*arr)[i]->YazarID);
		}
			
			fclose(fp1);
		
	
	}else if(secim == 1){
		YAZAR* temp = yazarHead;
		
		while(temp != NULL){
			printf("\nYazar ID = %d   Isim = %s    Soyisim = %s ",temp->yazarID,temp->yazarAd,temp->yazarSoyad);
			temp = temp->next;
	}
		
		printf("\n%s kitabina yazar olarak eklemek istediginiz yazarin ID'sini giriniz = ",check->kitapAdi);
		scanf("%d",&ID);
			
		(*arr) = realloc((*arr),(n+1)*sizeof(KITAPYAZAR*));
		(*arr)[n] = (KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
		(*arr)[n]->YazarID = ID;
		strcpy((*arr)[n]->ISBN,check->ISBN);
		
		FILE *fp = fopen(fileName, "a");
		if(fp == NULL){
		printf("\nDosya acilirken bir hata olustu!\n");
		}

		fprintf(fp,"\n%s,%d",(*arr)[n]->ISBN,(*arr)[n]->YazarID);
		n++;
		fclose(fp);

	}

	return n;
}
