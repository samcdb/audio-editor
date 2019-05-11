#ifndef Audio_h
#define Audio_h
#include <cstdint>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace DBRSAM003{


template <typename T, int numchan>
 class Audio{
	
	private:
	T bitnum;	//either 8 or 16
	int fs;    //sampling freq
	std::vector<T> monovec;
	
	
	
	
	public:
	
	Audio();
	Audio(T bitnumber, int samplef) : bitnum(bitnumber), fs(samplef){}
	
	
	load(std::string file);
	save(std::string file);
};




template <typename T>
 class Audio<T,2>{
	
	private:
	T bitnum;	//either 8 or 16
	int fs;    //sampling freq
	
	std::vector<std::pair<T,T>>  stereovec;
	
	
	
	public:
	
	Audio();
	
	Audio(T bitnumber,int samplef, std::vector<std::pair<T,T>> stereo); //stereo constructor
	
	
	load(std::string file);
	save(std::string file);
};



}


#endif