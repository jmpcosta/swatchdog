// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	System Service API definition
//			It implements the logic behind the integration with the OS Service Manager
//
// *****************************************************************************************


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <iostream>
#include <string>


// Import OSAPI+ headers
#include "osapi.hh"

// Import project headers
#include "platform_defs.hh"
#include "platform_service.hh"

// Import own headers
#include "service_defs.hh"
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


// Return a reference to the single instance of systemService
systemService & systemService::getService()
{
 static systemService instance;

 return instance;
}


systemService::systemService()
{
 configurationName = SERVICE_NAME;
 serviceActive = false;

 // Set log defaults
 logSource = SERVICE_DEFAULT_LOG_SOURCE;
 logTarget = SERVICE_DEFAULT_LOG_TARGET;
}

systemService::~systemService()
{ serviceActive = false; }



void systemService::readConfiguration( int argc, char * argv[] )
{
 if( argc > 1 )
   {
	 string filename( argv[1] );

	 configurationFileParser parser;
	 parser.import( filename, configurationName );
  }
}


void systemService::initLog( void )
{
 static char 	warnMsg[ INIT_ERROR_MSG_SIZE + 1 ];
 unsigned int	step = 0;
 Log & 			log  = Log::getLog();

 try {
	  // Get log source from my configuration
	  // conf = ConfigurationProvider::getProvider.getConfiguration( configurationName );
	  configuration		* p_conf = nullptr;
	  configurationItem * p_item = nullptr;

	  if( ConfigurationProvider::getProvider().getConfiguration( configurationName, & p_conf ) )
	    {
		  step++;
		  // If there is source name provided, use it
		  if( p_conf->getContainer( SERVICE_CONTAINER_LOG ).getItem( SERVICE_LOG_SOURCE, & p_item ) )
		    {
			  step++;
			  logSource = p_item->getString().c_str();
		    }

		  // If there is target name provided, use it
		  step++;
		  if( p_conf->getContainer( SERVICE_CONTAINER_LOG ).getItem( SERVICE_LOG_TARGET, & p_item ) )
		    {
			  step++;
			  logTarget = p_item->getString().c_str();
		    }

		  step++;
	    }
    }

  // If not possible to open log, continue anyway
  catch( const exception & e )
       {
	  	 snprintf( warnMsg, INIT_ERROR_MSG_SIZE, "%d - Some configuration parameters not found: %s.", step, e.what() );
	  	 warnMsg[ INIT_ERROR_MSG_SIZE ] = '\0';	// Ensure that it is correctly terminated
       }

  try  {
  	     log.open( logSource, logTarget, (const char**) SERVICE_DEFAULT_LOG_OPTIONS );

  	     if( step != 0 ) log.warn( warnMsg );

  	     // Add log parameters in Debug level
  	     string dbgMsg = "Source:";
  	     dbgMsg += logSource;
  	     log.debug( dbgMsg );
  	     dbgMsg = "Target:";
  	     dbgMsg += logTarget;
  	     log.debug( dbgMsg );

  	     //dbgMsg = ":" + logTarget;
  	     //log.debug( dbgMsg );
       }

  // If not possible to open log, continue anyway
  catch( const exception & e )
       {
	  	 cerr << "Error opening log file:" << e.what() << endl;
       }

}


void systemService::dumpIdentification( void )
{

}

void systemService::confirmRunConditions( void )
{

}

void systemService::boot( void )
{
  Log & log 		= Log::getLog();

  initLog();
/*
  dumpIdentification();			// Logs all relevant Service information to the system log

  confirmRunConditions();		// Ensures that the system meets the runtime pre-conditions

  secureEnvironment();			// Sets a secure runtime environment
*/
  plug();

  log.info( MESSAGE_BOOT );
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


void systemService::plug()
{
  Log & log = Log::getLog();

  log.debug( "Start plugging into the OS service manager." );

  // Set handler for process signals
  service::registerCallback();

  // Setup as a system service
  service::create();

  log.debug( "End plugging into the OS service manager." );
}

void systemService::unplug()
{
 Log & log = Log::getLog();

 log.debug( "Start unplugging from the OS service manager." );

 service::unregisterCallback();

 log.debug( "End unplugging from the OS service manager." );
}

void systemService::startManager()
{
 Log & log = Log::getLog();

 log.info( MESSAGE_STARTMGR );

 createServiceManager();
 serviceMutex.lock();						// If Service Manager was started, lock myself
}

void systemService::hibernate()
{
 Log & log = Log::getLog();

 serviceActive = true;
 while( serviceActive )
      {
	 	log.info( MESSAGE_PAUSE );
	    waitForWork();
      }
}

void systemService::shutdown()
{
 Log & log = Log::getLog();

 unplug();

 //serviceMutex.unlock();					// Remove lock before shutting down

 log.info( MESSAGE_SHUTDOWN );

 log.close();
}
