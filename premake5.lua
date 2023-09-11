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
IncludeDir["Glad"] = "Pulse/vendor/Glad/include"
IncludeDir["ImGui"] = "Pulse/vendor/imgui"

include "Pulse/vendor/GLFW"
include "Pulse/vendor/Glad"
include "Pulse/vendor/imgui"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "c++20"
		staticruntime "Off"
		systemversion "latest"

		defines{
			"PLS_PLATFORM_WINDOWS",
			"PLS_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..  outputDirectory .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "PLS_DEBUG"
		staticruntime "off"
		runtime "Debug"
		optimize "Off"

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
		staticruntime "Off"
		systemversion "latest"

		defines{
			"PLS_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "PLS_DEBUG"
		staticruntime "off"
		runtime "Debug"
		optimize "Off"

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