##-----------------------------LICENSE NOTICE------------------------------------
##  This file is part of CPCtelera: An Amstrad CPC Game Engine 
##  Copyright (C) 2018 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU Lesser General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU Lesser General Public License for more details.
##
##  You should have received a copy of the GNU Lesser General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.
##------------------------------------------------------------------------------
############################################################################
##                        CPCTELERA ENGINE                                ##
##                 Automatic compression utilities                        ##
##------------------------------------------------------------------------##
## This file is intended for users to automate the generation of          ##
## compressed files and their inclusion in users' projects.               ##
############################################################################

## COMPRESSION EXAMPLE (Uncomment lines to use)
##

## First 3 calls to ADD2PACK add enemy, hero and background
## graphics (previously converted to binary data) into the 
## compressed group 'mygraphics'. After that, call to PACKZX7B
## compresses all the data and generates an array with the result
## that is placed in src/mygraphics.c & src/mygraphics.h, ready
## to be included and used by other modules.
##
#$(eval $(call ADD2PACK,mygraphics,gfx/enemy.bin))
#$(eval $(call ADD2PACK,mygraphics,gfx/hero.bin))
$(eval $(call ADD2PACK,lvl0_pack, src/tilemaps/lvl0.bin))
$(eval $(call PACKZX7B,lvl0_pack,src/tilemaps))

$(eval $(call ADD2PACK,lvl0_2_pack, src/tilemaps/lvl0_2.bin))
$(eval $(call PACKZX7B,lvl0_2_pack,src/tilemaps))

## BOT LEFT

$(eval $(call ADD2PACK,bot_left_1_pack, src/tilemaps/bot_left_1.bin))
$(eval $(call PACKZX7B,bot_left_1_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_left_2_pack, src/tilemaps/bot_left_2.bin))
$(eval $(call PACKZX7B,bot_left_2_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_left_3_pack, src/tilemaps/bot_left_3.bin))
$(eval $(call PACKZX7B,bot_left_3_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_left_4_pack, src/tilemaps/bot_left_4.bin))
$(eval $(call PACKZX7B,bot_left_4_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_left_5_pack, src/tilemaps/bot_left_5.bin))
$(eval $(call PACKZX7B,bot_left_5_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_left_6_pack, src/tilemaps/bot_left_6.bin))
$(eval $(call PACKZX7B,bot_left_6_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_left_extra_pack, src/tilemaps/bot_left_extra.bin))
$(eval $(call PACKZX7B,bot_left_extra_pack,src/tilemaps))

## BOT RIGHT

$(eval $(call ADD2PACK,bot_right_1_pack, src/tilemaps/bot_right_1.bin))
$(eval $(call PACKZX7B,bot_right_1_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_right_2_pack, src/tilemaps/bot_right_2.bin))
$(eval $(call PACKZX7B,bot_right_2_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_right_3_pack, src/tilemaps/bot_right_3.bin))
$(eval $(call PACKZX7B,bot_right_3_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_right_4_pack, src/tilemaps/bot_right_4.bin))
$(eval $(call PACKZX7B,bot_right_4_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_right_5_pack, src/tilemaps/bot_right_5.bin))
$(eval $(call PACKZX7B,bot_right_5_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_right_6_pack, src/tilemaps/bot_right_6.bin))
$(eval $(call PACKZX7B,bot_right_6_pack,src/tilemaps))

$(eval $(call ADD2PACK,bot_right_extra_pack, src/tilemaps/bot_right_extra.bin))
$(eval $(call PACKZX7B,bot_right_extra_pack,src/tilemaps))

## TOP LEFT

$(eval $(call ADD2PACK,top_left_1_pack, src/tilemaps/top_left_1.bin))
$(eval $(call PACKZX7B,top_left_1_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_2_pack, src/tilemaps/top_left_2.bin))
$(eval $(call PACKZX7B,top_left_2_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_3_pack, src/tilemaps/top_left_3.bin))
$(eval $(call PACKZX7B,top_left_3_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_4_pack, src/tilemaps/top_left_4.bin))
$(eval $(call PACKZX7B,top_left_4_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_5_pack, src/tilemaps/top_left_5.bin))
$(eval $(call PACKZX7B,top_left_5_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_6_pack, src/tilemaps/top_left_6.bin))
$(eval $(call PACKZX7B,top_left_6_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_7_pack, src/tilemaps/top_left_7.bin))
$(eval $(call PACKZX7B,top_left_7_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_left_extra_pack, src/tilemaps/top_left_extra.bin))
$(eval $(call PACKZX7B,top_left_extra_pack,src/tilemaps))

