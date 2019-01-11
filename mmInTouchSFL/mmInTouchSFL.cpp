// HCInTouchUtils.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "mmInTouchSFL.h"
#include <stdio.h>
#include "PTACC.H"


HCINTOUCHUTILS_API int ReadWindowLocation(LPSTR AppDir, LPSTR WindowName, LPSTR XTag, LPSTR YTag)
{
	char filename[1024] = "";
	char line[1024];
	char* index = "";
	char* window;
	char* nexttoken;
	int success = 0;
	int error;
	FILE *fp;
	UINT32 winNameLenOffset = 0x78;
	UINT32  winCommentLenOffset;
	UINT32 Xoff;
	UINT32 Yoff;

	BYTE winNameLengthData[4];
	BYTE winCommentLengthData[4];
	BYTE Xdata[4];
	BYTE Ydata[4];
	
	long x;
	long y;

	UINT32 winNameLength;
	UINT32 winCommentLength;

	strcat_s(filename, 1024, AppDir);
	strcat_s(filename, 1024, "\\ww_wdws.ndx");
	error = fopen_s(&fp, filename, "r");
	if (error != 0)
		return 1; //Error: could not open window list
	while (fgets(line, 1024, fp)) {
		//skip any lines that are too short
		if (strlen(line) > 3) {
			index = strtok_s(line, " ", &nexttoken);
			window = strtok_s(NULL, "?\n", &nexttoken);
			if (strcmp(window, WindowName) == 0) {
				success = 1;
				break;
			}
		}
	}
	fclose(fp);

	if (success == 0)
		return 2;//Error: window index could not be located

	char winfile[30] = "win";
	while (strlen(winfile) < 8 - strlen(index)) {
		strcat_s(winfile, 30, "0");
	}
	strcat_s(winfile, 30, index);
	strcat_s(winfile, 30, ".win");

	strcpy_s(filename, 1024, AppDir);
	strcat_s(filename, 1024, "\\");
	strcat_s(filename, 1024, winfile);

	error = fopen_s(&fp, filename, "r");
	if (error != 0)
		return 3; //Error: could not open window file
	
	//first we need to read the length of the window name
	fseek(fp, winNameLenOffset, SEEK_SET);
	if (fread(&winNameLengthData, 4, 1, fp) == 0) {
		fclose(fp);
		return 4;//Error: could not read window data
	}
	winNameLength = (winNameLengthData[3] << 24) | (winNameLengthData[2] << 16) | (winNameLengthData[1] << 8) | winNameLengthData[0];
	//adding the length to our current position points us to the length of the comment field
	winCommentLenOffset = winNameLenOffset + winNameLength;
	//now read the comment length
	fseek(fp, winCommentLenOffset, SEEK_SET);
	if (fread(&winCommentLengthData, 4, 1, fp) == 0) {
		fclose(fp);
		return 4;//Error: could not read window data
	}
	winCommentLength = (winCommentLengthData[3] << 24) | (winCommentLengthData[2] << 16) | (winCommentLengthData[1] << 8) | winCommentLengthData[0];
	//we can now move to the X/Y offsets which should be fixed offsets from here... (hopefully)
	Xoff = winCommentLenOffset + winCommentLength + 0x104;
	Yoff = winCommentLenOffset + winCommentLength + 0x11C;

	fseek(fp, Xoff, SEEK_SET);
	if (fread(&Xdata, 4, 1, fp) == 0) {
		fclose(fp);
		return 4;//Error: could not read window data
	}

	fseek(fp, Yoff, SEEK_SET);
	if (fread(&Ydata, 4, 1, fp) == 0) {
		fclose(fp);
		return 4;//Error: could not read window data
	}

	x = (Xdata[3] << 24) | (Xdata[2] << 16) | (Xdata[1] << 8) | Xdata[0];
	y = (Ydata[3] << 24) | (Ydata[2] << 16) | (Ydata[1] << 8) | Ydata[0];
	
	//write the x/y values to the tags
	ACCID accID = PtAccInit(0, 0);
	if (accID == 0)
		return 5;//Error: InTouch is not running
	HPT hPtLeft = PtAccActivate(accID, XTag);
	HPT hPtTop = PtAccActivate(accID, YTag);
	if (hPtLeft != 0) 
		PtAccWriteI(accID, hPtLeft, x);
	if (hPtTop != 0)
		PtAccWriteI(accID, hPtTop, y);
	PtAccDeactivate(accID, hPtLeft);
	PtAccDeactivate(accID, hPtTop);
	PtAccShutdown(accID);
	
	return 0;
}

HCINTOUCHUTILS_API int PasteBuiltInFuncs(LPSTR funcName, LPSTR result)
{
	strcpy_s(result, 100, funcName);
	strcat_s(result, 100, " (InfoInTouchAppDir(), \"WindowName\", XTag.Name, YTag.Name);");		
	return 0;
}
