#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "string.h"
#include "Spell.h"
#include "General.h"
#include "Macros.h"

static const char* SpellDiffStr[eNofSpellDifficulty]
= {  "Easy", "Medium", "Hard"};


int  initSpell(Spell* pSpell, const Spell** spellArr, int spellCount)
{
	while (1)
	{
		if (!getSpellName(pSpell))
			return 0;

		if (checkUniqueName(spellArr, spellCount, pSpell->spellName))
			break;

		printf("This spell exist in school - enter a different name\n");
	}
	////
	pSpell->difficulty = getSpellDifficulty();
	pSpell->minYearUse = getMinYearOfUse();
	pSpell->power = MULT(pSpell->minYearUse,(pSpell->difficulty + 1));
	return 1;
}

int	isSameSpell(const Spell* pSpell1, const Spell* pSpell2)
{
		if (!pSpell1 || !pSpell2)
			return 0;
		if (strcmp(pSpell1->spellName, pSpell2->spellName) == 0)
			return 1;
		return 0;	
}
int		isSpellName(const Spell* pSpell1, const char* name)
{
	if (!pSpell1)
		return 0;
	if (strcmp(pSpell1->spellName, name) == 0)
		return 1;
	return 0;
}


int getMinYearOfUse()
{
	int min=0;
	while (1)
	{
		printf("\nEnter min academic year to use that spell: the max year is %d\n",MAX_YEAR_USE);
		scanf("%d", &min);
		if (min > MAX_YEAR_USE || min <= 0)
			printf("enter again\n");
		else
			break;
			
	}
	return min;
}
int checkUniqueName(const Spell** spellArr,int spellCount, const char* name)
{

	for (int i = 0; i < spellCount; i++)
	{
		if (equalStrIgnoreCase(spellArr[i]->spellName,name)==1)
			return 0;
	}
	return 1;
}


eSpellDifficulty		getSpellDifficulty()
{
	int option;
	printf("\n\n");
	do {
		printf("Please enter one of the following types\n");
		for (int i = 0; i < eNofSpellDifficulty; i++)
			printf("%d for %s\n", i, SpellDiffStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofSpellDifficulty);
	getchar();
	return (eSpellDifficulty)option;
}


int getSpellName(Spell* pSpell) {
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter spell name - remember the spell '%s' is forbidden!!!\n", FORBIDDEN_SPELL);
		myGets(temp, MAX_STR_LEN, stdin);
		
		if (equalStrIgnoreCase(temp, FORBIDDEN_SPELL)) {
			printf("You can't use the forbidden spell '%s'!\n", FORBIDDEN_SPELL);
			ok = 0;
		}
		else if (strlen(temp) >= MAX_STR_LEN - 1) {
			printf("Spell name is too long. Please enter a shorter name.\n");
			ok = 0;
		}
	} while (!ok);

	// Allocate memory for the name and copy the entered spell name
	pSpell->spellName = (char*)malloc(strlen(temp) + 1); // +1 for the null terminator
	if (pSpell->spellName == NULL) {
		printf("Memory allocation failed for spell name.\n");
		return 0; // Return failure
	}
	strcpy(pSpell->spellName, temp);

	return 1; // Return success
}

void	printSpell(const Spell* pSpell)
{
	printf("Spell name:%-20s\t", pSpell->spellName);
	printf("Difficulty: %s\n", SpellDiffStr[pSpell->difficulty]);
	printf("Min year to use: %d\n", pSpell->minYearUse);
	printf("Spell power: %d\n", pSpell->power);
}

void	printSpellV(const void* val)
{
	printSpell((const Spell*)val);
}

int		saveSpellToFileTXT(const Spell* pSpell, FILE* fp)
{
	if (!pSpell)
		return 0;
	fprintf(fp, "%s\n", pSpell->spellName);
	fprintf(fp, "%s\n",SpellDiffStr[pSpell->difficulty]);
	fprintf(fp, "%d\n", pSpell->minYearUse);
	fprintf(fp, "%d\n", pSpell->power);

	return 1;
}
int		loadSpellFromFileTXT(Spell* pSpell, FILE* fp)
{
	char difficultyStr[20]; // Assuming max difficulty string length is 20 characters
	char temp[MAX_STR_LEN];
	if (!pSpell)
		return 0;

	myGets(temp, MAX_STR_LEN, fp);
	pSpell->spellName = getDynStr(temp);

	if (fscanf(fp, "%19s\n", difficultyStr) != 1) 
	{
		printf("Error reading spell difficulty from file\n");
		return 0;
	}
	// Add null terminator explicitly
	difficultyStr[19] = '\0'; // Ensure null termination

	// Convert difficulty string to enum
	eSpellDifficulty difficulty1 = eNofSpellDifficulty;
	for (int i = 0; i < eNofSpellDifficulty; i++) {
		if (strcmp(difficultyStr, SpellDiffStr[i]) == 0) {
			difficulty1 = i;
			break;
		}
	}
	// Assign the difficulty outside of the else block
	pSpell->difficulty = difficulty1;
	fscanf(fp, "%d\n", &pSpell->minYearUse);
	fscanf(fp, "%d\n", &pSpell->power);
	return 1;
}

int		saveSpellToFileBCompressed(const Spell* pSpell, FILE* fp)
{
	BYTE data[2] = { 0 };
	int len = (int)strlen(pSpell->spellName);

	data[0] = pSpell->minYearUse << 5 | len;
	data[1] = pSpell->power<< 2 | pSpell->difficulty;

	//data[0] = len << 3 | pSt->type << 2 | pSt->year >> 1;
	//data[1] = ((pSt->year) & 0x1) << 7 | pSt->grade;

	if (fwrite(&data, sizeof(BYTE), 2, fp) != 2)
		return 0;

	if (fwrite(pSpell->spellName, sizeof(char), len, fp) != len)
		return 0;

	return 1;
}
int loadSpellFromFileBCompressed(Spell* pSpell, FILE* fp)
{
	BYTE data[2];

	if (fread(&data, sizeof(BYTE), 2, fp) != 2) {
		printf("Error reading compressed data from file.\n");
		return 0;
	}
	int len = 0;
	len = data[0] & 0x1F; // Get length of spell name
	pSpell->minYearUse = data[0] >> 5; // Get minimum year of use
	pSpell->power = data[1] >> 2; // Get power
	pSpell->difficulty = data[1] & 0x03; // Get difficulty

	// Allocate memory for spellName
	pSpell->spellName = (char*)malloc(len + 1);
	if (pSpell->spellName == NULL) {
		printf("Memory allocation failed.\n");
		return 0;
	}

	// Read the spell name from the file
	if (fread(pSpell->spellName, sizeof(char), len, fp) != len) {
		printf("Error reading spell name from file.\n");
		free(pSpell->spellName); // Free allocated memory
		return 0;
	}
	pSpell->spellName[len] = '\0'; // Null-terminate the string

	return 1;
}

void	printSpellPtr(void* pSpellPtr)
{
	const Spell* temp = *(Spell**)pSpellPtr;
	printSpell(temp);
}

void	freeSpellPtr(void* pSpellPtr)
{
	Spell* temp = *(Spell**)pSpellPtr;
	free(temp);
}

const char* GetSpellDiffStr(int type)
{
	if (type < 0 || type >= eNofSpellDifficulty)
		return NULL;
	return SpellDiffStr[type];
}
void	freeSpell(Spell* pSpell)
{
	free(pSpell->spellName);
	free(pSpell);
}

void	freeSpellV(void* val)
{
	freeSpell((Spell*)val);
}