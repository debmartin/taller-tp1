################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vista/Animacion.cpp \
../src/vista/Capa.cpp \
../src/vista/Dibujable.cpp \
../src/vista/EscenarioGrafico.cpp \
../src/vista/LimitesLogicos.cpp \
../src/vista/PersonajeDibujable.cpp \
../src/vista/Posicionable.cpp \
../src/vista/Renderizador.cpp \
../src/vista/Sprite.cpp \
../src/vista/VentanaGrafica.cpp 

OBJS += \
./src/vista/Animacion.o \
./src/vista/Capa.o \
./src/vista/Dibujable.o \
./src/vista/EscenarioGrafico.o \
./src/vista/LimitesLogicos.o \
./src/vista/PersonajeDibujable.o \
./src/vista/Posicionable.o \
./src/vista/Renderizador.o \
./src/vista/Sprite.o \
./src/vista/VentanaGrafica.o 

CPP_DEPS += \
./src/vista/Animacion.d \
./src/vista/Capa.d \
./src/vista/Dibujable.d \
./src/vista/EscenarioGrafico.d \
./src/vista/LimitesLogicos.d \
./src/vista/PersonajeDibujable.d \
./src/vista/Posicionable.d \
./src/vista/Renderizador.d \
./src/vista/Sprite.d \
./src/vista/VentanaGrafica.d 


# Each subdirectory must supply rules for building sources it contributes
src/vista/%.o: ../src/vista/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


