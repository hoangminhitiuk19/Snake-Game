# Snake Game
OpenGL is a 2D and 3D graphics API that provides a cross-platform application programming interface for a wide variety of computer platforms. It is operating system independent and has a transparent network. Application developers use it to develop high-performing and visually compelling graphics software applications.

Prerequisites:
Visual Studio 2019 (Download)
Installation:
Now let’s jump into the setup of OpenGL. To do so follow the below steps:

Step 1: First we have to download Visual Studio 2019 for Windows 10 (or the latest version that works with your computer). In this guide, we will talk about Visual Studio 2019 version.

Step 2: Now we have installed Visual Studio 2019 from its downloaded .exe file with the Windows installer.
![visual-studio-installer](https://github.com/hoangminhitiuk19/Snake-Game/assets/75331479/de27f969-1433-419b-8750-76b89017b3cb)

Select Visual Studio Community 2019 and click Modify, now select  the required components as shown below image and click Install while Downloading :
 
![workloads](https://github.com/hoangminhitiuk19/Snake-Game/assets/75331479/8900f548-4e45-4660-aab1-b3081ab98fbe)

It will take some time after it will be complete restart the computer after the installation takes place.

Step 3: Now download the GLUT header file,.LIB, and . DLL files are all pre-compiled for Intel platforms, you can simply download the glutdlls37beta.zip file from the website.

The file inside the folder looks like this:
 
![glut-files](https://github.com/hoangminhitiuk19/Snake-Game/assets/75331479/07bc893a-7017-4bf9-b2c3-6feb41ea6a15)



Step 4: After this, we have to copy the file as instructed below:

1.	First, paste glut.h file in: 
C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\include\gl
2.	Then paste glut.lib in: 
C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\lib\x64
3.	Then paste the glut32.lib in: 
C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\lib\x86
4.	Then paste glut.dll and glut32.dll in: 
C:\Windows\SysWOW64
5.	Finally copy glut32.dll to: 
C:\Windows\System32 

That is how you will set up the OpenGL library for your Windows 10 to get everything ready to go.
