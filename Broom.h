#ifndef __BROOM__
#define __BROOM__


#define CODE_LENGTH 3
#define MIN_SPEED 50
#define MAX_SPEED 100

typedef struct
{
	char*	nickName;
	int		numOfRaces;
	int		speed;// km per hour
	char	code[CODE_LENGTH + 1];
}Broom;


int		isSameBroom(const Broom* pBroom1, const Broom* pBroom2);
int		isBroomCode(const Broom* pBroom1, const char* code);
int		getBroomSpeed();


void    getBroomCode(char* code);
void	printBroom(const Broom* pBroom);
void	printBroomV(const void* val);



void	freeBroom(Broom* pBroom);
void	freeBroomV(void* val);

int		loadBroomFromFileB(Broom* pBroom, FILE* fp);
int		saveBroomToFileB(const Broom* pBroom, FILE* fp);


int		loadBroomFromFileTXT(Broom* pBroom, FILE* fp);
int		saveBroomToFileTXT(const Broom* pBroom, FILE* fp);

#endif

