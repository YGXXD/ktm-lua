--  MIT License
--
--  Copyright (c) 2025 有个小小杜
--
--  Created by 有个小小杜
--

print("test ktm-lua script")

function main()
    print("- test ktm-lua vec")
    print(getmetatable(fvec2))
    local vec0 = fvec2({
        x = 128,
        y = 128,
    })
    local vec1 = fvec2({
        x = -5,
        y = -20,
    })
    local vec2 = vec0 + vec1
    print("-- " .. vec2.x .. ", " .. vec2.y)
end

main()