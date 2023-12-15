//
// Created by lbert on 2/9/2023.
//
#ifndef ZYGISKPG_MISC_H
#define ZYGISKPG_MISC_H

#include "Includes/Dobby/dobby.h"
#include "Include/Unity.h"
#include "KittyMemory/KittyMemory.h"
#include "KittyMemory/KittyScanner.h"
#include "KittyMemory/MemoryPatch.h"

using KittyMemory::ProcMap;
using KittyScanner::RegisterNativeFn;

void hook(void *offset, void* ptr, void **orig)
{
    if(offset == nullptr) {
        LOG_PROPLAM("First arg (offset*) is null");
        return;
    }

    if(ptr == nullptr) {
        LOG_PROPLAM("Second arg (void*) is null");
        return;
    }

    if(orig == nullptr) {
        LOG_PROPLAM("Third arg (void**) is null");
        return;
    }

    DobbyHook(offset, ptr, orig);
}

std::vector<MemoryPatch> memoryPatches;
std::vector<uint64_t> offsetVector;

void patchOffsetAbsolute(uint64_t offset, std::string hexBytes, bool isOn) {

    if(offset == 0) return;

    MemoryPatch patch = MemoryPatch::createWithHex(offset, hexBytes);

    //Check if offset exists in the offsetVector
    if (std::find(offsetVector.begin(), offsetVector.end(), offset) != offsetVector.end()) {
        //LOGE(OBFUSCATE("Already exists"));
        std::vector<uint64_t>::iterator itr = std::find(offsetVector.begin(), offsetVector.end(), offset);
        patch = memoryPatches[std::distance(offsetVector.begin(), itr)]; //Get index of memoryPatches vector
    } else {
        memoryPatches.push_back(patch);
        offsetVector.push_back(offset);
        //LOGI(OBFUSCATE("Added"));
    }

    if (!patch.isValid()) {
        return;
    }
    if (isOn && patch.get_CurrBytes() == patch.get_OrigBytes()) {
        patch.Modify();
    } else if (!isOn && patch.get_CurrBytes() != patch.get_OrigBytes()) {
        patch.Restore();
    }
}


uintptr_t string2Offset(const char *c) {
    int base = 16;
    // See if this function catches all possibilities.
    // If it doesn't, the function would have to be amended
    // whenever you add a combination of architecture and
    // compiler that is not yet addressed.
    static_assert(sizeof(uintptr_t) == sizeof(unsigned long)
                  || sizeof(uintptr_t) == sizeof(unsigned long long),
                  "Please add string to handle conversion for this architecture.");

    // Now choose the correct function ...
    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    // All other options exhausted, sizeof(uintptr_t) == sizeof(unsigned long long))
    return strtoull(c, nullptr, base);
}

#define PATCH(offset, hex) patchOffsetAbsolute(offset, OBFUSCATE(hex), true)
#define PATCH_SWITCH(offset, hex, boolean) patchOffsetAbsolute((uint64_t) offset, OBFUSCATE(hex), boolean)
#define HOOK(pointer, ptr) hook((void*) pointer, (void*)ptr, (void**)&old##ptr);

#define RESTORE(offset) patchOffset(string2Offset(OBFUSCATE(offset)), "", false)
#define BOOL_TO_STRING(x) x ? "true" : "false"

#endif //ZYGISKPG_MISC_H
