#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h"
using namespace std;
struct DLL
{
	int id;
	char* profession;
	float salary;
	DLL* pNext;
};



struct HashTable {
	DLL** accessTable;
	int size;
};



DLL* createElement(int, char*, float);					///WE PASS BY ADDRESS ONLY WHEN WE NEED TO CHANGE THE HEAD OF A DATA STRUCTURE
void initHashTable(HashTable*, int);
void insertHashTable(HashTable, DLL*);
int fhash(int, int);
void printList(int, DLL**);

void main()
{
	FILE* pFile = fopen("Data.txt", "r");

	HashTable hashTable;
	//init hashTable
	initHashTable(&hashTable, 31);

	if (pFile)
	{
		char buffer[100]; float salary; int id;
		fscanf(pFile, "%d", &id);
		while (!feof(pFile))
		{
			fscanf(pFile, "%s", buffer);
			fscanf(pFile, "%d", &salary);

			//1. create an element of type List*
			DLL* newElement = createElement(id, buffer, salary);

			//2. insert the newly created element
			insertHashTable(hashTable, newElement);
			//insertToTail(&listHead, newElement);
			fscanf(pFile, "%d", &id);
		}
		fclose(pFile);
	}

	for (int i = 0; i < hashTable.size; i++) {
		printList(i, hashTable.accessTable);
	}
}


void printList(int index, DLL** accessTable) {
	DLL* list = accessTable[index];
	if (list == NULL) {
		printf("Index: %d NULL \n", index);
	}
	else {
		printf("Index: %d ", index);
			while (list) {
				printf("%s; ", list->profession);
				list = list->pNext;
			}
			printf("\n");
	}
}

int fhash(int key, int size) {
	return key % size;
}


void insertHashTable(HashTable hashTable, DLL* element) {
	int index = fhash(element->id, hashTable.size);
	if (hashTable.accessTable != NULL) {
		DLL* indexElement = hashTable.accessTable[index];
		if (indexElement == NULL) {
			hashTable.accessTable[index] = element;
		}
		else {
			while (indexElement->pNext) {
				indexElement = indexElement->pNext;
			}
			indexElement->pNext = element;
		}
	}
}

void initHashTable(HashTable* hashTable, int size) {
	hashTable->size = size;
	hashTable->accessTable = (DLL**)malloc(sizeof(DLL*)*size);
	memset(hashTable->accessTable, NULL, sizeof(DLL*)*size);
}



DLL* createElement(int id, char* buffer, float salary)
{
	//1.allocate memory for the new element
	DLL* newElement = (DLL*)malloc(sizeof(DLL));
	//2.initialize it with the params 
	//(the connection attributes should remain NULL)
	newElement->pNext = NULL;
	newElement->id = id;
	newElement->salary = salary;
	newElement->profession = (char*)malloc(strlen(buffer) + 1);
	strcpy(newElement->profession, buffer);
	//3.return the new element
	return newElement;
}

