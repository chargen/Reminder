#ifndef	___multimedia_timers___
#define	___multimedia_timers___

#include	<mmsystem.h>

class CMMTimers : public CWnd
{
public:
	CMMTimers(UINT resolution);
	virtual ~CMMTimers();

	UINT	getTimerRes() { return timerRes; };

	bool	startTimer(UINT period,bool oneShot);
	bool	stopTimer();

	virtual void timerProc() {};

protected:
	UINT	timerRes;
	UINT	timerId;
};


#endif