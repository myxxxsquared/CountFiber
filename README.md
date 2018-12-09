# CountFiber

数出图中光纤（亮斑）的个数，并保存为ROOT的TTree格式。

## 代码说明

main函数在CountLight.cpp中，其余函数在对应的名称当中。

## 需求

OpenCV core imgproc highgui flann imgcodecs

ROOT cern

## 生成

```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
make -j4
```

## 执行

``
$ ./Count
$ root fiber.root
[1] new TBrowser();
``
