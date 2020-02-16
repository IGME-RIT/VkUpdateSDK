/*
Copyright 2019
Original authors: Niko Procopi
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
<http://www.gnu.org/licenses/>.

Special Thanks to Exzap from Team Cemu,
he gave me advice on how to optimize Vulkan
graphics, he is working on a Wii U emulator
that utilizes Vulkan, see more at http://cemu.info
*/

#include "Scene.h"

Scene::Scene()
{
	// Load all the OBJ files
	catMesh = new Mesh("../../../Assets/kitten.3Dobj", false);
	dogMesh = new Mesh("../../../Assets/dog.3Dobj", false);
	rockMesh = new Mesh("../../../Assets/building.3Dobj", true);
	skyMesh = new Mesh("../../../Assets/skybox.3Dobj", false);

	// Load all the PNG files
	catTex = new Texture("../../../Assets/CatColor.png");
	dogTex = new Texture("../../../Assets/DogColor.png");
	skyTex = new Texture("../../../Assets/skybox.png");

	rockColor = new Texture("../../../Assets/BrickColor.png");
	rockNormal = new Texture("../../../Assets/BrickNormal.png");

	// These are for 2D entities
	logoTex = new Texture("../../../Assets/Logo.png");
	fontTex = new Texture("../../../Assets/font2.png");

	// In this example, each entity has its own seperate
	// OBJ and PNG file. However, you can use the same
	// Model and Texture with multiple entities, without
	// needing to reload the same file multiple times

	// Load a cat and dog, because they're adorable
	catEntity = new Entity();
	catEntity->mesh = catMesh;
	catEntity->texture[0] = catTex;
	catEntity->CreateDescriptorSetBasic();

	dogEntity = new Entity();
	dogEntity->mesh = dogMesh;
	dogEntity->texture[0] = dogTex;
	dogEntity->CreateDescriptorSetBasic();

	// this is the building from previous OpenGL tutorials
	buildingEntity = new Entity();
	buildingEntity->mesh = rockMesh;
	buildingEntity->texture[0] = rockColor;
	buildingEntity->texture[1] = rockNormal;
	buildingEntity->CreateDescriptorSetBumpy();

	// the skybox has a cube with a 2D PNG, not a cubemap
	skyEntity = new Entity();
	skyEntity->mesh = skyMesh;
	skyEntity->texture[0] = skyTex;
	skyEntity->CreateDescriptorSetBasic();

	// No mesh needed here, its procedurally generated
	logoEntity = new Entity();
	logoEntity->texture[0] = logoTex;
	logoEntity->CreateDescriptorSet2D();

	textEntity = new Entity();
	textEntity->texture[0] = fontTex;
	sprintf(textEntity->name, "_______");
	textEntity->CreateDescriptorSet2D();

	textEntity2 = new Entity();
	textEntity2->texture[0] = fontTex;
	sprintf(textEntity2->name, "_______");
	textEntity2->CreateDescriptorSet2D();
}

void Scene::Draw()
{
	Demo* d = Demo::GetInstance();

	// 2D Pipeline
	// draw 2D logo and fonts
	d->ApplyPipeline2D();
	d->DrawEntity(logoEntity);
	d->DrawEntity(textEntity);
	d->DrawEntity(textEntity2);

	// Bind the "basic" pipeline
	// draw the cat and the dog
	d->ApplyPipelineBasic();
	d->DrawEntity(catEntity);
	d->DrawEntity(dogEntity);

	// Bind the bumpy pipeline (for normal maps)
	// Draw the building, which will use the pipeBumpy pipeline
	d->ApplyPipelineBumpy();
	d->DrawEntity(buildingEntity);

	// Bind the sky pipeline
	// Draw the sky, which will use the pipeSky pipeline
	d->ApplyPipelineSky();
	d->DrawEntity(skyEntity);
}

// used to record time
float time = 0.0f;
float angle = 0.0f;
float dist = 0.0f;
bool noPressYet = true;
glm::vec3 cameraPosition;

char LetterToVirtualKey(char letter)
{
	return letter - 20;
}

