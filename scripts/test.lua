print("测试 C++ 导出的函数")
print("调用 cpp_add 函数:")
result = cpp_add(10.5, 20.7)
print("10.5 + 20.7 =", result)

-- 测试更多数值
print("\n测试更多数值:")
print("5 + 3 =", cpp_add(5, 3))
print("-10 + 15 =", cpp_add(-10, 15))

-- 测试向量操作
print("\n测试向量操作:")
v1 = fvec(1, 2, 3)
v2 = fvec(4, 5, 6)
print("v1 =", v1)
print("v2 =", v2)
v3 = v1 + v2
print("v1 + v2 =", v3) 