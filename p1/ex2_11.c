#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


int main(){
	int i,d,u,c,v,deu,ci,dos,un ;
	i = d =u=c=v=deu=ci=dos=un=0;
	float a;
	scanf("%f", &a);
	printf("%f\n", a );
	i=a*100;
	printf("%d\n", i);
	if(i>= 200){
			d= i/200;
			i = i%200;
		}
		
	if(i >= 100 ){
			u =i/100;
			i = i%100;
		}
	if(i >= 50){
			c=i/50;
			i = i%50;
		}
		
	if(i >= 20){
			v=i/20;
			i=i%20;
		}
	if(i >= 10){
			deu =i/10;
			i = i%10;
		}
	if(i >= 5){
			ci= i/5;
			i = i%5;
		}
	if(i >= 2){
			dos = i/2;
			i = i%2;
		}
	if(i >= 1){
			un = i/1;
			i = i%1;
		}
	
	printf("Necesites aquestes monedes: De 2€ =%d, de 1€ =%d, de 50c =%d, de 20c = %d, de 10c = %d, de 5c = %d, de 2c =%d, i de 1c =%d\n",d,u,c,v,deu,ci,dos,un );

}