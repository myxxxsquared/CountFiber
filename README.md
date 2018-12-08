# CountFiber

数出图中光纤（亮斑）的个数，并保存为ROOT的TTree格式。

## 需求

OpenCV core imgproc highgui flann imgcodecs

ROOT cern

## 生成和执行

> mkdir build
> cd build
> cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
> make -j4
> ./Count
> root fiber.root
>    new TBrowser();


