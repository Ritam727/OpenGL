project "test"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

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