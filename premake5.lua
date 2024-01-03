-- premake5.lua
workspace "Cherno"
    configurations { "Debug", "Release" }
    platforms { "Linux", "Windows" }

group "Dependencies"
    include "src/include"
    include "src/vendor/glad"
    include "src/tests"
    include "src/vendor/imgui"
    include "src/vendor/stb_image"
    include "src/vendor/glm"
group""

project "Application"
    kind "ConsoleApp"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    targetdir ""
    objdir "objects"

    includedirs {
        "src/include",
        "src/vendor"
    }

    files {
        "src/*.cpp"
    }

    links {
        "imgui",
        "test",
        "GLU",
        "GL",
        "glfw",
        "obj",
        "glad"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "Off"