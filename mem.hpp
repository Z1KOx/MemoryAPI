#ifndef MEM_HPP_
#define MEM_HPP_

#include <string>
#include <windows.h>

class Memory
{
public:
	explicit Memory( uintptr_t* address ) noexcept
		: m_address(address)
	{ }

	Memory() = default;
	~Memory() noexcept = default;

	Memory( const Memory& other )            = delete;
	Memory( Memory&& other )                 = delete;
	Memory& operator=( const Memory& other ) = delete;
	Memory& operator=( Memory&& other )      = delete;

public:
    template<typename T>
    void __fastcall write(const uintptr_t offset, const T value) const noexcept { *reinterpret_cast<T*>((*m_address + offset)) = value; }

    template<typename T>
    [[nodiscard]] T read(const uintptr_t offset) const noexcept { return *reinterpret_cast<T*>((*m_address + offset)); }

public:
	[[nodiscard]] DWORD getProcID( const std::string& procName ) const noexcept;
	[[nodiscard]] uintptr_t __fastcall getModuleBase (const std::string& modName, const DWORD procID ) const noexcept;

private:
	uintptr_t* m_address{ nullptr };
};

#endif // MEM_HPP_
