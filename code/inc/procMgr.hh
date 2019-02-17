// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Declarations for the Process Manager which is responsible
//			for the control of the life cycle of an application
//
// *****************************************************************************************

#ifndef SWATCHDOG_PROCMGR_HH_
#define SWATCHDOG_PROCMGR_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <string>
#include <memory>

// Import OSAPI header
#include "osapi.hh"

// Import project headers
#include "templates.hh"

// *****************************************************************************************
//
// Section: Import namespaces
//
// *****************************************************************************************

using namespace std;
using namespace osapi;

using runner_ptr = std::unique_ptr<osapi::process::runner>;

// *****************************************************************************************
//
// Section: Class declaration/definition
//
// *****************************************************************************************

enum class procState { unconfigured, configured, starting, started, stopping, stopped };

class procMgr
{
public:
		// Constructor & Destructor
						procMgr	();
						~procMgr() 	{}

		// Set configuration information
		void 			configure				( string & config		);
		void 			unconfigure				( void					);

		void 			start					( void					);
		void 			stop					( void 					);
		void 			processWork				( void 					);

		// Set Child state
		void 			setState				( procState newState	);
		bool			inState					( procState state		);

		// Class methods
		void			postMortem				( void					);

private:
		// Methods
		void 			configureCallback		( void					);
		void 			unconfigureCallback		( void					);
		void 			configureApplication	( string & config		);
		void 			dumpConfiguration		( void					);
		const char *	getStateString			( void 					);

		// Variables
		stateHolder<procState>	iState;
		process::plan 			proc;
		runner_ptr				app;
};



#endif /* SWATCHDOG_PROCMGR_HH_ */
