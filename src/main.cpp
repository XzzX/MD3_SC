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

	std::fstream fout((gConfig.mLogName+"_Size.txt").c_str(), std::fstream::out);

	fout << gConfig;

	for (double p=gConfig.mPStart; p<gConfig.mPStop; p+=gConfig.mPStep){
		gConfig.mP = p;
		MeanVar	size;
		while (gConfig.mRuns>0){
			Perkolation	perkolation;

			perkolation.ResetGrid(gConfig.mL);
			perkolation.OccupyGrid(gConfig.mP);

			perkolation.HoshenKopelman();

			long	lCluster = perkolation.GetLargestCluster();
			if (!perkolation.IsPercolating(lCluster)){
				size.Add(perkolation.GetClusterSize(lCluster));
				gConfig.mRuns--;
			}
		}
		fout << p << "\t" << size.Mean() << "\t" << size.Error() << std::endl;
	}

    fout.close();

	//perkolation.DumpData();

	//perkolation.PrintGrid();

    return 0;
}
