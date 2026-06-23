#include "profiler/Profiler.h"

namespace eng
{
    Profiler& Profiler::GetInstance()
    {
        static Profiler instance;
        return instance;
    }

    void Profiler::BeginFrame()
    {
        // Nothing atm but might need later on
    }

    void Profiler::EndFrame(float frameDeltaSeconds)
    {
        // Convert frame time to milliseconds for storage/graphs
        const float frameMs = frameDeltaSeconds * 1000.0f;

        // Keep live per-frame values for graphs
        m_FrameMs = frameMs;
        m_Fps = (frameDeltaSeconds > 0.0f) ? (1.0f / frameDeltaSeconds) : 0.0f;

        // Push into ring buffers every frame so graphs stay smooth
        m_FpsHistory[m_HistoryIndex] = m_Fps;
        m_FrameHistory[m_HistoryIndex] = m_FrameMs;
        m_HistoryIndex = (m_HistoryIndex + 1) % static_cast<int>(m_FpsHistory.size());

        // Accumulate frame stats for 1-second display refresh
        m_SecondTimer += frameDeltaSeconds;
        m_FrameMsAccum += frameMs;
        m_FrameCountAccum++;

        // Accumulate each profiler section for 1-second display refresh
        for (auto& [name, sample] : m_Samples)
        {
            m_SecondAccumulators[name].totalMs += sample.lastMs;
            m_SecondAccumulators[name].count++;
        }

        // Once per second, update the numbers shown in the Debug window
        if (m_SecondTimer >= 1.0f)
        {
            // Average frame time over the last second
            if (m_FrameCountAccum > 0)
            {
                m_DisplayFrameMs = m_FrameMsAccum / static_cast<float>(m_FrameCountAccum);
                m_DisplayFps = static_cast<float>(m_FrameCountAccum) / m_SecondTimer;
            }

            // Average each profiler section over the last second
            for (auto& [name, sample] : m_Samples)
            {
                const SampleAccumulator& acc = m_SecondAccumulators[name];
                if (acc.count > 0)
                {
                    sample.displayMs = acc.totalMs / static_cast<float>(acc.count);
                }
            }

            // Reset accumulators for the next second
            m_SecondTimer = 0.0f;
            m_FrameMsAccum = 0.0f;
            m_FrameCountAccum = 0;
            m_SecondAccumulators.clear();
        }
    }

    void Profiler::RecordSample(const std::string& name, float durationMs)
    {
        ProfileSample& sample = m_Samples[name];
        // Save this frame's result
        sample.lastMs = durationMs;
        // Smooth average so values don't flicker too much
        sample.avgMs = sample.avgMs * 0.85f + durationMs * 0.15f;
    }

    const ProfileSample* Profiler::GetSample(const std::string& name) const
    {
        auto it = m_Samples.find(name);
        if (it == m_Samples.end()) return nullptr;

        return &it->second;
    }

    ProfileScope::ProfileScope(const char* name) noexcept
        : m_Name{ name },
        m_Start{ std::chrono::high_resolution_clock::now() }
    {

    }

    ProfileScope::~ProfileScope() noexcept
    {
        // Measure elapsed time since construction
        auto end = std::chrono::high_resolution_clock::now();
        float durationMs = std::chrono::duration<float, std::milli>(end - m_Start).count();

        // Store under this section name
        Profiler::GetInstance().RecordSample(m_Name, durationMs);
    }

}
