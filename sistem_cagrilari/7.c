#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main() {
    printf("1) printf ile merhaba\n");
    fflush(stdout);

    write(1, "2) write ile merhaba\n", 21);

    syscall(SYS_write, 1, "3) syscall ile merhaba\n", 23);

    printf("\nBu makinede write sistem cagrisinin numarasi: %d\n", SYS_write);
    printf("getpid sistem cagrisinin numarasi: %d\n", SYS_getpid);
    return 0;
}
