#include "reglaengine.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <chrono>

Regla ReglaEngine::obtenerRegla(const Contexto& ctx, const std::string& pythonExec) {
    std::ostringstream payload;
    payload << "{"
            << "\"context\":\"" << ctx.nombre() << "\","
            << "\"features\":{\"coef_var\":" << ctx.coefVar()
            << ",\"trend\":" << ctx.tendencia()
            << ",\"units\":" << ctx.unidades()
            << "}}";

    std::string cmd = pythonExec + " python/rule_engine.py";
    FILE* pipe = popen(cmd.c_str(), "w");
    if (!pipe) throw std::runtime_error("No se pudo abrir el proceso Python.");
    fwrite(payload.str().c_str(), 1, payload.str().size(), pipe);
    pclose(pipe);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::ifstream result("data/result_" + ctx.nombre() + ".txt");
    std::string nombreRegla;
    getline(result, nombreRegla);
    return Regla(std::move(nombreRegla), "Obtenida automáticamente desde Python");
}
