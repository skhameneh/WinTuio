/*
 Touch2Tuio - Windows 7 Touch to TUIO Bridge
 http://dm.tzi.de/research/hci/touch2tuio
 
 Copyright (c) 2010 Marc Herrlich and Benjamin Walther-Franks, Research Group Digital Media, TZI, University of Bremen
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <Windows.h>

#include <iostream>
#include <map>
#include <memory>

// TODO: reference additional headers your program requires here
#include "TuioServer.h"

#define CHAR_BUFFER_SIZE 256
