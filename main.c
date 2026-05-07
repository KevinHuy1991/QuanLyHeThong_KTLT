#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ENGVIEdict.h"

int main() {
    Node* dictionary = NULL;
    int choice;
    char english[100], vietnamese[200];
    const char* filename = "dictionary.txt";

    loadDictionaryFromFile(&dictionary, filename);

    clearScreen();
    setColor(11);
    slowPrint("\n\t[SYSTEM] Dang khoi tao tu dien Anh - Viet...\n", 20);
    slowPrint("\t[SYSTEM] San sang!\n", 20);
    Sleep(500);

    do {
        clearScreen();
        boxHeader("TU DIEN ANH - VIET");
        
        setColor(14); printf("\t1. "); setColor(7); printf("Tra cuu tu vung\n");
        setColor(14); printf("\t2. "); setColor(7); printf("Them tu moi \n");
        setColor(14); printf("\t3. "); setColor(7); printf("In toan bo tu dien\n");
        setColor(14); printf("\t4. "); setColor(7); printf("Thay doi nghia cua tu\n");
        setColor(14); printf("\t5. "); setColor(7); printf("Xoa tu khoi he thong\n");
        setColor(12); printf("\t0. "); setColor(7); printf("Luu du lieu va Thoat\n");
        
        printf("\t-------------------------------\n");
        printf("\tLua chon cua ban(0-5): ");
        if (scanf("%d", &choice) != 1) {
            choice = -1;
            while(getchar() != '\n');
        }
        getchar(); 

        switch (choice) {
            case 1: 
                printf("\tNhap tu tieng Anh can tim: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                wordSearch(dictionary, english);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); // Dung man hinh doi nguoi dung bam phim 
                break;

            case 2: 
                printf("\tNhap tu tieng Anh: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                printf("\tNhap nghia tieng Viet: ");
                fgets(vietnamese, sizeof(vietnamese), stdin);
                removeNewline(vietnamese);
                addWord(&dictionary, english, vietnamese);
                setColor(10); printf("\t=> Da them tu moi thanh cong!\n");
                setColor(7); 
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 3: 
                dictionaryPrinting(dictionary);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 4: 
                printf("\tNhap tu tieng Anh can sua: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                printf("\tNhap nghia tieng Viet moi: ");
                fgets(vietnamese, sizeof(vietnamese), stdin);
                removeNewline(vietnamese);
                updateMeaning(dictionary, english, vietnamese);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 5: 
                printf("\tNhap tu tieng Anh can xoa: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                removeWord(&dictionary, english);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 0: 
                setColor(11);
                slowPrint("\n\tDang luu file... \n", 30);
                setColor(7);
                break;

            default:
                setColor(12);
                printf("\tLua chon khong hop le. Vui long nhap lai!\n");
                setColor(7); getch();
        }
    } while (choice != 0);

    saveDictionaryToFile(dictionary, filename); // lu l?i khi thot
    freeMemory(&dictionary);

    return 0;
}
