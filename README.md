# HybridRuleEngine

HybridRuleEngine is a high-performance rule evaluation engine written in modern C++ (C++20), designed to load, validate and execute business rules from external definitions (JSON, database, or other sources).  
It can optionally delegate complex calculations to Python, combining **C++ speed** with **Python flexibility**.

> ⚙️ Typical use cases: eligibility checks, pricing/discount rules, risk scoring, routing logic, feature flags, etc.

---

## Features

- 🔁 **Hybrid design (C++ + Python)**  
  Evaluate rules in C++ and call Python functions for dynamic or ML-based logic.

- 🧱 **Declarative rules**  
  Rules are defined outside the binary (e.g. JSON), so they can be versioned and updated without recompiling.

- 🧮 **Context-based evaluation**  
  Rules operate on a `Context` (key–value map) that represents the current business data.

- 🧵 **Thread-safe evaluation**  
  The engine is designed to be used safely from multiple threads.

- 🧷 **Versioning with CAS (Compare-And-Swap)**  
  Rules can be updated atomically; readers always see a consistent snapshot.

- 🧪 **Pluggable strategies**  
  Different evaluation strategies or backends can be plugged in (e.g. pure C++, Python callback, mixed).

---

## Architecture overview

At a high level the engine is composed of:

- `RuleEngine` – Public façade used by applications. Loads rules and exposes `evaluate()` APIs.
- `RuleStore` – In-memory storage of rules, with versioning and atomic updates.
- `Rule` / `Condition` / `Action` – Domain model for rules.
- `Context` – Key–value structure passed to rules during evaluation.
- `RuleEvaluator` – Component that executes the conditions/actions of a rule.
- `PythonAdapter` (optional) – Bridge to call Python functions from C++.

A UML diagram describing the main components can be found in:  
`docs/architecture.puml` (PlantUML) and/or `docs/architecture.png`.

---

## Getting started

### Requirements

- C++20 compatible compiler (GCC, Clang, MSVC)
- CMake (3.20+ recommended)
- Python 3.x (optional, only if you enable Python integration)
- A standard C++ toolchain (make/ninja, etc.)

### Build

```bash
git clone https://github.com/pablocalvo/HybridRuleEngine.git
cd HybridRuleEngine
mkdir build && cd build
cmake ..
cmake --build .
```

(Adjust CMake options according to your environment if needed.)

---

## Basic usage example

Below is a minimal example showing how to load rules and evaluate one of them:

```cpp
#include "RuleEngine.hpp"
#include "Context.hpp"

int main() {
    // 1. Create the engine
    RuleEngine engine;

    // 2. Load rules from a JSON file
    engine.loadFromJson("examples/simple_rules.json");

    // 3. Prepare the input context
    Context ctx;
    ctx.set("age", 42);
    ctx.set("country", std::string("AR"));
    ctx.set("monthly_income", 2500.0);

    // 4. Evaluate a specific rule by id
    auto result = engine.evaluate("LoanEligibility", ctx);

    if (result.passed()) {
        std::cout << "Customer is eligible for a loan.\n";
        std::cout << "Approved amount: " << result.get<double>("approved_amount") << "\n";
    } else {
        std::cout << "Customer is NOT eligible. Reason: "
                  << result.get<std::string>("reason") << "\n";
    }

    return 0;
}
```

---

## Example rule definition (JSON)

A simple example of rule structure (see more in `examples/simple_rules.json`):

```json
{
  "version": "1.0",
  "rules": [
    {
      "id": "LoanEligibility",
      "description": "Basic loan eligibility rule",
      "priority": 10,

      "conditions": {
        "all": [
          { "field": "age", "op": ">=", "value": 18 },
          { "field": "monthly_income", "op": ">=", "value": 1000.0 }
        ]
      },

      "actions": [
        { "type": "set", "field": "eligible", "value": true },
        { "type": "set", "field": "approved_amount", "value": 5000.0 }
      ]
    }
  ]
}
```

This is only an example schema; the real engine may support more operators and action types.

---

## Python integration (optional)

When Python integration is enabled, actions can call Python functions:

```json
{
  "id": "DynamicDiscount",
  "description": "Compute discount using a Python function",
  "priority": 5,

  "conditions": {
    "any": [
      { "field": "segment", "op": "==", "value": "VIP" },
      { "field": "total_amount", "op": ">=", "value": 500.0 }
    ]
  },

  "actions": [
    {
      "type": "python",
      "function": "compute_discount",
      "args": ["total_amount"],
      "target_field": "discount"
    }
  ]
}
```

And the Python function could look like:

```python
def compute_discount(total_amount: float) -> float:
    if total_amount >= 1000:
        return 20.0
    if total_amount >= 500:
        return 10.0
    return 5.0
```

---

## Thread-safety and versioning

The rule store is updated using atomic operations (CAS). Readers see a consistent snapshot while writers update the rule set in a lock-free or low-contention fashion.

Typical flow:

1. Parse rules into an immutable structure.
2. Atomically swap the active rule set using CAS.
3. Worker threads keep evaluating the old snapshot until the swap succeeds.

This makes the engine suitable for **high-throughput, low-latency** applications.

---

## Project structure (suggested)

```text
HybridRuleEngine/
├── src/              # C++ implementation
├── include/          # Public headers
├── examples/         # Example JSON rules and sample applications
├── docs/             # UML diagrams and design notes
├── tests/            # Unit tests (e.g. GoogleTest)
├── CMakeLists.txt
├── README.md
└── CHANGELOG.md
```

---

## Roadmap

- More built-in operators and functions.
- Additional backends for rule storage (database, remote service).
- Advanced profiling and tracing for rule execution.
- Example integrations (REST API, message queues, etc.).

---

## License

Distributed under the MIT License. See `LICENSE` for details.
