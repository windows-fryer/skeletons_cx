#ifndef SKELETONS_CX_CLIENT_CLASS_HPP
#define SKELETONS_CX_CLIENT_CLASS_HPP

namespace sdk
{
	struct recv_table;

	struct client_class {
	public:
		void* m_p_create_fn;
		void* m_p_create_event_fn;
		const char* m_p_network_name;
		recv_table* m_p_recv_table;
		client_class* m_p_next;
		int m_class_id;
	};
} // namespace sdk

#endif // SKELETONS_CX_CLIENT_CLASS_HPP
