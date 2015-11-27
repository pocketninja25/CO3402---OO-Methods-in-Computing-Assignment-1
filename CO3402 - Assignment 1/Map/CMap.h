#pragma once
#include "Pair.h"

template <typename TItem1, typename TItem2>
class CIterator 	//For this map implementation the iterator is merely a wrapper for the SPair pointer
{
	template <typename TKey, typename TData> friend class CMap;
private:
	SPair<TItem1, TItem2>* m_Pair;

	CIterator(SPair<TItem1, TItem2> &theItem)
	{
		m_Pair = &theItem;
	}

public:
	~CIterator()
	{
	}

	SPair<TItem1, TItem2> operator*() const	//Dereference operator overload to return the pair item
	{
		return *m_Pair;
	}

	CIterator<TItem1, TItem2>& operator++()
	{
		m_Pair++;
		return *this;
	}

	CIterator<TItem1, TItem2> operator++(int)
	{
		CIterator<TItem1, TItem2> tmp(*this);
		operator++();
		return tmp;
	}

	bool operator==(const CIterator<TItem1, TItem2>& other) 
	{
		return (this->m_Pair == other.m_Pair);
	}

	bool operator!=(const CIterator<TItem1, TItem2>& other)
	{
		return (this->m_Pair != other.m_Pair);
	}
};

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
		if (m_ArrayTop >= m_ArrayMax)	//Array full, create new array that is bigger
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

	bool remove(TKey iKey, TData &removedData)	//Pop the data that matches the key and pass it to the caller through removedData reference parameter
	{
		for (int i = 0; i < m_ArrayTop; i++)
		{
			if (m_Array[i].item1 == iKey)
			{
				//Populate retrieval data
				removedData = m_Array[i].item2;

				//Remove the data from the m_Array
				m_ArrayTop--;	//Reduce the array size
				m_Array[i] = m_Array[m_ArrayTop];	//Put the item currently on the top of the array in the empty space

				return true;	//Found, shortcut out of the function
			}
		}
		//Return either found item or item passed here if item not found
		return false;	//Could not find
	}

	bool remove(TKey iKey)	//Version of pop that does not return the data removed by the function
	{
		float temp;
		return remove(iKey, temp);
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

	CIterator<TKey, TData> IterBegin()	//Returns an iterator that points at the first (0th) item in the array
	{
		return CIterator<TKey, TData>(m_Array[0]);
	}

	CIterator<TKey, TData> IterEnd()	//Returns an iterator that points 1 item past the final item in the array
	{
		return CIterator<TKey, TData>(m_Array[m_ArrayTop]);
	}
	
};

