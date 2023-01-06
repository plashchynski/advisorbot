# Advisorbot

Midterm project for the course "Object Oriented Programming" at the University of London.

## Dependencies

* [Boost C++ Libraries version >= 1.80](https://www.boost.org/)
* [CMake version => 3.10](https://cmake.org/)
* [C++17 Compiler](https://gcc.gnu.org/)

## Build

1. ```20200601.csv``` should be placed into ```data/``` folder.


2. Install [CMake](https://cmake.org/) on Mac OS X:
```bash
brew install cmake
```

3. Install [Boost C++ Libraries](https://www.boost.org/) on Mac OS X:
```bash
brew install boost
```

On Ubuntu:

```bash
sudo apt-get install cmake libboost-all-dev
```

4. Run the following commands to build the project:

```bash
mkdir -p build
cd build/
cmake ..
cmake --build .
```

5. Run the tests:
```bash
cd test/
./advisorbot_unit_tests --log_level=all
```

6. Run the executable:

```bash
./advisorbot
```
