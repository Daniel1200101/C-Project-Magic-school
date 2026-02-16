#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileHelper.h"
#include "House.h"
#include "General.h"
#include "Macros.h"


static const char* sortOptStr[eNofSortOpt] = {
	"None","Academic Credits", "Wand Code","Name Length","Year" };
void	    initHouse(House* pHouse, eHouseName name)
{
	pHouse->houseName = name;
	pHouse->studentsNum = 0;
	pHouse->studentsArr = NULL;
	pHouse->headOfHouse = NULL;//no head of house yet
	//pHouse->headOfHouse->ID = 0;
}



void	sortStudent(House* pHouse)
{
	pHouse->studentSortOpt = showSortMenu();
	int(*compare)(const void* student1, const void* student2) = NULL;

	switch (pHouse->studentSortOpt)
	{
	case eCredits:
		compare = compareStudentByCredits;
		break;
	case eWandCode:
		compare = compareStudentByWandCode;
		break;
	case eNameLen:
		compare = compareStudentByNameLength;
		break;
	case eYear:
		compare = compareStudentByYear;
		break;
	}
	if (compare != NULL)
		qsort(pHouse->studentsArr, pHouse->studentsNum, sizeof(Student*), compare);

}

eSortOption showSortMenu()
{
	int opt;
	PRINT(Base on what field do you want to sort?);
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}

void	findStudent(const House* pHouse)
{
	int(*compare)(const void* student1, const void* student2) = NULL;
	Student s = { 0 };
	Student* pStudent = &s;

	switch (pHouse->studentSortOpt)
	{
	case eCredits:
		PRINT(Find student by Total Credits:);
		scanf("%f", &s.totalCredits);						//////////////////////////// Need explaination
		compare = compareStudentByCredits;
		break;
	case eWandCode:
		PRINT(Find student by Wand code : );
		getWandCode(s.wand.code);
		compare = compareStudentByWandCode;
		break;
	case eNameLen:
		PRINT(Find student by name length : );
		getFavoriteWizard(s.favorite);
		compare = compareStudentByNameLength;
		break;
	case eYear:
		PRINT(Find student by year of study : );
		getCorrectYear(s.year);
		compare = compareStudentByYear;
		break;
	}

	if (compare != NULL)
	{
		Student** pS = bsearch(&pStudent, pHouse->studentsArr, pHouse->studentsNum, sizeof(Student*), compare);
		if (pS == NULL)
		{
			PRINT(Student was not found);
		}
		else
		{
			{
				PRINT(Student found);
			}
			printStudent(*pS);
		}
	}
	else
	{
		PRINT(The search cannot be performed the array is not sorted);
	}
}

Student* findHeadOfHouse(const House* pHouse)
{
	if (pHouse->studentsNum != 0)
	{
		Student* max = pHouse->studentsArr[0];
		for (int i = 1; i < pHouse->studentsNum; i++)
		{
			if (max->totalCredits < pHouse->studentsArr[i]->totalCredits)
				max = pHouse->studentsArr[i];
		}
		return max;
	}
	return NULL;
}

void setHeadOfHouse(House* pHouse)
{	
	//////////////////////////////////
	pHouse->headOfHouse = findHeadOfHouse(pHouse);
	/////////////////////////////////
}


int		addStudentToHouse(House* pHouse,Student* pStudent)
{
	pHouse->studentsArr = (Student**)realloc(pHouse->studentsArr, (pHouse->studentsNum + 1) * sizeof(Student*));
	if (!pHouse->studentsArr)
	{
		freeStudent(pStudent);
		return 0;
	}
	pHouse->studentsArr[pHouse->studentsNum] = pStudent;
	pHouse->studentsNum++;
	pHouse->studentSortOpt = eNone;
	return 1;
}



