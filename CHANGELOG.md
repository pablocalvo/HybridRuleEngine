# Changelog

## [1.0.0] - 2025-11-12
### Added
- Initial hybrid architecture (C++20 + Python + PostgreSQL)
- Threads communicating with Python via stdin/stdout
- Rule-based decisions stored in `inventario.reglas`
- Sample algorithms: Pareto ABC, Linear Regression, DBSCAN
- CMake build support for Linux/Windows

### Next
- Replace file-based exchange with socket/JSON-RPC
- Implement real analytical algorithms
- Add PostgreSQL metrics logging per execution
