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
				DBRSAM003::Audio<int8_t,1> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int8_t,1> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
				//save output
			//	audio3.save(string(argv[8]));
				
			}
			
			else if(bitsize == 16){ //16 bit sample size
				DBRSAM003::Audio<int16_t,1> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int16_t,1> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
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
				//save output
				audio1.save(string(argv[8]));
			}
			
			else if(bitsize == 16){ //16 bit sample size
				DBRSAM003::Audio<int16_t,2> audio1(bitsize, samplefreq);
				DBRSAM003::Audio<int16_t,2> audio2(bitsize, samplefreq);
				
				//loading files
				audio1.load(string(argv[10]));
				audio2.load(string(argv[11]));
				//save output
				audio1.save(string(argv[8]));
			}
	}
	//END OF ADD

	
	
	
	
	}
	
	
	else if (argc == 5 && string(argv[9]) == "add" ){ 	//check if add command
		cout << "Adding" << endl;
		
		
	}
	
	
	
	
	

} 