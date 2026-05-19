#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "ENGVIEdict.h"

int main() {
    SetConsoleOutputCP(437);
    Node* dictionary = NULL;
    HistoryNode* history = NULL;
    int choice;
    char english[100], vietnamese[200];
    const char* filename = "dictionary.txt";
    const char* historyFile = "history.txt";

    loadDictionaryFromFile(&dictionary, filename);
    sortDictionary(&dictionary);

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
        setColor(14); printf("\t6. "); setColor(7); printf("Liet ke tu theo chu cai dau\n");
        setColor(14); printf("\t7. "); setColor(7); printf("Xem lich su tra cuu\n");
        setColor(14); printf("\t8. "); setColor(7); printf("On tap tu vung (Mini Game)\n");
        setColor(12); printf("\t0. "); setColor(7); printf("Luu du lieu va Thoat\n");
        
        printf("\t-------------------------------\n");
        printf("\tLua chon cua ban(0-8): ");
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

                advancedWordSearch(dictionary, english);

                {
                    Node* found = dictionary;
                    int isFound = 0; // Cờ kiểm tra
                    char histResult[200];
                    
                    while (found != NULL) {
                        if (strcasecmp(found->word, english) == 0) {
                            strncpy(histResult, found->meaning, sizeof(histResult) - 1);
                            isFound = 1; // Đánh dấu là đã tìm thấy
                            break;
                        }
                        found = found->next;
                    }
                    
                    // CHỈ GỌI HÀM LƯU VÀO LỊCH SỬ KHI TÌM THẤY TỪ
                    if (isFound) {
                        saveSearchHistory(english, histResult, historyFile);
                    }
                }

                printf("\n\tBam phim bat ky de quay lai menu...");
                getch();
                break;

            case 2: 
                printf("\tNhap tu tieng Anh: ");
                fgets(english, sizeof(english), stdin);
                removeNewline(english);
                printf("\tNhap nghia tieng Viet: ");
                fgets(vietnamese, sizeof(vietnamese), stdin);
                removeNewline(vietnamese);
                addWord(&dictionary, english, vietnamese);
                sortDictionary(&dictionary);
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
                
                // Xóa từ khỏi bộ nhớ (Linked List)
                removeWord(&dictionary, english);
                
                // GỌI HÀM DỌN DẸP LỊCH SỬ NGAY SAU KHI XÓA TỪ
                cleanHistory(historyFile, dictionary); 
                
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;

            case 6:
                printf("\tNhap chu cai dau: ");
                char ch;
                scanf("%c", &ch);
                searchByFirstChar(dictionary, ch);
                printf("\n\tBam phim bat ky de quay lai menu...");
                getch(); 
                break;
            
            case 7:
                printHistory(historyFile, dictionary); 
                break;
            
            case 8:
                randomQuizFromHistory(historyFile);
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

    saveDictionaryToFile(dictionary, filename); 
    cleanHistory("history.txt", dictionary);
    freeMemory(&dictionary);

    return 0;
}
