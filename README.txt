Documentation Author: Niko Procopi

Vulkan 1.2

As of Feb 15, 2019, the newest version of Vulkan is 1.2.131
This tutorial applies to all future versions of the API

This tutorial has three parts
	- How to update the Vulkan SDK within the Visual Studio solution
	- How to initialize the newest version of the Vulkan SDK
	- How to use new features in new versions of the SDK

The best part about upgrading Vulkan 1.0 to 1.1+ is that we can 
flip the viewport upside down, making it so we do not need to 
modify the projection matrix every time we want to draw. This is 
standard practice in all modern Vulkan projects in the gaming industry

How to update the Vulkan SDK
	1. In the directory of this README, delete the Bin, Include, and Lib folders
		Caution: GLM is inside the Include folder, you'll need to save that
	2. Download and install the latest SDK
		https://vulkan.lunarg.com/sdk/home
	3. Go to the install directory
		Default is C:\VulkanSDK\version
	4. Copy and Paste the Bin, Include, and Lib folders from
		Vulkan SDK into the directory of this README
	5. Compile and run the program, it should work just fine

How to initialize the newest version of Vulkan SDK 
	Prior to now, we've had the Vulkan 1.1.114 SDK bundled
	with each project, but we were initializing Vulkan 1.0.
	We did this to ensure compatibility with all Vulkan-enabled 
	devices, we did not want to exclude anyone with legacy hardware.
	Now that we are 20+ tutorials into the series, it is time to move on

	void Demo::prepare_instance()
	In this function, we have vkCreateInstance function that uses a pointer
	to a VkInstanceCreateInfo structure. This structure has the ability to hold
	a pointer to a VkApplicationCreateInfo. This was never used, and as a
	result, Vulkan 1.0 was initialized.

	The apiVersion variable inside VkApplicationInfo will determine which
	version of Vulkan API is initialized, in this case we want Vulkan 1.2.
	Nothing else in this structure will have any impact on the program or the
	performance of the program

	This structure is then given to VkCreateInstanceInfo, and then the newer
	version of Vulkan is initialized

How to use new Vulkan features

	First thing we will do is flip the Viewport. If you try to do this in Vulkan 1.0,
	you would get a validation error if validation was enabled, or the program
	would crash

	In Vulkan 1.1+, we can give the viewport a negative height, so that
	the screen does not render upside-down (the way Vulkan is by default)
	which can be seen here
		Demo::build_secondary_cmd()

	Now that we flipped the viewport, we do not need to invert the Y axis
	in projection matrices anymore. You can see that it is removed from
	Scene.cpp, we can now use unmodifed projection matrices, just like
	OpenGL.
	
	This is standard for all modern Vulkan projects in the gaming industry.
	It is used in Cemu, Yuzu, RPCS3, GPCS4, Dolphin, and more