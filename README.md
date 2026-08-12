# object_programming

## Overview
This repository contains a C++ object-oriented programming project for managing movie and client data from text files.  
It includes:
- domain classes for movies and clients,
- shared helpers for parsing and validation,
- a console application entry point,
- a basic GoogleTest unit test.

## Repository structure
```text
object_programming/
├── main.cpp              # Console application entry point
├── clients/clients.h     # Client model and client-related operations
├── movies/movies.h       # Movie model and movie-related operations
├── shared.h              # Shared utility functions
├── settings.h            # Project-wide constants and file paths
├── data/
│   ├── clients.txt       # Client data source
│   └── movies.txt        # Movie data source
├── tests/
│   ├── CMakeLists.txt
│   └── test_client.cpp   # Unit test example
├── CMakeLists.txt
└── LICENSE
```

## Build
This project uses CMake.

```bash
cmake -S . -B build
cmake --build build
```

## Run
After building, run the executable:

```bash
./build/object_programming
```

## Tests
The repository includes a GoogleTest-based test target under `tests/`.
If GoogleTest is available in your environment, run:

```bash
ctest --test-dir build --output-on-failure
```

## Notes
- `settings.h` defines file paths used by the app (`data/clients.txt`, `data/movies.txt`).
- `CMakeLists.txt` currently contains compiler path settings that may need adjustment on your machine.

## License
This project is licensed under the MIT License.
