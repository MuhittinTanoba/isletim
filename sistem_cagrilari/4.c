#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char pid_metni[20];

    printf("Ben 4 numarali programim. PID: %d\n", getpid());
    printf("Simdi exec ile kendimi 'ps' programina donusturuyorum...\n");
    printf("ps'nin gosterdigi PID ile benim PID'im ayni olacak!\n\n");

    fflush(stdout);

    snprintf(pid_metni, sizeof(pid_metni), "%d", getpid());

    execlp("ps", "ps", "-o", "pid,ppid,comm", "-p", pid_metni, NULL);

    perror("exec basarisiz");
    printf("Bu satiri goruyorsaniz exec basarisiz olmustur.\n");
    return 1;
}
