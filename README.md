"# getMonitorInfo" 


Preparing an environment:

choco install mingw,winlibs,msys2,vscode,git -y


Compiling with static libraries:

 g++ .\GetMonitorInfo.cpp -o getMonitorInfo.exe -static-libgcc -static