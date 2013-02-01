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

	Perkolation	perkolation;

	perkolation.ResetGrid(gConfig.mL);
	perkolation.OccupyGrid(gConfig.mP);

	perkolation.HoshenKopelman();

	std::cout << "#perkolation?: \t" << perkolation.IsPercolating(gConfig.mL/2, gConfig.mL/2) << std::endl;

	perkolation.DumpData();

	//perkolation.PrintGrid();

	int a;
	std::cin >> a;

    return 0;
}
