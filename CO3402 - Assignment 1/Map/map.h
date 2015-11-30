#pragma once

template <typename TItem1, typename TItem2>
struct SPair	//Structure that stores two public items of the templated types - no functions
{
public:
	TItem1 item1;		//The first item in the pair (Key)
	TItem2 item2;		//The second item in the pair (Data)

};

template <typename TI1, typename TI2>
//Used as a pseudo constructor in a similar way to the stl, creates an SPair object and populates it with the passed templated items
SPair<TI1, TI2> make_pair(TI1 iItem1, TI2 iItem2)
{
	SPair<TI1, TI2> newPair;
	newPair.item1 = iItem1;
	newPair.item2 = iItem2;
	return newPair;
}

template <typename TItem1, typename TItem2>
class CIterator 	//For this map implementation the iterator is merely a wrapper for the SPair pointer
{
	//Associate CMap as friend to allow it to create CIterators using the constructor
	template <typename TKey, typename TData> friend class CMap;
private:
	SPair<TItem1, TItem2>* m_Pair;	//The pair that this Iterator is pointing to

	//Private Constructor - iterators are only creatable by the friend map class
	CIterator(SPair<TItem1, TItem2> &theItem)
	{
		m_Pair = &theItem;
	}

public:
	//Default destructor - nothing to deallocate
	~CIterator()
	{
	}

	//Dereference operator, returns the pair m_Pair points to
	SPair<TItem1, TItem2> operator*() const	//Dereference operator overload to return the pair item
	{
		return *m_Pair;
	}

	//Increment operator - points to the next SPair<TItem1, TItem2>
	CIterator<TItem1, TItem2>& operator++()
	{
		//Just increment the m_Pair pointer, this is the simplest and quickest method, requires no communication with map class
		m_Pair++;
		return *this;
	}

	//Increment operator with parameter - uses the parameterless increment operator's implementation of increment
	CIterator<TItem1, TItem2> operator++(int)
	{
		CIterator<TItem1, TItem2> tmp(*this);
		operator++();
		return tmp;
	}

	//Is equal operator - Identifies if the two pairs are the same pair object, will not return true if the pairs have the same key but are e.g. in different maps
	bool operator==(const CIterator<TItem1, TItem2>& other) 
	{
		return (this->m_Pair == other.m_Pair);
	}

	//Not equal operator - Identifies if the two pairs are not the same pair object
	bool operator!=(const CIterator<TItem1, TItem2>& other)
	{
		return (this->m_Pair != other.m_Pair);
	}
};


template <typename TKey, typename TData>	//Template to allow any data type for the key and data
class CMap
{
private:
	SPair<TKey, TData>* m_Array;	//The array of data items (using pointer type to allow dynamic reallocation of size by creating new array at runtime)
	int m_ArrayMax;					//The current amount of maximum items the array can store without reallocating the size of the array
	int m_ArrayTop;					//The amount of items currently in the array, also can be used to 'point at' the top of the array
	int m_OriginalMax;

public:
	//Create a map of starting size 'mapSize', this is not necessarily the final size of the map, just a starting point, the map will grow in size to accomodate any items over it's current capacity
	CMap(int mapSize = 50)
	{
		m_OriginalMax = mapSize;
		m_ArrayTop = 0;
		m_ArrayMax = mapSize;
		m_Array = new SPair<TKey, TData>[m_ArrayMax];
	}
	
	//Map destructor - deallocate the array object and its contained pairs
	~CMap()
	{
		delete[] m_Array;
	}

	//Override copy constructor to deep copy, ensuring the m_Array object is recreated for the copy object
	CMap(const CMap<TKey, TData>& iOriginal)
	{
		//Constructs a new object using a copy
		m_ArrayMax = iOriginal.m_ArrayMax;
		m_ArrayTop = iOriginal.m_ArrayTop;
		//Allocate new array
		m_Array = new SPair<TKey, TData>[iOriginal.m_ArrayMax];
		//Copy array data from original to copy
		for (int i = 0; i < m_ArrayTop; i++)
		{
			m_Array[i] = iOriginal.m_Array[i];
		}

	}

	//Overload assignment operator to ensure the m_Array object is properly deallocated from the copy and recreated from the original
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

	//Insert an item pair with the key type TKey and data type TData, if the key already exists then the data will be overwritten instead of an item being added - use make_pair to construct a pair object
	void insert(SPair<TKey, TData> iPair)
	{
		//Try to change data of existing key
		for (int i = 0; i < m_ArrayTop; i++)
		{
			if (m_Array[i].item1 == iPair.item1)	//The keys match
			{
				//Reassign the data of the stored pair
				m_Array[i].item2 = iPair.item2;
				return;	//Completed - dont carry on
			}
		}

		//If the function reaches this point then the key does not exist, a new pair need to be added

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

	//Insert an item pair with the key type TKey and data type TData, if the key already exists then the data will be overwritten instead of an item being added - uses the SPair version for implementation, provides an alternate easier to use interface
	void insert(TKey iKey, TData iData)
	{
		insert(make_pair(iKey, iData));
	}

	//Remove the item with the provided key, returns false if the item was not found. Returns true if the item was found and removed, also passes the data of the item removed through the removedData reference parameter
	bool remove(TKey iKey, TData &removedData)
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

	//Alternate version of remove that does not return the data that is removed, uses the alternate version of the function as its implementation
	bool remove(TKey iKey)
	{
		TData temp;
		return remove(iKey, temp);
	}

	//Find the object with the key iKey, if the object is not found then construct a default TData object paired with the provided key - delegates to the square bracket operator for implementation
	TData& find(TKey iKey)
	{
		//Delegate to the operator implementation of this function
		return this->operator[](iKey);
	}

	//Overload square bracket operator to Find the object with the key iKey, if the object is not found then construct a default TData object paired with the provided key
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

	//Returns the number of items currently stored in the map 
	int size()
	{
		return m_ArrayTop;
	}

	//Removes all objects from the map array and resets the array size to the size passed when it was first constructed
	void clear()
	{
		delete[] m_Array;
		m_ArrayMax = m_OriginalMax;
		m_Array = new SPair<TKey, TData>[m_ArrayMax];
		m_ArrayTop = 0;
	}

	//Returns an iterator to the 0th element in the map array
	CIterator<TKey, TData> IterBegin()
	{
		return CIterator<TKey, TData>(m_Array[0]);
	}

	//Returns an iterator to the element after the final element in the map array - for iteration in a similar way to the stl iterator
	CIterator<TKey, TData> IterEnd()
	{
		return CIterator<TKey, TData>(m_Array[m_ArrayTop]);
	}
	
};
