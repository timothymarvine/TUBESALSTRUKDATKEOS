#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "boolean.h"
#include "wordl399.h"
#include "ADT\mesinkata\mesinkata.h"  
#include "ADT\mesinkarakter\mesinkarakter.h"


#define BIAYA_PERMAINAN 500
#define HADIAH 1500
#define PANJANG_KATA 5
#define MAX_PELUANG 6


const char *daftar_kata[] = {"STEIK", "CISCO", "JAKET", "HUJAN", "LUCKY","INGIN","MAKAN"};
const int ukuran_daftar_kata = 5;


int string_length(const char *str){
    int length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}



void pilih_kata_acak(char *kata_terpilih) {
    srand(time(NULL)); 
    int indeks = rand() % ukuran_daftar_kata;
    for (int i = 0; i < PANJANG_KATA; i++) {
        kata_terpilih[i] = daftar_kata[indeks][i];
    }
    kata_terpilih[PANJANG_KATA] = '\0'; 
}


void proses_tebakan(const char *tebakan, const char *target, char *hasil) {
    bool sudah_digunakan[PANJANG_KATA] = {false};  

    
    for (int i = 0; i < PANJANG_KATA; i++) {
        if (tebakan[i] == target[i]) {
            hasil[i * 2] = tebakan[i]; // Huruf yang benar
            hasil[i * 2 + 1] = ' ';
            sudah_digunakan[i] = true;
        }
    }

    
    for (int i = 0; i < PANJANG_KATA; i++) {
        if (tebakan[i] != target[i]) {
            bool ditemukan = false;
            for (int j = 0; j < PANJANG_KATA; j++) {
                if (!sudah_digunakan[j] && tebakan[i] == target[j]) {
                    hasil[i * 2] = tebakan[i];
                    hasil[i * 2 + 1] = '*';  // Huruf benar tapi posisinya salah
                    sudah_digunakan[j] = true;
                    ditemukan = true;
                    break;
                }
            }
            if (!ditemukan) {
                hasil[i * 2] = tebakan[i];
                hasil[i * 2 + 1] = '%';  // Huruf tidak ada dalam kata
            }
        }
    }

    hasil[PANJANG_KATA * 2] = '\0';  // Menambahkan null terminator
}


int bandingkan_string(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


void tampilkan_progress(char tebakan[MAX_PELUANG][PANJANG_KATA * 2 + 1], int peluang) {
    for (int i = 0; i < MAX_PELUANG; i++) {
        if (i < peluang) {
            printf("%s\n", tebakan[i]);
        } else {
            for (int j = 0; j < PANJANG_KATA; j++) {
                printf("_ ");  
            }
            printf("\n");
        }
    }
    printf("\n");
}


void WORDL399(int *uang_asal) {
    if (*uang_asal < BIAYA_PERMAINAN) {
        printf("Uang Anda tidak cukup untuk memainkan W0RDL399.\n");
        return;
    }

    *uang_asal -= BIAYA_PERMAINAN;  
    printf("Uang Anda tersisa %d.\n\n", *uang_asal);
    printf("\nSELAMAT DATANG DI W0RDL3, ANDA MEMILIKI %d PELUANG UNTUK MENEBAK KATA!\n\n", MAX_PELUANG);

    char kata_target[PANJANG_KATA + 1];
    pilih_kata_acak(kata_target);  // Memilih kata acak

    char tebakan[MAX_PELUANG][PANJANG_KATA * 2 + 1] = {0};  
    char tebakan_input[PANJANG_KATA + 1];
    int peluang = 0;
    bool tebakan_benar = false;
    char temp[PANJANG_KATA+1];
    while (peluang < MAX_PELUANG && !tebakan_benar) {
        tampilkan_progress(tebakan, peluang + 1); 

        
        printf("Masukkan kata tebakan Anda: ");
        
        STARTWORD();  
        WordToString(currentWord,temp);

        
        for (int i = 0; i < PANJANG_KATA; i++) {
            tebakan_input[i] = currentWord.TabWord[i];
        }
        tebakan_input[PANJANG_KATA] = '\0'; 
        
        if (string_length(tebakan_input) != PANJANG_KATA) {
            printf("Kata harus terdiri dari %d huruf. Coba lagi.\n", PANJANG_KATA);
            continue;
        }

        
        proses_tebakan(tebakan_input, kata_target, tebakan[peluang]);
        printf("Hasil:\n");
        tampilkan_progress(tebakan, peluang + 1);

        
        if (bandingkan_string(tebakan_input, kata_target) == 0) {
            tebakan_benar = true;
            printf("Selamat, Anda menang!\n");
            printf("+%d rupiah telah ditambahkan ke akun Anda.\n", HADIAH);
            *uang_asal += HADIAH;  // Memberikan hadiah
            printf("Uang Anda sekarang: %d\n", *uang_asal);
            return;
        }

        peluang++;
    }

    // Jika pemain tidak berhasil menebak dalam percobaan terbatas
    printf("Maaf, Anda kalah! Kata yang benar adalah: %s\n", kata_target);
    printf("Uang Anda tersisa: %d\n", *uang_asal);
}

