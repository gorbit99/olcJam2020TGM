cmake_minimum_required(VERSION 3.12)

project(
    "I'm gonna make an MMO"
    VERSION 1.0
    LANGUAGES CXX
)

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(game src/main.cpp src/Game.h src/Game.cpp src/SkillTree.h src/SkillTree.cpp
    src/StatusBar.h src/StatusBar.cpp src/SpeechBubble.h src/SpeechBubble.cpp src/Minigame.h
    src/ModeratingDiscordMinigame.h src/ModeratingDiscordMinigame.cpp src/AnsweringCommentsMinigame.h src/AnsweringCommentsMinigame.cpp)

target_link_libraries(game X11 GL pthread png stdc++fs asound soloud_static dl)
set_property(TARGET game PROPERTY CXX_STANDARD 17)
