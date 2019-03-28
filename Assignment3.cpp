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
	SmartPointer() {
		i = new T;
		(*i) = 0;
		//cout << "Created " << (*i) << endl;
	};

	SmartPointer(T j) {

		if (sizeof(j) > sizeof(T)) {
			throw "Error: This is too large.";
		}
		if (j < 0) {
			throw "We don't do negatives.";
		}
		i = new T(j);
		//cout << "Created " << (*i) << endl;
	};

	~SmartPointer() {
		delete i;
		i = NULL;
		cout << "Deleted" << endl;
	};

	T setValue(T j);
	T getValue();
	
	friend SmartPointer operator+(const SmartPointer<T> &sp1, const SmartPointer<T> &sp2) {
		SmartPointer<T> result(0);
		T* p1 = sp1.i;
		T* p2 = sp2.i;
		T sum;
		sum= (*p1) + (*p2);
		result.setValue(sum);
		return result;
	};

	friend SmartPointer operator-(const SmartPointer<T> &sp1, const SmartPointer<T> &sp2) {
		SmartPointer<T> result(0);
		T* p1 = sp1.i;
		T* p2 = sp2.i;
		T sum;
		sum = (*p1) - (*p2);
		if (sum < 0) {
			throw "We don't do negatives.";
		}
		result.setValue(sum);
		return result;
	};

	friend SmartPointer operator*(const SmartPointer<T> &sp1, const SmartPointer<T> &sp2) {
		SmartPointer<T> result(0);
		T* p1 = sp1.i;
		T* p2 = sp2.i;
		T sum;
		sum = (*p1) * (*p2);
		result.setValue(sum);
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
	this->i = new T(j);
	return 0;
}

template <class T>
T SmartPointer<T>::getValue() {
	return (*i);
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

	SmartPointer<float> SmartFloatPointer3 = SmartFloatPointer1 + SmartFloatPointer2;
	cout << "SmartFloatPointer1 + SmartFloatPointer2 = " << SmartFloatPointer3.getValue() << endl;

	SmartPointer<float> SmartFloatPointer4 = SmartFloatPointer2 - SmartFloatPointer1;
	cout << "SmartFloatPointer2 - SmartFloatPointer1 = " << SmartFloatPointer4.getValue() << endl;

	SmartPointer<float> SmartFloatPointer5 = SmartFloatPointer1 * SmartFloatPointer2;
	cout << "SmartFloatPointer1 * SmartFloatPointer2 = " << SmartFloatPointer5.getValue() << endl;

	return 0;

}
