// **********************************************************************************************
//
// File description:
//
// Author:		Joao Costa
// Purpose:		Implements a UNIX service/daemon.
// Description: The class uses the OSAPI+ library to implement a UNIX Daemon functionality.
//
// **********************************************************************************************


// Make sure that this implementation is only available in an Unix environment
#ifdef OS_LINUX


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <cerrno>
#include <iostream>
#include <memory>

// Import OSAPI+ header
#include "osapi.hh"

// Import service headers
#include "service.hh"


// *****************************************************************************************
//
// Section: Imports
//
// *****************************************************************************************

// Import C++ Standard namespace
using namespace std;

// Import OSAPI+ namespace
using namespace osapi;


// *****************************************************************************************
//
// Section: UNIX specific service implementation
//
// *****************************************************************************************

// Create the OS System Service
void Service::createSystem( void )
{
 bool		clone			= false;
 Log &		log				= Log::getLog();
 process::Current	& proc	= process::Current::get();

 log.debug( "Entering Service::create" );

 bool success = proc.clone( clone );
 if( ! success )
     log.error( "Cloning process failed" );

 // Terminate parent to become Daemon
 if( ! clone )
	 process::Current::get().terminate( true );

 // Clone / child proceeds
 if( proc.setSession() )
   {
	 log.info( "Successfully set myself as Session Leader" );

	 // Change to a safe directory

	 // Set the default mask: S_IWGRP | S_IWOTH
	 setState( serviceState::inService );
   }

 log.debug( "Leaving Service::create"  );
}


static void termination_handler( int signo )
{
  int myError = errno;	// Save error code since there is only one per thread

  Log & log = Log::getLog();

  if( signo == SIGTERM )
    {
	  Service::getService().getManager().setState( procState::stopping );
	  Service::getService().setState( serviceState::stopping );
	  log.info( "Service Shutdown requested." );
    }

  errno = myError;		// Restore errno
}



// Plug into OS only for termination communication
void Service::plug()
{
 Log &				log = Log::getLog();
 process::Current & cur = process::Current::get();

 log.debug( "Start plugging into the OS service manager." );

 cur.clearAllSignals();

 process::signal term( SIGTERM );

 term.setHandler( termination_handler );

 cur.addSignal( term  );

 cur.activateAllSignals();

 log.debug( "End plugging into the OS service manager." );
}

void Service::unplug()
{
 Log & log = Log::getLog();

 log.debug( "Start unplugging from the OS service manager." );

 process::Current::get().eraseAllSignals();

 log.debug( "End unplugging from the OS service manager." );
}


#endif		// OS_LINUX
