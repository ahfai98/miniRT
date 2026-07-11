# miniRT — 42KL

> A ray tracer written in C that renders 3D scenes — spheres, planes, and cylinders — with ambient and diffuse lighting, interactive camera and object controls.

## Overview

Ray tracing is the technique behind photorealistic rendering in film and games. For every pixel on screen, a ray is cast from the camera into the scene. The renderer computes which objects the ray hits, how far away they are, and what colour the surface should be based on the lights in the scene. The result is physically plausible shading — shadows, highlights, and depth emerge naturally from the geometry.

miniRT implements this from scratch in C: vector arithmetic, ray–object intersection math, the Phong lighting model, scene file parsing, and a MiniLibX window for interactive display. This is one of the most mathematically intensive projects in the 42 curriculum.

## The Challenge

Parse a `.rt` scene description file defining a camera, one or more lights, ambient illumination, and any number of geometric objects (spheres, planes, cylinders). Cast one ray per pixel from the camera through the scene, find the closest intersection, compute shading, and write the resulting colour to the image buffer. Display the result in a window with live keyboard and mouse controls to manipulate the scene.

The subject forbids using any external maths or graphics libraries. All vector operations, ray equations, quadratic solvers, and lighting calculations must be hand-written.

## Concepts Introduced

- **Ray tracing algorithm**: ray generation from a camera, parametric ray equation `P = O + tD`
- **Ray–object intersection**: solving analytic equations for spheres (quadratic), planes (dot product), and capped cylinders (quadratic + cap disk test)
- **Vector mathematics**: dot product, cross product, normalisation, reflection, used throughout the renderer
- **Phong lighting model**: ambient term (constant base light), diffuse term (Lambertian cosine law with a point light source)
- **Surface normals**: computing the outward normal at each intersection point for shading
- **Scene parsing**: structured `.rt` file format with strict validation and error reporting
- **Event-driven graphics**: MiniLibX hooks for keyboard and mouse, re-rendering the scene on interaction
- **Memory management**: heap-allocated scene graph, clean teardown on exit

## Learning Outcomes

After completing this project you will have:
- Implemented a working ray tracer from mathematical first principles
- Applied linear algebra (vectors, normals, projections) to solve real geometric problems
- Designed a modular C codebase with clear separation between parsing, geometry, lighting, and rendering
- Understood why every pixel in a photorealistic render involves solving equations, not just drawing shapes
- Gained practical experience with floating-point precision issues in geometric computation
- Built an interactive graphics application with real-time object and camera manipulation

## Architecture

```
.rt scene file
   │
parse.c / parse_obj.c / parse_light_and_camera.c
   │ → t_scene (camera, ambient light, point light, linked list of objects)
   │
camera.c  → generate rays from camera origin through each pixel
   │
intersect.c / intersect_pl_sp.c / intersect_cy.c
   │ → for each ray: find closest intersection with all scene objects
   │
lighting.c / color.c
   │ → compute ambient + diffuse colour at the intersection point
   │
mlx_interface.c
   └── write colour to image buffer → blit to window → mlx_loop
```

## Scene File Format (`.rt`)

```
# Ambient light: intensity  R,G,B
A  0.2  255,255,255

# Camera: position  orientation  field-of-view (degrees)
C  0,0,-5  0,0,1  70

# Point light: position  brightness  R,G,B
L  -2,4,-3  0.7  255,255,255

# Sphere: centre  diameter  R,G,B
sp  0,0,3  2  255,0,0

# Plane: point-on-plane  normal-vector  R,G,B
pl  0,-1,0  0,1,0  0,255,0

# Cylinder: centre  axis-vector  diameter  height  R,G,B
cy  0,0,3  0,1,0  1  3  0,0,255
```

Rules: exactly one `A`, one `C`, one `L`. Any number of `sp`, `pl`, `cy`. Any invalid format or out-of-range value exits with an error message.

## Interactive Controls

| Input | Action |
|-------|--------|
| Arrow keys | Translate selected object |
| `W/A/S/D` + `Q/E` | Rotate selected object |
| `R/F` | Scale selected object |
| `Tab` | Cycle through objects / camera / light |
| Mouse scroll | Zoom camera |
| `ESC` | Exit |

## How to Build

```bash
make        # Linux (requires libx11-dev, libxext-dev)
make re
make fclean
```

## How to Use

```bash
./miniRT scenes/correct_tests/sphere_only.rt
./miniRT scenes/correct_tests/room_with_obj2.rt
./miniRT scenes/correct_tests/90spheres.rt
./miniRT scenes/correct_tests/duck.rt
```

To write your own scene, create a `.rt` file following the format above and pass it as the argument. The renderer window opens at 500×500 px.
