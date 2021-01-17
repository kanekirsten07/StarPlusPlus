To generate projects, run:

`cmake CMakeLists.txt -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake`

From the StarPlusPlus directory

## WSL 2 Setup in Visual Studio
1. Follow the instructions on https://docs.microsoft.com/en-us/cpp/linux/connect-to-your-remote-linux-computer?view=msvc-160
2. From wsl2 you may need to first run `sudo apt update`
3. You may need to follow these instructions to get SSH working on WSL2 https://jeetblogs.org/post/sshing-into-a-windows-wsl-linux-subsystem/

## VCPKG on WSL2 setup
1. Follow the instructions on https://github.com/microsoft/vcpkg#installing-linux-developer-tools
2. Follow the instructions for https://github.com/microsoft/vcpkg#quick-start-unix
3. Add the following to you `~/.bashrc` file: `VCPKG_TOOLCHAIN_PATH=<vcpkg install path>`
4. You make need to run `sudo apt-get install pkg-config gperf`

## Install Dependencies in WSL2
1. `vcpkg install proxygen`