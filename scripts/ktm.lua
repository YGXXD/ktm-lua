--  MIT License
--
--  Copyright (c) 2025 有个小小杜
--
--  Created by 有个小小杜
--

print("test ktm-lua script")

function main()
    print("- test ktm-lua vec")
    local vec0 = fvec2({
        x = 128,
        y = 128,
    })
    local vec1 = fvec2({
        x = -5,
        y = -20,
    })
    local vec2 = vec0 + vec1
    print(vec2)

    print("- test ktm-lua quat")
    local quat0 = fquat({
        i = 1,
        j = 2,
        k = 3,
        r = 4,
    })
    local quat1 = fquat({
        i = 5,
        j = 6,
        k = 7,
        r = 8,
    })
    local quat2 = quat0 * quat1
    print(quat2)
end

main()