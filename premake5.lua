workspace "Poto"
	architecture "x64"
	startproject "EatingSnake"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Poto/vendor/GLFW/include"
IncludeDir["Glad"] = "Poto/vendor/Glad/include"
IncludeDir["ImGui"] = "Poto/vendor/imgui"
IncludeDir["glm"] = "Poto/vendor/glm"
IncludeDir["stb_image"] = "Poto/vendor/stb_image"

include "Poto/vendor/GLFW"
include "Poto/vendor/Glad"
include "Poto/vendor/imgui"

project "Poto"
	location "Poto"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ptpch.h"
	pchsource "Poto/src/ptpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
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
			"PT_PLATFORM_WINDOWS",
			"PT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PT_DIST"
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
		"Poto/vendor/spdlog/include",
		"Poto/src",
		"Poto/vendor",
		"Poto/vendor/imgui/bin/Debug-windows-x86_64/ImGui",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Poto"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PT_DIST"
		runtime "Release"
		optimize "on"
		
project "EatingSnake"
	location "EatingSnake"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
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
		"Poto/vendor/spdlog/include",
		"Poto/src",
		"Poto/vendor",
		"Poto/vendor/imgui/bin/Debug-windows-x86_64/ImGui",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Poto"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PT_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PT_DIST"
		runtime "Release"
		optimize "on"