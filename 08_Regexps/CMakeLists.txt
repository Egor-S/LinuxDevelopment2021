cmake_minimum_required(VERSION 3.10)
project(esub)

add_executable(esub esub.c subparser.h)

enable_testing()
add_test(NAME just_replace COMMAND ./test.sh "ty" "yt" "qwerty" "$<TARGET_FILE:esub>" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME date_format COMMAND ./test.sh "([0-9]{2})\\.([0-9]{2})\\.([0-9]{4})" "\\3-\\2-\\1" "Today: 17.11.2021, Wednesday" "$<TARGET_FILE:esub>" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
add_test(NAME first_occurance COMMAND ./test.sh "me" "Me" "mee me do, mee me do" "$<TARGET_FILE:esub>" WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
