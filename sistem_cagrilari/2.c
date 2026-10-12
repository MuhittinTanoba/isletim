#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*
Birden fazla fork() işlemi olduğunda durum.
*/
int main() {
    int status;
    pid_t original_pid = getpid();
    // Program ilk başladımızda kendi shell/terminalimizden forklanır.
    printf("Ana islem basladi. Ana islem PID: %d, Ana islemin ebevyni: %d\n", getpid(), getppid());

    // İlk fork
    fork();
    // İkinci fork (Bu hem ana islem hem de cocuk islem tarafindan isletilecek)
    fork();

    // Bu kod tüm işlemler tarafından işletilecek.
    printf("İslem PID: %d, Ana isleminin PID: %d\n", getpid(), getppid());

    // Eger orijinal ana islemdeyse cocukları bekle
    if (getpid() == original_pid) {
        // Tüm çocukların işlemleri bitene kadar bekkiyoruz
        while (wait(NULL) > 0) {

        }
        printf("\nToplam islem sayisi: 4 olur. 2^n\n");
    } else {
        // Cocuk islemler ana islemler hemen cikmasin diye uyusun.
        usleep(100000);  // 0.1 saniye uyu.
    }
    /*
    NOT: Eğer ana işlem, çocuk işlem bitmeden sonlandırılmışsa, çocuk işlemde getppid() 1 döndürecektir.
    Bu işletim sisteminin init işlemidir. Aile ağacının en tepesinde yer alır.
    Kendi ana işlemi ölmüş işlemleri bu işlem evlat alır (adopting).
    */

    return 0;
}