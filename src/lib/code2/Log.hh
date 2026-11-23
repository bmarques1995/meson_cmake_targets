#pragma once

#include "Exporter.hh"

namespace MesonExport
{
    class MESON_LOG_API Log
    {
    public:
        static void Message(const char* msg);
        static void SampleSymbol();
    };
}