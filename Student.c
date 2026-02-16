#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"
#include "General.h"
#include "FileHelper.h"

static const char* FavoriteWizardStr[eNofFavorite]
= { "Harry Potter","Hermione Granger","Ron Weasley" };



int		initStudentNoID(Student* pStudent)
{
	pStudent->name = getStrExactName("Enter student name");
	if (!pStudent->name)
		return 0;
	pStudent->year = 1;
	pStudent->totalCredits = 0;
	pStudent->numOfCourses = 0;
	pStudent->courseCodeArr = NULL;
	pStudent->favorite = getFavoriteWizard();
	return 1;
}
void	getCorrectYear(int year)
{
	int temp;
	int ok = 0;

	do {
		printf("Enter year of studying between %d to %d\t",
			MIN_YEAR, MAX_YEAR);
		scanf("%d", &temp);
		if (temp > MAX_YEAR || temp < MIN_YEAR)
			printf("Error try again\n");
		else
			ok = 1;
	} while (!ok);
	year = temp;
}
eFavoriteWizard		getFavoriteWizard()
{
	int option;
	printf("\n\n");
	do {
		printf("Please choose your favorite wizard\n");
		for (int i = 0; i < eNofFavorite; i++)
			printf("%d for %s\n", i, FavoriteWizardStr[i]);
		scanf("%d", &option);
	} while (option < 0 || option >= eNofFavorite);
	getchar();
	return (eFavoriteWizard)option;
}


int		compareStudentByCredits(const void* student1, const void* student2)/////////////////////
{
	const Student* pStudent1 = *(const Student**)student1;
	const Student* pStudent2 = *(const Student**)student2;
	if (pStudent1->totalCredits - pStudent2->totalCredits < 0) {
		return -1; // student1 credits < student2 credits
	}
	else if (pStudent1->totalCredits - pStudent2->totalCredits > 0) {
		return 1; // student1 credits > student2 credits
	}
	else {
		return 0; // student1 credits == student2 credits
	}
}
int		compareStudentByWandCode(const void* student1, const void* student2)
{
	const Student* pStudent1 = *(const Student**)student1;
	const Student* pStudent2 = *(const Student**)student2;
	return strcmp(pStudent1->wand.code,pStudent2->wand.code);
}
int		compareStudentByNameLength(const void* student1, const void* student2)
{
	const Student* pStudent1 = *(const Student**)student1;
	const Student* pStudent2 = *(const Student**)student2;

	if (strlen(pStudent1->name) - strlen(pStudent2->name) > 0) 
	{
		return 1; 
	}
	else if (strlen(pStudent1->name) - strlen(pStudent2->name) < 0) 
	{
		return -1;
	}
	else 
	{
		return 0; 
	}

}
int		compareStudentByYear(const void* student1, const void* student2)
{
	const Student* pStudent1 = *(const Student**)student1;
	const Student* pStudent2 = *(const Student**)student2;
	return pStudent1->year - pStudent2->year;
}
int		uniqueCode(const int* courseArr,int size,int code)
{
	for (int i = 0; i < size; i++) {
		if (courseArr[i] == code) {
			return 0; // Code is not unique
		}
	}
	return 1; // Code is unique


}
int	addCourseCode(Student* pStudent, Course* course)
{
	
	pStudent->courseCodeArr = (int*)realloc(pStudent->courseCodeArr, sizeof(int) * (pStudent->numOfCourses + 1));
	if (pStudent->courseCodeArr == NULL)
	{
		// Memory allocation failed
		printf("Memory allocation failed\n");
		return 0;
	}
	
	if (!uniqueCode(pStudent->courseCodeArr, pStudent->numOfCourses, course->code)) 
	{
		printf("\nStudent already passed that course\n");
		return 0;
	}
	
	// Add the new number at the end of the array
	pStudent->courseCodeArr[pStudent->numOfCourses] = course->code;
	pStudent->numOfCourses++;
	addCredits(pStudent, course);
	return 1;
}

void     addCredits(Student* pStudent, const Course* course)
{
	pStudent->totalCredits += course->credits;
	if (pStudent->totalCredits >= pStudent->year * CRETIDS_PER_YEAR)
	{
		if (pStudent->year != MAX_YEAR)
		{
			pStudent->year++;
			printf("Congratulation you have passed to %d\n", pStudent->year);
		}

	}
	printf("\nGood job %.1f credits has been added\n\n", pStudent->totalCredits);
}


