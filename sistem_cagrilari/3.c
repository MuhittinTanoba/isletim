#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/* Birden fazla işlemi kullanma amacımız aynı anda iki farklı işi yapabilmektir.
 * Bu sayede programımız birden fazla işlemci/işlemci çekirdeğini kullanarak
 *    daha verimli çalışabilir.
 */
int main() {
    pid_t pid;    // İşlem IDsini tutar
    int status;   // Çocuk işlemin bitme durumunu tutar.


    printf("Ana işlem (PID: %d) yeni bir cocuk islem olusturuyor....\n", getpid());
    // Yeni bir işlem oluşturmak için fork() fonksiyonunu kullan
    pid = fork();

    // fork basarili mi kontol et
    if (pid < 0) {
        // Fork başarısız
        fprintf(stderr, "Fork başarısız oldu!\n");
        exit(1);
    }
    else if (pid == 0) {
        // Bu kod yeni çocuk işlem tarafından işletilmektedir.
        printf("\nBen COCUK islemim (PID: %d).!\n", getpid());
        printf("Ben cocuk islemim, ana islemim: %d\n", getppid());

        // Buraya cocuk isleme yapması için (uzun) bir iş veriyoruz.
        // Burada basit olması için sadece bir döngü kullandak
        printf("Cocuk 1'den 5'e kadar sayiyor:\n");
        for (int i = 1; i <= 5; i++) {
            printf("Cocuk: %d\n", i);
            sleep(1);  // Her sayidan sonra 1 saniye bekle
        }

        printf("Cocuk islemin isi bitti!\n");
        exit(0);  // Cocuk islem cikiyor.
    }
    else {
        // Bu kod ana islem tarafindan isletiliyor...
        printf("\nBen ANA islemim (PID: %d)!\n", getpid());

        // Buraya ana isleme de bir is veriyoruz...
        printf("Ana islem A'dan E'ye alfabeyi yaziyor:\n");
        for (char c = 'A'; c <= 'E'; c++) {
            printf("Ana: %c\n", c);
            sleep(2);  // Her harften sonra 2 saniye bekle
        }

        // Ana islem cocugun bitmesini bekler.
        printf("\nAna islem cocugun bitmesini bekliyor...\n");
        wait(&status);

        if (WIFEXITED(status)) {
            printf("Cocuk islem su islem koduyla cikti: %d\n",
                   WEXITSTATUS(status));
        }
        //Çıkma durumu C standardında tanımlanmadığından platformda platforma
        //farklı hatalar oluşturabilir.
        printf("Ana islem tamamlandi. Program sonlandi!\n");
    }

    return 0;
}