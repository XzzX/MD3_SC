#include	"Configuration.hpp"

#include	<fstream>

#include	"util.h"

Configuration	gConfig;

std::ostream &operator << (std::ostream &stream, const Configuration& config){
	stream << "#CONFIGURATION" << std::endl;
	stream << "#seed:                " << config.mRandomSeed << std::endl;
	stream << "#box length:          " << config.mL << std::endl;
	stream << "#probability:         " << config.mP << std::endl;
    return stream;
}

Configuration::Configuration() :
	mRandomSeed(time(0)),
	mLogName("data"),
	mL(50),
	mP(0.592746)
{}

void	Configuration::ReadCommandLineParameters( unsigned int argc, char **argv ){
    for (unsigned int i=1; i<argc; i++){

        std::string cmd = argv[i];

        if (cmd.compare("-seed") == 0){
			i++;
            mRandomSeed = StringTo<unsigned int>(argv[i]);
		} else if (cmd.compare("-log") == 0){
			i++;
            mLogName = argv[i];
        } else if (cmd.compare("-L") == 0){
			i++;
            mL = StringTo<long>(argv[i]);
        } else if (cmd.compare("-p") == 0){
			i++;
            mP = StringTo<double>(argv[i]);
        }

    }
}

void Configuration::SaveConfiguration(){
    std::fstream fout((gConfig.mLogName+"_conf.txt").c_str(), std::fstream::out);
	fout << gConfig;

	fout << mRandomSeed << std::endl;
	fout << mL << std::endl;
	fout << mP << std::endl;

    fout.close();
}
