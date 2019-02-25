// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	UNIX implementation for child process management functionality
//
// *****************************************************************************************

// Make sure that this implementation is only available in an Unix environment
#ifdef OS_LINUX


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <cerrno>

// Import OSAPI headers
#include "osapi.hh"

// Import project headers
#include <defs.hh>
#include "service.hh"

// Import own header
#include "procMgr.hh"

// *****************************************************************************************
//
// Section: Import namespaces
//
// *****************************************************************************************

// Import C++ Standard namespace
using namespace std;

// Import OSAPI namespace
using namespace osapi;


// *****************************************************************************************
//
// Section: UNIX specific function declarations
//
// *****************************************************************************************

static void child_handler( int signo );


// *****************************************************************************************
//
// Section: Function definition for UNIX implementation
//
// *****************************************************************************************

void procMgr::configureCallback( void )
{
 Log & log = Log::getLog();

 log.debug( "Start configuring callback." );

 // Set handler for process signals
 process::Current & cur = process::Current::get();

 cur.clearAllSignals();

 process::signal child( SIGCHLD );

 child.setHandler( child_handler );

 cur.addSignal( child );
 cur.activateAllSignals();

 log.debug( "End configuring callback." );
}

void procMgr::unconfigureCallback( void )
{
 Log & log = Log::getLog();

 log.debug( "Start unconfiguring callback." );

 process::Current::get().eraseAllSignals();

 log.debug( "End unconfiguring callback." );
}

static void child_handler( int signo )
{
  int myError = errno;	// Save error code since there is only one per thread

  Log & log = Log::getLog();

  if( signo == SIGCHLD )   	  // restart child
    {
  	  log.info( "Managed application died" );
  	  Service::getService().getManager().setState( procState::stopped );
    }

  errno = myError;		// Restore errno
}



#endif		// OS_LINUX
