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
	
int main(){

	CREATEWRAPPER(NEWLIST)
	std::string s;
	std::cin>>s;
	BIGSWITCH(s, (2, (1, 1.)))
		
}

