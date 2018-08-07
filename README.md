# Serial_port_example_Windows
A C++ example to operate the serial port for Windows.

Windows has two modes to read/write a file: overlapped(asynchronous) and nonoverlapped(synchronous).

One of the many factors to consider when choosing between nonoverlapped and overlapped operations is portability. Overlapped operation is not a good choice because most operating systems do not support it. Most operating systems support some form of multithreading, however, so multithreaded nonoverlapped I/O may be the best choice for portability reasons.

Therefore, this example only uses nonoverlapped.

# Build example
```c
// on Windows with VS 2015 installed
git clone https://github.com/gongfan99/Serial_port_example_Windows.git
build
test
```

# Reference
* https://msdn.microsoft.com/en-us/library/ff802693.aspx