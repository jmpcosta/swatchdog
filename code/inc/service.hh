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

// Import OSAPI headers
#include "osapi.hh"

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

// Standard C++ library
using namespace std;

// OSAPI Plus namespace
using namespace osapi;

// *****************************************************************************************
//
// Section: Class declaration/definition
//
// *****************************************************************************************

/// @brief The possible service states
enum class serviceState
{
	unconfigured,	///< Service is not yet configured
	configuring,	///< Service in the process of being configured
	configured,		///< Service is already configured
	inService,		///< Service active
	stopping,		///< Service is going down
	stopped			///< Service terminated
};


/// @brief Class that models a system service
class Service
{
public:

			/// @brief Get singleton instance reference
			/// @returns The service instance
	static	Service & 					getService();

	// Instance methods
			/// @brief Bootstrap the service
			/// @param [in] argc - The number of the service command line arguments
 			/// @param [in] argv - The command line arguments
			void 						boot( int argc, char * argv[] );

			/// @brief Start the manager of the application
			void						startManager();

			/// @brief Put the service on hold until an event arrives
			void 						hibernate();

			/// @brief Shuts the service down
			void 						shutdown();

			/// @brief Changes the service state
			/// @param [in] newState - Changes the service state to a new one
			void 						setState		( serviceState newState	);

			/// @brief Check the if a state of a service is the given one
			/// @param [in] state - The service state to query
			/// @return True if service state matches the current service state. False otherwise
			bool						inState			( serviceState state	);

			/// @brief Process any awake event received by the OS
			void						processWork		( void					);

			/// @brief Obtain the reference to the Application Manager
			/// @return The manager's reference
			procMgr &					getManager		( void					);

			// Inline Utility functions to get service state
			/// @brief Check if the service state is inService
			/// @return True if inService. False otherwise
			bool						inService() 	{return iState.inState( serviceState::inService);}

			/// @brief Check if the service state is configured
			/// @return True if configured. False otherwise
			bool						configured()	{return iState.inState( serviceState::configured );}

			/// @brief Check if the service state is stopping
			/// @return True if stopping. False otherwise
			bool						stopping()		{return iState.inState( serviceState::stopping );}

			/// @brief Check if the service state is stopped
			/// @return True if stopped. False otherwise
			bool						stopped()		{return iState.inState( serviceState::stopped );}

	// delete copy and move constructors and assign operators
			Service( Service const& ) 				= delete;		// Copy construct
			Service( Service&& ) 					= delete;		// Move construct
			Service& operator=( Service const& )	= delete; 		// Copy assign
			Service& operator=( Service && )		= delete;		// Move assign

private:

	// Instance methods
			/// @brief Read the swatchdog configuration file
			/// @param [in] argc - The number of the service command line arguments
 			/// @param [in] argv - The command line arguments
			void						readConfiguration( int argc, char * argv[] );

			/// @brief Class destructor
										~Service() {}

			/// @brief Class constructor
										Service();

			/// @brief Initialize the service logging
			void						initLog();

			/// @brief Initialize the default service logging
			///
			/// Before the service can use the configuration information to set the correct system log, it must be possible
			/// to logs the initial service configuration events using the hardcoded platform configuration log settings
			void						initDefaultLog();

			/// @brief Wait for new OS events/work
			void						waitForWork();

			/// @brief Setup a secure environment for the service to run
			void						secureEnvironment();

			/// @brief Plug into the OS service to listen for work events
			void						plug();

			/// @brief Detach from the OS and stop receiving system events/work
			void						unplug();

			/// @brief Check that the service has all conditions to work
			void						confirmRunConditions();

			/// @brief Dumps the service information to the system log facility
			void						dumpIdentification();

			/// @brief Create the system service as defined by the runtime platform (e.g. Daemon in UNIX)
			void						createSystem();

			/// @brief Get the corresponding string for the given service state
			/// @return Service state string
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
