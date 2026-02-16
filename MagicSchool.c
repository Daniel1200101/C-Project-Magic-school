#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "MagicSchool.h"
#include "General.h"
#include "Macros.h"
//static const char* HouseNames[eNofHouses]
//= { "Gryffindor", "Ravenclaw", "Slytherin" ,"Hufflepuff" };

void	initMagicSchool(MagicSchool* pSchool)
{
	strcpy(pSchool->name, NAME);
	strcpy(pSchool->principal, NAME_PRINCIPAL);
	pSchool->spellsArr = NULL;
	pSchool->spellCount = 0;
	pSchool->coursesArr = NULL;
	pSchool->numOfCourses = 0;
	initMagicSchoolHouses(pSchool);
}
void	initMagicSchoolHouses(MagicSchool* pSchool)
{
	for (int i = 0; i < eNofHouses; i++)
	{
		initHouse(&pSchool->housesArr[i], (eHouseName)i);
	}
}
int	initStudent(Student* pStudent, const MagicSchool* pSchool, MagicFactory* pFactory)
{
	int numOFWands = getWandCount(pFactory);
	if (numOFWands == 0)
	{
		PRINT(There are no wands in the factory - wizard must have a wand);
		return 0;
	}
	pStudent->ID = getStudentID(pSchool);
	if (!initStudentNoID(pStudent))
		return 0;
	pStudent->wand = *chooseWandFromList(pFactory, "Choose wand from the magic factory");
	return 1;
}

