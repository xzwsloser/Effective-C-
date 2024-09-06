# 成对使用new和delete需要采取相同的形式
- 首先明确使用`new`或者`delete`的时候可以提供的形式: 比如可以提供创建一个单独对象的形式,或者提供一个可以创建一个连续空间的形式(比如使用`[]`)
- 本节的意思就是如果使用`new`开辟了一个数组空间,就需要使用`delete[]` 的方式删除调这一个空间,如果使用`new`的方式初始化了一个对象,那么就需要使用`delete`的方式释放这一个对象
- 演示`demo`:
```cpp
std::string str = new string("hello");
delete str;

int* arr = new int[10];
delete[] arr;
```
- 但是有时候需要注意使用`typedef`自定义的类型,比如利用`typedef`定义的类型如下:
```cpp
typedef std::string books[5];  // books 就是一个字符串数组
std::string* ptr = new book;
delete[] ptr; // true
```
- 总结:
  - 如果你在`new`表达式中使用`[]`,必须在相应的`delete`表达式中使用`[]`,如果你在`new`表达式中不使用`[]`,一定不要再相应的`delete`表达式中使用`[]`