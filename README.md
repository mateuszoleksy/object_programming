# object_programming

## Overview
`object_programming` is a C++ console application for managing a small DVD rental database.  
It demonstrates object-oriented programming concepts through two core domains:
- **Movies** (`moviesClass::movie`)
- **Clients** (`clientsClass::client`)

The app supports login, registration, CRUD operations, and searching over movie and client records stored in text files.

## Main Features
- User login and registration (`users.txt`)
- Movie management:
  - add / modify / delete records
  - search by multiple fields
- Client management:
  - add / modify / delete records
  - search by multiple fields
  - register and return rented movies
- Persistent storage in:
  - `data/movies.txt`
  - `data/clients.txt`

## Repository Structure
```text
object_programming/
├── main.cpp               # Application entry point and menu flow
├── clients/clients.h      # Client model + client operations
├── movies/movies.h        # Movie model + movie operations
├── shared.h               # Shared helper functions
├── settings.h             # Constants and file/config settings
├── data/
│   ├── clients.txt        # Client database
│   └── movies.txt         # Movie database
├── users.txt              # Login credentials and roles
├── tests/
│   ├── CMakeLists.txt
│   └── test_client.cpp
└── CMakeLists.txt
```

## Build
The project uses CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Run
After building:

```bash
./build/object_programming
```

## Data Format
- Field separator: `&`
- Multi-value separator (dates / movie ids): `%`

Configured in `settings.h`:
- `FILE_OUT_CLIENTS` → `data/clients.txt`
- `FILE_OUT_MOVIES` → `data/movies.txt`

## License
This project is licensed under the MIT License. See `LICENSE`.
