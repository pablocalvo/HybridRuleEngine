#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>

class Logger {
public:
    static Logger& instance() {
        static Logger inst;
        return inst;
    }

    void log(const std::string& contexto, const std::string& mensaje) {
        std::scoped_lock lock(m_mutex);
        std::ofstream out("logs/engine.log", std::ios::app);
        if (!out.is_open()) return;

        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        out << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] "
            << "[" << contexto << "] " << mensaje << "\n";
    }

private:
    Logger() { std::ofstream("logs/engine.log").close(); }
    std::mutex m_mutex;
};
