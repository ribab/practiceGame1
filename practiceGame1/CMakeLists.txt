add_definitions(-g -std=c++11)

project(practicegame1)

add_executable(practicegame1 Button.cpp paddle.cpp ball.cpp TitleState.cpp PlayState.cpp main.cpp Game.cpp)

install(TARGETS practicegame1 RUNTIME DESTINATION bin)

target_link_libraries(practicegame1 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network)

