
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was HeyListenConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../usr/local" ABSOLUTE)

####################################################################################

include("${CMAKE_CURRENT_LIST_DIR}/HeyListenTargets.cmake")
check_required_components("hey_listen")
