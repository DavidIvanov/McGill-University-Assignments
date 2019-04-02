//David Ivanov ID:260806837
/*
There are 3 types of smartpointers: unique_pointer,  shared_pointer and the weak_pointer.
Unique_pointer is a pointer which owns a dynamically allocated ressource and it can only be the one pointing to it.
Shared_pointer is a pointer which owns a dynamically allocated ressource, it contains a counter which keeps track of
how many pointers are pointing to that allocated ressource. Multiple shared_pointers can point to the same data.
The weak_pointer holds a reference to an allocated ressources it does not own. It can share the ressource it points to
and it does not keep track of how many pointers are looking at that ressource.
*/


#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <exception>
using namespace std;

// below is a class which uses templates. If no template is stated it is automatically set to integer. Compatible with int, double and float
template <class T = int>
class SmartPointer //smart pointer class
{
private:
	T* i; // points to data 
	int size;  //stores size of array. if storing single values stores 1.
public:
	//constructor for single value no input
	SmartPointer() {
		
		size = 1;
		i = new T[1];
		(*i) = 0;
		
	};
	//constructor for single value with input. thorws exception if input is negative
	SmartPointer(T j) {
		size = 1;
		if (j < 0) {
			throw "Negatives cannot be inputed!";
		}
		i = new T[1];
		(*i) = j;
	};

	//constructor for array. takes size of array and array/pointer as an input. throws exception if array value is negative 
	SmartPointer(T j[], int _size) {
		size = _size;
		i = new T[size];
		for (int k = 0; k < size; k++) {
			if (*(j + k) < 0) {
				throw "Negatives cannot be inputed!";
			}

			i[k] = *(j + k);
		}
		
	}
	//destructor deletes all data
	~SmartPointer() {
		delete[] i;
		i = NULL;
	};


	T setValue(T j);            //set value for singular
	T setValue(T j, int index); //set value for array
	T getValue();               //get value for singular
	T getValue(int index);	    //get value for array

	//operator+ overload for arrays of the size or singular values
	friend SmartPointer operator+(const SmartPointer<T> &sp1, const SmartPointer<T> &sp2) {
		if (sp1.size != sp2.size) { //verify if both arrays are if the same size 
			throw "Check sizes first.";
		}

		int sizes = sp1.size;
		T* arr = new T[sizes];
		SmartPointer<T> result(arr, sizes);
		for (int k = 0; k < sizes; k++) { // add all values of corresponding indices
			T p1 = sp1.i[k];
			T p2 = sp2.i[k];
			T sum;
			sum = (p1)+(p2);
			result.setValue(sum, k);
		}
		return result;
	};

	//operator- overload for arrays of the size or singular values. throws exception if negative value is computed
	friend SmartPointer operator-(const SmartPointer<T> &sp1, const SmartPointer<T> &sp2) {
		if (sp1.size != sp2.size) {
			throw "Check sizes first.";
		}

		int sizes = sp1.size;
		T* arr = new T[sizes];
		SmartPointer<T> result(arr, sizes);
		for (int k = 0; k < sizes; k++) { //compute the difference between the corresponding indices
			T p1 = sp1.i[k];
			T p2 = sp2.i[k];
			T diff;
			diff = (p1)-(p2);
			if (diff < 0) {
				throw "We don't do negatives";
			}
			result.setValue(diff, k);
		}
		return result;
	};
	//operator* overload for arrays of the size or singular values.
	friend SmartPointer operator*(const SmartPointer<T> &sp1, const SmartPointer<T> &sp2) {
		if (sp1.size != sp2.size) {
			throw "Check sizes first.";
		}

		int sizes = sp1.size;
		T* arr = new T[sizes];
		SmartPointer<T> result(arr, sizes);
		for (int k = 0; k < sizes; k++) { //computes the product of the corresponding indices
			T p1 = sp1.i[k];
			T p2 = sp2.i[k];
			T total;
			total = (p1)*(p2);
			result.setValue(total, k);
		}
		return result;
	};
};

//sets value at pointer for singular. throws exception if negative
template <class T>
T SmartPointer<T>::setValue(T j) {
	if (j < 0) {
		throw "We don't do negatives.";
	}
	(*i) = j;
	return 0;
}

