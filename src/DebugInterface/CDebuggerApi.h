#ifndef _CDEBUGGERAPI_H_
#define _CDEBUGGERAPI_H_

#include "SYS_Defs.h"
#include "DebuggerDefs.h"
#include "SYS_KeyCodes.h"
#include "CDebugInterface.h"
#include "SYS_Threading.h"
#include "CImageData.h"

class CGuiView;
class CDebugInterface;

class CDebuggerApi
{
public:
	CDebuggerApi(CDebugInterface *debugInterface);
	virtual ~CDebuggerApi();
	
	CDebugInterface *debugInterface;
	
	static CDebuggerApi *GetDebuggerApi(u8 emulatorType);
	
	virtual void ResetMachine(bool isHardReset);
	virtual void PauseEmulation();
	virtual void UnPauseEmulation();
	
	virtual void StepOneCycle();
	virtual void StepOverInstruction();
	virtual void StepOverSubroutine();	// step over JSR

	virtual u64 GetMainCpuCycleCounter();
	virtual u64 GetMainCpuInstructionCycleCounter();
	virtual unsigned int GetEmulationFrameNumber();

	virtual void CreateNewPicture(u8 mode, u8 backgroundColor);
	virtual void StartThread(CSlrThread *run);
	
	// rgb reference image in vic editor
	virtual void ClearReferenceImage();
	virtual void LoadReferenceImage(char *filePath);
	virtual void LoadReferenceImage(CImageData *imageData);
	virtual void SetReferenceImageLayerVisible(bool isVisible);
	CImageData *GetReferenceImage();
	
	// emulated computer screen
	virtual void ClearScreen();
	virtual void ZoomDisplay(float newScale);
	
	// load from png file
	virtual bool ConvertImageToScreen(char *filePath);
	virtual bool ConvertImageToScreen(CImageData *imageData);
	virtual CImageData *GetScreenImage(int *width, int *height);
	
	// always returns 320x200 for C64:
	virtual CImageData *GetScreenImageWithoutBorders();
	
	//
	virtual u8 PaintPixel(int x, int y, u8 color);
	virtual u8 PaintReferenceImagePixel(int x, int y, u8 color);
	virtual u8 PaintReferenceImagePixel(int x, int y, u8 r, u8 g, u8 b, u8 a);
	
	// data adapters
	CDataAdapter *GetDataAdapterMemoryWithIO();
	CDataAdapter *GetDataAdapterMemoryDirectRAM();

	// direct access
	virtual void SetByte(int addr, u8 v);	/// NOTE: this is generic poke, peek, in most cases including I/O, should not be used
	virtual void SetByteWithIo(int addr, u8 v);
	virtual void SetByteToRam(int addr, u8 v);
	virtual u8 GetByte(int addr);
	virtual u8 GetByteWithIo(int addr);
	virtual u8 GetByteFromRam(int addr);
	
	virtual void SetWord(int addr, u16 v);
	virtual void MakeJmp(int addr);
	
	//
	virtual void DetachEverything();
	virtual void ClearRam(int startAddr, int endAddr, u8 value);
	
	//
	virtual int Assemble(int addr, char *assembleText);
	
	CByteBuffer *byteBufferAssembleText;
	virtual u8 *Assemble64Tass(char *assembleText, int *codeStartAddr, int *codeSize);
	virtual void Assemble64TassClearBuffer();
	virtual u8 *Assemble64Tass(int *codeStartAddr, int *codeSize);
	virtual u8 *Assemble64Tass(int *codeStartAddr, int *codeSize, const char *storeAsmFileName, bool quiet);
	virtual bool Assemble64TassToRam(int *codeStartAddr, int *codeSize);
	virtual bool Assemble64TassToRam(int *codeStartAddr, int *codeSize, char *storeAsmFileName, bool quiet);
	virtual void Assemble64TassAddLine(const char *format, ...);
	
	//
	virtual void AddWatch(CSlrString *segmentName, int address, CSlrString *watchName, uint8 representation, int numberOfValues);
	virtual void AddWatch(int address, char *watchName, uint8 representation, int numberOfValues);
	virtual void AddWatch(int address, char *watchName);
	
	//
	virtual void SaveBinary(int fromAddr, int toAddr, const char *fileName);
	virtual int LoadBinary(int fromAddr, const char *filePath);
	
	//
	virtual void LoadSnapshot(const char *fileName);
	
	virtual u8 *ExomizerMemoryRaw(u16 fromAddr, u16 toAddr, int *compressedSize);
	
	//
	virtual void ResetEmulationCounters();
	
	//
	virtual void SetWarpSpeed(bool isWarpSpeed);

	// input
	virtual bool KeyboardDown(u32 mtKeyCode);
	virtual bool KeyboardUp(u32 mtKeyCode);
	
	virtual void JoystickDown(int port, u32 axis);
	virtual void JoystickUp(int port, u32 axis);
	
	// shortcuts to the Engine
	virtual void ShowMessage(const char *text);
	virtual void BlitText(const char *text, float posX, float posY, float fontSize);
	virtual void Sleep(long milliseconds);
	virtual long GetCurrentTimeInMilliseconds();
	virtual long GetCurrentFrameNumber();
	
	static u32 JoypadAxisNameToAxisCode(std::string axisName);

	// segments
	CSlrString *GetCurrentSegmentName();
	bool SetCurrentSegment(CSlrString *segmentName);
	
	// breakpoints
	u64 AddBreakpointPC(int addr);
	u64 RemoveBreakpointPC(int addr);
	u64 AddBreakpointMemory(int address, u32 memoryAccess, DataBreakpointComparison comparison, int value);
	u64 RemoveBreakpointMemory(int address);
	
	//
	virtual void AddView(CGuiView *view);

	//
	virtual nlohmann::json GetCpuStatusJson();
};

#endif
