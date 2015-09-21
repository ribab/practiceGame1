add_definitions(-std=c++11)

project(practicegame1)

add_executable(practicegame1 Entity.cpp Boundingbox.cpp paddle.cpp ball.cpp main.cpp PlayState.cpp Game.cpp)

install(TARGETS practicegame1 RUNTIME DESTINATION bin)

target_link_libraries(practicegame1 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network)

