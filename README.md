"# getMonitorInfo" 


Preparing an environment:

choco install mingw -y
choco install winlibs -y
choco install msys2 -y
choco install vscode -y
choco install git -y


Compiling with static libraries:

 g++ .\GetMonitorInfo.cpp -o getMonitorInfo.exe -static-libgcc -static