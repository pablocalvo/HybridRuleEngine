#pragma once
#include <string>
#include <utility>

class Contexto {
public:
    Contexto(std::string nombre, double coefVar, double tendencia, double unidades)
        : m_nombre(std::move(nombre)), m_coefVar(coefVar),
          m_tendencia(tendencia), m_unidades(unidades) {}

    Contexto(const Contexto&) = default;
    Contexto(Contexto&& other) noexcept
        : m_nombre(std::move(other.m_nombre)),
          m_coefVar(other.m_coefVar),
          m_tendencia(other.m_tendencia),
          m_unidades(other.m_unidades) {}

    Contexto& operator=(const Contexto&) = default;
    Contexto& operator=(Contexto&& other) noexcept {
        if (this != &other) {
            m_nombre = std::move(other.m_nombre);
            m_coefVar = other.m_coefVar;
            m_tendencia = other.m_tendencia;
            m_unidades = other.m_unidades;
        }
        return *this;
    }

    const std::string& nombre() const noexcept { return m_nombre; }
    double coefVar() const noexcept { return m_coefVar; }
    double tendencia() const noexcept { return m_tendencia; }
    double unidades() const noexcept { return m_unidades; }

private:
    std::string m_nombre;
    double m_coefVar;
    double m_tendencia;
    double m_unidades;
};
