# 蓝目训练版策略编写指南

前言：我们提供了一套针对C++及python语言开发算法的接口，可以根据我们的标准接口规范创建自己的算法动态链接库，或者python包，进行回测训练及交易，如下是详细使用规范：

## 1.函数命名约定
指标宏语言(script)编写，为了区分内置静态函数和外部动态加载函数，对函数命名做了一些约定：  
内置函数直接以函数名称开头，比如SIN, MAX,等。  
外挂DLL函数，以关键词“DLL_”和文件名（文件名称限定字幕数字，其它字符不支持）开头，后跟”@”符号与函数，不区分大小写， 比如”dll_file@fourier”，表示dll插件file文件中的函数 fourier。  
外挂PY语言（需安装完整的PYTHON环境），以文件名（文件名称限定字幕数字，其它字符不支持）和关键词“PY_”开头，区分大小写， 比如”py_func@pyfile”，表示启动运行python的pyfile.py这个文件，并运行func这个函数。  
## 2.DLL插件的注册
在策略编辑的窗口，使用“注册DLL”按钮，如下图所示：

![image](https://github.com/blueye-com/algo-plug/blob/master/blueye_photo/%E5%9B%BE%E7%89%871.png)

点击“注册DLL”后，进入如下界面。

![image](https://github.com/blueye-com/algo-plug/blob/master/blueye_photo/%E5%9B%BE%E7%89%872.png)

如上所示，先选择导入一个已经编译测试好好了的DLL文件，导入后如果该文件是一个新的则需要注册全部函数，如果已经注册过，则会自动把原来注册的函数全部列出来。然后对该DLL的函数进行增删维护（如果要修改，可以先删除再增加）。如下图所示：

![image](https://github.com/blueye-com/algo-plug/blob/master/blueye_photo/%E5%9B%BE%E7%89%873.png)

用户添加的函数名称，系统会自动增加前缀, 格式为“DLL_” + 文件名 + “@”函数名，比如刚刚添加了一个名称为Linear_regression的函数，则系统生成的函数全名为：
DLL_ALGO_PLUGIN.DLL@LINEAR_REGRESSION，以后在脚本语言中如果需要使用该函数，则需要书写该全名，这样编译器在编译的时候会自动搜索导向到指定库文件名称的指定函数。

注意，如果导入的文件是一个非法的DLL（接口函数不存在），则会出现如下提示报错，不能通过。

![image](https://github.com/blueye-com/algo-plug/blob/master/blueye_photo/%E5%9B%BE%E7%89%874.png)

添加函数完成以后，点击“保存”按钮，即可实现了注册。
这时候再点击插入函数页面，则会在“外挂插件函数”中看见刚刚添加的这些函数。

![image](https://github.com/blueye-com/algo-plug/blob/master/blueye_photo/%E5%9B%BE%E7%89%875.png)

插件注册完成后，需要重新启动软件，才能生效，这时候打开指标编辑器，点击插入刚刚增加的函数，则会出现颜色变蓝，以及使用说明的浮动信息提示，如下图所示：

![image](https://github.com/blueye-com/algo-plug/blob/master/blueye_photo/%E5%9B%BE%E7%89%876.png)

## 3.如何在脚本语言(SCRIPT)中调用算法盒子函数
这里特别对几个重要的名词进行释义：
参数：脚本语言调用函数是传递的的每一个参数，默认是一个一维数组，比如LOG(OPEN)中的OPEN是由一系列K线开盘价的数组组成。
元素：由于每一个参数都是一个一维数组，其中的每一个值被称为元素。 一个参数由其包含的多个元素组成。
返回值：返回值默认也是一个一维数组值，其元素顺序与输入参数的元素顺序一一对应,返回值也可以成为一个返回结果元素集。
多参数：一个函数的调用，可能会传递两个以上的参数，即多参数。由于每个参数有其包含的多个元素，所以多参数的数据微观存储结构将是一个多维数组，也可以成为矩阵。

下面介绍脚本语言对于外部函数的调用规范：  
■单参数的函数脚本语言调用规范如下：
	A:=DLL_FILE1@FUNC01(CLOSE);
	如上，根据CLOSE参数，直接使用DLL_FILE@FUNC01函数计算结果，并按照与CLOSE同样的时序返回结果。

■	多参数，输入参数的个数不做限制，返回一个结果。
	B:=DLL_FILE1@FUNC03(OPEN,CLOSE,…);
	有关返回矩阵的函数调用方法，后续再增加。
  
## 4.如何使用VISUAL C++编写DLL的规范
有关DLL的编写常规规范，本文不做说明。这里只介绍一下如何定义外挂函数的接口规范，以及初始化、参数传递等方法，并且给除了基于visual c++的工程模板和一些函数编写例子。
DLL程序设计的时候，必须提供如下5个几口函数：
■初始化函数，此函数负责算法函数的名称和地址映射。
```cpp
typedef bool	(*i_init)();
```

■单变量函数，输入和输出是一个变量而非数组或者矩阵。该函数暂时保留未用。
```cpp
typedef void	(*i_dynamic_func_a)(float _arg_input, float &_arg_output);
```

■单参数函数，输入和输出都是一个一维数组，该函数可能是使用最多的一种。
```cpp
typedef void	(*i_dynamic_func_b)(std::deque<float> _arg_input, std::deque<float> &_arg_output);
```

■多参数函数，输入是多个参数，输出是一个一维数组。
```cpp
typedef void	(*i_dynamic_func_c)(std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output);
```

■矩阵函数，输入是多个参数，输出亦是多个参数。也即输入和输出均为矩阵。该函数暂时保留未用。
```cpp
typedef void	(*i_dynamic_func_d)(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);
```


脚本语言对外部函数的调用，最终底层实现了一个C++的DLL接口函数的调用，这里做一个对应关系说明：
■SCRIP和DLL之间在 单参数模式调用下的对应关系如下：  
SCRIPT语句：A:=DLL_FILE1@FUNC01(CLOSE);  
DLL接口函数如下：  
```cpp
dynamic_func_b(“DLL_FILE1@FUNC01”,  
INPUT,   
OUTPUT);  
```
参数分别为 函数名称， 以INPUT为输入参数，返回结果在OUTPUT，最后通过脚本解释器底层把OUTPUT的值赋给变量A 。  
dynamic_func_b的c++函数原型如下：  
```cpp
typedef void	(*i_dynamic_func_b)(std::deque<float> _arg_input, std::deque<float> &_arg_output);  
```

■SCRIP和DLL之间在 多参数模式调用下的对应关系如下：  
SCRIPT语句：A:=DLL_FILE1@FUNC01(ARG1,ARG2,…);  
DLL接口函数如下：  
```cpp
dynamic_func_c(“DLL_FILE1@FUNC01”,  
std::deque<INPUT>,   
OUTPUT);  
 ```
参数分别为 函数名称， std::deque<input>是一个二维数组参数，返回结果在OUTPUT，最后通过脚本解释器底层把OUTPUT的值赋给变量A .  
	dynamic_func_c的c++函数原型如下：  
  ```cpp
typedef void	(*i_dynamic_func_c)(std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output);
  ```


另外，函数增加两个一个初始化函数 bool dynamic_init(); 其主要作用是创建一个函数映射表，即每个函数的名称和其多个重载函数的地址映射。C++函数原型和指针极其映射表的定义结构如下：
  ```cpp
typedef bool	(*i_init)();
typedef void	(*i_dynamic_func_a)(float _arg_input, float &_arg_output);
typedef void	(*i_dynamic_func_b)(std::deque<float> _arg_input, std::deque<float> &_arg_output);
typedef void	(*i_dynamic_func_c)(std::deque< std::deque<float> > _arg_input, std::deque<float> &_arg_output);
typedef void	(*i_dynamic_func_d)(std::deque< std::deque<float> > _arg_input, std::deque< std::deque<float> > &_arg_output);

typedef struct  
{
	i_dynamic_func_a dynamic_func_a_;
	i_dynamic_func_b dynamic_func_b_;
	i_dynamic_func_c dynamic_func_c_;
}tag_FUNC_LIST;
```
函数初始化的编写实例如下：
  ```cpp
bool dynamic_init()
{
	tag_FUNC_LIST _func_list;
	
	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::Example01;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::Example02;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::Example03;
	g_map_functions.insert(std::make_pair("EXAMPLE0",_func_list));

	_func_list.dynamic_func_a_ = (i_dynamic_func_a)CAlgorithms::Example11;
	_func_list.dynamic_func_b_ = (i_dynamic_func_b)CAlgorithms::Example12;
	_func_list.dynamic_func_c_ = (i_dynamic_func_c)CAlgorithms::Example13;
	g_map_functions.insert(std::make_pair("EXAMPLE1",_func_list));
	
	// To do, add more functions in the following ......
	//...

	return true;
}
```
最后，用visual c++编写的DLL工程示例规范，详见algo_plugin。