int		saveStudentToFileTXT(const Student* pStudent, FILE* fp)
{
		if (!pStudent)
			return 0;
		fprintf(fp, "%s\n", pStudent->name);
		fprintf(fp, "%d\n", pStudent->ID);
		fprintf(fp, "%d\n", pStudent->year);
		fprintf(fp, "%f\n", pStudent->totalCredits);
		fprintf(fp, "%s\n", FavoriteWizardStr [pStudent->favorite]);
		fprintf(fp, "%d\n", pStudent->numOfCourses);
		if (!saveCourseArrToFileTXT(pStudent->courseCodeArr, pStudent->numOfCourses, fp))
			return 0;
		if (!saveWandToFileTXT(&pStudent->wand, fp))
			return 0;
		return 1;
}
int		saveCourseCodeArrToFileB(const int* courseArr, int size, FILE* fp) /// * or 2 **?
{
	for (int i = 0; i < size; i++)
	{
		if (!writeIntToFile(courseArr[i], fp, "Error write \n"))
		{
			return 0;
		}
	}
	return 1;
}
int		loadCourseCodeArrFromFileB(int* courseArr, int size, FILE* fp) /// * or 2 **?
{
	
	if (!courseArr)
	{
		return 0;
	}
	for (int i = 0; i < size; i++)
	{
		if (!readIntFromFile(&courseArr[i], fp, "Error write \n"))
		{
			printf("Failed to read course code from file.\n");
			free(courseArr);
			return 0;
		}
	}
	return 1;
	
}
int		saveCourseArrToFileTXT(const int* courseArr, int size, FILE* fp) /// * or 2 **?
{
	for (int i = 0; i < size; i++) {
		if (!fprintf(fp, "%d\n", courseArr[i])) {
			return 0; // Error writing to file
		}
	}
	return 1; // Successfully saved course array to file
}
int		loadStudentFromFileTXT(Student* pStudent, FILE* fp)
{
//	char favoriteStr[20]; // Assuming max favorite wizard string length is 20 characters
	char temp[MAX_STR_LEN];
	if (!pStudent)
		return 0;

	myGets(temp, MAX_STR_LEN, fp);
	pStudent->name = getDynStr(temp);
	pStudent->courseCodeArr = NULL;
	if (!(pStudent->name))
	{
		return 0;
	}

	if (fscanf(fp, "%d\n", &pStudent->ID) != 1)
	{
		free(pStudent->name);
		printf("Failed to read student id from file.\n");
		return 0;
	}
	if (fscanf(fp, "%d\n", &pStudent->year) != 1)
	{
		free(pStudent->name);
		printf("Failed to read student year from file.\n");
		return 0;
	}
	if (fscanf(fp, "%f\n", &pStudent->totalCredits) != 1)
	{
		free(pStudent->name);
		printf("Failed to read academic credits from file.\n");
		return 0;
	}
	myGets(temp, MAX_STR_LEN, fp);
	if (!temp)
	{
		free(pStudent->name);
		printf("Failed to read\n");
		return 0;
	}

	// Convert difficulty string to enum
	eFavoriteWizard favorite1 = eNofFavorite;
	for (int i = 0; i < eNofFavorite; i++) {
		if (strcmp(temp, FavoriteWizardStr[i]) == 0)
		{
			favorite1 = i;
			break;
		}
	}
	// Assign the difficulty outside of the else block
	pStudent->favorite = favorite1;
	if (fscanf(fp, "%d", &pStudent->numOfCourses) != 1)
	{
		free(pStudent->name);
		printf("Failed to read num of courses from file.\n");
		return 0;
	}
	pStudent->courseCodeArr = (int*)malloc(sizeof(int) * pStudent->numOfCourses);
	if (!loadCourseArrFromFileTXT(pStudent->courseCodeArr, pStudent->numOfCourses, fp))
		return 0;
	if (!loadWandFromFileTXT(&pStudent->wand, fp))
		return 0;

	return 1;
}

int		loadCourseArrFromFileTXT(int* courseArr, int size, FILE* fp) /// * or 2 **?
{
	
	if (!courseArr)
	{
		return 0;
	}
	for (int i = 0; i < size; i++)
	{
		if (fscanf(fp, "%d", &courseArr[i]) != 1)
		{
			printf("Failed to read course code from file.\n");
			free(courseArr);
			return 0;
		}
	}
	return 1;
}


