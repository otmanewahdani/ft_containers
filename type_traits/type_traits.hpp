/* this file implements the following:
	+ enable_if
	+ is_same
	+ is_output_iterator
	+ is_input_iterator
	+ integral_constant
	+ is_integral
	+ is_floating_point
*/

#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <iterator.hpp>
#include <iterator>
#include <limits>

namespace ft{

	// enable_if
	template < bool, class T = void >
	struct enable_if {};

	template< class T >
	struct enable_if<true, T>{
		
		typedef T type;

	};

	// is_same
	template < class T, class U >
	struct is_same{

		const static bool value = false;

	};

	template < class T>
	struct is_same<T,T>{

		const static bool value = true;

	};

	// is_input_iterator
	template < class InputIt >
	struct is_input_iterator{

		const static bool value = is_same<
			typename iterator_traits<InputIt>::iterator_category,
			std::input_iterator_tag>::value;

	};

	// is_output_iterator
	template < class OutputIt >
	struct is_output_iterator{

		const static bool value = is_same<
			typename iterator_traits<OutputIt>::iterator_category,
			std::output_iterator_tag>::value;

	};

	// integral_constant
	template< class T, T v >
	struct integral_constant{

		//member types
		typedef T value_type;
		typedef integral_constant type;

		// member constants
		const static T value = v;

		// member functions
		operator value_type() const { return value; }
		value_type operator()() const { return value; }

	};

	// is_integral
	template < class T >
	struct is_integral : integral_constant<
		bool,
		std::numeric_limits<T>::is_integer
	> {};

	// is_floating_point
	template < class T >
	struct is_floating_point : integral_constant<
		bool,
		std::numeric_limits<T>::is_iec559
	> {};

}

#endif
