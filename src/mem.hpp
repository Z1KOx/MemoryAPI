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

	Memory( const Memory& other )            = delete; // Copy constructor
	Memory( Memory&& other )                 = delete; // Move constructor
	Memory& operator=( const Memory& other ) = delete; // Copy assignment operator
	Memory& operator=( Memory&& other )      = delete; // Move assignment operator

public:
    // Write a value of type T to a memory address at the specified offset
    template<typename T>
    void __fastcall write( const uintptr_t offset, const T value ) const noexcept { *reinterpret_cast<T*>( (*m_address + offset) ) = value; }

    // Read a value of type T from a memory address at the specified offset
    template<typename T>
    [[nodiscard]] T read( const uintptr_t offset ) const noexcept { return *reinterpret_cast<T*>( (*m_address + offset) ); }

public:
    // Retrieve the process ID of a process with the given name
    [[nodiscard]] DWORD getProcID( const std::string& procName ) const noexcept;

    // Retrieve the base address of a module with the given name in the specified process
    [[nodiscard]] uintptr_t __fastcall getModuleBase ( const std::string& modName, const DWORD procID ) const noexcept;

private:
	uintptr_t* m_address{ nullptr };
};

#endif // MEM_HPP_
