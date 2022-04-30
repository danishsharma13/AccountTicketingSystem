/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   : Danish Sharma
	ID     : 148201205
	Email  : dsharma115@myseneca.ca
	Section: BTP100NBB
*/

#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include "account.h"
#include "ticket.h"
#include "commonHelpers.h"

// ========================= A2 MS2 =============================================

struct AccountTicketingData {
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

// ==============================================================================

void displayAccountSummaryHeader(void);

void displayAccountDetailHeader(void);

void displayAccountSummaryRecord(const struct Account* account);

void displayAccountDetailRecord(const struct Account* account);

// ============================ MS4 =============================================

void applicationStartup(struct AccountTicketingData* accountTicketingData);

int menuLogin(const struct AccountTicketingData* accountTicketingData);

void menuCustomer(const struct Account* account, struct Ticket ticket[], const int MAX_TICKET_SIZE);

void menuAgent(struct AccountTicketingData* accountTicketingData, const struct Account* account);

int findAccountIndexByAcctNum(int account_number, const struct Account accountsArr[], const int ACCOUNT_MAX_SIZE, int prompt_user);

void displayAllAccountSummaryRecords(const struct AccountTicketingData* accountTicketingData);

void displayAllAccountDetailRecords(const struct AccountTicketingData* accountTicketingData);

void displayCustomerTicketHeader(void);

void displayCustomerTicketDetail(const struct Ticket* ticket);

void displayCustomerTicketList(const struct Ticket ticket[], const int TICKET_MAX_SIZE);

void displayAgentTicketHeader(void);

void displayAgentTicketDetail(const struct Ticket* ticket);

void displayAgentTicketList(const struct Ticket tickets[], const int allOrOne, const int TICKET_MAX_SIZE, const int activeOrClosed);

int loginApprove(const struct AccountTicketingData* accountTicketingData);

int loadAccounts(struct Account accounts[], const int ACCOUNT_SIZE);

int loadTickets(struct Ticket tickets[], const int TICKET_SIZE);

void pauseExecution(void);

#endif // !ACCOUNT_TICKETING_UI_H_