#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_
#include <iostream>

float g1(int, float){ std::cout<<__FUNCTION__<<std::endl; return 0.1; }	
float g2(int, float){ std::cout<<__FUNCTION__<<std::endl; return 0.2; }	
float g3(int, float){ std::cout<<__FUNCTION__<<std::endl; return 0.3; }	
float g4(int, float){ std::cout<<__FUNCTION__<<std::endl; return 0.4; }	
float g5(int, float){ std::cout<<__FUNCTION__<<std::endl; return 0.5; }
float g6(int, float){ std::cout<<__FUNCTION__<<std::endl; return 0.6; }
#endif
