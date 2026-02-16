#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "MagicFactory.h"
#include "FactoryFile.h"
#include "General.h"
#include "FileHelper.h"
#include "Macros.h"
int	initFactory(MagicFactory* pFactory)
{
	if (!L_init(&pFactory->broomList))
		return 0;
	if (!L_init(&pFactory->wandList))
		return 0;
	return 1;
}



int		addWand(MagicFactory* pFactory)
{
	PRINT(All the wand in the factory:);
	printWands(pFactory);
	Wand* pWand = (Wand*)calloc(1, sizeof(Wand));
	if (!pWand)
		return 0;
	initWand(pWand, pFactory);
	return insertNewWandToList(&pFactory->wandList, pWand);
}

void 	initWand(Wand* pWand, MagicFactory* pFactory)
{
	//printWands(pFactory);
	while (1)
	{
		getWandCode(pWand->code);
		if (checkWandUniqueCode(pWand->code, pFactory))
			break;

		printf("This code already in use - enter a different code\n");
	}

	pWand->mfgYear = getWandMFGYear();
}
Wand* chooseWandFromList(MagicFactory* pFactory, const char* msg)
{
	printWands(pFactory);
	char code[MAX_STR_LEN];
	Wand* wand;
	do
	{
		printf("%s\t", msg);
		getWandCode(code);
		wand = findWandByCode(pFactory, code);
		if (wand == NULL)
			printf("No wand with this code - try again\n");
	} while (wand == NULL);

	///every wizard have a unique wand
	//removeWand(pFactory, wand);
	////////////


	return wand;
}


int		insertNewWandToList(LIST* pProductList, Wand* pWand)
{
	NODE* pN = pProductList->head.next; //first Node
	NODE* pPrevNode = &pProductList->head;
	Wand* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Wand*)pN->key;
		compRes = strcmp(pTemp->code, pWand->code);
		if (compRes == 0) //found a product with this name is cart
		{
			printf("Not new wand - error!!!\n");
			return 0;
		}

		if (compRes > 0) //found a place for new item, the next one bigger
		{
			if (!L_insert(pPrevNode, pWand))
				return 0;
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	//insert at end
	if (!L_insert(pPrevNode, pWand))
		return 0;
	return 1;
}
Wand* findWandByCode(const MagicFactory* pFactory, const char* code)
{
	NODE* pN = pFactory->wandList.head.next; //first Node
	if (!pN)
		return NULL;

	Wand* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Wand*)pN->key;
		compRes = strcmp(pTemp->code, code);
		if (compRes == 0)
			return pTemp;
		if (compRes > 1) //not fount
			return NULL;
		pN = pN->next;
	}

	return NULL;
}
int		checkWandUniqueCode(const char* code, const MagicFactory* pFactory)
{
	Wand* wand = findWandByCode(pFactory, code);

	if (wand != NULL)
		return 0;

	return 1;
}



void    removeWand(MagicFactory* pFactory, Wand* wand)
{
	const NODE* pNode = L_find(pFactory->broomList.head.next, wand->code, compareWandByCode);
	L_Change_Pointer(&pFactory->broomList, pNode);

}
int		getWandCount(const MagicFactory* pFactory)
{
	int count = 0;
	NODE* pN = pFactory->wandList.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}
int		addBroom(MagicFactory* pFactory)
{
	Broom* pBroom = (Broom*)calloc(1, sizeof(Broom));
	if (!pBroom)
		return 0;
	if(!initBroom(pBroom, pFactory))
		return 0;
	
	return insertNewBroomToList(&pFactory->broomList, pBroom);
}
int	initBroom(Broom* pBroom, MagicFactory* pFactory)
{
	printBrooms(pFactory);
	while (1)
	{
		getBroomCode(pBroom->code);
		if (checkBroomUniqueCode(pBroom->code, pFactory))
			break;

		printf("This code already in use - enter a different code\n");
	}
	pBroom->nickName = getStrExactName("Enter Broom nick name");
	if (!pBroom->nickName)
		return 0;
	
	pBroom->speed = getBroomSpeed();
	pBroom->numOfRaces = 0;
	
	return 1;
}
int		insertNewBroomToList(LIST* pProductList, Broom* pBroom)
{
	NODE* pN = pProductList->head.next; //first Node
	NODE* pPrevNode = &pProductList->head;
	Broom* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Broom*)pN->key;
		compRes = strcmp(pTemp->code, pBroom->code);
		if (compRes == 0) //found a product with this name is cart
		{
			printf("Not new broom - error!!!\n");
			return 0;
		}

		if (compRes > 0) //found a place for new item, the next one bigger
		{
			if (!L_insert(pPrevNode, pBroom))
				return 0;
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	//insert at end
	if (!L_insert(pPrevNode, pBroom))
		return 0;
	return 1;
}
Broom* findBroomByCode(const MagicFactory* pFactory, const char* code)
{
	NODE* pN = pFactory->broomList.head.next; //first Node
	if (!pN)
		return NULL;

	Broom* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Broom*)pN->key;
		compRes = strcmp(pTemp->code, code);
		if (compRes == 0)
			return pTemp;
		if (compRes > 1) //not fount
			return NULL;
		pN = pN->next;
	}
	return NULL;
}
int		getBroomCount(const MagicFactory* pFactory)
{
	int count = 0;
	NODE* pN = pFactory->broomList.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}
int		checkBroomUniqueCode(const char* code, const MagicFactory* pFactory)
{
	Broom* broom = findBroomByCode(pFactory, code);

	if (broom != NULL)
		return 0;

	return 1;
}

void	printBrooms(const MagicFactory* pFactory)
{
	int count = getBroomCount(pFactory);
	printf("there are %d Magical brooms in the factory\n", count);
	L_print(&pFactory->broomList, printBroomV);
}

void	printWands(const MagicFactory* pFactory)
{
	int count = getWandCount(pFactory);
	printf("there are %d wands in the factory\n", count);
	L_print(&pFactory->wandList, printWandV);

}


void	freeFactory(MagicFactory* pFactory)
{
	L_free(&pFactory->wandList, freeWandV);
	L_free(&pFactory->broomList, freeBroomV);
}

void	printMagicFactory(const MagicFactory* pF)
{
	printf("---------The products in the magic factory---------\n");
	int count = getWandCount(pF);
	printf("there are %d wands\n", count);
	L_print(&pF->wandList, printWandV);
	count = getBroomCount(pF);
	printf("there are %d brooms\n", count);
	L_print(&pF->broomList, printBroomV);

}