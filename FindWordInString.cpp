#include <stdio.h>

void ppl(char* p) {
	for(int i=0; *(p+i) !='\0'; i++) {
		printf("%c", *(p+i));
	}
	printf("\n");
}

int str(char *p, char* check, char f) {
	int u;
	for(u=0; check[u]!='\0'; u++) ;
	int index = 0;
	for(int i=0; *(p+i)!='\0'; i++) {
		if(*(p+i) == *(check+index)) {
			index++;
		} else if(index != u){
			index=0;
		}
		if(index == u) {
			printf("축하합니다 모두 맞습니다\n");
			break;
		}
	}
	return index;
}

int main() {
	char pl[100];
	 
	char check[5] = {'h','e','l','l','o'};
	scanf("%s", pl);
	ppl(pl);
	printf("%d", str(pl, check, ','));
	return 0;
}
