#include <iostream>
#include <fstream>
#include <list>
#include <semaphore.h>
#include "swftypes.h"
#include "tags.h"
#include "frame.h"

class SWF_HEADER
{
private:
	UI8 Signature[3];
	UI8 Version;
	UI32 FileLenght;
	RECT FrameSize;
	UI16 FrameRate;
	UI16 FrameCount;
public:
	SWF_HEADER(std::ifstream& in);
	const RECT& getFrameSize(){ return FrameSize; }
};

class SystemState
{
public:
	//Semaphore to wait for new frames to be available
	sem_t new_frame;

	std::list < RenderTag* > dictionary;

	//Frames mutex (shared with drawing thread)
	sem_t sem_frames;
	std::vector<Frame> frames;

	RGBA Background;

	SystemState();
};

class ParseThread
{
private:
	static pthread_t t;
	static void* worker(void*);
public:
	ParseThread(std::ifstream& in);
	void wait();
	static std::list < DisplayListTag* > displayList;
};
