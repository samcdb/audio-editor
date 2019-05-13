#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Audio.h"

using namespace std;
using namespace DBRSAM003;


TEST_CASE("Testing single channel overloaded operators ", ""){

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
	Audio<int8_t,1>	  test11(8,1,1,{3});

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



}

TEST_CASE("Testing double channel overloaded operators ", ""){

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
	Audio<int8_t,1>	  test11(8,1,1,{3});

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

}
TEST_CASE("Testing mono 8 special member functions", ""){

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
	Audio<int8_t,1>	  test11(8,1,1,{3});
	//SPECIAL MEMBER FUNCTIONS mono

	SECTION("copy constructor 8 bit mono"){

       Audio<int8_t, 1> copytest = test11;




        REQUIRE(copytest.getbitnum()==test11.getbitnum());
		REQUIRE(copytest.getchannelnum()==test11.getchannelnum());
		REQUIRE(copytest.getfs()==test11.getfs());
		REQUIRE(copytest.getAudiovec()[0]==test11.getAudiovec()[0]);




    }



	SECTION("copy assignment 8 bit mono"){

       Audio<int8_t, 1> copyassign1 = test11;
	   Audio<int8_t, 1> copyassign2 = test5;

		copyassign2 = copyassign1;



        REQUIRE(copyassign1.getbitnum()==copyassign2.getbitnum());
		REQUIRE(copyassign1.getchannelnum()==copyassign2.getchannelnum());
		REQUIRE(copyassign1.getfs()==copyassign2.getfs());
		REQUIRE(copyassign1.getAudiovec()[0]==copyassign2.getAudiovec()[0]);


    }

	SECTION("move assignment operator 8 bit mono"){

       Audio<int8_t, 1> movecon1 = test11;
	   Audio<int8_t, 1> movecon2 = test5;

		movecon1 = std::move(movecon2);



        REQUIRE(movecon1.getbitnum()==8);

		REQUIRE(movecon1.getfs()==1);
		REQUIRE(movecon1.getAudiovec()[0]==3);


		REQUIRE(movecon2.getbitnum()==-1);
		REQUIRE(movecon2.getchannelnum()==-1);
		REQUIRE(movecon2.getfs()==-1);




    }

	SECTION("move constructor 8 bit mono"){


	   Audio<int8_t, 1> movecon2 = test5;

		Audio<int8_t, 1>movecon1 = std::move(movecon2);



        REQUIRE(movecon1.getbitnum()==8);

		REQUIRE(movecon1.getfs()==1);



		REQUIRE(movecon2.getbitnum()==-1);
		REQUIRE(movecon2.getchannelnum()==-1);
		REQUIRE(movecon2.getfs()==-1);


    }
}
TEST_CASE("Testing stereo special member functions ", ""){

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
	Audio<int8_t,1>	  test11(8,1,1,{3});
	//SPECIAL MEMBER FUNCTIONS stereo

	SECTION("copy constructor 16 bit stereo"){

       Audio<int16_t, 2> copytest = test10;




        REQUIRE(copytest.getbitnum()==test10.getbitnum());
		REQUIRE(copytest.getchannelnum()==test10.getchannelnum());
		REQUIRE(copytest.getfs()==test10.getfs());
		REQUIRE(copytest.getfirst(0)==test10.getfirst(0));
		REQUIRE(copytest.getsecond(0)==test10.getsecond(0));




    }



	SECTION("copy assignment operator 16 bit stereo"){

       Audio<int16_t, 2> copyassign1 = test10;
	   Audio<int16_t, 2> copyassign2 = test3;

		copyassign2 = copyassign1;



        REQUIRE(copyassign1.getbitnum()==copyassign2.getbitnum());
		REQUIRE(copyassign1.getchannelnum()==copyassign2.getchannelnum());
		REQUIRE(copyassign1.getfs()==copyassign2.getfs());

		REQUIRE(copyassign1.getfirst(0)==copyassign2.getfirst(0));
		REQUIRE(copyassign1.getsecond(0)==copyassign2.getsecond(0));


    }

	SECTION("move assignment operator 16 bit stereo"){

       Audio<int16_t, 2> movecon1 = test3;
	   Audio<int16_t, 2> movecon2 = test10;

		movecon1 = std::move(movecon2);



        REQUIRE(movecon1.getbitnum()==16);

		REQUIRE(movecon1.getfs()==1);
		REQUIRE(movecon1.getfirst(0)==52);
		REQUIRE(movecon1.getsecond(0)==52);


		REQUIRE(movecon2.getbitnum()==-1);
		REQUIRE(movecon2.getchannelnum()==-1);
		REQUIRE(movecon2.getfs()==-1);




    }

	SECTION("move constructor 16 bit stereo"){


	   Audio<int16_t, 2> movecon2 = test10;

		Audio<int16_t, 2>movecon1 = std::move(movecon2);



        REQUIRE(movecon1.getbitnum()==16);

		REQUIRE(movecon1.getfs()==1);



		REQUIRE(movecon2.getbitnum()==-1);
		REQUIRE(movecon2.getchannelnum()==-1);
		REQUIRE(movecon2.getfs()==-1);


	}}
