/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   : Danish Sharma
	ID     : 148201205
	Email  : dsharma115@myseneca.ca
	Section: BTP100NBB
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

struct Demographic {
	int dateOfBirth;
	double income;
	char country[31];
};

struct UserLogin {
	char name[31];
	char loginName[11];
	char password[9];
};

struct Account {
	int accountNumber;
	char accountType;
	struct UserLogin userLogin;
	struct Demographic demographic;
};


void getAccount(struct Account* account, const struct Account accountArr[], int ACCOUNT_MAX_SIZE);

void getUserLogin(struct Account* userLogin);

void getDemographic(struct Account* demographic);

void updateAccount(struct Account* account);

void updateUserLogin(struct Account* userLogin);

void updateDemographic(struct Account* demographic);

void passwordSecurity(struct Account* userLogin);

#endif // !ACCOUNT_H_