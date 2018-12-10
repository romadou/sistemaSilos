################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/DELAY_DHT.c" \
"../Sources/ESPERANDO.c" \
"../Sources/INICIALIZAR.c" \
"../Sources/MCUinit.c" \
"../Sources/MEF.c" \
"../Sources/MTIM.c" \
"../Sources/RECPARAMETROS.c" \
"../Sources/REC_UC.c" \
"../Sources/RTC.c" \
"../Sources/SCI.c" \
"../Sources/TPM.c" \
"../Sources/TRANS_UC.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/DELAY_DHT.c \
../Sources/ESPERANDO.c \
../Sources/INICIALIZAR.c \
../Sources/MCUinit.c \
../Sources/MEF.c \
../Sources/MTIM.c \
../Sources/RECPARAMETROS.c \
../Sources/REC_UC.c \
../Sources/RTC.c \
../Sources/SCI.c \
../Sources/TPM.c \
../Sources/TRANS_UC.c \
../Sources/main.c \

OBJS += \
./Sources/DELAY_DHT_c.obj \
./Sources/ESPERANDO_c.obj \
./Sources/INICIALIZAR_c.obj \
./Sources/MCUinit_c.obj \
./Sources/MEF_c.obj \
./Sources/MTIM_c.obj \
./Sources/RECPARAMETROS_c.obj \
./Sources/REC_UC_c.obj \
./Sources/RTC_c.obj \
./Sources/SCI_c.obj \
./Sources/TPM_c.obj \
./Sources/TRANS_UC_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/DELAY_DHT_c.obj" \
"./Sources/ESPERANDO_c.obj" \
"./Sources/INICIALIZAR_c.obj" \
"./Sources/MCUinit_c.obj" \
"./Sources/MEF_c.obj" \
"./Sources/MTIM_c.obj" \
"./Sources/RECPARAMETROS_c.obj" \
"./Sources/REC_UC_c.obj" \
"./Sources/RTC_c.obj" \
"./Sources/SCI_c.obj" \
"./Sources/TPM_c.obj" \
"./Sources/TRANS_UC_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/DELAY_DHT_c.d \
./Sources/ESPERANDO_c.d \
./Sources/INICIALIZAR_c.d \
./Sources/MCUinit_c.d \
./Sources/MEF_c.d \
./Sources/MTIM_c.d \
./Sources/RECPARAMETROS_c.d \
./Sources/REC_UC_c.d \
./Sources/RTC_c.d \
./Sources/SCI_c.d \
./Sources/TPM_c.d \
./Sources/TRANS_UC_c.d \
./Sources/main_c.d \

OBJS_OS_FORMAT += \
./Sources/DELAY_DHT_c.obj \
./Sources/ESPERANDO_c.obj \
./Sources/INICIALIZAR_c.obj \
./Sources/MCUinit_c.obj \
./Sources/MEF_c.obj \
./Sources/MTIM_c.obj \
./Sources/RECPARAMETROS_c.obj \
./Sources/REC_UC_c.obj \
./Sources/RTC_c.obj \
./Sources/SCI_c.obj \
./Sources/TPM_c.obj \
./Sources/TRANS_UC_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/DELAY_DHT_c.obj: ../Sources/DELAY_DHT.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/DELAY_DHT.args" -ObjN="Sources/DELAY_DHT_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/ESPERANDO_c.obj: ../Sources/ESPERANDO.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/ESPERANDO.args" -ObjN="Sources/ESPERANDO_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/INICIALIZAR_c.obj: ../Sources/INICIALIZAR.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/INICIALIZAR.args" -ObjN="Sources/INICIALIZAR_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUinit.args" -ObjN="Sources/MCUinit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/MEF_c.obj: ../Sources/MEF.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MEF.args" -ObjN="Sources/MEF_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/MTIM_c.obj: ../Sources/MTIM.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MTIM.args" -ObjN="Sources/MTIM_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/RECPARAMETROS_c.obj: ../Sources/RECPARAMETROS.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/RECPARAMETROS.args" -ObjN="Sources/RECPARAMETROS_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/REC_UC_c.obj: ../Sources/REC_UC.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/REC_UC.args" -ObjN="Sources/REC_UC_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/RTC_c.obj: ../Sources/RTC.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/RTC.args" -ObjN="Sources/RTC_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SCI_c.obj: ../Sources/SCI.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SCI.args" -ObjN="Sources/SCI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TPM_c.obj: ../Sources/TPM.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TPM.args" -ObjN="Sources/TPM_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TRANS_UC_c.obj: ../Sources/TRANS_UC.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TRANS_UC.args" -ObjN="Sources/TRANS_UC_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


