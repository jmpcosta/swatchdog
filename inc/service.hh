// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	System Service API declaration
//
// *****************************************************************************************

#ifndef INC_SERVICE_HH_
#define INC_SERVICE_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>
#include <mutex>
#include <memory>

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


class systemService
{
public:

	static	systemService & 	getService();

	// Instance methods
			void				readConfiguration( int argc, char * argv[] );
			void 				boot();
			void				startManager();
			void 				hibernate();
			void 				shutdown();

	// delete copy and move constructors and assign operators
	systemService( systemService const& ) 				= delete;		// Copy construct
	systemService( systemService&& ) 					= delete;		// Move construct
	systemService& operator=( systemService const& )	= delete; 		// Copy assign
	systemService& operator=( systemService && )		= delete;		// Move assign

private:

	// Instance methods
								~systemService();
								systemService();
			void				initLog();
			void				waitForWork();
			void				secureEnvironment();
			void				plug();
			void				unplug();
			void				confirmRunConditions();
			void				dumpIdentification();
			void				createServiceManager();

	// Instance Variables
			const char *		logSource;
			const char *		logTarget;
			unique_ptr<char *>  logOptions;
			bool				serviceActive;
			string				configurationName;
			mutex				serviceMutex;

};



#endif /* INC_SERVICE_HH_ */
