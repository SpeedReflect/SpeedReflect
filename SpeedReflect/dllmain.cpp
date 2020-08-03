// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "types.h"
#include "carbon.h"
#include "underground2.h"

#pragma warning(disable : 4996)



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		auto base = (uintptr_t)GetModuleHandleA(NULL);
		auto dos = (IMAGE_DOS_HEADER*)(base);
		auto nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);
		auto entry = base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base);

		AllocConsole();
		std::freopen("CONOUT$", "w", stdout);
		std::freopen("CONIN$", "r", stdin);

		if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::carbon))
		{
			
			std::cout << "Found game: [Need for Speed: Carbon]" << std::endl;
			speedreflect::carbon::process();
			std::cout << "Finished processing: [Need for Speed: Carbon]" << std::endl;

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::mostwanted))
		{

			std::cout << "Found game: [Need for Speed: Most Wanted]" << std::endl;
			std::cout << "Finished processing: [Need for Speed: Most Wanted]" << std::endl;

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::prostreet))
		{
			
			std::cout << "Found game: [Need for Speed: Prostreet]" << std::endl;
			std::cout << "Finished processing: [Need for Speed: Prostreet]" << std::endl;

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::underground1))
		{

			std::cout << "Found game: [Need for Speed: Underground 1]" << std::endl;
			std::cout << "Finished processing: [Need for Speed: Underground 1]" << std::endl;

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::underground2))
		{

			std::cout << "Found game: [Need for Speed: Underground 2]" << std::endl;
			speedreflect::underground2::process();
			std::cout << "Finished processing: [Need for Speed: Underground 2]" << std::endl;

		}
		else
		{

			MessageBoxA(NULL, "This .exe is not supported!", "SpeedReflect", MB_ICONERROR);
			return FALSE;
		
		}
	}
	return TRUE;
}

