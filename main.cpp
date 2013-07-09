#include <iostream>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>
#include <utility>
#include <string>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/cat.hpp>


#define FUNCTIONRECORD(R, _, name) \
	, \
	FunctionWrapper<HASH(#name), name>

#define CREATEWRAPPER(LIST) \
	typedef Wrapper< \
	FunctionWrapper<0, int> \
	BOOST_PP_LIST_FOR_EACH(FUNCTIONRECORD, _, LIST) \
	> wrapper; \

#define BIGSWITCH(strString) \
	unsigned long strHash =  operator""_toHash(strString.c_str(), strString.length()); \
	switch(strHash) { \
	BOOST_PP_LIST_FOR_EACH(CASE, _, FUNCTIONLIST) \
	default: \
		std::cout<<"No such handle"<<std::endl; \
		break; \
	} 

#define CASE(R, _, T) \
	case HASH(#T): \
		wrapper::GetFunction<HASH(#T)>{}(); \
		break; \

auto f1=[](){ std::cout<<"lambda1"<<std::endl; };
auto f2=[](){ std::cout<<"lambda2"<<std::endl; };
auto f3=[](){ std::cout<<"lambda3"<<std::endl; };
auto f4=[](){ std::cout<<"lambda4"<<std::endl; };
auto f5=[](){ std::cout<<"lambda5"<<std::endl; };

typedef decltype(f1) F1;
typedef decltype(f2) F2;
typedef decltype(f3) F3;
typedef decltype(f4) F4;
typedef decltype(f5) F5;

#define FUNCTIONLIST (F1, (F2, (F3, (F4, (F5, BOOST_PP_NIL)))))

template<class first, class... rest> // first ignored intentionally so macros are easier.
struct Wrapper {
	typedef boost::mpl::map<rest...> mp;
	template<long hash>
	using GetFunction = typename boost::mpl::at<mp, boost::mpl::long_<hash>>::type;
};

template<unsigned long l, class Function>
using FunctionWrapper = boost::mpl::pair<boost::mpl::long_<l>, Function>;

constexpr unsigned long operator "" _toHash ( const char* str, std::size_t length ) {
	return (length>0)?
			static_cast<unsigned long>(str[length-1]>=97?str[length-1]-97:str[length-1]-65) + 
			26*operator ""_toHash(str, length-1)
		:0 ;
}

template<unsigned N>
constexpr unsigned long HASH(const char (&str) [N]) {
	return operator""_toHash(str, N-1);
}

int main(){
	CREATEWRAPPER(FUNCTIONLIST)	
	
	std::string s;
	std::cin>>s;
	BIGSWITCH(s)
}