int		saveHouseToFileB(const House* pHouse, FILE* fp)
{
	if (pHouse->headOfHouse)
	{
		if (!writeIntToFile(pHouse->headOfHouse->ID, fp, "Error write head of house ID\n"))
		{

			return 0;
		}
	}
	else
	{
		if (!writeIntToFile(0, fp, "Error write head of house ID\n"))
		{

			return 0;
		}
	}

	if (!writeStringToFile(HouseNames[pHouse->houseName], fp, "Error write \n"))
	{		
		return 0;
	}
	if (!writeIntToFile(pHouse->studentsNum, fp, "Error write \n"))
	{
		
		return 0;
	}
	for (int i = 0; i < pHouse->studentsNum; i++)
	{
		if (!saveStudentToFileB(pHouse->studentsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}

int		loadHouseFromFileB(House* pHouse, FILE* fp)
{

	pHouse->studentsArr = NULL;
	int id = 0;
	if (!readIntFromFile(&id, fp, "Error reading int\n"))
	{
		return 0;
	}
	//???
	//char temp[256];
	char* temp;
	temp = readStringFromFile(fp, "Error reading  name\n");
	if (!temp)
	{
		return 0;
	}

	eHouseName name = eNofHouses;
	for (int i = 0; i < eNofHouses; i++) {
		if (strcmp(temp, HouseNames[i]) == 0)
		{
			name = i;
			break;
		}
	}

	pHouse->houseName = name;
	if (!readIntFromFile(&pHouse->studentsNum, fp, "Error reading\n"))
	{
		return 0;
	}
	
	if (!createStudentArr(pHouse))
	{
		PRINT(Allocation error);
		return 0;
	}

	if (!loadStudentArrFromFileB(pHouse,fp))
	{
		free(pHouse->studentsArr);
		return 0;
	}
	pHouse->studentSortOpt = eNone;

	
		if (id == 0)
			pHouse->headOfHouse = NULL;
		else
		{
			pHouse->headOfHouse = findStudentByID(pHouse->studentsArr, pHouse->studentsNum, id);
			if (!pHouse->headOfHouse)
				return 0;
		}
	return 1;

}
Student* findStudentGeneral(const House* pHouse)
{
	////
	if (pHouse->studentsNum != 0)
	{
		for (int i = 0; i < pHouse->studentsNum; i++)
		{
			printf("%d)", i + 1);
			printStudent(pHouse->studentsArr[i]);
		}
	}
	else
	{
		PRINT(There are no students in this house);             ////////////////////////////////////////////////////////////////
		return NULL;
	}
	Student* p = NULL;
	int num = 0;
	while (1)
	{
		PRINT(\nEnter the ID of the student you want to select);
		scanf("%d", &num);
		p = findStudentByID(pHouse->studentsArr, pHouse->studentsNum, num);
		if (p)
			return p;
	}

}
Student* findStudentByID(Student** studentsArr, int numOfStudents, int id)
{
	for (int i = 0; i < numOfStudents;i++)
	{
		if ((studentsArr[i]->ID-id) == 0)
			return studentsArr[i];
	}
	return NULL;
}
int createStudentArr(House* pHouse)
{
	if (pHouse->studentsNum> 0)
	{
		pHouse->studentsArr = (Student**)malloc(pHouse->studentsNum * sizeof(Student*));
		if (!pHouse->studentsArr)
		{
			PRINT(AlLocation error);
			return 0;
		}
	}
	else
		pHouse->studentsArr = NULL;

	for (int i = 0; i < pHouse->studentsNum; i++)
	{
		pHouse->studentsArr[i] = (Student*)calloc(1, sizeof(Student));
		if (!pHouse->studentsArr[i])
		{
			PRINT(AlLocation error);
			return 0;
		}
	}
	return 1;
}

int		saveHouseToFileTXT(const House* pHouse, FILE* fp)
{
	int id;
	if (pHouse->headOfHouse)
		id = pHouse->headOfHouse->ID;
	else
		id = 0;
	fprintf(fp, "%d\n", id);
	fprintf(fp, "%d\n", pHouse->houseName);
	fprintf(fp, "%d\n", pHouse->studentsNum);
	for (int i = 0; i < pHouse->studentsNum; i++)
	{
		if (!saveStudentToFileTXT(pHouse->studentsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;

}

int		loadHouseFromFileTXT(House* pHouse, FILE* fp)
{
	/////////////////
	int id = 0;
	fscanf(fp, "%d\n",&id);
	fscanf(fp, "%d\n", &pHouse->houseName);
	fscanf(fp, "%d\n", &pHouse->studentsNum);
	pHouse->studentSortOpt = eNone;

	if (!createStudentArr(pHouse))
	{
		PRINT(Allocation error);
		return 0;
	}
	if (!loadStudentArrFromFileTXT(pHouse, fp))
	{
		free(pHouse->studentsArr);
		return 0;
	}
	if (id == 0)
		pHouse->headOfHouse = NULL;
	else
	{
		pHouse->headOfHouse = findStudentByID(pHouse->studentsArr, pHouse->studentsNum, id);
		if (!pHouse->headOfHouse)
			return 0;
	}
	return 1;
}
int loadStudentArrFromFileB(House* pHouse,FILE* fp)
{

	for (int i = 0; i < pHouse->studentsNum; i++)
	{
		if (!loadStudentFromFileB(pHouse->studentsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
int loadStudentArrFromFileTXT(House* pHouse, FILE* fp)
{

	for (int i = 0; i < pHouse->studentsNum; i++)
	{
		if (!loadStudentFromFileTXT(pHouse->studentsArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}
void    printHouse(const House* pHouse)
{
	printf("\nHouse name:  ***%s***\t\n", HouseNames[pHouse->houseName]);
	if (pHouse->headOfHouse)
	{

		printf("The head of house is: ");
		printf("%s,ID:%d\n",pHouse->headOfHouse->name, pHouse->headOfHouse->ID);
	}
	if (pHouse->studentsNum != 0)
	{
		for (int i = 0; i < pHouse->studentsNum; i++)
		{
			printf("%d) ", i + 1);
			printStudent(pHouse->studentsArr[i]);
			printf("\n");
		}
	}
	else
		PRINT(There are no students in this house);
}

void	printStudentArr(const Student** arr, int studentsCount)
{
	generalArrayFunction(arr, studentsCount, sizeof(Student*), printStudentPtr);
}

void    printHouseV(void* val)
{
	printHouse((const House*)val);
}

void    freeHouse(House* pHouse)
{
	freeStudentArr(pHouse->studentsArr, pHouse->studentsNum);
	free(pHouse->studentsArr);
	
}

void	freeStudentArr(Student** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Student*), freeStudentPtr);

}

