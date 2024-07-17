# MemoryAPI

# How does this work

### Memory Access

```cpp
// Reading memory
Memory localPlayer( LOCAL_PLAYER );
auto currentAmmo = localPlayer.read<DWORD>( 0x140 );

// Writing to memory
Memory localPlayer( LOCAL_PLAYER );
localPlayer.write( 0xF8, 500 );
```

### Process and Module Address Retrieval

```cpp
// Obtaining the process ID
Memory mem();
auto procID = mem.getProcID( "target.exe" );

// Acquiring the module base address
Memory mem();
auto modBaseAddr = mem.getModuleBase( "target.exe", procID );
```

# Getting Started
### Clone this project using Git
```bash
git clone https://github.com/Z1KOx/MemoryAPI.git
```
- If Git is not installed on your system, you can <a href="https://git-scm.com/downloads">download</a> it from the official website.
