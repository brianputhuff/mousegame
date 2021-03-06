/**

Mouse Game

Copyright 2021 Brian Puthuff

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/



#include "fps.h"



void FPS_init ( struct FramesPerSecond *fps_struct )
{
	uint8_t i;



	/* initialize FPS counter */
	for ( i = 0; i < FPS_AVG_COUNT; i++ )
	{
		fps_struct->fps_data [ i ] = 0.0f;
		fps_struct->fps_data_index = 0;
		fps_struct->average = 0.0f;
	}
}



void FPS_start ( struct FramesPerSecond *fps_struct )
{
    	/* get performance counter ( start ) */
	fps_struct->performance_counter_start = SDL_GetPerformanceCounter ( );
}



void FPS_end ( struct FramesPerSecond *fps_struct )
{
	uint8_t i;
	float sum;



	/* get performance counter ( end ) */
	fps_struct->performance_counter_end = SDL_GetPerformanceCounter ( );
    	
	/* calculate elapsed time ( in  milliseconds )*/
	fps_struct->elapsed_ms = ( float ) ( fps_struct->performance_counter_end - fps_struct->performance_counter_start ) \
	/ ( float ) SDL_GetPerformanceFrequency ( ) * 1000.0f;

    	/* if there is free time, spin idle until ready */
	while ( fps_struct->elapsed_ms < FPS_FRAME_DURATION )
	{
        	/* get performance counter ( end ) */
        	fps_struct->performance_counter_end = SDL_GetPerformanceCounter ( );
		
        	/* get update elapsed time */
		fps_struct->elapsed_ms = ( float ) ( fps_struct->performance_counter_end - fps_struct->performance_counter_start ) \
		/ ( float ) SDL_GetPerformanceFrequency ( ) * 1000.0f;
	}


	/* calculate frames per second */
	/* get performance counter ( end ) */
	fps_struct->performance_counter_end = SDL_GetPerformanceCounter ( );

	/* add elapsed time to data */	
	fps_struct->fps_data [ fps_struct->fps_data_index ] = ( float ) ( fps_struct->performance_counter_end - fps_struct->performance_counter_start ) \
	/ ( float ) SDL_GetPerformanceFrequency ( );

    	/* increment data index and update average if ready */
	fps_struct->fps_data_index++;
	if ( fps_struct->fps_data_index == FPS_AVG_COUNT )
	{
		sum = 0;
		for ( i = 0; i < FPS_AVG_COUNT; i++ )
		{
			sum += fps_struct->fps_data [ i ];
		}
		fps_struct->average = ( uint8_t ) ceil ( 1.0f / ( sum / FPS_AVG_COUNT ) );
		fps_struct->fps_data_index = 0;
	}
}




