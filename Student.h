#ifndef __STUDENT__
#define __STUDENT__


#include "Wand.h"
#include "Course.h"

#define MAX_YEAR 7
#define MIN_YEAR 1

#define CRETIDS_PER_YEAR 10
#define ID_LENGTH 5

typedef enum {
	eHarry_Potter, eHermione_Granger, eRon_Weasley, eNofFavorite
} eFavoriteWizard;

static const char* FavoriteWizardStr[eNofFavorite];

typedef struct
{
	char*		name;
	int			ID;
	float		totalCredits;
	int			year;
	Wand		wand;
	int*		courseCodeArr;//every student have array of all the courses that he learned, the code of that course
	int			numOfCourses;
	eFavoriteWizard	favorite;
}Student;
int		 initStudentNoID(Student* pStudent);
void     addCredits(Student* pStudent, const Course* course);
eFavoriteWizard		getFavoriteWizard();

int		compareStudentByCredits(const void* student1, const void* student2);
int		compareStudentByWandCode(const void* student1, const void* student2);
int		compareStudentByNameLength(const void* student1, const void* student2);
int		compareStudentByYear(const void* student1, const void* student2);

int		addCourseCode(Student* pStudent, Course* course);
int		uniqueCode(const int* courseArr, int size, int code);

void	getCorrectYear(int year);

int		saveStudentToFileTXT(const Student* pStudent, FILE* fp);
int		loadStudentFromFileTXT(Student* pStudent, FILE* fp);

int		saveStudentToFileB(const Student* pStudent, FILE* fp);
int		loadStudentFromFileB(Student* pStudent, FILE* fp);

int		saveCourseCodeArrToFileB(const int* courseArr, int size, FILE* fp);
int		loadCourseCodeArrFromFileB(int* courseArr, int size, FILE* fp); /// * or 2 **?

int		saveCourseArrToFileTXT(const int* courseArr, int size, FILE* fp);
int		loadCourseArrFromFileTXT(int* courseArr, int size, FILE* fp); /// * or 2 **?

void    printCourseCodeArr(int* courseCodeArr, int	numOfCourses);
void	printStudentPtr(const void* pStudentPtr);
void    printStudent(const Student* pStudent);
void    printStudentV(const void* val);

void	freeStudentV(void* val);
void	freeStudentPtr(void* pStudentPtr);
void    freeStudent(Student* pStudent);

#endif