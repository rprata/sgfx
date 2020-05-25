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
    if surface then
        res, x, y = sgfx.get_resolution(surface)
        print(x, y)
    end
    sgfx.close()
else 
    print(err)
end
