# DynamicFactory

A lightweight C++11 template-based factory pattern implementation.

## About

This is an old hobby project that demonstrates a simple yet flexible factory pattern using C++ templates. It allows for dynamic object creation based on string identifiers, making it useful for scenarios where you need to create objects at runtime based on configuration files or user input.

**Note:** This is an old project created as a hobbyist experiment with C++ template metaprogramming and design patterns.

## Features

- Template-based factory pattern implementation
- Runtime object registration and creation
- Type-safe object instantiation
- Simple and clean API

## Requirements

- C++11 compatible compiler (GCC 4.8+, Clang 3.3+, MSVC 2013+)
- Make (for building with the provided Makefile)

## Project Structure

```
.
├── AbstractInstantiator.hpp    # Abstract base for object instantiators
├── DynamicFactory.hpp          # Main factory class declaration
├── DynamicFactory.tpp          # Factory implementation
├── Instantiator.hpp            # Concrete instantiator declaration
├── Instantiator.tpp            # Instantiator implementation
├── main.cpp                    # Example usage
├── Makefile                    # Build configuration
└── README.md                   # This file
```

## Building

### Using Make

```bash
# Build debug version (default)
make

# Build release version
make release

# Clean build artifacts
make clean

# Show all available targets
make help
```

### Manual Compilation

If you prefer to compile manually:

```bash
g++ -Wall -Wextra -std=c++11 main.cpp -o DynamicFactory
```

## Running

```bash
# Run debug build
make run

# Run release build
make run-release

# Or run directly after building
./build/debug/DynamicFactory
```

## Example Usage

The project includes a simple example in `main.cpp` that demonstrates:

1. Creating a factory for a base class (`AbstractComponent`)
2. Registering derived classes (`HealthComponent`, `WeaponComponent`)
3. Creating instances using string identifiers
4. Using the created objects polymorphically

```cpp
DynamicFactory<AbstractComponent> componentFactory;
componentFactory.RegisterClass<HealthComponent>("HealthComponent");
componentFactory.RegisterClass<WeaponComponent>("WeaponComponent");

AbstractComponent* hp = componentFactory.CreateInstance("HealthComponent");
AbstractComponent* weapon = componentFactory.CreateInstance("WeaponComponent");
```
