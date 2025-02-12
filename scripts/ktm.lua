print("test ktm-lua script")

vec0 = svec4(1, 2, 3, 4)
print(3 * vec0)

vec1 = fvec3(1, 2, 3)
print(vec1)

vec2 = fvec3(5)
vec2.x = 10
print((vec1 + vec2)[2])
print(vec2 - 1)
print(vec1 * vec2)
print(vec1 / vec2)

print(vec1 < vec2)
print(vec1 > vec2)
print(vec1 <= vec2)
print(vec1 >= vec2)
print(vec1 == vec1)
print(vec1 ~= vec2)