#ifndef SKELETONS_CX_I_BASECLIENTDLL_HPP
#define SKELETONS_CX_I_BASECLIENTDLL_HPP

struct baseclientdll {
public:
	virtual int              connect(void* appsystemfactory, void* globals) = 0;
	virtual int              disconnect(void) = 0;
	virtual int              init(void* appsystemfactory, void* globals) = 0;
	virtual void             postinit() = 0;
	virtual void             shutdown(void) = 0;
	virtual void             levelinitpreentity(char const* mapname) = 0;
	virtual void             levelinitpostentity() = 0;
	virtual void             levelshutdown(void) = 0;
	virtual clientclass* getallclasses(void) = 0;

};



#endif // SKELETONS_CX_I_BASECLIENTDLL_HPP
