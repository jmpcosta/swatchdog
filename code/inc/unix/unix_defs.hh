// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide Unix specific settings for the System Service
//			It programmatically allows the configuration of UNIX mechanisms
//
// *****************************************************************************************

#ifndef SWATCHDOG_UNIX_UNIX_DEFS_HH_
#define SWATCHDOG_UNIX_UNIX_DEFS_HH_


// *****************************************************************************************
//
// Section: Constants
//
// *****************************************************************************************

// Default settings for logging
constexpr const char         SERVICE_DEFAULT_LOG_SOURCE[]  = "HASIS";
constexpr const char         SERVICE_DEFAULT_LOG_TARGET[]  = "LOCAL0";
constexpr const char * const SERVICE_DEFAULT_LOG_OPTIONS[] = { "LOG_CONS", "LOG_PID", nullptr };


#endif /* SWATCHDOG_UNIX_UNIX_DEFS_HH_ */
