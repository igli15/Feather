workspace "Feather"

	location("PREMAKE_GENERATED_FILES/")
	
	architecture "x64"
	startproject "Feather"
	configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

	outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Feather"

	location("PREMAKE_GENERATED_FILES/")

	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
		"src/**.c"
	}

	includedirs
	{
		"src",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "RELEASE"
		optimize "On"


	filter "configurations:Dist"
		defines "DIST"
		optimize "On"
