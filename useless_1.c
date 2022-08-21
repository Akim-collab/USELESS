#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    FILE *file;
    if(argc != 2) {
        printf("Ошибка. Некорректно введены данные\n");
        return 1;
    }

    if ((file = fopen(argv[1], "r")) == NULL) {
                printf("Не удалось открыть файл\n");
                return 2;
    }

        char name[10];
        int time;
        pid_t pid;

        while((fscanf(file, "%d %s", &time, name)) && (feof(file) == 0)) {
                pid = fork();
                if (pid < 0) {
                        printf("Невозможно создать процесс\n");
                        return 3;
                }
                if (pid == 0) {
                        sleep(time);
			printf("\n");
                        execlp(name, name, NULL);
                        return 0;
                }
        }
    return 0;
}

