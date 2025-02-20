--  MIT License
--
--  Copyright (c) 2025 有个小小杜
--
--  Created by 有个小小杜
--

print("test ktm-lua script")

function main()
    print("- test ktm-lua vec")
    local vec0 = fvec4(1, 2, 3, 4)
    local vec1 = fvec4(5, 6, 7, 8)
    local vec2 = vec0 + vec1
    print("-- " .. tostring(vec2))
    print("-- " .. vec2.x .. ", " .. vec2.y .. ", " .. vec2.z .. ", " .. vec2.w)
    print("-- " .. vec2[1] .. ", " .. vec2[2] .. ", " .. vec2[3] .. ", " .. vec2[4])
    print("-- " .. tostring(vec2 + vec2))
    print("-- " .. tostring(vec2 + 2))
    print("-- " .. tostring(2 + vec2))
    print("-- " .. tostring(vec2 - vec2))
    print("-- " .. tostring(vec2 - 2))
    print("-- " .. tostring(vec2 * vec2))
    print("-- " .. tostring(vec2 * 2))
    print("-- " .. tostring(2 * vec2))
    print("-- " .. tostring(vec2 / vec2))
    print("-- " .. tostring(vec2 / 2))
    print("-- " .. tostring(vec2 == vec2))
    print("-- " .. tostring(vec2 ~= vec2))
    print("-- " .. tostring(vec2 < vec2))
    print("-- " .. tostring(vec2 <= vec2))
    print("-- " .. tostring(vec2 > vec2))
    print("-- " .. tostring(vec2 >= vec2))

    print("- test ktm-lua mat")
    local mat0 = fmat3x4(vec0, vec1, vec2)
    local mat1 = fmat4x3(fvec3(3, 4, 5), fvec3(6, 7, 8), fvec3(-3, -4, -5), fvec3(-6, -7, -8))
    local mat2 = mat0 * mat1
    print("-- " .. tostring(mat2))
    print("-- " .. tostring(mat2 + mat2))
    print("-- " .. tostring(mat2 - mat2))
    print("-- " .. tostring(mat2 * mat2))
    print("-- " .. tostring(mat2 * 2))
    print("-- " .. tostring(2 * mat2))
    print("-- " .. tostring(mat2 / 2))
    print("-- " .. tostring(mat2 == mat2))
    print("-- " .. tostring(mat2 ~= mat2))
    print("-- " .. tostring(mat2 < mat2))
    print("-- " .. tostring(mat2 <= mat2))
    print("-- " .. tostring(mat2 > mat2))
    print("-- " .. tostring(mat2 >= mat2))

    print("- test ktm-lua quat")
    local quat0 = fquat(1, 2, 3, 4)
    local quat1 = fquat(5, 6, 7, 8)
    local quat2 = quat0 + quat1
    print("-- " .. tostring(quat2))
    print("-- " .. quat2.i .. ", " .. quat2.j .. ", " .. quat2.k .. ", " .. quat2.r)
    print("-- " .. quat2[1] .. ", " .. quat2[2] .. ", " .. quat2[3] .. ", " .. quat2[4])
    print("-- " .. tostring(quat2 + quat2))
    print("-- " .. tostring(quat2 - quat2))
    print("-- " .. tostring(quat2 * quat2))
    print("-- " .. tostring(quat2 * 2))
    print("-- " .. tostring(2 * quat2))
    print("-- " .. tostring(quat2 / 2))
    print("-- " .. tostring(quat2 == quat2))
    print("-- " .. tostring(quat2 ~= quat2))
    print("-- " .. tostring(quat2 < quat2))
    print("-- " .. tostring(quat2 <= quat2))
    print("-- " .. tostring(quat2 > quat2))
    print("-- " .. tostring(quat2 >= quat2))

    print("- test ktm-lua comp")
    local comp0 = fcomp(1, 2)
    local comp1 = fcomp(3, 4)
    local comp2 = comp0 + comp1
    print("-- " .. tostring(comp2))
    print("-- " .. comp2.i .. ", " .. comp2.r)
    print("-- " .. comp2[1] .. ", " .. comp2[2])
    print("-- " .. tostring(comp2 + comp2))
    print("-- " .. tostring(comp2 - comp2))
    print("-- " .. tostring(comp2 * comp2))
    print("-- " .. tostring(comp2 * 2))
    print("-- " .. tostring(2 * comp2))
    print("-- " .. tostring(comp2 / 2))
    print("-- " .. tostring(comp2 == comp2))
    print("-- " .. tostring(comp2 ~= comp2))
    print("-- " .. tostring(comp2 < comp2))
    print("-- " .. tostring(comp2 <= comp2))
    print("-- " .. tostring(comp2 > comp2))
    print("-- " .. tostring(comp2 >= comp2))
end

main()