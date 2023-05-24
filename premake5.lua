workspace "Pulse"
	architecture "x86_64"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

outputDirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pulse"
	location "Pulse"
	kind "SharedLib"

	language "C++"

	targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
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
		optimize "On"

	filter "configurations:Release"
		defines "PLS_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PLS_DIST"
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