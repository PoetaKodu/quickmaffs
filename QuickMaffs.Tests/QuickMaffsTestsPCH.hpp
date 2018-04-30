#pragma once

// Headers for CppUnitTest
#include "CppUnitTest.h"

// QuickMaffs
#include <QuickMaffs/Everything.hpp>
#ifndef QUICKMAFFS_HEADER_ONLY
#error "QuickMaffs needs to be compiled separately! When QuickMaffs is properly linked, remove this error."
#endif
namespace math = quickmaffs; // alias the namespace not to use the long one.

// Standard:
#include <array>



// TODO: reference additional headers your program requires here
