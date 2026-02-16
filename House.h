#ifndef __HOUSE__
#define __HOUSE__

#include "Student.h"

//struct Student;

typedef enum { eNone, eCredits, eWandCode, eNameLen, eYear, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];

typedef enum {
    eGryffindor, eRavenclaw, eSlytherin, eHufflepuff, eNofHouses
} eHouseName;

//static const char* HouseNames[eNofHouses];

static const char* HouseNames[eNofHouses]
= { "Gryffindor", "Ravenclaw", "Slytherin" ,"Hufflepuff" };
typedef struct
{
   Student*    headOfHouse;
    eHouseName houseName;
   Student** studentsArr;
    int        studentsNum;
    eSortOption	studentSortOpt;
} House;

void	initHouse(House* pHouse, eHouseName name);

eSortOption showSortMenu();

void	 sortStudent(House* pHouse);
int		 addStudentToHouse(House* pHouse,Student* pStudent);

Student* findHeadOfHouse(const House* pHouse);
void	 findStudent(const House* pHouse);

void     setHeadOfHouse(House* pHouse);
int      createStudentArr(House* pHouse);//fileB

Student* findStudentByID(Student** studentsArr, int numOfStudents, int id);
Student* findStudentGeneral(const House* pHouse);


int      loadStudentArrFromFileB(House* pHouse, FILE* fp);
int      loadStudentArrFromFileTXT(House* pHouse, FILE* fp);

int		 saveHouseToFileB(const House* pHouse, FILE* fp);
int	  	 loadHouseFromFileB(House* pHouse, FILE* fp);

int	     saveHouseToFileTXT(const House* pHouse, FILE* fp);
int		 loadHouseFromFileTXT(House* pHouse, FILE* fp);

void	 printStudentArr(const Student** arr, int studentsCount);
void     printHouse(const House* pHouse);
void     printHouseV(void* val);

void     freeHouse(House* pHouse);
void	 freeStudentArr(Student** arr, int size);

#endif