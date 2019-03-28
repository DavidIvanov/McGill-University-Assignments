//David Ivanov ID:260806837

using namespace std;
#include <iostream>
#include <ctype.h>
#include <cstdlib>

//Ticket struct has the properties of an array of numbers and next which is the following ticket
struct ticket
{
	unsigned int numbers[ 6 ];
	ticket* next;
};

//SuperDraw class comes with a multitude of methods
//Its attributes consist of 2 ticket pointers, one to the start of the chain and one at the end
class SuperDraw
{	private :
		ticket* ticketListHead;
		ticket* ticketListTail;
	public :
		SuperDraw();
		SuperDraw(int x);
		~SuperDraw();
		newTicket(int verbose =0);
		printAllTicketNumbers();
		verifySequence(int pnumbers[6]);
		deleteSequence(int pnumbers[6]);
		SuperDraw(const SuperDraw &sd);
	
};

//Basic constructor initializes both pointers to NULL
SuperDraw::SuperDraw(){
	this->ticketListHead = NULL;
	this->ticketListTail = NULL;
}

//Constructor which adds tickets according to inputed integer
SuperDraw::SuperDraw(int x){
	//initializes both pointers to NULL for safety
	this->ticketListHead = NULL;
	this->ticketListTail = NULL;
	//if the input is less than or equal to zero end constructor process
	if(x<=0){
		return;
	}
	
	cout << x << " tickets were generated." << endl;
	cout << "The number are : "<< endl;
	//adds the desired amount of tickets to the SuperDraw object
	for(int i = 1; i<=x;i++){
		this->newTicket();
	}
	
	//Runs through the tickets and prints out their values using 2 for loops
	ticket* newticket = this->ticketListHead;
	for(int i = 1; i<=x; i++){
		for(int j =0; j<6; j++){
			cout << (*newticket).numbers[j] << " ";
		}
		newticket= (*newticket).next;	
		cout << endl;
	}
	//points pointer to null for safety
	newticket = NULL;
}


//copy constructor takes as input the reference to a SuperDraw object
SuperDraw::SuperDraw(const SuperDraw &sd){
	//intialize pointers to null for safety
	this->ticketListHead = NULL;
	this->ticketListTail = NULL;
	//if the provided sd reference is null then end the process
	if(!&sd){
		return;
	}
	
	//while loop to count the number of tickets in the sd object
	ticket* ptrToSd;
	ptrToSd = sd.ticketListHead;
	int nbrOfTickets= 0;
	while(ptrToSd){
		nbrOfTickets++;
		ptrToSd = (*ptrToSd).next;
	}
	
	//for loop to add the according number of tickets
	for(int i=1 ; i<=nbrOfTickets; i++){
		this->newTicket();	
	}
	
	//while loop to equate the numbers in the new superdraw to the one being copied
	ticket* ptr;
	ptrToSd = sd.ticketListHead;
	ptr = this->ticketListHead;
	while(ptr){
		//for loop here copies the numbers
		for(int i=0; i<6; i++){
			(*ptr).numbers[i] = (*ptrToSd).numbers[i];
		}
		ptr = (*ptr).next;
		ptrToSd = (*ptrToSd).next;
	}
	//ptrs go to null for safety
	ptr =NULL;
	ptrToSd =NULL;
}

//SuperDraw destructor
SuperDraw::~SuperDraw(){
	//ptrs below are responsible for fetching the information in the SuperDraw object
	//and deleting each ticket
	ticket* ptr;
	ticket* ptrNext;
	ptr= ticketListHead;
	ptrNext = (*ptr).next;
	//while loop goes through all the tickets and deletes their data
	while(ptrNext){
		delete ptr;
		ptr = ptrNext;
		ptrNext = (*ptrNext).next;
	}
	//deletes ticket pointer attribute for safety
	ticketListHead= NULL;
	ticketListTail= NULL;
	cout<< "done";
}

