//
// Created by Liga on 2/23/2022.
//

#ifndef SEKELETONS_CX_SNAKEIFY_HPP
#define SEKELETONS_CX_SNAKEIFY_HPP

#define dll_main DllMain
#define win_api WINAPI
#define create_thread(function) CreateThread(0, 0, (LPTHREAD_START_ROUTINE)function, 0, 0, 0)

#endif //SEKELETONS_CX_SNAKEIFY_HPP