//sets value at index in array. throws exception if negative or if out of bounds.
template <class T>
T SmartPointer<T>::setValue(T j, int index) {
	if (j < 0) {
		throw "We don't do negatives.";
	}
	if (index >= size) {
		throw "You are out of bounds.";
	}
	i[index] = j;
	return i[index];
}

//gets value for the singular
template <class T>
T SmartPointer<T>::getValue() {
	return (*i);
}

//get value for the array at index or returns 0 if out of bounds
template <class T>
T SmartPointer<T>::getValue(int index) {
	if (index >= size || index <0) {
		return 0;
	}
	return i[index];
}

int main() {

	try {
		cout << "Testing error throwing" << endl;
		SmartPointer<> sp1(-1);
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	
	try {
		cout << "Creating a SmartPointer of type int with no value provided" << endl;
		SmartPointer<int> SmartIntPointer2;
		cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

		// Testing Setter & Getter
		cout << "Setting value of SmartIntPointer2 to 5" << endl;
		SmartIntPointer2.setValue(5);
		cout << "SmartIntPointer2 = " << SmartIntPointer2.getValue() << endl;

		cout << "Creating a SmartPointer of type float with no value provided" << endl;
		SmartPointer<float> SmartFloatPointer1;
		cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

		cout << "Setting value of SmartFloatPointer1 to 1.5" << endl;
		SmartFloatPointer1.setValue(1.5);
		cout << "SmartFloatPointer1 = " << SmartFloatPointer1.getValue() << endl;

		cout << "Creating a SmartPointer of type float with no value provided" << endl;
		SmartPointer<float> SmartFloatPointer2;
		cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

		cout << "Setting value of SmartFloatPointer2 to 2.5" << endl;
		SmartFloatPointer2.setValue(2.5);
		cout << "SmartFloatPointer2 = " << SmartFloatPointer2.getValue() << endl;

		SmartPointer<float> SmartFloatPointer3 = SmartFloatPointer1 + SmartFloatPointer2;
		cout << "SmartFloatPointer1 + SmartFloatPointer2 = " << SmartFloatPointer3.getValue() << endl;

		SmartPointer<float> SmartFloatPointer4 = SmartFloatPointer2 - SmartFloatPointer1;
		cout << "SmartFloatPointer2 - SmartFloatPointer1 = " << SmartFloatPointer4.getValue() << endl;

		SmartPointer<float> SmartFloatPointer5 = SmartFloatPointer1 * SmartFloatPointer2;
		cout << "SmartFloatPointer1 * SmartFloatPointer2 = " << SmartFloatPointer5.getValue() << endl;
		//testing arrays
		//testing constructor and get value
		cout << "Testing array constructor and getValue for arrays" << endl;
		float f[] = { 1, 4, 6, 7, 5, 20, 8, 9 };
		SmartPointer<float> SmartArray1(f, 8);
		cout << "SmartArray1: ";
		for (int i = 0; i < 8; i++) {
			cout << SmartArray1.getValue(i) << " ";
		}
		cout << endl;

		//testing setValue for arrays
		cout << "Testing setValue for arrays" << endl;
		cout << "SmartArray2: ";
		SmartPointer<float> SmartArray2(f, 8);
		for (int i = 0; i < 8; i++) {
			cout << SmartArray2.setValue(i, i) << " ";
		}
		cout << endl;

		//testing all operators
		cout << "Testing + operator" << endl;
		cout << "SmartArray3 = SmartArray1 + SmartArray2 = ";

		SmartPointer<float> SmartArray3 = SmartArray1 + SmartArray2;
		for (int i = 0; i < 8; i++) {
			cout << SmartArray3.getValue(i) << " ";
		}
		cout << endl;

		cout << "Testing - operator" << endl;
		cout << "SmartArray4 = SmartArray1 - SmartArray2 = ";

		SmartPointer<float> SmartArray4 = SmartArray1 - SmartArray2;
		for (int i = 0; i < 8; i++) {
			cout << SmartArray4.getValue(i) << " ";
		}
		cout << endl;

		cout << "Testing * operator" << endl;
		cout << "SmartArray5 = SmartArray1 * SmartArray2 = ";

		SmartPointer<float> SmartArray5 = SmartArray1 * SmartArray2;
		for (int i = 0; i < 8; i++) {
			cout << SmartArray5.getValue(i) << " ";
		}
		cout << endl;
	}
	catch (bad_alloc& e) {

		cout << "Out of memory!"<<endl;
	}


}
