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
	int audiosize; // size of file
	int channelnum;
	int samplenum;
	std::vector<T> audiovec;
	
	
	
	
	public:
	
	Audio();  //default constructor
	Audio(T bitnumber, int samplef) : bitnum(bitnumber), fs(samplef), channelnum(numchan){}
	
	
	//copy constructor
	Audio(const Audio & rhs) : bitnum(rhs.bitnum), fs(rhs.fs), channelnum(rhs.channelnum), samplenum(rhs.samplenum){
		
		audiovec = rhs.audiovec;
		
	}
	
	//copy assignment
	Audio operator=(const Audio & rhs)
		{
		channelnum = rhs.channelnum;
		fs = rhs.fs;
		bitnum = rhs.bitnum;
		samplenum = rhs.samplenum;
		audiosize = rhs.audiosize;
		audiovec = rhs.audiovec;
		return *this;
			}
			
	//move constructor
	Audio(Audio && rhs) : channelnum(rhs.channelnum),fs(rhs.fs),samplenum(rhs.samplenum), bitnum(rhs.bitnum), audiosize(rhs.audiosize)
		{
		this->data = rhs.data;
		rhs.channelnum = -1;
		rhs.fs = -1;
		rhs.samplenum = -1;
		rhs.bitnum = -1;
		rhs.audiosize = -1;
		}
	//move assignment
	Audio operator=(Audio && rhs){
		channelnum = rhs.channelnum;	rhs.channelnum = -1;
		fs = rhs.fs;					rhs.fs = -1;
		samplenum = rhs.samplenum;		rhs.samplenum = -1;
		bitnum = rhs.bitnum;			rhs.bitnum = -1;
		audiosize = rhs.audiosize;		rhs.audiosize = -1;
		return *this;
	}
	

	//destructor
	~Audio(){};
	
	void load(std::string file){
		std::ifstream inputfile;
				
		inputfile.open(file, std::ios::binary);
				
		//finding size of file
		inputfile.seekg(0,inputfile.end); //go to end of stream
		 audiosize = (int)(inputfile.tellg()); // get size
		inputfile.seekg(0, inputfile.beg);  // go back to beginning

		//determining number of samples
		samplenum = audiosize/channelnum;
		

		char * temp_array = new char[samplenum];
		inputfile.read(temp_array, samplenum);
		for(int g = 0; g < samplenum; g++)
		{
			audiovec.push_back((T)(temp_array[g]));
			}
		delete temp_array;
		inputfile.close();
				
		
	}
	void save(std::string file){
		
		
		std::ofstream outputfile(file, std::ios::binary);
				//creating temporary array
		char * save_arr = new char[samplenum];
		for(int k = 0; k < samplenum; ++k)
		{
			save_arr[k] = (char)audiovec[k];
		}
		//write temporary array contents to output file
		outputfile.write(save_arr, samplenum);
		delete save_arr;
		outputfile.close();
		}
		
		
	Audio add(const Audio & other){
		
	}
		
		
	
};




template <typename T>
 class Audio<T,2>{
	
	private:
	T bitnum;	//either 8 or 16
	int channelnum;
	int fs;    //sampling freq
	int audiosize;
	int samplenum; 
	std::vector<std::pair<T,T>>  audiovec;
	
	
	
	public:
	
	Audio();
	
	Audio(T bitnumber,int samplef) : bitnum(bitnumber), fs(samplef), channelnum(2){} //stereo constructor
	//copy constructor
	Audio(const Audio & rhs) : bitnum(rhs.bitnum), fs(rhs.fs), channelnum(rhs.channelnum), samplenum(rhs.samplenum){
		
		audiovec = rhs.audiovec;
		
	}
	
	//copy assignment
	Audio operator=(const Audio & rhs)
		{
		channelnum = rhs.channelnum;
		fs = rhs.fs;
		bitnum = rhs.bitnum;
		samplenum = rhs.samplenum;
		audiosize = rhs.audiosize;
		audiovec = rhs.audiovec;
		return *this;
			}
			
	//move constructor
	Audio(Audio && rhs) : channelnum(rhs.channelnum),fs(rhs.fs),samplenum(rhs.samplenum), bitnum(rhs.bitnum), audiosize(rhs.audiosize)
		{
		this->data = rhs.data;
		rhs.channelnum = -1;
		rhs.fs = -1;
		rhs.samplenum = -1;
		rhs.bitnum = -1;
		rhs.audiosize = -1;
		}
	//move assignment
	Audio operator=(Audio && rhs){
		channelnum = rhs.channelnum;	rhs.channelnum = -1;
		fs = rhs.fs;					rhs.fs = -1;
		samplenum = rhs.samplenum;		rhs.samplenum = -1;
		bitnum = rhs.bitnum;			rhs.bitnum = -1;
		audiosize = rhs.audiosize;		rhs.audiosize = -1;
		return *this;
	}
	

	//destructor
	~Audio(){};
	
	
	void load(std::string file){
		
		std::ifstream inputfile;
				
		inputfile.open(file, std::ios::binary);
				
		//finding size of file
		inputfile.seekg(0,inputfile.end); //go to end of stream
		audiosize = (int)(inputfile.tellg()); // get size
		inputfile.seekg(0, inputfile.beg);  // go back to beginning

		//determining number of samples
		samplenum = audiosize/channelnum;
		

		char * temp_array = new char[2*samplenum];
		inputfile.read(temp_array, samplenum);
		
		for(int g = 0; g < samplenum*2; g=g+2)
		{
			std::pair<T,T> stereopair = std::make_pair((T)temp_array[g],(T)temp_array[g+1]);
			audiovec.push_back(stereopair);
			}
		delete temp_array;
		inputfile.close();
		
		
	}
	void save(std::string file){
		
		std::ofstream outputfile(file, std::ios::binary);
				//creating temporary array
		char * save_arr = new char[samplenum*2];
		int count = 0;
		int k = 0;
		while (k<samplenum)
		{
			save_arr[count] = (char)audiovec[k].first;
			save_arr[count+1] = (char)audiovec[k].second;
			count = count+2;
			k++;
		}
		//write temporary array contents to output file
		outputfile.write(save_arr, samplenum);
		delete save_arr;
		outputfile.close();
		
		
	}
};



}


#endif