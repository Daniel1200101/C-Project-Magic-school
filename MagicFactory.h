#ifndef __MAGIC_FACTORY__
#define __MAGIC_FACTORY__

#include "GeneralList.h"

#include "Wand.h"
#include "Broom.h"


#define ERROR 0
#define FROM_FILE 1
#define FROM_USER 2



typedef struct
{
	LIST		wandList;
	LIST		broomList;
}MagicFactory;

int		initFactory(MagicFactory* pFactory);
void	initWand(Wand* pWand, MagicFactory* pFactory);
int		initBroom(Broom* pBroom, MagicFactory* pFactory);


int		addWand(MagicFactory* pFactory);
int		insertNewWandToList(LIST* pProductList, Wand* pWand);
Wand*   findWandByCode(const MagicFactory* pFactory, const char* code);
int		getWandCount(const MagicFactory* pFactory);
int		checkWandUniqueCode(const char* code, const MagicFactory* pFactory);
void	printWands(const MagicFactory* pFactory);
void    removeWand(MagicFactory* pFactory, Wand* wand);
Wand*	chooseWandFromList(MagicFactory* pFactory, const char* msg);//factory


int		addBroom(MagicFactory* pFactory);
int		insertNewBroomToList(LIST* pProductList,Broom* pBroom);
Broom*  findBroomByCode(const MagicFactory* pFactory, const char* code);
int		getBroomCount(const MagicFactory* pFactory);
int		checkBroomUniqueCode(const char* code, const MagicFactory* pFactory);
void	printBrooms(const MagicFactory* pFactory);


void	printMagicFactory(const MagicFactory* pF);
void	freeFactory(MagicFactory* pFactory);


#endif