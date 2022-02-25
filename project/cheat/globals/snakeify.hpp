//
// Created by Liga on 2/23/2022.
//

#ifndef SKELETONS_CX_SNAKEIFY_HPP
#define SKELETONS_CX_SNAKEIFY_HPP

#include "../../dependencies/fnv/fnv.hpp"

#define dll_main                         DllMain
#define win_api                          WINAPI
#define create_thread( function )        CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )function, 0, 0, 0 )
#define fnv( string )                    fnv::hash( string )
#define get_proc_address( module, name ) GetProcAddress( module, name )
#define get_module_handle( name )        GetModuleHandle( name )

#endif // SKELETONS_CX_SNAKEIFY_HPP
