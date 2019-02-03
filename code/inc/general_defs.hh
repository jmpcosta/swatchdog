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

constexpr const char * SERVICE_NAME	 	= "swatchdog";
constexpr const char * SERVICE_VERSION 	= "0.1";

constexpr const char * MESSAGE_BOOT	 	= "Booting up Service";
constexpr const char * MESSAGE_PAUSE	= "Pausing service until new work arrives";
constexpr const char * MESSAGE_SHUTDOWN	= "Shutting down Service";
constexpr const char * MESSAGE_STARTMGR	= "Starting HASI Service Manager";
constexpr const char * MESSAGE_ENDTMGR	= "Started HASI Service Manager";
constexpr const char * MESSAGE_APPOK	= "Successfully started managed application";
constexpr const char * MESSAGE_APPNOK	= "Failed to start managed application";

// Configuration related definitions
// - First containers
constexpr const char * SERVICE_CONTAINER 				= "service";
constexpr const char * SERVICE_CONTAINER_LOG 			= "log.options";
constexpr const char * SERVICE_CONTAINER_LOG_OPTIONS 	= "log.options";
// - Next Configuration Items
constexpr const char * SERVICE_LOG_SOURCE 				= "source";
constexpr const char * SERVICE_LOG_TARGET 				= "target";

// - App related definitions
constexpr const char * APP_CONTAINER_NAME				= "app";
constexpr const char * APP_NAME							= "name";
constexpr const char * APP_USER							= "user";
constexpr const char * APP_GROUP						= "group";
constexpr const char * APP_CONTAINER_CMDLINE			= "app.arg";
constexpr const char * APP_CONTAINER_ENVIRONMENT		= "app.env";

// Define some size constants
constexpr int INIT_ERROR_MSG_SIZE = 200;


#endif /* SWATCHDOG_DEFS_HH_ */
