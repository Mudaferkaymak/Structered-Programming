#include <stdio.h>
#include <stdlib.h>

int functions(int a){
	if(a%2==0){
		return a/2;
	}else if(a%2==1){
		return (3*a)+1;
	}
}
int main(){
	int i=1,n,size=2,j,deger;
	printf("ilk sayiyi girin:");
	scanf("%d",&n);
	int* matris = (int*)malloc(size*sizeof(int));
	if(matris == NULL){
		printf("Memory is not allocated\n");
	}
	matris[0]=n;
	deger=functions(n);
	while(deger!=1){
		matris[i] = deger;
		 
		if((i+1)>=size){
			size=size*2;
			matris = (int *)realloc(matris, size * sizeof(int));
		}
		i++;
		deger = functions(deger); 
	}
	matris[i]=1;
	i++;
	for(j=0;j<i;j++){
		printf("%d ",matris[j]);
	}
	printf("\neleman sayisi = %d\n",i);
	printf("kapladigi alan = %d\n",size);

	
	free(matris);
	return 0;
}
