#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h"

using namespace std;
struct DLL
{
	char* profession;
	float salary;
	DLL* pNext;
	DLL* pPrev;
};

DLL* createElement(const char*, float);
DLL* insertToHead(DLL*, DLL*);
//void insertToTail(DLL**, DLL*);
////void insertToTail(List*&, List*);
//void afisareLista(DLL*);
//void insertMiddle(const char*, DLL*, DLL*);


void printQueue(DLL*);
void putQueue(DLL*&, DLL*);
char* getQueue(DLL**); //passed by pointer single* equals reference
void main()
{
	FILE* pFile = fopen("Text.txt", "r");

	DLL* listHead = NULL;

	if (pFile)
	{
		char buffer[100]; float salary;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			fscanf(pFile, "%f", &salary);

			//1. create an element of type List*
			DLL* newElement = createElement(buffer, salary);

			//2. insert the newly created element
			//listHead = insertToHead(listHead, newElement);
			//insertToTail(&listHead, newElement);
			putQueue(listHead, newElement);
			fscanf(pFile, "%s", buffer);
		}
		fclose(pFile);
		printQueue(listHead);
		printf("\n-----------------------------------------------\n");

		//afisareLista(listHead);
		DLL* node = createElement("Avocat", 1300);
		putQueue(listHead, node);
		printQueue(listHead);

		//insertMiddle("Judecator", listHead, node);
		printf("----------------------------\n");
		char* result = NULL;
		while ((result = getQueue(&listHead))!= NULL) {
			printf("\n Returned value: %s \n", result);
		}


		getQueue(&listHead);
		//afisareLista(listHead);
	}
}

char* getQueue(DLL** head) {
	 
	char* result = NULL;
	if (*head != NULL)
	{
		//1. Save the return info
		result = (*head)->profession;
		//2. Save the temporary node
		DLL*tmp = *head;
		//3. Reconnect the structure
		(*head)->pNext->pPrev = (*head)->pPrev;
		(*head)->pPrev->pNext = (*head)->pNext;
		*head = tmp->pNext;
		//4. free temp
		free(tmp);
	}
	//5. return info
	return result;
	
	
	




}


void putQueue(DLL*& head, DLL* node) {
	if (head == NULL) {
		node->pNext = node->pPrev = node;
		head = node;
	}

	else {
		node->pNext = head;
		node->pPrev = head->pPrev;
		head->pPrev->pNext = node;
		head->pPrev = node;
	  }
}

DLL* createElement(const char* buffer, float salary)
{
	//1.allocate memory for the new element
	DLL* newElement = (DLL*)malloc(sizeof(DLL));
	//2.initialize it with the params 
	//(the connection attributes should remain NULL)
	newElement->pNext = NULL;
	newElement->pPrev = NULL;
	newElement->salary = salary;
	newElement->profession = (char*)malloc(strlen(buffer) + 1);
	strcpy(newElement->profession, buffer);
	//3.return the new element
	return newElement;
}


void printQueue(DLL* head) {
	DLL* index = head;
	do {
		printf("Proffesion: %s, Salary: %f  \n", index->profession, index->salary);
		index = index->pNext;
	} while (index != head);
}

//void afisareLista(DLL* head)
//{
//	if (head)
//		do
//		{
//			printf("Profesie: %s, salariu: %f \n",
//				head->profession, head->salary);
//			head = head->pNext;
//		} while (head->pNext);
//		printf("Profesie: %s, salariu: %f \n",
//			head->profession, head->salary);
//		printf("---------------------------------------\n");
//		for (DLL* index = head; index; index = index->pPrev)
//		{
//			printf("Profesie: %s, salariu: %f \n",
//				index->profession, index->salary);
//		}
//
//}

//void insertMiddle(const char* cond, DLL* head, DLL* node)
//{
//	while (head && strcmp(cond, head->profession) != 0)
//		head = head->pNext;
//	if (head)
//	{
//		//1.legare nod de structura
//		node->pNext = head->pNext;
//		node->pPrev = head;
//		//2.legare structura de 
//		if (head->pNext)
//			head->pNext->pPrev = node;
//		head->pNext = node;
//	}
//}