eHouseName		getHouseName()
{
	int option;
	printf("\n");
	do {
		PRINT(Please Choose House:);
		for (int i = 0; i < eNofHouses; i++)
			printf("%d for %s\n", i, HouseNames[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofHouses);
	getchar();
	return (eHouseName)option;
}

void setHeadTOHouse(MagicSchool* pSchool)
{
	eHouseName name = getHouseName();
	setHeadOfHouse(&pSchool->housesArr[name]);
	PRINT(Head of house has been choosen);
}

void	findStudentInHouse(const MagicSchool* pSchool)
{
	eHouseName name = getHouseName();
	findStudent(&pSchool->housesArr[name]);
}
void	sortStudentsInHouse(MagicSchool* pSchool)
{

	eHouseName name = getHouseName();
	sortStudent(&pSchool->housesArr[name]);
}
int addCourseCodeToStudent(MagicSchool* pSchool)
{
	Student* s = NULL;
	eHouseName name = getHouseName();
	s = findStudentGeneral(&pSchool->housesArr[name]);
	if (!s)
		return 0;
	printCoursesArr(pSchool->coursesArr, pSchool->numOfCourses);
	Course* c = findCourse(pSchool->coursesArr, pSchool->numOfCourses, "Enter course code");
	
	if (!c)
		return 0;
	if (!addCourseCode(s, c)) 
	{
		return 0;
	}
		
	return 1;

}

int		addStudentToMagicalSchool(MagicSchool* pSchool,MagicFactory* pFactory)
{
	Student* pStudent = (Student*)calloc(1, sizeof(Student));
	if (!pStudent)
		return 0;
	if (!initStudent(pStudent, (const MagicSchool*)pSchool, pFactory))
	{
		printf("Error init student\n");
		free(pStudent);
		return 0;
	}
	printf("Welcome to %s!\n", NAME);
	int houseNum=sortingHat();
	if (addStudentToHouse(&pSchool->housesArr[houseNum], pStudent))
	{
		printf("the student added to the house!\n\n");
		return 1;
	}
	printf("Error adding student\n");
	return 0;
}
int getStudentID(const MagicSchool* pSchool)
{
	int num;
	int unique = 0;
	do {
		printf("Enter Student ID number - have to be %d\n", ID_LENGTH);
		scanf("%d", &num);
		if (checkIDLength(num) == ID_LENGTH)
			unique = isIDNumUnique(pSchool, num);
	} while (!unique);
	return num;
}
int		isIDNumUnique(const MagicSchool* pSchool, int num)
{
	for (int i = 0; i < eNofHouses; i++)
	{
		for (int j = 0; j < pSchool->housesArr[i].studentsNum; j++)
		{
			if (pSchool->housesArr[i].studentsArr[j]->ID == num)
			{
				printf("\n!!!your ID in not unique!!!\n");
				return 0;
			}
		}
	}
	return 1;
}
int totalStudentInSchool(const MagicSchool* pSchool)
{
	int size = 0;
	for (int i = 0; i < eNofHouses; i++)
	{
		size += pSchool->housesArr[i].studentsNum;
	}
	return size;
}

int spellDuel(const MagicSchool* pSchool)
{
	if (totalStudentInSchool(pSchool) < 2)
	{
		PRINT(There are not enough students for duel(min 2 student));
		return 0;
	}
	if (pSchool->spellCount == 0)
	{
		PRINT(Add Spells to school before you start battle!);
		return 0;
	}
	Student* s1 = NULL;
	Student* s2 = NULL;
	Spell sP1;
	Spell sP2;
	int score1 = 0;
	int score2 = 0;
	if (!studentsForDuel(pSchool, &s1, &s2, "\nWELCOME TO SPELL DUELS :"))
		return 0;

	printf("\n -------- Spells for students: %d\n", pSchool->spellCount);
	for (int i = 0; i < pSchool->spellCount; i++)
	{
		printSpell(pSchool->spellsArr[i]);
	}
	printf("\n%d BATTELS:\n", DUEL_ROUNDS);
	for (int i = 0; i < DUEL_ROUNDS; i++)
	{
		printf("Round %d:\n", i+1);
		PRINT(Student 1 choose spell);
		while (1)
		{
			sP1 = *chooseSpellFromArr(pSchool);
			if (sP1.minYearUse > s1->year)
			{
				printf("The student %s is not experienced enough to use this spell", s1->name);
			}
			else
				break;
		}

		PRINT(Student 2 choose spell);
		while (1)
		{
			sP2 = *chooseSpellFromArr(pSchool);
			if (sP2.minYearUse > s2->year)
			{
				printf("The student %s is not experienced enough to use this spell", s2->name);
			}
			else
				break;
		}
		score1 = SUM(score1, MULT(sP1.power, sP1.difficulty + generateRandomNumber(100)));
		score2 = SUM(score2, MULT(sP2.power, sP2.difficulty + generateRandomNumber(100)));

		printf("\n*Round %d score:*\n", i);
		printf("Student1-%s: %d", s1->name, score1);
		printf("\tStudent2-%s: %d\n\n", s2->name, score2);

	}
	int max = MAX(score1, score2);
	if (max == score1)
	{
		printf("%s, won!\n", s1->name);
	}
	else
	{
		printf("%s, won!\n", s2->name);
	}

	return 1;

}
int broomRace(const MagicSchool* pSchool, const MagicFactory* pFactory)
{
	if (totalStudentInSchool(pSchool) < 2)
	{
		PRINT(There are not enough students for race(min 2 student));
		return 0;
	}
	int broomCount = getBroomCount(pFactory);
	if (broomCount<2)
	{
		PRINT(Add BroomSticks to school before you start Race!);
		return 0;
	}
	Student* s1;
	Student* s2;
	Broom*  B1;
	Broom* B2;
	int distance1 = 0;
	int distance2 = 0;
	if (!studentsForDuel(pSchool, &s1, &s2, "\n\nWELCOME TO BROOM_STICK RACE:"))
		return 0;
	printf("\n -------- Brooms for students: %d\n", broomCount);
	printBrooms(pFactory);
	
	PRINT(Student 1 choose BroomStick);
	do
	{
		char* broomCode = getStrExactName("Enter Broom code\n");
		B1 = findBroomByCode(pFactory, broomCode);
	} while (!B1);
			
	int unique = 0;
	PRINT(Student 2 choose BroomStick);		
	do
	{
		char* broomCode = getStrExactName("Enter Broom code\n");
		B2 = findBroomByCode(pFactory, broomCode);
		if(B2)
			if (B2->code - B1->code != 0) 
				unique = 1;
			else
				PRINT(This broomStick is already taken!)
			
	} while (!B2||!unique);
		
		printf("The race begins in\n");
		for (int i = DUEL_ROUNDS; i >0; i--)
		{
			printf("%d\n",i);
			_sleep(1000);
		}
		printf("GO!!\n");
			for (int i = 0; i < DUEL_ROUNDS; i++)
		{			
			distance1 += B1->speed * generateRandomNumber(50);
		    distance2 += B2->speed * generateRandomNumber(50);
		    printf("Student1:%s distance:%d[M]\t", s1->name, distance1);
			printf("Student2:%s distance:%d[M]\n", s2->name, distance2);
			_sleep(3000);
		}
			
			int max = MAX(distance1, distance2);
			if (max == distance1)
			{
				printf("%s, won! with distance-%d[M]\n", s1->name,distance1);
			}
			else
			{
				printf("%s, won! with distance-%d[M]\n\n", s2->name, distance2);
			}
			return 1;
}
int studentsForDuel(const MagicSchool* pSchool, Student** s1, Student** s2,char* msg)
{
	printf(msg);
	PRINT(\nChoose student 1:);
	do {
		eHouseName name = getHouseName();
		*s1 = findStudentGeneral(&pSchool->housesArr[name]);
	} while (!*s1);

	PRINT(\nChoose student 2:);
	while (1) {
		do {
			eHouseName name = getHouseName();
			*s2 = findStudentGeneral(&pSchool->housesArr[name]);
		} while (!*s2);
		if ((*s2)->ID == (*s1)->ID) {
			PRINT(\nYou cant choose the same student);
		}
		else {
			break;
		}
	}
	return 1;
}


Spell* chooseSpellFromArr(const MagicSchool* pSchool)
{
	char temp[MAX_STR_LEN];
	Spell* s = NULL;
	int found = 0;

	while (!found) {
		printf("Enter spell name:\n");
		myGets(temp, MAX_STR_LEN, stdin);

		if (strcmp(temp, FORBIDDEN_SPELL) == 0)
		{
			printf("You can't use the forbidden spell '%s'!\n", FORBIDDEN_SPELL);
		}
		else {
			for (int i = 0; i < pSchool->spellCount; i++) {
				if (strcmp(temp, pSchool->spellsArr[i]->spellName) == 0) {
					s = pSchool->spellsArr[i];
					found = 1;
					break;
				}
			}
			if (!found) {
				printf("Spell '%s' not found. Please enter a valid spell name.\n", temp);
			}
		}
	}

	return s;
}

void printSong()
{
	printf("Now the Sorting Hat choose to which house you belong!\n\n");
	printf("Old %s Sorting Hat sing me a song\n", NAME);
	printf("Speak in my head tell me where I belong\n");
	printf("And when things look bad and there's no where to run\n");
	printf("Unite all the houses and we'll fight as one\n");
}
int   sortingHat() 
{
	printSong();
	int houseNum = generateRandomNumber(eNofHouses);
	printf("\nthe choosen house is: ***%s***\n", HouseNames[houseNum]);
	return houseNum;
}
int		addCourse(MagicSchool* pSchool)
{
	pSchool->coursesArr = (Course*)realloc(pSchool->coursesArr, (pSchool->numOfCourses + 1) * sizeof(Course));
	if (!pSchool->coursesArr)
		return 0;
	if (!initCourse(&pSchool->coursesArr[pSchool->numOfCourses], pSchool->coursesArr, pSchool->numOfCourses))
	{
		free(&pSchool->coursesArr[pSchool->numOfCourses]);
		return 0;
	}	
	pSchool->numOfCourses++;
	return 1;
}


int	addSpell(MagicSchool* pSchool)
{
	Spell* pSpell = (Spell*)calloc(1, sizeof(Spell));
	if (!pSpell)
		return 0;

	if (!initSpell(pSpell, pSchool->spellsArr, pSchool->spellCount)) 
	{
		free(pSpell);
		return 0;
	}

	pSchool->spellsArr = (Spell**)realloc(pSchool->spellsArr, (pSchool->spellCount+ 1) * sizeof(Spell*));
	if (!pSchool->spellsArr)
	{
		free(pSpell);
		return 0;
	}
	pSchool->spellsArr[pSchool->spellCount] = pSpell;
	pSchool->spellCount++;
	///////////////////
	return 1;
}

Course* findCourseByCode(Course* coursesArr, int numOfCourses, int code)
{
	for (int i = 0; i < numOfCourses;i++)
	{
		if ((coursesArr[i].code - code) == 0)
			return &coursesArr[i];
	}
	return NULL;
}
Course* findCourse(Course* coursesArr, int numOfCourses, const char* msg)
{
	int code;
	Course* course;
	do
	{
		printf("%s\t", msg);
		scanf("%d", &code);
		course = findCourseByCode(coursesArr, numOfCourses, code);
		if (course == NULL)
			printf("No course with this code - try again\n");
	} while (course == NULL);

	return course;
}

void	printHousesArr(const House* houseArr, int size)
{
	for (int i = 0; i < size; i++)
		printHouse(&houseArr[i]);
	printf("\n");
}

void	printCoursesArr(const Course* coursesArr, int numOfCourses)
{
	for (int i = 0; i < numOfCourses; i++)
	{
		printf("%d)", i+1);
		printCourse(&coursesArr[i]);
	}
}

void	printSpellsArr(const Spell** pArr, int size)
{
	for (int i = 0; i <size; i++)
	{
		printSpell(pArr[i]);
		printf("\n");
	}
	printf("\n");
}

void	printMagicSchool(const MagicSchool* pSchool)
{
	printf("\nMagic School: %s\n", pSchool->name);
	printf("Principal: %s\n", NAME_PRINCIPAL);
	printf("\n -------- Has %d houses\n\n", eNofHouses);
	printHousesArr(pSchool->housesArr, eNofHouses);
	printf("\n -------- Number of magic courses: %d\n", pSchool->numOfCourses);
	printCoursesArr(pSchool->coursesArr, pSchool->numOfCourses);
	printf("\n -------- Spells for students: %d\n", pSchool->spellCount);
	printSpellsArr(pSchool->spellsArr,pSchool->spellCount);
}

void	freeCourseArr(Course* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Course), freeCourse);

}

void	freeSpellArr(Spell** arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Spell*), freeSpellPtr);
}

void	freeHouseArr(House* arr, int numOfHouses)
{
	for (int i = 0; i < numOfHouses; i++)
	{
		freeHouse(&arr[i]);
	}
	//////////?free kofsa////////?
}

void	freeMagicSchool(MagicSchool* pSchool) 
{
	freeSpellArr(pSchool->spellsArr, pSchool->spellCount);
	free(pSchool->spellsArr);
	freeHouseArr(pSchool->housesArr,eNofHouses);
	freeCourseArr(pSchool->coursesArr,pSchool->numOfCourses);
}