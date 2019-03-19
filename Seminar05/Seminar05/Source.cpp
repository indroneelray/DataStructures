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
void insertToTail(DLL**, DLL*);
//void insertToTail(List*&, List*);
void printList(DLL*);
void insertAfter(const char*, DLL*, DLL*);


void main()
{
	FILE* pFile = fopen("Data.txt", "r");

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
			insertToTail(&listHead, newElement);
			fscanf(pFile, "%s", buffer);
		}
		fclose(pFile);
		printList(listHead);
	}

	DLL* node = createElement("Attorney", 1400.9);
	insertAfter("Judecator", listHead, node);
	printList(listHead);


}




void insertToTail(DLL** head, DLL* newElemenet)
{
	//test if the first element exists
	if (*head == NULL)
	{
		*head = newElemenet;
	}
	else
	{
		DLL* index = *head;
		while (index->pNext)
			index = index->pNext;
		//1. Connect node to struture
		newElemenet->pPrev = index;
		//2. Connect structure to node
		index->pNext = newElemenet;
	}

}



DLL* insertToHead(DLL* head, DLL* newElement)
{
	newElement->pNext = head;
	if (head) {
		head->pPrev = newElement;
	}
	return newElement;
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

void printList(DLL* head) {
	if (head)
		do {
			printf("Profession: %s, salary: %f \n", head->profession, head->salary);
			head = head->pNext;

		} while (head->pNext);
		printf("Profession: %s, salary: %f \n", head->profession, head->salary);
		printf("\n End of traversal from head");

		for (head; head != NULL; head = head->pPrev) {
			printf("\n Profession: %s, salary: %f ", head->profession, head->salary);
		}


		//for(DLL* index=head;index!=NULL;index->pPrev)[if we wanted to use an index method]
	

		//for (DLL* index = head; index != NULL; index = index->pPrev) {
		//	printf("\n Profession: %s, salary: %f ", index->profession, index->salary);
		//}

}

void insertAfter(const char* buffer, DLL* head, DLL* node) {
	while (head && strcmp(buffer, head->profession) != 0) 
		head = head->pNext;

		if (head) {
			node->pNext = head->pNext;
			node->pPrev = head;
			head->pNext = node;
			node->pNext->pPrev = node;
			
		}
	
}