cmake_minimum_required(VERSION 3.6)

set(UTILS_SOURCE
        xhook.c
        xh_core.c
        xh_elf.c
        xh_jni.c
        xh_log.c
        xh_util.c
        xh_version.c
        )

#[[if (${ANDROID_ABI} STREQUAL "x86")
    set(TRAMPOLINE trampoline_x86.c)
else ()
    set(TRAMPOLINE trampoline_arm.c)
endif ()

message(${TRAMPOLINE})]]
add_library(xhook
        STATIC
        ${UTILS_SOURCE}
        )
target_link_libraries(xhook)