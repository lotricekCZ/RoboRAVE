#!/bin/bash
home=`echo ~`
binary=build/logic_motorduino.ino.hex
path_to_avrdude=$home/Arduino_program/arduino-1.8.9/arduino-builder
path_to_hardware=$home/Arduino_program/arduino-1.8.9/hardware
arduino15=$home/.arduino15
avrdude_dir=$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17
avrdude=$avrdude_dir/bin/avrdude
configure=$avrdude_dir/etc/avrdude.conf
current_dir=`pwd`

#~ while getopts f: flag
#~ do
	#~ case "${flag}" in
		#~ f)	case "${OPTARG}" in
				#~ stm) compiled_one=logic_stm/logic_stm.ino;;
				#~ motor) compiled_one=logic_motorduino/logic_motorduino.ino;;
				#~ ir) compiled_one=logic_daters/logic_daters.ino;;
				#~ gnd) compiled_one=logic_daters/logic_daters.ino;;
			#~ esac
    #~ esac
#~ done

arduino15=`realpath --relative-to="$current_dir" "$arduino15"`


cd $current_dir
$arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude \
	-C/home/jakub/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf \
	-v \
	-patmega328p \
	-carduino \
	-P/dev/ttyUSB0 \
	-b57600 \
	-D \
	-Uflash:w:$binary:i 
