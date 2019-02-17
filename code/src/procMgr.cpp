// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Cross platform implementation for child process management functionality
//
// *****************************************************************************************


// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <iostream>
#include <memory>
#include <vector>

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
// Section: Public Function definition
//
// *****************************************************************************************

procMgr::procMgr()
{
 iState.init( procState::unconfigured, procState::stopped );
}


void procMgr::setState( procState newState )
{
 string	msg;
 Log &	log = Log::getLog();

 iState.set( newState );

 msg = "Changing Application state to ";
 msg += getStateString();

 log.info( msg );
}

bool procMgr::inState( procState state )
{
 return iState.inState( state );
}


void procMgr::configure( string & config )
{
 configureCallback();
 configureApplication( config );
}

void procMgr::unconfigure( void )
{
 unconfigureCallback();
 iState.reset();
}

void procMgr::start( void )
{
 Log & log = Log::getLog();

 log.info( "Entering start up of application" );

 if( ! ( iState.inState( procState::configured ) || iState.inState( procState::stopped ) ) )
	 log.error( "Unable to start managed application" );
 else
   {
	 setState( procState::starting );

	 process::runner * p_proc = process::factory::make( proc );
	 if( p_proc == nullptr )
	   {
		 if( process::factory::isChild( proc ) )
			 log.info( "Managed application running" );
		 else
			 log.error( "An error occurred while starting managed application" );
	   }
	 else
	   {
		 // Keep reference to child
	     app = unique_ptr<osapi::process::runner>( p_proc );
	     iState.set( procState::started );
	     string msg = "Application started:";
	     msg += proc.getName();
	     log.info( msg );

	     setState( procState::started );
	   }
   }

 log.info( "Leaving start up of application" );
}


void procMgr::stop( void )
{
 Log & log = Log::getLog();

 log.info( "Entering stop of the managed application" );

 if( ! iState.inState( procState::stopping ) )
	 log.info( "Unable to stop application" );
else
   {
	 string msg ="Stopping managed application:";
	 msg += proc.getName();
	 log.info( msg );
	 app.get()->terminate( (size_t) 5000 );
   }

 log.info( "Leaving stop of the managed application" );
}


void procMgr::processWork( void )
{
 Log & log = Log::getLog();

 log.info( "Entering process work at the application manager" );

 // If service is stopping, stop also application if it is not already
 if( Service::getService().stopping() )
   {
	 if( iState.inState( procState::started ) ) stop();

   }
 else		// Service is running
   {
	 // Managed application should be also running
	 if( iState.inState( procState::stopped ) )
	   {
		 postMortem();
		 start();
	   }
   }

 log.info( "Leaving process work at the application manager" );
}


// *****************************************************************************************
//
// Section: Private Function definition
//
// *****************************************************************************************

void procMgr::dumpConfiguration()
{
 string							msg;
 vector<char *>					vec;
 std::vector<char*>::size_type	i;
 Log & 							log		= Log::getLog();
 ConfigurationProvider &		prov	= ConfigurationProvider::getProvider();

 log.info( "===============================" );
 log.info( "Dump of process information:" );
 log.info( "===============================" );

 // Dump app name
 msg = "Application Name:";
 msg += proc.getName();
 log.info( msg );

 // Dump app state
 msg = "Current state of application:";
 msg += getStateString();
 log.info( msg );

 log.info( "Command line:" );
 log.info( "------------" );
 vec = proc.getCommandLine();
 for( i = 0; i < vec.size(); i++ )
    {
	  msg = to_string( i );
	  msg += ":";
	  msg += vec[ i ];
	  log.info( msg );
    }
 log.info( "************" );

 log.info( "Environment:" );
 log.info( "-----------" );
 vec = proc.getEnvironment();
 for( i = 0; i < vec.size(); i++ )
	  log.info( vec[i] );
 log.info( "***********" );

 log.info( "===============================" );
}


void procMgr::configureApplication( string & config )
{
 string	errorMsg;
 Log & log 						= Log::getLog();
 configuration * p_config		= nullptr;
 ConfigurationProvider & prov	= ConfigurationProvider::getProvider();

 log.info( "Entering configuration of application" );

 if( ! prov.getConfiguration( config, &p_config ) )
   {
	 errorMsg = "Unable to find configuration: " + config;
	 log.error( errorMsg );
   }
 else
   {
	 configurationItem * p_item;

	 ciContainer & appContainer = p_config->getContainer( APP_CONTAINER_NAME );

	 if( ! appContainer.getItem( APP_USER, &p_item ) )
		 log.error( "Unable to find User Name. Using default User" );
	 else
	   {
		 const string & str = p_item->getString();
		 proc.addUser( str );
	   }

	 if( ! appContainer.getItem( APP_GROUP, &p_item ) )
		 log.error( "Unable to find group name. Using default Group." );
	 else
	   {
		 const string & str = p_item->getString();
		 proc.addGroup( str );
	   }


	 if( ! appContainer.getItem( APP_NAME, &p_item ) )
		 log.error( "Unable to find an application to launch." );
	 else
	   {
		 const string & str = p_item->getString();
		 proc.addName( str );
		 iState.set( procState::configured );		// latter on, moving to this state should be only if binary meets requirements (exists, is executable, etc.
	   }

	 ciContainer & cmdLineContainer = p_config->getContainer( APP_CONTAINER_CMDLINE );
	 vector<refConstStr> cmdLine = cmdLineContainer.getStringList();
	 proc.addCommandLine( cmdLine );

	 ciContainer & envContainer = p_config->getContainer( APP_CONTAINER_ENVIRONMENT );
	 vector<refConstStr> env = envContainer.getStringList();
	 proc.addEnvironment( env );

	 setState( procState::configured );

	 dumpConfiguration();
   }

	 log.info( "Leaving configuration of application" );
}


const char * procMgr::getStateString( void )
{
 const char * ptr;

 switch( iState.get() )
 	   {
 	 	 case 	procState::unconfigured:	ptr = "Unconfigured";	break;
 	 	 case 	procState::configured:		ptr = "Configured";		break;
 	 	 case 	procState::starting:		ptr = "Starting";		break;
 	 	 case 	procState::started:			ptr = "Started"; 		break;
 	 	 case 	procState::stopping:		ptr = "Stopping"; 		break;
 	 	 case 	procState::stopped:			ptr = "Stopped";	 	break;
 	 	 default:							ptr = "Unknown"; 		break;
 	   }

 return ptr;
}


void procMgr::postMortem( void )
{
 Log & log 						= Log::getLog();

 using state	= process::state;
 using info		= process::statusInfo;

 state appState = app.get()->getState();

 if( appState == state::terminated || appState == state::stopped )
   {
	 process::status st = app.get()->getStatus();

	 switch( st.getInfo() )
	 	   {
	 	 	 case 	info::unavailable:	log.error( "No application status available" );			break;
	 	 	 case 	info::available:	log.info( "Application exited normally (by itself)" );	break;
	 	 	 case 	info::signal:		log.warn( "Application exited due to a signal" );		break;
	 	 	 case 	info::core:			log.error( "Application core dumped" );					break;
	 	 	 case 	info::stopped:		log.warn( "Application was stopped" );					break;
	 	 	 case 	info::continued:	log.info( "Application was resumed" );					break;

			 // Other cases from other platforms
			 // ...
	 	 	 default:					log.error( "Unknown process status" );					break;
	 	   }
   }
}
