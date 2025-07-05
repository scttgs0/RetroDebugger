#ifndef _CDEBUGSYMBOLS_H_
#define _CDEBUGSYMBOLS_H_

#include "SYS_Defs.h"
#include "hjson.h"
#include <list>
#include <vector>

class CSlrFile;
class CByteBuffer;
class CSlrString;
class CDebugInterface;
class CDebugAsmSource;
class CDebugSymbolsSegment;
class CDebugSymbolsCodeLabel;
class CDebugDataAdapter;
class CDebugEventsHistory;
class CDebugMemoryCell;
class CDebugMemory;

#define MAX_LABEL_TEXT_BUFFER_SIZE	512

#define C64_SYMBOL_DEVICE_COMMODORE	1
#define C64_SYMBOL_DEVICE_DRIVE1541	2

class CDebugSymbols
{
public:
	CDebugSymbols(CDebugInterface *debugInterface, bool supportBreakpoints);
	virtual ~CDebugSymbols();
	
	CDebugInterface *debugInterface;
	virtual void SetDataAdapter(CDebugDataAdapter *dataAdapter);
	
	bool supportBreakpoints;

	CDebugDataAdapter *dataAdapter;
	CDebugEventsHistory *debugEventsHistory;

	CDebugAsmSource *asmSource;
	
	std::vector<CDebugSymbolsSegment *> segments;
	CDebugSymbolsSegment *currentSegment;
	CSlrString *previousSegmentName;
	int currentSegmentNum;
	CDebugSymbolsSegment *FindSegment(CSlrString *segmentName);
	
	void ActivateSelectedSegment();
	void ActivateSegment(CDebugSymbolsSegment *segment);
	void DeactivateSegment();
	
	//
	void SelectNextSegment();
	void SelectPreviousSegment();
	bool SetSegment(CSlrString *segmentName);
	
	virtual void ClearTemporaryBreakpoint();
	virtual void UpdateRenderBreakpoints();
	
	//
	
	void DeleteAllSymbols();
	void ParseSymbols(CSlrString *fileName);
	void ParseSymbols(CSlrFile *file);
	void ParseSymbols(CByteBuffer *byteBuffer);
	
	void DeleteAllBreakpoints();
	void ParseBreakpoints(CSlrString *fileName);
	void ParseBreakpoints(CByteBuffer *byteBuffer);
	
	void DeleteAllWatches();
	void ParseWatches(CSlrString *fileName);
	void ParseWatches(CSlrFile *file);
	void ParseWatches(CByteBuffer *byteBuffer);

	void DeleteSourceDebugInfo();
	void ParseSourceDebugInfo(CSlrString *fileName);
	void ParseSourceDebugInfo(CSlrFile *file);
	void ParseSourceDebugInfo(CByteBuffer *byteBuffer);
	
	//
	void LoadLabelsRetroDebuggerFormat(CSlrString *filePath);
	void SaveLabelsRetroDebuggerFormat(CSlrString *filePath);
	
	bool SerializeLabelsToHjson(Hjson::Value hjsonRoot);
	bool DeserializeLabelsFromHjson(Hjson::Value hjsonRoot);

	//
	void LoadWatchesRetroDebuggerFormat(CSlrString *filePath);
	void SaveWatchesRetroDebuggerFormat(CSlrString *filePath);
	bool SerializeWatchesToHjson(Hjson::Value hjsonRoot);
	bool DeserializeWatchesFromHjson(Hjson::Value hjsonRoot);
	
	//
	void LoadBreakpointsRetroDebuggerFormat(CSlrString *filePath);
	void SaveBreakpointsRetroDebuggerFormat(CSlrString *filePath);
	bool SerializeBreakpointsToHjson(Hjson::Value hjsonRoot);
	bool DeserializeBreakpointsFromHjson(Hjson::Value hjsonRoot);

	// get currently executed addr (PC) to be checked against breakpoint, note it is virtual to have it different for C64 Drive CPU
	virtual int GetCurrentExecuteAddr();

	//
	virtual void LockMutex();
	virtual void UnlockMutex();
	
	//
	void CreateDefaultSegment();
	
	// virtual method to create specific symbols segment (for C64 including raster line, VIC, CIA, NMI irqs, for Drive including VIA irqs, etc.)
	virtual CDebugSymbolsSegment *CreateNewDebugSymbolsSegment(CSlrString *name);
	virtual CDebugSymbolsSegment *CreateNewDebugSymbolsSegment(CSlrString *name, int segmentNum);
	
	// memory cells for memory events and coloring
	virtual CDebugMemory *CreateNewDebugMemoryMap();
	CDebugMemory *memory;
};

#endif
