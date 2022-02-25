#ifndef SKELETONS_CX_I_CLIENTMODE_HPP
#define SKELETONS_CX_I_CLIENTMODE_HPP

struct headtrackmovementmode_t;

struct clientmode {
	virtual ~clientmode(){}
	virtual void initviewport() = 0;
	virtual void init() = 0;
	virtual void vgui_shutdown() = 0;
	virtual void shutdown() = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual void layout() = 0;
	virtual unsigned int* getviewport() = 0;
	virtual void* getviewportanimationcontroller() = 0;
	virtual void processinput(bool active) = 0;
	virtual bool shoulddrawdetailobjects() = 0;
	virtual bool shoulddrawentity(void* ent) = 0;
	virtual bool shoulddrawlocalplayer(void* player) = 0;
	virtual bool shoulddrawparticles() = 0;
	virtual bool shoulddrawfog(void) = 0;
	virtual void overrideview(void* setup) = 0;
	virtual int keyinput(int down, int keynum, const char* pszcurrentbinding) = 0;
	virtual void startmessagemode(int messagemodetype) = 0;
	virtual unsigned int* getmessagepanel() = 0;
	virtual void overridemouseinput(float* x, float* y) = 0;
	virtual bool createmove(float inputsampletime, void* cmd) = 0;
	virtual void levelinit(const char* newmap) = 0;
	virtual void levelshutdown(void) = 0;
	virtual bool shoulddrawviewmodel(void) = 0;
	virtual bool shoulddrawcrosshair(void) = 0;
	virtual void adjustengineviewport(int& x, int& y, int& width, int& height) = 0;
	virtual void prerender(void* setup) = 0;
	virtual void postrender(void) = 0;
	virtual void postrendervgui() = 0;
	virtual void activateingamevguicontext(unsigned int* panel) = 0;
	virtual void deactivateingamevguicontext() = 0;
	virtual float getviewmodelfov(void) = 0;
	virtual bool canrecorddemo(char* errormsg, int length) const = 0;
	virtual void computevguiresconditions(void* kvconditions) = 0;
	virtual wchar_t* getservername() = 0;
	virtual void setservername(wchar_t* name) = 0;
	virtual wchar_t* getmapname() = 0;
	virtual void setmapname(wchar_t* name) = 0;
	virtual bool dopostscreenspaceeffects(const void* setup) = 0;
	virtual void displayreplaymessage(const char* localizename, float duration, bool urgent, const char* sound,
	                                   bool dlg) = 0;
	virtual void update() = 0;
	virtual bool shouldblackoutaroundhud() = 0;
	virtual headtrackmovementmode_t shouldoverrideheadtrackcontrol() = 0;
	virtual bool isinfopanelallowed() = 0;
	virtual void infopaneldisplayed() = 0;
	virtual bool ishtmlinfopanelallowed() = 0;
	virtual void ondemorecordstart(const char* demobasename) = 0;
	virtual void ondemorecordstop() = 0;
};

#endif // SKELETONS_CX_I_CLIENTMODE_HPP
