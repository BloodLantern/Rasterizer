# Rasterizer

### The rasterization process consists in transforming a 3D space to a 2D plane (the screen).

![thumbnail](https://cdn.discordapp.com/attachments/1031829395016536085/1106569973586997268/image.png "General window insights")

## Implemented features:

- Model, View and Projection transformations
- Triangle fill with color and texture interpolation
- Texture handling in JPEG and PNG formats
- Depth test

## Implemented optimizations:

- Depth test
- Clipping
- Interpolation

## Scene

- Base triangle
- Multiple models and textures at the same time (2 by default)

## ImGui window

### General window

![thumbnail](https://cdn.discordapp.com/attachments/1031829395016536085/1106569345783582761/image.png "General window insights")

- FPS display
- Checkbox to switch between the base triangle and the 3D models
- Text fields to load specific textures and models at runtime

### Camera window

![thumbnail](https://cdn.discordapp.com/attachments/1031829395016536085/1106569399374188664/image.png "General window insights")

- FOV
- Z near
- Z far
- Up vector
- Eye position
- Center position (where the camera is looking)

### World transformations window

![thumbnail](https://cdn.discordapp.com/attachments/1031829395016536085/1106569433641648219/image.png "General window insights")

- Position
- Rotation
- Scale factor
