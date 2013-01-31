#ifndef RANDOM_H
#define RANDOM_H

#include	<boost/random/mersenne_twister.hpp>
#include	<boost/random/uniform_01.hpp>

class Random{
	public:
		Random();

		void	Seed(const long seed);
		double	Uniform(const double min, const double max);

	private:
		///random number generator
		boost::random::mt19937 mRNG;
};

extern Random gRandom;

#endif // PERKOLATION_H
