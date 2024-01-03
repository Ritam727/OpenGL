project "glad"
    kind "SharedLib"
    language "C++"

    includedirs {
        "include"
    }
    
    targetdir "../../../lib"
    objdir "../../../objects"

    files {
        "src/glad.c"
    }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }