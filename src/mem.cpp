#include "mem.hpp"

#include <TlHelp32.h>

[[nodiscard]] DWORD Memory::getProcID( const std::string& procName ) const noexcept
{
	DWORD procID{ 0 };

	// Snapshot all currently running processes
	const auto hSnapShot{ CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL ) };

	if ( hSnapShot == nullptr || hSnapShot != INVALID_HANDLE_VALUE )
	{
		PROCESSENTRY32 pe;
		ZeroMemory( &pe, sizeof(pe) );
		pe.dwSize = sizeof( pe );

		// Iterate through each process to find the specified process by name
		for ( bool proc = Process32First(hSnapShot, &pe); proc; proc = Process32Next(hSnapShot, &pe) )
		{
			// Check if the current process matches the specified process name
			if ( strcmp(pe.szExeFile, procName.c_str()) != 0 ) {
				continue;
			}

			procID = pe.th32ProcessID;
			break; // Break out of the loop once the process is found
		}
	}

	CloseHandle( hSnapShot );
	return procID;
}

[[nodiscard]] uintptr_t __fastcall Memory::getModuleBase( const std::string& modName, const DWORD procID ) const noexcept
{
	uintptr_t modBaseAddr{ 0 };

	// Snapshot all currently loaded modules in the process
	const auto hSnapShot{ CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID ) };

	if ( hSnapShot == nullptr || hSnapShot != INVALID_HANDLE_VALUE )
	{
		MODULEENTRY32 me;
		ZeroMemory( &me, sizeof(me) );
		me.dwSize = sizeof( me );

		// Iterate through each module to find the specified module by name
		for ( bool module = Module32First(hSnapShot, &me); module; module = Module32Next(hSnapShot, &me) )
		{
			// Check if the current module matches the specified module name
			if ( strcmp(me.szModule, modName.c_str()) != 0 ) {
				continue;
			}

			modBaseAddr = reinterpret_cast<uintptr_t>(me.modBaseAddr);
			break; // Break out of the loop once the module is found
		}
	}

	CloseHandle( hSnapShot );
	return modBaseAddr;
}
