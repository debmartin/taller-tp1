################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/json/CapaDef.cpp \
../src/json/EscenarioDef.cpp \
../src/json/ObjetoJson.cpp \
../src/json/Parser.cpp \
../src/json/PersonajeDef.cpp \
../src/json/SpriteDef.cpp \
../src/json/VentanaDef.cpp 

OBJS += \
./src/json/CapaDef.o \
./src/json/EscenarioDef.o \
./src/json/ObjetoJson.o \
./src/json/Parser.o \
./src/json/PersonajeDef.o \
./src/json/SpriteDef.o \
./src/json/VentanaDef.o 

CPP_DEPS += \
./src/json/CapaDef.d \
./src/json/EscenarioDef.d \
./src/json/ObjetoJson.d \
./src/json/Parser.d \
./src/json/PersonajeDef.d \
./src/json/SpriteDef.d \
./src/json/VentanaDef.d 


# Each subdirectory must supply rules for building sources it contributes
src/json/%.o: ../src/json/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


