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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"
#include "accountTicketingUI.h"

void getAccount(struct Account* account, const struct Account accountArr[], int ACCOUNT_MAX_SIZE) {
	int run = 1, rand_num = 0, arr_index;

	while (run) {
		arr_index = findAccountIndexByAcctNum(82043 + rand_num, accountArr, ACCOUNT_MAX_SIZE, 0);

		if (arr_index == -1) {
			run = 0;
			account->accountNumber = 82043 + rand_num;
		}

		rand_num++;
	}
	
	printf("\nNew Account Data (Account#:%d)\n", account->accountNumber);
	printf("----------------------------------------\n");


	printf("Enter the account type (A=Agent | C=Customer): ");
	account->accountType = getCharOption("AC");

	printf("\n");
}

void getUserLogin(struct Account* userLogin) {

	int run = 1, len, i, space_or_nah = 1;

	printf("User Login Data Input\n");
	printf("----------------------------------------\n");

	// WHILE LOOP FOR LOGIN REQUIREMENT: NO SPACE OR TAB
	while (run) {

		space_or_nah = 1;

		printf("Enter user login (10 chars max): ");
		getCString(userLogin->userLogin.loginName, 1, 10);

		len = strlen(userLogin->userLogin.loginName);

		for (i = 0; i < len; i++) {
			if(isblank(userLogin->userLogin.loginName[i])){
				space_or_nah = 0;
			}
		// FOR END
		}

		if (space_or_nah) {
			run = 0;
		}
		else {
			printf("ERROR:  The user login must NOT contain whitespace characters.\n");
		}

	// WHILE END
	}

	run = 1;

	printf("Enter the display name (30 chars max): ");
	getCString(userLogin->userLogin.name, 1, 30);

	passwordSecurity(userLogin);

	printf("\n");
}

void getDemographic(struct Account* demographic) {

	int i, len;

	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");

	printf("Enter birth year (current age must be between 18 and 110): ");
	demographic->demographic.dateOfBirth = getIntFromRange(currentYear() - 110, currentYear() - 18);

	printf("Enter the household Income: $");
	demographic->demographic.income = getPositiveDouble();

	printf("Enter the country (30 chars max.): ");
	getCString(demographic->demographic.country, 1, 30);

	len = strlen(demographic->demographic.country);

	for (i = 0; i < len; i++) {
		demographic->demographic.country[i] = toupper(demographic->demographic.country[i]);
	}

	printf("\n");
}

// ============================================ MS4 ==============================================

void updateAccount(struct Account* account) {

	int run = 1, option;

	while (run) {
		printf("Account: %d - Update Options\n", account->accountNumber);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 3);

		if (option == 1) {
			printf("\n");
			printf("Enter the account type (A=Agent | C=Customer): ");
			account->accountType = getCharOption("AC");
		}
		else if (option == 2) {
			printf("\n");
			updateUserLogin(account);
		}
		else if (option == 3) {
			printf("\n");
			updateDemographic(account);
		}
		else {
			run = 0;
		}

	}
}

void updateUserLogin(struct Account* userLogin) {

	int run = 1, option;

	while (run) {
		printf("User Login: %s - Update Options\n", userLogin->userLogin.loginName);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", userLogin->userLogin.name);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 2);

		if (option == 1) {
			printf("\n");
			printf("Enter the display name (30 chars max): ");
			getCString(userLogin->userLogin.name, 1, 30);
			printf("\n");
		}
		else if (option == 2) {
			printf("\n");
			passwordSecurity(userLogin);
			printf("\n");
		}
		else {
			run = 0;
			printf("\n");
		}

	}
}

void updateDemographic(struct Account* demographic) {

	int run = 1, option, i , len;

	while (run) {
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demographic->demographic.income);
		printf("2) Country (current value: %s)\n", demographic->demographic.country);
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 2);

		if (option == 1) {
			printf("\nEnter the household Income: $");
			demographic->demographic.income = getPositiveDouble();
			printf("\n");
		}
		else if (option == 2) {
			printf("\nEnter the country (30 chars max.): ");
			getCString(demographic->demographic.country, 1, 30);

			len = strlen(demographic->demographic.country);

			for (i = 0; i < len; i++) {
				demographic->demographic.country[i] = toupper(demographic->demographic.country[i]);
			}

			printf("\n");
		}
		else {
			run = 0;
			printf("\n");
		}

	}
}

void passwordSecurity(struct Account* userLogin) {
	int run = 1, len, i, j, upper_counter = 0, lower_counter = 0, symbol_counter = 0, digit_counter = 0;
	char symbol_arr[9] = "!@#$%^&*";
	// WHILE LOOP FOR PASSWORD SECURITY
	while (run) {

		upper_counter = 0, lower_counter = 0, symbol_counter = 0, digit_counter = 0;

		printf("Enter the password (must be 8 chars in length): ");
		getCString(userLogin->userLogin.password, 8, 8);

		len = strlen(userLogin->userLogin.password);

		for (i = 0; i < len; i++) {
			if (isdigit(userLogin->userLogin.password[i])) {
				digit_counter++;
			}
			else if (isupper(userLogin->userLogin.password[i])) {
				upper_counter++;
			}
			else if (islower(userLogin->userLogin.password[i])) {
				lower_counter++;
			}
			else {
				for (j = 0; j < 8; j++) {
					if (userLogin->userLogin.password[i] == symbol_arr[j]) {
						symbol_counter++;
					}
				}
				// ELSE END
			}
			// FOR END	
		}

		if (digit_counter >= 2 && upper_counter >= 2 && lower_counter >= 2 && symbol_counter >= 2) {
			run = 0;
		}
		else {
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: %s\n", symbol_arr);
		}
		// WHILE END
	}
}





