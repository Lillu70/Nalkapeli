
#pragma once



struct Random_Machine
{
	i32 noise_position = 0;
	static inline i32 seed = 1;
	
	u32 random_u32(u32 max)
	{
		u32 result = (noise_squirrel3(noise_position++, seed) % max);
		return result;
	}
	
	f32 random_f32()
	{
		u32 r = noise_squirrel3(noise_position++, seed) % 1000;
		
		f32 result = ((f32)r / (f32)1000);
		
		return result;
	} 
};
