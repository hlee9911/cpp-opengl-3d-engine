Graphics Programming Concepts

Shader Program defines how pixels are rendered using shaders.
Material stores the shader and uniform values
Mesh holds the geometry data (vertices, indices) for rendering.
The GraphicsAPI provides unified access to create and manage these resources.

Model transforms local space into world spce
View transforms world spce into camera space (as if moving the world), view is inverse
Projection transform camera space into the screen space // maps 3d to 2d

Camera only renders only between the near and far planes
forms view frustum
Near Plane is the closest visible distance
Far Plane is the farthest visible distance
Aspect Ratio: Width / Height and affects horizontal scaling

Z-buffer
Invisible grayscale image, the sme size as your screen
for every pixel you draw, it stores the depth, how far that pixel is from the camera
when draawing the next object, the GPU compares its depth against whats already stored
if its farther, it gets hidden
with the depth testing, the GPU knows the sphere is behind and hides it correctly
by default, in OpenGL, the z-buffer is disbled, so we need to enable it

Quaternion
A quaternion has four components: x, y, z, and w
orientation is one value not three separate angles
this avoids rotation-order issue entirely

Lighting
lightDir = normalize(lightPos - fragPos);
float diffuseFactor = dot(normal, lightDir);

Specular lighting
Specular gives shiny reflections at certain angles, 
it depends on the view direction as well as the light direction

RigidBody
RigidBody represents an object in the physics world
It combines shape, mass, and friction properties to simulate realistic movement and interactions
It also manages the object's transform and motion state
Rigidbody comes in three types: 
Static (immovable = environments), 
Dynamic (fully simulated = simulated objects), 
Kinematic (moved by code, but can affect dynamic objects e.g. moving platforms, elevators, player character capsule = scripted motion)	

Sprite
A sprite is a plane, a rectangle with a texture applied to it, that always faces the camera
Origin Start
For sprites, the coordinates start in the bottom left corner not the center
Next: Size, with width(x) and height(y)
A sprite can use part of a texture like a region in an atlas
Thus, two UV coordinates: lower left and upper right define which area of the texture to sample
Pivot Point
The pivot point is the sprite that rotates around. By default, the pivot is centered at (0.5, 0.5)
Pivot values range from 0 to 1 relative to the sprite size
2D transformation
Sprites only moves on x/y and rotate around z axis
Thus, the translation, scaling and rotation are easier to manage than 3D objects
2D Rendering
2D at z = 0 can fight with the 3D depth. To prevent this, add depth test toggling in GraphicsAPI.
Blend Mode
Blend mode defines how the sprite's colors blend with the background

