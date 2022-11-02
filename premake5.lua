workspace "Hazel"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Samples
group "Samples"
	include "Samples"
group ""

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]			= "%{wks.location}/Hazel/vendor/GLFW/include"
IncludeDir["Glad"]			= "%{wks.location}/Hazel/vendor/Glad/include"
IncludeDir["ImGui"]			= "%{wks.location}/Hazel/vendor/imgui"
IncludeDir["glm"]			= "%{wks.location}/Hazel/vendor/glm"
IncludeDir["stb_image"]		= "%{wks.location}/Hazel/vendor/stb_image"
IncludeDir["entt"]			= "%{wks.location}/Hazel/vendor/entt/include"
IncludeDir["yaml_cpp"]		= "%{wks.location}/Hazel/vendor/yaml-cpp/include"

group "Dependencies"
	include "Hazel/vendor/GLFW"
	include "Hazel/vendor/Glad"
	include "Hazel/vendor/imgui"
	include "Hazel/vendor/yaml-cpp"
group ""

include "Hazel"
include "Hazelnut"
include "Sandbox"

