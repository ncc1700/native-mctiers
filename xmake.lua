target("mctiers-re")
    add_files("src/*.c")
    if is_os("windows") then
        add_links("gdi32", "kernel32", "user32")
    else
        add_links("x11")
    end