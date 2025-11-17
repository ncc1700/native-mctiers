set_project("nativemctiers")

set_xmakever("2.6.0")

set_languages("c11")

target("nativemctiers")
    set_kind("binary")  
    add_files("src/*.c")
    set_targetdir(".")
    add_files("src/**/*.c") 
    add_files("resource.rc")
    add_includedirs("src") 
    add_links("lib/raylibdll", "lib/raylib") 
    add_cflags("/fsanitize=address", {force=true})
    add_syslinks("gdi32", "winmm", "winhttp", "Shlwapi", "shell32", "user32", "kernel32", "msvcrt") 
    -- before_build(function (target)
    --     local result = os.run("rc resource.rc")     
    -- end)

