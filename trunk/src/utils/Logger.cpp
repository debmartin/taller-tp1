/*
 * Logger.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: ariel
 */

#include "Logger.h"

#include <string>

#include "../Configuracion.h"

#define DEBUG_MODE false

Logger* Logger::logger = NULL;
int Logger::limit = 100000;

Logger::Logger() {
	//Logger::limit = cantRegistros;
	Logger::nextFile = Logger::setNextFile();
	Logger::count = 0;
	std::string c;


	ioFile.open("logger.log", std::ios_base::in);
	if (ioFile.is_open())
		while(!ioFile.eof()){
			getline(ioFile,c);
			if(c.compare(""))
				Logger::count++;
		}


	ioFile.close();
	ioFile.open("logger.log", std::ios_base::out | std::ios_base::app);
}

Logger* Logger::getInstance(){
	if ( Logger::logger  == NULL )
		Logger::logger = new Logger();
	return Logger::logger;
}

void Logger::setLimit(int cantRegistros) {
	Logger::limit = cantRegistros;
}

Logger::~Logger(){
	ioFile.close();
}

void Logger::renameFile(){
	ioFile.close();

	std::stringstream file;
	file << "logger" << Logger::nextFile << ".log";

	rename("logger.log", file.str().c_str());

	Logger::nextFile ++;
	Logger::count = 0;

	ioFile.open("logger.log", std::ios_base::out | std::ios_base::app);
}

std::string Logger::getTime(){
	time_t rawtime;
	time(&rawtime);
	struct tm* timestamp = localtime(&rawtime);

	std::stringstream out;
	if (timestamp->tm_mday < 10)
		out << "0" << timestamp->tm_mday << "/" ;
	else out << timestamp->tm_mday << "/" ;
	if (timestamp->tm_mon < 10)
		out << "0" << timestamp->tm_mon + 1 << "/" ;
	else out << timestamp->tm_mon + 1 << "/" ;
	out << timestamp->tm_year + 1900;
	out << " ";
	if (timestamp->tm_hour < 10 )
		out << "0" << timestamp->tm_hour << ":"  ;
	else out << timestamp->tm_hour << ":";
	if (timestamp->tm_min < 10 )
		out << "0" << timestamp->tm_min << ":" ;
	else out << timestamp->tm_min << ":";
	if (timestamp->tm_sec < 10 )
		out << "0" << timestamp->tm_sec ;
	else out << timestamp->tm_sec;
	out << " ";
	return out.str();
}

int Logger::setNextFile(){
	bool right = false;
	int i = 1;
	while (!right){
		std::stringstream file;
		file << "logger" << i << ".log";

		if ( access(file.str().c_str(),0) != 0)
			right = true;
		else i++;
	}
	return i;
}

void Logger::debug(std::string  message){
	std::string key = "DEBUG";
	Logger::insert(key,message);
}

void Logger::debug(ObjetoJson* unObjetoJson) {
	this->debug(unObjetoJson->toString());
}

void Logger::debug(string unString, int unEntero) {
    ostringstream stream;
    stream <<unString<<": "<<unEntero;
    this->debug(stream.str());
}

void Logger::debug(string unString, double unDouble) {
    ostringstream stream;
    stream <<unString<<": "<<unDouble;
    this->debug(stream.str());
}

void Logger::debugArgs(const char * format, ... )
{
    char sMessage[256];
    va_list args;
    va_start (args, format);
    vsprintf (sMessage,format, args);
    va_end (args);
    this->debug(sMessage);
}

void Logger::info(std::string message){
	std::string key = "INFO";
	Logger::insert(key,message);
}

void Logger::info(ObjetoJson* unObjetoJson) {
	this->info(unObjetoJson->toString());
}

void Logger::info(string unString, int unEntero) {
    ostringstream stream;
    stream <<unString<<": "<<unEntero;
    this->info(stream.str());
}

void Logger::info(string unString, double unDouble) {
    ostringstream stream;
    stream <<unString<<": "<<unDouble;
    this->info(stream.str());
}

void Logger::infoArgs(const char * format, ... )
{
    char sMessage[256];
    va_list args;
    va_start (args, format);
    vsprintf (sMessage,format, args);
    va_end (args);
    this->info(sMessage);
}

void Logger::error(std::string  message){
	std::string key = "ERROR";
	Logger::insert(key,message);
}

void Logger::error(ObjetoJson* unObjetoJson) {
	this->error(unObjetoJson->toString());
}

void Logger::error(string unString, int unEntero) {
    ostringstream stream;
    stream <<unString<<": "<<unEntero;
    this->error(stream.str());
}

void Logger::error(string unString, double unDouble) {
    ostringstream stream;
    stream <<unString<<": "<<unDouble;
    this->error(stream.str());
}

void Logger::errorArgs(const char * format, ... )
{
    char sMessage[256];
    va_list args;
    va_start (args, format);
    vsprintf (sMessage,format, args);
    va_end (args);
    this->error(sMessage);
}

void Logger::insert(std::string& key, std::string& value){
	if (ioFile.is_open()) {

		#ifndef DEBUG_MODE
			std::cout << Logger::getTime() << key << " : " << value << std::endl;
	    #endif

		this->nivel_log = Configuracion::getInstance()->getNivelLogger();

		if ( this->nivel_log == "ERROR")
		{
			if ( key == "ERROR" )
			{
				ioFile << Logger::getTime() << key << " : " << value << std::endl;
				ioFile.flush();
				Logger::count++;
			}
		}
		else if ( this->nivel_log == "INFO")
		{
			if ( key == "ERROR" || key == "INFO")
				{
					ioFile << Logger::getTime() << key << " : " << value << std::endl;
					ioFile.flush();
					Logger::count++;
				}

		}
		else if ( this->nivel_log == "DEBUG")
		{
			ioFile << Logger::getTime() << key << " : " << value << std::endl;
			ioFile.flush();
			Logger::count++;
		}

		if (Logger::count >= Logger::limit) Logger::renameFile();

	} else { }
}