void Scene::Update()
{
	Demo* d = Demo::GetInstance();

	// create projection matrix
	// If this looks confusing, go back to
	// prepare_uniform_buffers and read those comments
	d->projection_matrix = glm::perspective(45.0f * 3.14159f / 180.0f, (float)d->width / (float)d->height, 0.1f, 100.0f);

	// all key codes are here, https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	// Any of these can go into keys[]
	// including VK_ESCAPE, which was used in Main.cpp
	// VK does not mean "vulkan" in this case, VK means "Virtual Key",
	// it is part of Win32 and can be used in any API

	// to detect input with letters, you must use 
	// capital letters in the code

	// hitting the letter P on the keyboard
	// will pause the scene
	if (!keys['P'])
	{
		// add to time
		time += 1.0f / 60.0f;
	}
	
	if (keys[VK_UP])
	{
		// stop using default camera animation
		noPressYet = false;

		dist -= 0.05f;

		if (dist <= 1.0f)
			dist = 1.0f;
	}

	if (keys[VK_DOWN])
	{
		// stop using default camera animation
		noPressYet = false;

		dist += 0.05f;

		if (dist >= 9.0f)
			dist = 9.0f;
	}
	
	if (keys[VK_LEFT])
	{
		// stop using default camera animation
		noPressYet = false;

		angle -= 0.01f;
	}

	if (keys[VK_RIGHT])
	{
		// stop using default camera animation
		noPressYet = false;

		angle += 0.01f;
	}

	// Change cat's position
	catEntity->pos = glm::vec3(sin(time) - 1, 0, cos(time));
	catEntity->rot.y = time;
	catEntity->scale = glm::vec3(1);

	// Change dog's position
	dogEntity->pos = glm::vec3(sin(3.14f - time) + 1, 0, cos(3.14f - time));
	dogEntity->rot.y = -time;
	dogEntity->scale = glm::vec3(0.8f);

	// Change building
	buildingEntity->pos = glm::vec3(0, 0, -1);
	buildingEntity->scale = glm::vec3(1.0f);

	float adjustZ = 0.0f;

	// View matrix, where the camera is
	
	// play default camera animation
	// until user tries pressing arrow keys
	if (noPressYet)
	{
		angle = time / 2;
		dist = 5.0f;
		adjustZ = 3.0f;
	}

	cameraPosition = {
		dist * sin(angle),
		2.0f,
		dist * cos(angle) + adjustZ };

	// The position of the camera
	glm::vec3 focus = { 0, 0, 0 };				// The position the camera is looking at
	glm::vec3 up = { 0.0f, 1.0f, 0.0 };			// The direction that faces up, which is the Y axis
	d->view_matrix = glm::lookAt(cameraPosition, focus, up);	// build the view matrix from thsi data

	// Notice the scale is small, yet the skybox is always drawn
	// behind everything else, this is how we know the Sky.Vert shader is 
	// working, because it sets depth to the maximum possible value
	skyEntity->pos = cameraPosition;
	skyEntity->scale = glm::vec3(1.0f);

	logoEntity->pos = glm::vec3(-0.7, 0.7, 0.0f);
	logoEntity->scale = glm::vec3(0.5f);

	textEntity->pos = glm::vec3(-0.5, 0.6, 0.0f);
	textEntity->scale = glm::vec3(0.5f);
	sprintf(textEntity->name, "NikoRIT");

	textEntity2->pos = glm::vec3(0.2, 0.6, 0.0f);
	textEntity2->scale = glm::vec3(0.5f);
	sprintf(textEntity2->name, "Time%02f", time);

	// update the data in the uniform buffer
	// this recalculates the model matrix (for rotation)
	// and the projection matrix (for the window dimensions),
	// it does not recalculate the view matrix, becasue we are
	// not moving the camera
	catEntity->Update3D();
	dogEntity->Update3D();
	buildingEntity->Update3D();
	skyEntity->Update3D();

	// width and height here, are window dimensions
	logoEntity->Update2D();
	textEntity->Update2D();
	textEntity2->Update2D();
}

Scene::~Scene()
{
	// We delete our uniform buffer (which was on the CPU),
	// then we destroy all of our GPU buffers that were 
	// originally made from staging buffers
	delete catEntity;
	delete dogEntity;
	delete buildingEntity;
	delete skyEntity;
	delete logoEntity;
	delete textEntity;
	delete textEntity2;

	// Meshes
	delete catMesh;
	delete dogMesh;
	delete rockMesh;
	delete skyMesh;

	// Textures
	delete catTex;
	delete dogTex;
	delete skyTex;
	delete rockColor;
	delete rockNormal;
	delete logoTex;
	delete fontTex;
}
