--  MIT License
--
--  Copyright (c) 2025 有个小小杜
--
--  Created by 有个小小杜
--

print("test ktm-lua script")

local function main()
    print("- test ktm-lua vec: ")
    local vec0 = fvec2.new({
        x = 128,
        y = 128,
    })
    local vec1 = fvec2.new({
        x = -5,
        y = -20,
    })
    print("  "..tostring(vec0 + vec1))
    print("  "..tostring(vec0 - vec1))
    print("  "..tostring(vec0 * vec1))
    print("  "..tostring(vec0 / vec1))
    print("  "..tostring(vec0 == vec1))
    print("  "..tostring(vec0 ~= vec1))
    print("  "..tostring(vec0 <= vec1))
    print("  "..tostring(vec0 >= vec1))
    print("  "..tostring(vec0 < vec1))
    print("  "..tostring(vec0 > vec1))
    vec0.x = 100
    vec0.y = -150
    print("  "..tostring(-vec0))

    print("- test ktm-lua quat: ")
    local quat0 = fquat.new({
        i = 1,
        j = 2,
        k = 3,
        r = 4,
    })
    local quat1 = fquat.new({
        i = 5,
        j = 6,
        k = 7,
        r = 8,
    })
    print("  "..tostring(quat0 + quat1))
    print("  "..tostring(quat0 - quat1))
    print("  "..tostring(quat0 * quat1))
    print("  "..tostring(quat0 == quat1))
    print("  "..tostring(quat0 ~= quat1))
    print("  "..tostring(quat0 <= quat1))
    print("  "..tostring(quat0 >= quat1))
    print("  "..tostring(quat0 < quat1))
    print("  "..tostring(quat0 > quat1))
    quat0.i = 0.5
    quat0.j = -0.5
    quat0.k = -0.5
    quat0.r = 0.5
    print("  "..tostring(-quat0))

    print("- test ktm-lua comp: ")
    local comp0 = fcomp.new({
        r = 1,
        i = 2,
    })
    local comp1 = fcomp.new({
        i = 3,
        r = 4,
    })
    print("  "..tostring(comp0 + comp1))
    print("  "..tostring(comp0 - comp1))
    print("  "..tostring(comp0 * comp1))
    print("  "..tostring(comp0 == comp1))
    print("  "..tostring(comp0 ~= comp1))
    print("  "..tostring(comp0 <= comp1))
    print("  "..tostring(comp0 >= comp1))
    print("  "..tostring(comp0 < comp1))
    print("  "..tostring(comp0 > comp1))
    comp0.i = 0.5
    comp0.r = -0.5
    print("  "..tostring(-comp0))

    print("- test ktm-lua mat: ")
    local mat0 = fmat2x3.new({
        col1 = fvec3.new({
            x = 2,
            y = 2,
            z = 2,
        }),
        col2 = fvec3.new({
            x = 5,
            y = 6,
            z = 7,
        })
    })
    local mat1 = fmat3x2.new({
        col1 = fvec2.new({
            x = 1,
            y = 2,
        }),
        col2 = fvec2.new({
            x = 3,
            y = 4,
        }),
        col3 = fvec2.new({
            x = 2,
            y = 1,
        }),
    })
    print("  "..tostring(mat0 + mat0))
    print("  "..tostring(mat0 - mat0))
    print("  "..tostring(mat0 * mat1))
    
    mat0.col1.x = 0
    mat0.col1.y = 1
    mat0.col1.z = 1
    mat0.col2.x = 0
    mat0.col2.y = 0
    mat0.col2.z = 1
    print("  "..tostring(mat0))

    mat0 = fmat4x4.new({
        col1 = fvec4.new({
            x = 1,
            y = 2,
            z = 3,
            w = 4,
        }),
        col2 = fvec4.new({
            x = 5,
            y = 6,
            z = 7,
            w = 8,
        }),
        col3 = fvec4.new({
            x = 1,
            y = 2,
            z = 3,
            w = 4,
        }),
        col4 = fvec4.new({
            x = 5,
            y = 6,
            z = 7,
            w = 8,
        }),
    })
    mat1 = mat0 * mat0
    print("  "..tostring(mat1))
    print("  "..tostring(mat0 == mat1))
    print("  "..tostring(mat0 ~= mat1))
    print("  "..tostring(mat0 <= mat1))
    print("  "..tostring(mat0 >= mat1))
    print("  "..tostring(mat0 < mat1))
    print("  "..tostring(mat0 > mat1))
end

main()