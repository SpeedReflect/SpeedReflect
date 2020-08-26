// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "types.h"
#include "carbon.h"
#include "prostreet.h"
#include "mostwanted.h"
#include "underground2.h"



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


		if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::carbon))
		{
			
			speedreflect::carbon::process();

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::mostwanted))
		{

			speedreflect::mostwanted::process();

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::prostreet))
		{
			
			speedreflect::prostreet::process();

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::underground1))
		{

		}
		else if (entry == static_cast<std::uint32_t>(speedreflect::entry_points::underground2))
		{

			speedreflect::underground2::process();

		}
		else
		{

			MessageBoxA(NULL, "This .exe is not supported!", "SpeedReflect", MB_ICONERROR);
			return FALSE;
		
		}
	}
	return TRUE;
}

