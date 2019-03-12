#include"stdio.h"
#include"malloc.h"
#include"stdlib.h"
#include"string.h"

using namespace std;

struct List {
	char* employee;
	float salary;
	List* pList;
};

List* initialiseElement(char* buffer, float salary) {
	List* newElement = (List*)malloc(sizeof(List));
	newElement->employee = (char*)malloc(sizeof(buffer) + 1);
	strcpy(newElement->employee, buffer);
	newElement->salary = salary;
	newElement->pList = NULL;
	return newElement;
}

List* insertAtBeginning(List* head,List* newElement) {
	newElement->pList = head;
	return newEslement;
}

void insertToTail(List** head, List* newElement) {
	//test if first element exists
	if (*head == NULL) {
		*head = newElement;
	}

	List* index = *head;
	while (index->pList) {
		index = index->pList;
	}
	index->pList = newElement;
}


void main() {


	FILE* pFile = fopen("source.txt", "r");
	List* listHead = NULL;
	
	if (pFile) {
		char buffer[100]; float salary;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile)) {
			fscanf(pFile, "%d", &salary);
			//1.Create an element of type List
			List* newElement = initialiseElement(buffer, salary);
			//2.Insert the newly created element
			listHead = insertAtBeginning(listHead, newElement);

			fscanf(pFile, "%s", buffer);
		}
	}
}