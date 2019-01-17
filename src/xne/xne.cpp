/**
 * @file    xne.cpp
 * @author  isnullxbh
 * @date    2019-01-16 06:47
 * @version 0.0.1
 */

#include "xne/xne.h"

#ifndef XNE_VERSION
#   define XNE_VERSION  "unknown"
#endif  // XNE_VERSION

namespace xne {

std::string_view version() {
    return XNE_VERSION;
}

} // namespace xne
