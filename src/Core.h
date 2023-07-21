#include <assert.h>
#include <iostream>

#define ASSERT(x, message) if (!(x)) \
    {\
    std::cout << "[ASSERTION FAILED]: " << message << " FILE: " << __FILE__ << \
        " LINE: " << __LINE__ << std::endl; \
    assert(x); \
    }
