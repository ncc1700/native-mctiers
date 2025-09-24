set_project("nativemctiers")

set_xmakever("2.6.0")

set_languages("c11")

target("nativemctiers")
    set_toolchains("msvcstandalone")
    set_kind("binary")  
    add_files("src/*.c")
    set_targetdir(".")
    add_files("src/**/*.c") 
    add_files("resource.rc")
    add_includedirs("src") 
    add_syslinks("gdi32", "winmm", "winhttp", "Shlwapi", "shell32", "user32", "kernel32", "msvcrt", "ntdll") 
    -- before_build(function (target)
    --     local result = os.run("rc resource.rc")     
    -- end)


toolchain("msvcstandalone")
    set_kind("standalone")
    set_toolset("cc", "cl");
    set_toolset("ld", "link")
    set_toolset("mrc", "rc")
toolchain_end();