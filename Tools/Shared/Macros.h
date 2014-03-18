// This code is part of the Super Play Library (http://www.superplay.info),
// and may only be used under the terms contained in the LICENSE file,
// included with the Super Play Library.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.

#pragma once

#include <map>
#include <memory>

// Define a namespace
#define NAMESPACE(name) namespace name {
#define ENDNAMESPACE }

// Create a shared pointer
#define SHAREDPTR(type, ptr) std::shared_ptr<type>(ptr)
 
 // Create class name+"Ptr" shared pointer typedef
#define CLASSPTR(name) class name; typedef std::shared_ptr<name> name ## Ptr;

 // Create data+"Ptr" shared pointer typedef
#define DATAPTR(name, type) typedef std::shared_ptr<type> name ## Ptr;

// Create a map, pair and iterator
#define MAPTYPE(key, value, name) typedef std::map<key, value> name ## Map; typedef std::pair<key, value> name ## Pair; typedef std::map<key, value>::iterator name ## Iterator;
#define UNORDERED_MAPTYPE(key, value, name) typedef std::unordered_map<key, value> name ## Map; typedef std::pair<key, value> name ## Pair; typedef std::unordered_map<key, value>::iterator name ## Iterator;
#define LISTTYPE(value, name) typedef std::list<value> name ## List; typedef std::list<value>::iterator name ## Iterator;
