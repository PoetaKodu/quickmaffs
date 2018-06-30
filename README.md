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
- computing dot product
- computing cross product

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

#### Setting vector components

`Vector2` has `x`, `y` components and `Vector3` adds another one - `z`.
Default constructor initializes these components to zero. You can also set it
by yourself.

```cpp
// Two following lines are equal:
math::Vector2f vec2_a;
math::Vector2f vec2_b{ 0.f, 0.f };

// Two following lines are equal:
math::Vector3f vec3_a;
math::Vector3f vec3_b{ 0.f, 0.f, 0.f };

// Later, you can set value, either by assigning new vector:
vec2_a = { 30.f, 20.5f };
// ... or by using `set` method:
vec2_a.set( 30.f, 20.5f );

// Same for Vector3, but with third parameter.
```

#### Type safety

Vectors do not like to change its components' type without you knowing about that.
You cannot multiply `Vector3i32` with `float` scalar. You need to explicitly convert
it, using `convert` template method:

```cpp
Vector3i32 vec3 = { 200, 50, 10 };
// Vector3f vec3f = 5.f * vec3; // error! multiplication: float with Vector3i32
Vector3f vec3f = 5.f * vec3.convert<float>(); // Ok
```

#### List of other useful methods:

- `Vector`*`N`*`::toString`
- `Vector`*`N`*`::nearlyEqual`
- `Vector`*`N`*`::absolute`
- `Vector`*`N`*`::normalize`
- `Vector`*`N`*`::normalizeSelf` (modifies self) 
- `Vector`*`N`*`::reflect`
- `Vector`*`N`*`::reflectSelf` (modifies self) 
- `Vector`*`N`*`::length`
- `Vector`*`N`*`::lengthSquared`
- `Vector`*`N`*`::distance`
- `Vector`*`N`*`::distanceSquared`
- `Vector`*`N`*`::dot`
- `Vector`*`N`*`::cross`
- **`static`**` Vector`*`N`*`::lowerBounds`
- **`static`**` Vector`*`N`*`::upperBounds`
- **`static`**` Vector`*`N`*`::bounds`

### Length calculation

Method that look like this:

```cpp
// Only as example:
struct Car {
    float getTopSpeed() const {
        return 220.f; //  mph? kmph? per hour? per second?
    }
};
```

does not really express programmer's intention. It should look like this:

```cpp
Kilometers getTopSpeed() const {
    return 220.f; //  per hour? per second?
}
```

or more perfectly, like this:

```cpp
Kilometers getTopSpeedPerHour() const {
    return 220.f;
}
```

You can easily manipulate length units using `Length<Type, Ratio>` template:
[src: Length.hpp](quickmaffs/include/QuickMaffs/Math/Length.hpp)
There are aliases defined for:

- **`Nanometers`** equal to `Length<double, std::nano>` equal to `0.000'000'001m`
- **`Micrometers`** equal to `Length<double, std::micro>` equal to `0.000'001m`
- **`Millimeters`** equal to `Length<double, std::milli>` equal to `0.001m`
- **`Centimeters`** equal to `Length<double, std::centi>` equal to `0.01m`
- **`Decimeters`** equal to `Length<double, std::deci>` equal to `0.1m`
- **`Meters`** equal to `Length<double>` equal to `1m`
- **`Decameters`** equal to `Length<double, std::deca>` equal to `10m`
- **`Hectometers`** equal to `Length<double, std::hecto>` equal to `100m`
- **`Kilometers`** equal to `Length<double, std::kilo>` equal to `1'000m`
- **`Megameters`** equal to `Length<double, std::mega>` equal to `1'000'000m`
- **`Gigameters`** equal to `Length<double, std::giga>` equal to `1'000'000'000m`
- **`Miles`** equal to `Length<double, std::ratio<1609, 1>>;` equal to `1609m`
- **`Yards`** equal to `Length<double, std::ratio<9144, 10000>>` equal to `0.9144m`
- **`LightYears`** equal to `Length<double, std::ratio<9460730472580800>>` equal to `9460730472580800m`

Example usage:

```cpp
math::Yards yards = 500;
math::Meters meters = yards; // unlike in vectors, here conversion is implicit
std::cout << std::fixed << yards.value << " yards is equal to " << meters.value << " meters." << std::endl;
// possible output:
// 500.000000 miles is equal to 804500.000000 meters.
```
