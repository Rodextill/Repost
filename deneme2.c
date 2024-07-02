#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <locale.h>
#include <time.h>
 
// Maksimum kullan�c� say�s�
#define MAX_KULLANICILAR 100
 
// ortalama fonksiyonu
void printCentered(char *title) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
 
    int titleLength = strlen(title);
 
    printf("%*s\n", ((titleLength + columns) / 2), title);
}

#define WIDTH 119

void pprintCentered(const char* text, int width) {
    int length = strlen(text);
    int padding = (width - length) / 2;
    int i;
    for ( i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", text);
    for (i = 0; i < padding; i++) {
        printf(" ");
    }
    if (length % 2 != 0 && width % 2 == 0) {
        printf(" ");
    }
}

// Verilen bir tarih i�in struct tm olu�turur
struct tm createDate(int year, int month, int day) {
    struct tm date = {0};
    date.tm_year = year - 1900; // tm_year 1900'dan itibaren y�l say�s�n� tutar
    date.tm_mon = month - 1;    // tm_mon 0-11 aras� ay de�erini tutar
    date.tm_mday = day;
    return date;
}


// Rastgele tarih olu�turur
struct tm generateRandomDate(struct tm startDate) {
    time_t start_time = mktime(&startDate);
    int random_days = rand() % 365; // Rastgele 0-364 g�n ekle
    time_t random_time = start_time + (random_days * 24 * 60 * 60); // Rastgele g�n� ekle
    struct tm *random_date = localtime(&random_time);
    return *random_date;
}

 
// Kullan�c� bilgilerini tutan diziler
char kullaniciAdlari[MAX_KULLANICILAR][50];
char sifreler[MAX_KULLANICILAR][50];
int kullaniciSayisi = 0;
 
// Kullan�c� kay�t fonksiyonu
int kullaniciKayit() {
	system("COLOR A");
    if (kullaniciSayisi < MAX_KULLANICILAR) {
        printCentered("KULLANICI ADI: ");
        scanf("%s", kullaniciAdlari[kullaniciSayisi]);
 
        printCentered("��FRE: ");
        scanf("%s", sifreler[kullaniciSayisi]);
        system("cls");
 
        // Dosyaya yazma i�lemi
        FILE *dosya = fopen("kullanicilar.txt", "a");
        if (dosya != NULL) {
            fprintf(dosya, "%s %s\n", kullaniciAdlari[kullaniciSayisi], sifreler[kullaniciSayisi]);
            fclose(dosya);
        } else {
            printCentered("Dosya a�ma hatas�!\n");
        }
 
        printCentered("KAYIT BA�ARIYLA TAMAMLANDI!\n");
 
        kullaniciSayisi++;
        return 1;
    } else {
        printCentered("Maksimum kullan�c� say�s�na ula��ld�!\n");
        return 0;
    }
}
 
// Kullan�c� giri�i fonksiyonu
int kullaniciGirisi() {
	system("COLOR A");
    char kullaniciAdi[50];
    char sifre[50];
 
    printCentered("KULLANICI ADI: ");
    scanf("%s", kullaniciAdi);
 
    printCentered("��FRE: ");
    scanf("%s", sifre);
    system("cls");
 
    // Dosyadan okuma i�lemi
    FILE *dosya = fopen("kullanicilar.txt", "r");
    if (dosya != NULL) {
        while (fscanf(dosya, "%s %s", kullaniciAdlari[kullaniciSayisi], sifreler[kullaniciSayisi]) != EOF) {
            if (strcmp(kullaniciAdi, kullaniciAdlari[kullaniciSayisi]) == 0 && strcmp(sifre, sifreler[kullaniciSayisi]) == 0) {
                printCentered("G�R�� BA�ARIYLA TAMAMLANDI!\n");
                fclose(dosya);
                return 1;
            }
        }
        fclose(dosya);
    } else {
        printCentered("Dosya a�ma hatas�!\n");
    }
 
    printCentered("KULLANICI ADI VEYA ��FRE HATALI!\n");
    return 0;
}
 
struct hasta{ 
        char ad[50]; // Hasta kayd� k�sm� i�in de�i�ken tan�mlama. HASTA KAYDI VE HASTA L�STELEME ���N �NEML� TARAF.
        char soyad[50];
        char cinsiyet[20];
        char emekli_mi[20];
        char sigortali_mi[20];
        char adres[100];
        char telefon[15];
    };
    
    
    int isNumeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0; // Say� de�il
        }
        str++;
    }
    return 1; // Say�
}
 
