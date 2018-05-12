#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
 
FILE *fileptr;

void main()
{
    printf("My name is Nikhil");

    fileptr = fopen("test2.txt", "w");
    if(fileptr == NULL)
    {
        printf("No file");
    }

    fputc('n', fileptr);
    fclose(fileptr);
    fileptr = NULL;

    fileptr = fopen("test2.txt", "a");
    int n =100;
    char * arrptr = (char *)malloc(sizeof(char) * n);
    char * s1 = (char *)malloc(sizeof(char) * n);
    
    printf("Enter a string:");
    scanf("%s", s1);
    
    fileptr = fopen("test2.txt", "w");
    if(fileptr == NULL)
    {
        printf("No file");    
    }
    fgets(s1, 100, fileptr);
    
    fflush(fileptr);

    fclose(fileptr);

    fileptr = NULL;

    fileptr = fopen("test2.txt", "r");
    
    char c = getc(fileptr);
    char * cptr = (char *)malloc(sizeof(char) * 10);

    char d[100];
    char * dptr = (char *)malloc(sizeof(char) * 10);
    dptr = fgets(cptr, 10, fileptr);

    fclose(fileptr);

    fileptr = NULL;
    
}
