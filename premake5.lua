workspace "bank management system"
    configurations {"Debug", "Release"}

project "bank management system"
    kind "ConsoleApp"
    language 	"C++"
    targetdir 	"bin/%{cfg.buildcfg}"
	objdir		"bin/%{cfg.buildcfg}-obj"

    files {"%{prj.location}/src/**.hpp", "%{prj.location}/src/**.cpp"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        symbols "On"