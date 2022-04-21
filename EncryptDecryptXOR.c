/*
 * ZENON MATYCHAK LAB3 FILE POINTERS
 * 2/18/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* fileRead(unsigned long *size, char *file_name);
int fileWrite(unsigned long size, char *output, char *file_name);
char* make_rand_key(int lengthOfKey, char *key);
void encrypt(char *clear_file, char *key_file, char *cipher_file);
void decrypt(char *key_file, char *cipher_file, char *answer);


int main(int argc, char *atgv[])
{
    srand(time(NULL));
    char *contents = NULL;
    char ans[64];
    int choice=0;
    char clearFile[] = "clear_file.txt";
    char keyFile[] = "key_file.txt";
    char cipherFile[] = "cipher_file.txt";
    char answerFile[] = "answer.txt";
    while(1)
    {
        printf("\n\n");
        printf("Encrypt a file:  1 \n"
                      "Decrypt a file:  2 \n"
                      "Exit:    3 \n"
                      "Enter a Choice:");
        scanf("%s", &ans);
        choice=atoi(ans);
        printf("Your Choice was: %d\n",choice);
        if(choice==1)
        {
            encrypt(clearFile, keyFile, cipherFile);
            puts("encrypting file.....");
        }
        else if(choice==2)
        {
            decrypt(keyFile, cipherFile, answerFile);
            puts("DEcrypting file.....");
        }
        else
            break;

        //encrypt(clearFile, keyFile, cipherFile);
        //decrypt(keyFile, cipherFile, answerFile);
    }
    puts("goodbye");
    free(contents);
    return 0;
}

char* fileRead(unsigned long *size, char *file_name)
{
    FILE *fileread;
    fileread=fopen(file_name,"r");
    if(fileread == NULL)
    {
        fprintf(stderr, "File %s not opened!\n", *file_name);
        exit(1);
    }

    fseek(fileread, 0, SEEK_END);
    *size = (unsigned long) ftell(fileread);
    rewind(fileread);
   // printf("READ SIZE: %d\n ",&size);

    char *char_arr = (char*) malloc(sizeof(char) * 256);
    fread(char_arr, *size, sizeof(char), fileread);

    fclose(fileread);
    return char_arr;
}

int fileWrite(unsigned long size, char *output, char *file_name)
{

    FILE *filewrite;
    filewrite=fopen(file_name,"w");
    if(filewrite == NULL)
    {
        fprintf(stderr, "File %s not opened!\n", *file_name);
        exit(2);
    }

    fwrite(output , sizeof(char) , size , filewrite);
    fclose(filewrite);
    return 1;
}

char* make_rand_key(int lengthOfKey,char *key)
{
    for(int i=0;i<lengthOfKey;i++)
    {
        char random = 33 + (rand() % 93);
        key[i]=random;
    }
    return key;
}

void encrypt(char *clear_file, char *key_file, char *cipher_file)
{
    unsigned long len=256;
    char *clear;
    char randomKey2[8];
    char result[8];
    clear=fileRead(&len,clear_file);
    //printf("%s",clear);
    make_rand_key(8,randomKey2);
    printf("Random key: %s\n",randomKey2);
    for(int i=0;i<8;i++)
    {
        result[i]=clear[i]^randomKey2[i];
        //printf("%c",result[i]);
    }
    fileWrite(8, randomKey2, key_file);
    fileWrite(8, result, cipher_file);
}

void decrypt(char *key_file, char *cipher_file, char *answer)
{
    unsigned long len=256;
    char *cipher;
    char *randomKey3;
    cipher=fileRead(&len,cipher_file);
    randomKey3=fileRead(&len,key_file);
    char result[8];
    for(int i=0;i<8;i++)
    {
        result[i]=cipher[i]^randomKey3[i];
    }
    fileWrite(8, result, answer);
}