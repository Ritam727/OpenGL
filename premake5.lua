-- premake5.lua
workspace "Cherno"
    configurations { "Debug", "Release" }

group "Dependencies"
    include "src/include"
    include "src/vendor/glad"
    include "src/tests"
    include "src/vendor/imgui"
    include "src/vendor/stb_image"
    include "src/vendor/glm"
    include "src/vendor/glfw"
group""

project "Application"
    kind "ConsoleApp"
    language "C++"

    targetdir ""
    objdir "objects"

    includedirs {
        "src/include",
        "src/vendor",
        "src/vendor/glfw/include"
    }

    files {
        "src/*.cpp"
    }

    links {
        "imgui",
        "test",
        "glfw",
        "obj",
        "glad"
    }

    filter "system:Linux"
        links {
            "X11",
            "Xrandr",
            "GL",
            "GLU"
        }

    filter "system:windows"
        links {
            "opengl32.lib"
        }

    filter "configurations:Debug"
        buildoptions {
            "-g",
            "-fdiagnostics-color=always"
        }
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "Off"