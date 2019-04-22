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
[B-L475E-IOT01A](https://www.st.com/en/evaluation-tools/b-l475e-iot01a.html)

## Example
Blink user led

## Manual

### Toolchain
* Download the gcc-arm-none-eabi toolchain from [ARM official website](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). Unpack it to wherever you want. In this case I put it into "/usr/local/install".
```sh
tar -jxvf gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2 -C /usr/local/install
```
### Debugger
* Download the Open On-Chip Debugger binary packages from [GNU MCU Eclipse Project](https://github.com/gnu-mcu-eclipse/openocd/releases). Unpack it to wherever you want. In this case I put it into "/usr/local/install".
```sh
tar -zxvf gnu-mcu-eclipse-openocd-0.10.0-11-20190118-1134-centos64.tgz -C /usr/local/install
```
* Copy the "60-openocd.rules" file in "contrib" folder to "/etc/udev/rules.d/" directory. Then reload the udev rules.
```sh
cp /usr/local/install/gnu-mcu-eclipse/openocd/0.10.0-11-20190118-1134/contrib/60-openocd.rules /etc/udev/rules.d/
udevadm control --reload
```
### IDE
* Download open-jdk from [oracle official website](jdk.java.net). Unpack it to wherever you want. In this case I put it into "/usr/local/install".
```sh
tar -zxvf openjdk-12.0.1_linux-x64_bin.tar.gz -C /usr/local/install
```
* Download [Eclipse IDE for C/C++ Developers](https://www.eclipse.org/downloads/packages/). Unpack it to wherever you want. In this case I put it into "/usr/local/install".
```sh
tar -zxvf eclipse-cpp-2019-03-R-linux-gtk-x86_64.tar.gz -C /usr/local/install
```
* Add the jvm executable file path parameter like follows in "eclipse.ini" file.
![image](https://github.com/otakann/STM32-GNU-Project-Sample/blob/master/raw/eclipse_ini.png)
* Create a new "desktop" configuration file named "eclipse.desktop" like follows in "/usr/share/applications". Then you can launch eclipse from application shortcut.
![image](https://github.com/otakann/STM32-GNU-Project-Sample/blob/master/raw/eclipse_desktop.png)
* Launch the eclipse IDE and click the "Help->Eclipse Marketplace" tab. Then search the "GNU MCU Eclipse" plug-in and install it.
![image](https://github.com/otakann/STM32-GNU-Project-Sample/blob/master/raw/GNU_MCU_eclipse.png) 
### STM32Cube
* Download STM32Cube MCU Package from [ST official website](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html#tools-software). Please select the package according to your MCU model. The MCU of my board(B-L475E-IOT01A) is STM32L475VGT6. So I choose the file "en.stm32cubel4.zip".
* Use the file "stm32l4xx.h" in "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Device/ST/STM32L4xx/Include" to replace the same  named file in "led_blink/cmsis/device/inc". And so on, if your MCU is STM32F4 series, this file maybe "stm32f4xx.h". Then uncomment the specific macro to indicate your target MCU. In my case I choose "STM32L475xx".
