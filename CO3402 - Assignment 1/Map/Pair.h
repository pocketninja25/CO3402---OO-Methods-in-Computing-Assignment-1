#pragma once


template <typename TItem1, typename TItem2>
struct SPair
{
public:
	SPair()	{}

	TItem1 item1;
	TItem2 item2;


};

template <typename TI1, typename TI2>
SPair<TI1, TI2> make_pair(TI1 iItem1, TI2 iItem2)
{
	SPair<TI1, TI2> newPair;
	newPair.item1 = iItem1;
	newPair.item2 = iItem2;
	return newPair;
}