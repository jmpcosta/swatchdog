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

/// @brief The state of the application
enum class procState
{
	unconfigured,	///< Application not yet configured
	configured,		///< Application is now configured
	starting,		///< Application is being started
	started,		///< Application is now running
	stopping,		///< Application is being stopped
	stopped			///< Application is now stopped
};

/// @brief Class that models the manager component (of the application)
class procMgr
{
public:
		/// @brief Constructor
						procMgr	();

		/// @brief Destructor
						~procMgr() 	{}

		/// @brief Configure the managed application
		/// @param [in] config - Name of configuration
		void 			configure				( string & config		);

		/// @brief Unconfigure the managed application
		void 			unconfigure				( void					);

		/// @brief Start application
		void 			start					( void					);

		/// @brief Stop application
		void 			stop					( void 					);

		/// @brief Process application related work
		void 			processWork				( void 					);

		// Set Child state
		/// @brief Change application state to a new one
		/// @param [in] newState - The new application state
		void 			setState				( procState newState	);

		/// @brief Query the application state
		/// @param [in] state - Is the application in this state
		/// @return True if in state. False otherwise
		bool			inState					( procState state		);

		/// @brief Upon application crash, log the causes
		void			postMortem				( void					);

private:
		// Methods
		/// @brief Configure the OS callback to be informed of the application state
		void 			configureCallback		( void					);

		/// @brief Unplug from the OS to stop receiving information for the application
		void 			unconfigureCallback		( void					);

		/// @brief Configured the application according with the configured file settings
		void 			configureApplication	( string & config		);

		/// @brief Log the application configuration
		void 			dumpConfiguration		( void					);

		/// @brief Get the string that corresponds to the application state
		const char *	getStateString			( void 					);

		// Variables
		stateHolder<procState>	iState;
		process::plan 			proc;
		runner_ptr				app;
};



#endif /* SWATCHDOG_PROCMGR_HH_ */
