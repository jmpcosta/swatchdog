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

// Include C system headers
#include <sys/types.h>
#include <sys/wait.h>

// Import C++ system headers
#include <cerrno>

// Import OSAPI headers
#include "osapi.hh"

// Import project headers
#include "general_defs.hh"
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
  	  log.error( "Child died. Restarting" );
  	  Service::getService().getManager().setChildAlive( false );
  	  procMgr::postMortem();
  	  //start();
    }

  errno = myError;		// Restore errno
}



void procMgr::postMortem( void )
{
 pid_t		pid 		= (pid_t) 0;
 int 		status 		= 0;
 Log &		log			= Log::getLog();

 // Get the status of the child process
 pid = waitpid( -1, &status, WNOHANG );

 switch( pid )
       {
  	  	  case 0:	/* Child alive: status not available	*/
  	  		  	  	log.warn( "pos Mortem called but there is no dead child !" );
  	  		  	  	break;

  	  	  case -1:	/* An error occurred (e.g. interrupted function call, child died,...) */
  	  		  	  	if( errno == ECHILD )
  	  		  	  		log.warn( "Unable to get post Mortem status information" );
  	  		  	  	else
  	  		  	  	  {
  	  		  	  		string msg = "waitpid function error ";
  	  		  	  		msg += std::to_string( errno );
  	  		  	  		log.warn( msg );
  	  		  	  	  }
  	  		  	  	break;

  	  	  default:
  	  		  	  	if( pid > 0 )	/* Status available: Process dead. */
  	  		  	  		procMgr::display_status( status );
  	  		  	  	else
  	  		  	  	  {
  	  		  	  		string str ="waitpid returned for PID ";
  	  		  	  		str += std::to_string( pid );
  	  		  	  		str += "with status ";
  	  		  	  		str += std::to_string( status );
  	  		  	  		str += "and errno";
  	  		  	  		str += std::to_string( errno );
  	  		  	  		log.error( str );
  	  		  	  	  }
  	  		  	  	break;

       }
}



void procMgr::display_status( int status )
{
 int		rs;
 string		str;
 Log &		log			= Log::getLog();

 if( WIFEXITED( status ) )
   {
	 rs = WEXITSTATUS( status );
	 str = "Normal child termination, exit status = "; str += std::to_string( rs );
     log.info( str );
     return;
   }

 if( WIFSTOPPED( status ) )
   {
	 rs = WSTOPSIG( status );
	 str = "child stopped, signal number = "; str += std::to_string( rs );
     log.warn( str );
     return;
   }

 if( WIFSIGNALED( status ) )
   {
		 rs = WTERMSIG( status );
		 str = "Abnormal child termination, signal number = ";
		 str += std::to_string( rs );

		 #ifdef WCOREDUMP
		  if( WCOREDUMP( status ) )   str += "(core file generated)";
		 #endif

		 log.error( str );
   }
}



#endif		// OS_LINUX