Homework 06
===========

# Activity 1 - Questions

1. What is the difference between a shared library such as `libstr.so` and a static library such as `libstr.a`?

In a shared library, code is referenced from the library while the program runs. In a static library, all the library code that is referenced in the program is copied into the program when it's compiled.

2. Compare the sizes of `libstr.so` and `libstr.a`, which one is larger? Why?

Libstr.so is 13 KB while libstr.a is 8 KB. Normally, a shared library would be smaller than a static library because it doesn't copy the entire library in the program but references it in real time. However because the program is so small, the overhead for running the shared library is greater than the size actually saved in a larger program.

# Activity 2 - Questions

1. What is the difference between a static executable such as `str-static`
   and a dynamic executable such as `str-dynamic`?

   A static library is linked into the executable, becoming part of the executable itself. A dynamic executable on the other hand calls a dynamic library every time it's executed. It is not a part of the executable itself.

2. Compare the sizes of `str-static` and `str-dynamic`, which one is larger?
   Why?

   Str-static is 18 K while str-dynamic is 15 K. The str-dynamic is a smaller size because it doesn't link the dynamic library with the executable but calls it every time it needs it. Although this is slower, it saves size compared to a static executable since this links the entire library with the executable.

3. Login into a new shell and try to execute `str-dynamic`.  Why doesn't
   `str-dynamic` work?  Explain what you had to do in order for `str-dynamic`
   to actually run.

   Str-dynamic can't be opened because it can't load the shared library linked, libstr.so. In order to make it run, you need to add the path of the library to the executable.

4. Login into a new shell and try to execute `str-static`.  Why does
   `str-static` work, but `str-dynamic` does not in a brand new shell session?

   For a static library, the library is part of the executable itself. It is readily available for the program to access and doesn't need to be searched for, so an edit to the path isn't required.
