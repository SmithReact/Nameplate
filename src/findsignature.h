/*
This file is part of Nameplate.
Copyright (C) 2024 BunnyBox Productions

Nameplate is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Nameplate is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Nameplate.
If not, see <https://www.gnu.org/licenses/>.
*/

// Reworked as a conventional C++20 header for the Ashita 4.30 port on
// 2026-08-16. See ASHITA4-PORT.md and NOTICE.md.

#pragma once

#include <windows.h>
#include <psapi.h>

#include <stddef.h>
#include <stdint.h>

struct SignatureScanResult {
    uint8_t* Address;
    size_t Count;
};

class Signature {
public:
    constexpr Signature(const char* text, size_t textLength) : m_Text(text), m_TextLength(textLength) {}

    SignatureScanResult Scan() const {
        SignatureScanResult result = {};

        HMODULE module = GetModuleHandleW(L"FFXiMain.dll");
        if (module == nullptr || (m_TextLength % 2) != 0) {
            return result;
        }

        MODULEINFO moduleInfo = {};
        if (GetModuleInformation(GetCurrentProcess(), module, &moduleInfo, sizeof(moduleInfo)) == FALSE) {
            return result;
        }

        const size_t patternLength = m_TextLength / 2;
        if (patternLength == 0) {
            return result;
        }

        const uintptr_t moduleBegin = reinterpret_cast<uintptr_t>(moduleInfo.lpBaseOfDll);
        const uintptr_t moduleEnd = moduleBegin + moduleInfo.SizeOfImage;
        uintptr_t cursor = moduleBegin;

        while (cursor < moduleEnd) {
            MEMORY_BASIC_INFORMATION memoryInfo = {};
            if (VirtualQuery(reinterpret_cast<const void*>(cursor), &memoryInfo, sizeof(memoryInfo)) == 0) {
                break;
            }

            uintptr_t regionBegin = reinterpret_cast<uintptr_t>(memoryInfo.BaseAddress);
            uintptr_t regionEnd = regionBegin + memoryInfo.RegionSize;
            if (regionBegin < moduleBegin) {
                regionBegin = moduleBegin;
            }
            if (regionEnd > moduleEnd) {
                regionEnd = moduleEnd;
            }

            const DWORD protection = memoryInfo.Protect & 0xFF;
            const bool executable =
                protection == PAGE_EXECUTE ||
                protection == PAGE_EXECUTE_READ ||
                protection == PAGE_EXECUTE_READWRITE ||
                protection == PAGE_EXECUTE_WRITECOPY;
            const bool readable = memoryInfo.State == MEM_COMMIT &&
                (memoryInfo.Protect & (PAGE_GUARD | PAGE_NOACCESS)) == 0;

            if (readable && executable && regionEnd >= regionBegin + patternLength) {
                const uintptr_t lastCandidate = regionEnd - patternLength;
                for (uintptr_t candidate = regionBegin; candidate <= lastCandidate; ++candidate) {
                    if (Matches(reinterpret_cast<const uint8_t*>(candidate), patternLength)) {
                        if (result.Address == nullptr) {
                            result.Address = reinterpret_cast<uint8_t*>(candidate);
                        }
                        ++result.Count;
                    }
                }
            }

            if (regionEnd <= cursor) {
                break;
            }
            cursor = regionEnd;
        }

        return result;
    }

    uint8_t* Find() const {
        return Scan().Address;
    }

private:
    static constexpr uint8_t HexDigit(char value) {
        return value >= 'A' ? static_cast<uint8_t>(10 + value - 'A') : static_cast<uint8_t>(value - '0');
    }

    bool Matches(const uint8_t* candidate, size_t patternLength) const {
        for (size_t index = 0; index < patternLength; ++index) {
            const char high = m_Text[index * 2];
            const char low = m_Text[index * 2 + 1];
            if (high == '?' && low == '?') {
                continue;
            }

            const uint8_t expected = static_cast<uint8_t>((HexDigit(high) << 4) | HexDigit(low));
            if (candidate[index] != expected) {
                return false;
            }
        }
        return true;
    }

    const char* m_Text;
    size_t m_TextLength;
};

template <size_t N>
constexpr Signature MakeSig(const char (&text)[N]) {
    return Signature(text, N - 1);
}
