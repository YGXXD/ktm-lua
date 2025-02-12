print("test ktm-lua script")

vec1 = fvec3(1, 2, 3)
print(vec1)

vec2 = fvec3(5)
vec2.x = 10
print((vec1 + vec2)[2])
print(vec2 - 1)
print(vec1 * vec2)
print(vec1 / vec2)

print(vec1 == vec2)