# slide_viewer_cpp
C++ implementation of demo of a class for a digital slide viewer. 

Computes which pixel on a slide to retrieve and display in a pixel in slide viewer after a rotation of the slide by a user.

Sets up a coordinate system for both the viewer and slide. The x- and y-axes are what you think they would be. The x-axis is horizontal; the y-axis is vertical. Coordinates are expressed as (x,y). Initially , when the slide is loaded, the coordinate systems of the slide and the viewer are aligned.

The viewer pixel coordinate and the slide coordinate currently displayed in the viewer pixel are encapsulated together in a Display object. As the slide is rotated with respect to the viewer, the coordinate of the slide displayed in the viewer pixel is updated.

Rotation is accomplished by matrix multiplication with a rotation matrix. For further information on rotation matrices: https://mathworld.wolfram.com/RotationMatrix.html.

Here the operation is applied to one display pixel, but to get all of the slide pixels to display, this same operation is applied to every pixel. This operation is embarrassingly parallel and so is amenable to GPU impleementation.
