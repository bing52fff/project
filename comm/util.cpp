#include "util.h"

void debug_printf(const std::string& err)
{
#ifdef _DEBUG_
	std::cerr << err;
#endif
}
