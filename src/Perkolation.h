#ifndef PERKOLATION_H
#define PERKOLATION_H

#include	<vector>

#include	"random.h"

class Perkolation{
	public:
		enum GRID_STATE {
			EMPTY,
			OCCUPIED
		};
		Perkolation(const unsigned long L, const double p);

		///dumps informations to logfiles
		void	DumpData();
		///writes information to console screen
		void	PrintGrid();

		void	HoshenKopelman();

	private:
		std::vector<std::vector<GRID_STATE> >	mGrid;
		std::vector<std::vector<long> >	mCluster;
		std::vector<long>	mClusterConnection;

		void	ResetGrid(const unsigned long L);
		void	OccupyGrid(const double p);

		long	ResolveClusterConnection(long m);
};

#endif // PERKOLATION_H
