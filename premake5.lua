workspace "Infinity"
	architecture "x64"
	startproject "Sandbox"

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
IncludeDir["Glad"] = "Infinity/vendor/Glad/include"

group "Dependencies"
	include "Infinity/vendor/GLFW"
	include "Infinity/vendor/Glad"

group ""

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

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
	}

	links 
	{
		"GLFW",
		"Glad",
		"opengl32.lib" 
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"INF_PLATFORM_WINDOWS",
			"INF_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
		
	filter "configurations:Debug"
		defines "INF_DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "INF_RELEASE"
		buildoptions "/MD"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "INF_DIST"
		buildoptions "/MD"
		runtime "Release"
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
		buildoptions "/MDd"
		symbols "On"
		
	filter "configurations:Release"
		defines "INF_RELEASE"
		buildoptions "/MD"
		optimize "On"
		
	filter "configurations:Dist"
		defines "INF_DIST"
		buildoptions "/MD"
		optimize "On"