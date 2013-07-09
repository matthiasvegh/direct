#ifndef MACRODEFINES
#define MACRODEFINES

#include <boost/preprocessor/seq/to_list.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/list/to_seq.hpp>
#include <boost/preprocessor/list/for_each.hpp>
#include <boost/preprocessor/tuple/to_list.hpp>
#include <boost/preprocessor/list/append.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/variadic/elem.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/array/enum.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/control/expr_iif.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/at.hpp>


// fuck if I know.
#define BOOST_PP_TUPLE_REM_0() \

#define ENUMERATE(arr) \
	BOOST_PP_ARRAY_ENUM(arr) \

#define STRINGIZE_SEQ2(N, S) \
	BOOST_PP_EXPAND(BOOST_PP_SEQ_ELEM(N, S)) \

#define STRINGIZE_SEQ(N, S) \
	BOOST_PP_STRINGIZE(STRINGIZE_SEQ2(N, S)) \


#define FUNCTIONRECORD(R, _, name) \
	, \
	FunctionWrapper<HASH(STRINGIZE_SEQ(1, name)), BOOST_PP_EXPAND(GET_TYPE_NAME(BOOST_PP_SEQ_ELEM(0, name)))>

#define CREATEWRAPPER(SEQ) \
	BOOST_PP_EXPAND(CREATE_STRUCTS(NEWLIST)) \
	typedef Wrapper< \
	FunctionWrapper<0, int> \
	BOOST_PP_LIST_FOR_EACH(FUNCTIONRECORD, _, SEQ) \
	> wrapper; \

#define BIGSWITCH(strString, args) \
	unsigned long strHash = operator""_toHash(strString.c_str(), strString.length()); \
	switch(strHash) { \
	BOOST_PP_LIST_FOR_EACH(CASE, args, NEWLIST) \
	default: \
		std::cout<<"No such handle"<<std::endl; \
		break; \
	} \

#define CASE(R, args, T) \
	case HASH( STRINGIZE_SEQ(1, T) ): \
		wrapper::GetFunction< \
			HASH(BOOST_PP_STRINGIZE(BOOST_PP_EXPAND(BOOST_PP_SEQ_ELEM(1, T)))) \
		>{}( ENUMERATE(args) ); \
		break; \

#define GET_TYPE_NAME(f) \
	BOOST_PP_CAT(DIRECT_TYPE_, f) \

#define MAKE_TYPE(R, _, f) \
	struct GET_TYPE_NAME(BOOST_PP_SEQ_ELEM(0, f)) { void operator()(FORMAL_PARAMETERS){ BOOST_PP_SEQ_ELEM(0, f)(ACTUAL_PARAMETERS); } };

#define CREATE_STRUCTS(l) \
	BOOST_PP_LIST_FOR_EACH(MAKE_TYPE, _, l) \

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
			static_cast<unsigned long>(str[length-1]>='A'?str[length-1]-'A':(str[length-1]<'a'?str[length-1]-'0':str[length-1]-'A')) + 
			26*operator ""_toHash(str, length-1)
		:0 ;
}

template<unsigned N>
constexpr unsigned long HASH(const char (&str) [N]) {
	return operator""_toHash(str, N-1);
}

#endif

