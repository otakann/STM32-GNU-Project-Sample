# Project Sample of stm32 MCU program develop

## What is this
Step to show how to use free tools to code , build and debug stm32 MCU program.

## Environment
* [Ubuntu](https://www.ubuntu.com/download/desktop)
* [Eclipse IDE for C/C++ Developers](https://www.eclipse.org/downloads/packages/)
* [gcc-arm-none-eabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
* [openocd](https://github.com/gnu-mcu-eclipse/openocd/releases)

## SDK
* [STM32Cube MCU Package](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html#tools-software)
* [FreeRTOS](https://www.freertos.org/a00104.html)

## Evaluation board
* [B-L475E-IOT01A](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html)

## Example
Blink user led

## Manual
* Download the gcc-arm-none-eabi toolchain from [ARM official website](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). Unpack it to wherever you want. In this case I put it in "/usr/local/install".
```sh
tar -jxvf gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 -C /usr/local/install
```
* Download the Open On-Chip Debugger binary packages from [GNU MCU Eclipse Project](https://github.com/gnu-mcu-eclipse/openocd/releases). Unpack it to wherever you want. In this case I put it in "/usr/local/install".
```sh
tar -zxvf gnu-mcu-eclipse-openocd-0.10.0-11-20190118-1134-centos64.tgz -C /usr/local/install
```
* Copy the "60-openocd.rules" file in "contrib" folder to "/etc/udev/rules.d/" directory. Then reload the udev rules.
```sh
cp /usr/local/install/gnu-mcu-eclipse/openocd/0.10.0-11-20190118-1134/contrib/60-openocd.rules /etc/udev/rules.d/
udevadm control --reload
```
