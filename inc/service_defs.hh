// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide service wide definitions
//
// *****************************************************************************************


#ifndef SERVICE_DEFS_HH_
#define SERVICE_DEFS_HH_


// *****************************************************************************************
//
// Section: Constants
//
// *****************************************************************************************

constexpr const char * SERVICE_NAME	 	= "swatchdog";
constexpr const char * MESSAGE_BOOT	 	= "Booting up Service";
constexpr const char * MESSAGE_PAUSE	= "Pausing service until new work arrives";
constexpr const char * MESSAGE_SHUTDOWN	= "Shutting down Service";
constexpr const char * MESSAGE_STARTMGR	= "Starting HASI Service Manager";

// Configuration related definitions
// - First containers
constexpr const char * SERVICE_CONTAINER 				= "service";
constexpr const char * SERVICE_CONTAINER_LOG 			= "log.options";
constexpr const char * SERVICE_CONTAINER_LOG_OPTIONS 	= "log.options";
// - Next Configuration Items
constexpr const char * SERVICE_LOG_SOURCE 				= "source";
constexpr const char * SERVICE_LOG_TARGET 				= "target";


// Define some size constants
constexpr int INIT_ERROR_MSG_SIZE = 200;


#endif /* SERVICE_DEFS_HH_ */
