/*
 Touch2Tuio - Windows 7 Touch to TUIO Bridge
 http://dm.tzi.de/research/hci/touch2tuio
 
 Copyright (c) 2010 Marc Herrlich and Benjamin Walther-Franks, Research Group Digital Media, TZI, University of Bremen
 
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


// Touch2Tuio.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "windows.h"
#include <windows.h>
//#include <dos.h>
//#include <stdio.h>
//#include <conio.h>

int main(int argc, char *argv[])
{
	DWORD threadId = 0;

	std::string url;

	if (argc == 1)
	{
		std::cout << "No url provided, defaulting to http://www.extraordinarythoughts.com/\n";
		url = "http://www.extraordinarythoughts.com/";
	} else {
		url = argv[1];
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	std::string command;

	command = "chrome.exe --kiosk ";
	command.append(url);

	if( !CreateProcess( NULL,   // No module name (use command line)
		(char*)command.c_str(),        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi )           // Pointer to PROCESS_INFORMATION structure
	) 
	{
		printf( "Failed to start chrome.exe\n");
		return 1;
	}
	HWND hWndForeground;
	DWORD fPid;

	std::cout << "Waiting for foreground window of process: " << pi.dwProcessId << "\n";

	INT count = 0;

	do {
		hWndForeground = GetForegroundWindow();
		GetWindowThreadProcessId(hWndForeground, &fPid);
		Sleep(100);
		count++;
		if(count == 50) {
			std::cout << "Failed to find window in foreground.\n";
			return 1;
		}
	} while(fPid != pi.dwProcessId);

	threadId = pi.dwThreadId;
	CloseHandle(&si);
	CloseHandle(&pi);

	std::string address = "127.0.0.1";
	int port = 3333;

	SetConsoleId(GetCurrentProcessId());
	SetTuioServerAddress(address.c_str(), port);
	if(threadId != 0) {
		if (!InstallHookFromThreadId(threadId))
		{
			std::cout << "Could not install hook for process." << std::endl;
			return 1;
		}
	} else {
		std::cout << "Thread not running?" << std::endl;
		return 1;
	}
	std::cout << "Successfully installed hook and started TUIO server" << std::endl;

	char c = getchar();

	if (!RemoveHook())
	{
		std::cout << "Could not remove hook" << std::endl;
		return 1;
	}

	std::cout << "Successfully removed hook and killed TUIO server" << std::endl;

	return 0;
}
