// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	The purpose of the application is to serve as a Super Watchdog process/service.
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <iostream>
#include <exception>

// Import service headers
#include "service.hh"

// *****************************************************************************************
//
// Section: Import namespaces
//
// *****************************************************************************************

// Import C++ Standard namespace
using namespace std;


// *****************************************************************************************
//
// Section: Function definition
//
// *****************************************************************************************

int main( int argc, char * argv[] )
{
 try
   {
	 // First, get own service instance
	 systemService	& service	= systemService::getService();

	 service.readConfiguration( argc, argv );		// Init own configuration

	 service.boot();								// Bootstrap myself

	 //service.startManager();						// Launch the HASI Service Manager

	 service.hibernate();							// Wait until the OS Service Manager asks for service to terminate

	 //service.shutdown();							// Perform a clean shutdown of self

   }

 catch( const exception & e )
   { std::cerr << "Terminating the service since: " << e.what() << endl; }

}
