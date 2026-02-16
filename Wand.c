#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Wand.h"
#include "General.h"


int	isSameWand(const Wand* pWand1, const Wand* pWand2)
{
	if (!pWand1 || !pWand2)
		return 0;
	if (strcmp(pWand1->code, pWand2->code) == 0)
		return 1;

	return 0;
}


int	isWandCode(const Wand* pWand1, const char* code)
{
	if (!pWand1)
		return 0;
	if (strcmp(pWand1->code, code) == 0)
		return 1;

	return 0;
}


int		compareWandByCode(const void* v1, const void* v2)
{
	const Wand* pW1 = (const Wand*)v1;
	const Wand* pW2 = (const Wand*)v2;
	return strcmp(pW1->code, pW2->code);

}
int		getWandMFGYear()
{
	int num;
	int flag = 0;
	do {
		printf("Enter wand manufacturing year - between %d to %d\n", MIN_YEAR_MFG, MAX_YEAR_MFG);
		scanf("%d", &num);
		if (num >= MIN_YEAR_MFG && num <= MAX_YEAR_MFG)
			flag = 1;
	} while (!flag);
	return num;
}
void    getWandCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter wand code  - %d UPPER CASE letters\t", CODE_LENGTH);
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
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}
void	printWand(const Wand* pWand)
{
	printf("Manufacturing year: %-20d\t Code:%s\n", pWand->mfgYear, pWand->code);
}

void	printWandV(const void* val)
{
	printWand((const Wand*)val);

}


void	freeWand(Wand* pWand)
{
	//free(pWand);
}
void	freeWandV(void* val)
{
	freeWand((Wand*)val);
}

int		saveWandToFileB(const Wand* pWand, FILE* fp)
{
	if (fwrite(pWand, sizeof(Wand), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

int		loadWandFromFileB(Wand* pWand, FILE* fp)
{
	if (fread(pWand, sizeof(Wand), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

int		saveWandToFileTXT(const Wand* pWand, FILE* fp)
{
	if (!pWand)
		return 0;
	fprintf(fp, "%d\n", pWand->mfgYear);
	fprintf(fp, "%s\n", pWand->code);
	return 1;
}

int		loadWandFromFileTXT(Wand* pWand, FILE* fp)
{
	if (!pWand)
		return 0;

	fscanf(fp, "%d", &pWand->mfgYear);
	myGets(pWand->code, MAX_STR_LEN, fp);
	return 1;
}
