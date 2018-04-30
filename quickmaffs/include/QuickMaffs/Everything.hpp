#pragma once

// The following line will be removed (not switched to 0 !) when QuickMaffs will require compiling.
#define QUICKMAFFS_HEADER_ONLY 1

// When this file is included from other project, we need to define what "QUICKMAFFS_PCH" macro stands for
// because it is defined inside project settings, not in any other file.
#ifndef QUICKMAFFS_ACTIVE_PROJECT
#define QUICKMAFFS_PCH "QuickMaffs/../../QuickMaffsPCH.hpp"
#endif

#include <QuickMaffs/Math/Helper.hpp>
#include <QuickMaffs/Math/Length.hpp>
#include <QuickMaffs/Math/TypeTraits.hpp>
#include <QuickMaffs/Math/Random.hpp>
#include <QuickMaffs/Math/Vector2.hpp>
#include <QuickMaffs/Math/Vector3.hpp>
#include <QuickMaffs/Math/VectorStringBuilder.hpp>

// Shapes:
#include <QuickMaffs/Math/ShapesInc.hpp>