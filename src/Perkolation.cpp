#include	"Perkolation.h"

#include	<iostream>
#include	<fstream>

#include	"Configuration.hpp"
#include	"Vector.hpp"
#include	"MeanVar.h"

/**
@param L length of the grid
@param p probability for occupation
**/
Perkolation::Perkolation(){

}

void	Perkolation::ResetGrid(const unsigned long L){
	mGrid.resize(L);
	for (unsigned long i = 0; i<L; i++)
		mGrid[i].resize(L, EMPTY);

	mCluster.resize(L);
	for (unsigned long i = 0; i<L; i++)
		mCluster[i].resize(L, 0);

	mClusterConnection.resize(1, 0);
}

void	Perkolation::OccupyGrid(const double p){
	for (unsigned long i = 0; i<mGrid.size(); i++)
		for (unsigned long j=0; j<mGrid[i].size(); j++)
			if (gRandom.Uniform(0.0, 1.0)<=p) mGrid[i][j] = OCCUPIED; else mGrid[i][j] = EMPTY;
}

void	Perkolation::HoshenKopelman(){
	for (long i = 0; i<mGrid.size(); i++)
		for (long j=0; j<mGrid[i].size(); j++){
			if (mGrid[i][j] == OCCUPIED){

				if ((i-1)>=0)
					if (mGrid[i-1][j] == OCCUPIED){
						//left connection
						mCluster[i][j] = mCluster[i-1][j];
						mClusterConnection[ResolveClusterConnection(mCluster[i][j])]++;
					}

				if ((j-1)>=0)
					if (mGrid[i][j-1] == OCCUPIED){
						//already connected?
						if (mCluster[i][j]==0){
							//top connection
							mCluster[i][j] = mCluster[i][j-1];
							mClusterConnection[ResolveClusterConnection(mCluster[i][j])]++;
						}else{
							//connection between two clusters
							long c1 = ResolveClusterConnection(mCluster[i][j]);
							long c2 = ResolveClusterConnection(mCluster[i][j-1]);
							if (c1!=c2) {
								mClusterConnection[c1] += mClusterConnection[c2];
								mClusterConnection[c2] = -c1;
							}
						}
					}
				if (mCluster[i][j]==0){
					//new cluster
					mCluster[i][j] = mClusterConnection.size();
					mClusterConnection.push_back(1);
				}
			}
		}

	//Beauty loop ;-)
	//overwrites number of molecules in cluster!!!!
	/*long	temp = 1;
	for (long i = 1; i<mClusterConnection.size(); i++)
		if (mClusterConnection[i]>0){
			mClusterConnection[i] = temp;
			temp++;
		}*/

	for (long i = 0; i<mGrid.size(); i++)
		for (long j=0; j<mGrid[i].size(); j++)
			mCluster[i][j] = ResolveClusterConnection(mCluster[i][j]);
}

long Perkolation::GetLargestCluster(){
	long temp = 0;
	for (long i=1; i<mClusterConnection.size(); i++)
		if (mClusterConnection[temp]<mClusterConnection[i]) temp = i;
	return temp;
}

long Perkolation::GetClusterSize(const long clusterId){
	return mClusterConnection[clusterId];
}

bool Perkolation::IsPercolating(const long clusterId){
	bool temp1 = false;
	bool temp2 = false;
	for (unsigned long i = 0; i<mCluster.size(); i++){
		if (mCluster[i][0]==clusterId) temp1= true;
		if (mCluster[i][mCluster.size()-1]==clusterId) temp2= true;
	}
	if (temp1&&temp2) return true; else {
		temp1 = false;
		temp2 = false;
	}
	for (unsigned long i = 0; i<mCluster.size(); i++){
		if (mCluster[0][i]==clusterId) temp1= true;
		if (mCluster[mCluster.size()-1][i]==clusterId) temp2= true;
	}
	return temp1&&temp2;
}

bool	Perkolation::IsPercolating(const long x, const long y){
	if (mCluster[x][y]!=0) return IsPercolating(mCluster[x][y]); else return false;
}

Vector	Perkolation::GetCenterOfMass(const long clusterId){
	Vector	temp(0,0,0);
	long	n = 0;
	for (unsigned long i = 0; i<mCluster.size(); i++)
		for (unsigned long j=0; j<mCluster[i].size(); j++){
			if (mCluster[i][j]==clusterId) temp += Vector(i,j,0);
			n++;
		}
	return temp/n;
}

void	Perkolation::MR(const Vector& CM, const double dR, std::vector<MeanVar>& MR){
	std::vector<long>	masses;
	masses.resize(MR.size(),0);

	for (unsigned long i = 0; i<mGrid.size(); i++)
		for (unsigned long j=0; j<mGrid[i].size(); j++){
			if (mGrid[i][j]==OCCUPIED) masses[int(norm(Vector(i,j,0)-CM)/dR)]++;
		}

	for (unsigned long i = 0; i<MR.size(); i++)
		MR[i].Add(masses[i]);
}

long 	Perkolation::ResolveClusterConnection(long m){
	while (mClusterConnection[m]<0) m = -mClusterConnection[m];
	return m;
}

void	Perkolation::PrintGrid(){
	for (unsigned long i = 0; i<mGrid.size(); i++){
		for (unsigned long j=0; j<mGrid[i].size(); j++)
			if (mGrid[i][j] == OCCUPIED) std::cout << "X"; else std::cout << "O";
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	for (unsigned long i = 0; i<mGrid.size(); i++){
		for (unsigned long j=0; j<mGrid[i].size(); j++)
			std::cout << mCluster[i][j];
		std::cout << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::endl;

	for (unsigned long i = 0; i<mClusterConnection.size(); i++)
		std::cout << i << "\t" << mClusterConnection[i] << std::endl;
}

void    Perkolation::DumpData(){
    std::fstream fout((gConfig.mLogName+"_cluster.txt").c_str(), std::fstream::out);

	fout << gConfig;

	for (unsigned long i = 0; i<mGrid.size(); i++){
		for (unsigned long j=0; j<mGrid[i].size(); j++)
			fout << mClusterConnection[mCluster[i][j]] << " ";
		fout << std::endl;
	}

    fout.close();
}
