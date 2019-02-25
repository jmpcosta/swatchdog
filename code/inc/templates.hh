// *****************************************************************************************
//
// File description:
//
// Author:	Joao Costa
// Purpose:	Defines templates for the project
//
// *****************************************************************************************

#ifndef SWATCHDOG_TEMPLATES_HH_
#define SWATCHDOG_TEMPLATES_HH_

// *****************************************************************************************
//
// Section: Import headers
//
// *****************************************************************************************

// Import C++ system headers
#include <exception>

// *****************************************************************************************
//
// Section: Template to hold a sequential state
//
// *****************************************************************************************

/// @brief Template class to manage/hold a generic state
template <class T> class stateHolder
{
public:
			void	init	( T first, T last	);
			void	set		(  T state			);
			T&		get		( void				);
			void	reset	( 	void			);
			bool	inState	( T state			);

			stateHolder<T>& operator=( const T & state );
private:
			T		iFirst;
			T		iCurrent;
			T		iLast;
};

/// @brief Initialize the initial and last element states
/// @param [in] first - The first state in the set (and current state)
/// @param [in] last  - The last state in the set
template <class T> void stateHolder<T>::init(T first, T last)
{
 iCurrent	= first;
 iFirst		= first;
 iLast		= last;
}

/// @brief Reset current state to the initial state
template <class T> void stateHolder<T>::reset( void )
{
 iCurrent = iFirst;
}

/// @brief Set the current state to the new state
/// @param [in] state - The new state to hold
template <class T> void stateHolder<T>::set( T state )
{
 iCurrent = state;
}


/// @brief Get the current state
/// @return The current state
template <class T> T& stateHolder<T>::get( void )
{
 return iCurrent;
}

/// @brief Set the current state to the new state
/// @param [in] state - The new state to hold
/// @return The current stateHolder instance
template <class T> stateHolder<T>& stateHolder<T>::operator=(const T & state) {
  iCurrent = state;
  return *this;
}

/// @brief Query the stateHolder class to check the current state
/// @param [in] state - Is this the current state?
/// @return True if current state matches. False otherwise
template <class T> bool stateHolder<T>::inState( T state )
{
 if( iCurrent == state )
	 return true;
 else
	 return false;
}

#endif /* SWATCHDOG_TEMPLATES_HH_ */
