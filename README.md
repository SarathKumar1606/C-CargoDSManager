Download the latest curl library suitable for your device from the following link:
https://curl.se/windows/

1.Copy all the folders inside curl's "include" folder. Then navigate to the dev cpp's include folder and paste it there.
Note : Usually the directory of devcpp required folder will be as  follows:

for older versions of dev cpp:
"C:\Program Files (x86)\Dev-Cpp\MinGW64"


for latest Embarcadero cpp:

"C:\Program Files (x86)\Embarcadero\Dev-Cpp\TDM-GCC-64"

2. Copy all files inside curl's lib folder to Dev-cpp lib folder.

3.Copy all files inside  curl's bin folder to Dev-cpp bin folder.

4.Inside Dev-cpp Go to :   Tools> Compiler Options > Add the following commands when calling the linker :
-static -lib-gcc -lcurl

5.Modify lines 298 and 471 in the C code with your relevant folder paths to hold the generated images.


