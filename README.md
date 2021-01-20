## Generate the project


## WSL 2 Setup in Visual Studio
1. Follow the instructions on https://docs.microsoft.com/en-us/cpp/linux/connect-to-your-remote-linux-computer?view=msvc-160
2. From wsl2 you may need to first run `sudo apt update`
3. You may need to follow these instructions to get SSH working on WSL2 https://jeetblogs.org/post/sshing-into-a-windows-wsl-linux-subsystem/

## VCPKG on WSL2/Native Linux etup
1. Follow the instructions on https://github.com/microsoft/vcpkg#installing-linux-developer-tools . For now clone vcpkg to your home directory (will be fixed in a later version)
2. Follow the instructions for https://github.com/microsoft/vcpkg#quick-start-unix
3. Add the following to you `~/.bashrc` file: `VCPKG_TOOLCHAIN_PATH=<vcpkg install path>`
4. You may need to run `sudo apt-get install pkg-config gperf`
5. You may need to run `sudo apt install -y libzstd-dev`

## Install Dependencies in WSL2
1. `vcpkg install proxygen`

# Windows with Visual studio and WSL 
1. From Visual Studio, clone the repo
2. Select Linux as target (WSL2)

# Native Linux with Visual Studio Code
1. Clone the repo to a directory of your choice
2. Follow the guide here to install extensions and set your build targets (ex. GCC 10.2.0)
3. Note: you may need to update your settings.json file to set the right toolchain path
    This will be fixed later

## Building

# Windows 
1. Select `WSL-GCC-Debug` as the configuration
2. Build `StarPPServer`

# Linux
1. Select "Build" from vscode

## Run
Select "Run" and navigate to localhost:8080/helloWorld
