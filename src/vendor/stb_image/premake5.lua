project "stbi"
    kind "SharedLib"
    language "C++"

    targetdir "../../../lib"
    objdir "../../../objects"

    files {
        "*"
    }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }