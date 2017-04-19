### Emscripten glfw3 example

Tested on MSVC14 and Emscripten for windows.

##Building with Emscripten
```
cmake .. -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" -DCMAKE_MAKE_PROGRAM="mingw32-make.exe"
```