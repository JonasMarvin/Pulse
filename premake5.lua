workspace "Pulse"
	architecture "x86_64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Pulse/vendor/GLFW/include"

include "Pulse/vendor/GLFW"

project "Pulse"
	location "Pulse"
	kind "SharedLib"

	language "C++"

	targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Pulse/src/pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines{
			"PLS_PLATFORM_WINDOWS",
			"PLS_BUILD_DLL"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..  outputDirectory .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "PLS_DEBUG"
		staticruntime "off"
		runtime "Debug"
		optimize "On"

	filter "configurations:Release"
		defines "PLS_RELEASE"
		staticruntime "off"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PLS_DIST"
		staticruntime "off"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"

	language "C++"

	targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Pulse/vendor/spdlog/include",
		"Pulse/src"
	}

	links{
		"Pulse"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "On"
		systemversion "latest"

		defines{
			"PLS_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "PLS_DEBUG"
		optimize "On"

	filter "configurations:Release"
		defines "PLS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PLS_DIST"
		optimize "On"