// **********************************************************************************************
//
// File description:
//
// Author:		Joao Costa
// Purpose:		Implement Service Management OS specific related tasks.
// Description: The file implements the part of the systemService class that is OS more specific.
//				It uses the OSAPI libs but with a static parameterization, i.e. it knows in
//				advance which mechanism are present in the particular OS type, in this case Unix.
// **********************************************************************************************

#ifndef INC_SERVICE_UNIX_HH_
#define INC_SERVICE_UNIX_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// *****************************************************************************************
//
// Section: UNIX specific service class declaration
//
// *****************************************************************************************

class service
{
public:
		// Methods
		static	void	create();
		static	void	setState			( bool st	);
		static	bool	getState			( void    	);
		static  void	registerCallback	( void		);
		static  void	unregisterCallback	( void		);

private:
		// Class variables
		static bool		state;

		// No instances are to be created
						service				()	{}
						~service			()  {}
		static	void	signal_handler		( int signo );
};




#endif /* INC_SERVICE_UNIX_HH_ */
