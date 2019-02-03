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

// Import C++ Standard headers
#include <iostream>
#include <string>

// Import OSAPI+ headers
#include "osapi.hh"

// Import project headers
#include "general_defs.hh"
#include "platform_defs.hh"

// Import own header
#include "procMgr.hh"
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
Service & Service::getService()
{
 static Service instance;

 return instance;
}


Service::Service()
{
 configurationName	= SERVICE_NAME;
 serviceActive 		= false;

 // Set log defaults
 logSource = SERVICE_DEFAULT_LOG_SOURCE;
 logTarget = SERVICE_DEFAULT_LOG_TARGET;
}

Service::~Service()
{ serviceActive = false; }



void Service::readConfiguration( int argc, char * argv[] )
{
 if( argc > 1 )
   {
	 string filename( argv[1] );

	 configurationFileParser parser;
	 parser.import( filename, configurationName );
  }
}



void Service::boot( void )
{
  Log & log 		= Log::getLog();

  initLog();

  dumpIdentification();			// Logs all relevant Service information to the system log
/*
  confirmRunConditions();		// Ensures that the system meets the runtime pre-conditions

  secureEnvironment();			// Sets a secure runtime environment
*/

  createSystem();				// Create the System service
  plug();						// Plug myself to the OS callback mechanisms

  log.info( MESSAGE_BOOT );
}


void Service::startManager()
{
 Log & log 						= Log::getLog();

 log.info( MESSAGE_STARTMGR );

 try
 {
   manager.configure( configurationName );
   manager.start();
 }

 catch( exception const & e )
 {
   log.error( e.what() );
 }

 log.info( MESSAGE_ENDTMGR );
}

void Service::hibernate()
{
 Log & log = Log::getLog();

 serviceActive = true;
 while( serviceActive )
      {
	 	log.info( MESSAGE_PAUSE );
	    waitForWork();
      }
}

void Service::shutdown()
{
 Log & log = Log::getLog();

 unplug();

 serviceMutex.unlock();					// Remove lock before shutting down

 log.info( MESSAGE_SHUTDOWN );

 log.close();
}


void Service::setActive( bool newState )
{
 serviceActive = newState;
}


procMgr & Service::getManager( void )
{
 return manager;
}


// *****************************************************************************************
//
// Section: Implementation of private methods
//
// *****************************************************************************************



void Service::initLog( void )
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


void Service::dumpIdentification( void )
{
 string msg;
 Log & log			= Log::getLog();

 msg = SERVICE_NAME; msg += " version "; msg += SERVICE_VERSION; msg += ".";

 log.info( msg );
}

void Service::confirmRunConditions( void )
{

}



void Service::waitForWork( void )
{
 Log & log = Log::getLog();

 log.debug( "Entering wait for work." );

 process::Current::get().suspend();

 log.debug( "Leaving wait for work." );
}





void Service::secureEnvironment()
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
void Service::processNotification()
{

}
*/
