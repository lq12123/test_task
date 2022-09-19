find_package(OpenSSL)

if (NOT OPENSSL_FOUND)
    find_path(CYCLES_LIB_DIR
        NAMES
        ${CMAKE_SHARED_LIBRARY_PREFIX}ssl${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${CMAKE_SHARED_LIBRARY_PREFIX}crypto${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${CMAKE_SHARED_LIBRsARY_PREFIX}ssl${CMAKE_SHARED_LIBRARY_SUFFIX}.1.1
        ${CMAKE_SHARED_LIBRARY_PREFIX}crypto${CMAKE_SHARED_LIBRARY_SUFFIX}.1.1

        HINTS
        ${CMAKE_SOURCE_DIR}/src/cli/lib

        DOC "Cycles Libraries directory"
    )

    if (NOT CYCLES_LIB_DIR)
        execute_process(COMMAND
            ${CMAKE_SOURCE_DIR}/scripts/load_openssl
            ${CMAKE_SOURCE_DIR}/src/cli/lib)
    endif()

     set(CYCLES_LIBS
        ssl
        crypto)

    foreach (lib ${CYCLES_LIBS})
        find_library(${lib}_LIBRARY
            NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}${lib}${CMAKE_SHARED_LIBRARY_SUFFIX}.1.1
            HINTS ${CYCLES_LIB_DIR})
        if (${lib}_LIBRARY)
            add_library(${lib} INTERFACE IMPORTED)
            set_target_properties(${lib}
                PROPERTIES
                INTERFACE_LINK_LIBRARIES ${${lib}_LIBRARY}
            )
        endif ()
    endforeach ()
endif()
