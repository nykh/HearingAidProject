################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /opt/ti/ccsv6/tools/compiler/c6000_7.4.8

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./Exercise0.obj" \
"./ISRs.obj" \
"./OMAPL138_Support_DSP.obj" \
"./StartUp.obj" \
"./amplitude_selection.obj" \
"./amplitude_selection_data.obj" \
"./amplitude_selection_initialize.obj" \
"./amplitude_selection_terminate.obj" \
"./eml_rand_mt19937ar_stateful.obj" \
"./mean.obj" \
"./rand.obj" \
"./rtGetInf.obj" \
"./rtGetNaN.obj" \
"./rt_nonfinite.obj" \
"./sortrows.obj" \
"./vectors.obj" \
"../link6748.cmd" \
-l"libc.a" \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
amplitude_selection.out \

EXE_OUTPUTS__QUOTED += \
"amplitude_selection.out" \

BIN_OUTPUTS += \
amplitude_selection.hex \

BIN_OUTPUTS__QUOTED += \
"amplitude_selection.hex" \


# All Target
all: amplitude_selection.out

# Tool invocations
amplitude_selection.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"/opt/ti/ccsv6/tools/compiler/c6000_7.4.8/bin/cl6x" -mv6740 --abi=coffabi -g --display_error_number --diag_warning=225 --diag_wrap=off -z -m"amplitude_selection.map" -i"/opt/ti/ccsv6/tools/compiler/c6000_7.4.8/lib" -i"/opt/ti/ccsv6/tools/compiler/c6000_7.4.8/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="amplitude_selection_linkInfo.xml" --rom_model -o "amplitude_selection.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

amplitude_selection.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C6000 Hex Utility'
	"/opt/ti/ccsv6/tools/compiler/c6000_7.4.8/bin/hex6x"  -o "amplitude_selection.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "Exercise0.pp" "ISRs.pp" "OMAPL138_Support_DSP.pp" "StartUp.pp" "amplitude_selection.pp" "amplitude_selection_data.pp" "amplitude_selection_initialize.pp" "amplitude_selection_terminate.pp" "eml_rand_mt19937ar_stateful.pp" "mean.pp" "rand.pp" "rtGetInf.pp" "rtGetNaN.pp" "rt_nonfinite.pp" "sortrows.pp" 
	-$(RM) "Exercise0.obj" "ISRs.obj" "OMAPL138_Support_DSP.obj" "StartUp.obj" "amplitude_selection.obj" "amplitude_selection_data.obj" "amplitude_selection_initialize.obj" "amplitude_selection_terminate.obj" "eml_rand_mt19937ar_stateful.obj" "mean.obj" "rand.obj" "rtGetInf.obj" "rtGetNaN.obj" "rt_nonfinite.obj" "sortrows.obj" "vectors.obj" 
	-$(RM) "vectors.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

