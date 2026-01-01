#pragma once

#include <Windows.h>

class Timer
{
	public:

		Timer() = default;

        void initialise()
        {
            QueryPerformanceFrequency( &ticks_per_second );

            reset();
        }

		void reset()
		{
			QueryPerformanceCounter( & ticks_start );
			ticks_current = ticks_start;
		}

		void tick()
		{
			ticks_previous = ticks_current;

			QueryPerformanceCounter( & ticks_current );

			ticks_elapsed.QuadPart = ticks_current.QuadPart - ticks_start.QuadPart;
						
			//m_delta.QuadPart /= m_frequency.QuadPart;
			//( ( ctr2 - ctr1 ) * 1.0 / freq )
		}

		double delta()
		{ 
			ticks_delta.QuadPart = ticks_current.QuadPart - ticks_previous.QuadPart;

			double time_delta = static_cast< double >( ticks_delta.QuadPart ) / static_cast< double >( ticks_per_second.QuadPart );

			// if( time_delta < 0.0f ) time_delta = 0.0f;

			return time_delta;	
		}

		double total()
		{
			double total = static_cast< double >( ticks_elapsed.QuadPart ) / static_cast< double >( ticks_per_second.QuadPart );

			return total;
		}

		void start()
		{
			QueryPerformanceCounter( & ticks_start );
		}

		//void stop() {}
		//void pause();
		//void fps();
        //void single_step() {}
		//double elapsed() { return m_start - m_last; }
		// set_alarm

	private:

		static inline LARGE_INTEGER ticks_per_second {};
		double                      seconds_per_tick {};
        //const double one_second = 1.0;

        static inline LARGE_INTEGER ticks_delta    {};
		static inline LARGE_INTEGER ticks_start    {};
        static inline LARGE_INTEGER ticks_current  {};
        static inline LARGE_INTEGER ticks_previous {};
        static inline LARGE_INTEGER ticks_elapsed  {};

		// frames_last_main_loop
		// int framesThisSecond;
		// static int framesSkipped;

		bool is_paused { false };
};

// Variability of the CPU's frequency ** windows message ?
// unsigned long mask_previous = SetThreadAffinityMask( GetCurrentThread , 1 );
// and then set it back at the end 
// SetThreadAffinityMask( GetCurrentThread , old_mask ) 