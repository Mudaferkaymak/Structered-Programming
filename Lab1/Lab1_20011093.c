#include<stdio.h>
#include<conio.h>
#define N 200
int main(){
	int a,arr[N],i,j,counter=1,dizi[N],k=0;
	printf("dizi boyutunu giriniz:");
	scanf("%d",&a);
	for(i=0;i<a;i++){
		printf("%d. degeri giriniz:",i+1);
		scanf("%d",&arr[i]);	
	}
	
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			if(arr[i]==arr[j] && i!=j){
				counter++;
			}
		}
		if(arr[i]==counter){
			dizi[k]=arr[i];
			k++;
		}
		counter=1;
	}

	for(i=0;i<k;i++){
		for(j=0;j<k;j++){
			if(dizi[i]==dizi[j] && i!=j){
				dizi[j]='\0';
			}
		}
	}
	for(i=0;i<k;i++){
		if(dizi[i]!=0){
		printf("Sihirli sayi:%d\n",dizi[i]);
	}
	}
	
	return 0;
}
