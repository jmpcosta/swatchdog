// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide service wide definitions
//
// *****************************************************************************************


#ifndef SWATCHDOG_DEFS_HH_
#define SWATCHDOG_DEFS_HH_


// *****************************************************************************************
//
// Section: Constants
//
// *****************************************************************************************

/// @brief Name of the system service
constexpr const char * SERVICE_NAME	 	= "SWatchDog";

/// @brief Version of the system service
constexpr const char * SERVICE_VERSION 	= "0.3";

/// @brief Message for service boot
constexpr const char * MESSAGE_BOOT	 	= "Booting up Service";

/// @brief Message for service hibernation
constexpr const char * MESSAGE_PAUSE	= "Pausing service until new work arrives";

/// @brief Message for service down
constexpr const char * MESSAGE_SHUTDOWN	= "Shutting down Service";

/// @brief Message for service starting
constexpr const char * MESSAGE_STARTMGR	= "Starting Service Manager";

/// @brief Message for service started
constexpr const char * MESSAGE_ENDTMGR	= "Started Service Manager";

/// @brief Message for application start
constexpr const char * MESSAGE_APPOK	= "Successfully started managed application";

/// @brief Message for failing to start the managed application
constexpr const char * MESSAGE_APPNOK	= "Failed to start managed application";

// *********************************
// Configuration related definitions
// *********************************

// - First configuration file name

/// @brief Default system service configuration file
constexpr const char * SERVICE_DEFAULT_CONFIGFILE_NAME	= "swatchdog.properties";

// - Next, containers

/// @brief Name of service own related configuration settings
constexpr const char * SERVICE_CONTAINER 				= "service";

/// @brief Name of configuration container for log options
constexpr const char * SERVICE_CONTAINER_LOG 			= "service.log";

/// @brief Name of configuration container for log options
constexpr const char * SERVICE_CONTAINER_LOG_OPTIONS 	= "service.log.options";

// - Next Configuration Items

/// @brief Name of log source property
constexpr const char * SERVICE_LOG_SOURCE 				= "source";

/// @brief Name of log target property
constexpr const char * SERVICE_LOG_TARGET 				= "target";

// - App related definitions

/// @brief Name of application container
constexpr const char * APP_CONTAINER_NAME				= "app";

/// @brief Name of application property (which defines the name of the application)
constexpr const char * APP_NAME							= "name";

/// @brief Name of application property (which defines the user that will run the application)
constexpr const char * APP_USER							= "user";

/// @brief Name of application property (which defines the group that will run the application)
constexpr const char * APP_GROUP						= "group";

/// @brief Name of application container (command line arguments)
constexpr const char * APP_CONTAINER_CMDLINE			= "app.arg";

/// @brief Name of application container (environment list)
constexpr const char * APP_CONTAINER_ENVIRONMENT		= "app.env";

// Define some size constants
/// @brief Size of error message for initial logging
constexpr int INIT_ERROR_MSG_SIZE = 200;


#endif /* SWATCHDOG_DEFS_HH_ */
