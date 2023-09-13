
#--------------------------------------------------------------
# SystemC
#
find_package(SystemCLanguage CONFIG REQUIRED)

#--------------------------------------------------------------
# Simulator
#
add_library(sim STATIC
    base_instructions.cpp
    bus_controller.cpp
    debug.cpp
    disassemble.cpp
    log.cpp
    peripherals.cpp
    periph_names.cpp
    phys_memory.cpp
    processor.cpp
    read_elf.cpp
    registers.cpp
    simulator.cpp
    timer.cpp
    #../firmware/esp32-c3-rev3-drom1.c
    #../firmware/esp32-c3-rev3-irom0.c
)
add_executable(picosim
    main.cpp
)
include_directories(
    /usr/local/include
)
target_link_libraries(picosim sim SystemC::systemc)

install(TARGETS picosim DESTINATION bin)
