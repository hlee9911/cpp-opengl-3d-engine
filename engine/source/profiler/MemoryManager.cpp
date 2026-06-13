#include "profiler/MemoryManager.h"

#ifdef _WIN32
    #define NOMINMAX
    #include <Windows.h>
    #include <Psapi.h>
    #pragma comment(lib, "Psapi.lib")
#endif

namespace eng
{
    /// <summary>
    /// Get the process memory from the processor
    /// </summary>
    /// <returns></returns>
    MemoryStats MemoryManager::GetProcessMemoryStats()
    {
        MemoryStats stats{};
#ifdef _WIN32
        PROCESS_MEMORY_COUNTERS_EX pmc{};
        pmc.cb = sizeof(pmc);
        // Ask Windows for this process's memory usage
        if (GetProcessMemoryInfo(
            GetCurrentProcess(),
            reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc),
            sizeof(pmc)))
        {
            // Convert bytes -> megabytes
            stats.workingSetMB = static_cast<float>(pmc.WorkingSetSize) / (1024.0f * 1024.0f);
            stats.privateUsageMB = static_cast<float>(pmc.PrivateUsage) / (1024.0f * 1024.0f);
            stats.peakWorkingSetMB = static_cast<float>(pmc.PeakWorkingSetSize) / (1024.0f * 1024.0f);
        }
#endif

        return stats;
    }
}
