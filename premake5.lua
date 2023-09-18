workspace "Pulse"
	architecture "x86_64"
	startproject "Sandbox"

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
IncludeDir["glm"] = "Pulse/vendor/glm"

group "Dependencies"
	include "Pulse/vendor/GLFW"
	include "Pulse/vendor/Glad"
	include "Pulse/vendor/imgui"

group ""

project "Pulse"
	location "Pulse"
	kind "StaticLib"
	language "C++"
	cppdialect "c++20"
	staticruntime "on"

	targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Pulse/src/pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/imgui/backends/imgui_impl_glfw.cpp",
		"%{prj.name}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
	}

	defines{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"PLS_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "PLS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PLS_RELEASE"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "c++20"
	staticruntime "on"

	targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Pulse/vendor/spdlog/include",
		"%{IncludeDir.glm}",
		"Pulse/src",
		"Pulse/vendor"
	}

	links{
		"Pulse"
	}

	filter "system:windows"
		systemversion "latest"

		defines{
			"PLS_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "PLS_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PLS_RELEASE"
		runtime "Release"
		optimize "on"
