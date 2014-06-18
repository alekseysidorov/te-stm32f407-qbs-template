import qbs
import Stm32Library
import qbs.FileInfo
import qbs.ModUtils

Stm32Library {
    name: "Libraries"
    condition: project.withMurenaCnc

    cpp.includePaths: [
        "../app",
        ".",
        "cmsis",
        "port/gcc",
        "periphery",
        "System",
        "ethernet",
        "lwip/src/",
        "lwip/src/arch/",
        "lwip/src/include",
        "lwip/src/include/lwip",
        "lwip/src/include/ipv4", //Use old internet protocol due ipv6 has experimental status
        "lwip/src/include/netif",
        "lwip/src/netif",
        "lwip/include",
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

    Group {
        name: "sources"
        prefix: "**/"
        files: [
            "*.c",
            "*.cpp",
            "*.h",
            "*.s"
        ]
        excludeFiles: [
            "mdk/*.*",
            "ipv6/*.*",
            "test/unit/**/*.*",
        ]
        cpp.cxxFlags: [ "-std=c++11" ]
        cpp.cFlags: [ "-std=gnu89" ]
    }

    Export {
        Depends { name: "cpp" }

        cpp.includePaths: [
            "../app",
            ".",
            "cmsis",
            "port/gcc",
            "periphery",
            "System",
            "ethernet",
            "lwip/src/",
            "lwip/src/arch/",
            "lwip/src/include",
            "lwip/src/include/lwip",
            "lwip/src/include/ipv4", //Use old internet protocol due ipv6 has experimental status
            "lwip/src/include/netif",
            "lwip/src/netif",
            "lwip/include",
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
    }
}
