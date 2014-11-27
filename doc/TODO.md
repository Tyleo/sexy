# TODO

* Figure out an efficient way for things to subscribe to events. I'm thinking of something like C# events but it can't use virtual method calls or any sort of pointers to functions.

* Figure out a way to make it so that the components to remove are stored in a vector inside of the SystemImpl instead of a pointer to a vector. Maybe it would be safe to just return a raw vector in this case? SystemImpl should be cleaned up whenever System is cleaned up so it shouldn't be awful.

* Set up precompiled header.

* Provide a better default filter time... get default filters working in the first place.

* Provide some way of constructing entities easily from a document.
