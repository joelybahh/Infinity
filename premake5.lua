workspace "Infinity"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Infinity/vendor/GLFW/include"

include "Infinity/vendor/GLFW"

project "Infinity"
	location "Infinity"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "infpch.h"
	pchsource "Infinity/src/infpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"${IncludeDir.GLFW}"
	}

	links 
	{
		"GLFW",
		"opengl32.lib" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"INF_PLATFORM_WINDOWS",
			"INF_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "INF_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "INF_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "INF_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Infinity/vendor/spdlog/include",
		"Infinity/src";
	}

	links
	{
		"Infinity"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"INF_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "INF_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "INF_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "INF_DIST"
		optimize "On"