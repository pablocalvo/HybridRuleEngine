#include <iostream>
#include <thread>
#include <vector>
#include "contexto.h"
#include "regla.h"
#include "reglaengine.h"
#include "logger.h"

void procesarContexto(Contexto ctx, const std::string& pythonExec) {
    Logger::instance().log(ctx.nombre(), "→ Enviando datos al motor Python");
    auto regla = ReglaEngine::obtenerRegla(ctx, pythonExec);
    Logger::instance().log(ctx.nombre(), "← Regla aplicada: " + regla.nombre());
    std::cout << "[" << ctx.nombre() << "] Regla aplicada: " << regla.nombre() << std::endl;
}

int main() {
#ifdef _WIN32
    std::string pythonExec = "python";
#else
    std::string pythonExec = "python3";
#endif

    std::vector<Contexto> contextos = {
        {"bebidas", 0.45,  1.2, 1000},
        {"lacteos", 0.22, -0.4, 600},
        {"limpieza", 0.90, 0.1, 300},
        {"snacks", 0.30, 0.8, 850}
    };

    std::vector<std::thread> hilos;
    for (auto& ctx : contextos) {
        hilos.emplace_back([ctx = std::move(ctx), &pythonExec]() {
            procesarContexto(std::move(ctx), pythonExec);
        });
    }

    for (auto& h : hilos) h.join();

    Logger::instance().log("SYSTEM", "✅ Procesamiento completo con move semantics y logging concurrente.");
    std::cout << "\n✅ Procesamiento completo con move semantics y logging concurrente.\n";
    return 0;
}
