//
// Created by Liga on 2/23/2022.
//

#ifndef SKELETONS_CX_SNAKEIFY_HPP
#define SKELETONS_CX_SNAKEIFY_HPP

#define dll_main                  DllMain
#define win_api                   WINAPI
#define create_thread( function ) CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )function, 0, 0, 0 )

#endif // SKELETONS_CX_SNAKEIFY_HPP
