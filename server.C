/*
 * server.C
 *
 *  Created on: 11.09.2019
<<<<<<< HEAD
 *      Author: M.F
 */
#include <cstdio> 											// standard input and output library
#include <cstdlib> 											// this includes functions regarding memory allocation
#include <cstring> 											// contains string functions
#include <cerrno> 											//It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> 											//contains various functions for manipulating date and time

#include <unistd.h> 										//contains various constants
#include <sys/types.h> 										//contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> 										// defines in_addr structure
#include <sys/socket.h> 									// for socket creation
#include <netinet/in.h> 									//contains constants and structures needed for internet domain addresses
#include <iostream>

#include "SIMPLESOCKET.H"
#include "TASK1.H"

using namespace std;
using namespace TASK1;


class myTCPserver : public TCPserver{

public :
	myTCPserver(int port, int maxDataSize) : TCPserver(port, maxDataSize){;}



protected:
	string myResponse(string input);
	BlackBoxSafe *Safe_;
};

// 2022 =  port number
int main(){
	srand(time(nullptr));
	myTCPserver srv(2022,25);

	srv.run();
}




string myTCPserver::myResponse(string input){

	string response("Unbekannte Eingabe");


	int pwdL,alphL;

	if(input.compare(0,7,"pwdNeu[")== 0){


		sscanf(input.c_str(),"pwdNeu[%d,%d]", &pwdL, &alphL);

		Safe_ = new BlackBoxSafe(pwdL,alphL);


		response = string("Passwort erstellt ");


	}else if(input.compare(0,4,"PWD:") == 0){
		char pwd[32];
		sscanf(input.c_str(), "PWD:%s",pwd);


		response = Safe_->input(pwd);



	}

	return response;
}



=======
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"


int main(){
	srand(time(nullptr));
	TCPserver srv(2022,25);
	srv.run();
}
>>>>>>> 0a80798e07c41eb3cf14f1b9e8ca006ea854299a
