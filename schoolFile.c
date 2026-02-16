#include <stdio.h>
#include <stdlib.h>
#include "General.h"
#include "fileHelper.h"
#include "schoolFile.h"
#include "FactoryFile.h"


int		saveSchoolToFileB(const MagicSchool* pSchool,const MagicFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open school file to write\n");
		return 0;
	}

	if (!fwrite(pSchool->name, sizeof(char),LENGTH, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!fwrite(pSchool->principal, sizeof(char), LENGTH_PRINCIPAL, fp))
	{
		fclose(fp);
		return 0;
	}

	if (!writeIntToFile(eNofHouses, fp, "Error write\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!saveHouseArrFileB(pSchool, eNofHouses, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pSchool->spellCount, fp, "Error write\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!saveSpellArrFileB(pSchool,pSchool->spellCount, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pSchool->numOfCourses, fp, "Error write\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!saveCourseArrFileB(pSchool,pSchool->numOfCourses, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!saveFactoryToFileB(pFactory, fp))
	{
		fclose(fp);
		return 0;
	}
	
	fclose(fp);
	return 1;
}

int saveHouseArrFileB(const MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!saveHouseToFileB(&pS->housesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int saveHouseArrFileTXT(const MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!saveHouseToFileTXT(&pS->housesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int saveSpellArrFileB(const MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i <size; i++)
	{
		if (!saveSpellToFileBCompressed(pS->spellsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int saveSpellArrFileTXT(const MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!saveSpellToFileTXT(pS->spellsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int saveCourseArrFileB(const MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!saveCourseToFileB(&pS->coursesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int saveCourseArrFileTXT(const MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!saveCourseToFileTXT(&pS->coursesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int		loadSchoolFromFileB(MagicSchool* pSchool, MagicFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open file\n");
		return 0;
	}

	pSchool->spellsArr = NULL;
	
	if (!fread(pSchool->name, sizeof(char), LENGTH, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!fread(pSchool->principal, sizeof(char), LENGTH_PRINCIPAL, fp))
	{
		fclose(fp);
		return 0;
	}
	int num=0;
	if (!readIntFromFile(&num, fp, "Error reading \n"))
	{
		fclose(fp);
		return 0;
	}
	if (!loadHouseArrFileB(pSchool,num, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!readIntFromFile(&pSchool->spellCount, fp, "Error reading count\n"))
	{
		fclose(fp);
		return 0;
	}

	if (!createSpellArr(pSchool))
	{
		printf("Allocation error\n");
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}
	if (!loadSpellArrFromFileB(pSchool,fp))
	{
		free(pSchool->spellsArr);
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}
	if (!readIntFromFile(&pSchool->numOfCourses, fp, "Error reading count\n"))
	{
		free(pSchool->spellsArr);
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}
	if (!createCourseArr(pSchool))
	{
		printf("Allocation error\n");
		free(pSchool->spellsArr);
		freeHouseArr(pSchool->housesArr, num);
		freeSpellArr(pSchool->spellsArr, num);
		fclose(fp);
		return 0;
	}
	if (!loadCourseArrayFileB(pSchool,pSchool->numOfCourses, fp))
	{
		free(pSchool->spellsArr);
		free(pSchool->coursesArr);
		freeHouseArr(pSchool->housesArr, num);
		freeSpellArr(pSchool->spellsArr, num);
		fclose(fp);
		return 0;
	}
	if (!loadFactoryFromFileB(pFactory, fp))
	{
		free(pSchool->spellsArr);
		freeCourseArr(pSchool->coursesArr,pSchool->numOfCourses);
		freeHouseArr(pSchool->housesArr, num);
		freeSpellArr(pSchool->spellsArr, num);
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;

}

int loadHouseArrFileB(MagicSchool* pS,int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!loadHouseFromFileB(&pS->housesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int loadHouseArrFileTXT(MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!loadHouseFromFileTXT(&pS->housesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int loadCourseArrayFileB(MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!loadCourseFromFileB(&pS->coursesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int loadCourseArrayFileTXT(MagicSchool* pS, int size, FILE* fp)
{
	for (int i = 0; i < size; i++)
	{
		if (!loadCourseFromFileTXT(&pS->coursesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int createSpellArr(MagicSchool* pS)
{
	if (pS->spellCount > 0)
	{
		pS->spellsArr = (Spell**)malloc(pS->spellCount * sizeof(Spell*));
		if (!pS->spellsArr)
		{
			printf("Allocation error\n");
			return 0;
		}
	}
	else
		pS->spellsArr = NULL;

	for (int i = 0; i < pS->spellCount; i++)
	{
		pS->spellsArr[i] = (Spell*)calloc(1, sizeof(Spell));
		if (!pS->spellsArr[i])
		{
			printf("Allocation error\n");
			return 0;
		}
	}
	return 1;
}
int loadSpellArrFromFileB(MagicSchool* pS, FILE* fp)
{

	for (int i = 0; i < pS->spellCount; i++)
	{
		if (!loadSpellFromFileBCompressed(pS->spellsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int loadSpellArrFromFileTXT(MagicSchool* pS, FILE* fp)
{

	for (int i = 0; i < pS->spellCount; i++)
	{
		if (!loadSpellFromFileTXT(pS->spellsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int		createCourseArr(MagicSchool* pS)
{
	pS->coursesArr = (Course*)malloc(pS->spellCount * sizeof(Course));
	if (!pS->coursesArr)
	{
		printf("Allocation error\n");
		return 0;
	}
	return 1;
}

int		saveSchoolToFileTXT(const MagicSchool* pSchool, const MagicFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open school file to write\n");
		return 0;
	}

	fprintf(fp, "%s\n", pSchool->name);
	fprintf(fp, "%s\n", pSchool->principal);
	fprintf(fp, "%d\n", eNofHouses);
	if (!saveHouseArrFileTXT(pSchool, eNofHouses, fp))
	{
		fclose(fp);
		return 0;
	}
	fprintf(fp, "%d\n", pSchool->spellCount);
	if (!saveSpellArrFileTXT(pSchool,pSchool->spellCount, fp))
	{
		fclose(fp);
		return 0;
	}

	fprintf(fp, "%d\n", pSchool->numOfCourses);

	if (!saveCourseArrFileTXT(pSchool,pSchool->numOfCourses, fp))
	{
		fclose(fp);
		return 0;
	}
	if (!saveFactoryToFileTXT(pFactory, fp))
	{
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}
int		loadSchoolFromFileTXT(MagicSchool* pSchool, MagicFactory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open file\n");
		return 0;
	}

	pSchool->spellsArr = NULL;
	int num = 0;
	myGets(pSchool->name, MAX_STR_LEN, fp);
	myGets(pSchool->principal, MAX_STR_LEN, fp);
	if (fscanf(fp, "%d", &num) != 1)
	{
		fclose(fp);
		return 0;
	}

	if (!loadHouseArrFileTXT(pSchool, num, fp))
	{
		fclose(fp);
		return 0;
	}
	if (fscanf(fp, "%d", &pSchool->spellCount) != 1)
	{
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}

	if (!createSpellArr(pSchool))
	{
		printf("Allocation error\n");
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}
	if (!loadSpellArrFromFileTXT(pSchool, fp))
	{
		free(pSchool->spellsArr);
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}
	if (!fscanf(fp, "%d", &pSchool->numOfCourses))
	{
		free(pSchool->spellsArr);
		freeHouseArr(pSchool->housesArr, num);
		fclose(fp);
		return 0;
	}
	if (!createCourseArr(pSchool))
	{
		printf("Allocation error\n");
		free(pSchool->spellsArr);
		freeHouseArr(pSchool->housesArr, num);
		freeSpellArr(pSchool->spellsArr, num);
		fclose(fp);
		return 0;
	}
	if (!loadCourseArrayFileTXT(pSchool, pSchool->numOfCourses, fp))
	{
		free(pSchool->spellsArr);
		free(pSchool->coursesArr);
		freeHouseArr(pSchool->housesArr, num);
		freeSpellArr(pSchool->spellsArr, num);
		fclose(fp);
		return 0;
	}
	if (!loadFactoryFromFileTXT(pFactory, fp))
	{
		free(pSchool->spellsArr);
		freeCourseArr(pSchool->coursesArr, pSchool->numOfCourses);
		freeHouseArr(pSchool->housesArr, num);
		freeSpellArr(pSchool->spellsArr, num);
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;

}

