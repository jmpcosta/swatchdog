// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	System Service API declaration
//
// *****************************************************************************************

#ifndef SWATCHDOG_SERVICE_HH_
#define SWATCHDOG_SERVICE_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>
#include <mutex>
#include <memory>

// Import project headers
#include "procMgr.hh"

// *****************************************************************************************
//
// Section: Import namespaces
//
// *****************************************************************************************

using namespace std;


// *****************************************************************************************
//
// Section: Class declaration/definition
//
// *****************************************************************************************


class Service
{
public:
	// Get singleton instance reference
	static	Service & 	getService();

	// Instance methods
			void				readConfiguration( int argc, char * argv[] );
			void 				boot();
			void				startManager();
			void 				hibernate();
			void 				shutdown();
			void				setActive( bool newState );
			procMgr &			getManager( void );

	// delete copy and move constructors and assign operators
			Service( Service const& ) 				= delete;		// Copy construct
			Service( Service&& ) 					= delete;		// Move construct
			Service& operator=( Service const& )	= delete; 		// Copy assign
			Service& operator=( Service && )		= delete;		// Move assign

private:

	// Instance methods
								~Service();
								Service();
			void				initLog();
			void				waitForWork();
			void				secureEnvironment();
			void				plug();
			void				unplug();
			void				confirmRunConditions();
			void				dumpIdentification();
			void				createSystem();

	// Instance Variables
			// Logging variables
			const char *		logSource;
			const char *		logTarget;
			unique_ptr<char *>  logOptions;

			// Service variables
			bool				serviceActive;
			string				configurationName;

			// Manager of application
			procMgr				manager;

			// Synchronizer of this service
			mutex				serviceMutex;
};



#endif /* SWATCHDOG_SERVICE_HH_ */
