project "glad"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    includedirs {
        "include"
    }
    
    targetdir "../../../lib"
    objdir "../../../objects"

    files {
        "src/glad.c"
    }