#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#define MyMapType	//Keep this commented in to use my implementation, comment it out to use the stl implementation //May have to use ifdefs elsewhere should my implementation diverge

//Decides which map to use based on if CMAP is defined
#ifdef MyMapType
	#include "CMap.h"
	#define MAP CMap
#else
	#include <map>
	using std::map;
	using std::make_pair;
	#define MAP map
#endif

int main()
{
	MAP<char, float> myMap = MAP<char, float>();

	//Output fresh items
	cout <<	myMap.find('1') << endl;
	cout <<	myMap['4'] << endl;
	cout <<	myMap['3'] << endl;
	cout <<	myMap['2'] << endl;
	cout <<	myMap['5'] << endl;
	cout << endl;

	//Assign data to items
	myMap['1'] = 1.1f;
	myMap['4'] = 4.4f;
	myMap['3'] = 3.3f;
	myMap['2'] = 2.2f;
	myMap['5'] = 5.5f;

	//Reassign data to items
	myMap['1'] = 2.2f;
	myMap['2'] = 3.3f;
	myMap['3'] = 4.4f;
	myMap['4'] = 5.5f;
	myMap['5'] = 6.6f;

	//Output reassigned values
	cout << myMap.find('1') << endl;
	cout << myMap['5'] << endl;
	cout << myMap['3'] << endl;
	cout << myMap['2'] << endl;
	cout << myMap['4'] << endl;
	cout << endl;

	myMap.remove('3');
	
	cout << myMap.find('1') << endl;
	cout << myMap['5'] << endl;
	cout << myMap['3'] << endl;
	cout << myMap['2'] << endl;
	cout << myMap['4'] << endl;
	cout << endl;


	//Figure out how to guarantee the operators used within the class are supported by the key and the data
	
	system("pause");


	return 0;
}