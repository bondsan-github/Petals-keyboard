"import" fatal error C1083: Cannot open header unit file: ' windows.h': No such file or directory

https://docs.microsoft.com/en-us/cpp/cpp/modules-cpp?view=msvc-160
std.regex provides the content of header <regex>
std.filesystem provides the content of header <filesystem>
std.memory provides the content of header <memory>
std.threading provides the contents of headers <atomic>, <condition_variable>, <future>, <mutex>, <shared_mutex>, and <thread>
std.core provides everything else in the C++ Standard Library
To consume these modules, add an import declaration to the top of the source code file. For example:

import std.core;
import std.regex;
To consume the Microsoft Standard Library modules, compile your program with /EHsc and /MD options.