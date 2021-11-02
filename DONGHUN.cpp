#include <stdio.h>
using namespace std;
int main(){
	char arr[10000]={};
	gets(arr);
	char isadded[7]={'s','a','d','d','e','d'};
	char plant[5]={'l','a','n','t'};
	for(int i=0;arr[i]!=NULL;i++){
		if(arr[i]=='i'){
			bool flag=true;
			for(int j=0;j<6;j++){
				if(arr[i+1+j]!=isadded[j]){
					flag=false;
					break;
				}
			}
			if(flag){
				for(int j=i+9;arr[j]!=',';j++){
					printf("%c",arr[j]);
				}
				printf("\n");
			}
		}
		if(arr[i]=='p'&&arr[i+5]!='c'){
			bool flag=true;
			for(int j=0;j<4;j++){
				if(arr[i+1+j]!=plant[j]){
					flag=false;
					break;
				}
			}
			if(flag){
				for(int j=i+7;arr[j-1]!='}';j++){
					printf("%c",arr[j]);
				}
				printf("\n");
			}
			
		}
	}
}
