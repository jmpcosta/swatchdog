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
//#ifdef OS_LINUX


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <unistd.h>

// Import OSAPI+ header
#include "osapi.hh"

// Import service headers
#include "service.hh"


// *****************************************************************************************
//
// Section: Import namespaces
//
// *****************************************************************************************

// Import C++ Standard namespace
using namespace std;

// Import OSAPI+ namespaces
using namespace osapi;



// *****************************************************************************************
//
// Section: Method definition
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

void systemService::plug()
{
  //registerHandler();
}

void systemService::unplug()
{
  //unregisterHandler();
}


void systemService::waitForWork( void )
{
 // Pause process
 process::suspend();
}

/*
void systemService::processNotification()
{

}
*/
void systemService::createServiceManager()
{

}

//#endif		// OS_LINUX
