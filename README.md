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
#### CMSIS
* Copy the file "stm32l4xx.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Device/ST/STM32L4xx/Include" into  "led_blink/cmsis/device/inc". And so on, if your MCU is STM32F2 series, this file maybe "stm32f2xx.h". Then uncomment the specific macro to indicate your target MCU. In my case I choose "STM32L475xx".
* Copy the file "stm32l475xx.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Device/ST/STM32L4xx/Include" into "led_blink/cmsis/device/inc". And so on, this file is chosen according to your MCU model.
* Copy the file "system_stm32l4xx.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Device/ST/STM32L4xx/Include" into "led_blink/cmsis/device/inc". And so on, if your MCU is STM32F4 series, this file maybe "system_stm32f4xx.h".
* Copy the file "system_stm32l4xx.c" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Device/ST/STM32L4xx/Source/Templates" into "led_blink/cmsis/device/src". And so on, if your MCU is STM32F1 series, this file maybe "system_stm32f1xx.c". Then change HSE value and Vector table offset value in this file. HSE is the default value of external oscillator (in Hz). Please check the hardware of your board. Normally, vector table offset value will be 0. But if you do not want to put the farmware at the head of the flash (such as there is another bootloader), you may change it.  
* Copy the file "core_cm4.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Include" into "led_blink/cmsis/device/inc". And so on, this file is chosen according to your MCU model (STM32L4 series is cotex-M4 processor).
* Copy the file "cmsis_gcc.h","core_cmFunc.h","core_cmInstr.h" and "core_cmSimd.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/CMSIS/Include" into "led_blink/cmsis/device/inc".
* Copy the file "cmsis_os2.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" into "led_blink/cmsis/rtos/inc".
* Implement your own RTOS wrapper for CMSIS-RTOS v2 in "led_blink/cmsis/rtos/src". In this case I write a simple package for FreeRTOS. You can also copy the file "cmsis_os2.c" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" directly. 
### Hardware driver
* ST provide three forms of driver API. Standard Peripheral Library, Cube HAL APIs and Cube low layer APIs. In this case I use the low layer APIs. 
* Copy all of the files such as "stm32l4xx_ll_xxx.h" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/STM32L4xx_HAL_Driver/Inc" into "led_blink/package/ll_driver/inc".
* Copy all of the files such as "stm32l4xx_ll_xxx.c" from "en.stm32cubel4/STM32Cube_FW_L4_V1.13.0/Drivers/STM32L4xx_HAL_Driver/Src" into "led_blink/package/ll_driver/src".
