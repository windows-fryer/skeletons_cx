#ifndef SKELETONS_CX_VFUNC_HPP
#define SKELETONS_CX_VFUNC_HPP
#include <cstdint>

namespace virtual_func
{

	struct impl {
	public:
		uintptr_t* get_virtual_table( void* instance );

		uintptr_t* get_virtual_function_index( void* instance, const std::uint32_t index );
	};
} // namespace virtual_func

inline virtual_func::impl g_vfunc;

#endif // SKELETONS_CX_VFUNC_HPP