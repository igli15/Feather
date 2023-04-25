project "Feather"

	location("../../" .. buildFilesLocation)
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	
	targetdir ("bin/" .. outputDir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{ 
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c"
	}

	removefiles 
	{
		"%{prj.name}/src/main.cpp" 
	}

	includedirs
	{
		"%{prj.name}/src",
	}

	filter "system:windows"
		cppdialect "C++17"
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
