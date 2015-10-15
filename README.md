# malloc
Malloc implementation as a school project, in normed C.

The logic:

By using the system call mmap, the goal of this project is to reimplement our own version of malloc.
In this idea, this is a very interesting project as it allows us to really work on memory, and to understand it better.

As a matter of fact, I learned in this work that memory is a continuously indexed big line, and that this memory is mute. Only by adding headers to the memory can we give it a meaning, and return it to the user. It is to the developper's appreciation to determine how to segment this memory. This is why the program doesn't just call a mmap for every user's call of malloc, but it makes one call of mmap, then segment the allocated memory to give back the segments required by the user or the system.

![Alt text](./cover/ft_malloc_screenshot.png "Malloc show alloc memory screenshot")
