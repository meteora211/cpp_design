## TypeLists

### 编译期迭代
编译期无法进行迭代, 编译期特点：
- template 偏特化充当if/else
- integer calculation是不可变的
- typedef 可以被视为 named type constant, 也是定义之后不可变。

而迭代是持有一个迭代器并改变它，直到某个条件吻合。而编译期都是不可变的，所以只能采用递归。

