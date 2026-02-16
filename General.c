#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "General.h"

int checkIDLength(int id)
{
	int count = 0;

	// If the number is 0, it has one digit
	if (id == 0) {
		return 1;
	}

	// Count digits by repeatedly dividing the number by 10
	while (id != 0) {
		id /= 10;
		count++;
	}

	return count;
}

char* getStrExactName(const char* msg)
{
	char* str;
	char temp[MAX_STR_LEN];
	printf("%s\t", msg);
	myGets(temp, MAX_STR_LEN, stdin);

	str = getDynStr(temp);
	return str;
}

char* getDynStr(char* str)
{
	char* theStr;
	theStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (!theStr)
		return NULL;

	strcpy(theStr, str);
	return theStr;
}

int generateRandomNumber(int num) 
{
	// Generate a random number between 0 and 99
	int randomNumber = rand() % num;

	return randomNumber;
}
int equalStrIgnoreCase(const char* s1, const char* s2) {
	while (*s1 && *s2) {
		if (toupper(*s1) != toupper(*s2)) {
			return 0; // Characters differ, strings are not equal
		}
		s1++;
		s2++;
	}
	return (*s1 == '\0' && *s2 == '\0'); // Check if both strings ended at the same time
}
char* myGets(char* buffer, int size, FILE* source)
{
	char* ok;
	if (buffer != NULL && size > 0)
	{
		do {
			ok = fgets(buffer, size, source);
		} while (ok && ((strlen(buffer) <= 1) && (isspace(buffer[0]))));
		if (ok)
		{
			char* back = buffer + strlen(buffer);
			//trim end spaces
			while ((buffer < back) && (isspace(*--back)));
			*(back + 1) = '\0';
			return buffer;
		}
		buffer[0] = '\0';
	}
	return NULL;
}



void generalArrayFunction(void* arr, int size, int typeSize, void(*func)(void* element))
{
	for (int i = 0; i < size; i++)
		func((char*)(arr)+i * typeSize);

}
