#ifndef __MY_EXAMPLE_INTERFACE_IMPL_H__
#define __MY_EXAMPLE_INTERFACE_IMPL_H__

#include "example.hh"

class MyExampleInterface_impl : public POA_ExampleInterface
{
	public:
		virtual char * send_message(const char * message);
};

#endif // __MY_EXAMPLE_INTERFACE_IMPL_H__