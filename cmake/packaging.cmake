set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT "Luis Díaz Más <piponazo@gmail.com>")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

set(CPACK_SOURCE_GENERATOR TBZ2)
set(CPACK_SOURCE_IGNORE_FILES "build.*;\.git/;\.DS_Store/;test;third-party;")

## -----------------------------------------------
## TODO:  Luis will rewrite this -----------------
if ( CYGWIN OR MINGW OR MSVC )
    set(CPACK_GENERATOR TGZ)
else()
    set(CPACK_GENERATOR TBZ2)
endif()

if ( MSVC )
     set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-msvc)
endif()

# https://stackoverflow.com/questions/17495906/copying-files-and-including-them-in-a-cpack-archive
install(DIRECTORY "${PROJECT_SOURCE_DIR}/samples/" DESTINATION "samples")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/contrib/" DESTINATION "contrib")

# Copy top level documents (eg README.md)
# https://stackoverflow.com/questions/21541707/cpack-embed-text-files
set( DOCS
     README-CMAKE.md
     README-CONAN.md
     README.md
     license.txt
)
foreach(doc ${DOCS})
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${doc} DESTINATION .)
endforeach()

# Copy releasenotes.txt and appropriate ReadMe.txt (eg releasenotes/Darwin/ReadMe.txt)
if ( MSVC )
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/releasenotes/msvc/ReadMe.txt DESTINATION .)
else()
    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/releasenotes/${CMAKE_SYSTEM_NAME}/ReadMe.txt DESTINATION .)
endif()

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/releasenotes/releasenotes.txt DESTINATION                .)

## TODO: End                     -----------------
## -----------------------------------------------

include (CPack)
