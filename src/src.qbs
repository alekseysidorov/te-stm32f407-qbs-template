import qbs
import Stm32Application
import qbs.FileInfo
import qbs.ModUtils

Stm32Application {
    name: "Application"

    cpp.includePaths: [
        "app",
        "libs",
        "libs/cmsis",
        "libs/port/gcc",
        "libs/periphery",
        "libs/system",
        "libs/ethernet",
        "libs/lwip/src/",
        "libs/lwip/src/arch/",
        "libs/lwip/src/include",
        "libs/lwip/src/include/lwip",
        "libs/lwip/src/include/ipv4", //Use old internet protocol due ipv6 has experimental status
        "libs/lwip/src/include/netif",
        "libs/lwip/src/netif",
        "libs/lwip/include",
    ]
    cpp.defines: [
        "STM32F4XX",
        "STM32F40_41xxx",
        "USE_STDPERIPH_DRIVER",
        "HSE_VALUE=168000000",
    ]
    Properties {
        condition: cpp.debugInformation
        cpp.defines: outer.concat("DEBUG")
    }

    cpp.linkerScripts: [
        "../ldscripts/libs.ld",
        "../ldscripts/mem.ld",
        "../ldscripts/sections.ld",
    ]

    Group {
        name: "sources"
        prefix: "../**/"
        files: [
            "*.c",
            "*.cpp",
            "*.h",
            "*.s"
        ]
        excludeFiles: [
            "ipv6/*.*",
            "test/unit/**/*.*",
        ]
        cpp.cxxFlags: [ "-std=c++11" ]
        cpp.cFlags: [ "-std=gnu99" ]
        cpp.warningLevel: "all"
    }
    Group {
        name: "ldscripts"
        prefix: "../ldscripts/"
        files: "*.ld"
    }
}
