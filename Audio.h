#ifndef Audio_h
#define Audio_h
#include "normalise.h"
#include <cstdint>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>

namespace DBRSAM003{


template <typename T, int numchan=1>
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
		/*
		inputfile.seekg(0,inputfile.end); //go to end of stream
		 audiosize = (int)(inputfile.tellg()); // get size
		inputfile.seekg(0, inputfile.beg);  // go back to beginning
		std::cout << audiosize<< std::endl;
		//determining number of samples
		samplenum = (audiosize/(sizeof(T)*1) );
		std::cout << "sample num " <<samplenum<< std::endl;
		
		
		
		
		
		std::cout << samplenum << std::endl;
		char * temp_array = new char[samplenum];
		inputfile.read(temp_array, samplenum);
		audiovec.resize(samplenum);
		*/
		
		
		inputfile.seekg(0, inputfile.end);
		std::streampos fileSize = inputfile.tellg();

		samplenum = fileSize / (sizeof(T));
		audiovec.resize(samplenum);
		int fLength = samplenum / (float)fs;

		inputfile.seekg(0, inputfile.beg);
		std::cout << "sample num " <<samplenum<< std::endl;
		inputfile.read((char *)& audiovec[0], samplenum);
		
		/*
		for(int g = 0; g < samplenum; g++)
		{
			audiovec[g] = (T)(temp_array[g]);
			}
		delete temp_array;
		std::cout << "last in array " << audiovec[audiovec.size()-1] <<std::endl;
		inputfile.close();
				*/
		
	}
	void save(std::string file){
		std::ofstream outputfile(file, std::ios::binary);
				//creating temporary array
				/*
		char * save_arr = new char[samplenum];
		int counter = 0;
		for(int k = 0; k < samplenum; ++k)
		{
			save_arr[k] = (char)audiovec[k];
			counter++;
		}
		std::cout << "last in array " << save_arr[audiovec.size()-1] <<std::endl;

		std::cout << "save length " << counter <<std::endl;
		//write temporary array contents to output file
		outputfile.write(save_arr, samplenum);
		delete save_arr;
		*/
		
		
		std::cout << "vec sizeeeee " << audiovec.size() <<std::endl;

		outputfile.write((char *)& audiovec[0], audiovec.size());
		outputfile.flush();
		
		outputfile.close();
		}
		
		
	Audio add(const Audio & other){
		Audio answer(*this);
		
		auto beg1 = answer.audiovec.begin(), end1 = answer.audiovec.end();
		auto beg2 = other.audiovec.begin(), end2 = other.audiovec.end();
	int counter = 0;
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
			++counter;
		}
		std::cout << "vec size " <<answer.audiovec.size() << std::endl;
		std::cout << "count size " <<counter << std::endl;
		std::cout << "last two vector elements " <<answer.audiovec[audiovec.size()-30] << " " <<answer.audiovec[audiovec.size()-10] << std::endl;
		
		
		
		
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
		
		answer.audiovec.clear();
		answer.audiovec = newaudiovec;
		answer.samplenum = newaudiovec.size();
		
		return answer;
		
	}
	
	Audio concatenate(Audio & other){
		Audio answer(*this);
		int joinpoint = answer.samplenum;
		answer.samplenum += other.samplenum;
		answer.audiovec.resize(answer.samplenum);
		
		auto beg1 = answer.audiovec.begin() + joinpoint, end1 = answer.audiovec.end();
		auto beg2 = other.audiovec.begin(), end2 = other.audiovec.end();
		
		while(beg1 != end1){
			
			*beg1 = *beg2;
			
			++beg1; ++beg2;
			
		}
		
		return answer;
		
	}
	
	//ranged add
	
	Audio radd(std::pair<int,int> rangepair1,std::pair<int,int> rangepair2, Audio & other){
		Audio answer(*this);
		Audio oth(other);
		std::vector<T>  ansraddaudiovec;
		std::vector<T>  othraddaudiovec;
		ansraddaudiovec.resize((rangepair1.second - rangepair1.first)*fs);
		othraddaudiovec.resize((rangepair2.second - rangepair2.first)*fs);
		std::cout << other.audiovec.size()<< std::endl;
		std::copy ( answer.audiovec.begin()+rangepair1.first*fs, answer.audiovec.begin()+rangepair1.second*fs, ansraddaudiovec.begin() );   // copy range into new vector
		std::cout << "end of radd" << std::endl;
		std::copy ( oth.audiovec.begin()+rangepair2.first*fs, oth.audiovec.begin()+rangepair2.second*fs, othraddaudiovec.begin() );	//copy range into new vector
		
		answer.audiovec = ansraddaudiovec;
		oth.audiovec = othraddaudiovec;
		
		answer = answer + oth;
		answer.samplenum = answer.audiovec.size();
		
		return answer;
	
	}
	
	//volume
	Audio volume(std::pair<float, float> setting){
		Audio volchange(*this);
		
		auto beg1 = volchange.audiovec.begin(), end1 = volchange.audiovec.end();
		
		while(beg1 != end1){
	
			float volume = *beg1 *setting.first;
			if (volume > std::pow(2,bitnum-1)-1){
				*beg1 = (std::pow(2,bitnum-1)-1);
			}
			else if(volume < -1*std::pow(2,bitnum-1)-1){
				*beg1 = -1*(std::pow(2,bitnum-1)-1);
			}
			else{
				*beg1 = volume;
			}
			
			++beg1;
		}
		return volchange;
	}
	
	//reverse
	Audio reverse(){
		Audio rev(*this);
		std::reverse(rev.audiovec.begin(),rev.audiovec.end());
		
		return rev;
	}
	
	//RMS
	float rms(){
		int accsum = 0;
		
		accsum = std::accumulate(audiovec.begin(), audiovec.end(), accsum, [](int a, T b) {
			
			return a + (b*b);
			
		});

		float rmsanswer = sqrt(accsum / (float)samplenum);

		return rmsanswer;
		
	}
	
	
	//normalisation
	Audio normalisation(std::pair<float, float> givenrms) {
		float nowrms = rms();

		Audio answer(bitnum, fs);
		answer.samplenum = samplenum;
		std::transform(audiovec.begin(), audiovec.end(), answer.audiovec.begin(), normalise<T>(givenrms.first, nowrms, bitnum));
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
	//concatenate
	Audio operator|( Audio & other){
	return concatenate(other);
	}
	//volume
	Audio operator* (std::pair<float,float> setting){
		return volume(setting);
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
		std::cout <<"Loading" <<std::endl;
		std::ifstream inputfile;
				
		inputfile.open(file, std::ios::binary);
				
		//finding size of file
		inputfile.seekg(0,inputfile.end); //go to end of stream
		audiosize = (int)(inputfile.tellg()); // get size
		inputfile.seekg(0, inputfile.beg);  // go back to beginning

		//determining number of samples
		samplenum = audiosize/channelnum;
		std::cout << "channel " << channelnum <<std::endl;
		

		char * temp_array = new char[2*samplenum];
		inputfile.read(temp_array, 2*samplenum);
		
		for(int g = 0; g < samplenum*2; g=g+2)
		{
			std::pair<T,T> stereopair = std::make_pair((T)temp_array[g],(T)temp_array[g+1]);
			audiovec.push_back(stereopair);
			
			}
		
		delete temp_array;
		inputfile.close();
		
		
	}
	void save(std::string file){
		std::cout <<"saving" <<std::endl;
		std::ofstream outputfile(file, std::ios::binary);
				//creating temporary array
		char * save_arr = new char[samplenum*2];
		int count = 0;
		int k = 0;
		std::cout << "hi" << std::endl;
		while (k<samplenum)
		{
			
			save_arr[count] = (char)audiovec[k].first;
			save_arr[count+1] = (char)audiovec[k].second;
			count = count+2;
			k++;
		}
		std::cout << count << std::endl;
		//write temporary array contents to output file
		
		outputfile.write(save_arr, samplenum*2);
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
	
	
		Audio cut(std::pair<int,int> cutrange){
		Audio answer(*this);
		std::vector<std::pair<T,T>> newaudiovec;
		
		int startsmpl = cutrange.first*fs*2; //multiply by sampling freq        ************establish why
		int endsmpl = cutrange.second*fs*2;
		newaudiovec.resize(samplenum - (endsmpl-startsmpl) + 1);
		std::cout << "secs " <<(samplenum )*1/fs <<std::endl;
		auto beg1 = answer.audiovec.begin(), end1 = answer.audiovec.end();    
		auto beg2 = newaudiovec.begin(), end2 = newaudiovec.end();
		auto cutstart = beg1+startsmpl+1, cutend = beg1+endsmpl;
		std::cout<<"new "<<newaudiovec.size()<<std::endl;
		std::cout <<"old " <<this->audiovec.size() <<std::endl;
		std::cout<<"start " <<startsmpl << " end " << endsmpl<<std::endl;
		while(beg1 != cutstart){  //go from beginning to start of cut
			*beg2 = *beg1;
			
			++beg1; ++beg2;
		}
			
		
		while(cutend != end1 ){  //go from end of cut to end
			*beg2 = *cutend;
			
			++cutend; ++beg2; 
		}
		
		answer.audiovec.clear();
		answer.audiovec = newaudiovec;
		answer.samplenum = newaudiovec.size();
		
		return answer;
		
	}
	//concat
	Audio concatenate(Audio & other){
		Audio answer(*this);
		int joinpoint = answer.samplenum;
		answer.samplenum += other.samplenum;
		answer.audiovec.resize(answer.samplenum);
		
		auto beg1 = answer.audiovec.begin() + joinpoint, end1 = answer.audiovec.end();
		auto beg2 = other.audiovec.begin(), end2 = other.audiovec.end();
		
		while(beg1 != end1){
			
			*beg1 = *beg2;
			
			++beg1; ++beg2;
			
		}
		
		return answer;
		
	}
	
	//ranged add
	
	Audio radd(std::pair<int,int> rangepair1,std::pair<int,int> rangepair2, Audio & other){
		Audio answer(*this);
		Audio oth(other);
		std::vector<std::pair<T,T>>  ansraddaudiovec;
		std::vector<std::pair<T,T>>  othraddaudiovec;
		ansraddaudiovec.resize((rangepair1.second - rangepair1.first)*fs*2);
		othraddaudiovec.resize((rangepair2.second - rangepair2.first)*fs*2);
		std::cout << other.audiovec.size()<< std::endl;
		std::copy ( answer.audiovec.begin()+rangepair1.first*fs*2, answer.audiovec.begin()+rangepair1.second*fs*2, ansraddaudiovec.begin() );   // copy range into new vector
		std::cout << "end of radd" << std::endl;
		std::copy ( oth.audiovec.begin()+rangepair2.first*fs*2, oth.audiovec.begin()+rangepair2.second*fs*2, othraddaudiovec.begin() );	//copy range into new vector
		
		answer.audiovec = ansraddaudiovec;
		oth.audiovec = othraddaudiovec;
		
		answer = answer + oth;
		answer.samplenum = answer.audiovec.size();
		
		return answer;
	
	}
	
	
	//volume
	Audio volume(std::pair<float, float> setting){
		Audio volchange(*this);
		
		
		
		auto beg1 = volchange.audiovec.begin(), end1 = volchange.audiovec.end();
		
		while(beg1 != end1){
		
			float left = (*beg1).first * setting.first;
			float right = (*beg1).second * setting.second;
		
		if (left > std::pow(2,bitnum-1)-1){
				(*beg1).first = (std::pow(2,bitnum-1)-1);
			}
			else if(left < -1*std::pow(2,bitnum-1)-1){
				(*beg1).first = -1*(std::pow(2,bitnum-1)-1);
			}
			else{
				(*beg1).first = left;
			}
					
		if (right > std::pow(2,bitnum-1)-1){
				(*beg1).second = (std::pow(2,bitnum-1)-1);
			}
			else if(right < -1*std::pow(2,bitnum-1)-1){
				(*beg1).second = -1*(std::pow(2,bitnum-1)-1);
			}
			else{
				(*beg1).second = right;
			}		
					
					
		++beg1; 
		}
		std::cout <<"check " << volchange.audiovec[2].first <<" " << volchange.audiovec[2].second<<std::endl;
		return volchange;
		
		
	}
	
	//reverse
	Audio reverse(){
		Audio rev(*this);
		std::cout <<"before working rev"<< rev.audiovec[0].first << " " << rev.audiovec[0].second<<std::endl;
		std::reverse(rev.audiovec.begin(),rev.audiovec.end());
		std::cout <<"working rev"<< rev.audiovec[3].first << " " << rev.audiovec[3].second<<std::endl;
		return rev;
	}
	
	
	
	
	// RMS
	std::pair<float, float> rms() {
		
		std::pair<int, int> sumpair = std::make_pair(0,0);

		sumpair = std::accumulate(audiovec.begin(), audiovec.end(), sumpair, [](std::pair<int, int> a, std::pair<T, T> b) {
			a.first = a.first + (b.first*b.first);
			
			a.second = a.second + (b.second*b.second);
			return a;
		});

		float firstfloat = sqrt(sumpair.first / (float)samplenum);
		
		
		float secondfloat = sqrt(sumpair.second / (float)samplenum);

		std::pair<float, float> rmsanswer = std::make_pair(firstfloat, secondfloat);
		
		return rmsanswer;
	}
	
		// normalisation
	Audio normalisation(std::pair<float, float> givenrms) {
		std::pair<float, float> nowrms = rms();

		Audio answer( bitnum, fs);
		answer.samplenum = samplenum;
		if (bitnum == 8) {
			std::transform(audiovec.begin(), audiovec.end(), answer.audiovec.begin(), normalise<int8_t, 2>(givenrms, nowrms, bitnum));
		}
		else if (bitnum == 16) {
			
			
			std::transform(audiovec.begin(), audiovec.end(), answer.audiovec.begin(), normalise<int16_t, 2>(givenrms, nowrms, bitnum));
		}

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
	//concatenate
	Audio operator|( Audio & other){
	return concatenate(other);
	}
	//volume
	Audio operator* (std::pair<float,float> setting){
		return volume(setting);
	}
};



}


#endif