#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TAMPON_BOYUTU 4096

int main(int argc, char *argv[]) {
    char tampon[TAMPON_BOYUTU];
    ssize_t okunan;

    if (argc != 3) {
        fprintf(stderr, "Kullanim: %s kaynak hedef\n", argv[0]);
        return 1;
    }

    int kaynak = open(argv[1], O_RDONLY);
    if (kaynak < 0) {
        perror("Kaynak dosya acilamadi");
        return 1;
    }

    int hedef = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (hedef < 0) {
        perror("Hedef dosya olusturulamadi");
        close(kaynak);
        return 1;
    }

    printf("kaynak fd = %d, hedef fd = %d\n", kaynak, hedef);

    int tur = 0;
    while ((okunan = read(kaynak, tampon, TAMPON_BOYUTU)) > 0) {
        if (write(hedef, tampon, okunan) != okunan) {
            perror("Yazma hatasi");
            break;
        }
        tur++;
    }
    if (okunan < 0) {
        perror("Okuma hatasi");
    }

    close(kaynak);
    close(hedef);

    printf("Kopyalama bitti. %d kez read/write yapildi.\n", tur);
    return 0;
}
