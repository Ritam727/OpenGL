project "obj"
    kind "SharedLib"
    language "C++"

    targetdir "../../lib"
    objdir "../../objects"

    includedirs {
        "../vendor",
        "../vendor/glad/include",
        "../vendor/glfw/include"
    }

    links {
        "stbi"
    }

    files {
        "*.cpp",
        "*.hpp"
    }

    filter "system:Linux"
        defines {
            "PLATFORM_LINUX"
        }
    
    filter "system:windows"
        defines {
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }