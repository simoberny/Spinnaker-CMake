# Teledyne FLIR Spinnaker SDK
## CMake implementation
Spinnaker SDK delivers with only Makefile and Visual Studio support. 
To compile Spinnaker based project using CMake use the **FindFlir.cmake** module and reference it on the *CMAKE_MODULE_PATH* of yours CMakeLists. 
From default Vimba in installed in /opt/spinnaker/. If not change folder reference in the cmake module. 

#### Cotire
Cotire is just a CMake module that speeds up the build process. Just a try, ignore it. 

## Requirements
Tested on Linux Mint 20
- spinnaker (v2.5.0.80)

## Compile examples
```bash
    mkdir build && cd build
    cmake ..
    cmake --build .
```
