#ifndef HOOKS_HPP_
#define HOOKS_HPP_

#include <windows.h>

class NopHook
{
public:
	explicit NopHook( BYTE* nopPosition, size_t length ) noexcept;
	NopHook() noexcept = default;
	~NopHook() noexcept;

	// Delete copy and move operations to prevent unintended behavior
	NopHook( const NopHook& other ) = delete;
	NopHook( NopHook&& other ) = delete;
	NopHook& operator=( const NopHook& other ) = delete;
	NopHook& operator=( NopHook&& other ) = delete;

public:
	void nop() const noexcept;
	void patchNop() const noexcept;

	[[nodiscard]] bool toggleActivation() noexcept { m_bToggle = !m_bToggle; return m_bToggle; }
	[[nodiscard]] BYTE* getNopPosition()  const { return m_nopPosition; }
	[[nodiscard]] size_t getLength()      const { return m_length; }

private:
	BYTE* m_nopPosition{ nullptr };
	size_t m_length{ 0 };
	BYTE m_stolenBytes[20]{ 0 };
	bool m_bToggle{ false };
};

#endif // HOOKS_HPP_