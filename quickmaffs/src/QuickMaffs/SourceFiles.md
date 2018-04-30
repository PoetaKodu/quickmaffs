# QuickMaffs source files

This is QuickMaffs source files directory.

This library currently does not require compiling - it is all in headers library.
However I cannot promise, that in future it won't change. You can get notified easily
by checking if `QUICKMAFFS_HEADER_ONLY` macro is defined:

```cpp
#include <QuickMaffs/Everything.hpp>

#ifndef QUICKMAFFS_HEADER_ONLY
#error "QuickMaffs needs to be compiled separately. After doing it, remove this error!"
#endif

namespace math = quickmaffs; // alias the namespace not to use the long one.
```