#include "mem.hpp"

#include <TlHelp32.h>

[[nodiscard]] DWORD Memory::getProcID( const std::string& procName ) const noexcept
{
	DWORD procID{ 0 };
	const auto hSnapShot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL) };

	if ( hSnapShot != INVALID_HANDLE_VALUE )
	{
		PROCESSENTRY32 pe;
		ZeroMemory( &pe, sizeof(pe) );
		pe.dwSize = sizeof( pe );

		for ( bool proc = Process32First(hSnapShot, &pe); proc; proc = Process32Next(hSnapShot, &pe) )
		{
			if ( strcmp(pe.szExeFile, procName.c_str()) != 0 ) {
				continue;
			}

			procID = pe.th32ProcessID;
			break;
		}
	}

	CloseHandle( hSnapShot );
	return procID;
}

[[nodiscard]] uintptr_t __fastcall Memory::getModuleBase( const std::string& modName, const DWORD procID ) const noexcept
{
	uintptr_t modBaseAddr{ 0 };
	const auto hSnapShot{ CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID) };

	if ( hSnapShot != INVALID_HANDLE_VALUE )
	{
		MODULEENTRY32 me;
		ZeroMemory(&me, sizeof(me));
		me.dwSize = sizeof( me );

		for ( bool module = Module32First(hSnapShot, &me); module; module = Module32Next(hSnapShot, &me) )
		{
			if ( strcmp(me.szModule, modName.c_str()) != 0 ) {
				continue;
			}

			modBaseAddr = reinterpret_cast<uintptr_t>(me.modBaseAddr);
			break;
		}
	}

	CloseHandle( hSnapShot );
	return modBaseAddr;
}
