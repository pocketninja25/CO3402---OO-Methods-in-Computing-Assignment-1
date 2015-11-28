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