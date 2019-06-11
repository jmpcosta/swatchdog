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
#include <defs.hh>
#include <filesystem>
#include <iostream>
#include <string>

// Import OSAPI+ headers
#include "osapi.hh"

// Import project headers
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

 iState.set( serviceState::unconfigured );

 // Set log defaults
 logSource = SERVICE_DEFAULT_LOG_SOURCE;
 logTarget = SERVICE_DEFAULT_LOG_TARGET;
}


// The next two functions are wrapper functions to set/verify service state

void Service::setState( serviceState newState )
{
 string	msg;
 Log &	log = Log::getLog();

 iState.set( newState );

 msg = "Changing Service state to ";
 msg += getStateString();

 log.info( msg );
}

bool Service::inState( serviceState state )
{
 return iState.inState( state );
}



void Service::boot( int argc, char * argv[] )
{
  Log & log 		= Log::getLog();

  initDefaultLog();

  readConfiguration( argc, argv );

  dumpIdentification();			// Logs all relevant Service information to the default system log

  if( configured() )
    {
	  initLog();
  	  // confirmRunConditions();		// Ensures that the system meets the runtime pre-conditions
  	  // secureEnvironment();			// Sets a secure runtime environment
	  createSystem();				// Create the System service
  	  plug();						// Plug myself to the OS callback mechanisms
    }

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

 while( inService() )
      {
	 	log.info( MESSAGE_PAUSE );
	    waitForWork();
      }
}

void Service::shutdown()
{
 Log & log = Log::getLog();

 unplug();	// from the OS

 // Stop the managed process
 manager.stop();

 log.info( MESSAGE_SHUTDOWN );

 log.close();
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


void Service::initDefaultLog( void )
{
 Log & 			log  = Log::getLog();

  try  {
  	     log.open( SERVICE_DEFAULT_LOG_SOURCE, SERVICE_DEFAULT_LOG_TARGET, (const char**) SERVICE_DEFAULT_LOG_OPTIONS );
       }

  // If not possible to open log, continue anyway
  catch( const exception & e )
       { }

}


void Service::readConfiguration( int argc, char * argv[] )
{
 Log & 			log  = Log::getLog();
 string 		filename, logMsg;

 if( argc < 2 )
	 filename = SERVICE_DEFAULT_CONFIGFILE_NAME;
 else
	 filename = argv[1];

 if( ! filesystem::element::exists( filename ) )
   {
	 logMsg = "Service Configuration file doesn't exist: " + filename;
	 log.error( logMsg );
	 return;
   }

 logMsg = "Service Configuration file (" + filename + ") found. Importing configuration.";
 log.info( logMsg );

 try {
	 	 configuration::fileParser parser;
	 	 parser.import( filename, configurationName );
 	 }
 catch( const exception & e )
 	 {
	 	log.error( e.what() );
	 	return;
 	 }

 // If reached this far, change service state
 setState( serviceState::configured );
}




void Service::initLog( void )
{
 static char 	warnMsg[ INIT_ERROR_MSG_SIZE + 1 ];
 unsigned int	step = 0;
 Log & 			log  = Log::getLog();
 string			logMsg;

 try {
	  // Get log source from my configuration
	  // conf = ConfigurationProvider::getProvider.getConfiguration( configurationName );
	  configuration::configuration		* p_conf = nullptr;
	  configuration::item 				* p_item = nullptr;

	  if( configuration::Provider::getProvider().getConfiguration( configurationName, & p_conf ) )
	    {
		  step++;
		  // If there is a source name that was provided, use it
		  if( p_conf->getContainer( SERVICE_CONTAINER_LOG ).getItem( SERVICE_LOG_SOURCE, & p_item ) )
		    {
			  step++;
			  logSource = p_item->getString().c_str();
		    }

		  // If there is a target name that was provided, use it
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
	  	 // First close the default logger
	  	 log.close();
	  	 // Attempt to use the new log settings
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
	  	  if( ! Log::isLogAvailable() )	// New log settings failed to open log, use default settings
	  		  initDefaultLog();

	  	  if( ! Log::isLogAvailable() )
	  		  return;
	  	  else							// If we have now a logger, log the error that occurred using the configured settings
	  	    {
	  		  logMsg += "Error opening log file:";
	  		  logMsg += e.what();
	  		  log.error ( logMsg );
	  	    }
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

 if( inService() )		// Process resumes when OS awakes it
	 processWork();

 log.debug( "Leaving wait for work." );
}


void Service::processWork( void )
{
 Log & log = Log::getLog();

 log.debug( "Entering process work." );

 // Delegate to application manager any work received
 manager.processWork();

 log.debug( "Leaving process work." );
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



const char * Service::getStateString()
{
 const char * ptr;

 switch( iState.get() )
 	   {
 	 	 case 	serviceState::unconfigured:	ptr = "Unconfigured";	break;
 	 	 case 	serviceState::configured:	ptr = "Configured";		break;
 	 	 case 	serviceState::configuring:	ptr = "Configuring";	break;
 	 	 case 	serviceState::inService:	ptr = "inService"; 		break;
 	 	 case 	serviceState::stopping:		ptr = "Stopping"; 		break;
 	 	 case 	serviceState::stopped:		ptr = "Stopped";	 	break;
 	 	 default:							ptr = "Unknown"; 		break;
 	   }

 return ptr;
}

