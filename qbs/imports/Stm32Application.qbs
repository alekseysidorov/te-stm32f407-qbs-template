import qbs

Stm32Product {
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true
    
    cpp.positionIndependentCode: false
    cpp.linkerFlags: {
        base.push("-Xlinker");
        base.push("--gc-sections");
        return base;
    }
}
