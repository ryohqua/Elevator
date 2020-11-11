#include "C:\RTExamples\RTExamples\rt.h"
#include <atomic>
#include "dispatcher.h"
#include "elevator.h"
#include "monitor.h"
#include "updLink.h"
#include "inputKey.h"

struct 	    mydatapooldata {		// start of structure template
	int floor;				// floor corresponding to lifts current position
	int dir;			// direction of travel of lift
	int status;		//status
};



int InputKey::main() {
	CTypedPipe <int>	p1("Pipe1", 1024);			// create the three named pipelines 
	CSemaphore P1("Elv", 0, 1);
	CSemaphore C1("ElvDone", 1, 1);
	CDataPool 		dp("Elevator", sizeof(struct mydatapooldata));
	struct mydatapooldata* MyDataPool = (struct mydatapooldata*)(dp.LinkDataPool());
	int ecounter = 0;


	while (1) {
		int message = _getch(); // get the first message
		int message2;
		printf("%d", message);// print the up or down in integer
		if (message == 100 || message == 117) {
			p1.Write(&message);// send up and down to the dispatcher
			message2 = _getch();// get the floor info
			if (message2 > '0' && message2 <= '9') {
				p1.Write(&message2); //send to dispatcher
			}
		}
		else {
			continue;
		}


		/*
		do {
			message = _getch();
			if (message == 'e') {
				ecounter++;
				if (ecounter == 2) {
					//notify dispatcher to go to 0
				}
			}
			else if (message == '+') {

			}
		} while (message != '1' || message != '2');
		*/
		message = _getch();
		p1.Write(&message); //1 or a 2
		message = _getch();
		printf("%d \n", message - 48);// print the floor we want to go to
		if (message > '0' && message <= '9') {
			string m1s = std::to_string(message);
			char b[100];
			strcpy_s(b, m1s.c_str());
			p1.Write(&message);
		}
	}
	return 0;
}
