#pragma once

#define AUDIO_FREQ					(47916)
#define AUDIO_BUFFER_LEN			(2048)
#define AUDIO_BUFFER_HALF			(AUDIO_BUFFER_LEN/2)

#define AUDIO_MS_PER_SAMPLE			(float)(1.0f/AUDIO_FREQ)
#define AUDIO_BUFFER_MS				(AUDIO_MS_PER_SAMPLE*AUDIO_BUFFER_LEN*1000.0f)
#define AUDIO_BUFFER_HALF_MS		(AUDIO_MS_PER_SAMPLE*AUDIO_BUFFER_HALF*1000.0f)
