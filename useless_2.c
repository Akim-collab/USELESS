#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

int main(int argc, char *argv[]) {
    
    int time_wait[256], i = 0;
    char name_program[5][10];
    FILE *file;
    
    
    if(argc != 2) {
        printf("Ошибка. Некорректно введены данные\n");
        return 1;
    }
    
    if ((file = fopen(argv[1], "r")) == NULL) {
                printf("Не удалось открыть файл\n");
                return 2;
    }
   
    while ((fscanf(file, "%d %s", &time_wait[i], name_program[i])) && (!feof(file))) {
	i = i + 1;	
    }
    fclose(file);
    //qsort(time_wait, i, sizeof(int), cmp);
    
    for (int j = 0; j < i; j++) {
 	pid_t pid = fork();
	if(pid < 0) {
		printf("Не удалось создать процесс\n");
		return 3;
	}
	if(pid == 0) {
		sleep(time_wait[j]);
		printf("\n");
        	execlp(name_program[j], name_program[j], NULL);
	}
    }
    return 0;
}

