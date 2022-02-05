#!/bin/bash
home=`echo ~`
compiled_one=logic_motorduino/logic_motorduino.ino
path_to_compiler=$home/Arduino_program/arduino-1.8.9/arduino-builder
path_to_hardware=$home/Arduino_program/arduino-1.8.9/hardware
arduino15=$home/.arduino15
arduinoOTA=$arduino15/packages/arduino/tools/arduinoOTA/1.3.0
arduino=$home/Arduino_program/arduino-1.8.9
tools_selected=""
current_dir=`pwd`
tools=("-tools $arduino/tools-builder" \
		"-tools /home/jakub/Arduino_program/arduino-1.8.9/hardware/tools/avr" \
		"-tools /home/jakub/.arduino15/packages"
		)

prefs=("-prefs=build.warn_data_percentage=75" \
	# STM
	"-prefs=runtime.tools.arm-none-eabi-gcc.path=$arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1" \
	"-prefs=runtime.tools.arm-none-eabi-gcc-4.8.3-2014q1.path=$arduino15/packages/arduino/tools/arm-none-eabi-gcc/4.8.3-2014q1" \
	"-prefs=runtime.tools.stm32tools.path=$arduino15/packages/stm32duino/tools/stm32tools/2020.12.26" \
	"-prefs=runtime.tools.stm32tools-2020.12.26.path=$arduino15/packages/stm32duino/tools/stm32tools/2020.12.26" \
	# Arduino
	"-prefs=runtime.tools.arduinoOTA.path=$arduinoOTA " \
	"-prefs=runtime.tools.arduinoOTA-1.3.0.path=$arduinoOTA " \
	"-prefs=runtime.tools.avrdude.path=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17 " \
	"-prefs=runtime.tools.avrdude-6.3.0-arduino17.path=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17 " \
	"-prefs=runtime.tools.avr-gcc.path=$arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5 " \
	"-prefs=runtime.tools.avr-gcc-7.3.0-atmel3.6.1-arduino5.path=$arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5 " \
	)

fqbn="arduino:avr:pro:cpu=8MHzatmega328"

tools_selected="$tools_selected ${tools[*]}"
prefs_selected="${tools[0]} ${tools[5]} ${tools[6]} ${tools[7]} ${tools[8]} ${tools[9]} ${tools[10]} "
echo "$tools_selected"


#path_to_stm_compiler=/home/jakub/Arduino_program/arduino-1.8.9/arduino-builder\
#	-dump-prefs\
#	-logger=machine\
#	-hardware /home/jakub/Arduino_program/arduino-1.8.9/hardware\
#	-hardware /home/jakub/.arduino15/packages\
#	-built-in-libraries /home/jakub/Arduino_program/arduino-1.8.9/libraries\
#	-libraries /home/jakub/_programovani/C++/Arduino/libraries\
#	-fqbn=stm32duino:STM32F1:genericSTM32F103C:device_variant=STM32F103C8,upload_method=STLinkMethod,cpu_speed=speed_72mhz,opt=o3std\
#	-ide-version=10809\
#	-build-path /tmp/arduino_build_668116\
#	-warnings=default\
#	-build-cache /tmp/arduino_cache_509306\
#	-verbose /home/jakub/_programovani/Python/RoboRAVE/hardware_interfaces/arduino/logic_stm/logic_stm.ino
#path_to_stm_hardware=/home/jakub/Arduino_program/arduino-1.8.9/arduino-builder\
#	-compile\
#	-logger=machine\
#	-hardware /home/jakub/Arduino_program/arduino-1.8.9/hardware\
#	-hardware /home/jakub/.arduino15/packages\
#	-tools /home/jakub/Arduino_program/arduino-1.8.9/tools-builder\
#	-tools /home/jakub/Arduino_program/arduino-1.8.9/hardware/tools/avr\
#	-tools /home/jakub/.arduino15/packages\
#	-built-in-libraries /home/jakub/Arduino_program/arduino-1.8.9/libraries\
#	-libraries /home/jakub/_programovani/C++/Arduino/libraries\
#	-fqbn=stm32duino:STM32F1:genericSTM32F103C:device_variant=STM32F103C8,upload_method=STLinkMethod,cpu_speed=speed_72mhz,opt=o3std\
#	-ide-version=10809\
#	-build-path /tmp/arduino_build_668116\
#	-warnings=default\
#	-build-cache /tmp/arduino_cache_509306\
#	-verbose /home/jakub/_programovani/Python/RoboRAVE/hardware_interfaces/arduino/logic_stm/logic_stm.ino


while getopts f: flag
do
	case "${flag}" in
		f)	case "${OPTARG}" in
				stm) compiled_one=logic_stm/logic_stm.ino; \
					prefs_selected="${tools[0]} ${tools[1]} ${tools[2]} ${tools[3]} ${tools[4]} "; \
					fqbn="stm32duino:STM32F1:genericSTM32F103C:device_variant=STM32F103C8,upload_method=STLinkMethod,cpu_speed=speed_72mhz,opt=o3std";;
				motor) compiled_one=logic_motorduino/logic_motorduino.ino;;
				ir) compiled_one=logic_daters/logic_daters.ino;;
				gnd) compiled_one=logic_daters/logic_daters.ino;;
			esac
    esac
done

path_to_hardware=`realpath --relative-to="$current_dir" "$path_to_hardware"`
path_to_compiler=`realpath --relative-to="$current_dir" "$path_to_compiler"`
arduino15=`realpath --relative-to="$current_dir" "$arduino15"`
arduinoOTA=`realpath --relative-to="$current_dir" "$arduinoOTA"`
arduino=`realpath --relative-to="$current_dir" "$arduino"`

cd $current_dir
echo $arduino15
echo $current_dir
echo $path_to_hardware

$path_to_compiler \
	-dump-prefs \
	-logger=machine \
	-hardware $path_to_hardware \
	-hardware $arduino15/packages \
	$tools_selected \
	-built-in-libraries $arduino/libraries \
	-libraries $current_dir/libraries \
	-fqbn=$fqbn \
	-ide-version=10809 \
	-build-path $current_dir/build \
	-warnings=default \
	$prefs_selected \
	-verbose $compiled_one

cd $current_dir

$path_to_compiler \
	-compile \
	-logger=machine \
	-hardware $path_to_hardware \
	-hardware $arduino15/packages \
	$tools_selected \
	-built-in-libraries $arduino/libraries \
	-libraries $current_dir/libraries \
	-fqbn=$fqbn \
	-ide-version=10809 \
	-build-path $current_dir/build \
	-warnings=default \
	$prefs_selected \
	-verbose $compiled_one
