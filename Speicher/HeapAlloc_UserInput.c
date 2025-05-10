#include <stdio.h>
#include <windows.h>

#define ANSI_RED        "\x1b[0;31m"
#define ANSI_GREEN      "\x1b[0;32m"
#define ANSI_PURLPLE    "\x1b[0;35m"

#define ANSI_RESET_ALL  "\x1b[0m"


int main(){

    char *UserInput = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 255);
    printf("Input: ");
    fgets(UserInput, 255, stdin);

    UserInput[strcspn(UserInput, "\n")] = 0;

    size_t ActLen = strlen(UserInput) + 1; //+1 wegen Nullterminator
    char *ShrkInput = HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, UserInput, ActLen);
    if(ShrkInput == NULL){

        printf(ANSI_RED"Speicherverkleinerung fehlgeschlagen %d" ANSI_RESET_ALL , GetLastError());
        HeapFree(GetProcessHeap(), 0, UserInput);

    } else {

        UserInput = ShrkInput;
        printf(ANSI_GREEN"Optimaler Speicher wird verwendet: " ANSI_RESET_ALL "%s" ANSI_GREEN "(Größe: %llu)\n" ANSI_RESET_ALL , UserInput, (unsigned long long)ActLen);
        printf("Speicheradresse: " ANSI_PURLPLE "%p\n" ANSI_RESET_ALL, UserInput);
        if (HeapFree(GetProcessHeap(), 0, UserInput) == 0){

            printf("Speicher freigabe fehlgeschlagen %d\n", GetLastError());

        } else {

            printf(ANSI_GREEN"Speicher erfolgreich freigeben\n"ANSI_RESET_ALL);
            UserInput = NULL; //Nur auf NULL setzen wenn nciht mehr gebraucht wird.
        }
    }

    return 0;
}

