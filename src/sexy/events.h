#pragma once

namespace sexy
{
    #define SEXY_EVENT(Event) \
        struct Event final { };

    namespace events
    {
        SEXY_EVENT(Initialize);
        SEXY_EVENT(Update);
        SEXY_EVENT(Uninitialize);
    }
}
