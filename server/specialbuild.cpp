//----------------------------------------------------------
//
//   SA:MP Multiplayer Modification For GTA:SA
//   Copyright 2004-2006 SA:MP team
//
//----------------------------------------------------------

#if defined(SCRIPTING_ONLY) && defined(SCRIPTING_SIGNATURE)

// The following is defined for scripting builds only

// A plugin development key will be embedded into the scripting build
// to identify who the build was made for.

#include "main.h"
#include "signer.h"
#include "pluginkey.h"

#pragma section(".sig", read)

// This value needs to be set manually using a hex editor / PE Explorer.
__declspec(allocate(".sig"))
BYTE g_pbScriptingSignature[0x80] = 
	{ 0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
	  0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
	  0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
	  0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
	  0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
	  0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
	  0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
      0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA };

bool VerifyScriptingBuildSignature(tDevKeyStruct* pdksDevKey)
{				
	BYTE pbHash[] = {0xe8, 0x07, 0x21, 0x79, 0x3c, 0x24, 0xae, 0x14, 0xed, 0xfc, 0xa9,
						0xb2, 0x6a, 0xd4, 0x06, 0xa9, 0x81, 0x5c, 0xd3, 0xff};

	CSigner signer;
	signer.SetPublicKey((unsigned char*)PLUGIN_PUB_KEY);
	signer.SetSignature(g_pbScriptingSignature);
	signer.DecryptSignBuffer(reinterpret_cast<unsigned char*>(pdksDevKey));
	
	if (memcmp(pdksDevKey->dwSHA1, pbHash, sizeof(pbHash))==0) 
		return true;
	else
		return false;
}

#endif