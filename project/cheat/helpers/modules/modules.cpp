#include "modules.hpp"

void modules::init( )
{
	g_client_dll           = module( "client.dll" );
	g_engine_dll           = module( "engine.dll" );
	g_materialsystem_dll   = module( "materialsystem.dll" );
	g_vguimatsurface_dll   = module( "vguimatsurface.dll" );
	g_inputsystem_dll      = module( "inputsystem.dll" );
	g_studiorender_dll     = module( "studiorender.dll" );
	g_filesystem_stdio_dll = module( "filesystem_stdio.dll" );
	g_server_dll           = module( "server.dll" );
	g_shaderapidx9_dll     = module( "shaderapidx9.dll" );
};

void modules::shutdown( ) { }