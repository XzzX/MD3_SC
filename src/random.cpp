#include	"random.h"

#include	<time.h>

Random	gRandom;

Random::Random(){
	mRNG.seed(time(0));
}

void	Random::Seed(const long seed){
	mRNG.seed(seed);
}

double	Random::Uniform(const double min, const double max){
	boost::random::uniform_01<> uni;
	return	uni(mRNG) * (max-min) + min;
}