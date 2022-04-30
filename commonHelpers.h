/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   : Danish Sharma
	ID     : 148201205
	Email  : dsharma115@myseneca.ca
	Section: BTP100NBB
*/

#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_


int currentYear(void);
void clearStanadardInputBuffer(void);

int getInteger(void);
int getPositiveInteger(void);
int getIntFromRange(int lower_bound, int upper_bound);

double getDouble(void);
double getPositiveDouble(void);

char getCharOption(const char valid_string[]);
void getCString(char* c_str, int min_num, int max_num);

#endif // !COMMON_HELPERS_H_