int		saveStudentToFileB(const Student* pStudent, FILE* fp)
{
	if (!writeStringToFile(pStudent->name, fp, "Error write  name\n"))
	{
		
		return 0;
	}

	if (!writeIntToFile(pStudent->ID, fp, "Error write ID\n"))
	{
		return 0;
	}
	if (!writeFloatToFile(pStudent->totalCredits, fp, "Error write \n"))
	{
		return 0;
	}
	if (!writeIntToFile(pStudent->year, fp, "Error write \n"))
	{
		return 0;
	}
	if (!saveWandToFileB(&pStudent->wand, fp))
	{
		return 0;
	}

	if (!writeIntToFile(pStudent->numOfCourses, fp, "Error write \n"))
	{
		return 0;
	}
	if (!saveCourseCodeArrToFileB(pStudent->courseCodeArr, pStudent->numOfCourses, fp))
	{
		return 0;
	}
	if (!writeStringToFile(FavoriteWizardStr[pStudent->favorite], fp, "Error write  name\n"))
	{
		fclose(fp);
		return 0;
	}
	return 1;
}



int		loadStudentFromFileB(Student* pStudent, FILE* fp)
{
	pStudent->courseCodeArr = NULL;

	pStudent->name = readStringFromFile(fp, "Error reading  name\n");
	if (!pStudent->name)
	{
		return 0;
	}
	if (!readIntFromFile(&pStudent->ID, fp, "Error reading \n"))
	{
		free(pStudent->name);
		return 0;
	}
	if (!readFloatFromFile(&pStudent->totalCredits, fp, "Error write \n"))
	{
		free(pStudent->name);
		return 0;
	}
	if (!readIntFromFile(&pStudent->year, fp, "Error reading \n"))
	{
		free(pStudent->name);
		return 0;
	}
	if (!loadWandFromFileB(&pStudent->wand, fp))
	{
		free(pStudent->name);
		return 0;
	}
	if (!readIntFromFile(&pStudent->numOfCourses, fp, "Error write \n"))
	{
		free(pStudent->name);
		return 0;
	}
	pStudent->courseCodeArr = (int*)malloc(sizeof(int) * pStudent->numOfCourses);
	if (!loadCourseCodeArrFromFileB(pStudent->courseCodeArr, pStudent->numOfCourses, fp))
	{
		free(pStudent->name);
		return 0;
	}
	
	char* temp;
	temp= readStringFromFile(fp, "Error reading  name\n");
	if (!temp)
	{
		free(pStudent->name);
		return 0;
	}
	eFavoriteWizard favorite1 = eNofFavorite;
	for (int i = 0; i < eNofFavorite; i++) {
		if (strcmp(temp, FavoriteWizardStr[i]) == 0)
		{
			favorite1 = i;
			break;
		}
	}
	// Assign the difficulty outside of the else block
	pStudent->favorite = favorite1;
	return 1;

}
void	printStudent(const Student* student)/////////////////////
{
	printf("Student %s:\n", student->name);
	printf("ID: %d\n", student->ID);
	printf("Year: %d\n", student->year);
	printf("Total academic Credits: %.1f\n", student->totalCredits);
	printf("The code of courses he learned:\n");
	printCourseCodeArr(student->courseCodeArr, student->numOfCourses);
	printf("Wand:");
	printWand(&student->wand);
	printf("Favorite Wizard - %s\n", FavoriteWizardStr[student->favorite]);
}

void   printCourseCodeArr(int* courseCodeArr, int	numOfCourses) // Should he print the course name or the code that he passed?
{
	for (int i = 0; i < numOfCourses; i++)
	{
		printf("%d. %d\n", i + 1, courseCodeArr[i]);
	}
}
void    printStudentV(void* val)
{
	printStudent((const Student*)val);
}

void	printStudentPtr(const void* pStudentPtr)
{
	const Student* temp = (Student*)pStudentPtr;
	printStudent(temp);
}

void	freeStudentPtr(void* pStudentPtr)
{
	Student* temp = (Student*)pStudentPtr;
	freeStudent(temp);

}

void    freeStudent(Student* pStudent)/////////////////////////////////////////////
{
	// Free the dynamically allocated name
	free(pStudent->name);
	// Free the dynamically allocated courseCodeArr array
	//free(pStudent->courseCodeArr);
}
void	freeStudentV(void* val)
{
	freeStudent((Student*)val);
}