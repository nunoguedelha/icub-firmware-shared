# Copyright: (C) 2014 iCub Facility, Istituto Italiano di Tecnologia
# Authors: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT


project(embobj)

set(TEST ON CACHE BOOL "use the embObjLib lib")

if(TEST)
    message(INFO " TEST is ON ")
else(TEST)
    message(INFO " TEST is OFF ")
endif(TEST)


#--------------------------------------------------------#
# list of robots
#include(robotConfigList.cmake)
#--------------------------------------------------------#
# using embObjLib.conf to define PATH VARIABLES
include(embObjLib.cmake)
include_directories (${embObj_includes})    #derived from previous file
#--------------------------------------------------------#

if(WITH_EMBOBJ)
# right now install means copy the source folder somewhere ... to be changed!! Install just the needed headers and the binaries
#    install(DIRECTORY embobj
#            DESTINATION ${icub_firmware_shared_INCLUDE_DIR})
#    install(DIRECTORY robotconfig
#            DESTINATION ${icub_firmware_shared_INCLUDE_DIR})
endif()

#message("firmware/eth: icub_firmware_shared_INCLUDE_DIR is ${icub_firmware_shared_INCLUDE_DIR}\n")
#message("firmware/eth: CMAKE_CURRENT_SOURCE_DIR is ${CMAKE_CURRENT_SOURCE_DIR}\n")
message("firmware/eth: embObj_includes is ${embObj_includes}\n")

#set_property(GLOBAL APPEND PROPERTY icub_firmware_shared_TARGETS embobj)
#set_property(GLOBAL PROPERTY icub_firmware_shared_embobj_BUILD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#set_property(GLOBAL PROPERTY icub_firmware_shared_embobj_BUILD_INCLUDE_DIR ${embObj_includes})
#set_property(GLOBAL PROPERTY icub_firmware_shared_embobj_INSTALL_INCLUDE_DIR ${icub_firmware_shared_INCLUDE_DIR})

#set()
message( INFO " EO_BASE_DIR is ${EO_BASE_DIR} ")
message( INFO " CORE_FOLDER is ${CORE_FOLDER} ")

#find_package(icub REQUIRED)
#if(icub_FOUND)
#    message(INFO " icub found ")
#    message(INFO " icub_INCLUDE_DIRS is ${ICUB_INCLUDE_DIRS} ")
#    message(INFO " icub_INCLUDES is ${ICUB_INCLUDES} ")

#    include_directories(${ICUB_INCLUDE_DIRS})
#else()
#    message(INFO " icub was NOT found ")
#endif()

add_definitions(-D_ICUB_CALLBACK_ -DUSE_EOPROT_XML -DEOPROT_CFG_OVERRIDE_CALLBACKS_IN_RUNTIME)


set(HT_CONFIG_iCubGenova04  ${NVS_EB_SRC_FOLDER}eOprot_robot_ge04.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b01.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b02.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b03.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b04.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b05.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b06.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b07.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b08.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b09.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b10.c
                            ${NVS_EB_SRC_FOLDER}eOprot_b11.c
                            )


#set(embObj_robot_list iCubGenova04)
set(embObj_robot_list )

MESSAGE(STATUS "Robot list : ${embObj_robot_list}")
foreach(robot ${embObj_robot_list})
    MESSAGE(STATUS "Process robot: ${robot}")
    SOURCE_GROUP("robot ${robot} Source Files" FILES ${HT_CONFIG_${robot}})
    add_library(transceiver_config_${robot} ${HT_CONFIG_${robot}})
set_property(GLOBAL APPEND PROPERTY icub_firmware_shared_TARGETS transceiver_config_${robot})

endforeach(robot)

