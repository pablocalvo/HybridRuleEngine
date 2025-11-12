# HybridRuleEngine 🧠⚙️
Hybrid multithreaded rule engine combining **C++20**, **Python**, and **PostgreSQL**.

## Overview
Each C++ thread acts as an autonomous agent. It sends a JSON packet to a Python rule engine that queries PostgreSQL (`inventario.reglas`) to determine which analytical rule to apply.

## Architecture
C++ Threads → JSON (stdin) → Python (psycopg2) → PostgreSQL

## Build & Run
### Windows
```
mkdir build && cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
.\Release\hre.exe
```

### Linux / WSL
```
mkdir build && cd build
cmake ..
make -j
./hre
```

### Environment variable
```
export PG_DSN="dbname=inventario user=postgres password=tu_clave host=localhost"
```

## Features
- Threads communicate with Python via stdin/stdout
- Rules stored in `inventario.reglas`
- Algorithms: Pareto ABC, Linear Regression, DBSCAN