// �la� yap�s� tan�mlama
typedef struct {
    char ilac_adi[100];
    char barkod[20];
    int ilacfiyat;
} Ilac;
 
void strtrim(char *str) {
  int i = 0, j = strlen(str) - 1;
 
  // Remove leading whitespace
  while (i < strlen(str) && isspace(str[i])) {
    i++;
  }
 
  // Remove trailing whitespace
  while (j >= 0 && isspace(str[j])) {
    j--;
  }
 
  // Truncate the string if necessary
  str[j + 1] = '\0';
 
  // Move the trimmed string to the beginning of the original array
  memmove(str, str + i, j - i + 1);
}

void printMedicationInfo() {
    printf("1. Paracetamol (Asetaminofen)\n\n");
    printf("-Kullan�m alan�: A�r� kesici ve ate� d���r�c�.\n");
    printf("-Olas� yan etkiler: Karaci�er hasar� (y�ksek dozda), mide bulant�s�, alerjik reaksiyonlar (cilt d�k�nt�leri, ka��nt�).\n\n");
    
    printf("2. Ibuprofen\n\n");
    printf("-Kullan�m alan�: A�r� kesici, iltihap giderici ve ate� d���r�c�.\n");
    printf("-Olas� yan etkiler: Mide rahats�zl���, mide �lseri, mide kanamas�, b�brek hasar�, ba� a�r�s�, ba� d�nmesi.\n\n");
    
    printf("3. Aspirin\n\n");
    printf("-Kullan�m alan�: A�r� kesici, iltihap giderici, ate� d���r�c� ve kan suland�r�c�.\n");
    printf("-Olas� yan etkiler: Mide rahats�zl���, mide �lseri, mide kanamas�, alerjik reaksiyonlar, ast�m belirtilerinin k�t�le�mesi.\n\n");
    
    printf("4. Antibiyotikler (�rne�in, Amoksisilin)\n\n");
    printf("-Kullan�m alan�: Bakteriyel enfeksiyonlar�n tedavisi.\n");
    printf("-Olas� yan etkiler: Mide bulant�s�, ishal, mantar enfeksiyonlar� (�rne�in, kandida), alerjik reaksiyonlar (d�k�nt�ler, anafilaksi).\n\n");
    
    printf("5. Antidepresanlar (�rne�in, Sertralin)\n\n");
    printf("-Kullan�m alan�: Depresyon ve anksiyete bozukluklar�n�n tedavisi.\n");
    printf("-Olas� yan etkiler: Bulant�, uyku hali, ba� d�nmesi, cinsel i�lev bozukluklar�, kilo de�i�iklikleri, kuru a��z.\n\n");
    
    printf("6. Antihistaminikler (�rne�in, Loratadin)\n\n");
    printf("-Kullan�m alan�: Alerji belirtilerinin giderilmesi.\n");
    printf("-Olas� yan etkiler: Uyku hali, ba� d�nmesi, a��z kurulu�u, bulant�.\n\n");
    
    printf("7. Proton pompa inhibit�rleri (�rne�in, Omeprazol)\n\n");
    printf("-Kullan�m alan�: Mide asidi ile ilgili sorunlar�n tedavisi (�rne�in, refl�).\n");
    printf("-Olas� yan etkiler: Ba� a�r�s�, mide bulant�s�, ishal, kab�zl�k, kar�n a�r�s�.\n\n");
    
    printf("8. Beta blokerler (�rne�in, Metoprolol)\n\n");
    printf("-Kullan�m alan�: Y�ksek tansiyon, kalp rahats�zl�klar�.\n");
    printf("-Olas� yan etkiler: Yorgunluk, ba� d�nmesi, d���k tansiyon, bradikardi (yava� kalp at���), depresyon.\n\n");
    
    printf("9. Statinler (�rne�in, Atorvastatin)\n\n");
    printf("-Kullan�m alan�: Kolesterol seviyelerinin d���r�lmesi.\n");
    printf("-Olas� yan etkiler: Kas a�r�lar�, karaci�er enzimlerinde art��, sindirim sistemi problemleri, ba� a�r�s�.\n\n");
    
    printf("10. Kortikosteroidler (�rne�in, Prednizon)\n\n");
    printf("-Kullan�m alan�: �ltihap ve alerji belirtilerinin giderilmesi.\n");
    printf("-Olas� yan etkiler: A��z kurulu�u, i�tah art���, kilo al�m�, osteoporoz, y�ksek tansiyon, kan �ekeri seviyelerinde art��.\n");
}

 
 
    
int main()
{
	setlocale(LC_ALL,"Turkish");
	system("COLOR A");
    int secim;
    char ad[50], soyad[50], tc[12], devam, cinsiyet[20],adres[20],tel[20],hasta,h1,barkod[14],ilac[100];
    int isSec, isAdet, isToplam = 0, isOdeme, isParaUstu, i, kontrol, ilacfiyat;
    int ilac1Fiyat = 10, ilac2Fiyat = 20, ilac3Fiyat = 30; //de�i�ken tan�mlama k�sm� bitiyor.
    int secim2;
    char devam2;
    int kullaniciGirildi = 0;
    
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________                      \n");
    printf("                    |__      __|                 \n");
    printf("                       |    |              \n");
    printf("                       |    |         \n");
    printf("                       |    |       \n");
    printf("                       |    |          \n");
    printf("                       |    |          \n");
    printf("                       |    |        \n");
    printf("                       |    |        \n");
    printf("                       |    |                                 \n");
    printf("                       |    |        \n");
    printf("                     __|    |__              \n");
    printf("                    |__________|    \n ");
    Sleep(800);
    system("cls");
    	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                                      ________________                    \n");
    printf("                                     |                |                    \n");
    printf("                                     |    ____________|                   \n");
    printf("                                     |   |                                   \n");
    printf("                                     |   |                               \n");
    printf("                                     |   |    _________                     \n");
    printf("                                     |   |   |         |                     \n");
    printf("                                     |   |   |         |                      \n");
    printf("                                     |   |   |____     |                         \n");
    printf("                                     |   |        |    |                              \n");
    printf("                                     |   |________|    |          \n");
    printf("                                     |                 |                      \n");
    printf("                                     |_________________|          \n ");
    Sleep(800);
    system("cls");
    	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                                                              ____        ____                     \n");
    printf("                                                             |    |      |    |                   \n");
    printf("                                                             |    |      |    |               \n");
    printf("                                                             |    |      |    |                \n");
    printf("                                                             |    |      |    |             \n");
    printf("                                                             |    |      |    |               \n");
    printf("                                                             |    |      |    |                \n");
    printf("                                                             |    |      |    |                  \n");
    printf("                                                             |    |      |    |                    \n");
    printf("                                                             |    |      |    |                         \n");
    printf("                                                             |    |______|    |          \n");
    printf("                                                             |                |                       \n");
    printf("                                                             |________________|     \n ");
    Sleep(800);
    system("cls");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(500);
    system("cls");
    Sleep(500);
    printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(500);
    system("cls");
    Sleep(500);
    printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(300);
    system("cls");
    Sleep(300);
    printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(200);
    system("cls");
    Sleep(200);
    printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(200);
    system("cls");
    Sleep(200);
    printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(100);
    system("cls");
    Sleep(100);
    printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                     __________       ________________        ____        ____                     \n");
    printf("                    |__      __|     |                |      |    |      |    |                   \n");
    printf("                       |    |        |    ____________|      |    |      |    |               \n");
    printf("                       |    |        |   |                   |    |      |    |                \n");
    printf("                       |    |        |   |                   |    |      |    |             \n");
    printf("                       |    |        |   |    _________      |    |      |    |               \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                \n");
    printf("                       |    |        |   |   |         |     |    |      |    |                  \n");
    printf("                       |    |        |   |   |____     |     |    |      |    |                    \n");
    printf("                       |    |        |   |        |    |     |    |      |    |                         \n");
    printf("                       |    |        |   |________|    |     |    |______|    |          \n");
    printf("                     __|    |__      |                 |     |                |                       \n");
    printf("                    |__________|     |_________________|     |________________|     \n ");
    Sleep(2000);
    system("cls");
 
 
	while(1){
	
    do {
    printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                  HOSGELDINIZ, GIRIS KISMINA YONLENDIRILIYORSUNUZ                                            \n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
 
	Sleep(3000);
	system("cls");
        // �lk kutucuk
    int i;
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("1. KAYIT OL", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    

    // �kinci kutucuk
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("2. G�R�� YAP", WIDTH - 2);
    printf("*\n");
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    

    // ���nc� kutucuk
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("3. �IKI�", WIDTH - 2);
    printf("*\n");
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    // D�rd�nc� kutucuk
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("SE��M�N�Z: ", WIDTH - 2);
    printf("*\n");
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
        scanf("%d", &secim2);
        system("cls");
 
        switch (secim2) {
            case 1:
                kullaniciKayit();
                break;
            case 2:
                if (kullaniciGirisi()) {
                    kullaniciGirildi = 1;  // Kullan�c� giri� yapt�ktan sonra flag'i g�ncelle
                    printCentered("ANA MEN�YE Y�NLEND�R�L�YORSUNUZ...\n");
                    Sleep(2000);
                    system("cls");
                    devam2 = kullaniciGirildi;
                } else {
                    devam2 = 'H';
                }
                break;
            case 3:
                printCentered("PROGRAMDAN �IKILIYOR...\n");
                return 0;
                break;
            default:
                printCentered("GE�ERS�Z SE��M! L�TFEN TEKRAR DENEY�N.\n");
                
        }
    } while (0);
 
    
 
    // Kullan�c� giri�i yap�lm��sa devam et
    if (kullaniciGirildi) {
//men�ye olu�turma=Yusuf Yi�it. printf ile se�im yapaca��m�z men�leri ekliyoruz.
    while(1){
	printCentered("ECZANE OTOMASYONU \n\n");  
// �lk kutucuk
    int i;
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("1. SATI� YAP", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");


    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("2. HASTA KAYIT", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");

    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("3. �LA� KAYIT", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");


    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("4. HASTA L�STELE", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");

    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("5. �LA� L�STELE", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("6. RANDEVU L�STELE", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("7. �LA� B�LG�LER/YAN ETK�LER�", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("8. HAZIRLAYANLAR", WIDTH - 2);
    printf("*\n");
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
	printCentered("0-Program� Kapat  \n\n") ; 
	printCentered("Se�iminiz :  ") ; 
	scanf("%d", &secim) ; //burda da se�iminiz dedikten sonra se�im de�i�keniyle birlikte kullan�c�dan se�imini al�yoruz.
	system("cls");
 
    
	
	if(secim==1){  //if e�er se�im 1'e e�it ise sat�� yap kodu devreye girerek �al���cak.
	printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @     @ @     @\n");
    printf("                           @           @  Y�KLENIYOR... \n");
    printf("                            @*********@     63/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @*****@ @*****@\n");
    printf("                           @***********@  Y�KLENIYOR... \n");
    printf("                            @*********@     89/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @***@   @***@ \n");
    printf("                          @*****@ @*****@\n");
    printf("                           @***********@  Y�KLENIYOR... \n");
    printf("                            @*********@     100/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                            ILAC SATIS EKRANINA HOSGELDINIZ                                            \n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
 
	Sleep(2000);
	system("cls");
    printCentered("Ana men�ye d�nmek istiyor musunuz? (E/H): ");
	char devam;
	float para;
	scanf(" %c", &devam);
 
	if (devam == 'E' || devam == 'e') {
    system("cls");
    continue; // Ana men�ye d�nmek i�in d�ng�y� devam ettirir
	} else if (devam == 'H' || devam == 'h') {
    printCentered("��leminize devam edebilirsiniz...\n"); // Kullan�c� "Hay�r" se�erse devam edebilir
	} else {
    printCentered("Ge�ersiz se�im! L�tfen E/H girin.\n");
	}
	
	 char devam1 = 'E'; // Ba�lang��ta d�ng�ye girmek i�in 'E' de�eri atan�r
    do {
	// �la� veritaban� dosyas�n� a�ma
  FILE *ilacDosyasi = fopen("ilac_veritabani.txt", "r");
  if (ilacDosyasi == NULL) {
    printCentered("�la� veritaban� dosyas� bulunamad�!\n");
    return 1;
  }
 
  // �la�lar� okuma ve ila�lar dizisine ekleme
  Ilac ilaclar[100]; // Maksimum 100 ila� i�in yer ayr�ld�
  int ilacSayisi = 0;
 
  char satir[100];
  while (fgets(satir, sizeof(satir), ilacDosyasi) != NULL) {
    if (strncmp(satir, "ILAC ISMI: ", 11) == 0) {
      strcpy(ilaclar[ilacSayisi].ilac_adi, satir + 11);
      fgets(satir, sizeof(satir), ilacDosyasi); // Barkod numaras�n� oku
      strcpy(ilaclar[ilacSayisi].barkod, satir + 20); // "ILAC BARKOD NUMARASI: " uzunlu�u 20
      fgets(satir, sizeof(satir), ilacDosyasi); // Bo� sat�r� atla
      fgets(satir, sizeof(satir), ilacDosyasi); // Fiyat� oku
      ilaclar[ilacSayisi].ilacfiyat = atoi(satir + 12); // "ILAC FIYATI: " uzunlu�u 12
      fgets(satir, sizeof(satir), ilacDosyasi); // Bo� sat�r� atla
      ilacSayisi++;
    }
  }
 
  fclose(ilacDosyasi);
 
  // Sat�� yap�lacak ilac� ve adetini kullan�c�dan alma
  char satilacakIlac[100];
  int adet;
 
  printCentered("Sat�lacak ilac�n ismini girin: ");
  scanf("%s", satilacakIlac);
  printCentered("Ka� adet sat�n almak istiyorsunuz? ");
  scanf("%d", &adet);
  
  int urunIndex = -1;
  int i;
  for ( i = 0; i < ilacSayisi; i++) {
    
    char trimmedSatilacakIlac[100];
    strcpy(trimmedSatilacakIlac, satilacakIlac);
    strtrim(trimmedSatilacakIlac); 
 
    char trimmedIlacAdi[100];
    strcpy(trimmedIlacAdi, ilaclar[i].ilac_adi);
    strtrim(trimmedIlacAdi); 
 
    if (strcasecmp(trimmedIlacAdi, trimmedSatilacakIlac) == 0) {
      urunIndex = i;
      break;
    }
  }
 
  // Hata mesajlar� ve toplam tutar hesaplama
  if (urunIndex == -1) {
    printCentered("�zg�n�z, belirtilen ila� bulunamad�!\n");
  } else if (adet <= 0) {
    printCentered("L�tfen ge�erli bir adet girin!\n");
  } else {
    //Toplam tutar ve para �st� hesaplama
    int toplamTutar=adet*ilaclar[urunIndex].ilacfiyat;
    printf("\nSat�n al�nan ilac�n ismi:%s\n",ilaclar[urunIndex].ilac_adi);
    printf("Sat�n al�nan adet:%d \n",adet);
    printf("Toplam Tutar:%d TL\n",toplamTutar);
    
    printCentered("\nSat�n alma i�lemi i�in �deyece�iniz tutar� giriniz(TL):");
    scanf("%f",&para);
    if(toplamTutar>para){
    	printCentered("Yetersiz para miktar�! L�tfen ilac�n fiyat�n� tam olarak �deyin.\n");
	}else if(para > toplamTutar){
		float ust = para - (float)toplamTutar;
		printf("%d adet ila� al��veri�inize vermi� oldu�unuz %.0f i�in para �st�n�z %.0f TL", adet, para, ust);
	}else{
		printCentered("Ba�ar�yla al��veri�iniz ger�ekle�ti.");
		system("cls");
	}
  }
  	char devam;
  	 printCentered("\nBa�ka bir ila� almak istiyor musunuz? (E/H): ");
        scanf(" %c", &devam);
        
 
        // Giri�lerin tamam�n� t�ketmek i�in kullan�lan kod
        while (getchar() != '\n');
        if(devam=='E'||devam=='e'){
		}else{
			devam1='H';
		}
 
   } while (devam1 == 'E' || devam1 == 'e');
    printCentered("Ana men�ye d�n�l�yor...\n");
 
 
}
	else if(secim==2){ //else if se�im 2'ye e�it ise hasta kayd� k�sm� devreye giricek.
	printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @     @ @     @\n");
    printf("                           @           @  YUKLENIYOR... \n");
    printf("                            @*********@     63/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @*****@ @*****@\n");
    printf("                           @***********@  YUKLENIYOR... \n");
    printf("                            @*********@     89/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @***@   @***@ \n");
    printf("                          @*****@ @*****@\n");
    printf("                           @***********@  YUKLENIYOR... \n");
    printf("                            @*********@     100/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                            HASTA KAYIT EKRANINA HOSGELDINIZ                                            \n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
 
	Sleep(2000);
	system("cls");
	printCentered("Ana men�ye d�nmek istiyor musunuz? (E/H): ");
	char devam;
	scanf(" %c", &devam);
 
	if (devam == 'E' || devam == 'e') {
    system("cls");
    continue; // Ana men�ye d�nmek i�in d�ng�y� devam ettirir
	} else if (devam == 'H' || devam == 'h') {
    printCentered("��leminize devam edebilirsiniz...\n"); // Kullan�c� "Hay�r" se�erse devam edebilir
	} else {
    printCentered("Ge�ersiz se�im! L�tfen E/H girin.\n");
	}
	struct hasta hasta; //yukar�da struct komutu ile tan�mlad���m�z de�i�kenleri burada takma isime aktar�yoruz.
    FILE *dosyaYaz= // ufak bir veritaban� tutmak i�in .txt uzant�l� bir klas�r a��yoruz ve buna dosyaYaz ismi veriyoruz.
    fopen("hasta_bilgileri.txt", "a"); // Hasta_bilgiler.txt ad� alt�nda bir dosya a��yorruz.
    
    if(dosyaYaz==NULL){ //E�er dosya bulunamaz ya da yok ise dosya a�ma hatas�yla kar��la��yoruz.
        fprintf(stderr, "Dosya a�ma hatas�!\n");
        return 1;
    }
    printCentered("Ad: "); //Kullan�c�dan veri alma k�sm�.
    scanf("%s", hasta.ad); // Yukar�da belirtti�imiz stuct hasta hasta; komutunu burada g�r�yoruz hasta yaz�p "." i�areti koyduktan sonra yukar�da tan�mlad���m�z de�i�kenleri teker teker g�r�p kolayca ula�abilece�iz.
    printCentered("�SM�N�Z BA�ARIYLA KAYIT ED�LD�!");
    fprintf(dosyaYaz, "ad: %s\n", hasta.ad);
    sleep(2);
    
    system("cls");
    printCentered("Soyad: ");
    scanf("%s", hasta.soyad);
    printCentered("SOYADINIZ BA�ARIYLA KAYIT ED�LD�!");
    fprintf(dosyaYaz, "Soyad: %s\n", hasta.soyad);
    sleep(2);
    
    system("cls");
    printCentered("Cinsiyet?  (E/K): ");;
    scanf("%s", hasta.cinsiyet);
    printCentered("C�NS�YET�N�Z BA�ARIYLA KAYIT ED�LD�!");
    fprintf(dosyaYaz, "Cinsiyet: %s\n", hasta.cinsiyet);
    sleep(2);
    
    system("cls");
    printCentered("Emekli mi? (E/H): ");
    scanf("%s", hasta.emekli_mi);
    printCentered("SE��M�N�Z BA�ARIYLA KAYIT ED�LD�!");
    fprintf(dosyaYaz, "Emekli mi?: %s\n", hasta.emekli_mi);
    sleep(2);
    
	system("cls");
    printCentered("Sigortal� m�? (E/H): ");
    scanf("%s", hasta.sigortali_mi);
    printCentered("SE��M�N�Z BA�ARIYLA KAYIT ED�LD�!");
    fprintf(dosyaYaz, "Sigortali m�?: %s\n", hasta.sigortali_mi);
    fprintf(dosyaYaz, "-------------------------------------------------------\n");
    sleep(2);
    
    
    
    fclose(dosyaYaz); //B�t�n verileri ald�ktan sonra DosyaYaz adl� de�i�keni klas�r ile beraber kapat�yoruz.
    system("cls");
	}
	else if(secim==3){ //se�im 3'e e�itse ila� kayd� k�sm� devreye giricek.
	system("cls");
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @     @ @     @\n");
    printf("                           @           @  YUKLENIYOR... \n");
    printf("                            @*********@     63/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @*****@ @*****@\n");
    printf("                           @***********@  YUKLENIYOR... \n");
    printf("                            @*********@     89/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
    
    printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @***@   @***@ \n");
    printf("                          @*****@ @*****@\n");
    printf("                           @***********@  YUKLENIYOR... \n");
    printf("                            @*********@     100/100 \n");
    printf("                             @*******@      \n");
    printf("                              @*****@       \n");
    printf("                               @***@        \n");
    printf("                                @*@         \n");
    
    Sleep(1300);
    system("cls");
    
char ilac[100];	
char barkod[20];
int i;
int isnumber = 1;
int isvalidlength = 0; 
system("COLOR A");
 
printf("------------------------------------------------------------------------------------------------------------------------\n");
printf("                                            ILAC KAYIT EKRANINA HOSGELDINIZ                                            \n");
printf("------------------------------------------------------------------------------------------------------------------------\n");
 
Sleep(2000);
system("cls");
 
	printCentered("\nAna men�ye d�nmek istiyor musunuz? (E/H): ");
	char devam;
	scanf(" %c", &devam);
 
	if (devam == 'E' || devam == 'e') {
    system("cls");
    continue; // Ana men�ye d�nmek i�in d�ng�y� devam ettirir
	} else if (devam == 'H' || devam == 'h') {
    printCentered("��leminize devam edebilirsiniz...\n"); // Kullan�c� "Hay�r" se�erse devam edebilir
	} else {
    printCentered("Ge�ersiz se�im! L�tfen E/H girin.\n");
	}
 
printCentered("�LA� BARKOD NUMARASINI 13 HANEL� OLACAK �EKILDE G�R�N�Z:\n");
scanf("%s",barkod);
 
for(i=0;i<strlen(barkod);i++)
{
	if(!isdigit(barkod[i]))
	{
		isnumber=0;
		break;
	}
}
if(isnumber)
{
	if(strlen(barkod)==13)
	{
		isvalidlength = 1;
	}
}
if(!isnumber)
{
	printCentered("HATA ALDINIZ BARKOD SAYILARDAN OLU�MALIDIR\n");
}
else if(!isvalidlength)
{
	printCentered("HATA ALDINIZ BARKOD 13 HANEDEN OLU�MALIDIR\n");
}
else
{
	system("cls");
	printCentered("BARKOD BA�ARIYLA KAYDED�LD�");
	Sleep(2000);
	system("cls");
	printCentered("�LA� �SM�N� G�R�N�Z: \n ");
	scanf("%s",ilac);
	system("cls");
	printCentered("�LA� �SM� BA�ARIYLA KAYDED�LD�");
	Sleep(2000);
	system("cls");
	printCentered("�LA� F�YATINI G�R�N��Z: \n");
	scanf("%d",&ilacfiyat);
	system("cls");
	printCentered("�LA� F�YATI BA�ARIYLA KAYDED�LD�\n");
	Sleep(2000);
	system("cls");
	printf("�LA�:%s\n",ilac);
	printf("BARKOD:%s\n",barkod);
	printf("F�YAT:%d",ilacfiyat);
}
 
 
    // Veritaban� dosyas�na ekleme
    FILE *dosya = fopen("ilac_veritabani.txt", "a");
 
    if (dosya == NULL) {
        printCentered("Dosya a�ma hatas�!\n");
        return 1;
    }
 
    fprintf(dosya, "ILAC ISMI: %s\n", ilac);
    fprintf(dosya, "ILAC BARKOD NUMARASI: %s\n\n", barkod);
    fprintf(dosya, "ILAC FIYATI: %d\n", ilacfiyat);
    fprintf(dosya, "-------------------------------------------------------\n");
 
    fclose(dosya);
    
    system("cls");
 
	}
	else if(secim==4){ // se�im 4'e e�it ise hastalar� listeleme taraf� devreye giricek.
	FILE *dosyaOku=
    fopen("hasta_bilgileri.txt", "r");
    
    if(dosyaOku==NULL){
        fprintf(stderr,"Dosya a�ma hatas�!\n");
        return 1;
    }
    
    char satir[100];
    int bosDosya = 1; // Dosyan�n bo� olup olmad���n� kontrol etmek i�in bir bayrak
	if(fgets(satir, sizeof(satir), dosyaOku) != NULL){
        printCentered("\nHasta Bilgileri:\n");
    	printf("%s", satir);
		while(fgets(satir, sizeof(satir),dosyaOku)!=NULL){
        printf("%s", satir);
        }
	}else{
		printf("Dosya bo�.\n");
	}
        fclose(dosyaOku);
	}
	
	else if(secim==5){
	FILE *dosyaOku = fopen("ilac_veritabani.txt", "r");
    
	if(dosyaOku == NULL){
    	fprintf(stderr, "Dosya a�ma hatas�!\n");
    	return 1;
	}
 
	char satir[100];
	int bosDosya = 1; // Dosyan�n bo� olup olmad���n� kontrol etmek i�in bir bayrak
	if(fgets(satir, sizeof(satir), dosyaOku) != NULL){
    	printCentered("\n�la� Bilgileri:\n");
    	printf("%s", satir);
    	while(fgets(satir, sizeof(satir),dosyaOku)!=NULL){
        printf("%s", satir);
        }
        
	}else{
		printf("Dosya bo�.\n");
	}
 
	fclose(dosyaOku);
 
	}
	
	else if(secim==6){
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                            RANDEVU L�STELE EKRANINA HOSGELDINIZ                                            \n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
 	// 29 May�s 2024 ba�lang�� tarihi
    struct tm startDate = createDate(2024, 5, 29);

    // Rastgele say� �reticisini ba�lat
    srand(time(NULL));

    // Doktorlar i�in rastgele tarih �ret
    struct tm random_date_ahmet = generateRandomDate(startDate);
    struct tm random_date_bilal = generateRandomDate(startDate);
    struct tm random_date_serkan = generateRandomDate(startDate);
    struct tm random_date_charles = generateRandomDate(startDate);
    struct tm random_date_kendrick = generateRandomDate(startDate);

    // Sonu�lar� yazd�r
    printf("En Yak�n Randevu Tarihi:\n Doktor Ahmet i�in: %d-%02d-%02d\n",
           random_date_ahmet.tm_year + 1900,
           random_date_ahmet.tm_mon + 1,
           random_date_ahmet.tm_mday);

    printf("En Yak�n Randevu Tarihi:\n Doktor Bilal i�in: %d-%02d-%02d\n",
           random_date_bilal.tm_year + 1900,
           random_date_bilal.tm_mon + 1,
           random_date_bilal.tm_mday);

    printf("En Yak�n Randevu Tarihi:\n Doktor Serkan i�in: %d-%02d-%02d\n",
           random_date_serkan.tm_year + 1900,
           random_date_serkan.tm_mon + 1,
           random_date_serkan.tm_mday);

    printf("En Yak�n Randevu Tarihi:\n Doktor Charles i�in: %d-%02d-%02d\n",
           random_date_charles.tm_year + 1900,
           random_date_charles.tm_mon + 1,
           random_date_charles.tm_mday);

    printf("En Yak�n Randevu Tarihi:\n Doktor Kendrick Lamar i�in: %d-%02d-%02d\n",
           random_date_kendrick.tm_year + 1900,
           random_date_kendrick.tm_mon + 1,
           random_date_kendrick.tm_mday);
	}
	

	if (secim == 7) {
        printMedicationInfo();
    }
    
    if (secim == 8) {
    printf("--HAZIRLAYANLAR--\n\n");
    printf("--Yusuf Yi�it AYDIN\n");
    printf("--Ahmet Emin DO�AN\n");
    printf("--Sarptu� K�K\n");
    printf("--Merve KAYA\n");
    printf("--Muhammed YAMAN\n");
        
    }
	
    if(secim==0){
        printCentered("Programdan ��k�l�yor, bizi se�ti�iniz i�in te�ekk�rler...\n");
        return 0;
        break;
    }
      }
}
}
 
    return 0;
}
