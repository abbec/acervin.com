---
title: SPLAT
year: 2010
image: splat.png
---

Splat is a physics software for simulating deformable bodies. The simulation is done
in two dimensions but can easily be transformed to three.

Our implementation uses spring-mass systems where we split each object into squares
consisting of four masses and four springs (see first image above where mass points are
visualized).

We developed a graphical user interface to easier be able to evaluate
our algorithms and a simple visualization in OpenGL was also
developed.

## Techniques ##
- C++
- GTK+ (gtkmm)
- OpenGL

## Source Code ##
SPLAT is open source and you can grab the source code from 
<a href="https://launchpad.net/splat" rel="external">Launchpad</a>.
