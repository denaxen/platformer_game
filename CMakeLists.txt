cmake_minimum_required(VERSION 2.8.0)
project(game)

# Зададим переменную-строку SFML_DIR = "C:/Workspace/cs_mipt_faki/term2/3rdparty/SFML-2.5.1"
# Вам нужно задать свой путь, то место, где у вас лежит библиотека SFML
set(SFML_DIR /usr/include/SFML)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Укажем папку, где нужно искать header-файлы
include_directories(${SFML_DIR})
# Укажем папку, где нужно искать библиотеки
link_directories(${SFML_DIR})
 
# Создадим исполняемый файл по имени game из исходных файлов
add_executable(game src/main.cpp src/player.cpp src/player_states.cpp src/skeleton.cpp src/skeleton_states.cpp src/skeleton_strategy.cpp)

# Создадим исполняемый файл по имени editor из исходных файлов
add_executable(editor src/editor.cpp src/player.cpp src/player_states.cpp src/skeleton.cpp src/skeleton_states.cpp src/skeleton_strategy.cpp)

# Подключим статические библиотеки libsfml-graphics.a, libsfml-system.a, libsfml-window.a
target_link_libraries(game sfml-graphics sfml-window sfml-system)

target_link_libraries(editor sfml-graphics sfml-window sfml-system)
