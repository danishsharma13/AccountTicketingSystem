/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   : Danish Sharma
	ID     : 148201205
	Email  : dsharma115@myseneca.ca
	Section: BTP100NBB
*/

#ifndef TICKET_H_
#define TICKET_H_

#include "account.h"

struct Message {
	char accountType;
	char name[31];
	char messageDetail[151];
};

struct Ticket {
	int uniqueNumber;
	int accountNumber;
	int statusIndicator;
	char subjectLine[31];
	int counter;
	struct Message messages[20];
};

void getTicket(const struct Account* account, struct Ticket* ticket, const struct Ticket ticketArr[], const int TICKET_MAX_SIZE);

int findTicketByUniqNum(int ticketNum, const struct Ticket ticket[], int TICKET_MAX_SIZE);

void modifyTicket(const struct Account* account, struct Ticket* ticket);

void manageTicket(const struct Account* account, struct Ticket* ticket);

#endif // !TICKET_H_