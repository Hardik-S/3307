# Repository Guidelines

## Project Structure & Module Organization
This repository currently contains course guidance documents (e.g., `Instructions.txt`, `Plan.txt`, `Report.pdf`). When code is added, follow the required layout:

- `code/` for all C++ sources, headers, and build files (`.pro` or `CMakeLists.txt`).
- `code/ui/` for Qt UI files (Widgets or QML).
- `code/core/` for domain logic classes.
- `report/` for PDFs, UML diagrams, and design documentation.

Keep UI and core strictly separated. UI may depend on core, but core must not depend on UI; use controllers or interfaces to bridge the boundary.

## Build, Test, and Development Commands
Use Qt Creator for the primary workflow. Typical commands (adjust to your build system):

- `qmake && make` to configure and build a qmake-based project.
- `cmake -S code -B build && cmake --build build` for a CMake-based build.
- `ctest --test-dir build` to run CTest targets (if configured).

## Coding Style & Naming Conventions
- Language: C++ with Qt 6.
- Indentation: 4 spaces, no tabs (Qt Creator default).
- Naming: `CamelCase` for classes, `camelCase` for methods/variables, `UPPER_SNAKE_CASE` for constants.
- Keep modules in their respective folders (e.g., `code/core/InventoryService.h`).

## Testing Guidelines
- Use GoogleTest and Google Mock for unit tests; keep tests in `code/tests/`.
- Test domain logic only; avoid UI testing with gtest.
- Prefer dependency injection and interfaces (pure virtual `QObject` types) to enable mocks.
- Example: `code/tests/TestOrderService.cpp`.

## Commit & Pull Request Guidelines
No Git history is present in this folder, so no existing commit convention can be inferred. If you add version control, use a simple pattern such as `feat: add inventory repository` or `fix: handle null item in UI`. For pull requests, include:

- A brief summary of changes and design impact.
- Linked issue or requirement reference (e.g., Phase 2/3 deliverables).
- Screenshots or screen recordings for UI changes.

## Security & Configuration Tips
- Keep any external I/O (files, persistence) in `code/core/` and behind interfaces.
- Avoid hard-coded paths; use Qt APIs such as `QStandardPaths`.

## Agent-Specific Instructions
- Ensure at least 8 non-trivial classes across 3 logical modules.
- Implement 2 creational and 1 structural/behavioral design pattern, explicitly documented in code and reports.
