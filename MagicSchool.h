#ifndef __MAGIC_SCHOOL__
#define __MAGIC_SCHOOL__

#include "House.h"
#include "Spell.h"
#include "MagicFactory.h"
#include "Course.h"
#include "General.h"

#define NAME "HOGWARTS"
#define LENGTH 9
#define NAME_PRINCIPAL "DUMBLEDORE"
#define LENGTH_PRINCIPAL 11
#define DUEL_ROUNDS 3

typedef struct
{
	char		name[LENGTH];
	char	    principal[LENGTH_PRINCIPAL];
	House		housesArr[eNofHouses];
	Spell**		spellsArr;
	int			spellCount;
	Course*	    coursesArr;
	int			numOfCourses;
}MagicSchool;

void	initMagicSchool(MagicSchool* pSchool);
void	initMagicSchoolHouses(MagicSchool* pSchool);
int	    initStudent(Student* pStudent, const MagicSchool* pSchool,MagicFactory* pFactory);//school-???

int		addSpell(MagicSchool* pSchool);
int		addCourse(MagicSchool* pSchool);
int		addStudentToMagicalSchool(MagicSchool* pSchool,MagicFactory* pFactory);
int		totalStudentInSchool(const MagicSchool* pSchool);
Course* findCourse(Course* coursesArr, int numOfCourses, const char* msg);
Course* findCourseByCode(Course* coursesArr, int numOfCourses,int code);
void	findStudentInHouse(const MagicSchool* pSchool);
void	sortStudentsInHouse(MagicSchool* pSchool);
Spell* chooseSpellFromArr(const MagicSchool* pSchool);
int		spellDuel(const MagicSchool* pSchool);
eHouseName		getHouseName();

void    setHeadTOHouse(MagicSchool* pSchool);
int     getStudentID(const MagicSchool* pSchool);//school
int		isIDNumUnique(const MagicSchool* pSchool, int num);//school

int     sortingHat();
int     addCourseCodeToStudent(MagicSchool* sSchool);

int studentsForDuel(const MagicSchool* pSchool, Student** s1, Student** s2, char* msg);
int		broomRace(const MagicSchool* pSchool,MagicFactory* pFactory);


void	printMagicSchool(const MagicSchool* pSchool);
void	printHousesArr(const House* houseArr, int size);
void	printCoursesArr(const Course* coursesArr, int numOfCourses);
void	printSpellsArr(const Spell** pArr, int size);
void    printSong();

void	freeSpellArr(Spell** arr, int size);
void	freeHouseArr(House* arr, int numOfHouses);
void	freeCourseArr(Course* arr, int size);
void	freeMagicSchool(MagicSchool* pSchool);

#endif