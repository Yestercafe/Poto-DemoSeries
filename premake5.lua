workspace "Poto"
	architecture "x64"
	startproject "Sandbox"
	

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Poto"
	location "Poto"
	kind "SharedLib"
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
		"%{prj.name}/vendor/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PT_PLATFORM_WINDOWS",
			"PT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PT_DIST"
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
		"Poto/vendor/spdlog/include",
		"Poto/src"
	}

	links
	{
		"Poto"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"PT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "PT_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PT_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PT_DIST"
		optimize "On"