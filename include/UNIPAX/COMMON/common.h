// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// --------------------------------------------------------------------------
//                               UNIPAX
// --------------------------------------------------------------------------
//  Copyright (C) 2011 -- Oliver Kohlbacher, Hans-Peter Lenhof
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 3 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------
// $Id:$
// $Author:$
// $Maintainer:$
// --------------------------------------------------------------------------
//
#ifndef UNIPAX_COMMON_COMMON_H
#define UNIPAX_COMMON_COMMON_H

#include <UNIPAX/CONFIG/config.h>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/functional/hash.hpp>
#include <stdint.h>

#ifdef __ECLIPSE_CDT__
# define UNIPAX_EXPORT
# define UNIPAX_LOCAL
# define UNIPAX_EXTERN_VARIABLE extern
#elif UNIPAX_COMPILER_IS_MSVC
# define UNIPAX_LOCAL
# ifdef UNIPAX_BUILD_DLL
#  define UNIPAX_EXPORT __declspec(dllexport)
#  define UNIPAX_EXTERN_VARIABLE __declspec(dllexport) extern
# else
#  define UNIPAX_EXPORT __declspec(dllimport)
#  define UNIPAX_EXTERN_VARIABLE __declspec(dllimport) extern
# endif
#elif defined(UNIPAX_COMPILER_IS_GNUCXX) && (__GNUC__ >= 4)
# define UNIPAX_EXPORT __attribute((visibility ("default")))
# define UNIPAX_LOCAL __attribute((visibility ("hidden")))
# define UNIPAX_EXTERN_VARIABLE extern __attribute((visibility ("default")))
#else
# define UNIPAX_EXPORT
# define UNIPAX_LOCAL
# define UNIPAX_EXTERN_VARIABLE extern
#endif

//This declares a UNIPAX_DEPRECATED macro that can be used to mark deprecated api
//It is essentially copied from Qt 4.4.1 but simplified, thus there might be
//some cases where it does not work as expected.
#if defined(UNIPAX_COMPILER_IS_MSVC) && (_MSC_VER >= 1300)
    #define UNIPAX_DEPRECATED __declspec(deprecated)
#elif defined(UNIPAX_COMPILER_IS_GNUCXX) && (__GNUC__ >= 4)
    #define UNIPAX_DEPRECATED __attribute__((deprecated))
#else
    #define UNIPAX_DEPRECATED
#endif

// UniPAX type definitions

//typedef unsigned long long UnipaxId;
typedef unsigned long long UnipaxId;
typedef boost::posix_time::ptime UnipaxTime;
typedef boost::posix_time::microsec_clock micro_sec;

template<class T>
struct UnipaxPtr
{
	typedef boost::shared_ptr<T> type;
};

#endif //UNIPAX_COMMON_COMMON_H
