#include "entry.hpp"

#include <iostream>
#include <windows.h>

#include "cheat/helpers/cheat.hpp"

void entry::impl::init()
{
    std::cout << "Initializing entry\n";

    g_cheat.init();
}

void entry::impl::shutdown()
{
    std::cout << "Shutting down entry\n";
}

