#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int a[20],n;

int primecheck(int a){
   int flag=1;
   for(int i=2;i<=a/2;i++){
      if(a%i==0){
         flag=0;
      }
   }
   return flag;
}
void main(){
   int fr,n,sum=0;
   scanf("%d",&n);
   int flag;
   for(int i=0;i<n;i++){
      scanf("%d",&a[i]);
   }
   fr=fork();
   if(fr!=0){
      for(int i=0;i<n;i++){
         flag=primecheck(a[i]);
         if(flag==0){
              sum+=a[i];   
         }
      }
   printf("%d from parent \n",sum);
   }
   else{
      for(int i=0;i<n;i++){
         flag=primecheck(a[i]);
         if(flag==1){
              sum+=a[i];   
         }
      }
   printf("%d from child \n",sum);
   }
}
