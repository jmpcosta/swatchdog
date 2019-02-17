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
#include "templates.hh"
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

enum class serviceState { unconfigured, configuring, configured, inService, stopping, stopped };

class Service
{
public:
	// Get singleton instance reference
	static	Service & 					getService();

	// Instance methods
			void 						boot( int argc, char * argv[] );
			void						startManager();
			void 						hibernate();
			void 						shutdown();

			void 						setState		( serviceState newState	);
			bool						inState			( serviceState state	);

			void						processWork		( void					);
			procMgr &					getManager		( void					);

			// Inline Utility functions to get service state
			bool						inService() 	{return iState.inState( serviceState::inService);}
			bool						configured()	{return iState.inState( serviceState::configured );}
			bool						stopping()		{return iState.inState( serviceState::stopping );}
			bool						stopped()		{return iState.inState( serviceState::stopped );}

	// delete copy and move constructors and assign operators
			Service( Service const& ) 				= delete;		// Copy construct
			Service( Service&& ) 					= delete;		// Move construct
			Service& operator=( Service const& )	= delete; 		// Copy assign
			Service& operator=( Service && )		= delete;		// Move assign

private:

	// Instance methods
			void						readConfiguration( int argc, char * argv[] );

										~Service() {}
										Service();
			void						initLog();
			void						initDefaultLog();

			void						waitForWork();
			void						secureEnvironment();
			void						plug();
			void						unplug();
			void						confirmRunConditions();
			void						dumpIdentification();
			void						createSystem();
			const char *				getStateString();

	// Instance Variables
			// Logging variables
			const char *				logSource;
			const char *				logTarget;
			unique_ptr<char *>  		logOptions;

			// Service variables
			stateHolder<serviceState>	iState;
			string						configurationName;

			// Manager of application
			procMgr						manager;
};



#endif /* SWATCHDOG_SERVICE_HH_ */
