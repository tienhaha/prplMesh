if (NOT ${PROJECT}_REVISION)
    execute_process(COMMAND "git" "rev-parse" "HEAD" OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE ${PROJECT}_REVISION)
endif()
set(${PROJECT}_VERSION_MAJOR 1)
set(${PROJECT}_VERSION_MINOR 4)
set(${PROJECT}_VERSION_PATCH 0)
set(${PROJECT}_VERSION_STRING ${${PROJECT}_VERSION_MAJOR}.${${PROJECT}_VERSION_MINOR}.${${PROJECT}_VERSION_PATCH})
execute_process(COMMAND "date" "+%F %T" OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE ${PROJECT}_BUILD_DATE)
message(STATUS "MultiAP ${PROJECT} Version: ${${PROJECT}_VERSION_STRING}")
message(STATUS "MultiAP ${PROJECT} Build Date: ${${PROJECT}_BUILD_DATE}")
message(STATUS "MultiAP ${PROJECT} Revision: ${${PROJECT}_REVISION}")

find_package(MapfCommon REQUIRED)
find_package(bcl REQUIRED)
find_package(Tlvf REQUIRED)
find_package(btlvf REQUIRED)
find_package(elpp REQUIRED)
