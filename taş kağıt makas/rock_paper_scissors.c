#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Renk Kodları (ANSI Escape Codes)
#define KIRMIZI "\033[1;31m"
#define YESIL   "\033[1;32m"
#define SARI    "\033[1;33m"
#define MAVI    "\033[1;34m"
#define RESET   "\033[0m"

// --- Fonksiyon Tanımları ---

void menuYazdir() {
    printf("\n--- YENI TUR ---\n");
    printf("1. Tas\n");
    printf("2. Kagit\n");
    printf("3. Makas\n");
    printf("Seciminizi yapin (1-3): ");
}

int bilgisayarSecimiUret() {
    return (rand() % 3) + 1;
}

int sonucuHesapla(int oyuncu, int bilgisayar) {
    if (oyuncu == bilgisayar) {
        return 0; // Berabere
    }
    // Oyuncunun kazandığı durumlar
    if ((oyuncu == 1 && bilgisayar == 3) || 
        (oyuncu == 2 && bilgisayar == 1) || 
        (oyuncu == 3 && bilgisayar == 2)) {
        return 1; // Oyuncu kazandı
    }
    return 2; // Bilgisayar kazandı
}

// --- Ana Program ---

int main() {
    char *secenekler[] = {"Tas", "Kagit", "Makas"};
    srand(time(NULL)); // Rastgele sayı üretecini zamana göre başlat
    
    int guess;
    int hedefSayi;
    int bilgisayarSkor = 0;
    int oyuncuSkor = 0;

    // Oyun Döngüsü: Herhangi biri 3 olana kadar devam eder
    do {
        hedefSayi = bilgisayarSecimiUret();
        menuYazdir();

        // 1. Girdi Kontrolü: Sayı mı girildi?
        if (scanf("%d", &guess) != 1) { 
            printf(KIRMIZI "Hatali giris! Lutfen harf degil, sayi giriniz.\n" RESET);
            while(getchar() != '\n'); // Tamponu temizle
            continue; // Döngünün başına dön
        }

        // 2. Aralık Kontrolü: Sayı 1-3 arasında mı? 
        if (guess < 1 || guess > 3) {
            printf(KIRMIZI "Lutfen sadece 1, 2 veya 3 giriniz.\n" RESET);
            continue;
        }

        // Sonucu Hesapla
        int sonuc = sonucuHesapla(guess, hedefSayi);

        // Sonucu Ekrana Yazdır
        if (sonuc == 0) {
            printf(SARI "Berabere! Bilgisayarin secimi: %s\n" RESET, secenekler[hedefSayi - 1]);
        } else if (sonuc == 1) {
            printf(YESIL "Tebrikler! Kazandiniz. Bilgisayarin secimi: %s\n" RESET, secenekler[hedefSayi - 1]);
            oyuncuSkor++;
        } else {
            printf(KIRMIZI "Uzgunum, kaybettiniz. Bilgisayarin secimi: %s\n" RESET, secenekler[hedefSayi - 1]);
            bilgisayarSkor++;
        }

        // Güncel Skoru Göster
        printf(MAVI "-- Skor Durumu --\n" RESET);
        printf("Oyuncu: %d - Bilgisayar: %d\n", oyuncuSkor, bilgisayarSkor);

    } while (oyuncuSkor < 3 && bilgisayarSkor < 3);

    printf("\n=================================\n");
        if (oyuncuSkor == 3) {
        
            printf(YESIL "TEBRIKLER! OYUNU KAZANDINIZ!\n" RESET);
        } else {
        
            printf(KIRMIZI "UZGUNUM, BILGISAYAR KAZANDI.\n" RESET);
        }
        printf("=================================\n");
    // Dosyalama İşlemleri
    time_t t = time(NULL);
    struct tm *zaman = localtime(&t);

    FILE *f = fopen("skorlar.txt", "a");
    if (f == NULL) {
        printf("Hata: Skor dosyasi acilamadi.\n");
        return 1;   
    }

    fprintf(f, "--------------------------------------------------\n");
    fprintf(f, "Mac Tarihi: %02d.%02d.%d - Saat: %02d:%02d\n", 
        zaman->tm_mday, zaman->tm_mon + 1, zaman->tm_year + 1900, 
        zaman->tm_hour, zaman->tm_min);
    fprintf(f, "Sonuc -> Oyuncu: %d | Bilgisayar: %d\n", oyuncuSkor, bilgisayarSkor);
    fprintf(f, "--------------------------------------------------\n\n");
    
    fclose(f);
    printf("Mac sonucu 'skorlar.txt' dosyasina kaydedildi.\n");

    return 0;    
}
