# Project Compilation:

1) In the `CMakeLists.txt` file, change the `SFML_DIR` variable - it should contain the path to your version of SFML.
2) In the `PATH` environment variable, specify the path to the SFML library's dynamic libraries (`.dll` or `.so`).
3) If paths to `cmake` and `make` are not yet specified in your `PATH` environment variable, add them as well.

4) Depending on your environment:

    A) Linux:
        - Open the terminal in the `build` directory and enter the commands:
            ```
            cmake ..
            make
            ```

    B) Windows MinGW
        - Open the terminal in the `build` directory and enter the commands:
            ```
            cmake -G"MinGW Makefiles" ..
            mingw32-make.exe
            ```

    C) Windows Visual Studio
        - Open the terminal in the `build` directory and enter the commands:
            ```
            cmake -G"Visual Studio 16 2019" ..
            ```
        - Open the created Visual Studio project and compile.
        - If you have a different version of Visual Studio, you can call for help:
            ```
            cmake -h
            ```
