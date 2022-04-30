/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   : Danish Sharma
	ID     : 148201205
	Email  : dsharma115@myseneca.ca
	Section: BTP100NBB
*/
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "commonHelpers.h"

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStanadardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}

int getInteger(void) {
	int value, run = 1;
	char newLine;

	while (run) {
		scanf("%d%c", &value, &newLine);

		if (newLine != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else {
			run = 0;
		}
	}

	return value;
}

int getPositiveInteger(void) {
	int value, run = 1;

	while (run) {
		value = getInteger();

		if (value >= 0) {
			run = 0;
		}
		else {
			printf("ERROR: Value must be positive or zero: ");
		}

	}
	return value;
}

double getDouble(void) {
	int run = 1;
	double value;
	char newLine;

	while (run) {
		scanf("%lf%c", &value, &newLine);

		if (newLine != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
		else {
			run = 0;
		}
	}
	return value;
}

double getPositiveDouble(void) {
	int run = 1;
	double value;

	while (run) {
		value = getDouble();

		if (value > 0) {
			run = 0;
		}
		else {
			printf("ERROR: Value must be a positive double floating-point number: ");
		}

	}
	return value;
}

int getIntFromRange(int lower_bound, int upper_bound) {
	char newLine = 'a';
	int value;

	while (newLine != '\n') {
		scanf("%d%c", &value, &newLine);

		if (newLine != '\n') {
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (value > upper_bound || value < lower_bound){
			newLine = 'a';
			printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
		}
	}

	return value;
}

char getCharOption(const char valid_string[]) {
	int run = 1, i, bool = 1, count = 0;
	char single_char = 'x', char_arr[21];

	while (run) {
		scanf("%21s", char_arr);

		count = strlen(char_arr);

		if (count == 1) {
			single_char = char_arr[0];
			for (i = 0; valid_string[i] != '\0'; i++) {
				if (valid_string[i] == single_char) {
					run = 0;
					bool = 0;
				}
			}

		}

		count = 0;
		clearStanadardInputBuffer();

		if (bool) {
			printf("ERROR: Character must be one of [%s]: ", valid_string);
		}

	}

	return single_char;
}

void getCString(char* c_str, int min_num, int max_num) {
	char string_arr[151];
	int run = 1, count = 0;

	while (run) {
		scanf("%151[^\n]", string_arr);

		count = strlen(string_arr);


		if (count <= max_num && count >= min_num) {
			strcpy(c_str, string_arr);
			run = 0;

		}
		else if (min_num == max_num && count != max_num) {
			printf("ERROR: String length must be exactly %d chars: ", max_num);
		}
		else if (count > max_num) {
			printf("ERROR: String length must be no more than %d chars: ", max_num);
		}
		else {
			printf("ERROR: String length must be between %d and %d chars: ", min_num, max_num);
		}

		clearStanadardInputBuffer();
		count = 0;
	}


}
