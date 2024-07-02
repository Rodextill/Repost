#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include <locale.h>
#include <time.h>
 
// Maksimum kullanýcý sayýsý
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

// Verilen bir tarih için struct tm oluþturur
struct tm createDate(int year, int month, int day) {
    struct tm date = {0};
    date.tm_year = year - 1900; // tm_year 1900'dan itibaren yýl sayýsýný tutar
    date.tm_mon = month - 1;    // tm_mon 0-11 arasý ay deðerini tutar
    date.tm_mday = day;
    return date;
}


// Rastgele tarih oluþturur
struct tm generateRandomDate(struct tm startDate) {
    time_t start_time = mktime(&startDate);
    int random_days = rand() % 365; // Rastgele 0-364 gün ekle
    time_t random_time = start_time + (random_days * 24 * 60 * 60); // Rastgele günü ekle
    struct tm *random_date = localtime(&random_time);
    return *random_date;
}

 
// Kullanýcý bilgilerini tutan diziler
char kullaniciAdlari[MAX_KULLANICILAR][50];
char sifreler[MAX_KULLANICILAR][50];
int kullaniciSayisi = 0;
 
// Kullanýcý kayýt fonksiyonu
int kullaniciKayit() {
	system("COLOR A");
    if (kullaniciSayisi < MAX_KULLANICILAR) {
        printCentered("KULLANICI ADI: ");
        scanf("%s", kullaniciAdlari[kullaniciSayisi]);
 
        printCentered("ÞÝFRE: ");
        scanf("%s", sifreler[kullaniciSayisi]);
        system("cls");
 
        // Dosyaya yazma iþlemi
        FILE *dosya = fopen("kullanicilar.txt", "a");
        if (dosya != NULL) {
            fprintf(dosya, "%s %s\n", kullaniciAdlari[kullaniciSayisi], sifreler[kullaniciSayisi]);
            fclose(dosya);
        } else {
            printCentered("Dosya açma hatasý!\n");
        }
 
        printCentered("KAYIT BAÞARIYLA TAMAMLANDI!\n");
 
        kullaniciSayisi++;
        return 1;
    } else {
        printCentered("Maksimum kullanýcý sayýsýna ulaþýldý!\n");
        return 0;
    }
}
 
// Kullanýcý giriþi fonksiyonu
int kullaniciGirisi() {
	system("COLOR A");
    char kullaniciAdi[50];
    char sifre[50];
 
    printCentered("KULLANICI ADI: ");
    scanf("%s", kullaniciAdi);
 
    printCentered("ÞÝFRE: ");
    scanf("%s", sifre);
    system("cls");
 
    // Dosyadan okuma iþlemi
    FILE *dosya = fopen("kullanicilar.txt", "r");
    if (dosya != NULL) {
        while (fscanf(dosya, "%s %s", kullaniciAdlari[kullaniciSayisi], sifreler[kullaniciSayisi]) != EOF) {
            if (strcmp(kullaniciAdi, kullaniciAdlari[kullaniciSayisi]) == 0 && strcmp(sifre, sifreler[kullaniciSayisi]) == 0) {
                printCentered("GÝRÝÞ BAÞARIYLA TAMAMLANDI!\n");
                fclose(dosya);
                return 1;
            }
        }
        fclose(dosya);
    } else {
        printCentered("Dosya açma hatasý!\n");
    }
 
    printCentered("KULLANICI ADI VEYA ÞÝFRE HATALI!\n");
    return 0;
}
 
struct hasta{ 
        char ad[50]; // Hasta kaydý kýsmý için deðiþken tanýmlama. HASTA KAYDI VE HASTA LÝSTELEME ÝÇÝN ÖNEMLÝ TARAF.
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
            return 0; // Sayý deðil
        }
        str++;
    }
    return 1; // Sayý
}
 
