// process_1.cpp : Defines the entry point for the console application.
//use psapi.h

#include "stdafx.h"

int main(int argc, char* argv[])
{
	MessageBox(0,"Using at least 2 ways to enumerate all modules of your process\nthe module list needs to include ImageBase and PathName. ","zyguo (2012/03/16)",MB_OK);

	//char filename[MAX_PATH];
	DWORD dwProcessId[1024], cbNeededProcess,myid;
	
	myid=GetCurrentProcessId();
	//printf("%08x\n",myid);

	if ( !EnumProcesses( dwProcessId, sizeof(dwProcessId), &cbNeededProcess ) )
        return 0;

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, myid );
	
	if(hProcess!=NULL)
	{
		HMODULE hMods[1024];
		DWORD cbNeededModule ;
		
		if ( EnumProcessModules( hProcess, hMods, sizeof(hMods), &cbNeededModule ) )
		{
			PROCESS_MEMORY_COUNTERS ProcessMemCounters ;
			GetProcessMemoryInfo ( hProcess, &ProcessMemCounters, sizeof(ProcessMemCounters) ) ;
			//printf("id:%08x\n",myid);
			for ( unsigned int j = 0; j < ( cbNeededModule/sizeof(DWORD) ); j++ )
			{
				char szModuleName[MAX_PATH];
				if ( GetModuleFileNameEx ( hProcess, hMods[j], szModuleName, sizeof(szModuleName) ) )
				{
					MODULEINFO ModuleInfo ;
					//printf("%08x\n",hMods[j]);
					if ( GetModuleInformation ( hProcess, hMods[j], &ModuleInfo, sizeof(ModuleInfo) ) )
					{
						printf("%s",szModuleName);
						printf("\t%08x\n",hMods[j]);
					}
				
				}

			}
			

		}
	}	
	return 0;
}

