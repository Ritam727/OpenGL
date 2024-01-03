project "test"
    kind "SharedLib"
    language "C++"

    links {
        "glad"
    }

    includedirs {
        "../vendor",
        "../include",
        "../vendor/glad/include"
    }

    targetdir "../../lib"
    objdir "../../objects"

    files {
        "*.cpp",
        "*.hpp"
    }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }