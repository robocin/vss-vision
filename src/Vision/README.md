## RoboCIn VSSL - Vision Module

### Table of contents

1. [Description](#description)

2. [Repository Tree](#repository-tree)

3. [Architecture](#architecture)

4. [Dependencies](#dependencies)

5. [Vision Team](#vision-team)

### Description

This is the Vision module of the RoboCIn VSSL Software. It is responsible to process the camera frames and retreive **position and velocity** of all robots in field using Image Processing and Computacional Vision algorithms, creating a abstraction . 


### Repository Tree

~~~
Vision
|
*--> Vision.h
|
*--> Vision.cpp
|
+--> Position Processing
|   |
|   +--> Headers
|   |
|   *--> Kmeans.cpp
|   |
|   *--> GenericTracking.cpp
|   |
|   *--> WhereAreThose.cpp
|	|
|	(...)
|       
+--> Image Processing
|   |
|   +--> Headers
|   |
|   *--> LUTSegmentation.cpp
|   |
|   *--> WarpCorrection.cpp
|   |
|   *--> Preprocessing.cpp
|	|
|	(...)
|       
*--> Models.cpp
|
+--> Parameters
	|
	(...)

~~~

### Architecture

The Vision module was designed to facilitate the addition of new Filters and algorithms, and also provide a good level of abstraction to external modules. For that, we have the Vision object as Facade, with simple methods to get position and debug frames of the module, and two interfaces to implement algorithms that will be part of some part of the frame processing. The Vision processing is composed by the following steps:

1. **Image Correction:** Aims to correct camera distortions such as shearing, radial distortion and making easier to get real points from image points.

2. **Image Filtering:** Aims to improve the image quality, facilitating further processing. One goal of the image filtering step is minimizing the image noise.

3. **Segmentation:** Aims to group similar pixels tagging them with the same tag (Usually the tag is represented as a color in RGB). Non relevant elements will be tagged together usually with a black color. 

4. **Tracking and Detection:** The detect part aims to, given the segmented frame, identify similar region as a entity and extract the **position and velocity** informations. The tracking part aims to, given previous detection points, accelerate the detection process of the same points in subsequent frames.

The vision module conforms to the following architecture:

![Architecture](http://i64.tinypic.com/fu460o.png)

### Interacting with Vision module

To interact with the Vision module from other modules, you just to get a instance of Vision, set a frame to processing and call ``update()`` to recieve 
a Entities vector with the position of all robots at the moment. The following example shows a program that update continuously and print the position of the first entity: 

```c++
#include <iostream>
#include "Vision.hpp"
#include <opencv2/opencv.hpp>


int main(){
	
	VideoCapture cap(0);
	if(!cap.isOpened())  
        return -1;

	Vision * visionInstance = Vision.singleton();
	Entities* robotsPosition;
	Mat frame;

	while (1) {
		cap >> frame;
		visionInstance.setFrame(frame);

		robotsPositions = visionInstance->update();

		std::cout << "(" << robotsPositions[0].position.first << "," << robotsPositions[0].position.second << ")" << std::endl;
	}
	
	return 0;
}
```

If you want to get some debug frame, you can get using one of the **get_SomeStep_Frame()** . For more information, consult documentation.

### Development

To develop to the vision module, you probably will want to create a new class that inherit from ``PositionProcessing`` or ``ImageProcessing`` . **Do not make two differents algorithms implementations in one class, or make algorithms implementations inside the ``update()`` on Vision class.** This breaks the Architecture's cohesion and impairs the maintainability. The logic to implement a new process is simple:

* Create a **Position Processing** subclass if your algorithm receive a ``cv::Mat`` and will return `Entities*`. 

* Create a **Image Processing** subclass if your algorithm receive a ``cv::Mat`` and will return another ``cv::Mat``.

For example, let's say i want to create a **Warp Correction** implementation. You will need to create a WarpCorrection.hpp like:

```c++

	class WarpCorrection : ImageProcessing {
		//here other methods and atributes you need

	}

```

And in you .cpp file you will need at least this:

```c++
	void WarpCorrection::init(map <std::string, int> parameters) {
		//set your parameters here

	}

	cv::Mat WarpCorrection::run(cv::Mat frame){
		//here you will do your processing
		return frame;
	}

	void WarpCorrection::setup(string parameter, int value) {
		//here you do changes in parameters

	}

	cv::Mat WarpCorrection::getDebugFrame(cv::Mat frame){
		//return a debugFrame to let other people see whats going on :D
		return frame;
	}

```

To set your algorithm as one of the steps, you just need to place one instance of your class to the correct atribute in vision. For example:

```c++
	Vision::Vision(){
		//some code here

		this->imageCorrection = new WarpCorrection();

		map <string, int> parameters;
		//set your parameters here

		this->imageCorrection.init(parameters);
	}
```

### Dependencies

The dependencies direct related with this module include:

* OpenCV (Version 2.4.11)

### Vision Team

* Carlos Pena
* Heitor Rapela
* Iraline Nunes
* José Nilton
* Marvson Allan

