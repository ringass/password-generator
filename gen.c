#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

const char *sybs = "[]{}()*#;/,-_%";
const char *nums = "1234567890";
const char *upL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char *dwL = "abcdefghijklmnopqrstuvwxyz";

void mix(char *str1, const char *e1, const char *e2){
    int lene1 = strlen(e1);
    int lene2 = strlen(e2);
    int lenstr = lene1 + lene2;

    for(int i = 0; i < lenstr; i++){
        if(i < lene1){
            str1[i] = e1[i];
        }else{
            str1[i] = e2[i - lene1];
        }
    }
    str1[lenstr] = '\0';
}



int main()
{   
    srand(time(NULL));

    int sizeAll = strlen(sybs) + strlen(nums) + strlen(upL) + strlen(dwL);
    int sizeUpNum = strlen(upL) + strlen(nums);
    int sizeLetters = strlen(upL) + strlen(dwL);

    char all[sizeAll + 1];
    char upNum[sizeUpNum + 1];
    char letters[sizeLetters + 1];
    
    mix(upNum, upL, nums);
    mix(letters, upL, dwL);

    mix(all, upL, dwL);
    mix(all + strlen(upL) + strlen(dwL), sybs, nums);

    int choose, passlength, i;

    printf("COMO DESEJA SUA SENHA?\n");
    printf("->0 - Completo (letras, numeros, simbolos)\n");
    printf("->1 - Letras maiusculas e numeros\n");
    printf("->2 - Somente letras\n");
    printf("->3 - Digitar minha propria senha\n");
    
    printf("ESCOLHA: ");
    scanf("%d", &choose);

    printf("TAMANHO: ");
    scanf("%d", &passlength);
    
    char *password = (char*)malloc((passlength + 1) * sizeof(char));

    switch(choose){
        case 0: {
            for(i = 0; i < passlength; i++){
                password[i] = all[rand() % strlen(all)];
            }
            break;
        }
        case 1: {
            for(i = 0; i < passlength; i++){
                password[i] = upNum[rand() % strlen(upNum)];
            }
            break;
        }
        case 2: {
            for(i = 0; i < passlength; i++){
                password[i] = letters[rand() % strlen(letters)];
            }
            break;
        }
        case 3: {
            printf("DIGITE SUA PRÓPRIA SENHA: ");
            scanf("%s", password);
            break;
        }
        default: {
            printf("Opção inválida.\n");
            free(password);
            return 1;
        }
    }

    password[passlength] = '\0';

    printf("SENHA GERADA: %s\n", password);


    FILE *file = fopen("decrypted.txt", "a");

    if(file == NULL){
        printf("Erro ao salvar senha cryptografada");
        free(password);
        exit(1);
    }

    fprintf(file, "%s\n", password);

    free(password);
    fclose(file);

    return 0;
}
