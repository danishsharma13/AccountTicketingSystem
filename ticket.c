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
#include "accountTicketingUI.h"
#include "commonHelpers.h"
#include "ticket.h"

void getTicket(const struct Account* account, struct Ticket* ticket, const struct Ticket ticketArr[], const int TICKET_MAX_SIZE) {
	int run = 1, rand_num = 0, arr_index;

	// get user a new ticket and keep adding 1 to 80600 if it is not available until it is available
	while (run) {
		arr_index = findTicketByUniqNum(80600 + rand_num, ticketArr, TICKET_MAX_SIZE);

		if (arr_index == -1) {
			run = 0;
			ticket->uniqueNumber = 80600 + rand_num;
		}

		rand_num++;
	}

	printf("\nNew Ticket (Ticket#:%06d)\n", ticket->uniqueNumber);
	printf("----------------------------------------\n");


	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(ticket->subjectLine, 1, 30);
	
	printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(ticket->messages[0].messageDetail, 1, 150);
	
	ticket->accountNumber = account->accountNumber;
	ticket->counter++;
	ticket->statusIndicator = 1;
	ticket->messages[0].accountType = account->accountType;
	strcpy(ticket->messages[0].name, account->userLogin.name);

}

void modifyTicket(const struct Account* account, struct Ticket* ticket) {
	int run = 1, option, i, message_limit = 1;
	char YesNo = 'x', status_arr[9];
	// allow user to see modify ticket menu and pick from the options
	while (run) {
		message_limit = 1;

		if (ticket->statusIndicator == 1) {
			strcpy(status_arr, "ACTIVE");
		}
		else {
			strcpy(status_arr, "CLOSED");
		}

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->uniqueNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", status_arr);
		printf("Subject : %s\n", ticket->subjectLine);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 3);

		printf("\n");

		if (option == 1) {
			printf("Enter the revised ticket SUBJECT (30 chars. maximum): ");
			getCString(ticket->subjectLine, 1, 30);
			printf("\n");
		}
		else if (option == 2) {

			for (i = 0; i < 20; i++) {
				if (ticket->messages[i].accountType == 0) {
					printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
					getCString(ticket->messages[i].messageDetail, 1, 150);
					strcpy(ticket->messages[i].name, account->userLogin.name);
					ticket->messages[i].accountType = account->accountType;
					ticket->counter++;
					printf("\n");
					message_limit = 0;
					break;
				}
			}

			if (message_limit) {
				printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
			}

		}
		else if (option == 3) {
			// check if the user wants to close, and if it needs to be closed, ask for a final message
			printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			YesNo = getCharOption("YN");
			printf("\n");

			if (YesNo == 'Y') {

				ticket->statusIndicator = 0;
				run = 0;

				if (ticket->counter < 20) {
					printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
					YesNo = getCharOption("YN");
					printf("\n");

					if (YesNo == 'Y') {
						for (i = 0; i < 20; i++) {
							if (ticket->messages[i].accountType == 0) {
								printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
								getCString(ticket->messages[i].messageDetail, 1, 150);
								strcpy(ticket->messages[i].name, account->userLogin.name);
								ticket->messages[i].accountType = account->accountType;
								ticket->counter++;
								printf("\n");
								break;
							}
						}
					}
				}

				
				printf("*** Ticket closed! ***\n\n");
			}

		}
		else {
			run = 0;
		}
	}

}

void manageTicket(const struct Account* account, struct Ticket* ticket) {
	int run = 1, option, i, message_limit = 1;
	char YesNo = 'x', status_arr[9];
	// display agent the manage ticket menu and let them choose from the options
	while (run) {
		message_limit = 1;

		if (ticket->statusIndicator == 1) {
			strcpy(status_arr, "ACTIVE");
		}
		else {
			strcpy(status_arr, "CLOSED");
		}

		printf("----------------------------------------\n");
		printf("Ticket %06d - Update Options\n", ticket->uniqueNumber);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", status_arr);
		printf("Subject : %s\n", ticket->subjectLine);
		printf("Acct#   : %d\n", ticket->accountNumber);
		printf("Customer: %s\n", ticket->messages[0].name);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0,3);
		
		printf("\n");

		if (option == 1) {
			if (ticket->statusIndicator == 1) {
				for (i = 0; i < 20; i++) {
					if (ticket->messages[i].accountType == 0) {
						printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(ticket->messages[i].messageDetail, 1, 150);
						strcpy(ticket->messages[i].name, account->userLogin.name);
						ticket->messages[i].accountType = account->accountType;
						ticket->counter++;
						printf("\n");
						message_limit = 0;
						break;
					}
				}

				if (message_limit) {
					printf("ERROR: Message limit has been reached, call ITS Support!\n\n");
				}
			}
			else {
				printf("ERROR: Ticket is closed - new messages are not permitted.\n\n");
			}
		}
		else if (option == 2) {
			// check if the agent wants to close a ticket and if they want to add a final message to the ticket
			if (ticket->statusIndicator == 1) {
				printf("Are you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				YesNo = getCharOption("YN");
				printf("\n");

				if (YesNo == 'Y') {

					ticket->statusIndicator = 0;

					if (ticket->counter < 20) {
						printf("Do you want to leave a closing message? ([Y]es|[N]o): ");
						YesNo = getCharOption("YN");
						printf("\n");

						if (YesNo == 'Y') {
							for (i = 0; i < 20; i++) {
								if (ticket->messages[i].accountType == 0) {
									printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
									getCString(ticket->messages[i].messageDetail, 1, 150);
									strcpy(ticket->messages[i].name, account->userLogin.name);
									ticket->messages[i].accountType = account->accountType;
									ticket->counter++;
									printf("\n");
									break;
								}
							}
						}
					}

					printf("*** Ticket closed! ***\n\n");
				}
			}
			else {
				printf("ERROR: Ticket is already closed!\n\n");
			}
		}
		else if (option == 3) {
			// check if agent wants to open a closed ticket
			if (ticket->statusIndicator == 0) {
				printf("Are you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				YesNo = getCharOption("YN");
				printf("\n");

				if (YesNo == 'Y') {
					printf("*** Ticket re-opened! ***\n\n");
					ticket->statusIndicator = 1;
				}
			}
			else {
				printf("ERROR: Ticket is already active!\n\n");
			}
		}
		else {
			run = 0;
		}

	}

}

int findTicketByUniqNum(int ticketNum, const struct Ticket ticket[], int TICKET_MAX_SIZE) {
	int arr_index = -1, i;

	// find if ticket number is already in the ticket array
	for (i = 0; i < TICKET_MAX_SIZE; i++) {
		if (ticketNum == ticket[i].uniqueNumber) {
			arr_index = i;
			break;
		}
	}

	return arr_index;
}