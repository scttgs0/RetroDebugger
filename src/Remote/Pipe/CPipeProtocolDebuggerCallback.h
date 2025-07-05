#ifndef _CPipeProtocolRetroDebuggerCallback_H_
#define _CPipeProtocolRetroDebuggerCallback_H_

// TODO: this is deprecated and will be removed

#include "CByteBuffer.h"
#include "SYS_PIPE.h"

class CPipeProtocolDebuggerCallback : public CPipeProtocolCallback
{
public:
	virtual bool PipeProtocolCallbackInterpretPacket(CByteBuffer *inByteBuffer);
	void SendBinaryPacketStatus(u32 sequenceNumber, u8 errorNum);
	void SendBinaryPacket(u16 packetId, u32 sequenceNumber, CByteBuffer *data);
};


typedef enum c64d_packet_e {
	C64D_PACKET_STATUS = 0,
	C64D_PACKET_LOAD_FILE,
	C64D_PACKET_PAUSE_RUN,
	C64D_PACKET_CONTINUE_RUN,
	C64D_PACKET_STEP_ONE_CYCLE,
	C64D_PACKET_STEP_ONE_INSTRUCTION,
	C64D_PACKET_STEP_OVER_JSR,
	C64D_PACKET_RESET_SOFT,
	C64D_PACKET_RESET_HARD,
	C64D_PACKET_JMP_TO_ADDRESS_AT_CURSOR,
	C64D_PACKET_MOVE_CURSOR_TO_ADDRESS,
	C64D_PACKET_MAKE_JMP_TO_ADDRESS,
	C64D_PACKET_GET_CPU_STATUS,
	C64D_PACKET_SET_BREAKPOINT_PC,
	C64D_PACKET_LAST
} c64d_packet_t;

typedef enum c64d_packet_status_e {
	C64D_PACKET_STATUS_OK = 0,
	C64D_PACKET_STATUS_ERROR_NOT_FOUND
} c64d_packet_status_t;



#endif