// Ýlaç yapýsý tanýmlama
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
    printf("-Kullaným alaný: Aðrý kesici ve ateþ düþürücü.\n");
    printf("-Olasý yan etkiler: Karaciðer hasarý (yüksek dozda), mide bulantýsý, alerjik reaksiyonlar (cilt döküntüleri, kaþýntý).\n\n");
    
    printf("2. Ibuprofen\n\n");
    printf("-Kullaným alaný: Aðrý kesici, iltihap giderici ve ateþ düþürücü.\n");
    printf("-Olasý yan etkiler: Mide rahatsýzlýðý, mide ülseri, mide kanamasý, böbrek hasarý, baþ aðrýsý, baþ dönmesi.\n\n");
    
    printf("3. Aspirin\n\n");
    printf("-Kullaným alaný: Aðrý kesici, iltihap giderici, ateþ düþürücü ve kan sulandýrýcý.\n");
    printf("-Olasý yan etkiler: Mide rahatsýzlýðý, mide ülseri, mide kanamasý, alerjik reaksiyonlar, astým belirtilerinin kötüleþmesi.\n\n");
    
    printf("4. Antibiyotikler (örneðin, Amoksisilin)\n\n");
    printf("-Kullaným alaný: Bakteriyel enfeksiyonlarýn tedavisi.\n");
    printf("-Olasý yan etkiler: Mide bulantýsý, ishal, mantar enfeksiyonlarý (örneðin, kandida), alerjik reaksiyonlar (döküntüler, anafilaksi).\n\n");
    
    printf("5. Antidepresanlar (örneðin, Sertralin)\n\n");
    printf("-Kullaným alaný: Depresyon ve anksiyete bozukluklarýnýn tedavisi.\n");
    printf("-Olasý yan etkiler: Bulantý, uyku hali, baþ dönmesi, cinsel iþlev bozukluklarý, kilo deðiþiklikleri, kuru aðýz.\n\n");
    
    printf("6. Antihistaminikler (örneðin, Loratadin)\n\n");
    printf("-Kullaným alaný: Alerji belirtilerinin giderilmesi.\n");
    printf("-Olasý yan etkiler: Uyku hali, baþ dönmesi, aðýz kuruluðu, bulantý.\n\n");
    
    printf("7. Proton pompa inhibitörleri (örneðin, Omeprazol)\n\n");
    printf("-Kullaným alaný: Mide asidi ile ilgili sorunlarýn tedavisi (örneðin, reflü).\n");
    printf("-Olasý yan etkiler: Baþ aðrýsý, mide bulantýsý, ishal, kabýzlýk, karýn aðrýsý.\n\n");
    
    printf("8. Beta blokerler (örneðin, Metoprolol)\n\n");
    printf("-Kullaným alaný: Yüksek tansiyon, kalp rahatsýzlýklarý.\n");
    printf("-Olasý yan etkiler: Yorgunluk, baþ dönmesi, düþük tansiyon, bradikardi (yavaþ kalp atýþý), depresyon.\n\n");
    
    printf("9. Statinler (örneðin, Atorvastatin)\n\n");
    printf("-Kullaným alaný: Kolesterol seviyelerinin düþürülmesi.\n");
    printf("-Olasý yan etkiler: Kas aðrýlarý, karaciðer enzimlerinde artýþ, sindirim sistemi problemleri, baþ aðrýsý.\n\n");
    
    printf("10. Kortikosteroidler (örneðin, Prednizon)\n\n");
    printf("-Kullaným alaný: Ýltihap ve alerji belirtilerinin giderilmesi.\n");
    printf("-Olasý yan etkiler: Aðýz kuruluðu, iþtah artýþý, kilo alýmý, osteoporoz, yüksek tansiyon, kan þekeri seviyelerinde artýþ.\n");
}

 
 
    
int main()
{
	setlocale(LC_ALL,"Turkish");
	system("COLOR A");
    int secim;
    char ad[50], soyad[50], tc[12], devam, cinsiyet[20],adres[20],tel[20],hasta,h1,barkod[14],ilac[100];
    int isSec, isAdet, isToplam = 0, isOdeme, isParaUstu, i, kontrol, ilacfiyat;
    int ilac1Fiyat = 10, ilac2Fiyat = 20, ilac3Fiyat = 30; //deðiþken tanýmlama kýsmý bitiyor.
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
        // Ýlk kutucuk
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
    

    // Ýkinci kutucuk
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("2. GÝRÝÞ YAP", WIDTH - 2);
    printf("*\n");
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    

    // Üçüncü kutucuk
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("3. ÇIKIÞ", WIDTH - 2);
    printf("*\n");
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    // Dördüncü kutucuk
    for (i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("SEÇÝMÝNÝZ: ", WIDTH - 2);
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
                    kullaniciGirildi = 1;  // Kullanýcý giriþ yaptýktan sonra flag'i güncelle
                    printCentered("ANA MENÜYE YÖNLENDÝRÝLÝYORSUNUZ...\n");
                    Sleep(2000);
                    system("cls");
                    devam2 = kullaniciGirildi;
                } else {
                    devam2 = 'H';
                }
                break;
            case 3:
                printCentered("PROGRAMDAN ÇIKILIYOR...\n");
                return 0;
                break;
            default:
                printCentered("GEÇERSÝZ SEÇÝM! LÜTFEN TEKRAR DENEYÝN.\n");
                
        }
    } while (0);
 
    
 
    // Kullanýcý giriþi yapýlmýþsa devam et
    if (kullaniciGirildi) {
//menüye oluþturma=Yusuf Yiðit. printf ile seçim yapacaðýmýz menüleri ekliyoruz.
    while(1){
	printCentered("ECZANE OTOMASYONU \n\n");  
// Ýlk kutucuk
    int i;
    for ( i = 0; i < WIDTH; i++) {
        printf("*");
    }
    printf("\n");
    printf("*");
    pprintCentered("1. SATIÞ YAP", WIDTH - 2);
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
    pprintCentered("3. ÝLAÇ KAYIT", WIDTH - 2);
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
    pprintCentered("4. HASTA LÝSTELE", WIDTH - 2);
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
    pprintCentered("5. ÝLAÇ LÝSTELE", WIDTH - 2);
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
    pprintCentered("6. RANDEVU LÝSTELE", WIDTH - 2);
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
    pprintCentered("7. ÝLAÇ BÝLGÝLER/YAN ETKÝLERÝ", WIDTH - 2);
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
	printCentered("0-Programý Kapat  \n\n") ; 
	printCentered("Seçiminiz :  ") ; 
	scanf("%d", &secim) ; //burda da seçiminiz dedikten sonra seçim deðiþkeniyle birlikte kullanýcýdan seçimini alýyoruz.
	system("cls");
 
    
	
	if(secim==1){  //if eðer seçim 1'e eþit ise satýþ yap kodu devreye girerek çalýþýcak.
	printf("                       ___  _     _____  ____ \n");
    printf("                      |_ _|| |   |  _  ||  __|\n");
    printf("                       | | | |   |  _  || |   \n");
    printf("                       | | | |__ | | | || |__ \n");
    printf("                      |___||____||_| |_||____|\n");
 
 
    printf("                            @@@     @@@  \n");
    printf("                           @   @   @   @ \n");
    printf("                          @     @ @     @\n");
    printf("                           @           @  YÜKLENIYOR... \n");
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
    printf("                           @***********@  YÜKLENIYOR... \n");
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
    printf("                           @***********@  YÜKLENIYOR... \n");
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
    printCentered("Ana menüye dönmek istiyor musunuz? (E/H): ");
	char devam;
	float para;
	scanf(" %c", &devam);
 
	if (devam == 'E' || devam == 'e') {
    system("cls");
    continue; // Ana menüye dönmek için döngüyü devam ettirir
	} else if (devam == 'H' || devam == 'h') {
    printCentered("Ýþleminize devam edebilirsiniz...\n"); // Kullanýcý "Hayýr" seçerse devam edebilir
	} else {
    printCentered("Geçersiz seçim! Lütfen E/H girin.\n");
	}
	
	 char devam1 = 'E'; // Baþlangýçta döngüye girmek için 'E' deðeri atanýr
    do {
	// Ýlaç veritabaný dosyasýný açma
  FILE *ilacDosyasi = fopen("ilac_veritabani.txt", "r");
  if (ilacDosyasi == NULL) {
    printCentered("Ýlaç veritabaný dosyasý bulunamadý!\n");
    return 1;
  }
 
  // Ýlaçlarý okuma ve ilaçlar dizisine ekleme
  Ilac ilaclar[100]; // Maksimum 100 ilaç için yer ayrýldý
  int ilacSayisi = 0;
 
  char satir[100];
  while (fgets(satir, sizeof(satir), ilacDosyasi) != NULL) {
    if (strncmp(satir, "ILAC ISMI: ", 11) == 0) {
      strcpy(ilaclar[ilacSayisi].ilac_adi, satir + 11);
      fgets(satir, sizeof(satir), ilacDosyasi); // Barkod numarasýný oku
      strcpy(ilaclar[ilacSayisi].barkod, satir + 20); // "ILAC BARKOD NUMARASI: " uzunluðu 20
      fgets(satir, sizeof(satir), ilacDosyasi); // Boþ satýrý atla
      fgets(satir, sizeof(satir), ilacDosyasi); // Fiyatý oku
      ilaclar[ilacSayisi].ilacfiyat = atoi(satir + 12); // "ILAC FIYATI: " uzunluðu 12
      fgets(satir, sizeof(satir), ilacDosyasi); // Boþ satýrý atla
      ilacSayisi++;
    }
  }
 
  fclose(ilacDosyasi);
 
  // Satýþ yapýlacak ilacý ve adetini kullanýcýdan alma
  char satilacakIlac[100];
  int adet;
 
  printCentered("Satýlacak ilacýn ismini girin: ");
  scanf("%s", satilacakIlac);
  printCentered("Kaç adet satýn almak istiyorsunuz? ");
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
 
  // Hata mesajlarý ve toplam tutar hesaplama
  if (urunIndex == -1) {
    printCentered("Üzgünüz, belirtilen ilaç bulunamadý!\n");
  } else if (adet <= 0) {
    printCentered("Lütfen geçerli bir adet girin!\n");
  } else {
    //Toplam tutar ve para üstü hesaplama
    int toplamTutar=adet*ilaclar[urunIndex].ilacfiyat;
    printf("\nSatýn alýnan ilacýn ismi:%s\n",ilaclar[urunIndex].ilac_adi);
    printf("Satýn alýnan adet:%d \n",adet);
    printf("Toplam Tutar:%d TL\n",toplamTutar);
    
    printCentered("\nSatýn alma iþlemi için ödeyeceðiniz tutarý giriniz(TL):");
    scanf("%f",&para);
    if(toplamTutar>para){
    	printCentered("Yetersiz para miktarý! Lütfen ilacýn fiyatýný tam olarak ödeyin.\n");
	}else if(para > toplamTutar){
		float ust = para - (float)toplamTutar;
		printf("%d adet ilaç alýþveriþinize vermiþ olduðunuz %.0f için para üstünüz %.0f TL", adet, para, ust);
	}else{
		printCentered("Baþarýyla alýþveriþiniz gerçekleþti.");
		system("cls");
	}
  }
  	char devam;
  	 printCentered("\nBaþka bir ilaç almak istiyor musunuz? (E/H): ");
        scanf(" %c", &devam);
        
 
        // Giriþlerin tamamýný tüketmek için kullanýlan kod
        while (getchar() != '\n');
        if(devam=='E'||devam=='e'){
		}else{
			devam1='H';
		}
 
   } while (devam1 == 'E' || devam1 == 'e');
    printCentered("Ana menüye dönülüyor...\n");
 
 
}
	else if(secim==2){ //else if seçim 2'ye eþit ise hasta kaydý kýsmý devreye giricek.
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
	printCentered("Ana menüye dönmek istiyor musunuz? (E/H): ");
	char devam;
	scanf(" %c", &devam);
 
	if (devam == 'E' || devam == 'e') {
    system("cls");
    continue; // Ana menüye dönmek için döngüyü devam ettirir
	} else if (devam == 'H' || devam == 'h') {
    printCentered("Ýþleminize devam edebilirsiniz...\n"); // Kullanýcý "Hayýr" seçerse devam edebilir
	} else {
    printCentered("Geçersiz seçim! Lütfen E/H girin.\n");
	}
	struct hasta hasta; //yukarýda struct komutu ile tanýmladýðýmýz deðiþkenleri burada takma isime aktarýyoruz.
    FILE *dosyaYaz= // ufak bir veritabaný tutmak için .txt uzantýlý bir klasör açýyoruz ve buna dosyaYaz ismi veriyoruz.
    fopen("hasta_bilgileri.txt", "a"); // Hasta_bilgiler.txt adý altýnda bir dosya açýyorruz.
    
    if(dosyaYaz==NULL){ //Eðer dosya bulunamaz ya da yok ise dosya açma hatasýyla karþýlaþýyoruz.
        fprintf(stderr, "Dosya açma hatasý!\n");
        return 1;
    }
    printCentered("Ad: "); //Kullanýcýdan veri alma kýsmý.
    scanf("%s", hasta.ad); // Yukarýda belirttiðimiz stuct hasta hasta; komutunu burada görüyoruz hasta yazýp "." iþareti koyduktan sonra yukarýda tanýmladýðýmýz deðiþkenleri teker teker görüp kolayca ulaþabileceðiz.
    printCentered("ÝSMÝNÝZ BAÞARIYLA KAYIT EDÝLDÝ!");
    fprintf(dosyaYaz, "ad: %s\n", hasta.ad);
    sleep(2);
    
    system("cls");
    printCentered("Soyad: ");
    scanf("%s", hasta.soyad);
    printCentered("SOYADINIZ BAÞARIYLA KAYIT EDÝLDÝ!");
    fprintf(dosyaYaz, "Soyad: %s\n", hasta.soyad);
    sleep(2);
    
    system("cls");
    printCentered("Cinsiyet?  (E/K): ");;
    scanf("%s", hasta.cinsiyet);
    printCentered("CÝNSÝYETÝNÝZ BAÞARIYLA KAYIT EDÝLDÝ!");
    fprintf(dosyaYaz, "Cinsiyet: %s\n", hasta.cinsiyet);
    sleep(2);
    
    system("cls");
    printCentered("Emekli mi? (E/H): ");
    scanf("%s", hasta.emekli_mi);
    printCentered("SEÇÝMÝNÝZ BAÞARIYLA KAYIT EDÝLDÝ!");
    fprintf(dosyaYaz, "Emekli mi?: %s\n", hasta.emekli_mi);
    sleep(2);
    
	system("cls");
    printCentered("Sigortalý mý? (E/H): ");
    scanf("%s", hasta.sigortali_mi);
    printCentered("SEÇÝMÝNÝZ BAÞARIYLA KAYIT EDÝLDÝ!");
    fprintf(dosyaYaz, "Sigortali mý?: %s\n", hasta.sigortali_mi);
    fprintf(dosyaYaz, "-------------------------------------------------------\n");
    sleep(2);
    
    
    
    fclose(dosyaYaz); //Bütün verileri aldýktan sonra DosyaYaz adlý deðiþkeni klasör ile beraber kapatýyoruz.
    system("cls");
	}
	else if(secim==3){ //seçim 3'e eþitse ilaç kaydý kýsmý devreye giricek.
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
 
	printCentered("\nAna menüye dönmek istiyor musunuz? (E/H): ");
	char devam;
	scanf(" %c", &devam);
 
	if (devam == 'E' || devam == 'e') {
    system("cls");
    continue; // Ana menüye dönmek için döngüyü devam ettirir
	} else if (devam == 'H' || devam == 'h') {
    printCentered("Ýþleminize devam edebilirsiniz...\n"); // Kullanýcý "Hayýr" seçerse devam edebilir
	} else {
    printCentered("Geçersiz seçim! Lütfen E/H girin.\n");
	}
 
printCentered("ÝLAÇ BARKOD NUMARASINI 13 HANELÝ OLACAK ÞEKILDE GÝRÝNÝZ:\n");
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
	printCentered("HATA ALDINIZ BARKOD SAYILARDAN OLUÞMALIDIR\n");
}
else if(!isvalidlength)
{
	printCentered("HATA ALDINIZ BARKOD 13 HANEDEN OLUÞMALIDIR\n");
}
else
{
	system("cls");
	printCentered("BARKOD BAÞARIYLA KAYDEDÝLDÝ");
	Sleep(2000);
	system("cls");
	printCentered("ÝLAÇ ÝSMÝNÝ GÝRÝNÝZ: \n ");
	scanf("%s",ilac);
	system("cls");
	printCentered("ÝLAÇ ÝSMÝ BAÞARIYLA KAYDEDÝLDÝ");
	Sleep(2000);
	system("cls");
	printCentered("ÝLAÇ FÝYATINI GÝRÝNÝÝZ: \n");
	scanf("%d",&ilacfiyat);
	system("cls");
	printCentered("ÝLAÇ FÝYATI BAÞARIYLA KAYDEDÝLDÝ\n");
	Sleep(2000);
	system("cls");
	printf("ÝLAÇ:%s\n",ilac);
	printf("BARKOD:%s\n",barkod);
	printf("FÝYAT:%d",ilacfiyat);
}
 
 
    // Veritabaný dosyasýna ekleme
    FILE *dosya = fopen("ilac_veritabani.txt", "a");
 
    if (dosya == NULL) {
        printCentered("Dosya açma hatasý!\n");
        return 1;
    }
 
    fprintf(dosya, "ILAC ISMI: %s\n", ilac);
    fprintf(dosya, "ILAC BARKOD NUMARASI: %s\n\n", barkod);
    fprintf(dosya, "ILAC FIYATI: %d\n", ilacfiyat);
    fprintf(dosya, "-------------------------------------------------------\n");
 
    fclose(dosya);
    
    system("cls");
 
	}
	else if(secim==4){ // seçim 4'e eþit ise hastalarý listeleme tarafý devreye giricek.
	FILE *dosyaOku=
    fopen("hasta_bilgileri.txt", "r");
    
    if(dosyaOku==NULL){
        fprintf(stderr,"Dosya açma hatasý!\n");
        return 1;
    }
    
    char satir[100];
    int bosDosya = 1; // Dosyanýn boþ olup olmadýðýný kontrol etmek için bir bayrak
	if(fgets(satir, sizeof(satir), dosyaOku) != NULL){
        printCentered("\nHasta Bilgileri:\n");
    	printf("%s", satir);
		while(fgets(satir, sizeof(satir),dosyaOku)!=NULL){
        printf("%s", satir);
        }
	}else{
		printf("Dosya boþ.\n");
	}
        fclose(dosyaOku);
	}
	
	else if(secim==5){
	FILE *dosyaOku = fopen("ilac_veritabani.txt", "r");
    
	if(dosyaOku == NULL){
    	fprintf(stderr, "Dosya açma hatasý!\n");
    	return 1;
	}
 
	char satir[100];
	int bosDosya = 1; // Dosyanýn boþ olup olmadýðýný kontrol etmek için bir bayrak
	if(fgets(satir, sizeof(satir), dosyaOku) != NULL){
    	printCentered("\nÝlaç Bilgileri:\n");
    	printf("%s", satir);
    	while(fgets(satir, sizeof(satir),dosyaOku)!=NULL){
        printf("%s", satir);
        }
        
	}else{
		printf("Dosya boþ.\n");
	}
 
	fclose(dosyaOku);
 
	}
	
	else if(secim==6){
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("                                            RANDEVU LÝSTELE EKRANINA HOSGELDINIZ                                            \n");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
 	// 29 Mayýs 2024 baþlangýç tarihi
    struct tm startDate = createDate(2024, 5, 29);

    // Rastgele sayý üreticisini baþlat
    srand(time(NULL));

    // Doktorlar için rastgele tarih üret
    struct tm random_date_ahmet = generateRandomDate(startDate);
    struct tm random_date_bilal = generateRandomDate(startDate);
    struct tm random_date_serkan = generateRandomDate(startDate);
    struct tm random_date_charles = generateRandomDate(startDate);
    struct tm random_date_kendrick = generateRandomDate(startDate);

    // Sonuçlarý yazdýr
    printf("En Yakýn Randevu Tarihi:\n Doktor Ahmet için: %d-%02d-%02d\n",
           random_date_ahmet.tm_year + 1900,
           random_date_ahmet.tm_mon + 1,
           random_date_ahmet.tm_mday);

    printf("En Yakýn Randevu Tarihi:\n Doktor Bilal için: %d-%02d-%02d\n",
           random_date_bilal.tm_year + 1900,
           random_date_bilal.tm_mon + 1,
           random_date_bilal.tm_mday);

    printf("En Yakýn Randevu Tarihi:\n Doktor Serkan için: %d-%02d-%02d\n",
           random_date_serkan.tm_year + 1900,
           random_date_serkan.tm_mon + 1,
           random_date_serkan.tm_mday);

    printf("En Yakýn Randevu Tarihi:\n Doktor Charles için: %d-%02d-%02d\n",
           random_date_charles.tm_year + 1900,
           random_date_charles.tm_mon + 1,
           random_date_charles.tm_mday);

    printf("En Yakýn Randevu Tarihi:\n Doktor Kendrick Lamar için: %d-%02d-%02d\n",
           random_date_kendrick.tm_year + 1900,
           random_date_kendrick.tm_mon + 1,
           random_date_kendrick.tm_mday);
	}
	

	if (secim == 7) {
        printMedicationInfo();
    }
    
    if (secim == 8) {
    printf("--HAZIRLAYANLAR--\n\n");
    printf("--Yusuf Yiðit AYDIN\n");
    printf("--Ahmet Emin DOÐAN\n");
    printf("--Sarptuð KÖK\n");
    printf("--Merve KAYA\n");
    printf("--Muhammed YAMAN\n");
        
    }
	
    if(secim==0){
        printCentered("Programdan çýkýlýyor, bizi seçtiðiniz için teþekkürler...\n");
        return 0;
        break;
    }
      }
}
}
 
    return 0;
}
