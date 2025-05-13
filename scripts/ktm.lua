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
    local vec0 = fvec2()
    local vec1 = fvec2()
    vec0.x = 128
    vec0.y = 128
    vec1.x = -5
    vec1.y = -20
    local vec2 = vec0 + vec1
    print("-- " .. vec2.x .. ", " .. vec2.y)
end

main()