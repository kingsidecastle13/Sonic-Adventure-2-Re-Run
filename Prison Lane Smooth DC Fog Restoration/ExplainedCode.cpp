/* Code was inserted into a Frankensteined version of MainMemory's Emerald Coast master so might have some redundancies due to that of my VERY basic
understanding of C++. Hopefully I've made this clear enough that presuming you know how to insert a C++ based DLL into SA2 you can copy+ paste this code
into your own mod, no credit needs to be given. */

int fogV1 = 0;
int fogV2 = 0;

void DD()
{
	for (int i = 0; i < 2; i++)
	{
		if (CurrentLevel == LevelIDs_PrisonLane) 
		{
			if (fogV2 == 0) { fogV1++; }
			if (fogV1 >= 0x66) { fogV2 = 1; } // add to V1 until a cap is hit then use V2 to subtract
			if (fogV1 <= 0) { fogV2 = 0; }
			if (fogV2 == 1) { fogV1--; }
			{
			//FogDataPtr[i].near_ = 0x60; // 
			//FogDataPtr[i].far_ = 0x0600;
			FogDataPtr[i].color = (0x330000 + ((fogV1) * 0x10000)); // adds to the RED colour Byte, 
				/* swap '0x10000' to '0x100' && '0x330000' to '0x00##00' for GREEN where '##' = base colour value, don't exceed '0x99' without edits 
				to fogV1 code, like so:
				
				FogDataPtr[i].color = (0x003300 + ((fogV1) * 0x100)); // GREEN
				FogDataPtr[i].color = (0x000033 + fogV1); // BLUE
				FogDataPtr[i].color = (0x333300 + (((fogV1) * 0x10000) + ((fogV1) * 0x100))); // YELLOW
				FogDataPtr[i].color = (0x003333 + ((fogV1) + ((fogV1) * 0x100))); // TURQUIOSE
				FogDataPtr[i].color = (0x330033 + (((fogV1) * 0x10000) + fogV1)); // PURPLE
				FogDataPtr[i].color = (0x333333 + (((fogV1) * 0x10000) + ((fogV1) * 0x100) + fogV1)); // GREY

				 I believe that's ^ all correct, change all '3' digits to a lower numder to darken and upto '9' to lighten */
			}
		}	
	}
}


extern "C"
	{
		__declspec(dllexport) void __cdecl OnFrame()
		{
			if (GameState == GameStates_Ingame)
			{
				DD(); // Add 'void DD();' to your Header file
			}
			if (GameState == 13) // I have forgotten which is which but game state '13' and '1' are level reload/exit states
			{
				fogV1 = 0; fogV2 = 0; // not essential to reset of course
			}
			if (GameState == 1)
			{
				fogV1 = 0; fogV2 = 0; 
			}
		}
		__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
	}