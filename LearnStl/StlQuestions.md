## STL容器常见问答题  
# 1.push_back和emplace_back的区别？  
(1).两个函数均是往容器尾部添加一个元素;  
(2).若以对象元形式添加元素,两者均调用拷贝构造函数,效率一样;  
(3).若以构造函数参数形式添加,则有:  
  a.push_back会先调用对应的构造函数,生成临时对象然后调用拷贝构造函数添加元素;  
  b.emplace_back直接调用对应的构造函数就地构造元素,省略临时对象的拷贝和析构过程,效率更高。  
4.本质:参数不同:push_back的参数是左值和右值引用,emplace_back是参数包


# 2.容器resize和reserve的区别？  
(1).resize回会改变容器的size和capacity且会，reserve只改变capacity  
(2).resize的使用有三种情况：  
   a. 参数n < v.size()时，结果是容器v的size减小到n，删除n之后的元素；  
   b.v.size() < 参数n < v.capacity()，结果是容器v的size增加到n，增加的元素值初始化为m，m省略时，增加元素值为缺省值，即默认值；  
   c.v.capacity() < 参数n，结果是先增大容量capacity至n，然后初始化值，初始化方法与情况2相同，此时v中的size与capacity均发生改变。 
(3)reserve的使用情况有两种：  
   a.参数n < v.capacity()时，size与capacity均不发生改变；  
   b.参数n > v.capacity()时，此时会重新分配一块空间，使得capacity扩容至n，size不发生改变。  