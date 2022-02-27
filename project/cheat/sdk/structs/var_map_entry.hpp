#ifndef SKELETONS_CX_VAR_MAP_ENTRY_HPP
#define SKELETONS_CX_VAR_MAP_ENTRY_HPP

namespace sdk
{
	struct var_map_entry {
	public:
		unsigned short type;

		bool needs_to_interpolate;

		void* data;
		void* watcher;
	};
} // namespace sdk

#endif // SKELETONS_CX_VAR_MAP_ENTRY_HPP
