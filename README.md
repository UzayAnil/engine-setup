make build folder,
<br>
from build folder in terminal:
<br>
cmake -G Ninja .. (if ninja)
<br>
cmake -G "MinGW Makefiles" .. (if mingw)

then:
<br>
ninja (if ninja)
<br>
cmake --build . (if mingw)

then to run app from terminal:
<br>
app (if cmd)
<br>
./app (if mingw)

to stop from opening an external terminal window when running the app on windows,
<br>
uncomment the WIN32 from add_executable in cmakelists.txt
<br>
will stop debug messages from showing up though, ie. sokol errors/printf.
