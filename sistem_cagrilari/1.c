#include <stdio.h>
#include <unistd.h>  //  fork() için
#include <sys/wait.h> // wait() için
#include <stdlib.h>   // exit() için
/* Bu kod UNIX benzeri işletim sistemlerinde (macOS, Linux, BSD vb.) çalışmaktadır.
 * Denemek için Ubuntu'yu VMWare Workstation ya da Virtualbox ile de kurabilirsiniz.
 */

/*
 * fork() -> Yeni bir işlem oluştur.
 * getpid() -> mevcut işlemin PID (process id'si)
 * getppid() -> Mevcut işlemin ana/ebeveyn (parent) işleminin PID'si.
 */
int main() {


    // Bir değişken
    int x = 5;

    /* Yeni bir işlem (child process) oluşturmak için fork (çatallama) fonksiyonu kullanılır.
     * fork() fonksiyonu 3 farklı değer döndürebilir.
     * Ana/ebeveyn işleme (parent process) yeni oluşturulan çocuk işlemin ID'sini (pozitif sayı)
     * Çocuk işleme 0 sayısını
     * Hata olursa negatif sayi döndürür.
     * forkun pid_t turunde bir degiskene atiyoruz. if kotrollerinde fork()'u yeniden çağırırsanız
     * tekrar bir işlem oluşturursunuz.
    */
    pid_t pid = fork();

    // Hata kontrolü
    if (pid < 0) {
        // fork(), negatif sayi dondurduyse hata vardir
        fprintf(stderr, "Fork basarisiz!\n");
        exit(1);
    }

    // Çocuk işlem, fork()'un 0 döndürme durumu
    else if (pid == 0) {
        //Bu blok çocuk işlemde çalışacaktır.
        x = x + 1;  //x değişkenini burda değiştiriyorum
        printf("\nBEN COCUK ISLEMIM:\n");
        printf("* Cocuk islem IDsi (PID) getpid(): %d\n", getpid());
        printf("* Cocuk islemin ana isleminin IDsi (PPID) getppid(): %d\n", getppid());
        // x'i yukarıda global olarak tanımlamıştık.
        // Buradaki değişilik diğer processi ETKİLEMEDİ.
        printf("* Cocukta x degeri: %d\n", x);
        printf("* Cocukta fork()'un dondurdu deger: %d\n", pid);
        printf("* Cocuk process sonlaniyor...\n");
        exit(0);
    }

    // Ana islem, fork() cocugun ID'sini döndürme durumu
    else {
        //Bu blok ana/ebeveyn işlemde çalışacaktır.
        x = x - 1;  // x'i ana işlemde değerini değiştiriyorum.
        printf("\nBEN ANA ISLEMIM:\n");
        printf("* Ana islemin IDsi (PID): %d\n", getpid());
        printf("* Ana islemde x: %d\n", x);
        printf("* Ana islemde fork()'un dondurdugu deger: %d\n", pid);
        printf("* Ana islem cocugun isleminin bitmesini bekliyor...\n");

        // Cocugun isinin bitmesini beklemek için wait kullaniliyor.
        wait(NULL);
        printf("* Ana islem cocugun isinin bittigini farketti...\n");
    }

    return 0;

}