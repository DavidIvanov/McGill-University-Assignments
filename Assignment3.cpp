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
	int size;
public:
	SmartPointer() {
		size = 1;
		i = new T[1];
		(*i) = 0;
		//cout << "Created " << (*i) << endl;
	};

	SmartPointer(T j) {
		size = 1;
		if (sizeof(j) > sizeof(T)) {
			throw "Error: This is too large.";
		}
		if (j < 0) {
			throw "We don't do negatives.";
		}
		i = new T[1];
		(*i) = j;
		//cout << "Created " << (*i) << endl;
	};

	SmartPointer(T j[], int _size) {
		size = _size;
		i = new T[size];
		for (int k = 0; k < _size; k++) {
			i[k] = j[k];
		}
	}

	~SmartPointer() {
		delete[] i;
		i = NULL;
		cout << "Deleted" << endl;
	};


	T setValue(T j);
	T setValue(T j, int index);
	T getValue();
	T getValue(int index);

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
		T diff;
		diff = (*p1) - (*p2);
		if (diff < 0) {
			throw "We don't do negatives.";
		}
		result.setValue(diff);
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
	(*i) = j;
	return 0;
}

template <class T>
T SmartPointer<T>::setValue(T j, int index) {
	if (sizeof(j) > sizeof(T)) {
		throw "Error: This is too large.";
	}
	if (j < 0) {
		throw "We don't do negatives.";
	}
	if (index >= size) {
		throw "You are out of bounds.";
	}
	i[index] = j;
	return i[index];
}

template <class T>
T SmartPointer<T>::getValue() {
	return (*i);
}

template <class T>
T SmartPointer<T>::getValue(int index) {
	if (index >= size) {//maybe throw exception
		return 0;
	}
	return i[index];
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
	
	float arr[] = {1, 2, 3, 4, 5, 6, 7};
	SmartPointer<float> smartArray(arr, 7);

	for (int i = 0; i < 7; i++) {
		smartArray.setValue((float) i, i);
		cout << smartArray.getValue(i) << " ";
	}
	cout << endl;

	return 0;


}
