#pragma once
#include "Pair.h"

template <typename TKey, typename TData>

class CMap
{
private:
	SPair<TKey, TData>* m_Array;	//The array of data items (using pointer type to allow dynamic reallocation of size by creating new array at runtime)
	int m_ArrayMax;					//The current amount of maximum items the array can store without allocating a new array
	int m_ArrayTop;					//The amount of items currently in the array, also can be used to 'point at' the top of the array

public:
	//Create a map of size 'mapSize', this is not necessarily the final size of the map, just a starting point, the map can grow in size
	CMap(int mapSize = 50)
	{
		m_ArrayTop = 0;
		m_ArrayMax = mapSize;		
		m_Array = new SPair<TKey, TData>[m_ArrayMax];
	}
	//Map destructor
	~CMap()
	{
		delete[] m_Array;
	}
	//Override copy constructor to deep copy
	CMap(const CMap<TKey, TData>& iOriginal)	
	{
		//Constructs a new object using a copy

		m_ArrayMax = iOriginal->m_ArrayMax;
		m_ArrayTop = iOriginal->m_ArrayTop;
		//Allocate new array
		m_Array = new SPair<TKey, TData>[iOriginal->m_ArrayMax];
		//Copy array data from original to copy
		for (int i = 0; i < m_ArrayTop; i++)
		{
			m_Array[i] = iOriginal->m_Array[i];
		}

	}
	CMap& CMap::operator=(const CMap &iOriginal)
	{
		//Modifies an existing object using a copy

		//Check for self assignment, if this happens then just return this as there is no point assigning something to itself
		if (this == iOriginal)
		{
			return *this;
		}

		//Copy basic members over
		m_ArrayMax = iOriginal->m_ArrayMax;
		m_ArrayTop = iOriginal->m_ArrayTop;
		//Deallocate this array ready to copy the 'original' array
		delete[] m_Array;
		m_Array = new SPair<TKey, TData>[iOriginal->m_ArrayMax];
		//Copy array data from original to copy
		for (int i = 0; i < m_ArrayTop; i++)
		{
			m_Array[i] = iOriginal->m_Array[i];
		}

	}

	//Insert an item with the key type TKey and data type TData - use make_pair to construct a pair object
	void insert(SPair<TKey, TData> iPair)
	{
		if(m_ArrayTop >= m_ArrayMax)	//Array full, create new array that is bigger
		{
			//Construct new array at twice the size
			int newMax = m_ArrayMax * 2;
			SPair<TKey, TData>* newArray = new SPair<TKey, TData>[newMax];
			//Copy the existing array across
			for (int i = 0; i < m_ArrayMax; i++)
			{
				newArray[i] = m_Array[i];
			}
			//Deallocate original array memory
			delete[] m_Array;
			//Assign new variable data to member variables
			m_Array = newArray;
			m_ArrayMax = newMax;
		}
		//At this point the array is definitely a size that can hold the new item, add it
		m_Array[m_ArrayTop] = iPair;
		m_ArrayTop++;
	}

	//Find the object with the key iKey, if the object is not found then construct a default TData object paired with the provided key
	TData& find(TKey iKey)
	{
		//Delegate to the operator implementation of this function
		return this->operator[](iKey);
	}

	//Find the object with the key iKey, if the object is not found then construct a default TData object paired with the provided key
	TData& operator[] (TKey iKey)
	{
		for (int i = 0; i < m_ArrayTop; i++)
		{
			if (m_Array[i].item1 == iKey)
			{
				return m_Array[i].item2;
			}
		}
		//Not found, add in
		TData newData = TData();
		insert(make_pair<TKey, TData>(iKey, newData));
		return m_Array[(m_ArrayTop - 1)].item2;
	}

	//Returns the number of items in the map
	int size()
	{
		return m_ArrayTop;
	}

};