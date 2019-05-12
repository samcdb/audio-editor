#ifndef Audio_h
#define Audio_h
#include <cstdint>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
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
		this->audiovec = rhs.getAudiovec();
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
	
	std::vector<T> getAudiovec(){
		return audiovec;
	}
	
	void load(std::string file){
		std::ifstream inputfile;
				
		inputfile.open(file, std::ios::binary);
				
		//finding size of file
		inputfile.seekg(0,inputfile.end); //go to end of stream
		 audiosize = (int)(inputfile.tellg()); // get size
		inputfile.seekg(0, inputfile.beg);  // go back to beginning

		//determining number of samples
		samplenum = audiosize/channelnum;
		std::cout << samplenum<< std::endl;

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
		Audio answer(*this);
		
		auto beg1 = answer.audiovec.begin(), end1 = answer.audiovec.end();
		auto beg2 = other.audiovec.begin(), end2 = other.audiovec.end();

		while(beg1 != end1){
	//	for(int j=0;j<answer.getAudiovec().size();++j){
			int sum = *beg1 + *beg2;
			if (sum > std::pow(2,bitnum-1)-1){
				*beg1 = (std::pow(2,bitnum-1)-1);
			}
			else if(sum < -1*std::pow(2,bitnum-1)-1){
				*beg1 = -1*(std::pow(2,bitnum-1)-1);
			}
			else{
				*beg1 = sum;
			}
			
			++beg1; ++beg2;
		}
		return answer;
	}
	
	
	Audio cut(std::pair<int,int> cutrange){
		Audio answer(*this);
		std::vector<T> newaudiovec;
		
		int startsmpl = cutrange.first*fs; //multiply by sampling freq
		int endsmpl = cutrange.second*fs;
		newaudiovec.resize(samplenum - (endsmpl-startsmpl) + 1);
		
		auto beg1 = answer.audiovec.begin(), end1 = answer.audiovec.end();
		auto beg2 = newaudiovec.begin(), end2 = newaudiovec.end();
		auto cutstart = beg1+startsmpl+1, cutend = beg1+endsmpl;
	
		while(beg1 != cutstart){  //go from beginning to start of cut
			*beg2 = *beg1;
			
			++beg1; ++beg2;
		}
			
		
		while(cutend != end1 ){  //go from end of cut to end
			*beg2 = *cutend;
			
			++cutend; ++beg2; 
		}
		std::cout <<"hi"<<std::endl;
		answer.audiovec.clear();
		answer.audiovec = newaudiovec;
		answer.samplenum = newaudiovec.size();
		
		return answer;
		
	}
	
	
	
	//overloaded operators
	//add
	Audio operator+(const Audio & other){
	return add(other);
	}
	//cut
	Audio operator^ (std::pair<int,int> cutrange){
	return cut(cutrange);
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
		this->audiovec = rhs.audiovec;
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
		audiovec = rhs.audiovec;    	rhs.audiovec.clear();
		return *this;
	}
	

	//destructor
	~Audio(){};
	
	std::vector<T> getAudiovec(){
		return audiovec;
	}
	
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
	
	Audio add(const Audio & other){
		Audio answer(*this);
		
			
		
		auto beg1 = answer.audiovec.begin(), end1 = answer.audiovec.end();
		auto beg2 = other.audiovec.begin(), end2 = other.audiovec.end();
		while(beg1 != end1){
		//for(int j=0;j<answer.audiovec.size();++j){
			int leftsum = (*beg1).first + (*beg2).first;
			int rightsum = (*beg1).second + (*beg2).second;
		
		if (leftsum > std::pow(2,bitnum-1)-1){
				(*beg1).first = (std::pow(2,bitnum-1)-1);
			}
			else if(leftsum < -1*std::pow(2,bitnum-1)-1){
				(*beg1).first = -1*(std::pow(2,bitnum-1)-1);
			}
			else{
				(*beg1).first = leftsum;
			}
					
		if (rightsum > std::pow(2,bitnum-1)-1){
				(*beg1).second = (std::pow(2,bitnum-1)-1);
			}
			else if(rightsum < -1*std::pow(2,bitnum-1)-1){
				(*beg1).second = -1*(std::pow(2,bitnum-1)-1);
			}
			else{
				(*beg1).second = rightsum;
			}		
					
					
		++beg1; ++beg2;
		}
		
		return answer;
	}
	
	
	
	
	//overloaded operators
	
	Audio operator+(const Audio & other){
	return add(other);
	}
};



}


#endif