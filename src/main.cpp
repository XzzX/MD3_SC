#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

#include <boost/timer/timer.hpp>

#include	"Vector.hpp"
#include	"Configuration.hpp"
#include	"MeanVar.h"
#include	"util.h"
#include	"Perkolation.h"

int main( unsigned int argc, char **argv ) {
	boost::timer::auto_cpu_timer autoTimer;

	gConfig.ReadCommandLineParameters(argc, argv);

	std::cout << gConfig << std::endl;

	gConfig.SaveConfiguration();

	std::vector<MeanVar>	MR;
	MR.resize(int(ceil(1.5*gConfig.mL/gConfig.mDeltaR)));
	for (long i=0; i<MR.size(); i++)
		MR[i].Clear();

	while (gConfig.mRuns>0){
		Perkolation	perkolation;

		perkolation.ResetGrid(gConfig.mL);
		perkolation.OccupyGrid(gConfig.mP);

		perkolation.HoshenKopelman();

		long	lCluster = perkolation.GetLargestCluster();
		if (perkolation.IsPercolating(lCluster)){
			perkolation.MR(perkolation.GetCenterOfMass(lCluster), gConfig.mDeltaR, MR);
			gConfig.mRuns--;
			std::cout << gConfig.mRuns << std::endl;
		}
	}

    std::fstream fout((gConfig.mLogName+"_MR.txt").c_str(), std::fstream::out);

	fout << gConfig;

	for (long i = 0; i<MR.size(); i++){
		fout << gConfig.mDeltaR * i << "\t" << MR[i].Mean() << "\t" << MR[i].Error() << std::endl;
	}

    fout.close();

	//perkolation.DumpData();

	//perkolation.PrintGrid();

    return 0;
}
