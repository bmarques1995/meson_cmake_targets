#pragma once

#include "Exporter.hh"

namespace MesonExport
{
    class MESON_LIB_API Math
    {
    public:
        static void Add(double a, double b, double* out);
        static void Multiply(double a, double b, double* out);
    };
}