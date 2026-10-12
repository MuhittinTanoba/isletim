#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    char *varsayilan_komut[] = {"ls", "-l", NULL};
    char **komut;

    if (argc > 1) {
        komut = &argv[1];
    } else {
        komut = varsayilan_komut;
    }

    printf("Ana islem (PID: %d) '%s' komutunu calistirmak icin fork yapiyor...\n",
           getpid(), komut[0]);
    fflush(stdout);

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork basarisiz!\n");
        exit(1);
    }
    else if (pid == 0) {
        printf("Cocuk (PID: %d): kendimi '%s' programina donusturuyorum.\n",
               getpid(), komut[0]);
        printf("------------------------------------------------\n");
        fflush(stdout);

        execvp(komut[0], komut);

        perror("Cocuk: exec basarisiz");

        exit(127);
    }
    else {
        wait(&status);
        printf("------------------------------------------------\n");
        printf("Ana islem: cocuk (PID: %d) bitti.\n", pid);

        if (WIFEXITED(status)) {
            printf("Ana islem: cocugun cikis kodu: %d\n", WEXITSTATUS(status));
        }
        printf("Ana islem: ben hala calisiyorum, cunku exec'i ben degil cocuk yapti!\n");
    }

    return 0;
}
