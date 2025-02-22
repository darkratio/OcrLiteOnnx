# OcrLiteOnnx

### Project Download

* A complete project that integrates the source code and dependent libraries can be downloaded in Release (github)
* It can be downloaded from the Q group sharing. The compressed package file starting with Project is the source code project, for example:      Project_OcrLiteOnnx-version number.7z
* If you want to toss yourself, please continue reading this description

### Demo download (win, mac, linux)

* The compiled demo can be downloaded in the release, or downloaded in the Q group sharing
* Or Gitee download
* Or download from Github
* Executable files for each platform: linux-bin.7z, macos-bin.7z, windows-bin.7z
* jni libraries for java: linux-jni.7z, macos-jni.7z, windows-jni.7z
* Dynamic libraries for C: linux-clib.7z, macos-clib.7z, windows-clib.7z
* C dynamic library call example: OcrLiteOnnxLibTest
* C dynamic library:[OcrLiteOnnxLibTest](https://github.com/benjaminwan/OcrLiteOnnxLibTest)
* Note: The linux compilation platform is ubuntu18.04. If your linux version cannot run the demo, please compile the dependent library and complete project from the source code by yourself.

### Introduction

Super lightweight OCR PC Demo, supports onnxruntime reasoning

**Super lightweight OCR onnx branch**

This project uses the onnxruntime framework for inference

Adopt onnxruntime framework[https://github.com/microsoft/onnxruntime](https://github.com/microsoft/onnxruntime)

### 更新说明

#### 2021-10-15 update

* opencv 4.5.4
* onnxruntime 1.9.0
* 优化编译脚本和测试脚本

#### 2021-10-25 update

* fix:win编译打包C动态库缺少lib文件
* 编译c动态库添加打包include

#### 2022-06-18 update

* opencv 4.6.0
* onnxruntime 1.11.1
* 修改c lib导出方法，支持C调用

#### 2022-10-14 update

* onnxruntime 1.12.1
* 支持mt版引用库

### 模型下载

[模型下载地址](https://github.com/ouyanghuiyu/chineseocr_lite/tree/onnx/models)
下载后解压到项目根目录

```
OcrLiteOnnx/models
    ├── angle_net.onnx
    ├── crnn_lite_lstm.onnx
    ├── dbnet.onnx
    └── keys.txt
```

### [编译说明](./BUILD.md)

### 测试说明

1. 根据系统下载对应的程序包linux-bin.7z、macos-bin.7z、windows-bin.7z，并解压.
2. 把上面的模型下载，解压到第一步解压的文件夹里.
3. 终端运行run-test.sh或命令行运行run-test.bat，查看识别结果.
4. 终端运行run-benchmark.sh或命令行运行run-benchmark.bat，查看识别过程平均耗时.

### FAQ

#### windows静态链接msvc

- 作用:静态链接CRT(mt)可以让编译出来的包，部署时不需要安装c++运行时，但会增大包体积；
- 需要mt版的引用库，参考编译说明，下载mt版的库；

#### macOS缺少openmp(从1.7.0开始已不再依赖openmp)

```brew install libomp```

#### windows提示缺少"VCRUNTIME140_1.dll"

下载安装适用于 Visual Studio 2015、2017 和 2019 的 Microsoft Visual C++ 可再发行软件包
[下载地址](https://support.microsoft.com/zh-cn/help/2977003/the-latest-supported-visual-c-downloads)

#### Windows7执行错误|中文乱码

1. cmd窗口左上角-属性
2. 字体选项卡-选择除了“点阵字体”以外的TrueType字体,例如:Lucida Console、宋体
3. 重新执行bat

### 输入参数说明

* 请参考main.h中的命令行参数说明。
* 每个参数有一个短参数名和一个长参数名，用短的或长的均可。

1. ```-d --models```：模型所在文件夹路径，可以相对路径也可以绝对路径。
2. ```-1 --det```:dbNet模型文件名(含扩展名)
3. ```-2 --cls```:angleNet模型文件名(含扩展名)
4. ```-3 --rec```:crnnNet模型文件名(含扩展名)
5. ```-4 --keys```:keys.txt文件名(含扩展名)
6. ```-i --image```：目标图片路径，可以相对路径也可以绝对路径。
7. ```-t --numThread```：线程数量。
8. ```-p --padding```：图像预处理，在图片外周添加白边，用于提升识别率，文字框没有正确框住所有文字时，增加此值。
9. ```-s --maxSideLen```
   ：按图片最长边的长度，此值为0代表不缩放，例：1024，如果图片长边大于1024则把图像整体缩小到1024再进行图像分割计算，如果图片长边小于1024则不缩放，如果图片长边小于32，则缩放到32。
10. ```-b --boxScoreThresh```：文字框置信度门限，文字框没有正确框住所有文字时，减小此值。
11. ```-o --boxThresh```：请自行试验。
12. ```-u --unClipRatio```：单个文字框大小倍率，越大时单个文字框越大。此项与图片的大小相关，越大的图片此值应该越大。
13. ```-a --doAngle```：启用(1)/禁用(0) 文字方向检测，只有图片倒置的情况下(旋转90~270度的图片)，才需要启用文字方向检测。
14. ```-A --mostAngle```：启用(1)/禁用(0) 角度投票(整张图片以最大可能文字方向来识别)，当禁用文字方向检测时，此项也不起作用。
15. ```-h --help```：打印命令行帮助。

### 关于内存泄漏与valgrind

* 项目根目录的valgrind-memcheck.sh用来检查内存泄漏(需要debug编译)。
* 常见的并行库有tbb，hpx，openmp，gcd，concurrency，pthread
* 并行库的种类可以看：https://docs.opencv.org/4.x/db/d05/tutorial_config_reference.html
* 测试了openmp和pthread，目前已知这类并行库会导致检查报告中出现"possibly lost"
* opencv只做简单的图像预处理，可以完全不使用任何并行库，但需要定制编译
* onnxruntime1.6.0或之前，默认引用openmp，从1.7.0开始默认关闭openmp并使用自带的ThreadPool代码
* 阅读报告可以看出"possibly lost"发生位置均在引用的第三方库(如果使用了并行库的话)，如opencv或onnxruntime
* "possibly lost"不一定是内存泄露
* 以下3个检查报告，onnxruntime均使用v1.11.0且不引用openmp
* valgrind-memcheck-nothread.txt是opencv不使用任何并行库的检查报告。
* valgrind-memcheck-openmp.txt是opencv使用openmp的检查报告。
* valgrind-memcheck-pthread.txt是opencv使用pthread的检查报告。
* 如果opencv想定制编译不使用任何并行库，可以使用以下参数进行编译

```
-DWITH_TBB=OFF
-DWITH_HPX=OFF
-DWITH_OPENMP=OFF
-DWITH_GCD=OFF
-DWITH_CONCURRENCY=OFF
-DWITH_PTHREADS_PF=OFF
```
