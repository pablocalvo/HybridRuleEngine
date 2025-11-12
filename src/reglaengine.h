#pragma once
#include <string>
#include "contexto.h"
#include "regla.h"

class ReglaEngine {
public:
    static Regla obtenerRegla(const Contexto& ctx, const std::string& pythonExec);
};
