#include "defs.h"

void initList(BookListType *list) {
	list->head = NULL;
	list->tail = NULL;
}

void initBook(int i, char *t, char *a, int y, BookStatusType st,
			BookType **book) {
	*book = malloc(1 * sizeof(BookType));
	(*book)->id = i;
	strcpy((*book)->title, t);
	strcpy((*book)->author, a);
	(*book)->year = y;
	(*book)->status = st;
}

/*void addBook(BookListType *list, BookType *b) {
	NodeType *currNode;
	NodeType *prevNode;
	NodeType *newNode;
	
	currNode = list->head;
	prevNode = NULL;
	
	//if list is empty, add book 
	if (list->head == NULL && list->tail == NULL) {
		newNode = malloc(1 * sizeof(NodeType));
		newNode->data = b;
		newNode->next = NULL;
		
		list->head = newNode;
		list->tail = newNode;
		//printf("added first %s\n", newNode->data->title);
		return;
	}

	//compare book to items in list
	while (currNode != NULL) {
		//printf("comparing %s to %s\n", b->title, currNode->data->title);
		if (strcmp(b->title, currNode->data->title) < 0) {
			newNode = malloc(1 * sizeof(NodeType));
			newNode->data = b;

			newNode->next = currNode;
			prevNode->next = newNode;
			if (currNode->next == NULL) {
				list->tail = currNode;
			}
			//printf("added %s\n", newNode->data->title);
			return;
			
		}
		prevNode = currNode;
		currNode = currNode->next;
	}
	
	//if reaches, book becomes last element
	newNode = malloc(1 * sizeof(NodeType));
	newNode->data = b;
	prevNode->next = newNode;
	newNode->next = NULL;
	//list->tail = newNode;
	
	//printf("added %s\n", newNode->data->title);
	return;
	
	
}*/


void addBook(BookListType *list, BookType *b)
{
    NodeType *currNode;
    NodeType *prevNode;
    NodeType *newNode;

    currNode = list->head;
    prevNode = NULL;

    while (currNode != NULL) {
        if (strcmp(b->title, currNode->data->title) < 0) {
            break;
       	}        
        prevNode = currNode;
        currNode = currNode->next;
    }

    newNode = malloc(1 * sizeof(NodeType));
    newNode->data = b;
    newNode->next = NULL;
    
    //check if list is empty
    if (list->head == NULL && list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
        //printf("added %s at first\n", newNode->data->title);
        return;
    }    

	//adding to front
    if (prevNode == NULL) {
        list->head = newNode;
		newNode->next = currNode;
        //printf("added %s before %s\n", newNode->data->title, newNode->next->data->title);
        return;
    }
    
    prevNode->next = newNode;
    newNode->next = currNode;
    //printf("added %s after %s\n", newNode->data->title, prevNode->data->title);
    return;
    
}

int findBook(BookListType *list, int id, BookType **b) {
	NodeType *currNode;
	
	currNode = list->head;
	
	while (currNode != NULL) {
		if (currNode->data->id == id) {
			*b = currNode->data;
			return C_OK;
		}	
		currNode = currNode->next;
	}
	
	//only reaches here if book not found
	//printf("Error: could not find book\n");
	return C_NOK;	
}

void formatBook(BookType *b, char *outStr) {
	char buffer[MAX_BUFF];
	char id[MAX_STR];
	char year[MAX_STR];
	char status[MAX_STR];
	
	sprintf(id, "%d", b->id);
	sprintf(year, "%d", b->year);
	//sprintf(status, "%d", b->status);
	convertStatus(b->status, status);
	sprintf(buffer, "%s : %-36s : %-20s : %-5s : %2s\n", id, b->title, b->author, year, status);
	strcpy(outStr, buffer);
	//buffer[sizeof(buffer) - 1] = '\0';
	//printf("%d %s %s %d", b->id, b->title, b->author, b->year);
}

void convertStatus(BookStatusType status, char *bstStr) {
	switch (status) {
		case CHECKED_IN:
			strcpy(bstStr, "Checked In");
			break;
		case CHECKED_OUT:
			strcpy(bstStr, "Checked Out");
			break;
		case UNDER_REPAIR:
			strcpy(bstStr, "Under Repair");
			break;
		case LOST:
			strcpy(bstStr, "Lost");
			break;		
	}
}

void formatBooks(BookListType *list, char *outStr) {
	NodeType *currNode;
	char temp[MAX_BUFF];
	
	currNode = list->head;
	strcpy(outStr, "\n");
	
	while (currNode != NULL) {
		formatBook(currNode->data, temp);
		strcat(outStr, temp);
		//temp[sizeof(temp) - 1] = '\0';
		currNode = currNode->next;
	}
	//printf("out string:\n");
	//printf("%s\n", outStr);
}

void cleanupList(BookListType *list) {
	NodeType *currNode;
	NodeType *next;
		
	currNode = list->head;
	
	while (currNode != NULL) {
		next = currNode->next;
		free(currNode);
		currNode = next;
	}
	
	list->head = NULL;
	list->tail = NULL;
}



