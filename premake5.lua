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
IncludeDir["ImGui"] = "Infinity/vendor/imgui"
IncludeDir["glm"] = "Infinity/vendor/glm"

include "Infinity/vendor/GLFW"
include "Infinity/vendor/Glad"
include "Infinity/vendor/imgui"

project "Infinity"
	location "Infinity"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "infpch.h"
	pchsource "Infinity/src/infpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
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

		defines
		{
			"INF_PLATFORM_WINDOWS",
			"INF_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
	filter "configurations:Debug"
		defines "INF_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "INF_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "INF_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Infinity/src",
		"Infinity/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Infinity"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"INF_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "INF_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "INF_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "INF_DIST"
		runtime "Release"
		optimize "on"
