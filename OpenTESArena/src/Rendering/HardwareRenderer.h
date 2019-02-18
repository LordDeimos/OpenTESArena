#pragma once

#include "../Math/Matrix4.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../World/VoxelGrid.h"

typedef unsigned int GLuint;

class HardwareRenderer
{
public:
	//(Near) Duplicate of SoftwareRenderer::Camera
	struct Camera
	{
		Double3 eye; // Camera position.
		Double3 eyeVoxelReal; // 'eye' with each component floored.
		Double3 direction; // 3D direction the camera is facing.
		Int3 eyeVoxel; // 'eyeVoxelReal' converted to integers.
		Matrix4f transform; // Perspective transformation matrix. Floats instead of Doubles
		double forwardX, forwardZ; // Forward components.
		double forwardZoomedX, forwardZoomedZ; // Forward * zoom components.
		double rightX, rightZ; // Right components.
		double rightAspectedX, rightAspectedZ; // Right * aspect components.
		double frustumLeftX, frustumLeftZ; // Components of left edge of 2D frustum.
		double frustumRightX, frustumRightZ; // Components of right edge of 2D frustum.
		double fovY, zoom, aspect;
		double yAngleRadians; // Angle of the camera above or below the horizon.
		double yShear; // Projected Y-coordinate translation.

		Camera(const Double3 &eye, const Double3 &direction, double fovY, double aspect,
			double projectionModifier);

		// Gets the camera's Y voxel coordinate after compensating for ceiling height.
		int getAdjustedEyeVoxelY(double ceilingHeight) const;
	};

	HardwareRenderer();
	~HardwareRenderer();
	//Initialise the renderer
	void init(int width, int height);
	//Render to internal framebuffer and read into colourBuffer
	void render(const Double3 &eye, const Double3 &direction, double fovY, double ceilingHeight, const VoxelGrid &voxelGrid, uint32_t* colourBuffer);
private:
	//OpenGL ID's for various objects
	GLuint frameBuffer, colourBuffer, renderBuffer, frameVAO, frameVBO, shaderID;
	int width, height;
};

