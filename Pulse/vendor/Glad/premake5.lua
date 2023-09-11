project "Glad"
	kind "StaticLib"
  	language "C"

	targetdir ("bin/" .. outputDirectory .. "/%{prj.name}")
  	objdir ("bin-int/" .. outputDirectory .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
    }

	includedirs
	{
		"include"
	}

	filter "system:windows"
      		systemversion "latest"
      		staticruntime "off"

	filter "configurations:Release"
		runtime "Release"
		staticruntime "off"
		optimize "on"