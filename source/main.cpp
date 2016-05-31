/*
	RTC example made by Aurelio Mannara for ctrulib
	This code was modified for the last time on: 12/13/2014 2:45 UTC+1

	This wouldn't be possible without the amazing work done by:
	-Smealum
	-fincs
	-WinterMute
	-yellows8
	-plutoo
	-mtheall
	-Many others who worked on 3DS and I'm surely forgetting about
*/

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void OptA()
{
    printf("\x1b[2J");
    printf("OPT A\n");
    printf("\x1b[20;15HPress Start to exit.\n");
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    while(true)
    {
        printf("Why does this need to be here?\n");
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
        {
            break;
        }
    }
    return;
}

void OptB()
{
    printf("\x1b[2J");
    printf("OPT B\n");
    printf("\x1b[20;15HPress Start to exit.\n");
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    while(true)
    {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
        {
            break;
        }
    }
    return;
}

void OptC()
{
    printf("\x1b[2J");
    printf("OPT C\n");
    printf("\x1b[20;15HPress Start to exit.\n");
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    while(true)
    {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
        {
            break;
        }
    }
    return;
}

void OptD()
{
    printf("\x1b[2J");
    printf("OPT D\n");
    printf("\x1b[20;15HPress Start to exit.\n");
    gfxFlushBuffers();
    gfxSwapBuffers();
    gspWaitForVBlank();
    while(true)
    {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START)
        {
            break;
        }
    }
    return;
}

int doStuff(int selection, const char **dongs)
{
    printf("\x1b[2J");
    printf("Dongs: %d\n", selection);
    int i;
    for(i = 0; i < (int)sizeof(*dongs); i++)
    {
        if(i+1 == selection)
        {
            printf("%d)>> ", i);
        }
        else
        {
            printf("%d) ", i);
        }
        printf("%s", dongs[i]);
    }
    printf("\n\nDPAD Up/Down to change selected item.\n");
    printf("\x1b[20;15HPress Start to exit.\n");
    return 0;
}

void menu()
{
    const char *dongs[4];
    dongs[0] = "Option A\n";
    dongs[1] = "Option B\n";
    dongs[2] = "Option C\n";
    dongs[3] = "Option D\n";
    int selection = 1;

    printf("\x1b[2J");

    doStuff(1, dongs);

    while(true)
    {
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START) break; // break in order to return to hbmenu

        //The direction is reverse for UX
        if(kDown & KEY_DDOWN)
        {
            if(selection < (int)sizeof(*dongs))
            {
                selection++;
                doStuff(selection, dongs);
            }
            else
            {
                //Re-render the selection to give visual feedback that the button press has been detected, and the maximium value has been reached.
                doStuff(selection, dongs);
            }
        }

        if(kDown & KEY_DUP)
        {
            if(selection > 1)
            {
                selection--;
                doStuff(selection, dongs);
            }
            else
            {
                doStuff(selection, dongs);
            }
        }

        if(kDown & KEY_A)
        {
            printf("Enter");
            OptA();
            printf("Leave");
            //Rerender the menu after exiting a submenu!
            doStuff(selection, dongs);
        }

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();

        //Wait for VBlank
        gspWaitForVBlank();
    }

    return;

}

int main(int argc, char **argv)
{
    // Initialize services
    gfxInitDefault();

    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_TOP, NULL);

    // Main loop
    while (aptMainLoop())
    {
        //Enter menu
        menu();

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();

        //Wait for VBlank
        gspWaitForVBlank();

        break;
    }

    // Exit services
    gfxExit();

    return 0;
}