//newTicket method adds a ticket to the superDraw and take as input an integer to know if it should print the contents of the added ticket
SuperDraw::newTicket(int verbose){
	//new ticket struct is created and initialized
	ticket* newticket = new ticket;
	(*newticket).next = NULL;
	for(int i =0; i<6; i++){
		(*newticket).numbers[i] = rand()%50;
	}
	
	//if there is no head then then the new ticket becomes the head
	if(!ticketListHead){
			ticketListHead = newticket;
			ticketListTail = NULL;
	}else if(!ticketListTail){//if there is no tail then make the new ticket the tail
		ticketListTail = newticket;
		(*ticketListHead).next = newticket;	
	} else{ //otherwise add it to the tail and move the ticketListTail back by one
		(*ticketListTail).next = newticket;
		ticketListTail = newticket;
	}
	
	//if the user desires print out the contents of the ticket
	if(verbose == 1){
		cout<< "A new ticket was successfully generated. The numbers are : ";
		for(int i =0; i<5; i++){
			cout << (*newticket).numbers[i]<<", ";
		}
		cout<< (*newticket).numbers[5]	<< endl;	
	}
	//point pointer to null for safety
	newticket = NULL;
}

//SuperDraw method which prints all the tickets and their numbers
SuperDraw::printAllTicketNumbers(){
	//while loop below is used to run through all the tickets and count them
	ticket *ptr;
	ptr = ticketListHead;
	int nbrOfTickets= 0;
	while(ptr){
		nbrOfTickets++;
		ptr = (*ptr).next;
	}
	cout <<"We found " <<nbrOfTickets<< " generated tickets:"<< endl;
	
	//while loop below is used to run through the tickets and print their values
	ptr = ticketListHead;
	while(ptr){
		for(int i =0; i<5; i++){
			cout << (*ptr).numbers[i]<<", ";
		}
		cout<< (*ptr).numbers[5] << endl;
		ptr = (*ptr).next;
		
	}
	//send pointer to null for safety
	ptr = NULL;
	
}

//verifySequence runs through the tickets and checks if there is a ticket with the inputed sequence of numbers
//in the arraylist of size 6
SuperDraw::verifySequence(int pnumbers[6]){
	ticket* ptr;
	ptr = ticketListHead;
	//boolean will go to true if the ticket is found
	bool found = false;
	//while loop runs through the tickets
	while(ptr){
		//boolean will go to false if 1 number does not match
		bool match = true;
		//for loop runs through the number on the ticket
		for(int i = 0; i<6; i++){
			if((*ptr).numbers[i]!=pnumbers[i]){
				match =false;
				break;
			}
		}
		//if match stayed true then we found the ticket, found becomes true and the while loop breaks
		if(match){
			found =true;
			break;
		}
		ptr = (*ptr).next;
	}
	
	//if statement provides the right printed statement
	if(found){
		cout << "The provided sequence of numbers was already generated."<< endl;
	} else{
		cout<< "The provided sequence of numbers was never generated before"<< endl;
	}
	//ptr is sent to null for safety
	ptr = NULL;
}

//deleteSequence finds the ticket with the appropriate sequence using the inputed integer array of size 6
//and removes it from the SuperDraw
SuperDraw::deleteSequence(int pnumbers[6]){
	ticket* ptr;
	ticket* previousPtr = NULL;
	ptr = ticketListHead;
	bool found = false; //will go true if ticket is found
	//while loop used to run through the tickets
	while(ptr){
		bool match = true; //will go false if numbers dont match
		//for loop runs through the numbers
		for(int i = 0; i<6; i++){
			if((*ptr).numbers[i]!=pnumbers[i]){//checks if numbers mismatch
				match =false;
				break;
			}
		}
		//if match stayed true then found is true and loop breaks
		if(match){
			found =true;
			break;
		}
		previousPtr = ptr; //saved address for later
		ptr = (*ptr).next;
	}
	
	if(found){	
		if(ptr==ticketListHead){//if the ticket to delete is the head
			ticketListHead = (*ptr).next;
			delete ptr;
		}else if(ptr == ticketListTail){ //if the object to delete is the tail
			ticketListTail = previousPtr;
			(*ticketListTail).next = NULL;
			delete ptr;
		} else{ //otherwise
			(*previousPtr).next = (*ptr).next;
			delete ptr;
		}
		cout<< "The provided sequence of numbers has been successfully deleted."<<endl;
		
	} else {
		cout<< "The provided sequence of numbers was never generated before"<< endl;
	}
	
	//send pointers to NULL for safety
	previousPtr = NULL;
	ptr = NULL;
	
} 


int main(){
	
	
	SuperDraw sd(1);
	sd.newTicket(1);
	SuperDraw sd2(sd);
	// as many sd.newTicket() as you like
	sd2.printAllTicketNumbers();
	int i[] = {41, 17, 34, 0, 19, 24};
	sd2.deleteSequence(i);
	sd2.printAllTicketNumbers();
	

	
	
	return 0;
}
