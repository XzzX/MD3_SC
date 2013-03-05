#ifndef PERKOLATION_H
#define PERKOLATION_H

#include	<vector>

#include	"random.h"

class Vector;
class MeanVar;

class Perkolation{
	public:
		enum GRID_STATE {
			EMPTY,
			OCCUPIED
		};
		Perkolation();

		///dumps informations to logfiles
		void	DumpData();
		///writes information to console screen
		void	PrintGrid();

		void	HoshenKopelman();

		void	ResetGrid(const unsigned long L);
		void	OccupyGrid(const double p);

		long	GetLargestCluster();
		long	GetClusterSize(const long clusterId);
		bool	IsPercolating(const long clusterId);
		bool	IsPercolating(const long x, const long y);
		Vector	GetCenterOfMass(const long clusterId);

		void	MR(const Vector& CM, const double dR, std::vector<MeanVar>& MR);

	private:
		std::vector<std::vector<GRID_STATE> >	mGrid;
		std::vector<std::vector<long> >	mCluster;
		std::vector<long>	mClusterConnection;


		long	ResolveClusterConnection(long m);
};

#endif // PERKOLATION_H
