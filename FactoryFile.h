#pragma once
#include "MagicFactory.h"

int		loadWandListFromTXT(MagicFactory* pFactory, FILE* fp);
int		loadBroomListFromTXT(MagicFactory* pFactory, FILE* fp);
int		loadWandListFromB(MagicFactory* pFactory, FILE* fp);
int		loadBroomListFromB(MagicFactory* pFactory, FILE* fp);

int		saveWandListToB(const MagicFactory* pFactory, FILE* fp);
int		saveBroomListToB(const MagicFactory* pFactory, FILE* fp);
int		saveBroomListToTXT(const MagicFactory* pFactory, FILE* fp);
int		saveWandListToTXT(const MagicFactory* pFactory, FILE* fp);

int		saveFactoryToFileB(const MagicFactory* pFactory, FILE* fp);
int		saveFactoryToFileTXT(const MagicFactory* pFactory, FILE* fp);

int		loadFactoryFromFileB(MagicFactory* pFactory, FILE* fp);
int		loadFactoryFromFileTXT(MagicFactory* pFactory, FILE* fp);