h1. *Approximation* library feature development notes

h3. Usage 
This library is made to work with the Arduino platform.  It is not dependent on other libraries (except for Arduino.h).  _Users_ of the library should not need to include other libraries.

h3. Development/Continuous Integration
For development (adding features, regression testing, ...), this library depends on the following:
* Github
* Github Actions
** githubci.yml -- Arduino board configuration build checks (AVR, ESP32 ...)
** aunit_tests.yml -- regression tests on Linux
These Github scripts will check that code compiles and tests PASS, or warn you if there is a regression.

h3. Regression testing
Regression tests are added to extras/tests/* sketches, and depend on:
* Linux build environment
* the "AUnit" unit testing library
* the "EpoxyDuino" library for basic Linux compatibity

h3. Linux development
I find it useful to develop code on a Linux computer, as this lets me run my regression tests directly without downloading a sketch, or pushing each change to github.

While I have the Arduino IDE installed, it is more set up to _use_ libraries rather than _create_ them. Example sketches must be built one at a time, so getting interface changes to match in all examples is difficult.

So... the Github Actions use Makefiles and the gcc/g++ toolchain, and I use 'make' in the same way.  In the top-level directory:
* "make all" to do a full build and test
* "make run" to build tests
* "make test" to (build and) run tests
* "make clean" to delete generated output files
* "make debug" to create executables with debugger support

It is important that this library can find the EpoxyDuino and AUnit libraries it uses for testing.  To ensure this I do my put my development library inside the Arduino "libraries" directory. Other libraries are at the same level.  For example the AUnit library will be found  at the relative path "../AUnit":
* libraries/
** Approximation (this library)
** AUnit/
** EpoxyDuino/
** (other libraries...)

h3. Debugging and development with Visual Studio Code (experimental)
It would be nice to use a debugger while adding features and running my tests.  Debuggers provide much faster feedback than examining `Serial.print(...)` statements with every run.

So... this library supports a Visual Studio Code workspace which can build and debug the library and its tests.  To use this capability you must have the following installed:
* Visual Studio Code
** C/C++ (Microsoft Extension)
** C/C++ Extension Pack (Microsoft Extension)
** C/C++ Extension Themes (Microsoft Extension)
** Makefile Tools (Microsoft Extension)

At the top level of this library, I enter the command: `code Approximation.code-workspace` to run VS Code.  Specifying the `Approximation.code-workspace` file helps give VS Code a base path from which to search for useful files and libraries.

Interesting magic is in:
* Approximation.code-workspace
* .vscode/c_cpp_properties.json
* .vscode/launch.json
* .vscode/settings.json
* not needed? .vscode/tasks.json

It is important to do a ("clean" and) "debug" build before using the debugger.

I have been able to set breakpoints in a regression test, examine variables, step, and continue.

I have set up the VS Code settings to support "Debug" and "Release" configurations.  Usually I use the "Debug" configuration... but "Release" will behave differently and it's also worth testing.  The GitHub regression test uses the "Release" build.

Under "Makefile Tools" tab:
*  set "Configuration" to "Debug"
*  set "Build target" to "configuredBuild"