##TOP RIGHT

$(eval $(call ADD2PACK,top_right_1_pack, src/tilemaps/top_right_1.bin))
$(eval $(call PACKZX7B,top_right_1_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_right_2_pack, src/tilemaps/top_right_2.bin))
$(eval $(call PACKZX7B,top_right_2_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_right_3_pack, src/tilemaps/top_right_3.bin))
$(eval $(call PACKZX7B,top_right_3_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_right_4_pack, src/tilemaps/top_right_4.bin))
$(eval $(call PACKZX7B,top_right_4_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_right_5_pack, src/tilemaps/top_right_5.bin))
$(eval $(call PACKZX7B,top_right_5_pack,src/tilemaps))

$(eval $(call ADD2PACK,top_right_extra_pack, src/tilemaps/top_right_extra.bin))
$(eval $(call PACKZX7B,top_right_extra_pack,src/tilemaps))



$(eval $(call ADD2PACK,bot_right_left_power_up, src/tilemaps/bot_right_left_power_up.bin))
$(eval $(call PACKZX7B,bot_right_left_power_up_pack,src/tilemaps))


$(eval $(call ADD2PACK,top_right_left_power_up, src/tilemaps/top_right_left_power_up.bin))
$(eval $(call PACKZX7B,top_right_left_power_up_pack,src/tilemaps))


$(eval $(call ADD2PACK,top_bot_left_power_up, src/tilemaps/top_bot_left_power_up.bin))
$(eval $(call PACKZX7B,top_bot_left_power_up_pack,src/tilemaps))


$(eval $(call ADD2PACK,top_bot_right_power_up, src/tilemaps/top_bot_right_power_up.bin))
$(eval $(call PACKZX7B,top_bot_right_power_up_pack,src/tilemaps))

$(eval $(call ADD2PACK,boss1_pack, src/tilemaps/boss1.bin))
$(eval $(call PACKZX7B,boss1_pack,src/tilemaps))

$(eval $(call ADD2PACK,main_screen_pack, src/sprites/main.bin))
$(eval $(call PACKZX7B,main_screen_pack,src/tilemaps))




############################################################################
##              DETAILED INSTRUCTIONS AND PARAMETERS                      ##
##------------------------------------------------------------------------##
##                                                                        ##
## Macros used for compression are ADD2PACK and PACKZX7B:                 ##
##                                                                        ##
##	ADD2PACK: Adds files to packed (compressed) groups. Each call to this ##
##  		  macro will add a file to a named compressed group.          ##
##  PACKZX7B: Compresses all files in a group into a single binary and    ##
##            generates a C-array and a header to comfortably use it from ##
##            inside your code.                                           ##
##                                                                        ##
##------------------------------------------------------------------------##
##                                                                        ##
##  $(eval $(call ADD2PACK,<packname>,<file>))                            ##
##                                                                        ##
##		Sequentially adds <file> to compressed group <packname>. Each     ##
## call to this macro adds a new <file> after the latest one added.       ##
## packname could be any valid C identifier.                              ##
##                                                                        ##
##  Parameters:                                                           ##
##  (packname): Name of the compressed group where the file will be added ##
##  (file)    : File to be added at the end of the compressed group       ##
##                                                                        ##
##------------------------------------------------------------------------##
##                                                                        ##
##  $(eval $(call PACKZX7B,<packname>,<dest_path>))                       ##
##                                                                        ##
##		Compresses all files in the <packname> group using ZX7B algorithm ##
## and generates 2 files: <packname>.c and <packname>.h that contain a    ##
## C-array with the compressed data and a header file for declarations.   ##
## Generated files are moved to the folder <dest_path>.                   ##
##                                                                        ##
##  Parameters:                                                           ##
##  (packname) : Name of the compressed group to use for packing          ##
##  (dest_path): Destination path for generated output files              ##
##                                                                        ##
############################################################################
##                                                                        ##
## Important:                                                             ##
##  * Do NOT separate macro parameters with spaces, blanks or other chars.##
##    ANY character you put into a macro parameter will be passed to the  ##
##    macro. Therefore ...,src/sprites,... will represent "src/sprites"   ##
##    folder, whereas ...,  src/sprites,... means "  src/sprites" folder. ##
##  * You can omit parameters by leaving them empty.                      ##
##  * Parameters (4) and (5) are optional and generally not required.     ##
############################################################################
