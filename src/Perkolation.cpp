#include "Perkolation.h"

/**
@param L length of the grid
@param p probability for occupation
**/
Perkolation::Perkolation(const unsigned long L, const double p){
	mGrid.resize(L);
	for (unsigned long i = 0; i<0; i++)
		mGrid[i].resize(L, EMPTY);

	mCluster.resize(L);
	for (unsigned long i = 0; i<0; i++)
		mCluster[i].resize(L, 0);

}
