#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "schoolFile.h"
#include "Macros.h"

/// We made hardCoded files which contain exist school (You can use if you had problem with the last file)
#define HARD_CODED_TXT  "HardCodedSchool.txt"
#define HARD_CODED_BIN  "HardCodedSchool.bin"



#define FILE_NAME_TXT "MagicSchool.txt"
#define FILE_NAME_BIN "MagicSchool.bin"

#define LOAD

int initSchoolAndFactory(MagicSchool* pSchool, MagicFactory* pFactory);


int main()
{
	srand((unsigned int)time(NULL));
	MagicFactory factory;
	MagicSchool school;

	///files///
	
	printf("Welcome to %s !!!\nThe magic world of Harry Potter\n", NAME);
	
/// You can choose to load exist file or to init the system from 0.
#ifdef LOAD
	if (!initSchoolAndFactory(&school, &factory))
	{
		printf("error init");
		return;
	}
#else
	{
		initMagicSchool(&school);
		initFactory(&factory);		
	}
#endif // !LOAD			
	int flag = 0;
	int choose;
	while (!flag)
	{
		printf("\n1-->Print magic school- the main struct\n");
		printf("2-->Print the magic factory\n");
		printf("3-->Add WAND to Factory\n");
		printf("4-->Add BROOM to Factory\n");
		printf("5-->Add STUDENT to School- the sorting hat will choose the house\n");
		printf("6-->Add SPELL to School- students will use the spells in duel practice\n");
		printf("7-->Add COURSE to School\n");
		printf("8-->Add COURSE to Student- add him credits and he may pass to the next year\n");
		printf("9-->Sort student array in some house\n");
		printf("10-->Find student in some house\n");
		printf("11-->Set new HEAD OF HOUSE- a student with the most academic credits\n");
		printf("12-->Student spell duel\n");
		printf("13-->Student broom race\n");
		printf("-1-->Exit\n");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printMagicSchool(&school);
			break;
		case 2:
			printMagicFactory(&factory);
			break;
		case 3:
			if (!addWand(&factory))
				printf("Error adding Wand\n");
			break;
		case 4:
			if (!addBroom(&factory))
				printf("Error adding Broom\n");
			break;
		case 5:
			if (!addStudentToMagicalSchool(&school, &factory))
				printf("Error adding student to school\n");
			break;
		case 6:
			if (!addSpell(&school))
				printf("Error adding a new spell to school\n");
			break;
		case 7:
			if (!addCourse(&school))
				printf("Error adding a new course to school\n");
			break;
		case 8:
			if (!addCourseCodeToStudent(&school))
				printf("Error adding course code to student\n");
			break;
		case 9:	
			sortStudentsInHouse(&school);
			break;
		case 10:
			findStudentInHouse(&school);
			break;
		case 11:
			setHeadTOHouse(&school);
			break;
		case 12:
			if (!spellDuel(&school))
				PRINT(The duel cant be preformed);
			break;
		case 13:
			if (!broomRace(&school,&factory))
				PRINT(The race cant be preformed);
			break;
		case -1:
				PRINT(BYE BYE);
				flag = 1;
			break;
		default:
			printf("Error try again");
			break;
		}

	}
    saveSchoolToFileB(&school,&factory, FILE_NAME_BIN);
    saveSchoolToFileTXT(&school, &factory, FILE_NAME_TXT);
	freeMagicSchool(&school);
	freeFactory(&factory);
}

int initSchoolAndFactory(MagicSchool* pSchool, MagicFactory* pFactory)
{
	int flag = 0;
	int num = 0;
	while (!flag)
	{
		printf("choose file format to load and press enter:\n");
		printf("1 -> bin\n");
		printf("2 -> txt\n");
		scanf("%d", &num);
		flag = num == 1 || num == 2;
	}

	int load = 0;
	switch (num)
	{
	case 1:
		load = loadSchoolFromFileB(pSchool, pFactory, FILE_NAME_BIN);
		break;
	case 2:
		load = loadSchoolFromFileTXT(pSchool, pFactory, FILE_NAME_TXT);
		break;
	}
	if (!load)
	{
		initMagicSchool(pSchool);
		if (!initFactory(pFactory))
			return 0;
	}
	return 1;
}
