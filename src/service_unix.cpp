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

// Include C headers
#include <errno.h>
#include <signal.h>

// Import C++ system headers
#include <iostream>

// Import OSAPI+ header
#include "osapi.hh"

// Import service headers
#include "service_unix.hh"


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
// Section: UNIX specific service implementation
//
// *****************************************************************************************

bool service::state = false;

void service::setState( bool st )
{
 service::state = st;
}


bool service::getState( void )
{
 return service::state;
}


void service::create( void )
{
 bool		clone		= false;
 Log &		log			= Log::getLog();
 CurrentProcess	& proc	= process::getCurrent();

 log.debug( "Entering service::create" );

 bool success = proc.clone( clone );
 if( ! success )
     log.error( "Cloning process failed" );

 // Terminate parent to become Daemon
 if( ! clone )
	 CurrentProcess::getInstance().terminate( true );

 if( proc.setSession() )
	 log.info( "Successfully set myself as Session Leader" );

 /*
     if( chdir("/") != 0 )
         log.warn( "Unable to change to root directory. Errno (%d)", errno );


     umask( S_IWGRP | S_IWOTH );

     if( rc == JMPC_OK )
         sysRunning = JMPC_TRUE;
   }
*/
 log.debug( "Leaving service::create"  );
}


void service::signal_handler( int signo )
{
  int myError = errno;	// Save error code since there is only one per thread

  Log & log = Log::getLog();

  switch( signo )
        {
  	  	  case SIGCHLD:
  	  	  		  	  	  // restart child;
  	  		  	  	  	  log.info( "Child died." );
  	  	  		  	  	  break;

  	  	  case SIGTERM:
				  	  	  service::setState( false );
				  	  	  log.info( "Service Shutdown requested." );
				  	  	  break;
  	  	  default:
  	  		  	  	  	  // Do nothing
  	  		  	  	  	  break;
        }

  errno = myError;		// Restore errno
}


void service::registerCallback( void )
{
  osapi::signal	sig1( SIGTERM );
  osapi::signal	sig2( SIGCHLD );

  CurrentProcess & proc = CurrentProcess::getInstance();

  sig1.setHandler( service::signal_handler );
  sig2.setHandler( service::signal_handler );

  proc.addSignal( sig1 );
  proc.addSignal( sig2 );

  proc.clearSignals();

  proc.activateSignals();
}


void service::unregisterCallback( void )
{
  process::getCurrent().eraseAllSignals();
}

#endif		// OS_LINUX
