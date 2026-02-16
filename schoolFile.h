#pragma once
#include <stdio.h>
#include "MagicSchool.h"





int		saveSchoolToFileTXT(const MagicSchool* pSchool, const MagicFactory* pFactory, const char* fileName);
int		loadSchoolFromFileTXT(MagicSchool* pSchool, MagicFactory* pFactory,const char* fileName);

int		saveSchoolToFileB(const MagicSchool* pSchool, const MagicFactory* pFactory, const char* fileName);
int		loadSchoolFromFileB(MagicSchool* pSchool, MagicFactory* pFactory, const char* fileName);


int		saveHouseArrFileB(const MagicSchool* pS, int size, FILE* fp);
int		loadHouseArrFileB(MagicSchool* pS, int size, FILE* fp);

int		saveSpellArrFileB(const MagicSchool* pS, int size, FILE* fp);
int		loadSpellArrFromFileB(MagicSchool* pS, FILE* fp);

int		saveCourseArrFileB(const MagicSchool* pS, int size, FILE* fp);
int		loadCourseArrayFileB(MagicSchool* pS, int size, FILE* fp);

int		saveHouseArrFileTXT(const MagicSchool* pS, int size, FILE* fp);
int		loadHouseArrFileTXT(MagicSchool* pS, int size, FILE* fp);

int		saveSpellArrFileTXT(const MagicSchool* pS, int size, FILE* fp);
int		loadSpellArrFromFileTXT(MagicSchool* pS, FILE* fp);

int		saveCourseArrFileTXT(const MagicSchool* pS, int size, FILE* fp);
int		loadCourseArrayFileTXT(MagicSchool* pS, int size, FILE* fp);

int		createCourseArr(MagicSchool* pS);
int		createSpellArr(MagicSchool* pS);


