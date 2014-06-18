import qbs

Product {
    Depends { name: "cpp" }
    
    cpp.commonCompilerFlags: [
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mfpu=fpv4-sp-d16",
        "-mfloat-abi=softfp"
    ]
    cpp.linkerFlags: [
        "-mcpu=cortex-m4",
        "-mthumb",
        "-mfpu=fpv4-sp-d16",
        "-mfloat-abi=softfp",
    ]
}
