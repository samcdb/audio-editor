#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Audio.h"

using namespace std;
using namespace DBRSAM003;


TEST_CASE("Testing Overloaded operators ", ""){
	
	 Audio<int8_t, 1> test1(8,1,4,{2,30,1,40});
    Audio<int8_t, 1> test2(8,1,6,{20,12,132,3,5,6});
    Audio<int16_t, 2> test3(16,1,4,{10,70,5,90});
    Audio<int16_t, 2> test4(16,1,4,{50,60,70,80});
    Audio<int8_t, 1> test5(8,1,3,{43,45,90});
    Audio<int16_t, 2> test6(16,1,6,{23,4,16,27,15,24});
    Audio<int8_t, 1> test7(8,1,4,{2,4,5,1});
    Audio<int16_t, 2> test8(16,1,3,{51,67,89});
	Audio<int16_t, 2> test9(16,1,1,{51});
	Audio<int16_t, 2> test10(16,1,1,{52});
	
	SECTION("Add operation single channel and + overload"){
       Audio<int8_t, 1> addtest = test1 + test7;
        
        REQUIRE(addtest.getAudiovec()[0]==4);
        REQUIRE(addtest.getAudiovec()[1]==34);
        REQUIRE(addtest.getAudiovec()[2]==6);
        REQUIRE(addtest.getAudiovec()[3]==41);
		
       
    }
	
	SECTION("Cut operation single channel and ^ overload"){
		std::pair<int, int> testpair = std::make_pair(1,2);
       Audio<int8_t, 1> cuttest = test1^testpair;
        
        REQUIRE(cuttest.getAudiovec()[0]==2);
        REQUIRE(cuttest.getAudiovec()[1]==30);
		
	}


SECTION("Radd operation single channel"){
		std::pair<int, int> testpair1 = std::make_pair(1,2);
		std::pair<int, int> testpair2 = std::make_pair(0,1);
       Audio<int8_t, 1> raddtest1 = test2;
	    Audio<int8_t, 1> raddtest2 = test7;
		Audio<int8_t,1> raddtest3 = test2.radd(testpair1,testpair2,raddtest2);
	   
        
        REQUIRE(raddtest3.getAudiovec()[0]==12);
        
		
       
    }	
	
	SECTION("Cat operation single channel and | overload"){
		
       Audio<int8_t, 1> cattest1 = test2;
	    Audio<int8_t, 1> cattest2 = test7;
		Audio<int8_t,1> cattest3 = cattest1|cattest2;
	   
        
        REQUIRE(cattest3.getAudiovec()[0]==cattest1.getAudiovec()[0]);
		REQUIRE(cattest3.getAudiovec()[1]==cattest1.getAudiovec()[1]);
		REQUIRE(cattest3.getAudiovec()[2]==cattest1.getAudiovec()[2]);
		REQUIRE(cattest3.getAudiovec()[3]==cattest1.getAudiovec()[3]);
		REQUIRE(cattest3.getAudiovec()[4]==cattest1.getAudiovec()[4]);
		REQUIRE(cattest3.getAudiovec()[5]==cattest1.getAudiovec()[5]);
		REQUIRE(cattest3.getAudiovec()[6]==cattest2.getAudiovec()[0]);
		REQUIRE(cattest3.getAudiovec()[7]==cattest2.getAudiovec()[1]);
		REQUIRE(cattest3.getAudiovec()[8]==cattest2.getAudiovec()[2]);
		REQUIRE(cattest3.getAudiovec()[9]==cattest2.getAudiovec()[3]);
        
		
       
    }	
	
		SECTION("Reverse operation single channel"){
		
       Audio<int8_t, 1> revtest1 = test1;
	    
		Audio<int8_t,1> revtest3 = revtest1.reverse();
	   
        
        REQUIRE(revtest3.getAudiovec()[0]==revtest1.getAudiovec()[3]);
		REQUIRE(revtest3.getAudiovec()[1]==revtest1.getAudiovec()[2]);
		REQUIRE(revtest3.getAudiovec()[2]==revtest1.getAudiovec()[1]);
		REQUIRE(revtest3.getAudiovec()[3]==revtest1.getAudiovec()[0]);
	
        
		
       
    }	
	
	
	
	
	
	SECTION("Add operation double channel, 16 bit and + overload"){
       Audio<int16_t, 2> addtest = test3 + test4;
       
		
        REQUIRE((addtest.getfirst(0)==60));
		  REQUIRE((addtest.getsecond(0)==60));
        REQUIRE((addtest.getfirst(1)==130));
		 REQUIRE((addtest.getsecond(1)==130));
        REQUIRE((addtest.getfirst(2)==75));
		REQUIRE((addtest.getsecond(2)==75));
        REQUIRE((addtest.getfirst(3)==170));
		REQUIRE((addtest.getsecond(3)==170));
		
       
    }
	SECTION("Cut operation double channel and ^ overload"){
		std::pair<int, int> testpair = std::make_pair(0,2);
       Audio<int16_t, 2> cuttest = test4^testpair;
        
        REQUIRE(cuttest.getfirst(0)==50);
		REQUIRE(cuttest.getsecond(0)==50);
        
		
	}
	
	SECTION("Radd operation double channel"){
		std::pair<int, int> testpair1 = std::make_pair(1,2);
		std::pair<int, int> testpair2 = std::make_pair(0,1);
       Audio<int16_t, 2> raddtest1 = test3;
	    Audio<int16_t, 2> raddtest2 = test4;
		Audio<int16_t,2> raddtest3 = test3.radd(testpair1,testpair2,raddtest2);
	   
        
        REQUIRE(raddtest3.getfirst(0)==55);
		REQUIRE(raddtest3.getsecond(0)==55);
        
		
       
    }
	
		SECTION("Cat operation double channel and | overload"){
		
       Audio<int16_t, 2> cattest1 = test9;
	    Audio<int16_t, 2> cattest2 = test10;
		Audio<int16_t,2> cattest3 = cattest1|cattest2;
	   
        
        REQUIRE(cattest3.getfirst(0)==cattest1.getfirst(0));
		 REQUIRE(cattest3.getsecond(0)==cattest1.getsecond(0));
		 REQUIRE(cattest3.getfirst(1)==cattest2.getfirst(0));
		  REQUIRE(cattest3.getsecond(1)==cattest2.getsecond(0));
	
        
		
       
    }	
	
			SECTION("Reverse operation double channel"){
		
       Audio<int16_t, 2> revtest1 = test8;
	    
		Audio<int16_t,2> revtest3 = revtest1.reverse();
	   
        
        REQUIRE(revtest3.getfirst(0)==revtest1.getfirst(2));
		REQUIRE(revtest3.getsecond(0)==revtest1.getsecond(2));
		REQUIRE(revtest3.getfirst(1)==revtest1.getfirst(1));
		REQUIRE(revtest3.getsecond(1)==revtest1.getsecond(1));
		REQUIRE(revtest3.getfirst(2)==revtest1.getfirst(0));
		REQUIRE(revtest3.getsecond(2)==revtest1.getsecond(0));
	
        
		
       
    }	
	
	
	//SPECIAL MEMBER FUNCTIONS
	
	SECTION("copy constructor 8 bit mono"){
		
       Audio<int8_t, 1> revtest1 = test9;
	    
		
	   
        
        REQUIRE(revtest3.getfirst(0)==);
		REQUIRE(revtest3.getsecond(0)==revtest1.getsecond(2));
		REQUIRE(revtest3.getfirst(1)==revtest1.getfirst(1));
		REQUIRE(revtest3.getsecond(1)==revtest1.getsecond(1));
		REQUIRE(revtest3.getfirst(2)==revtest1.getfirst(0));
		REQUIRE(revtest3.getsecond(2)==revtest1.getsecond(0));
	
        
		
       
    }	
	
	
	
}
