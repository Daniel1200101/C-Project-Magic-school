#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "FactoryFile.h"
#include "General.h"
#include "FileHelper.h"
#include "Macros.h"
int		saveFactoryToFileB(const MagicFactory* pFactory,FILE* fp)
{
	if (!pFactory)
		return 0;

	//wand list-save B
	if (!saveWandListToB(pFactory, fp))
	{
		
		return 0;
	}

	if (!saveBroomListToB(pFactory, fp))
	{
		
		return 0;
	}
	
	return 1;



}
int		loadFactoryFromFileB(MagicFactory* pFactory,FILE* fp)
{
	//int countWand = 0;
	//if (!readIntFromFile(&countWand, fp, "Error reading count\n"))
	//{
		//
		//return 0;
	//}
	//wand list- load B
	if (!loadWandListFromB(pFactory, fp))
	{
		return 0;
	}
	if (!loadBroomListFromB(pFactory, fp))
	{
		L_free(&pFactory->wandList, freeWandV);
	
		return 0;
	}
	
	return 1;
}
int saveBroomListToB(const MagicFactory* pFactory, FILE* fp)
{
	int count = getBroomCount(pFactory);
	if (!writeIntToFile(count, fp, "Error write  count\n"))
	{
		fclose(fp);
		return 0;
	}
	if (count > 0)
	{
		NODE* pN = pFactory->broomList.head.next; //first Node

		Broom* pTemp;
		while (pN != NULL)
		{
			pTemp = (Broom*)pN->key;
			if (!saveBroomToFileB(pTemp, fp))
			{
				PRINT(Error write broom);
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}

	}
	return 1;
}

int		saveFactoryToFileTXT(const MagicFactory* pFactory, FILE* fp)
{
	
	if (!saveWandListToTXT(pFactory, fp))
	{
		
		return 0;
	}

	if (!saveBroomListToTXT(pFactory, fp))
	{
		return 0;
	}

	return 1;
}
int		loadFactoryFromFileTXT(MagicFactory* pFactory, FILE* fp)
{
	

	if (!loadWandListFromTXT(pFactory, fp))
	{
	
		return 0;
	}
	if (!loadBroomListFromTXT(pFactory, fp))
	{
		L_free(&pFactory->wandList, freeWandV);
		
		return 0;
	}
	
	return 1;
}

int		loadWandListFromTXT(MagicFactory* pFactory, FILE* fp)
{
	L_init(&pFactory->wandList);
	int count;
	fscanf(fp, "%d", &count);
	//clean the buffer
	fgetc(fp);
	Wand* pWand;
	for (int i = 0; i < count; i++)
	{
		pWand = (Wand*)calloc(1, sizeof(Wand));
		if (!pWand)
			break;
		if (!loadWandFromFileTXT(pWand, fp))
		{
			PRINT(Error loading wand from file);
			return 0;
		}
		insertNewWandToList(&pFactory->wandList, pWand);
	}
	return 1;
}

int		loadBroomListFromTXT(MagicFactory* pFactory, FILE* fp)
{
	L_init(&pFactory->broomList);
	int count2;
	fscanf(fp, "%d", &count2);
	//clean the buffer
	fgetc(fp);

	Broom* pBroom;
	for (int i = 0; i < count2; i++)
	{
		pBroom = (Broom*)calloc(1, sizeof(Broom));
		if (!pBroom)
			break;
		if (!loadBroomFromFileTXT(pBroom, fp))
		{
			PRINT(Error loading broom from file);
			return 0;
		}
		insertNewBroomToList(&pFactory->broomList, pBroom);
	}
	return 1;
}
int		saveBroomListToTXT(const MagicFactory* pFactory, FILE* fp)
{
	int count = getBroomCount(pFactory);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pFactory->broomList.head.next; //first Node

		Broom* pTemp;
		while (pN != NULL)
		{
			pTemp = (Broom*)pN->key;
			if (!saveBroomToFileTXT(pTemp, fp))
			{
				PRINT(Error write broom);
				return 0;
			}
			pN = pN->next;
		}

	}
	return 1;
}

int		 saveWandListToTXT(const MagicFactory* pFactory, FILE* fp)
{
	int count = getWandCount(pFactory);
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{
		NODE* pN = pFactory->wandList.head.next; //first Node

		Wand* pTemp;
		while (pN != NULL)
		{
			pTemp = (Wand*)pN->key;
			if (!saveWandToFileTXT(pTemp, fp))
			{
				PRINT(Error write wand);
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}
	}
	return 1;
}
int loadWandListFromB(MagicFactory* pFactory, FILE* fp) {
	L_init(&pFactory->wandList);
	int count;
	if (!readIntFromFile(&count, fp, "Error reading count\n"))
	{
		return 0;
	}
	Wand* pWand;
	for (int i = 0; i < count; i++)
	{
		pWand = (Wand*)calloc(1, sizeof(Wand));
		if (!pWand)
			break;
		if (!loadWandFromFileB(pWand, fp))
		{
			PRINT(Error loading  from file);
			return 0;
		}
		insertNewWandToList(&pFactory->wandList, pWand);
	}
	return 1;
}

int loadBroomListFromB(MagicFactory* pFactory, FILE* fp) {
	L_init(&pFactory->broomList);
	int count2;
	if (!readIntFromFile(&count2, fp, "Error reading count\n"))
	{
		return 0;
	}
	Broom* pBroom;
	for (int i = 0; i < count2; i++)
	{
		pBroom = (Broom*)calloc(1, sizeof(Broom));
		if (!pBroom)
			break;
		if (!loadBroomFromFileB(pBroom, fp))
		{
			PRINT(Error loading broom from file);
			return 0;
		}
		insertNewBroomToList(&pFactory->broomList, pBroom);
	}
	return 1;
}
int		saveWandListToB(const MagicFactory* pFactory, FILE* fp)
{
	int count = getWandCount(pFactory);
	if (!writeIntToFile(count, fp, "Error write  count\n"))
	{
		fclose(fp);
		return 0;
	}
	if (count > 0)
	{
		NODE* pN = pFactory->wandList.head.next; //first Node

		Wand* pTemp;
		while (pN != NULL)
		{
			pTemp = (Wand*)pN->key;
			if (!saveWandToFileB(pTemp, fp))
			{
				PRINT(Error write wand);
				fclose(fp);
				return 0;
			}
			pN = pN->next;
		}
	}
	return 1;
}