#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ENGVIEdict.h"

int main() {
    Node* dictionary = NULL;
    int choice;
    char english[100], vietnamese[200];
    const char* filename = "dictionary.txt";

    loadDictionaryFromFile(&dictionary, filename);

    do {
        printf("\n===== TU DIEN ANH - VIET =====\n");
        printf("1. Tim kiem tu\n");
        printf("2. Them tu moi\n");
        printf("3. In toan bo tu dien\n");
        printf("4. Thay doi nghia tu\n");
        printf("5. Xoa tu\n");
        printf("0. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1: 
                printf("Nhap tu tieng Anh can tim: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                wordSearch(dictionary, english);
                break;

            case 2: 
                printf("Nhap tu tieng Anh: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);

                printf("Nhap nghia tieng Viet: ");
                fgets(vietnamese, sizeof(vietnamese), stdin);
                removeNewline(vietnamese);

                addWord(&dictionary, english, vietnamese);
                printf("=> Da them tu moi!\n");
                break;

            case 3: 
                dictionaryPrinting(dictionary);
                break;

            case 4: 
                printf("Nhap tu tieng Anh can sua: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);

                printf("Nhap nghia tieng Viet moi: ");
                fgets(vietnamese, sizeof(vietnamese), stdin);
                removeNewline(vietnamese);

                updateMeaning(dictionary, english, vietnamese);
                break;

            case 5: 
                printf("Nhap tu tieng Anh can xoa: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);

                removeWord(&dictionary, english);
                break;

            case 0: 
                printf("Dang thoat chuong trinh...\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long nhap lai!\n");
        }
    } while (choice != 0);

    saveDictionaryToFile(dictionary, filename); // l�u l?i khi tho�t
    freeMemory(&dictionary);

    return 0;
}

