# Advisorbot

Midterm project for the course "Object Oriented Programming" at the University of London.

## Build

Install [CMake](https://cmake.org/) on Mac OS X:
```bash
brew install cmake
```

Install [Boost C++ Libraries](https://www.boost.org/) on Mac OS X:
```bash
brew install boost
```

On Ubuntu:

```bash
sudo apt-get install cmake libboost-all-dev
```

Run the following commands to build the project:

```bash
mkdir -p build
cd build/
cmake ..
cmake --build . --target advisorbot
```

Run the executable:

```bash
./advisorbot
```
