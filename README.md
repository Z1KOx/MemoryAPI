# MemoryAPI

# How does this work

### Memory Access

```cpp
// Reading memory
Memory mem( LOCAL_PLAYER );
auto currentAmmo = mem.read<DWORD>( 0x140 );

// Writing to memory
Memory mem( LOCAL_PLAYER );
mem.write( 0xF8, 500 );
```

### Process and Module Address Retrieval

```cpp
// Obtaining the process ID
auto procID = mem.getProcID( L"target.exe" );

// Acquiring the module base address
auto modBaseAddr = mem.getModuleBase(L"target.exe", procID);
```

# Getting Started
### 1. Clone this project using Git
```bash
git clone https://github.com/Z1KOx/MemoryAPI.git
```
- If Git is not installed on your system, you can <a href="https://git-scm.com/downloads">download</a> it from the official website.
