#include "Audio.h"

using namespace std;


int main(int argc, char *argv[])
{
	
	//ADD
	if (argc == 12 && string(argv[9]) == "-add"){  //check if add command
		cout << "Adding" << endl;
		int channelnum;
		int bitsize;
		stringstream sstream;
		
		
		//getting number of channels
		sstream << string(argv[6]);
		sstream >> channelnum;
		
		//getting bit sample size
		sstream << string(argv[4]);
		sstream >> bitsize
		
		
		if(channelnum ==1){   // mono file
			cout<< "Mono" << endl;
			
			if(bitsize == 8){
				
			}
			
			
			
		}
		
		
		
		
		else if(channelnum ==2)   //stereo file
		cout << "Stereo" << endl;
		
		
		
		
	}
	
	
	else if (argc == 5 && string(argv[9]) == "add" ){ 	//check if add command
		cout << "Adding" << endl;
		
		
	}
	
	
	
	
	
}