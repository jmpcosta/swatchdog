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
#include <service_unix.hh>


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

// The UNIX system service callback is made using signals
void systemService::plug()
{
  Log & log = Log::getLog();

  log.debug( "Start plugging into the OS service manager." );

  // Set handler for process signals
  service::set_handlers();

  // Setup as a system service
  service::create();

  log.debug( "End plugging into the OS service manager." );
}

void systemService::unplug()
{
 Log & log = Log::getLog();

 log.debug( "Start unplugging from the OS service manager." );

 process::getCurrent().eraseAllSignals();

 log.debug( "End unplugging from the OS service manager." );
}


void systemService::waitForWork( void )
{
 Log & log = Log::getLog();

 log.debug( "Entering wait for work." );

 process::getCurrent().suspend();

 // If the process was resumed, update my state
 serviceActive = service::getState();

 log.debug( "Leaving wait for work." );
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
