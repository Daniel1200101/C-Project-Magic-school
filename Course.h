#ifndef __COURSE__
#define __COURSE__

#define MAX_CREDIT 5
#define CODE_LENGTH_COURSE 5


typedef struct
{
    char*     name;
    int       code;
    float     credits;
}Course;



int	    initCourse(Course* pCourse, const Course* courseArr, int courseCount);
int		initCourseNoCode(Course* pCourse1);

int		isSameCourse(const Course* pCourse1, const Course* pCourse2);
int		isCourseCode(const Course* pCourse1,int code);



float   getCourseCredit();
int     getCourseCode(const Course* courseArr, int courseCount);
int		isCodeNumUnique(const Course* courseArr, int courseCount, int num);

int		saveCourseToFileTXT(const Course* pCourse, FILE* fp);
int		loadCourseFromFileTXT(Course* pCourse, FILE* fp);

int		saveCourseToFileB(const Course* pCourse, FILE* fp);
int		loadCourseFromFileB(Course* pCourse, FILE* fp);

void	printCourse(const Course* pCourse);
void	printCourseV(const void* val);
void	freeCourse(Course* pCourse);
void	freeCourseV(void* val);

#endif

