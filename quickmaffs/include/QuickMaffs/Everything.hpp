#pragma once

// When this file is included from other project, we need to define what "QUICKMAFFS_PCH" macro stands for
// because it is defined inside project settings, not in any other file.
#ifndef QUICKMAFFS_ACTIVE_PROJECT
#define QUICKMAFFS_PCH "QuickMaffs/../../QuickMaffsPCH.hpp"
#endif

#include "Math/Helper.hpp"
#include "Math/Length.hpp"
#include "Math/TypeTraits.hpp"
#include "Math/Random.hpp"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/VectorStringBuilder.hpp"