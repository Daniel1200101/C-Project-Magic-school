#ifndef __SPELL__
#define __SPELL__

#define FORBIDDEN_SPELL "AVADA KADABRA"
#define MAX_YEAR_USE 6

typedef unsigned char BYTE;


typedef enum {
	eEasy, eMedium, eHard, eNofSpellDifficulty
} eSpellDifficulty;

static const char* SpellDiffStr[eNofSpellDifficulty];

typedef struct
{
	char* spellName;
	eSpellDifficulty	difficulty;
	int		minYearUse;
	int		power;

}Spell;

int		isSameSpell(const Spell*pSpell1, const Spell* pSpell2);
int		isSpellName(const Spell* pSpell1, const char* name);
int		initSpell(Spell* pSpell, const Spell** spellArr, int spellCount);

int		checkUniqueName(const Spell** spellArr, int spellCount, const char* name);

int		saveSpellToFileTXT(const Spell* pSpell, FILE* fp);
int		loadSpellFromFileTXT(Spell* pSpell, FILE* fp);

int		saveSpellToFileBCompressed(const Spell* pSpell, FILE* fp);
int		loadSpellFromFileBCompressed(Spell* pSpell, FILE* fp);

eSpellDifficulty  getSpellDifficulty();
int			getMinYearOfUse();
int			getSpellName(Spell* pSpel);
const char* GetSpellDiffStr(int type);

void	printSpell(const Spell* pSpell);
void	printSpellV(const void* val);
void	printSpellPtr(void* pSpellPtr);

void	freeSpell(Spell* pSpell);
void	freeSpellV(void* val);
void	freeSpellPtr(void* pSpellPtr);

#endif

