workspace "Feather"
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

	location "Feather"

	--in case we want to make a dll user "Shared lib" instead of "ConsoleApp"
	--kind "SharedLib"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c"
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CR_DEBUG"
		symbols "On"


	filter "configurations:Release"
		defines "CR_RELEASE"
		optimize "On"


	filter "configurations:Dist"
		defines "CR_DIST"
		optimize "On"
