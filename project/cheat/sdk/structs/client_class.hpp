#ifndef SKELETONS_CX_CLIENT_CLASS_HPP
#define SKELETONS_CX_CLIENT_CLASS_HPP

#include "dt_recv.hpp"

namespace sdk
{

	struct client_class {
	public:
		void* create_fn;
		void* create_event_fn;
		const char* network_name;
		recv_table* recv_table;
		client_class* next;
		int class_id;
	};
} // namespace sdk

#endif // SKELETONS_CX_CLIENT_CLASS_HPP
