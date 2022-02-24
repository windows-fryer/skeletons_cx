//
// Created by Liga on 2/23/2022.
//

#ifndef WEDNESDAY_TF2_CHEAT_HPP
#define WEDNESDAY_TF2_CHEAT_HPP

#include <iostream>
#include <windows.h>

#include "../globals/globals.hpp"

namespace cheat
{
    struct impl
    {
    public:
        static void init();
        static void shutdown();
    };
}

inline cheat::impl g_cheat;

#endif //WEDNESDAY_TF2_CHEAT_HPP
