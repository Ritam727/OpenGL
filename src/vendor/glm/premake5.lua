project "glm"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    targetdir "../../../lib"
    objdir "../../../objects"

    files {
        "*"
    }