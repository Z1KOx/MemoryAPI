#include "hooks.hpp"

NopHook::NopHook( BYTE* nopPosition, size_t length ) noexcept
	: m_nopPosition(nopPosition), m_length(length)
{
	if (!m_nopPosition || m_length == 0)
	{
		MessageBox( nullptr, "Nop-Position or length is invalid", "Nop Error", MB_OK | MB_ICONERROR );
		return;
	}

	// Copy stolen bytes
	memcpy_s( m_stolenBytes, m_length, m_nopPosition, m_length );
}

NopHook::~NopHook() noexcept
{
	if ( m_bActive ) {
		patchNop();
	}
}

void NopHook::nop() const noexcept
{
	DWORD oldprotect{ 0 };
	VirtualProtect( m_nopPosition, m_length, PAGE_EXECUTE_READWRITE, &oldprotect );

	// Set `nops` to our nop position
	memset( m_nopPosition, 0x90, m_length );

	VirtualProtect( m_nopPosition, m_length, oldprotect, &oldprotect );
}

void NopHook::patchNop() const noexcept
{
	DWORD oldprotect{ 0 };
	VirtualProtect( m_nopPosition, m_length, PAGE_EXECUTE_READWRITE, &oldprotect );

	// Restore our stolen bytes to the nop position
	memcpy_s( m_nopPosition, m_length, m_stolenBytes, m_length );

	VirtualProtect( m_nopPosition, m_length, oldprotect, &oldprotect );
}