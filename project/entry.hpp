#ifndef WEDNESDAY_TF2_ENTRY_HPP
#define WEDNESDAY_TF2_ENTRY_HPP

namespace entry
{
    struct impl
    {
    public:
        static void init();
        static void shutdown();
    };
}

inline entry::impl g_entry;

#endif //WEDNESDAY_TF2_ENTRY_HPP
