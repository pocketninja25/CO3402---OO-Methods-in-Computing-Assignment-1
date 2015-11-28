#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std::chrono;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;

#define MyMapType	//Keep this commented in to use my implementation, comment it out to use the stl implementation //May have to use ifdefs elsewhere should my implementation diverge
//#define ConsoleOut

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
	
#ifdef ConsoleOut
	#define out cout
#else
	#define out testFile
	#ifdef MyMapType
		ofstream out = ofstream("testResults - myMap.txt");
	#else
		ofstream out = ofstream("testResults - stlMap.txt");
	#endif
#endif

inline string AsText(bool booleanValue)
{
	if (booleanValue)
	{
		return "success";
	}
	else
	{
		return "fail";
	}
}

int main()
{

	MAP<int, float> myMap = MAP<int, float>();

#ifdef MyMapType
	out << "My CMap: " << endl << endl;
#else
	out << "STL Map: " << endl << endl;
#endif
	out << "Map Type: int, float" << endl;

	///////////////////////////
	out << "Insert 5 items" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Input: " << i << ", " << i * 1.1f << endl;
#ifdef MyMapType
		myMap.insert(i, i * 1.1f);
#else
		myMap.insert(std::make_pair(i, i * 1.1f));
#endif
	}
	out << "Current Size: " << myMap.size() << endl << endl;
	
	///////////////////////////
	out << "Find 5 items with function Find" << endl;
	for (int i = 1; i <= 5; i++)
	{
#ifdef MyMapType
		out << "Key: " << i << " Result: " << myMap.find(i) << endl;
#else
		out << "Key: " << i << " Result: " << (*myMap.find(i)).second << endl;
#endif
	}
	out << "Current Size: " << myMap.size() << endl << endl;
	
	///////////////////////////
	out << "Find 5 items with operator[]" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Key: " << i << " Result: " << myMap[i] << endl;		
	}
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Insert the same 5 keys with alternate values " << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Input: " << i;
#ifdef MyMapType
		myMap.insert(i, (i * 1.1f) + 1);
		out << " Data: " << myMap.find(i) << endl;
#else
		myMap.insert(std::make_pair(i, (i * 1.1f) + 1));
		out << " Data: " << (*myMap.find(i)).second << endl;
#endif
	}
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Find 5 items with function Find" << endl;
	for (int i = 1; i <= 5; i++)
	{
#ifdef MyMapType
		out << "Key: " << i << " Result: " << myMap.find(i) << endl;
#else
		out << "Key: " << i << " Result: " << (*myMap.find(i)).second << endl;
#endif
	}
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Remove 8 items (3 of which dont exist) with function remove" << endl;
	float removedValue;
#ifdef MyMapType
	bool wasRemoved;
#else
	int wasRemoved;
#endif
	for (int i = 1; i <= 8; i++)
	{
#ifdef MyMapType
		wasRemoved = myMap.remove(i, removedValue);
		out << "Key: " << i << " Removed: " << AsText(wasRemoved);
		if (wasRemoved)
		{
			out << " Value: " << removedValue;
		}
		out << endl;
#else
		
		wasRemoved = myMap.erase(i);
		out << "Key: " << i << " Removed: " << AsText(wasRemoved) << endl;
#endif
	}
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Insert 5 items (with function find)" << endl;
#ifdef MyMapType
	for (int i = 1; i <= 5; i++)
	{
		out << "Input: " << i << ", " << i * 1.1f << endl;
		myMap.find(i) = i * 1.1f;
	}
#else
	//(*myMap.find(i)).second = i * 1.1f;
	out << "Not allowed in stl implementation" << endl;
	out << "Refill the array using insert instead" << endl;
	for (int i = 1; i <= 8; i++)
	{
		myMap.insert(std::make_pair(i, i * 1.1f));
	}
#endif
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Add 3 to the value of 8 items (with function find) where 3 items don't exist" << endl;
#ifdef MyMapType
	for (int i = 1; i <= 8; i++)
	{
		out << "Key: " << i;
		myMap.find(i) += 3;
		out << " Value: " << myMap.find(i) << endl;
	}
#else
		//out << " Value: " << (*myMap.find(i)).second << endl;
		out << "Not allowed in stl implementation" << endl;
		out << "Insert 3 new values instead" << endl;
		for (int i = 5; i <= 8; i++)
		{
			myMap.insert(std::make_pair(i, 3.0f));
		}
#endif
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Use iterator to find key and data of each item" << endl;
#ifdef MyMapType
	for (CIterator<int, float> iter = myMap.IterBegin(); iter != myMap.IterEnd(); iter++)
	{
		out << "Key: " << (*iter).item1 << " Value: " << (*iter).item2 << endl;
	}
#else
	for (map<int, float>::iterator iter = myMap.begin(); iter != myMap.end(); iter++)
	{
		out << "Key: " << (*iter).first << " Value: " << (*iter).second << endl;
	}
#endif
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Remove selected items (keys divisible by 3)" << endl;
	for (int i = 1; i <= 8; i++)
	{
		if (i % 3 == 0)
		{
#ifdef MyMapType
			wasRemoved = myMap.remove(i, removedValue);
#else
			wasRemoved = myMap.erase(i);
#endif
			out << "Key: " << i << " Removed: " << AsText(wasRemoved) << endl;
		}
	}
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Use iterator to find key and data of each item" << endl;
#ifdef MyMapType
	for (CIterator<int, float> iter = myMap.IterBegin(); iter != myMap.IterEnd(); iter++)
	{
		out << "Key: " << (*iter).item1 << " Value: " << (*iter).item2 << endl;
	}
#else
	for (map<int, float>::iterator iter = myMap.begin(); iter != myMap.end(); iter++)
	{
		out << "Key: " << (*iter).first << " Value: " << (*iter).second << endl;
	}
#endif
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Use clear function to empty the map" << endl;
	myMap.clear();
	out << "Current Size: " << myMap.size() << endl << endl;

	///////////////////////////
	out << "Time to add 10,000 items to an empty map" << endl;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (int i = 0; i < 10000; i++)
	{
#ifdef MyMapType
		myMap.insert(i, i * 1.1f);
#else
		myMap.insert(std::make_pair(i, i * 1.1f));
#endif
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	long long noOfMilli = duration_cast<milliseconds>(end - start).count();
	out << "Time: " << noOfMilli << " MilliSeconds " << endl;

	///////////////////////////
	out << "Time to add 100,000 items to an empty map" << endl;
	start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
	{
#ifdef MyMapType
		myMap.insert(i, i * 1.1f);
#else
		myMap.insert(std::make_pair(i, i * 1.1f));
#endif
	}
	end = high_resolution_clock::now();
	noOfMilli = duration_cast<milliseconds>(end - start).count();
	out << "Time: " << noOfMilli << " MilliSeconds " << endl;

	out << endl;

	system("pause");


	return 0;
}