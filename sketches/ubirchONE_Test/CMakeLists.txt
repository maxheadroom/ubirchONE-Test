add_executable_avr(ubirchONE_Test
        main.cpp
        i2c/i2c_core.c
        i2c/i2c_registers.c
        )
target_link_libraries(ubirchONE_Test SoftwareSerial)
target_sketch_library(ubirchONE_Test SdFat "locally checked in")
target_sketch_library(ubirchONE_Test UbirchSIM800 https://github.com/ubirch/ubirch-avr-sim800)
# copy the config.h.template to config.h in case it is not there; it is ignored by .git!
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config.h")
    message(AUTHOR_WARNING "In directory 'sketches/ubirchONE_Test': installing the template config.h, please edit!")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.template ${CMAKE_CURRENT_SOURCE_DIR}/config.h COPYONLY)
endif ()
