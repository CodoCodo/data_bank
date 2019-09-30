#ifndef _T_COMMON_H
#define _T_COMMON_H

#include <iostream>

#define MEDIA_PATH ("medias/")

#define T_COMMON_OS(os) (os << __FILE__ << '\t' << __LINE__ << '\t')

#define T_COMMON_COUT T_COMMON_OS(std::cout)
#define T_COMMON_CERR T_COMMON_OS(std::cerr)

#endif //_T_COMMON_H
