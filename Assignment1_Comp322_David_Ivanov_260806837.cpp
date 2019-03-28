//David Ivanov ID:260806837

using namespace std;
#include <iostream>
#include <ctype.h>

//function with a void return type and no input
//which counts the number of times a char appears in a string
void countLetter(){
	//declaration of the 3 required variables 
	string sentence;  //will contain the sentence
	char letter;	  //will contain the letter selected
	int count = 0;    //will count how many time the letter is in the sentence
	
	cout<< "Please enter your sentence: ";	
	getline(cin, sentence);                                                                  //used to be able to collect the full sentence the user has inputed
	cout<< "Please enter your letter (Only the first letter inputted will be considered): "; 
	cin>> letter;                                                                            //letter variable is char type so it can only store the first char the user will input
	letter = (char) tolower(letter);                                                         // puts the letter to lowercase to make the comparison easier
	
	//for loop which runs through the string and counts the number of times the letter appears
	for(int i = 0; i<sentence.size(); i++){
		if((char) tolower(sentence[i]) == letter){
			count++;
		}
	}
	
	// a couple of if statements just to make sure that the output is grammatically correct
	if(count == 1)
		cout<< "The letter " << letter << " is repeated " << count << " time in your sentence.";	
	else if (count == 0)
		cout<< "The letter " << letter << " is not in your sentence.";
	else
		cout<< "The letter " << letter << " is repeated " << count << " times in your sentence.";
		
	cout<<"\n" << "\n";

}

//function with void return type and no input
//which takes a word and then converts it using the Nato phonetic alphabet
void convertPhonetic(){
	string word;          //this variable will take the inputted word by the user
	//the variable below is the Nato Phonetic Alphabet
	string natoAlphabet[26] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"};
	
	cout<< "Please enter a word: ";
	cin>>word;
	
	//loop which runs through every letter of the word
	for(int i =0; i<word.size(); i++){
		
		int j = tolower(word[i])-97; //j will adjust the characters in word using "a" as the pivot of the ascii table
		
		cout << natoAlphabet[j] << " "; //print the word representing each letter
	}
	cout<<"\n" << "\n";
}
/*
Question 3:
	Tail recursion is the idea of avoiding recalculating/redoing things that have already been computed
	by including another variable in the method which will carry that calculation to avoid repetitions. 
	Ultimately, it speeds up the running time by avoiding repetitive computations.
	
	Not all recursive functions can be written tail recursively. For example, sorting algorithms like quicksort
	and mergesort which depend on recursion cannot be written as such since they cannot be tailed. Functions
	that do computations can take advantage of tail recursion but sorting recursions and sometimes in dynamic
	programming it is impossible because adding an accumulator or some sort of extra counter wouldn't work.
*/
//helper method
int factorialCalculation(int x, int accumulator){ //calculates factorial of x tail recursively
	if(x==0)
		return accumulator;
	else
		return factorialCalculation(x-1,x*accumulator);		
}


void factorial(){//works out the inputs and output for the result calculated
	int x = 0;
	
	cout << "Please enter a number: ";
	cin >> x;
	if(x<0){ //making sure you cant input a negative number
		cout<< "Please input a whole positive number next time!";
		return;
	}
	cout<< "The factorial of " << x << " is " << factorialCalculation(x, 1);
	cout<<"\n" << "\n";
}


int enhancedFactorialCalculation(int x, int accumulator, int preCalculatedResult, int value){ //helper method which also takes extra inputs to reduce the number of calculations
	if(x==value)                                                                              //The preCalculatedResult and value will be received from the precalculated array
		return accumulator*preCalculatedResult;
	else
		return enhancedFactorialCalculation(x-1,x*accumulator, preCalculatedResult, value);		
}

void enhancedFactorial(){ //this is the enhancedFactorial method which uses the array of precalculated values to reduce the amount of calculations
	int x = 0;
	int preCalculatedFactorial[6] = { 1, 2, 6, 24, 120, 720 };
	
	cout << "Please enter a number: ";
	cin >> x;
	if(x<0){
		cout<< "Please input a whole positive number next time!";
		return;
	}
	if(x==0){//if zero is inputted print value from the array
		cout<< "The factorial of " << x << " is " << preCalculatedFactorial[0];	
	} else if(x<=6){//if less or equal to 6 grab value from the array
		cout<< "The factorial of " << x << " is " << preCalculatedFactorial[x-1];
	} else { // if more than 6 use helper function to output result
		cout<< "The factorial of " << x << " is " << enhancedFactorialCalculation(x, 1, preCalculatedFactorial[5], 6);	
	}
	
	cout<<"\n" << "\n";	
}

int main(){
	countLetter();	
	
	convertPhonetic();
	
	factorial();
	
	enhancedFactorial();
	
	return 0;
}


