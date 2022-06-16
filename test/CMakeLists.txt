function(make_test name)
    add_executable(${name} ${ARGN})
    target_link_libraries(${name} PRIVATE bufep)
    target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/test)
    add_test(NAME ${name} COMMAND ${name} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/test)
endfunction()

make_test(test_00 ${PROJECT_SOURCE_DIR}/test/test_00.c)
make_test(test_01 ${PROJECT_SOURCE_DIR}/test/test_01.c)
