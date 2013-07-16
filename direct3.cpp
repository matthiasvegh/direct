#include <iostream>
#include <string>
#include "defines.hpp"
#include "functions.hpp"

#define FORMAL_PARAMETERS \
	int First, float Second \

#define ACTUAL_PARAMETERS \
	First, Second \

#define NEWLIST \
	((g1)(a), \
	((g2)(b), \
	((g3)(c), \
	((g4)(d), \
	((g5)(e), \
	((g6)(f), \
	BOOST_PP_NIL))))))
	
int main(int argc, const char* argv[]){
	if(argc > 1){
		CREATEWRAPPER(NEWLIST)
		std::string s(argv[1]);
		auto v=BIGSWITCH(s, (2, (1, 1.)));
		std::cout<<v<<std::endl;
	}
}

