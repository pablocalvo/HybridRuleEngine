#pragma once
#include <string>
#include <utility>

class Regla {
public:
    Regla() = default;
    Regla(std::string nombre, std::string descripcion)
        : m_nombre(std::move(nombre)), m_descripcion(std::move(descripcion)) {}

    Regla(const Regla&) = default;
    Regla(Regla&& other) noexcept
        : m_nombre(std::move(other.m_nombre)),
          m_descripcion(std::move(other.m_descripcion)) {}

    Regla& operator=(const Regla&) = default;
    Regla& operator=(Regla&& other) noexcept {
        if (this != &other) {
            m_nombre = std::move(other.m_nombre);
            m_descripcion = std::move(other.m_descripcion);
        }
        return *this;
    }

    const std::string& nombre() const noexcept { return m_nombre; }
    const std::string& descripcion() const noexcept { return m_descripcion; }

private:
    std::string m_nombre;
    std::string m_descripcion;
};
