#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

int verifyVogal(char str){
    if(tolower(str) == 'a' || tolower(str) == 'e' || tolower(str) == 'i' || tolower(str) == 'o' || tolower(str) == 'u'){
        return 1;
    }else{
        return 0;
    }
}

void caeserModified(char *str, int key)
{

    int len = strlen(str);

    char offset;

    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            offset = islower(str[i]) ? 'a' : 'A';

            str[i] = ((str[i] - offset + key) % 26) + offset;
        }
        else
        {
            str[i] = str[i] + 10 - key;
        }
    }
    
    for (int i = 0; i < len; i++)
    {
        if (i % 2 == 0 || (isalpha(str[i]) && verifyVogal(str[i])))
        {
            str[i] = str[i] + key;
        }
    }

    printf("\n%s", str);
}

void decryptCaeser(char *str, int key)
{

    int len = strlen(str);

    char offset;

    for (int i = 0; i < len; i++)
    {
        if (isalpha(str[i]))
        {
            offset = islower(str[i]) ? 'a' : 'A';

            str[i] = ((str[i] - offset - key + 26) % 26) + offset;
        }
        else
        {
            str[i] = str[i] - 10 + key;
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (i % 2 == 0 || verifyVogal(str[i] - key))
        {
            str[i] = str[i] - key;
        }
    }

    printf("\n%s", str);
}

int main()
{

    int key;

    printf("Digite a key: ");
    scanf("%d", &key);

    FILE *file = fopen("decrypted.txt", "r");
    FILE *file2 = fopen("encrypted.txt", "a");

    char pass[200];
    int i = 0;

    fprintf(file2, "\n");
    while (fscanf(file, "%s", pass) == 1)
    {
        if (i > 1)
        {
            caeserModified(pass, key);
            fprintf(file2, "%s\n", pass);
        }
    i++;
    }

    fclose(file);
    fclose(file2);

    return 0;
}