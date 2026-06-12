#pragma once

#include "Core.h"

#include <array>
#include <string>
#include <chrono>

namespace eng
{
    // One timed section
    struct ProfileSample
    {
        float lastMs = 0.0f;        // raw value from most recent frame (internal)
        float avgMs = 0.0f;         // short smooth average (internal)
        float displayMs = 0.0f;     // value shown in Debug UI (updates every 1s)
    };

    class Profiler
    {
    public:

        static Profiler& GetInstance();

        // Call once per frame before timing anything
        void BeginFrame();

        // Call once per frame after all sections are done
        void EndFrame(float frameDeltaSeconds);

        // Record one named section's duration
        void RecordSample(const std::string& name, float durationMs);

        // Read a section's timing data
        const ProfileSample* GetSample(const std::string& name) const;

        // Frame stats for graphs
        float GetFrameMs() const noexcept { return m_FrameMs; }
        float GetFps() const noexcept { return m_Fps; }
        const std::array<float, 120>& GetFpsHistory() const  { return m_FpsHistory; }
        const std::array<float, 120>& GetFrameHistory() const { return m_FrameHistory; }

        // Use these in RenderDebugWindow instead of GetFps()/GetFrameMs()
        float GetDisplayFps() const noexcept { return m_DisplayFps; }
        float GetDisplayFrameMs() const noexcept { return m_DisplayFrameMs; }

    private:

        Profiler() noexcept = default;
        float m_FrameMs = 0.0f;
        float m_Fps = 0.0f;

        // Ring buffers used by ImGui::PlotLines
        std::array<float, 120> m_FpsHistory{};
        std::array<float, 120> m_FrameHistory{};
        int m_HistoryIndex = 0;
        Dictionary<std::string, ProfileSample> m_Samples;

        // Values shown in the UI (refreshed once per second)
        float m_DisplayFps = 0.0f;
        float m_DisplayFrameMs = 0.0f;

        // Accumulators for 1-second averaging
        float m_SecondTimer = 0.0f;
        float m_FrameMsAccum = 0.0f;
        int m_FrameCountAccum = 0;

        // Per-section accumulators for 1-second averaging
        struct SampleAccumulator
        {
            float totalMs = 0.0f;
            int count = 0;
        };
        Dictionary<std::string, SampleAccumulator> m_SecondAccumulators;
    };

    // RAII timer: starts on construction, records on destruction
    class ProfileScope
    {
    public:

        explicit ProfileScope(const char* name) noexcept;
        ~ProfileScope() noexcept;

    private:

        const char* m_Name;
        std::chrono::high_resolution_clock::time_point m_Start;

    };
}

// Easy macro for scoped timing
#define ENG_PROFILE(name) eng::ProfileScope _profileScope_##__LINE__(name)
