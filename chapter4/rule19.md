# 设计class犹如设计type
- 在`C ++`中设计一个`class`就好像设计一个`type`,所以必须慎重,需要考虑如下问题:
1. 新的`type`类型应该如何创建和销毁? (见`chapter8`)
2. 对象的初始化和对象的赋值之间该有什么差别? 注意赋值和初始化的差别(见`rule4`)
3. 新的`type`对象如何别使用值的方式传递,意味着什么?
4. 什么是`type`的合法值? (规范拷贝构造和`setter`等方法)
5. 你的新的`type`需要配合某一个继承图系? (比如你的`type`对于继承你的类有那些影响?)
6. 你的新的`type`需要怎样的类型转换? (可以参考条例`15`)
7. 什么样的操作符和函数对于这一个新的`type`而言比较合理?
8. 什么样的标准函数应该驳回?(见条款`06`)
9. 谁该采用新的`type`成员?
10. 你的新的`type`有多么一般化?
11. 你真的需要一个`type`吗? (如果不需要,可以使用成员函数替代)
- 总结:
  - `Class`的设计犹如设计`type`,在定义一个新的`type`之前,请确定你已经考虑过本条款覆盖的所有讨论主题了