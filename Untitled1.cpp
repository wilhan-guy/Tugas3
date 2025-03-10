#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct node{
    char data[100];
    struct node *next;
}*hashTable[100],*curr;


void pushBack(int hashKey, char data[])
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if(hashTable[hashKey] == NULL)
    {
        hashTable[hashKey] = newNode;
    }
    else
    {
        curr = hashTable[hashKey];
        while(curr->next != NULL)
            curr = curr->next;
        curr->next = newNode;
    }
}


int midSquareHash(char data[])
{
    int hashKey = 0, square, mid;

    for (int i = 0; i < strlen(data); i++) {
        hashKey += data[i];
    }

    square = hashKey * hashKey;
    mid = (square / 100) % 100; 

    return mid % 100;
}


int divisionHash(char data[])
{
    int hashKey = 0;

    for (int i = 0; i < strlen(data); i++) {
        hashKey += data[i];
    }

    return hashKey % 100; 
}


int foldingHash(char data[])
{
    int hashKey = 0, part = 0;

    for (int i = 0; i < strlen(data); i++) {
        part = data[i];
        hashKey += part;
    }

    return hashKey % 100;
}


int digitExtractionHash(char data[])
{
    int hashKey = 0;

    for (int i = 0; i < strlen(data); i++) {
        hashKey += data[i];
    }

    int extractedDigits = ((hashKey / 10) % 10) * 10 + ((hashKey / 1000) % 10);
    return extractedDigits % 100;
}


int rotationHash(char data[])
{
    int hashKey = 0;

    for (int i = 0; i < strlen(data); i++) {
        hashKey += data[i];
    }


    int rotatedHash = (hashKey << 1) | (hashKey >> (sizeof(int) * 8 - 1));
    return rotatedHash % 100;
}


void viewHashTable()
{
    for(int i = 0; i < 100; i++)
    {
        if(hashTable[i] != NULL)
        {
            printf("HASH TABLE INDEX [%d]:\n", i);
            curr = hashTable[i];

            while(curr != NULL)
            {
                printf("%s ", curr->data);
                curr = curr->next;
            }
            printf("\n\n");
        }
    }
}


void freeHashTable()
{
    for(int i = 0; i < 100; i++)
    {
        curr = hashTable[i];
        while(curr != NULL)
        {
            struct node *temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main()
{
    char data[100];
    int choice;

    for(int i = 0; i < 100; i++)
    {
        hashTable[i] = NULL;
    }

    do
    {
        printf("Pilih Metode Hash:\n");
        printf("1. Mid-Square\n");
        printf("2. Division\n");
        printf("3. Folding\n");
        printf("4. Digit Extraction\n");
        printf("5. Rotation\n");
        printf("6. Exit\n");
        printf("Pilihan Anda: ");
        scanf("%d", &choice); getchar();

        if(choice == 6) break;

        printf("Input Data: ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = '\0';

        int hashKey;
        switch(choice)
        {
            case 1: hashKey = midSquareHash(data); break;
            case 2: hashKey = divisionHash(data); break;
            case 3: hashKey = foldingHash(data); break;
            case 4: hashKey = digitExtractionHash(data); break;
            case 5: hashKey = rotationHash(data); break;
            default: printf("Metode tidak valid!\n"); continue;
        }

        pushBack(hashKey, data);
    } while(1);

    viewHashTable();
    freeHashTable();

    return 0;
}

