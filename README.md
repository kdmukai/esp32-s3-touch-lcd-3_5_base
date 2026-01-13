# ESP-IDF Dev Environment
This repository provides a Docker-based development environment for ESP32 projects using
ESP-IDF.


## Purpose
Containerize the ESP-IDF build toolchain while keeping device flashing and debugging on
the host machine. This approach provides:

- Consistent build environment across different development machines.
- Isolated dependencies without polluting the host system.

## Development Strategy

### Build in Container
- Compile ESP32 projects inside the DevContainer using Espressif's Docker image with all
  ESP-IDF tools pre-installed.
- Generated build artifacts are accessible via mounted volumes.

### Flash on Host
- Use `esptool.py` installed locally to flash the compiled binaries to the physical ESP32
  device.
- Direct USB/serial access avoids container complexities and limitations (e.g. cannot pass
  usbserial from macOS into Docker).

### Debug on Host
- Run live debugging tools (OpenOCD, GDB, serial monitors) directly on the host.
- Maintains reliable connection to hardware without container networking overhead.

This hybrid approach leverages containerization benefits for the build process while
maintaining straightforward hardware interaction on the host.


## Setup
Meant to run within VSCode with the "Dev Containers" extension which manages the Docker
container and places your VSCode editor context within the container.


### Install the local python dependencies
* Create virtualenv
* `pip install -r requirements.txt`


### Build and launch the container
Open the VSCode Command Palette (`CTRL+SHIFT+P`) and search for "Dev Containers: Rebuild
and Reopen in Container".

When VSCode reloads, your context will be inside the dev container and the ESP-IDF
extension will be running in VSCode, already wired up to interact with the ESP-IDF tools
in the container.

You can exit the container context via Command Palette -> "Dev Containers: Reopen Folder
Locally".


# Build and Flash
## Build
In the Dev Container context, VSCode will have the ESP-IDF extension active. Click it and select "Build Project".

## Flash
Exit the Dev Container context. We'll use our local dev `esptool` from the python virtualenv to flash the device:

```bash
python -m esptool --chip esp32s3 -b 460800 --before default-reset --after hard-reset write-flash --flash-mode dio --flash-size detect --flash-freq 40m 0x0 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin 0x10000 build/lvgl_example.bin
```
