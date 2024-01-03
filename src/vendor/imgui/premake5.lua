project "imgui"
    kind "SharedLib"
    language "C++"

    targetdir "../../../lib"
    objdir "../../../objects"

    includedirs {
        "../glfw/include"
    }

    files {
        "*"
    }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }