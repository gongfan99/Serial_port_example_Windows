/**
    Serial_port_example_Windows.cc
    Purpose: a C++ example to operate the serial port for Windows

    @author Fan Gong
    @version 1.0 07/03/18 
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <strsafe.h>

int main() {
  std::string commPortStr = "COM1";
  HANDLE hComm;
  try {
    // open the serial port
    hComm = CreateFile(
      commPortStr.data(),
      GENERIC_READ || GENERIC_WRITE,
      0, // dwShareMode, not share
      NULL, // ipSecurityAttributes, not inherited by child process
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL // no template file
    );
    if (hComm == INVALID_HANDLE_VALUE) throw std::runtime_error("Failed to open " + commPortStr);
    
    // set Device-Control Block
    DCB dcb = {0};
    if (!GetCommState(hComm, &dcb)) throw std::runtime_error("Failed to read Device-Control Block of " + commPortStr);
    dcb.BaudRate = CBR_9600;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    dcb.fOutX = false;
    dcb.fInX = false;
    if (!SetCommState(hComm, &dcb)) throw std::runtime_error("Failed to set Device-Control Block of " + commPortStr);
    
    // set timeouts
    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout = 0;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.ReadTotalTimeoutConstant = 500;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 500;
    if (!SetCommTimeouts(hComm, &timeouts)) throw std::runtime_error("Failed to set timeouts of " + commPortStr);
    
    // write to the serial port
    DWORD numberOfBytesWritten;
    std::string command = "things to write to the serial port";
    if (!WriteFile(hComm, command.data(), command.size(), &numberOfBytesWritten, NULL)) throw std::runtime_error("Failed to write to " + commPortStr);
    
    // read from the serial port
    DWORD numberOfBytesRead;
    DWORD numberOfBytesToRead = 100;
    std::string readBuffer(numberOfBytesToRead + 1, NULL);
    if (!ReadFile(hComm, (LPVOID)readBuffer.data(), numberOfBytesToRead, &numberOfBytesRead, NULL)) throw std::runtime_error("Failed to read from " + commPortStr);
  } catch (const std::exception& e){
    std::cout << "Error: " << e.what() << std::endl;
  }
  
  // clean up
  CloseHandle(hComm);
}