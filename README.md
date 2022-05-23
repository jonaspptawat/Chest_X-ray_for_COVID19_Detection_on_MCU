# Chest X-ray for COVID19 Detection on MCU

A very small DL model (0.3MB) that be able to run on most microcontrollers and other memory constrained devices. 
It can detect a COVID-19 via Chest x-ray images (96x96) using TensorFlow Lite C++ API.
However, the dataset that i use for training this DL model is from [this kaggle](https://www.kaggle.com/datasets/andyczhao/covidx-cxr2)(Thanks for this dataset to make this project happen). Moreover, i also have a notebook where i train this DL model which you can find [Here](https://www.kaggle.com/code/jonaspptawat/covid-x-ray-using-small-model-0-3mb-83-acc).

## Generate TFLite micro library for your specific Microcontroller

First of all, you have to create a directory where your code will be stored.
```console
mkdir chestx_proj && cd chestx_proj
```
Followingly, you need to clone a TFLite-micro repo using git clone.
```console
git clone https://github.com/tensorflow/tflite-micro.git && cd tflite-micro
```
Next, you will have to run a Makefile to create a project.
```console
make -f tensorflow/lite/micro/tools/make/Makefile generate_projects
```
However, you can do this for your particular Microcontroller. To do this, you can set your device name in TARGET.
```console
make -f tensorflow/lite/micro/tools/make/Makefile TARGET=<Your device name> hello_world_bin
```
For example
```console
make -f tensorflow/lite/micro/tools/make/Makefile TARGET=sparkfun_edge hello_world_bin
```
Finally, the hello_world_project will be created in the following path
```console
tensorflow/lite/micro/tools/make/gen/<your device name>/prj/hello_world
```
Then, you can copy the tflite folder to your main directory.

## To run this project
You can either use my application code or write you own code. Here is the guide, if you want to rewrite by yourself.

### image_provider.cpp and image_provider.h
In these two file, all it does just get the dummy image from GetDummyImage function which you can rewrite it to get the image from your own camera module.
But, you have to remember that the shape of the input image must be 96x96x1 before it is fed in to interpreter.

### model_setting.h
This header stores all the important things from model training process such as width, height and channel of the input image.

### model.cpp and model.h
For these two files, they are the essential key that we must to have because it is DL model from training process.
There will be only huge array (Our model) and size of the model in bytes.

### main.cpp
This file is where our application are implemented which you can modify in your own way.

### resolver.h
For this last file, it declares Register variable for adding our Ops in main.cpp.

## Thank you !
