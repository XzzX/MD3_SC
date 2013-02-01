#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include	<iostream>
#include	<sstream>
#include	<iomanip>
#include	<string>
#include    <stdexcept>

class Configuration{
	public:
		unsigned int 	mRandomSeed;				///<seed of the random number generator

		std::string 	mLogName;					///<filename of the logfile

		long			mL;							///<size of the simulation box
		double			mP;							///<probability for occupation

		///load basic configuration
		Configuration();
		///read out the command line parameters
		void	ReadCommandLineParameters( unsigned int argc, char **argv );
		void	SaveConfiguration();
};

extern	Configuration	gConfig;

///overloaded << operator to show easily the configuration on the screen
std::ostream &operator << (std::ostream &stream, const Configuration& config);

#endif
