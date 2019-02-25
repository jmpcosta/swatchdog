// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Provide Unix specific settings for the System Service
//			It programmatically allows the configuration of UNIX mechanisms
//
// *****************************************************************************************

#ifndef SWATCHDOG_UNIX_DEFS_HH_
#define SWATCHDOG_UNIX_DEFS_HH_


// *****************************************************************************************
//
// Section: Constants
//
// *****************************************************************************************

/// @brief Default log name of the application
constexpr const char         SERVICE_DEFAULT_LOG_SOURCE[]  = "SWATCHDOG";
/// @brief Default syslog facility
constexpr const char         SERVICE_DEFAULT_LOG_TARGET[]  = "LOCAL0";
/// @brief Default UNIX syslog options
constexpr const char * const SERVICE_DEFAULT_LOG_OPTIONS[] = { "LOG_CONS", "LOG_PID", nullptr };


#endif /* SWATCHDOG_UNIX_DEFS_HH_ */
