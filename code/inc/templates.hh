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


template <class T> void stateHolder<T>::init(T first, T last)
{
 iCurrent	= first;
 iFirst		= first;
 iLast		= last;
}

template <class T> void stateHolder<T>::reset( void )
{
 iCurrent = iFirst;
}

template <class T> void stateHolder<T>::set( T state )
{
 iCurrent = state;
}

template <class T> T& stateHolder<T>::get( void )
{
 return iCurrent;
}


template <class T> stateHolder<T>& stateHolder<T>::operator=(const T & state) {
  iCurrent = state;
  return *this;
}

template <class T> bool stateHolder<T>::inState( T state )
{
 if( iCurrent == state )
	 return true;
 else
	 return false;
}

#endif /* SWATCHDOG_TEMPLATES_HH_ */
