#include "defs.h"

int listenSocket;

int main()
{
	LibraryType *library;
	int clientSocket;
	
	char name[MAX_STR] = "LIBRARY";
	initLibrary (&library, name);
	
	setupServerSocket(&listenSocket);
	
	signal(SIGUSR1, handleSig1);
	
	printf("\nWaiting for connection request...\n");	
	acceptConnection(listenSocket, &clientSocket);
	printf("Connected!\n");

	serveOneClient(clientSocket, library);
	


  return 0;
}

void serveOneClient(int clientSocket, LibraryType *lib) {
	char buffer[MAX_BUFF];
  	int req;
  	int id;
  	int rc;
  	while (1){
  		printf("Waiting for message...\n");
		rcvData(clientSocket, buffer);
		sscanf(&buffer[0], "%d", &req);	
		switch (req){
		  case 0: //REQ_RET_BOOKS
		  	printf("Received message!\n");  		  		 
		  	formatBooks(&(lib->books), buffer);
		    sendData(clientSocket, buffer);
		    break;
		    
		  case 1: //REQ_CHECK_IN
		  	printf("Received message!\n");  	
		  	sscanf(buffer, "%d %d", &req, &id);	
		  	rc = checkOutBook(lib, id);		  	
		    sprintf(buffer, "%d", rc);
		    sendData(clientSocket, buffer);
		    break;
		    
		  case 2: //REQ_CHECK_OUT
		  	printf("Received message!\n");  	
		    sscanf(buffer, "%d %d", &req, &id);	
		  	rc = checkInBook(lib, id);		  	
		    sprintf(buffer, "%d", rc);
		    sendData(clientSocket, buffer);
		    break;
		    
		  case 3: //REQ_CLOSE
		  	printf("Shutting down...\n");  	
		    closeAll(lib);
		    printf("Done!\n");  
		    exit(0);		    	
		    break;
		}
  	}
}

void closeAll(LibraryType *lib) {
	close(listenSocket);
	cleanupList(&(lib->books));
	cleanupLibrary(lib);
}

void handleSig1(int i) {
	printf("Shutting down...\n");
	close(listenSocket);
	exit(SIGUSR1);
}
