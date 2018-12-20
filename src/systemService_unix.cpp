// **********************************************************************************************
//
// File description:
//
// Author:		Joao Costa
// Purpose:		Implement Service Management OS specific related tasks.
// Description: The file implements the part of the systemService class that is OS more specific.
//				It uses the OSAPI libs but with a static parameterization, i.e. it knows in
//				advance which mechanism are present in the particular OS type, in this case Unix.
// **********************************************************************************************


// Make sure that this implementation is only available in an Unix environment
#ifdef OS_LINUX


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Include C headers
#include <errno.h>
#include <signal.h>

// Import C++ system headers
#include <iostream>

// Import OSAPI+ header
#include "osapi.hh"

// Import service headers
#include "service.hh"
#include <platform_service.hh>


// *****************************************************************************************
//
// Section: Imports
//
// *****************************************************************************************

// Import C++ Standard namespace
using namespace std;

// Import OSAPI+ namespace
using namespace osapi;

extern int errno;




// *****************************************************************************************
//
// Section: API implementation
//
// *****************************************************************************************


void systemService::secureEnvironment()
{
  // First delete own environment
	/*
  deleteEnvironment();
  deleteCmdLine();
  resetSignals();
  resetFileDescriptors();
  preventCoreImages();
  */
}




/*
void systemService::processNotification()
{

}
*/
void systemService::createServiceManager()
{

}

#endif		// OS_LINUX
