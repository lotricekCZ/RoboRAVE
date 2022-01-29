#!/bin/bash
home=`echo ~`
compiled_one=logic_motorduino/logic_motorduino.ino
path_to_compiler=$home/Arduino_program/arduino-1.8.9/arduino-builder
path_to_hardware=$home/Arduino_program/arduino-1.8.9/hardware
arduino15=$home/.arduino15
arduinoOTA=$arduino15/packages/arduino/tools/arduinoOTA/1.3.0
arduino=$home/Arduino_program/arduino-1.8.9
current_dir=`pwd`

while getopts f: flag
do
	case "${flag}" in
		f)	case "${OPTARG}" in
				stm) compiled_one=logic_stm/logic_stm.ino;;
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
	-tools $arduino/tools-builder \
	-tools $path_to_hardware/tools/avr \
	-tools $arduino15/packages \
	-built-in-libraries $arduino/libraries \
	-libraries $current_dir/libraries \
	-fqbn=arduino:avr:pro:cpu=8MHzatmega328 \
	-ide-version=10809 \
	-build-path $current_dir/build \
	-warnings=default \
	-prefs=build.warn_data_percentage=75 \
	-prefs=runtime.tools.arduinoOTA.path=$arduinoOTA \
	-prefs=runtime.tools.arduinoOTA-1.3.0.path=$arduinoOTA \
	-prefs=runtime.tools.avrdude.path=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17 \
	-prefs=runtime.tools.avrdude-6.3.0-arduino17.path=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17 \
	-prefs=runtime.tools.avr-gcc.path=$arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5 \
	-prefs=runtime.tools.avr-gcc-7.3.0-atmel3.6.1-arduino5.path=$arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5 \
	-verbose $compiled_one

cd $current_dir

$path_to_compiler \
	-compile \
	-logger=machine \
	-hardware $path_to_hardware \
	-hardware $arduino15/packages \
	-tools $arduino/tools-builder \
	-tools $path_to_hardware/tools/avr \
	-tools $arduino15/packages \
	-built-in-libraries $arduino/libraries \
	-libraries $current_dir/libraries \
	-fqbn=arduino:avr:pro:cpu=8MHzatmega328 \
	-ide-version=10809 \
	-build-path $current_dir/build \
	-warnings=default \
	-prefs=build.warn_data_percentage=75 \
	-prefs=runtime.tools.arduinoOTA.path=$arduinoOTA \
	-prefs=runtime.tools.arduinoOTA-1.3.0.path=$arduinoOTA \
	-prefs=runtime.tools.avrdude.path=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17 \
	-prefs=runtime.tools.avrdude-6.3.0-arduino17.path=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17 \
	-prefs=runtime.tools.avr-gcc.path=$arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5 \
	-prefs=runtime.tools.avr-gcc-7.3.0-atmel3.6.1-arduino5.path=$arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5 \
	-verbose $compiled_one
