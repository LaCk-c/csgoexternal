#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <tchar.h>
#include <intrin.h>
#include <algorithm>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <thread>
#include "Offset.h"
void setcolor(unsigned short color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

bool toggleBunny = false;
bool toggleWallhack = false;
bool toggleRadar = false;

uintptr_t moduleBase;
DWORD proc;
HWND hwnd;
HANDLE hProcess;


using namespace std;
vector<string> serial;

uintptr_t GetModuleBase(const char* modName) {
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc);
	if (hSnap != INVALID_HANDLE_VALUE) {
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry)) {
			do {
				if (!strcmp(modEntry.szModule, modName)) {
					CloseHandle(hSnap);
					return (uintptr_t)modEntry.modBaseAddr;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
}

template<typename T> T RPM(SIZE_T address) {
	T buffer;
	ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
	return buffer;
}
template<typename T> void WPM(SIZE_T address, T buffer) {
	WriteProcessMemory(hProcess, (LPVOID)address, &buffer, sizeof(buffer), NULL);
}

void loadserial() {
	serial.push_back("1289134502");
	serial.push_back("serials");
	serial.push_back("serials");
	serial.push_back("serials");
}

void radar() { //okay guys this is all, now i will test it in csgo!
	while (true)
	{
		Sleep(5);
		if (!toggleRadar)
			continue; //this code you can find it in the description, (code by cyborg elf)
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc);
		while (true) {
			for (int i = 1; i < 64; i++) {
				DWORD dwCurrentEntity = RPM<DWORD>(moduleBase + dwEntityList + i * 0x10);
				if (dwCurrentEntity) {
					WPM<bool>(dwCurrentEntity + m_bSpotted, true);
				}
			}
			Sleep(100);
		}

	}
}

void bunny() {
	while (true) {
		if (!toggleBunny)
			continue;
		Sleep(250);


	}
}

void wallhack() {
	while (true) {
		if (!toggleWallhack)
		continue;
		Sleep(250);


	}
}


int main() {

	loadserial();
	setcolor(10);
	std::cout << "checking whitelist\n";
	Sleep(250);

	TCHAR volumeName[MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;
	if (GetVolumeInformation(_T("C:\\"), volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName)));

	while (true) {

		if (find(serial.begin(), serial.end(), to_string(serialNumber)) != serial.end())
		{
			std::cout << "Nice you are in the database!\n";
			Sleep(400);
			system("cls");

			SetConsoleTitle("Loading cheat");
			setcolor(10);
			std::cout << "Loading...\n";
			std::thread bunnyhop(bunny);
			std::thread wallhack(wallhack);
			std::thread radar(radar);

			hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive");
			GetWindowThreadProcessId(hwnd, &proc);
			std::cout << "CSGO id is founded!\n";
			moduleBase = GetModuleBase("client.dll");

			Sleep(1000);
			std::cout << "Done!\n";
			Sleep(200);
			system("cls");
			SetConsoleTitle("CSGO cheat");

			setcolor(12);

			std::cout << "       _                _   \n";
			std::cout << "      | |              | |  \n";
			std::cout << "   ___| |__   ___  __ _| |_ \n";
			std::cout << "  / __| '_ \ / _ \/ _` | __|\n";
			std::cout << " | (__| | | |  __/ (_| | |_ \n";
			std::cout << "  \___|_| |_|\___|\__,_|\__|\n";
			std::cout << "\n";

			setcolor(10);
			std::cout << "Welcome to csgo cheat zfesfed\n";
			setcolor(15);
			std::cout << "-------------------------------------------------------\n";
			setcolor(10);

			std::cout << "Toggles:\n";
			std::cout << "Wallhack: F5\n";
			std::cout << "Bunnyhop: F6\n";
			std::cout << "Radar: F7\n";
			std::cout << "Exit: F8\n";

			std::cout << "\n";

			while (true) {

				if (GetAsyncKeyState(VK_F5)) {
					toggleWallhack = !toggleWallhack;
					Sleep(200);
					if (toggleWallhack) {
						std::cout << "Wallhack: ON\n";
					}
					else {
						std::cout << "Wallhack: OFF\n";
					}

				}

				if (GetAsyncKeyState(VK_F6)) {
					toggleBunny = !toggleBunny;
					Sleep(200);
					if (toggleBunny) {
						std::cout << "Bunny: ON\n";
					}
					else {
						std::cout << "Bunny: OFF\n";
					}
				}

				if (GetAsyncKeyState(VK_F7)) {
					toggleRadar = !toggleRadar;
					Sleep(200);
					if (toggleRadar) {
						std::cout << "Radar: ON\n";
					}
					else {
						std::cout << "Radar: OFF\n";
					}
				}

				if (GetAsyncKeyState(VK_F8)) {
					Sleep(200);
					std::cout << "Closing\n";
					Sleep(200);
					system("cls");
					std::cout << "Closing.\n";
					Sleep(200);
					system("cls");
					std::cout << "Closing..\n";
					Sleep(200);
					system("cls");
					std::cout << "Closing...\n";
					Sleep(200);
					system("cls");
					std::cout << "Closing..\n";
					Sleep(200);
					system("cls");
					std::cout << "Closing.\n";
					Sleep(200);
					system("cls");
					exit(0);
				}

			}


		}
		else {

			setcolor(12);
			SetConsoleTitle("Whitelist failed");
			std::cout << "you arent in the whitelist\n";
			std::cout << "Your hwid is: ";
			std::cout << serialNumber << std::endl;
			Sleep(100000);
			exit(0);
		}

	}


}