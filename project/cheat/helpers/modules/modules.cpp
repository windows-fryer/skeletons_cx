#include "modules.hpp"

void modules::init( )
{
	client_dll           = module( "client.dll" );
	engine_dll           = module( "engine.dll" );
	materialsystem_dll   = module( "materialsystem.dll" );
	vguimatsurface_dll   = module( "vguimatsurface.dll" );
	inputsystem_dll      = module( "inputsystem.dll" );
	studiorender_dll     = module( "studiorender.dll" );
	filesystem_stdio_dll = module( "filesystem_stdio.dll" );
	server_dll           = module( "server.dll" );
};