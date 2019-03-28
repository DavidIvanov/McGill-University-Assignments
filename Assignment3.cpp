#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <exception>
using namespace std;

template <class T>
class SmartPointer
{
private:
	T* i;
public:
	SmartPointer(){
		i = new T;
		(*i) = 0;
		cout << "Created " << (*i) << endl;
	};
	
	SmartPointer(T j){
		i = new T;
		if (sizeof(j) > sizeof(T)) {
			throw "Error: This is too large.";
		}
		if (j < 0) {
			throw "We don't do negatives.";
		}
		this->i = &j;
		cout << "Created " << (*i) << endl;
	};

	~SmartPointer(){
		delete i;
		i = NULL;
		cout << "Deleted" << endl;
	};
	
	
	T setValue(T j);
	T getValue();
	friend SmartPointer<T> operator+(const SmartPointer<T>& sp){
		SmartPointer<T> result;
		result.(*i) = this->(*i)+ sp.(*i);
		return result;
	};

};

template <class T>
T SmartPointer<T>::setValue(T j) {
	if (sizeof(j) > sizeof(T)) {
		throw "Error: This is too large.";
	}
	if (j < 0) {
		throw "We don't do negatives.";
		
	}
	this->i = &j;
	return 0;
}

template <class T>
T SmartPointer<T>::getValue() {
	return *i;
}



int main() {
	
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

	

}

