#ifndef PERKOLATION_H
#define PERKOLATION_H

#include	<vector>

class Perkolation{
	public:
		enum GRID_STATE {
			EMPTY,
			OCCUPIED
		};
		Perkolation(const unsigned long L, const double p);

	private:
		std::vector<std::vector<long> >	mGrid;
		std::vector<std::vector<long> >	mCluster;
};

#endif // PERKOLATION_H
