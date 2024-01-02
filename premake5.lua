-- premake5.lua
workspace "Cherno"
    configurations { "Debug", "Release" }
    platforms { "Linux", "Windows" }

outputdir = ""

IncludeDir = {}
IncludeDir["vendor"] = "vendor/"
IncludeDir["include"] = "include/"

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
        "obj"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
    
    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "Off"

project "imgui"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }
    
    targetdir "lib"
    objdir "objects"

    files {
        "src/vendor/imgui/*"
    }

project "test"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    includedirs {
        "src/vendor",
        "src/include",
        "src/vendor/glad/include"
    }

    targetdir "lib"
    objdir "objects"

    files {
        "src/tests/*.cpp",
        "src/test/*.hpp",
        "src/vendor/glad/src/glad.c"
    }

project "glm"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    targetdir "lib"
    objdir "objects"

    files {
        "src/vendor/glm/*"
    }

project "stbi"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    targetdir "lib"
    objdir "objects"

    files {
        "src/vendor/stb_image/*"
    }

project "obj"
    kind "SharedLib"
    language "C++"

    buildoptions {
        "-g",
        "-fdiagnostics-color=always"
    }

    targetdir "lib"
    objdir "objects"

    includedirs {
        "src/vendor",
        "src/vendor/glad/include"
    }

    links {
        "stbi"
    }

    files {
        "src/include/*.cpp",
        "src/include/*.hpp"
    }