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
#include <general_defs.hh>
#include <memory>

// Import OSAPI headers
#include "osapi.hh"

// Import project headers
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
// Section: Function definition
//
// *****************************************************************************************

procMgr::procMgr()
{ isChildAlive = false; }

void procMgr::setChildAlive( bool newState )
{ isChildAlive = newState; }


bool procMgr::getChildAlive( void ) const
{
 return isChildAlive;
}


void procMgr::configureApplication( string & config )
{
 Log & log 						= Log::getLog();
 configuration * p_config		= nullptr;
 ConfigurationProvider & prov	= ConfigurationProvider::getProvider();

 log.info( "Entering configuration of application" );

 if( prov.getConfiguration( config, &p_config ) )
   {
	 configurationItem * p_item;

	 ciContainer & appContainer = p_config->getContainer( APP_CONTAINER_NAME );

	 if( appContainer.getItem( APP_NAME, &p_item ) )
	   {
		 const string & str = p_item->getString();
		 proc.addName( str );
	   }

	 if( appContainer.getItem( APP_USER, &p_item ) )
	   {
		 const string & str = p_item->getString();
		 proc.addUser( str );
	   }


	 if( appContainer.getItem( APP_GROUP, &p_item ) )
	   {
		 const string & str = p_item->getString();
		 proc.addGroup( str );
	   }

	 ciContainer & cmdLineContainer = p_config->getContainer( APP_CONTAINER_CMDLINE );
	 vector<string> cmdLine = cmdLineContainer.getStringList();

	 proc.addCommandLine( cmdLine );

	 ciContainer & envContainer = p_config->getContainer( APP_CONTAINER_ENVIRONMENT );
	 vector<string> env = envContainer.getStringList();

	 proc.addCommandLine( env );
   }

	 log.info( "Leaving configuration of application" );
}


void procMgr::configure( string & config )
{
 configureCallback();
 configureApplication( config );
}

void procMgr::unconfigure( void )
{
 unconfigureCallback();
}

void procMgr::start( void )
{
 Log & log = Log::getLog();

 log.info( "Entering start up of application" );

 //app = make_unique<process::runner *>( process::factory::make( proc ) );

 log.info( "Leaving start up of application" );
}



