#include <iostream>
#include <string>
#include "defines.hpp"
#include "functions.hpp"

#define FORMAL_PARAMETERS \
	int First, float Second \

#define ACTUAL_PARAMETERS \
	First, Second \

auto f1=[](FORMAL_PARAMETERS){ g1(ACTUAL_PARAMETERS); };
auto f2=[](FORMAL_PARAMETERS){ g2(ACTUAL_PARAMETERS); };
auto f3=[](FORMAL_PARAMETERS){ g3(ACTUAL_PARAMETERS); };
auto f4=[](FORMAL_PARAMETERS){ g4(ACTUAL_PARAMETERS); };
auto f5=[](FORMAL_PARAMETERS){ g5(ACTUAL_PARAMETERS); };

#define NEWLIST \
	((g1)(a), \
	((g2)(b), \
	((g3)(c), \
	((g4)(d), \
	((g5)(e), \
	BOOST_PP_NIL)))))

CREATE_STRUCTS(NEWLIST)


#define FUNCTIONLIST \
		((decltype(f1))(a), \
		((decltype(f2))(b), \
		((decltype(f3))(c), \
		((decltype(f4))(d), \
		((decltype(f5))(e), \
		BOOST_PP_NIL)))))

	
int main(){

	CREATEWRAPPER(FUNCTIONLIST)
	std::string s;
	std::cin>>s;
	BIGSWITCH(s, (2, (1, 1.)))
		
}

