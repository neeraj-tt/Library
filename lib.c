#include "defs.h"

void loadBooks(BookListType *books) {
	FILE *infile;
	
	int id = 1000;
  	char title[MAX_STR];
 	char author[MAX_STR];
  	char yearTemp[MAX_STR];
  	char statusTemp[MAX_STR];
  	int year;
  	//bookstatustype?
  	int status;
  	
  	
	infile = fopen("booksData.txt", "r");
	if (!infile) {
		printf("Error: could not open file\n");
		exit(1);
	}
	
	while (1) {
		//edit for plag
		//checking for EOF
		fgets(title, MAX_STR, infile);
		title[strlen(title) - 1] = 0;
		fgets(author, MAX_STR, infile);
		author[strlen(author) - 1] = 0;
		fgets(yearTemp, MAX_STR, infile);
		yearTemp[strlen(yearTemp) - 1] = 0;
		fgets(statusTemp, MAX_STR, infile);
		statusTemp[strlen(statusTemp) - 1] = 0;
		sscanf(yearTemp, "%d", &year);
		sscanf(statusTemp, "%d", &status);
		id++;
		
		// change this		
		if (feof(infile)) {
			break;
		}	
		
		BookType *book;
		initBook(id, title, author, year, status, &book);
		addBook(books, book);			
		//printf("Title: %12s, Author: %15s, Year: %d, ID: %d\n", title, author, year, status);
	}
	/*NodeType *currNode;
	
	currNode = books->head;
	
	while (currNode != NULL) {
	printf("%s %d\n", currNode->data->title, currNode->data->id);
		currNode = currNode->next;
	}*/
	fclose(infile);
}

void initLibrary(LibraryType **library, char *n) {
	char outStr[MAX_BUFF];

	*library = malloc(1 * sizeof(LibraryType));
	strcpy((*library)->name, n);
	initList(&(*library)->books);
	loadBooks(&(*library)->books);
	formatBooks(&(*library)->books, outStr);
}

int checkOutBook(LibraryType *lib, int bookId) {
	BookType *book;
	
	int rc = findBook(&(lib->books), bookId, &book);
	if (rc < 0) {
		//printf("Book was not found\n");
		return C_BOOK_NOT_FOUND;		
	}	
	
	if (book->status == CHECKED_IN) {
		book->status = CHECKED_OUT;
		return C_OK;
		//printf("Checked out!\n");		
	}
	
	//printf("Book not checked in\n");
	return C_BAD_STATUS;
		
}

int checkInBook(LibraryType *lib, int bookId) {
	BookType *book;
	
	int rc = findBook(&(lib->books), bookId, &book);
	if (rc < 0) {
		//printf("Book was not found\n");
		return C_BOOK_NOT_FOUND;		
	}	
	if (book->status == CHECKED_OUT) {
		book->status = CHECKED_IN;
		return C_OK;
		//printf("Checked in!\n");		
	}
	
	//printf("Book not checked out\n");
	return C_BAD_STATUS;

}

void cleanupLibrary(LibraryType *lib) {
	NodeType *currNode;
	NodeType *next;
		
	currNode = lib->books.head;
	
	while (currNode != NULL) {
		next = currNode->next;
		free(currNode);
		currNode = next;
	}
	
	lib->books.head = NULL;
	lib->books.tail = NULL;
	free(lib);
}