set_property(GLOBAL PROPERTY icub_firmware_shared_embobj_BUILD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(GLOBAL APPEND PROPERTY icub_firmware_shared_embobj_BUILD_INCLUDE_DIR  ${embObj_includes})
#set_property(GLOBAL PROPERTY icub_firmware_shared_embobj_INSTALL_INCLUDE_DIR ${icub_firmware_shared_INCLUDE_DIR})


# EmbObj-src
set(CORE_FOLDER_SOURCE      ${CORE_FOLDER}/EOarray.c
                            ${CORE_FOLDER}/EoCommon.c
                            ${CORE_FOLDER}/EOconstarray.c
                            ${CORE_FOLDER}/EOconstvector.c
                            ${CORE_FOLDER}/EOdeque.c
                            ${CORE_FOLDER}/EOfifo.c
                            ${CORE_FOLDER}/EOfifoByte.c
                            ${CORE_FOLDER}/EOfifoWord.c
                            ${CORE_FOLDER}/EOlist.c
                            ${CORE_FOLDER}/EOtheErrorManager.c
                            ${CORE_FOLDER}/EOtheMemoryPool.c
                            ${CORE_FOLDER}/EOvector.c
                            ${CORE_FOLDER}/EOpacket.c
                            ${CORE_YEE}/EOYtheSystem.c
                            )

set(CORE_VEE_SOURCE         ${CORE_FOLDER}/EOVmutex.c
                            ${CORE_FOLDER}/EOVtask.c
                            ${CORE_FOLDER}/EOVtheSystem.c
                            )

#set(CORE_API_HEADER         ${CORE_FOLDER}/EOarray.h
#                            ${CORE_FOLDER}/EoCommon.h
#                            ${CORE_FOLDER}/EOconstarray.h
#                            ${CORE_FOLDER}/EOconstvector.h
#                            ${CORE_FOLDER}/EOdeque.h
#                            ${CORE_FOLDER}/EOfifo.h
#                            ${CORE_FOLDER}/EOfifoByte.h
#                            ${CORE_FOLDER}/EOfifoWord.h
#                            ${CORE_FOLDER}/EOlist.h
#                            ${CORE_FOLDER}/EOtheErrorManager.h
#                            ${CORE_FOLDER}/EOtheMemoryPool.h
#                            ${CORE_FOLDER}/EOvector.h
#                            ${CORE_YEE}/EOYtheSystem.h
#                            ${CORE_FOLDER}/EOpacket.h
#                            )

#set(CORE_FOLDER_HEADER      ${CORE_FOLDER}/EOarray_hid.h
#                            ${CORE_FOLDER}/EoCommon_hid.h
#                            ${CORE_FOLDER}/EOconstarray_hid.h
#                            ${CORE_FOLDER}/EOconstvector_hid.h
#                            ${CORE_FOLDER}/EOdeque_hid.h
#                            ${CORE_FOLDER}/EOfifo_hid.h
#                            ${CORE_FOLDER}/EOfifoByte_hid.h
#                            ${CORE_FOLDER}/EOfifoWord_hid.h
#                            ${CORE_FOLDER}/EOlist_hid.h
#                            ${CORE_FOLDER}/EOtheErrorManager_hid.h
#                            ${CORE_FOLDER}/EOtheMemoryPool_hid.h
#                            ${CORE_API}/EOvector_hid.h
#                            ${CORE_FOLDER}/EOpacket_hid.h
#                            ${CORE_YEE}/EOYtheSystem_hid.h
#                            )

# EmbObj-NV & Protocol files
set(PROT_SOURCE
                            ${PROT_FOLDER}/transport/EOnv.c
                            ${PROT_FOLDER}/transport/EOnvSet.c
                            ${PROT_FOLDER}/transport/EOreceiver.c
                            ${PROT_FOLDER}/transport/EOrop.c
                            ${PROT_FOLDER}/transport/EOropframe.c
                            ${PROT_FOLDER}/transport/EOagent.c
                            ${PROT_FOLDER}/transport/EOtheFormer.c
                            ${PROT_FOLDER}/transport/EOtheParser.c
                            ${PROT_FOLDER}/transport/EOtransceiver.c
                            ${PROT_FOLDER}/transport/EOtransmitter.c
                            ${PROT_FOLDER}/transport/EOtheBOARDtransceiver.c
                            ${PROT_FOLDER}/transport/EOhostTransceiver.c
                            ${PROT_FOLDER}/transport/EOconfirmationManager.c
                            ${PROT_FOLDER}/transport/EOproxy.c
                            ${PROT_FOLDER}/transport/EOprotocolConfigurator.c
                            ${PROT_FOLDER}/transport/EOnvsetDEVbuilder.c
                            )

#set(PROT_HEADER             ${PROT_FOLDER}/transport/EOhostTransceiver_hid.h
#                            ${PROT_FOLDER}/transport/EOnv_hid.h
#                            ${PROT_FOLDER}/transport/EOnvSet_hid.h
#                            ${PROT_FOLDER}/transport/EOreceiver_hid.h
#                            ${PROT_FOLDER}/transport/EOrop_hid.h
#                            ${PROT_FOLDER}/transport/EOropframe_hid.h
#                            ${PROT_FOLDER}/transport/EOtheFormer_hid.h
#                            ${PROT_FOLDER}/transport/EOtheParser_hid.h
#                            ${PROT_FOLDER}/transport/EOtransceiver_hid.h
#                            ${PROT_FOLDER}/transport/EOtransmitter_hid.h
#                            ${PROT_FOLDER}/transport/EOtransmitter_hid.h
#                            ${PROT_FOLDER}/transport/EOprotocolConfigurator.h
#                            ${PROT_FOLDER}/transport/EOnvsetDEVbuilder.h
#                            )

set(NVS_SOURCE              ${NVS_MC_SRC_FOLDER}/EoProtocol.c
                            ${NVS_MC_SRC_FOLDER}/EoProtocolEPs.c
                            )


set(NVS_MC_SOURCE           ${NVS_MC_SRC_FOLDER}EoProtocolMC_fun.c
                            ${NVS_MC_SRC_FOLDER}EoProtocolMC_rom.c
                            )

set(NVS_MNGMNT_SOURCE       ${NVS_MNGMNT_SRC_FOLDER}EoProtocolMN_fun.c
                            ${NVS_MNGMNT_SRC_FOLDER}EoProtocolMN_rom.c
                            )

set(NVS_SENSORS_SOURCE      ${NVS_SENSORS_SRC_FOLDER}EoProtocolAS_fun.c
                            ${NVS_SENSORS_SRC_FOLDER}EoProtocolAS_rom.c
                            )

set(NVS_SKIN_SOURCE         ${NVS_SKIN_SRC_FOLDER}EoProtocolSK_fun.c
                            ${NVS_SKIN_SRC_FOLDER}EoProtocolSK_rom.c
                            )


set(embObj_CoreLib          ${CORE_FOLDER_SOURCE}
                            ${CORE_VEE_SOURCE}
                            ${PROT_SOURCE}
                            ${NVS_SOURCE}
                            ${NVS_MC_SOURCE}
                            ${NVS_MNGMNT_SOURCE}
                            ${NVS_SENSORS_SOURCE}
                            ${NVS_SKIN_SOURCE}
#                            ${NVS_USR_SOURCE}
                            )

set(embObj_CoreLib_HDRS     ${CORE_FOLDER_HEADER}
                            ${CORE_API_HEADER}
                            ${PROT_HEADER}
                            )

#message (INFO " embObj_CoreLib is compiling files ${embObj_CoreLib}")
SOURCE_GROUP("embObj_CoreLib Source Files" FILES ${embObj_CoreLib})
SOURCE_GROUP("embObj_CoreLib Header Files" FILES ${embObj_CoreLib_HDRS})


set_property(GLOBAL APPEND PROPERTY icub_firmware_shared_TARGETS embObj_Core)
#set_property(GLOBAL APPEND PROPERTY icub_firmware_shared_embobj_BUILD_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(GLOBAL PROPERTY icub_firmware_shared_embobj_INSTALL_INCLUDE_DIR ${icub_firmware_shared_INCLUDE_DIR})

add_library(embObj_Core ${embObj_CoreLib})

foreach(robot ${embObj_robot_list})
    TARGET_LINK_LIBRARIES(transceiver_config_${robot} embObj_Core)
endforeach(robot)
