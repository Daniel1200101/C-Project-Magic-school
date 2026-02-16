#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "Course.h"
#include "General.h"
#include "FileHelper.h"
#include "Macros.h"
int	initCourse(Course* pCourse,const Course* courseArr, int courseCount)
{
	
	if (!initCourseNoCode(pCourse))
		return 0;
	pCourse->code =getCourseCode(courseArr,courseCount);
	return 1;
}

int		initCourseNoCode(Course* pCourse1)
{

	pCourse1->name = getStrExactName("Enter course name: ");
	if (!pCourse1->name)
		return 0;
	pCourse1->credits = getCourseCredit();


	return 1;
}

int getCourseCode(const Course* courseArr, int courseCount)
{
	int num;
	int unique = 0;
	do 
	{
		printf("Enter course code number - have to be %d digits\n", CODE_LENGTH_COURSE);
		scanf("%d", &num);
		if (checkIDLength(num) == CODE_LENGTH_COURSE)
			unique = isCodeNumUnique(courseArr, courseCount,num);
	} while (!unique);
	return num;
}

int		isCodeNumUnique(const Course* courseArr,int courseCount, int num)
{
	for (int i = 0; i < courseCount; i++)
	{
		if (courseArr[i].code == num)
			return 0;
	}
	return 1;
}

int		isSameCourse(const Course* pCourse1, const Course* pCourse2) 
{
	if (!pCourse1 || !pCourse2)
		return 0;
	if ((pCourse1->code - pCourse2->code) == 0)
		return 1;
	
	return 0;
}

int		isCourseCode(const Course* pCourse1, int code)
{
	if (!pCourse1)
		return 0;
	if ((pCourse1->code-code)==0)
		return 1;
	return 0;
}

float getCourseCredit() 
{
	float credit;
	while (1)
	{
		printf("Enter course credit ,Max credit=%d\n", MAX_CREDIT);
		scanf("%f",&credit);
		if (credit <=0 || credit > MAX_CREDIT )
		{
			PRINT(Enter again);
		}
		else
			return credit;
	}
	
}

int		saveCourseToFileTXT(const Course* pCourse, FILE* fp)
{
	if (!pCourse)
		return 0;
	fprintf(fp, "%s\n", pCourse->name);
	fprintf(fp, "%d\n", pCourse->code);
	fprintf(fp, "%f\n", pCourse->credits);
	return 1;
}

int		loadCourseFromFileTXT(Course* pCourse, FILE* fp)
{
	char temp[MAX_STR_LEN];
	if (!pCourse)
		return 0;

	myGets(temp, MAX_STR_LEN, fp);
	pCourse->name = getDynStr(temp);
	fscanf(fp, "%d", &pCourse->code);
	fscanf(fp, "%f", &pCourse->credits);


	return 1;
}

int		saveCourseToFileB(const Course* pCourse, FILE* fp)
{
	if (!writeStringToFile(pCourse->name, fp, "Error write course name\n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeIntToFile(pCourse->code, fp, "Error write code \n"))
	{
		fclose(fp);
		return 0;
	}
	if (!writeFloatToFile(pCourse->credits, fp, "Error write credits \n"))
	{
		fclose(fp);
		return 0;
	}
	return 1;
}
int		loadCourseFromFileB(Course* pCourse, FILE* fp)
{
	pCourse->name = readStringFromFile(fp, "Error reading course name\n");
	if (!pCourse->name)
	{
		fclose(fp);
		return 0;
	}

	if (!readIntFromFile(&pCourse->code, fp, "Error reading code\n"))
	{
		free(pCourse->name);
		fclose(fp);
		return 0;
	}
	if (!readFloatFromFile(&pCourse->credits, fp, "Error reading credits\n"))
	{
		free(pCourse->name);
		fclose(fp);
		return 0;
	}
	return 1;
}
void	printCourse(const Course* pCourse)
{
	printf("%s-[code: %d , Credits: %.1f]\n", pCourse->name, pCourse->code, pCourse->credits);
}
void	printCourseV(void* val)
{
	printCourse((const Course*)val);
}
void	freeCourse(Course* pCourse)
{
	free(pCourse->name);

}
void	freeCourseV(void* val)
{
	freeCourse((Course*)val);
}