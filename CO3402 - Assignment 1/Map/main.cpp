#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
using namespace std::chrono;
using std::cout;
using std::endl;
using std::string;
using std::ofstream;

//#define ConsoleOut

#include "map.h"
#include <map>
using std::map;
	
#ifdef ConsoleOut
	#define out cout
	#define sout cout
#else
	#define out testFile
	#define sout stestFile
	ofstream out = ofstream("testResults - myMap.txt");
	ofstream sout = ofstream("testResults - stlMap.txt");

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


void Test1CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Insert 5 items" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Input: " << i << ", " << i * 1.1f << endl;
		myMap.insert(i, i * 1.1f);
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		  
void Test2CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Find 5 items with function Find" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Key: " << i << " Result: " << myMap.find(i) << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		  
void Test3CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Find 5 items with operator[]" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Key: " << i << " Result: " << myMap[i] << endl;		
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		  
void Test4CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Insert the same 5 keys with alternate values " << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Input: " << i;
		myMap.insert(i, (i * 1.1f) + 1);
		out << " Data: " << myMap.find(i) << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;

}
		  
void Test5CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Find 5 items with function Find" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Key: " << i << " Result: " << myMap.find(i) << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		  
void Test6CMap(CMap<int, float> &myMap)
{

	///////////////////////////
	out << "Remove 8 items (3 of which dont exist) with function remove" << endl;
	float removedValue;
	bool wasRemoved;
	for (int i = 1; i <= 8; i++)
	{
		wasRemoved = myMap.remove(i, removedValue);
		out << "Key: " << i << " Removed: " << AsText(wasRemoved);
		if (wasRemoved)
		{
			out << " Value: " << removedValue;
		}
		out << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		  
void Test7CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Insert 5 items (with function find)" << endl;
	for (int i = 1; i <= 5; i++)
	{
		out << "Input: " << i << ", " << i * 1.1f << endl;
		myMap.find(i) = i * 1.1f;
	}
	out << "Current Size: " << myMap.size() << endl << endl;

}
		  
void Test8CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Add 3 to the value of 8 items (with function find) where 3 items don't exist" << endl;
	for (int i = 1; i <= 8; i++)
	{
		out << "Key: " << i;
		myMap.find(i) += 3;
		out << " Value: " << myMap.find(i) << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		  
void Test9CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Use iterator to find key and data of each item" << endl;
	for (CIterator<int, float> iter = myMap.IterBegin(); iter != myMap.IterEnd(); iter++)
	{
		out << "Key: " << (*iter).item1 << " Value: " << (*iter).item2 << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}

void Test10CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Remove selected items (keys divisible by 3)" << endl;
	float removedValue;
	bool wasRemoved;
	for (int i = 1; i <= 8; i++)
	{
		if (i % 3 == 0)
		{
			wasRemoved = myMap.remove(i, removedValue);
			out << "Key: " << i << " Removed: " << AsText(wasRemoved) << endl;
		}
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		 
void Test11CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Use iterator to find key and data of each item" << endl;
	for (CIterator<int, float> iter = myMap.IterBegin(); iter != myMap.IterEnd(); iter++)
	{
		out << "Key: " << (*iter).item1 << " Value: " << (*iter).item2 << endl;
	}
	out << "Current Size: " << myMap.size() << endl << endl;
}
		   
void Test12CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Use clear function to empty the map" << endl;
	myMap.clear();
	out << "Current Size: " << myMap.size() << endl << endl;
}
		   
void Test13CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Time to add 10,000 items to an empty map" << endl;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (int i = 0; i < 10000; i++)
	{
		myMap.insert(i, i * 1.1f);
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	long long noOfMilli = duration_cast<milliseconds>(end - start).count();
	out << "Time: " << noOfMilli << " MilliSeconds " << endl;
}
		   
void Test14CMap(CMap<int, float> &myMap)
{
	///////////////////////////
	out << "Time to add 100,000 items to an empty map" << endl;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		myMap.insert(i, i * 1.1f);
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	long long noOfMilli = duration_cast<milliseconds>(end - start).count();
	out << "Time: " << noOfMilli << " MilliSeconds " << endl;
}


void Test1STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Insert 5 items" << endl;
	for (int i = 1; i <= 5; i++)
	{
		sout << "Input: " << i << ", " << i * 1.1f << endl;
		myMap.insert(std::make_pair(i, i * 1.1f));
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test2STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Find 5 items with function Find" << endl;
	for (int i = 1; i <= 5; i++)
	{
		sout << "Key: " << i << " Result: " << (*myMap.find(i)).second << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test3STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Find 5 items with operator[]" << endl;
	for (int i = 1; i <= 5; i++)
	{
		sout << "Key: " << i << " Result: " << myMap[i] << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test4STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Insert the same 5 keys with alternate values " << endl;
	for (int i = 1; i <= 5; i++)
	{
		sout << "Input: " << i;
		myMap.insert(std::make_pair(i, (i * 1.1f) + 1));
		sout << " Data: " << (*myMap.find(i)).second << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;

}

void Test5STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Find 5 items with function Find" << endl;
	for (int i = 1; i <= 5; i++)
	{
		sout << "Key: " << i << " Result: " << (*myMap.find(i)).second << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test6STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Remove 8 items (3 of which dont exist) with function remove" << endl;
	float removedValue;
	int wasRemoved;
	for (int i = 1; i <= 8; i++)
	{
		wasRemoved = myMap.erase(i);
		sout << "Key: " << i << " Removed: " << AsText(wasRemoved) << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test7STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Insert 5 items (with function find)" << endl;
	//(*myMap.find(i)).second = i * 1.1f;
	sout << "Not allowed in stl implementation" << endl;
	sout << "Refill the array using insert instead" << endl;
	for (int i = 1; i <= 8; i++)
	{
		myMap.insert(std::make_pair(i, i * 1.1f));
	}
	sout << "Current Size: " << myMap.size() << endl << endl;

}

void Test8STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Add 3 to the value of 8 items (with function find) where 3 items don't exist" << endl;
	//sout << " Value: " << (*myMap.find(i)).second << endl;
	sout << "Not allowed in stl implementation" << endl;
	sout << "Insert 3 new values instead" << endl;
	for (int i = 5; i <= 8; i++)
	{
		myMap.insert(std::make_pair(i, 3.0f));
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test9STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Use iterator to find key and data of each item" << endl;
	for (map<int, float>::iterator iter = myMap.begin(); iter != myMap.end(); iter++)
	{
		sout << "Key: " << (*iter).first << " Value: " << (*iter).second << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test10STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Remove selected items (keys divisible by 3)" << endl;
	float removedValue;
	int wasRemoved;
	for (int i = 1; i <= 8; i++)
	{
		if (i % 3 == 0)
		{
			wasRemoved = myMap.erase(i);
			sout << "Key: " << i << " Removed: " << AsText(wasRemoved) << endl;
		}
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test11STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Use iterator to find key and data of each item" << endl;
	for (map<int, float>::iterator iter = myMap.begin(); iter != myMap.end(); iter++)
	{
		sout << "Key: " << (*iter).first << " Value: " << (*iter).second << endl;
	}
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test12STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Use clear function to empty the map" << endl;
	myMap.clear();
	sout << "Current Size: " << myMap.size() << endl << endl;
}

void Test13STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Time to add 10,000 items to an empty map" << endl;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (int i = 0; i < 10000; i++)
	{
		myMap.insert(std::make_pair(i, i * 1.1f));
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	long long noOfMilli = duration_cast<milliseconds>(end - start).count();
	sout << "Time: " << noOfMilli << " MilliSeconds " << endl;
}

void Test14STLMap(map<int, float> &myMap)
{
	///////////////////////////
	sout << "Time to add 100,000 items to an empty map" << endl;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	for (int i = 0; i < 100000; i++)
	{
		myMap.insert(std::make_pair(i, i * 1.1f));
	}
	high_resolution_clock::time_point end = high_resolution_clock::now();
	long long noOfMilli = duration_cast<milliseconds>(end - start).count();
	sout << "Time: " << noOfMilli << " MilliSeconds " << endl;
}

int main()
{

	CMap<int, float> myMap = CMap<int, float>();

	out << "My CMap: " << endl << endl;

	out << "Map Type: int, float" << endl;

	Test1CMap(myMap);
	
	Test2CMap(myMap);

	Test3CMap(myMap);
	
	Test4CMap(myMap);
	
	Test5CMap(myMap);

	Test6CMap(myMap);

	Test7CMap(myMap);

	Test8CMap(myMap);

	Test9CMap(myMap);

	Test10CMap(myMap);

	Test11CMap(myMap);

	Test12CMap(myMap);

	Test13CMap(myMap);

	Test14CMap(myMap);

	out << endl;

	//--------------------------------------------------------------

	map<int, float> stlMap = map<int, float>();


	sout << "STL Map: " << endl << endl;

	sout << "Map Type: int, float" << endl;

	Test1STLMap(stlMap);

	Test2STLMap(stlMap);

	Test3STLMap(stlMap);

	Test4STLMap(stlMap);

	Test5STLMap(stlMap);

	Test6STLMap(stlMap);

	Test7STLMap(stlMap);

	Test8STLMap(stlMap);

	Test9STLMap(stlMap);

	Test10STLMap(stlMap);

	Test11STLMap(stlMap);

	Test12STLMap(stlMap);

	Test13STLMap(stlMap);

	Test14STLMap(stlMap);

	sout << endl;

	system("pause");


	return 0;
}