################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/modelo/CargadorDeObjetos.cpp \
../src/modelo/Observable.cpp \
../src/modelo/Observador.cpp \
../src/modelo/Personaje.cpp \
../src/modelo/Posicionador.cpp \
../src/modelo/Vector2f.cpp 

OBJS += \
./src/modelo/CargadorDeObjetos.o \
./src/modelo/Observable.o \
./src/modelo/Observador.o \
./src/modelo/Personaje.o \
./src/modelo/Posicionador.o \
./src/modelo/Vector2f.o 

CPP_DEPS += \
./src/modelo/CargadorDeObjetos.d \
./src/modelo/Observable.d \
./src/modelo/Observador.d \
./src/modelo/Personaje.d \
./src/modelo/Posicionador.d \
./src/modelo/Vector2f.d 


# Each subdirectory must supply rules for building sources it contributes
src/modelo/%.o: ../src/modelo/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


