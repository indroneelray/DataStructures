#include "stdio.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h"
using namespace std;



struct HeapItem
{
	char* profession;
	float salary;
};

struct BT {
	HeapItem* info;
	BT* left;
	BT* right;
};

struct Heap
{
	HeapItem** items;
	//the maximum capacity of the structure
	int size;
	//the current no. of elements
	int noItems;
};

BT* createElement(HeapItem* info) {
	BT* node = (BT*)malloc(sizeof(BT));
	node->left = NULL;
	node->right = NULL;
	node->info = info;
	return node;
}

HeapItem* createElement(char*, float);
void initHeap(Heap*, int);
void enqueueHeap(Heap&, HeapItem*);
void reheapDown(Heap, int);
HeapItem* dequeueHeap(Heap&);



//INORDER - Left, Root, Right
//Preorder - Root, Left, Right
//PostOrder - Left, Right, Root
void preOrder(BT*);
void postOrder(BT*);
void inOrder(BT*);
BT* createElement(HeapItem*);
void insertNode(BT*&, BT*);//root, node

void main()
{
	FILE* pFile = fopen("Data.txt", "r");
	Heap maxHeap;
	BT* root = NULL;
	BT* treeFromHeapRoot = NULL;
	initHeap(&maxHeap, 10);
	if (pFile)
	{
		char buffer[100]; float salary;
		fscanf(pFile, "%s", buffer);
		while (!feof(pFile))
		{
			fscanf(pFile, "%f", &salary);
			//1. create an element of type List*
			HeapItem* newElement = createElement(buffer, salary);
			//2. Create BTnode
			BT* node = createElement(newElement);
			//3. insert the newly created element
			//enqueueHeap(maxHeap, newElement);
			insertNode(root, node);

			fscanf(pFile, "%s", buffer);
		}
		fclose(pFile);
	}
	for (int i = 0; i < maxHeap.noItems; i++)
	{
		printf("Index: %d, salary: %f\n",
			i, maxHeap.items[i]->salary);
	}


	printf("\n=========INORDER=========");
	inOrder(root);
	printf("\n=========PREORDER=========");
	preOrder(root);
	printf("\n=========POSTORDER=========");
	postOrder(root);

	HeapItem* result = NULL;
	while ((result = dequeueHeap(maxHeap))!=NULL) {
		BT* node = createElement(result);
		insertNode(root, node);
	}
	printf("\n=========INORDER=========");
	inOrder(root);
	printf("\n=========PREORDER=========");
	preOrder(root);
	printf("\n=========POSTORDER=========");
	postOrder(root);
}
void ReheapDown(Heap heap, int front)
{
	int leftIndex = front * 2 + 1;
	int rightIndex = front * 2 + 2;
	int maxIndex;
	HeapItem* max = NULL;
	HeapItem* parent = heap.items[front];
	if (leftIndex <= heap.noItems - 1)
	{
		if (leftIndex == heap.noItems - 1)
			max = heap.items[leftIndex];
		else
		{
			if (heap.items[leftIndex]->salary >
				heap.items[rightIndex]->salary)
			{
				max = heap.items[leftIndex];
				maxIndex = leftIndex;
			}
			else
			{
				max = heap.items[rightIndex];
				maxIndex = rightIndex;
			}
		}
		if (max->salary > heap.items[front]->salary)
		{
			heap.items[front] = max;
			heap.items[rightIndex] = parent;
			ReheapDown(heap, maxIndex);
		}
	}
}
HeapItem* dequeueHeap(Heap& heap)
{
	HeapItem* result = NULL;
	if (heap.noItems > 0)
	{
		result = heap.items[0];
		heap.items[0] = heap.items[heap.noItems - 1];
		heap.noItems--;
		ReheapDown(heap, 0);
	}
	return result;
}

void ReheapUp(Heap heap, int back)
{
	if (back != 0)
	{
		int parentIndex = (back - 1) / 2;
		HeapItem* parent = heap.items[parentIndex];
		HeapItem* last = heap.items[back];
		if (parent->salary < last->salary)
		{
			heap.items[back] = parent;
			heap.items[parentIndex] = last;
			ReheapUp(heap, parentIndex);
		}
	}
}

void insertNode(BT*&root, BT* node) {
	//refers to step n
	if (root == NULL) {
		root = node;
	}

	//refers to step n - 1
	else {
		if (root->left != NULL) {
			if (root->right == NULL) {
				insertNode(root->right, node);
			}
			else {
				insertNode(root->left, node);
			}
		}
		else {
			insertNode(root->left, node);

		}
	}

}

void inOrder(BT* root) {
	if (root) {
		inOrder(root->left);
		printf("Salary: %f\n", root->info->salary);
		inOrder(root->right);
	}
}

void preOrder(BT* root) {
	if (root) {
		printf("Salary: %f\n", root->info->salary);
		preOrder(root->right);
		preOrder(root->left);
	}
}

void postOrder(BT* root) {
	if (root) {
		postOrder(root->left);
		postOrder(root->right);
		printf("Salary: %f\n", root->info->salary);
		
	}
}



void enqueueHeap(Heap& maxHeap, HeapItem* item)
{
	if (maxHeap.noItems < maxHeap.size)
	{
		maxHeap.items[maxHeap.noItems] = item;
		maxHeap.noItems++;
		ReheapUp(maxHeap, maxHeap.noItems - 1);
	}
}

void initHeap(Heap* maxHeap, int size)
{
	maxHeap->size = size;
	maxHeap->noItems = 0;
	maxHeap->items = (HeapItem**)malloc(sizeof(HeapItem*)*size);
	memset(maxHeap->items, NULL, sizeof(HeapItem*)*size);
}

HeapItem* createElement(char* buffer, float salary)
{
	//1.allocate memory for the new element
	HeapItem* newElement = (HeapItem*)malloc(sizeof(HeapItem));
	//2.initialize it with the params 
	//(the connection attributes should remain NULL)
	newElement->salary = salary;
	newElement->profession = (char*)malloc(strlen(buffer) + 1);
	strcpy(newElement->profession, buffer);
	//3.return the new element
	return newElement;
}

