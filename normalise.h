#ifndef _NORMALISE_H
#define _NORMALISE_H
#include <cstdint>
#include <utility>
#include "Audio.h"

template<typename T, int channelnum = 1>    //single channel
class normalise {
public:

	int bitnum;
	float rmsgiven;
	float nowrms;
	

	normalise(float giverms, float rmsnow, int numbit):  bitnum(numbit), nowrms(rmsnow),rmsgiven(giverms){}

	float operator()( T & in) {
		
		float floatanswer =   rmsgiven *in/ nowrms;

			if (bitnum == 16) {
			if (floatanswer > INT16_MAX) {
				
				floatanswer = INT16_MAX;
			}
			if (floatanswer < INT16_MIN) {
				floatanswer = INT16_MIN;
				
			}
		}
		else if (bitnum == 8) {
			if (floatanswer > INT8_MAX) {
				floatanswer = INT8_MAX;
			}
			
			if (floatanswer < INT8_MIN) {
				floatanswer = INT8_MIN;
			}
		}
		

		return floatanswer;
	}
};


template<typename T>    	// double channel
class normalise<T, 2>{
public:
	std::pair<float, float> rmsgiven;
	std::pair<float, float> rmsnow;
	
	int bitnum;

	normalise(std::pair<float, float> giverms, std::pair<float, float> nowrms, int bitnumber) : rmsgiven(giverms), bitnum(bitnumber), rmsnow(nowrms) {}

	std::pair<float, float> operator()(const std::pair<float, float> & in)const {
		float firstfloat = in.first * rmsgiven.first / rmsnow.first;


			if (bitnum == 16) {
			if (firstfloat > INT16_MAX) {
				firstfloat = INT16_MAX;
			}
			if (firstfloat < INT16_MIN) {
				firstfloat = INT16_MIN;
			}
		}
		else if (bitnum == 8) {
			if (firstfloat > INT8_MAX) {
				firstfloat = INT8_MAX;
			}
			if (firstfloat < INT8_MIN) {
				firstfloat = INT8_MIN;
			}
		}
		

		float secondfloat = in.second * rmsgiven.second /rmsnow.second;
		 if (bitnum == 16) {
			if (secondfloat > INT16_MAX) {
				secondfloat= INT16_MAX;
			}
			if (secondfloat < INT16_MIN) {
				secondfloat = INT16_MIN;
			}
		}
		else if (bitnum == 8) {
			if (secondfloat > INT8_MAX) {
				secondfloat = INT8_MAX;
			}
			if (secondfloat < INT8_MIN) {
				secondfloat = INT8_MIN;
			}
		}
		

		std::pair<float, float> outputpair = std::make_pair(firstfloat, secondfloat);
		return outputpair;
	}
};
#endif
