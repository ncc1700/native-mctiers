set_project("nativemctiers")

set_xmakever("2.6.0")

set_languages("c11")

target("nativemctiers")
    set_kind("binary")  
    add_files("src/*.c")
    set_targetdir(".")
    add_files("src/**/*.c") 
    add_includedirs("src") 
    --add_cflags("/fsanitize=address", {force=true})
    if is_os("windows") then
        --add_cxflags("/fsanitize=address");
        add_files("resource.rc")
        add_linkdirs("lib/windows") 
        add_links("raylibdll", "raylib") 
        add_syslinks("gdi32", "winmm", "winhttp") 
    else
        --add_cxflags("-fsanitize=address");
        add_linkdirs("lib/linux") 
        add_links("libraylib.a")
        add_syslinks("curl");
    end

