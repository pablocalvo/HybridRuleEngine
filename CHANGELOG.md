# Changelog

All notable changes to this project will be documented in this file.  
This project follows Semantic Versioning.

## [1.0.1] - 2025-11-24
### Added
- Public documentation (README.md) describing architecture, usage, and examples.
- UML high-level architecture diagram in docs/architecture.puml.
- Example JSON rule set in examples/simple_rules.json.
- Initial CHANGELOG.md structure.

## [1.0.0] - 2025-11-12
### Added
- Initial hybrid architecture (C++20 + Python + PostgreSQL)
- Threads communicating with Python via stdin/stdout
- Rule-based decisions stored in inventario.reglas
- Sample algorithms: Pareto ABC, Linear Regression, DBSCAN
- CMake build support for Linux/Windows

### Next
- Replace file-based exchange with socket/JSON-RPC
- Implement real analytical algorithms
- Add PostgreSQL metrics logging per execution
