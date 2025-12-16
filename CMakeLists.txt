cmake_minimum_required(VERSION 3.16)
project(FitnessActivity)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_AUTOMOC ON)


find_package(Qt6 REQUIRED COMPONENTS Widgets)


include_directories(
    domain
    repository
    controller
    ui
)


add_executable(FitnessActivity
    main.cpp
    domain/Activity.cpp
    repository/Repository.cpp
    repository/CSVRepository.cpp
    repository/JSONRepository.cpp
    controller/Service.cpp
    controller/Command.cpp
    controller/FilterStrategy.cpp
    ui/Console.cpp
    ui/MainWindow.cpp
)


target_link_libraries(FitnessActivity Qt6::Widgets)
