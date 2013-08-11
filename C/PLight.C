#include <stdio.h>
#include <string.h> 

using namespace std;

FILE *f;
void file_write(const char* buf);
int usage(const char *command);

int main(int argc, char *argv[]){
	int i;
	f = fopen("/home/toor/.light", "r");
	fscanf(f, "%d", &i);
	if(i!=0){
		 printf("Error");
		 fclose(f);
		 return 1;
	 }
	
	if(argc==1){
		while(1){
			char command[10];
			printf("Команда\n");
			scanf("%s", command);
			int f = usage(command);
			if (f==-1){
					break;
				}
				if (f==1){
					continue;
				}
		}
	}
	else if (argc==2){
		usage(argv[1]);
	}
	
}


int usage(const char *command){
	//printf("%s", command);
	if(!strcmp(command,"q") || !strcmp(command,"quit") || !strcmp(command,"exit")){
			printf("Exit\n");
			return -1;
		}
	if (!strcmp(command,"lamp1on")) {
			file_write("11");
			return 0;
		}
	if (!strcmp(command,"lamp1off")) {
			file_write("10");
			return 0;
		}
	if (!strcmp(command,"lamp2on")) {
			file_write("21");
			return 0;
		}
	if (!strcmp(command,"lamp2off")) {
			file_write("20");
			return 0;
		}
	if (!strcmp(command,"alloff")) {
			file_write("1110");
			return 0;
		}
	if (!strcmp(command,"lampsoff")) {
			file_write("110");
			return 0;
		}
	if (!strcmp(command,"allon")) {
			file_write("1111");
			return 0;
		}
	if (!strcmp(command,"lampson")) {
			file_write("111");
			return 0;
		}
	if (!strcmp(command,"tableon")) {
			file_write("31");
			return 0;
		}
	if (!strcmp(command,"tableoff")) {
			file_write("30");
			return 0;
		}
		
		return 1;
}
	
void file_write(const char* buf){
	f=fopen("/home/toor/.light", "w");
	fprintf(f,"%s", buf);
	fclose(f);
}
