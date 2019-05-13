#include "Audio.h"

using namespace std;


int main(int argc, char *argv[])
{
	
	
	int channelnum;
		int bitsize;
		int samplefreq;
		stringstream sstream;
		
		
		//getting number of channels
		sstream << string(argv[6]);
		sstream >> channelnum;
		sstream.clear();
		
		//getting bit sample size
		sstream << string(argv[4]);
		sstream >> bitsize;
		sstream.clear();
		
		//getting sampling frequency
		sstream << string(argv[2]);
		sstream >> samplefreq;
		sstream.clear();
		
		
		cout << bitsize << " bit sample size" << endl;
		cout << samplefreq << " Hz sampling frequency" <<endl;
		
		
	
	//ADD
	if (argc == 12 && string(argv[9]) == "-add"){  //check if add command
		cout << "Adding" << endl;
		//two Audio objects
		
		

		if(channelnum ==1){   // mono file
		
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			cout <<"8"<<endl;
				DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int8_t,1> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
				
				//add files together
				DBRSAM003::Audio<int8_t,1> sum = audio1+audio2;
				//save output
				audio1.save(string(argv[8]));
				
			}
			
			else if(bitsize == 16){ //16 bit sample size
			cout <<"16" << endl;
				DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int16_t,1> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
				//add files together
			//	DBRSAM003::Audio<int16_t,1> sum = audio1+audio2;
				//save output
				audio1.save(string(argv[8]));
			}
		}
		
		else if(channelnum ==2){   //stereo file
			cout << "Stereo" << endl;
			if(bitsize == 8){ //8 bit sample size
				DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int8_t,2> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
				//add files together
				DBRSAM003::Audio<int8_t,2> sum = audio1+audio2;
				//save output
				sum.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
				DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int16_t,2> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
				//add files together
				DBRSAM003::Audio<int16_t,2> sum = audio1+audio2;
				//save output
				sum.save(string(argv[8]));
			}
	}
	}
	//END OF ADD
	
	
	//cut
	else if (argc == 13 && string(argv[9]) == "-cut" ){ 	//check if cut command
		cout << "Cutting" << endl;
		int cutstart;
		int cutend;
		sstream << string(argv[10]);
		sstream >> cutstart;
		sstream.clear();
		sstream << string(argv[11]);
		sstream >> cutend;
		sstream.clear();
		std::pair<int,int> cutrange = std::make_pair(cutstart,cutend);
		
		
		if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			//loading file
				audio1.load(string(argv[12]));
			//cut
			DBRSAM003::Audio<int8_t,1> cutaudio = audio1^cutrange;
			//save output
			cutaudio.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			//loading file
				audio1.load(string(argv[12]));
			//cut
			DBRSAM003::Audio<int16_t,1> cutaudio = audio1^cutrange;
				//save output
			cutaudio.save(string(argv[8]));
			}
			
		}
		
		else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			//loading file
				audio1.load(string(argv[12]));
			//cut
			DBRSAM003::Audio<int8_t,2> cutaudio = audio1^cutrange;
				//save output
			cutaudio.save(string(argv[8]));
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			//loading file
				audio1.load(string(argv[12]));
			//cut
			DBRSAM003::Audio<int16_t,2> cutaudio = audio1^cutrange;
				//save output
			cutaudio.save(string(argv[8]));
			}
		
		}
		
	}
	
	//END OF CUT
	
	
	//CONCATENATE
	
	else if (argc == 12 && string(argv[9]) == "-cat" ){  //check if concatenate command
	cout << "Concatenating" << endl;
	if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int8_t,1> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
			//concatenate
			DBRSAM003::Audio<int8_t,1> concataudio = audio1|audio2;
			//save output
			concataudio.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int16_t,1> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
			//cut
			DBRSAM003::Audio<int16_t,1> concataudio = audio1|audio2;
				//save output
			concataudio.save(string(argv[8]));
			}
			
		}
		
			else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int8_t,2> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
			//concat
			DBRSAM003::Audio<int8_t,2> concataudio = audio1|audio2;
				//save output
			concataudio.save(string(argv[8]));
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int16_t,2> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
			//concat
			DBRSAM003::Audio<int16_t,2> concataudio = audio1|audio2;
				//save output
			concataudio.save(string(argv[8]));
			}
		
		}
	
	}
	
	
	//Ranged add
	
		else if (argc == 16 && string(argv[9]) == "-radd" ){ 	//check if ranged command
		cout << "Ranged Add" << endl;
		int raddstart1;
		int raddend1;
		sstream << string(argv[10]);
		sstream >> raddstart1;
		sstream.clear();
		sstream << string(argv[11]);
		sstream >> raddend1;
		sstream.clear();
		std::pair<int,int> raddrange1 = std::make_pair(raddstart1,raddend1);
		
		int raddstart2;
		int raddend2;
		sstream << string(argv[12]);
		sstream >> raddstart2;
		sstream.clear();
		sstream << string(argv[13]);
		sstream >> raddend2;
		sstream.clear();
		std::pair<int,int> raddrange2 = std::make_pair(raddstart2,raddend2);
	
		
		if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int8_t,1> audio2(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[14]));
				audio2.load(string(argv[15]));
				
			//ranged add
			DBRSAM003::Audio<int8_t,1> raddaudio = audio1.radd(raddrange1,raddrange2,audio2);
			//save output
			raddaudio.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int16_t,1> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[14]));
				audio2.load(string(argv[15]));
			//ranged add
			DBRSAM003::Audio<int16_t,1> raddaudio = audio1.radd(raddrange1, raddrange2, audio2);
				//save output
			raddaudio.save(string(argv[8]));
			}
			
		}
		
			else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int8_t,2> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[14]));
				audio2.load(string(argv[15]));
			//ranged add
			DBRSAM003::Audio<int8_t,2> raddaudio = audio1.radd(raddrange1, raddrange2, audio2);
				//save output
			raddaudio.save(string(argv[8]));
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			DBRSAM003::Audio<int16_t,2> audio2(bitsize, samplefreq);
			//loading files
				audio1.load(string(argv[14]));
				audio2.load(string(argv[15]));
			//ranged add
			DBRSAM003::Audio<int16_t,2> raddaudio = audio1.radd(raddrange1, raddrange2, audio2);
				//save output
			raddaudio.save(string(argv[8]));
			}
		
		}
		
		
		}
	
	
	//volume
	else if (argc == 13 && string(argv[9]) == "-v" ){ 	//check if volume command
		cout << "Volume" << endl;
		float leftvol;
		float rightvol;
		sstream << string(argv[10]);
		sstream >> leftvol;
		sstream.clear();
		sstream << string(argv[11]);
		sstream >> rightvol;
		sstream.clear();
		
		std::pair<float,float> volpair = std::make_pair(leftvol,rightvol);
		cout << volpair.first << " " <<volpair.second << endl;
		
		if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			
			
			//loading files
				audio1.load(string(argv[12]));
				
				
			//volume
			DBRSAM003::Audio<int8_t,1> volaudio = audio1*(volpair);
			//save output
			volaudio.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[12]));
				
			//volume
			DBRSAM003::Audio<int16_t,1> volaudio = audio1*(volpair);
				//save output
			volaudio.save(string(argv[8]));
			}
			
		}
		
			else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[12]));
				
			//volume
			DBRSAM003::Audio<int8_t,2> volaudio =  audio1*(volpair);
				//save output
			volaudio.save(string(argv[8]));
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[12]));
				
			//ranged add
			DBRSAM003::Audio<int16_t,2> volaudio =  audio1*(volpair);
				//save output
			volaudio.save(string(argv[8]));
			}
		
		}
		
		
		}
		
		
		//reverse
	else if (argc == 11 && string(argv[9]) == "-rev" ){ 	//check if reverse command
		cout << "Reverse" << endl;
		
		
		
		
		if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			
			
			//loading files
				audio1.load(string(argv[10]));
				
				
			//reverse
			DBRSAM003::Audio<int8_t,1> revaudio = audio1.reverse();
			//save output
			revaudio.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//reverse
			DBRSAM003::Audio<int16_t,1> revaudio = audio1.reverse();
				//save output
			revaudio.save(string(argv[8]));
			}
			
		}
		
			else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//reverse
			DBRSAM003::Audio<int8_t,2> revaudio = audio1.reverse();
				//save output
			revaudio.save(string(argv[8]));
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//reverse
			DBRSAM003::Audio<int16_t,2> revaudio = audio1.reverse();
				//save output
			revaudio.save(string(argv[8]));
			}
		
		}
		
		
		}
		
		//rms
	else if (argc == 11 && string(argv[9]) == "-rms" ){ 	//check if reverse command
		cout << "RMS" << endl;
		
		
		
		
		if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			
			
			//loading files
				audio1.load(string(argv[10]));
				
				
			//RMS
			cout << "RMS for channel 1 is " << audio1.rms()<<endl;
			
			
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//RMS
			cout << "RMS for channel 1 is " << audio1.rms()<<endl;
			
			
				
			}
			
		}
		
			else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//RMS
			cout << "RMS for channel 1 is " << audio1.rms().first<<endl;
			cout << "RMS for channel 2 is " << audio1.rms().second<<endl;
			
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//RMS
			cout << "RMS for channel 1 is " << audio1.rms().first<<endl;
			cout << "RMS for channel 2 is " << audio1.rms().second<<endl;
			
			}
		
		}
		
		
		}
		
		
		//normalise
		else if (argc == 13 && string(argv[9]) == "-norm" ){ 	//check if normalise command
		cout << "Normalise" << endl;
		float rms1;
		float rms2;
		sstream << string(argv[10]);
		sstream >> rms1;
		sstream.clear();
		sstream << string(argv[11]);
		sstream >> rms2;
		sstream.clear();
		std::pair<float,float> normpair = std::make_pair(rms1,rms2);
		
		
		
		if(channelnum == 1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){   //8 bit sample size
			
			DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
			
			
			//loading files
				audio1.load(string(argv[10]));
				
				
			//normalise
			DBRSAM003::Audio<int8_t,1> normaudio = audio1.normalisation(normpair);
			//save
			normaudio.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//normalise
			DBRSAM003::Audio<int16_t,1> normaudio = audio1.normalisation(normpair);
			//save
			normaudio.save(string(argv[8]));
			
			
				
			}
			
		}
		
			else if(channelnum ==2){   //stereo file
		cout << "Stereo" << endl;
		if(bitsize == 8){   //8 bit sample size
			DBRSAM003::Audio<int8_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
		
				//normalise
			DBRSAM003::Audio<int8_t,2> normaudio = audio1.normalisation(normpair);
			//save
			normaudio.save(string(argv[8]));
			
			}
		else if(bitsize == 16){ //16 bit sample size
			DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
			
			//loading files
				audio1.load(string(argv[10]));
				
			//normalise
			DBRSAM003::Audio<int16_t,2> normaudio = audio1.normalisation(normpair);
			//save
			normaudio.save(string(argv[8]));
			
			}
		
		}
		
		
		}
	
	
	
	
				
} 

















