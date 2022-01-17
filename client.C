/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream> 	//for stringstream
#include <math.h>
#include <fstream> 	//enables writing in Files

#include "SIMPLESOCKET.H"

using namespace std;

string pwdErstellen(TCPclient *c, int pwdL, int alphL);
int pwdRaten(TCPclient *c, int pwdL, int alphL);

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);									// Port Nummer des Servers

	int pwdL = 4;											// Laenge des Passwortes
	int alphL = 4;											// Laenge des Alphabetes
 ofstream file ("statistik.csv",ofstream::app);
	for(int d=0; d<10; d++){
	string res("");											// String in dem die Antwort des Servers gespeichert wird
	cout << "Neues Passwort wird angefordert" << endl;
	res = pwdErstellen(&c,pwdL,alphL);						// Funktion zur Passworterstellung wird aufgerufen

	if(res.compare(0,16,"Passwort erstellt")){				// Client bekommt Rueckmeldung zur erfolgreichen Passworterstellung

	int counter;											// Zaehlt die Versuche das Passwort zu raten
	counter = pwdRaten(&c,pwdL,alphL);

	cout << "Das Passwort wurde mit " << counter << " Versuchen geraten" << endl;

 file<<pwdL<<" "<<alphL<< " "<<counter<<endl;

	}



	else{ 													// Fuer den Fall, dass der Client kein Passwort erstellt
		
		cout << "Fehler"<< endl;

	}
	}
 file.close();
	return 0;

	}



string pwdErstellen(TCPclient *c, int pwdL, int alphL){    	// pwdErstellen = Fordert vom Server die Erstellung eines Passwortes
															// pwdL = Passwortlaenge, alphL = Alphabetlaenge

	stringstream s;
	s << "pwdNeu[" << pwdL << "," << alphL << "]";
	string msg = s.str();									// Der Stringstream s wird als String msg gespeichert
	string res("");
	c->sendData(msg);
	res = c->receive(32);

	cout << res << endl;

	return res;

}



int pwdRaten(TCPclient *c, int pwdL, int alphL){			// pwdRaten zaehlt die Versuche die benoetigt werden um das Passwort zu erraten
															// Das Passwort wird über die Bruteforce Methode ermittelt
	const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";	// Moegliches Zeichen des Alphabets
	char symbArray[alphL];
	string pwdIdee,response;
	int m=0;
	int index;
	pwdIdee =string("");


	
	
	for(int i=0;i<alphL;i++){                     			// Das Alphabet wird auf die gegebene Laenge gekuerzt
		symbArray[i] = SYMBOLS.at(i);
	}
	


	if(pwdL > 0){
		for(int i=0;i < pwdL;i++){
			pwdIdee += symbArray[0];						// Der String pwdIdee wird auf der Laenge des Passwortes von der nullten Stelle des symbArrays erstellt (0 = A)
		}

		do{
			for(int i=0;i<pwdL;i++){
				if(i==0){
					pwdIdee.replace(i,1,1,symbArray[int(m % alphL)]);   // Die erste Stelle des Passwortes wird zwischen A und dem Ende des Alphabetes variiert.
				}else{
					index = (m / int(pow(float(alphL),float(i)))) % alphL;

					pwdIdee.replace(i,1,1,symbArray[index]);			// Die weiteren Stellen des Passwortes werden zwischen A und dem Ende des Alphabetes variiert.
				}
			}
			response = string();
			response = "PWD:";
			response += pwdIdee;
	
			cout << response << endl;
					
			c->sendData(response);										// Passwort wird an den Server gesendet

	
			response = c->receive(32);
			cout << response << endl;
			m++;

		}while(response.compare("ACCEPTED") != 0);						// Do-while Schleife laeuft so lange bis der Server "ACCEPTED" ausgibt


	return int( m );





}

return -1;


}

