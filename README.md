# quickmaffs
A C++17 custom math library that includes vector calculations, length, random numbers, etc.

## How to include

Add to include directories path to the `quickmaffs/include/QuickMaffs` directory,
and include the [Everything.hpp](quickmaffs/include/QuickMaffs/Everything.hpp) file:

```cpp
#include <QuickMaffs/Everything.hpp>
```

## How to compile

This is header only library, until `QUICKMAFFS_HEADER_ONLY` is removed from definitions
from the [Everything.hpp](quickmaffs/include/QuickMaffs/Everything.hpp) file. If you
rely on this library, you should create a guard, as described here:

[**SourceFiles.md**](quickmaffs/src/QuickMaffs/SourceFiles.md)

Example:

```cpp
#include <QuickMaffs/Everything.hpp>

#ifndef QUICKMAFFS_HEADER_ONLY
#error "QuickMaffs needs to be compiled separately! When QuickMaffs is properly linked, remove this error."
#endif

namespace math = quickmaffs; // alias the namespace not to use the long one.
```

## Example usage

For your comfort, use alias to `quickmaffs` namespace. This is very handy if you
use it as your main math library:

```cpp
namespace math = quickmaffs;
```

### Generating random numbers

Use `generate` method in namespace `random`:

```cpp
auto randomInteger = math::random::generate(100, 200);
auto randomFloat = math::random::generate(0.f, 1.f);
auto randomDouble = math::random::generate(0.0, 10.0);
```

### Working with vectors

Vectors are commonly used to describe points, size, displacement or force in space.
QuickMaffs' implementation of vectors provides you a lot of popular operations,
such as:

- normalization
- computing length and length<sup>2</sup>
- computing distance and distance<sup>2</sup>
- addition, subtraction, multiplication and division
  - `vector` operator `vector`
  - `vector` operator `scalar`
  - `scalar` operator (only `*` and `+`) `vector`

QuickMaffs defines following vector templates:

- `Vector2`
- `Vector3`

There are also following aliases created:

- `Vector2f` equals `Vector2<float>`
- `Vector2d` equals `Vector2<double>`
- `Vector2ld` equals `Vector2<long double>`
- `Vector2i8` equals `Vector2<std::int8_t>`
- `Vector2i16` equals `Vector2<std::int16_t>`
- `Vector2i32` equals `Vector2<std::int32_t>`
- `Vector2i64` equals `Vector2<std::int64_t>`
- `Vector2u8` equals `Vector2<std::uint8_t>`
- `Vector2u16` equals `Vector2<std::uint16_t>`
- `Vector2u32` equals `Vector2<std::uint32_t>`
- `Vector2u64` equals `Vector2<std::uint64_t>`
- `Vector2size` equals `Vector2<std::size_t>`

This also applies to `Vector3` template.
