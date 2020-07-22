# node

A C library for a doubly linked list implementation that allows printing, storage, sorting and retrieval of (homogenously typed) generic data.

A list is created with:
create_linked_list() 
and there are a variety of helper methods supplied in nodeLib.c which make interfacing with the list simple.

Note the use of GenericData and GenericNodeFunctions (e.g. comparison, copy, sort, stringPrinting) to faciliate the storage of any king of data - these need to be defined on a per data basis, examples given in the cardLib.c and cardLib.h files.
