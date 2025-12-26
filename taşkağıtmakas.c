#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int guess;
    int devam = 1;
    int hedefSayi;
    int bilgisayarSkor = 0;
    int oyuncuSkor = 0;
  


do{
    hedefSayi = (rand() %3) + 1;
    
    printf("1-Tas\n");
    printf("2-Kagit\n");
    printf("3-Makas\n");
    printf("Lutfen tas kagit makas oyununda kullanmak istediginiz sayiyi secin:\n");
    scanf("%d", &guess);

    
    if (guess <1 || guess >3){

        printf("Gecersiz secim yaptiniz. Lutfen 1 ile 3 arasi secim yapiniz. \n");
    } else if (guess == hedefSayi ){
        printf("Berabere! Bilgisayarin secimi: %d\n", hedefSayi);

    } else if ( (guess ==1 && hedefSayi ==3 ) || (guess ==2 && hedefSayi ==1) || (guess ==3 && hedefSayi ==2) ) {
        printf("Tebrikler ! Kazandiniz. Bilgisayarin secimi:%d\n", hedefSayi);
        oyuncuSkor++;

    } else {

        printf("Uzgunum, kaybettiniz. Bilgisayarin secimi: %d\n", hedefSayi);
        bilgisayarSkor++;

    } 

    printf("-- Skor Durumu --\n");
    printf("Oyuncu Skoru: %d\n", oyuncuSkor);
    printf("Bilgisayar Skoru: %d\n", bilgisayarSkor);


    printf("Oyuna devam etmek istiyor musunuz? Evet icin 1, Hayir icin 0 giriniz:");
    scanf("%d", &devam);


} while (devam == 1);

  FILE *f;
    f = fopen("skorlar.txt", "a");

    if (f == NULL){
        printf("Hata dosya acilamadi.\n");
        return 1;   
    }


    fprintf(f, "-- Son Maç Skor Durumu --\n\n");
    fprintf(f, "Oyuncu Skoru: %d\n Bilgisayar Skoru: %d\n",oyuncuSkor, bilgisayarSkor);
    fclose(f);


    return 0;    
}
