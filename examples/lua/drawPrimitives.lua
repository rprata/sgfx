sgfx = require("sgfx")

ret, err = sgfx.init()
if ret == true then
    local desc = {
        width = -1,
        height = -1, 
        color = 0x000000FF,
        type = 0,
        buffer = 1
    }
    surface, err = sgfx.create_surface(desc)
    print(surface, err)
    sgfx.close()
else 
    print(err)
end
