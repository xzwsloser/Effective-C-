# 为了异常安全而努力是值得的
- 首先给出一段代码:
```cpp
class PrettyMenu {
public:
    void changeBackground(std::istream& imgSrc);
private:
    Mutex mutex;    // 表示需要使用的互斥锁
    Image* bgImage;
    int imageChanges;
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    lock(&mutex);
    delete bgImage;
    ++imageChanges;  // 表示改变图片转换的时间
    bgImage = new Image(imgSrc);
    unlock(&mutex);
}
```
- 从异常安全性的角度来说,上述代码没有满足条件,异常安全性的两个条件:
  - 不泄露任何资源(一旦`new Image`出现异常就会导致`unlock`不会执行也就是资源无法被释放)
  - 不允许数据败坏(如果`new Image(imgSrc)`失败就会导致`bgImage`指向一个被删除的对象,并且成员`imageChanges`已经被累加了)
- 对于资源泄漏问题,可以使用`RAII`类来解决,比如使用如下的`RAII`类来管理`mutex`:
```cpp
class Lock {
public:
    Lock(Mutex* mutex): spm(mutex , unlock) 
    {
        lock(mutex);
    }
private:
    shared_ptr<Mutex> spm;
    void unlock(Mutex* mutex)
    {
        unlock(mutex);
    }
};
```
- 接下来解决数据败坏的问题,异常安全函数一般会提供如下三个保证之一:
  - 基本承诺: 如果异常被抛出,程序内的任何事物仍然保持在有效状态下,没有任何对象和数据结构因此败坏,所有对象都处于一种内部前后一致的状态之下(比如所有的`class`约束条件都获得满足),但是程序的现实状态恐怕不可预料(也就是不影响用户的体验但是隐藏底层的细节)
  - 强烈保证: 如果异常被抛出,程序状态不会发生改变,调用这样的函数需要这样的认知: 如果函数成功,就是完全成功,如果函数失败,程序就会回复到"函数调用之前"的状态(和基本承诺相比,其实这一种只有两种状态(成功或者失败),但是基本承诺拥有多种状态(只要状态处于合法状态之中))
  - 不抛出保证: 承诺绝对不抛出异常,因为他们总是能够完成他们原先承诺的功能,但是不一定"空白的异常明细"就是表示不抛出异常保证,比如如下函数中:
```cpp
int do_some() throw() ;  // 虽然有异常明细,但是表示如果异常抛出就会很严重,有想象不到的函数被调用
```
- 三个保证中只用选择一个,不抛出保证往往难以实现,这里可以尽量采用强烈保证的方式
- 对于最上面的代码,实现强烈保证的方式很简单(利用一个`RAII`类来管理`bgImage`即可)
- 改进代码如下:
```cpp
class PrettyMenu {
public:
    void changeBackground(std::istream& imgSrc);
private:
    Mutex mutex;    // 表示需要使用的互斥锁
    shared_ptr<Image> bgImage;
    int imageChanges;
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Lock m1(&mutex);
    bgImage.reset(new Image(imageSrc));
    ++ imageChanges;
}
```
- 但是这一种做法仍然美中不足,比如如果把`imageSrc`的源头移除,那么就会导致虽然初始化成功,但是还是无法找到图像的问题
- 所以为了实现强烈保证,就可以使用`copy and swap`技术来实现强烈的异常保证:
  - 首先拷贝需要改变的事物的副本
  - 对于副本中的数据进行修改
  - 最后把副本和原来的数据进行交换
- 这样就可以保证如果失败就会回滚到原来的状态,如果成功就会交换成功
- `swap`的实现之前说过:
  - 对于普通的类: 在类中实现`swap`方法(`using std::swap`),之后特化`std::swap`即可
  - 对于类模板: 在类模板中实现`swap`方法(使用函数重载的方式),之后在这一个类的命名空间中特化`swap`即可
- 所以改进之后的代码如下(最好把需要改变(也就是复制的)元素看成结构体):
```cpp
struct PMImpl {
    shared_ptr<Image> bgImage;
    int imageChanges;
};

class PrettyMenu {

private:
    Mutex mutex;
    shared_ptr<PMImpl> pImpl;
};

void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    using std::swap;
    Lock  m1(&mutex);
    shared_ptr<PMImpl> pNew(new PMImpl(*pImpl)); // 此时 shared_ptr 重载了 * 可以当成指针使用
    (pNew -> bgImage).reset(new Image(imgSrc));
    pnew -> imageChanges ++;
    swap(pnew , pImpl);
}
```
- 这里利用结构体封装`PMImpl`的原因就是使用`private`已经保证了数据的封装性
- 但是利用`copy and swap`技术之后仍然不一定保证异常安全性,比如如下代码中:
```cpp
void some_func()
{
    ...
    f1();
    f2();
    ...
}
```
- 如果`f1`或者`f2`没有提供强烈的异常保证(甚至提供了强烈的异常保证),那么`some_func`函数还是有可能不会提供强烈的异常保证
- 如果函数只是操作局部性状态,例如以上函数只是影响调用者的状态那么提供强烈保证较为容易,但是如果同时影响各种不同的状态(比如其中一个函数影响数据库的状态)还是那一保证强烈的一致性

- 所以程序的异常安全性只要其中有一段不是异常安全的代码就会被推翻
- 异常安全性的实现: 首先是 "以对象管理资源",那么就可以组织资源泄漏,然后就是挑选三个"异常安全保证"中的某一个实现于你所写的每一个函数上,你需要挑选"现实可以实施"条件下的最强烈等级,只有当你的函数调用了传统代码才别无它选的把它设置为"无任何保证"

- 总结:
  - 异常安全函数即使发生异常也不会泄漏资源或者允许任何数据结构败坏,这样的函数区分三种可能的保证: 基本型,强烈性和不抛出异常型
  - 强烈保证往往可以通过"`copy and swap`"实现,但是"强烈保证"并非对于所有函数都可以实现或者具备现实意义
  - 函数提供的"异常安全保证"通常最高只是等于各个函数中"异常安全保证"最大的哪一个