cmake_minimum_required(VERSION 3.20)

project(DharmadevasBlade
    VERSION 1.0.0
    LANGUAGES CXX RC
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# Source files
# ------------------------------------------------------------
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

set(APP_RESOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/dharmadevas_blade.rc"
)

add_executable(DharmadevasBlade
    ${GAME_SOURCES}
    ${APP_RESOURCE}
)

target_include_directories(DharmadevasBlade PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

if(MSVC)
    target_compile_options(DharmadevasBlade PRIVATE /W4 /utf-8)

    # The custom .rc file embeds our application manifest.
    # MSVC normally generates another manifest automatically,
    # which causes a duplicate RT_MANIFEST resource (type 24,
    # name 1, language 0x0409). Disable the linker's automatic
    # manifest so only the custom resource is embedded.
    target_link_options(DharmadevasBlade PRIVATE /MANIFEST:NO)
endif()

if(WIN32)
    target_link_libraries(DharmadevasBlade PRIVATE winmm)
endif()

# ------------------------------------------------------------
# Runtime data/assets
# ------------------------------------------------------------
add_custom_command(TARGET DharmadevasBlade POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:DharmadevasBlade>/data"
    COMMENT "Copying game data..."
)

add_custom_command(TARGET DharmadevasBlade POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:DharmadevasBlade>/assets"
    COMMENT "Copying game assets..."
)

# ------------------------------------------------------------
# Local development code signing
# ------------------------------------------------------------
# Existing local certificate:
#     C:\LocalDevSigningKey.pfx
# Password:
#     Developer123
#
# The PFX must remain outside the repository.
# ------------------------------------------------------------
if(WIN32)
    find_program(SIGNTOOL_EXECUTABLE
        NAMES signtool.exe signtool
        PATHS
            "$ENV{WindowsSdkDir}/bin"
            "C:/Program Files (x86)/Windows Kits/10/bin"
        PATH_SUFFIXES x64 x86
    )

    set(LOCAL_SIGNING_PFX "C:/LocalDevSigningKey.pfx")

    if(SIGNTOOL_EXECUTABLE AND EXISTS "${LOCAL_SIGNING_PFX}")
        add_custom_command(TARGET DharmadevasBlade POST_BUILD
            COMMAND "${SIGNTOOL_EXECUTABLE}"
                sign
                /f "${LOCAL_SIGNING_PFX}"
                /p "Developer123"
                /fd SHA256
                /tr http://timestamp.digicert.com
                /td SHA256
                "$<TARGET_FILE:DharmadevasBlade>"
            VERBATIM
            COMMENT "Signing Dharmadeva's Blade..."
        )
    else()
        message(WARNING
            "Signing skipped: signtool.exe or C:/LocalDevSigningKey.pfx was not found."
        )
    endif()
endif()

# ------------------------------------------------------------
# Install rules for packaging
# ------------------------------------------------------------
install(TARGETS DharmadevasBlade
    RUNTIME DESTINATION bin
)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION data)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION assets)

# Install top-level docs if present
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
    install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/README.md" DESTINATION .)
endif()

# ------------------------------------------------------------
# CPack configuration for creating installers (NSIS) and zips
# ------------------------------------------------------------
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "DharmadevasBlade")
set(CPACK_PACKAGE_VENDOR "DharmadevasBlade Team")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dharmadeva's Blade - a small game")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-win64")

set(CPACK_GENERATOR "NSIS;ZIP")

# Optional: set installer display name and default install directory
set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${CPACK_PACKAGE_NAME}")

# Try to use an installer icon if present
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/assets/installer_icon.ico")
    set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/assets/installer_icon.ico")
    set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/assets/installer_icon.ico")
endif()

include(CPack)

