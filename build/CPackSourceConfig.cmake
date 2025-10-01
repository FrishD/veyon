# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/app;/app/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqca-qt5-2-plugins")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Veyon is a free and open source software for monitoring and controlling
computers across multiple platforms. Veyon supports you in teaching in digital
learning environments, performing virtual trainings or giving remote support.

The following features are available in Veyon:

* Overview: monitor all computers in one or multiple locations or classrooms
* Remote access: view or control computers to watch and support users
* Demo: broadcast the teacher's screen in realtime (fullscreen/window)
* Screen lock: draw attention to what matters right now
* Communication: send text messages to students
* Start and end lessons: log in and log out users all at once
* Screenshots: record learning progress and document infringements
* Programs & websites: launch programs and open website URLs remotely
* Teaching material: distribute and open documents, images and videos easily
* Administration: power on/off and reboot computers remotely")
set(CPACK_DEBIAN_PACKAGE_RELEASE "")
set(CPACK_DEBIAN_PACKAGE_SECTION "Education")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS "ON")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "veyon built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "TGZ")
set(CPACK_IGNORE_FILES "/app/build/;/app/.git/;")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY "TRUE")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALLED_DIRECTORIES "/app;/")
set(CPACK_INSTALL_CMAKE_PROJECTS "")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/app/cmake/modules")
set(CPACK_NSIS_DISPLAY_NAME "veyon 4.9.7.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "veyon 4.9.7.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "/usr/bin/objcopy")
set(CPACK_OBJDUMP_EXECUTABLE "/usr/bin/objdump")
set(CPACK_OUTPUT_CONFIG_FILE "/app/build/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Tobias Junghans <tobydox@veyon.io>")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.28/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Cross-platform computer control and classroom management")
set(CPACK_PACKAGE_FILE_NAME "veyon-4.9.7.0-Source")
set(CPACK_PACKAGE_HOMEPAGE "https://veyon.io")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "veyon 4.9.7.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "veyon 4.9.7.0")
set(CPACK_PACKAGE_NAME "veyon")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Veyon Solutions")
set(CPACK_PACKAGE_VERSION "4.9.7.0")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
set(CPACK_READELF_EXECUTABLE "/usr/bin/readelf")
set(CPACK_RESOURCE_FILE_LICENSE "/app/COPYING")
set(CPACK_RESOURCE_FILE_README "/app/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.28/Templates/CPack.GenericWelcome.txt")
set(CPACK_RPM_EXCLUDE_FROM_AUTO_FILELIST_ADDITION "/lib")
set(CPACK_RPM_PACKAGE_DESCRIPTION "Veyon is a free and open source software for monitoring and controlling
computers across multiple platforms. Veyon supports you in teaching in digital
learning environments, performing virtual trainings or giving remote support.

The following features are available in Veyon:

* Overview: monitor all computers in one or multiple locations or classrooms
* Remote access: view or control computers to watch and support users
* Demo: broadcast the teacher's screen in realtime (fullscreen/window)
* Screen lock: draw attention to what matters right now
* Communication: send text messages to students
* Start and end lessons: log in and log out users all at once
* Screenshots: record learning progress and document infringements
* Programs & websites: launch programs and open website URLs remotely
* Teaching material: distribute and open documents, images and videos easily
* Administration: power on/off and reboot computers remotely")
set(CPACK_RPM_PACKAGE_LICENSE "GPLv2")
set(CPACK_RPM_PACKAGE_REQUIRES "qca-qt5-ossl")
set(CPACK_RPM_PACKAGE_SOURCES "ON")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "/app/build/;/app/.git/;")
set(CPACK_SOURCE_INSTALLED_DIRECTORIES "/app;/")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/app/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "veyon-4.9.7.0-Source")
set(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
set(CPACK_STRIP_FILES "")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux-Source")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/app/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
