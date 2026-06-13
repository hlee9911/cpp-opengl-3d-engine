#pragma once

namespace eng
{
    struct MemoryStats
    {
        float workingSetMB = 0.0f;      // RAM currently used by process
        float privateUsageMB = 0.0f;    // Private bytes
        float peakWorkingSetMB = 0.0f;  // Peak RAM usage so far
    };

    class MemoryManager
    {
    public:

        // Query current process memory from OS
        static MemoryStats GetProcessMemoryStats();

    };

}
