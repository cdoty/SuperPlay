// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <TinySTL/unordered_map.h>

// Create an ordered map, pair and iterator
#define UNORDERED_MAPTYPE(key, value, name) typedef tinystl::unordered_map<key, value> name ## Map; typedef tinystl::pair<key, value> name ## Pair; typedef tinystl::unordered_map<key, value>::iterator name ## Iterator;
