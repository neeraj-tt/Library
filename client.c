#include "defs.h"


int main()
{
  int choice = -1;
  int bookId;
  char req[MAX_STR];
  int rc;
  
  int clientSocket;
  setupClientSocket(&clientSocket);
  char buffer[MAX_BUFF];

  
  /*BookListType books;
  initList(&books);
  BookType *book;
  //loadBooks(&books);
  
  LibraryType *library;
  char name[MAX_STR] = "LIBRARY";
  initLibrary(&library, name);
  int rc = findBook(&(library->books), 1004, &book);
  checkOutBook(library, 1005);
  checkInBook(library, 1005);*/
  
  
  while (1) {

   clientMenu(&choice);

   switch(choice) {

      case 1:   // Print books
      	strcpy(req, "0");   	
		sendData(clientSocket, req);
		rcvData(clientSocket, buffer);
		printf("%s", buffer);
		
        break;

      case 2:   // Check out a book		
		printf("Enter a book id: ");
  		scanf("%d", &bookId);
		fgetc(stdin);
  		
  		sprintf(req, "%s %d", "1", bookId);  
  		sendData(clientSocket, req);
		rcvData(clientSocket, buffer);
		sscanf(buffer, "%d", &rc);
		if (rc == C_OK) {
			printf("Checked out!\n");
		} else if (rc == C_BOOK_NOT_FOUND) {
			printf("Book not found\n");
		} else if (rc == C_BAD_STATUS) {
			printf("Book not checked in\n");
		} 
		
        break;

      case 3:   // Check in a book
		printf("Enter a book id: ");
  		scanf("%d", &bookId);
  		fgetc(stdin);
  		
  		sprintf(req, "%s %d", "2", bookId);  
  		sendData(clientSocket, req);
		rcvData(clientSocket, buffer);
		sscanf(buffer, "%d", &rc);
		if (rc == C_OK) {
			printf("Checked in!\n");
		} else if (rc == C_BOOK_NOT_FOUND) {
			printf("Book not found\n");
		} else if (rc == C_BAD_STATUS) {
			printf("Book not checked out\n");
		} 

        break;

      case 0:   // Close everything
      	strcpy(req, "3");
      	sendData(clientSocket, req);
      	close(clientSocket);	
		exit(1);
        break;

      default:
        printf("ERROR:  invalid option\n");
    }
  }

  return 0;
}

void clientMenu(int* choice)
{
  int c = -1;
  int numOptions = 3;
  char str[MAX_STR];

  printf("\nMAIN MENU\n");
  printf("  (1) Print books\n");
  printf("  (2) Check out a book\n");
  printf("  (3) Check in a book\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  fgets(str, sizeof(str), stdin);
  str[strcspn(str, "\n")] = 0;
  sscanf(str, "%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    sscanf(str, "%d", &c);
  }

  *choice = c;
}

