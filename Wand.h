#ifndef __WAND__
#define __WAND__

#define CODE_LENGTH 3
#define MIN_YEAR_MFG 1800
#define MAX_YEAR_MFG 2024

typedef struct
{
	int mfgYear;//manufacturing year
	char	code[CODE_LENGTH + 1];
}Wand;


int		isSameWand(const Wand* pWand1, const Wand* pWand2);
int		isWandCode(const Wand* pWand1, const char* code);
int		getWandMFGYear();

int		compareWandByCode(const void* code1, const void* code2);


void    getWandCode(char* code);
void	printWand(const Wand* pWand);
void	printWandV(const void* val);


int		saveWandToFileB(const Wand* pWand, FILE* fp);
int		loadWandFromFileB(Wand* pWand, FILE* fp);

int		saveWandToFileTXT(const Wand* pWand, FILE* fp);
int		loadWandFromFileTXT(Wand* pWand, FILE* fp);

void	freeWand(Wand* pWand);
void	freeWandV(void* val);



#endif