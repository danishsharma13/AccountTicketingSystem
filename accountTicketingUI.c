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
#include <string.h>

#include "account.h"
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "ticket.h"

void displayAccountSummaryHeader(void) {
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountDetailHeader(void) {
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountSummaryRecord(const struct Account* account) {
	
	char customer[] = "CUSTOMER", agent[] = "AGENT", empty_string[9];

	if (account->accountType == 'C') {
		strcpy(empty_string, customer);
	}
	else if (account->accountType == 'A') {
		strcpy(empty_string, agent);
	}

	printf("%05d %-9s %5d\n", account->accountNumber, empty_string, account->demographic.dateOfBirth);
}

void displayAccountDetailRecord(const struct Account* account) {
	
	char customer[] = "CUSTOMER", agent[] = "AGENT", empty_string[9], hidden_pass[9];
	int i;


	if(account->accountType == 'C') {
		strcpy(empty_string, customer);
	}
	else if (account->accountType == 'A') {
		strcpy(empty_string, agent);
	}

	strcpy(hidden_pass, account->userLogin.password);

	for (i = 1; i <= 9; i++) {
		if (i % 2 == 0) {
			hidden_pass[i - 1] = '*';
		}
	}


	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %8s\n", account->accountNumber, empty_string, account->demographic.dateOfBirth, account->demographic.income, account->demographic.country, account->userLogin.name, account->userLogin.loginName, hidden_pass);
}

// ============================================= A1 MS4 =============================================

void applicationStartup(struct AccountTicketingData* accountTicketingData) {
	int login_exit, run = 1;

	while (run) {

		loadAccounts(accountTicketingData->accounts, accountTicketingData->ACCOUNT_MAX_SIZE);
		loadTickets(accountTicketingData->tickets, accountTicketingData->TICKET_MAX_SIZE);
	
		login_exit = menuLogin(accountTicketingData);

		// If statement to exit the application or Login into C or A
		if (accountTicketingData->accounts[login_exit].accountType == 'C') {
			printf("\n");
			menuCustomer(&accountTicketingData->accounts[login_exit], accountTicketingData->tickets, accountTicketingData->TICKET_MAX_SIZE);
		}
		else if (accountTicketingData->accounts[login_exit].accountType == 'A'){
			printf("\n");
			menuAgent(accountTicketingData, &accountTicketingData->accounts[login_exit]);

		}
		else {
			run = 0;
		}
	}
}

int menuLogin(const struct AccountTicketingData* accountTicketingData) {
	
	int login_exit, run = 1, arr_index = -1;
	char confirmation;

	// While loop to check either to login or exit application.
	while (run) {
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");
		login_exit = getIntFromRange(0, 1);

		// If statement to check login_exit is 0, then ask user if he/she really wants to quit?
		// Else statment to check login_exit is 1, and user wants to login in an account.
		if (login_exit == 0) {

			printf("\n");
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			confirmation = getCharOption("yYnN");
			printf("\n");

			if (confirmation == 'y' || confirmation == 'Y') {
				arr_index = -1;
				run = 0;
				printf("==============================================\n");
				printf("Account Ticketing System - Terminated\n");
				printf("==============================================\n");


			}
		// IF END Login_exit = 0
		}
		else {
			arr_index = loginApprove(accountTicketingData);

			if (arr_index != -1) {
				run = 0;
			}
			
		// ELSE END Login_exit = 1
		}
	// WHILE END run
	}

	return arr_index;
}

void menuCustomer(const struct Account* account, struct Ticket ticket[], const int TICKET_MAX_SIZE) {
	int run = 1, option, i, j, run2 = 1, ticket_full = 1, ticket_number, ticket_not_found = 1, ticket_closed = 0, counter = 0;
	FILE* fp = NULL;



	while (run) {
		ticket_full = 1;
		ticket_not_found = 1;
		run2 = 1;
		ticket_closed = 0;
		counter = 0;
		fp = NULL;
		struct Ticket ticket_arr[17] = { {0} };

		// copy only the ticketing data regarding the account in the parameter
		for (i = 0; i < TICKET_MAX_SIZE; i++) {
			if (ticket[i].uniqueNumber != 0 && strcmp(account->userLogin.name, ticket[i].messages[0].name) == 0) {
				for (j = 0; j < TICKET_MAX_SIZE; j++) {
					if (ticket_arr[j].uniqueNumber == 0) {
						ticket_arr[j] = ticket[i];
						break;
					}
				}
			}
		}

		// options for user to choose from, split into if-else if statements
		printf("CUSTOMER: %s (%d)\n", account->userLogin.name, account->accountNumber);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		option = getIntFromRange(0, 4);

		if (option == 1) {
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(account);
			printf("\n");
			pauseExecution();
		// IF END option 1
		}
		else if (option == 2) {
			// loop through ticket array to find empty ticket space and call getTicket to populate that space
			for (i = 0; i < TICKET_MAX_SIZE; i++) {
				if (ticket[i].uniqueNumber == 0) {
					getTicket(account, &ticket[i], ticket, TICKET_MAX_SIZE);
					printf("\n");
					printf("*** New ticket created! ***\n\n");
					ticket_full = 0;
					break;
				}
			}

			// If none ticketing space was found, then display an error
			if (ticket_full) {
				printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
			}
			pauseExecution();
			// ELSE IF END Option 2
		}
		else if (option == 3) {
			printf("\n");
			while (run2) {
				printf("Enter ticket number: ");
				ticket_number = getPositiveInteger();
				printf("\n");

				// find the ticket number that user input, check if the all ticket array matches, then check with the ticket array specifically created for the user data, then call the modifyTicket function to modify ticket.
				for (i = 0; i < TICKET_MAX_SIZE; i++) {
					if (ticket_arr[i].uniqueNumber == ticket_number && ticket_arr[i].statusIndicator == 1) {
						for (j = 0; j < TICKET_MAX_SIZE; j++) {
							if (ticket_arr[i].uniqueNumber == ticket[j].uniqueNumber) {
								modifyTicket(account, &ticket[j]);
								ticket_not_found = 0;
								run2 = 0;
								i = TICKET_MAX_SIZE;
								break;
							}
						}
					}
					else if (ticket_arr[i].uniqueNumber == ticket_number && ticket_arr[i].statusIndicator == 0) {
						ticket_closed = 1;
					}
				}
				
				// if ticket_closed, then no changes allowed display corresponding error, if ticket not found or is not user's ticket, display corresponding error
				if (ticket_closed) {
					printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
					run2 = 0;
				}
				else if (ticket_not_found) {
					printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
					run2 = 0;
				}
			

			// WHILE END run2
			}
			pauseExecution();
			// ELSE IF END Option 3
		}
		else if (option == 4) {
			printf("\n");
			displayCustomerTicketList(ticket_arr, TICKET_MAX_SIZE);
			// ELSE IF END Option 4
		}
		else { // 0 logging out

			fp = fopen("tickets.txt", "w");
			// logging out needs to recreate the ticket, so reprint all tickets so update the ticket.txt with new tickets or modifications.
			if (fp != NULL) {
				for (i = 0; i < TICKET_MAX_SIZE; i++) {
					fprintf(fp, "%d|%d|%d|%s|%d|", ticket[i].uniqueNumber, ticket[i].accountNumber, ticket[i].statusIndicator, ticket[i].subjectLine, ticket[i].counter);

					for (j = 0; j < ticket[i].counter; j++) {
						fprintf(fp, "%c|%s|%s|", ticket[i].messages[j].accountType, ticket[i].messages[j].name, ticket[i].messages[j].messageDetail);
					
						if (j + 1 == ticket[i].counter) {
							fprintf(fp, "\n");
						}

						counter = i + 1;
					}
				}
				fclose(fp);
			}
			else {
				printf("\n\nThe tickets file did not load, customer option 0\n\n");
			}

			
			printf("\n");
			printf("Saving session modifications...\n");
			printf("   %d tickets saved.\n", counter);
			printf("### LOGGED OUT ###\n");
			printf("\n");
			run = 0;
		// ELSE END Option 0
		}

	// WHILE END
	}
}


void menuAgent(struct AccountTicketingData* accountTicketingData, const struct Account* account) {
	FILE* fp_tickets = NULL;
	FILE* fp_accounts = NULL;

	int run = 1, option, i, j, list_full = 1, account_found = -1, ticket_number, counter = 0, counter_tickets = 0, counter_accounts = 0, counter_messages = 0;
	char YesNo, characters;
	struct Ticket tickets[17] = { {0} };

	while (run) {
		list_full = 1;
		account_found = -1;
		counter = 0;
		counter_accounts = 0;
		counter_tickets = 0;
		counter_messages = 0;
		fp_tickets = NULL;
		fp_tickets = NULL;

		// display options and then use if-else if statement to run choosen option logic
		printf("AGENT: %s (%d)\n", account->userLogin.name, account->accountNumber);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		option = getIntFromRange(0, 12);

		if (option == 1) {
			// loop through account array and find empty account space, call getAccount, getUserLogin and getDemographic functions to make a new account
			for (i = 0; i < accountTicketingData->ACCOUNT_MAX_SIZE; i++) {
				if (accountTicketingData->accounts[i].accountNumber == 0) {
					getAccount(&accountTicketingData->accounts[i], accountTicketingData->accounts, accountTicketingData->ACCOUNT_MAX_SIZE);
					getUserLogin(&accountTicketingData->accounts[i]);
					getDemographic(&accountTicketingData->accounts[i]);
					printf("*** New account added! ***\n");
					printf("\n");
					pauseExecution();
					list_full = 0;
					break;
				}
			// FOR END
			}

			// if no space available in account array, then display error.
			if (list_full) {
				printf("\nERROR: Account listing is FULL, call ITS Support!\n");
				printf("\n");
				pauseExecution();
			}
		// IF END Option 1
		}
		else if (option == 2) {
			printf("\n");
			account_found = findAccountIndexByAcctNum(0, accountTicketingData->accounts, accountTicketingData->ACCOUNT_MAX_SIZE, 1);

			if (account_found != -1) {
				printf("\n");
				updateAccount(&accountTicketingData->accounts[account_found]);
				printf("\n");
			}
		// ELSE IF END Option 2
		}
		else if (option == 3) {
			printf("\n");
			account_found = findAccountIndexByAcctNum(0, accountTicketingData->accounts, accountTicketingData->ACCOUNT_MAX_SIZE, 1);
			
			if (account_found != -1 && accountTicketingData->accounts[account_found].accountNumber != account->accountNumber) {
				displayAccountDetailHeader();
				displayAccountDetailRecord(&accountTicketingData->accounts[account_found]);

				printf("\n");

				printf("Are you sure you want to remove this record? ([Y]es|[N]o): ");
				YesNo = getCharOption("YN");

				if (YesNo == 'Y') {
					// if agent wants to remove account, then find the ticket associated with the account number and empty it.
					for (i = 0; i < accountTicketingData->TICKET_MAX_SIZE; i++) {
						if (accountTicketingData->tickets[i].accountNumber == accountTicketingData->accounts[account_found].accountNumber && accountTicketingData->tickets[i].statusIndicator == 1) {
							// if the ticket is active, just remove it
							accountTicketingData->tickets[i].uniqueNumber = 0;
						// IF END
						}
						else if (accountTicketingData->tickets[i].accountNumber == accountTicketingData->accounts[account_found].accountNumber && accountTicketingData->tickets[i].statusIndicator == 0 && accountTicketingData->tickets[i].uniqueNumber != 0) {
							// if ticket is closed, archive it, and append the ticket information to tickets_arc.txt
							fp_tickets = fopen("tickets_arc.txt", "a+");

							if (fp_tickets != NULL) {
								fprintf(fp_tickets, "%d|%d|%d|%s|%d|", accountTicketingData->tickets[i].uniqueNumber, accountTicketingData->tickets[i].accountNumber, accountTicketingData->tickets[i].statusIndicator, accountTicketingData->tickets[i].subjectLine, accountTicketingData->tickets[i].counter);

								for (j = 0; j < accountTicketingData->tickets[i].counter; j++) {
									fprintf(fp_tickets, "%c|%s|%s|", accountTicketingData->tickets[i].messages[j].accountType, accountTicketingData->tickets[i].messages[j].name, accountTicketingData->tickets[i].messages[j].messageDetail);

									if (j + 1 == accountTicketingData->tickets[i].counter) {
										fprintf(fp_tickets, "\n");
									}
								}

								fclose(fp_tickets);
							}
							else {
								printf("\n\nThe Tickets txt file is not loaded properly, Agent Option 3\n\n");
							}

							accountTicketingData->tickets[i].uniqueNumber = 0;
						// ELSE IF END
						}
					// FOR LOOP END TICKETS
					}

					fp_accounts = fopen("accounts_arc.txt", "a+");

					// after archiving tickets, archive the account in accounts_arc.txt and append the information to it.
					if (fp_accounts != NULL) {
						fprintf(fp_accounts, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accountTicketingData->accounts[account_found].accountNumber, accountTicketingData->accounts[account_found].accountType, accountTicketingData->accounts[account_found].userLogin.name, accountTicketingData->accounts[account_found].userLogin.loginName, accountTicketingData->accounts[account_found].userLogin.password, accountTicketingData->accounts[account_found].demographic.dateOfBirth, accountTicketingData->accounts[account_found].demographic.income, accountTicketingData->accounts[account_found].demographic.country);
					}
					else {
						printf("The Accounts txt file is not leaded properly, Agent Option 3");
					}

					fclose(fp_accounts);

					// remove the account from the account array.
					accountTicketingData->accounts[account_found].accountNumber = 0;

					printf("\n");
					printf("*** Account Removed! ***\n\n");
					pauseExecution();
				}
				else {
					printf("\n");
					printf("*** No changes made! ***\n\n");
					pauseExecution();
				}
			}
			else if (accountTicketingData->accounts[account_found].accountNumber == account->accountNumber) {
				clearStanadardInputBuffer();
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}

		// ELSE IF END Option 3
		}
		else if (option == 4) {

			printf("\n");
			displayAllAccountSummaryRecords(accountTicketingData);

		// ELSE IF END Option 4
		}
		else if (option == 5) {

			printf("\n");
			displayAllAccountDetailRecords(accountTicketingData);

		// ELSE IF END Option 5
		}
		else if (option == 6) {
			printf("\n");
			displayAgentTicketList(accountTicketingData->tickets, 1, accountTicketingData->TICKET_MAX_SIZE, 1);
		// ELSE IF END Option 6
		}
		else if (option == 7) {
			printf("\n");
			displayAgentTicketList(accountTicketingData->tickets, 0, accountTicketingData->TICKET_MAX_SIZE, 1);
		// ELSE IF END Option 7
		}
		else if (option == 8) {
			printf("\n");
			displayAgentTicketList(accountTicketingData->tickets, 0, accountTicketingData->TICKET_MAX_SIZE, 0);
		// ELSE IF END Option 8
		}
		else if (option == 9) {
			printf("\n");
			printf("Enter ticket number: ");
			ticket_number = getPositiveInteger();
			printf("\n");

			// loop through ticket array to find ticket number agent wants to manage, then call manageTicket function
			for (i = 0; i < accountTicketingData->TICKET_MAX_SIZE; i++) {
				if (accountTicketingData->tickets[i].uniqueNumber == ticket_number) {
					manageTicket(account, &accountTicketingData->tickets[i]);
				}
			}
		// ELSE IF END Option 9
		}
		else if (option == 10) {
			printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			YesNo = getCharOption("YN");
			printf("\n");

			// archive all closed tickets, check through all tickets which ticket has non zero unique number and status of closed to archive, then append the information to tickets_arc.txt, then set that ticket array index to unique = 0 to remove it.

			fp_tickets = fopen("tickets_arc.txt", "a+");

			if (YesNo == 'Y' && fp_tickets != NULL) {
				for (i = 0; i < accountTicketingData->TICKET_MAX_SIZE; i++) {
					if (accountTicketingData->tickets[i].statusIndicator == 0 && accountTicketingData->tickets[i].uniqueNumber != 0) {
						fprintf(fp_tickets, "%d|%d|%d|%s|%d|", accountTicketingData->tickets[i].uniqueNumber, accountTicketingData->tickets[i].accountNumber, accountTicketingData->tickets[i].statusIndicator, accountTicketingData->tickets[i].subjectLine, accountTicketingData->tickets[i].counter);

						for (j = 0; j < accountTicketingData->tickets[i].counter; j++) {
							fprintf(fp_tickets, "%c|%s|%s|", accountTicketingData->tickets[i].messages[j].accountType, accountTicketingData->tickets[i].messages[j].name, accountTicketingData->tickets[i].messages[j].messageDetail);

							if (j + 1 == accountTicketingData->tickets[i].counter) {
								fprintf(fp_tickets, "\n");
							}

						}

						accountTicketingData->tickets[i].uniqueNumber = 0;
						counter++;
					}
				}

				fclose(fp_tickets);
			}

			printf("*** %d tickets archived ***\n\n", counter);
			pauseExecution();
		// ELSE IF END Option 10
		}
		else if (option == 11) {
			// check how many accounts are in accounts_arc.txt by reading the txt file by finding the \n
			fp_accounts = fopen("accounts_arc.txt", "r");

			if (fp_accounts != NULL) {
				counter_accounts = 0;

				do {
					characters = fgetc(fp_accounts);

					if (characters != EOF) {
						if ((char)characters == '\n')
							counter_accounts++;
					}
				} while (feof(fp_accounts) == 0);

				fclose(fp_accounts);
			}

			printf("\nThere are %d account(s) currently archived.\n\n", counter_accounts);
			pauseExecution();

		}
		else if (option == 12) {
			// check how many tickets and messages are in tickets_arc.txt file by reading all the tickets and adding their message counter together.
			fp_tickets = fopen("tickets_arc.txt", "r");

			if (fp_tickets != NULL) {
				counter_tickets = 0;

				for (i = 0; feof(fp_tickets) == 0 && i < accountTicketingData->TICKET_MAX_SIZE; i++) {
					fscanf(fp_tickets, "%d|%d|%d|%30[^|]|%d|", &tickets[i].uniqueNumber, &tickets[i].accountNumber, &tickets[i].statusIndicator, tickets[i].subjectLine, &tickets[i].counter);

					for (j = 0; j < tickets[i].counter; j++) {
						fscanf(fp_tickets, "%c|%30[^|]|%150[^|\n]|", &tickets[i].messages[j].accountType, tickets[i].messages[j].name, tickets[i].messages[j].messageDetail);
					}
					
					counter_messages+= tickets[i].counter;

					counter_tickets = i;

				}

				fclose(fp_tickets);
			}

			printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n", counter_tickets, counter_messages);
			pauseExecution();
		}
		else {
			// recreate accounts and tickets txt file by iterating through tickets and accounts array and recreating the file from the information
			// unique number and account number = 0  means removed account.
			fp_accounts = fopen("accounts.txt", "w");
			fp_tickets = fopen("tickets.txt", "w");

			if (fp_tickets != NULL) {
				for (i = 0; i < accountTicketingData->TICKET_MAX_SIZE; i++) {
					if (accountTicketingData->tickets[i].uniqueNumber != 0) {
						fprintf(fp_tickets, "%d|%d|%d|%s|%d|", accountTicketingData->tickets[i].uniqueNumber, accountTicketingData->tickets[i].accountNumber, accountTicketingData->tickets[i].statusIndicator, accountTicketingData->tickets[i].subjectLine, accountTicketingData->tickets[i].counter);

						for (j = 0; j < accountTicketingData->tickets[i].counter; j++) {
							fprintf(fp_tickets, "%c|%s|%s|", accountTicketingData->tickets[i].messages[j].accountType, accountTicketingData->tickets[i].messages[j].name, accountTicketingData->tickets[i].messages[j].messageDetail);

							if (j + 1 == accountTicketingData->tickets[i].counter) {
								fprintf(fp_tickets, "\n");
							}

						}
						counter_tickets++;

					}
				}
				fclose(fp_tickets);
			}
			else {
				printf("\n\nThe tickets file did not load, agent option 0\n\n");
			}

			if (fp_accounts != NULL) {
				for (i = 0; feof(fp_accounts) == 0 && i < accountTicketingData->ACCOUNT_MAX_SIZE; i++) {
					if (accountTicketingData->accounts[i].accountNumber != 0) {
						fprintf(fp_accounts, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", accountTicketingData->accounts[i].accountNumber, accountTicketingData->accounts[i].accountType, accountTicketingData->accounts[i].userLogin.name, accountTicketingData->accounts[i].userLogin.loginName, accountTicketingData->accounts[i].userLogin.password, accountTicketingData->accounts[i].demographic.dateOfBirth, accountTicketingData->accounts[i].demographic.income, accountTicketingData->accounts[i].demographic.country);

						counter_accounts++;

					}
				}

				fclose(fp_accounts);
			}
			else {
				printf("\n\nThe accounts file did not load, agent option 0\n\n");
			}


			printf("\n");
			printf("Saving session modifications...\n");
			printf("   %d account saved.\n", counter_accounts);
			printf("   %d tickets saved.\n", counter_tickets);
			printf("### LOGGED OUT ###\n");
			printf("\n");
			run = 0;
		// ELSE END Option 0
		}
	// WHILE END
	}
}

void displayAllAccountSummaryRecords(const struct AccountTicketingData* accountTicketingData) {

	int i;

	displayAccountSummaryHeader();

	for (i = 0; i < accountTicketingData->ACCOUNT_MAX_SIZE; i++) {
		if (accountTicketingData->accounts[i].accountNumber != 0) {
			displayAccountSummaryRecord(&accountTicketingData->accounts[i]);
		}
	}

	printf("\n");
	pauseExecution();
}

void displayAllAccountDetailRecords(const struct AccountTicketingData* accountTicketingData) {

	int i;

	displayAccountDetailHeader();

	for (i = 0; i < accountTicketingData->ACCOUNT_MAX_SIZE; i++) {
		if (accountTicketingData->accounts[i].accountNumber != 0) {
			displayAccountDetailRecord(&accountTicketingData->accounts[i]);
		}		
	}

	printf("\n");
	pauseExecution();


}

void displayCustomerTicketHeader(void) {
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

void displayCustomerTicketDetail(const struct Ticket* ticket) {
	char status[8];

	if (ticket->statusIndicator == 1) {
		strcpy(status, "ACTIVE");
	}
	else {
		strcpy(status, "CLOSED");
	}

	printf("%06d %-6s %-30s %5d\n", ticket->uniqueNumber, status, ticket->subjectLine, ticket->counter);
}

void displayAgentTicketHeader(void) {
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayAgentTicketDetail(const struct Ticket* ticket) {
	char status[8];

	if (ticket->statusIndicator == 1) {
		strcpy(status, "ACTIVE");
		printf("%06d %05d %-15s %-6s %-30s %5d\n", ticket->uniqueNumber, ticket->accountNumber, ticket->messages[0].name, status, ticket->subjectLine, ticket->counter);
	} else if (ticket->statusIndicator == 0) {
		strcpy(status, "CLOSED");
		printf("%06d %05d %-15s %-6s %-30s %5d\n", ticket->uniqueNumber, ticket->accountNumber, ticket->messages[0].name, status, ticket->subjectLine, ticket->counter);
	}
}


int findAccountIndexByAcctNum(int account_number, const struct Account accountsArr[], const int ACCOUNT_MAX_SIZE, int prompt_user) {
	int i = 1, arr_index = -1;

	if (prompt_user != 0) {
		printf("Enter the account#: ");
		scanf("%d", &account_number);
	}

	for (i = 0; i < ACCOUNT_MAX_SIZE; i++) {

		if (account_number == accountsArr[i].accountNumber) {
			arr_index = i;
			break;
			// IF END account number found
		}
		// FOR END
	}

	return arr_index;
}

int loginApprove(const struct AccountTicketingData* accountTicketingData) {
	int arr_index, account_number, run2 = 2;
	char login_sec[31] = "x", password_sec[31] = "x";

	// security check for user or agent login information, loop it until system login fails.
	while (run2 != -1) {

		printf("\n");
		printf("Enter the account#: ");
		account_number = getInteger();
		arr_index = findAccountIndexByAcctNum(account_number, accountTicketingData->accounts, accountTicketingData->ACCOUNT_MAX_SIZE, 0);

		printf("User Login    : ");
		getCString(login_sec, 1, 30);

		printf("Password      : ");
		getCString(password_sec, 1, 30);

		if (arr_index != -1 && strcmp(accountTicketingData->accounts[arr_index].userLogin.loginName, login_sec) == 0 && strcmp(accountTicketingData->accounts[arr_index].userLogin.password, password_sec) == 0) {
			run2 = -1;
		}
		else {
			printf("INVALID user login/password combination! [attempts remaining:%d]\n", run2);
			run2--;

			if (run2 == -1) {
				printf("\nERROR:  Login failed!\n\n");
				arr_index = -1;
				pauseExecution();
			}
		}
	// WHILE END run2
	}

	return arr_index;
}

void displayCustomerTicketList(const struct Ticket ticket[], const int TICKET_MAX_SIZE) {
	int run = 1, invalid = 1, ticket_number, i, j;
	char status[8], empty_string[9];
	// display and allow user to interact with the tickets associated with user
	while (run) {
		invalid = 1;
		displayCustomerTicketHeader();
		for (i = 0; i < TICKET_MAX_SIZE; i++) {
			if (ticket[i].uniqueNumber != 0) {
				displayCustomerTicketDetail(&ticket[i]);
			}
		}
		printf("------ ------ ------------------------------ --------\n");
		printf("\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		ticket_number = getPositiveInteger();

		if (ticket_number == 0) {
			run = 0;
			printf("\n");
		}
		else {
			// let user manage its tickets or view the messages.
			for (i = 0; i < TICKET_MAX_SIZE; i++) {
				if (ticket[i].uniqueNumber == ticket_number) {

					if (ticket[i].statusIndicator == 1) {
						strcpy(status, "ACTIVE");
					}
					else {
						strcpy(status, "CLOSED");
					}

					printf("\n================================================================================\n");
					printf("%06d (%s) Re: %s\n", ticket[i].uniqueNumber, status, ticket[i].subjectLine);
					printf("================================================================================\n");

					for (j = 0; j < ticket[i].counter; j++) {
						if (ticket[i].messages[j].accountType != 0) {
							if (ticket[i].messages[j].accountType == 'C') {
								strcpy(empty_string, "CUSTOMER");
							}
							else {
								strcpy(empty_string, "AGENT");
							}

							printf("%s (%s):\n", empty_string, ticket[i].messages[j].name);
							printf("   %s\n\n", ticket[i].messages[j].messageDetail);

							if ((j + 1) % 5 == 0 && ticket[i].counter != j + 1) {
								pauseExecution();
							}
						}
						else {
							break;
						}
					}
					invalid = 0;
				}
			}

			if (invalid) {
				printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
			}
			pauseExecution();
		}

	// WHILE END run
	}
}

void displayAgentTicketList(const struct Ticket tickets[], const int allOrOne, const int TICKET_MAX_SIZE, const int activeOrClosed) {
	int run = 1, invalid = 1, ticket_number, i, j;
	char status[8], empty_string[9];
	struct Ticket tickets_arr[30] = { {0} };
	// allow agent to check the active or closed tickets.
	while (run) {
		invalid = 1;
		displayAgentTicketHeader();
		for (i = 0; i < TICKET_MAX_SIZE; i++) {
			if(tickets[i].statusIndicator == 1 && activeOrClosed == 1 && tickets[i].uniqueNumber != 0) {
				if (tickets[i].counter == 1 && allOrOne == 1) {
					displayAgentTicketDetail(&tickets[i]);
					tickets_arr[i] = tickets[i];
				}
				else if (allOrOne != 1) {
					displayAgentTicketDetail(&tickets[i]);
					tickets_arr[i] = tickets[i];
				}
			}
			else if (tickets[i].statusIndicator == 0 && activeOrClosed == 0 && tickets[i].uniqueNumber != 0 && allOrOne != 1) {
				displayAgentTicketDetail(&tickets[i]);
				tickets_arr[i] = tickets[i];
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");
		ticket_number = getPositiveInteger();

		if (ticket_number == 0) {
			run = 0;
			printf("\n");
		}
		else {
			// allow agent to manage the tickets or view messages
			for (i = 0; i < TICKET_MAX_SIZE; i++) {
				if (tickets_arr[i].uniqueNumber == ticket_number) {
					if (tickets_arr[i].statusIndicator == 1) {
						strcpy(status, "ACTIVE");
					}
					else {
						strcpy(status, "CLOSED");
					}

					printf("\n================================================================================\n");
					printf("%06d (%s) Re: %s\n", tickets_arr[i].uniqueNumber, status, tickets_arr[i].subjectLine);
					printf("================================================================================\n");

					for (j = 0; j < tickets_arr[i].counter; j++) {
						if (tickets_arr[i].messages[j].accountType != 0) {
							if (tickets_arr[i].messages[j].accountType == 'C') {
								strcpy(empty_string, "CUSTOMER");
							}
							else {
								strcpy(empty_string, "AGENT");
							}

							printf("%s (%s):\n", empty_string, tickets_arr[i].messages[j].name);
							printf("   %s\n\n", tickets_arr[i].messages[j].messageDetail);

							if ((j + 1) % 5 == 0 && tickets_arr[i].counter != j + 1) {
								pauseExecution();
							}
						}
						else {
							break;
						}
					}
					invalid = 0;
				}

			}

			if (invalid) {
				printf("\nERROR: Invalid ticket number.\n\n");
			}

			pauseExecution();
		}
		// WHILE END run
	}
}

int loadAccounts(struct Account accounts[], const int ACCOUNT_SIZE) {
	FILE* fp = NULL;
	int i, counter = 0;

	fp = fopen("accounts.txt", "r");

	if (fp != NULL) {
		for (i = 0; feof(fp) == 0 && i < ACCOUNT_SIZE; i++) {
			fscanf(fp, "%d~%c~%30[^~]~%10[^~]~%8[^~]~%d~%lf~%30[^\n]", &accounts[i].accountNumber, &accounts[i].accountType, accounts[i].userLogin.name, accounts[i].userLogin.loginName, accounts[i].userLogin.password, &accounts[i].demographic.dateOfBirth, &accounts[i].demographic.income, accounts[i].demographic.country);
			counter = i + 1;
		}
		fclose(fp);
	}
	else {
		printf("Accounts file could not open!");
	}


	return counter;
}

int loadTickets(struct Ticket tickets[], const int TICKET_SIZE) {
	FILE* fp = NULL;
	int i, j, counter = 0;

	fp = fopen("tickets.txt", "r");

	if (fp != NULL) {
		for (i = 0; feof(fp) == 0 && i < TICKET_SIZE; i++) {
			fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &tickets[i].uniqueNumber, &tickets[i].accountNumber, &tickets[i].statusIndicator, tickets[i].subjectLine, &tickets[i].counter);

			for (j = 0; j < tickets[i].counter; j++) {
				fscanf(fp, "%c|%30[^|]|%150[^|\n]|", &tickets[i].messages[j].accountType, tickets[i].messages[j].name, tickets[i].messages[j].messageDetail);
				counter = i + 1;
			}
		}
		fclose(fp);
	}
	else {
		printf("Tickets file could not open!");
	}

	return counter;
}

void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStanadardInputBuffer();
	putchar('\n');
}

