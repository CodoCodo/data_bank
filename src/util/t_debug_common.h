#ifndef _T_DEBUG_COMMON_H
#define _T_DEBUG_COMMON_H

#include <iostream>

#define T_DEBUG_OS(os) (os << __FILE__ << '\t' << __LINE__)

#define T_DEBUG_COUT T_DEBUG_OS(std::cout)
#define T_DEBUG_CERR T_DEBUG_OS(std::cerr)

#endif // _T_DEBUG_COMMON_H
