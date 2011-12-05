---
title: Monte Carlo (Stochastic) Ray Tracer
year: 2011
image: raytracer.png
points: 6
group: 2
---

This is a project done in the university course TNCG15 - "Advanced Global Illumination and Rendering". 
In a ray tracer modeled after Turner Whitted's model, only perfect specular reflections are considered.
To consider imperfect and, to some extent, diffuse interreflections, Monte Carlo integration schemes
are used.

Monte Carlo schemes are based on statistics and can be used to solve integrals that can be very hard
to solve analytically.

There are also different types of 
<a href="http://en.wikipedia.org/wiki/Bidirectional_reflectance_distribution_function" rel="external">BRDF:s</a> 
implemented such as the Blinn-Phong model and the Cook-Torrance model. Transmission is also handled by the
renderer.

Visual feedback of the render progress is given by rendering the resulting image to an 
<a href="http://libsdl.org/" rel="external">SDL</a> window. The resulting image
is then saved to a .png.

The project report is available <a href="https://github.com/downloads/abbec/flaXx/report.pdf">here</a>.

## Techniques ##
- C++
- SDL
- libpng
- Monte Carlo Integration
- Lighting calculations

## Source Code ##
The project is open source and the source code can be viewed on 
<a href="https://github.com/abbec/flaXx" rel="external">GitHub</a>.
