project "obj"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "../vendor",
        "../vendor/glad/include"
    }

    links {
        "stbi"
    }

    files {
        "*.cpp",
        "*.hpp"
    }