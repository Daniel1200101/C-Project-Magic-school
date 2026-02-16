#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "Broom.h"
#include "General.h"
#include "FileHelper.h"
#include "Macros.h"


int		isSameBroom(const Broom* pBroom1, const Broom* pBroom2) 
{
	if (!pBroom1 || !pBroom2)
		return 0;
	if (strcmp(pBroom1->code, pBroom2->code) == 0)
		return 1;

	return 0;

}
int		isBroomCode(const Broom* pBroom1, const char* code)
{
	if (!pBroom1)
		return 0;
	if (strcmp(pBroom1->code, code) == 0)
		return 1;

	return 0;
}
int		getBroomSpeed() 
{
	int num;
	int flag = 0;
	do 
	{
		printf("Enter Magic Broom speed- between %d to %d\n", MIN_SPEED, MAX_SPEED);
		scanf("%d", &num);
		if (num >= MIN_SPEED && num <= MAX_SPEED)
			flag = 1;
	} while (!flag);
	return num;
}


void    getBroomCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do 
	{
		ok = 1;
		printf("Enter Broom code  - %d UPPER CASE letters\t", CODE_LENGTH);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != CODE_LENGTH)
		{
			printf("code should be %d letters\n", CODE_LENGTH);
			ok = 0;
		}
		else {
			for (int i = 0; i < CODE_LENGTH; i++)
			{
				if (isupper(temp[i]) == 0)
				{
					PRINT(Need to be upper letter);
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}
void	printBroom(const Broom* pBroom) 
{
	printf("Magic Broom speed: %-20d\t Code:%s\n", pBroom->speed, pBroom->code);
	printf("Magic Broom nickName:%s\n", pBroom->nickName);
	printf("Num of races: %d\n", pBroom->numOfRaces);

}
void	printBroomV(const void* val) 
{
	printBroom((const Broom*)val);
}

void	freeBroom(Broom* pBroom)
{
	free(pBroom->nickName);
	//free(pBroom);
}
void	freeBroomV(void* val) 
{
	freeBroom((Broom*)val);
}

int		saveBroomToFileB(const Broom* pBroom, FILE* fp)
{
	if (!writeStringToFile(pBroom->nickName, fp, "Error write name\n"))
	{
		
		return 0;
	}
	if (!fwrite(pBroom->code, sizeof(char),CODE_LENGTH, fp))
	{
		
		return 0;
	}
	if (!writeIntToFile(pBroom->speed, fp, "Error count\n"))
	{
		
		return 0;
	}
	if (!writeIntToFile(pBroom->numOfRaces, fp, "Error count\n"))
	{
		
		return 0;
	}
	return 1;
}

int		loadBroomFromFileB(Broom* pBroom, FILE* fp)
{
	pBroom->nickName = readStringFromFile(fp, "Error reading name\n");
	if (!pBroom->nickName)
	{
		return 0;
	}
	if (!fread(pBroom->code, sizeof(char), CODE_LENGTH, fp))
	{
		free(pBroom->nickName);
		
		return 0;
	}
	if (!readIntFromFile(&pBroom->speed, fp, "Error reading speed\n"))
	{
		free(pBroom->nickName);
		return 0;
	}
	if (!readIntFromFile(&pBroom->numOfRaces, fp, "Error reading count\n"))
	{
		free(pBroom->nickName);
		return 0;
	}
	return 1;

}

int		saveBroomToFileTXT(const Broom* pBroom, FILE* fp)
{
	if (!pBroom)
		return 0;
	fprintf(fp, "%s\n", pBroom->code);
	fprintf(fp, "%s\n", pBroom->nickName);
	fprintf(fp, "%d\n", pBroom->speed);
	fprintf(fp,"%d\n", pBroom->numOfRaces);
	
	return 1;

}

int		loadBroomFromFileTXT(Broom* pBroom, FILE* fp)
{

	char temp[MAX_STR_LEN];
	if (!pBroom)
		return 0;
	myGets(pBroom->code, MAX_STR_LEN, fp);
	myGets(temp, MAX_STR_LEN, fp);
	pBroom->nickName = getDynStr(temp);
	fscanf(fp, "%d", &pBroom->speed);
	fscanf(fp, "%d", &pBroom->numOfRaces);

	return 1;
}
