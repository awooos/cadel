# Cadel &mdash; a vector graphics stack in C

Cadel is a vector-based graphics stack, with platform-specific backends.
Platforms can either be hardware architectures (e.g. i386 or amd64),
specific devices (e.g. Raspberry Pi), or certain software (e.g. Xorg or
Wayland).

These backends will typically be rendering rasterized images. As such,
Cadel will include a rasterizer.

## Definitions

- _coordinates_: a set of `(x, y)` coordinates.
- _line_: a collection of two sets of `(x, y)` coordinates.
- _curve_: a representation of a curved line.
  * TODO: what is the representation?
- _object_: a collection of _lines_ and/or _curves_ which defines a more
  complex shape.
  * Examples: any set of lines that are related, including intersecting
    lines, parallel lines which are directly related, and polygons.
- _primitive_: is a basic vector building block provided by the library.
  * Examples: lines, rectangles, circles.

## 
