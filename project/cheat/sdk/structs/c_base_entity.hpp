//
// Created by Liga on 2/25/2022.
//

#ifndef SKELETONS_CX_C_BASE_ENTITY_HPP
#define SKELETONS_CX_C_BASE_ENTITY_HPP

#include "../../helpers/netvars/netvars.hpp"

#include "i_client_entity.hpp"
#include "vector.hpp"

namespace sdk
{
	struct c_base_handle;

	struct c_base_entity : public i_client_entity {
		NETVAR( anim_time, float, "CBaseEntity", "m_flAnimTime" );
		NETVAR( simulation_time, float, "CBaseEntity", "m_flSimulationTime" );
		NETVAR( interpolation_frame, int, "CBaseEntity", "m_ubInterpolationFrame" );
		NETVAR( origin, vector, "CBaseEntity", "m_vecOrigin" );
		NETVAR( rotation, vector, "CBaseEntity", "m_angRotation" );
		NETVAR( model_index, int, "CBaseEntity", "m_nModelIndex" );
		NETVAR( effects, int, "CBaseEntity", "m_fEffects" );
		NETVAR( render_mode, int, "CBaseEntity", "m_nRenderMode" );
		NETVAR( render_fx, int, "CBaseEntity", "m_nRenderFX" );
		NETVAR( render, int, "CBaseEntity", "m_clrRender" );
		NETVAR( team_num, int, "CBaseEntity", "m_iTeamNum" );
		NETVAR( collision_group, int, "CBaseEntity", "m_CollisionGroup" );
		NETVAR( elasticity, float, "CBaseEntity", "m_flElasticity" );
		NETVAR( shadow_cast_distance, float, "CBaseEntity", "m_flShadowCastDistance" );
		NETVAR( owner_entity, c_base_handle, "CBaseEntity", "m_hOwnerEntity" );
		NETVAR( effect_entity, c_base_handle, "CBaseEntity", "m_hEffectEntity" );
		NETVAR( moveparent, int, "CBaseEntity", "moveparent" );
		NETVAR( parent_attachment, int, "CBaseEntity", "m_iParentAttachment" );
		NETVAR( collision, void*, "CBaseEntity", "m_Collision" );
		NETVAR( mins_pre_scaled, vector, "CBaseEntity", "m_vecMinsPreScaled" );
		NETVAR( maxs_pre_scaled, vector, "CBaseEntity", "m_vecMaxsPreScaled" );
		NETVAR( mins, vector, "CBaseEntity", "m_vecMins" );
		NETVAR( maxs, vector, "CBaseEntity", "m_vecMaxs" );
		NETVAR( solid_type, int, "CBaseEntity", "m_nSolidType" );
		NETVAR( solid_flags, int, "CBaseEntity", "m_usSolidFlags" );
		NETVAR( surround_type, int, "CBaseEntity", "m_nSurroundType" );
		NETVAR( trigger_bloat, int, "CBaseEntity", "m_triggerBloat" );
		NETVAR( uniform_trigger_bloat, bool, "CBaseEntity", "m_bUniformTriggerBloat" );
		NETVAR( specified_surrounding_mins_pre_scaled, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMinsPreScaled" );
		NETVAR( specified_surrounding_maxs_pre_scaled, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMaxsPreScaled" );
		NETVAR( specified_surrounding_mins, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMins" );
		NETVAR( specified_surrounding_maxs, vector, "CBaseEntity", "m_vecSpecifiedSurroundingMaxs" );
		NETVAR( texture_frame_index, int, "CBaseEntity", "m_iTextureFrameIndex" );
		NETVAR( predictable_id, int, "CBaseEntity", "m_PredictableID" );
		NETVAR( is_player_simulated, bool, "CBaseEntity", "m_bIsPlayerSimulated" );
		NETVAR( simulated_every_tick, bool, "CBaseEntity", "m_bSimulatedEveryTick" );
		NETVAR( animated_every_tick, bool, "CBaseEntity", "m_bAnimatedEveryTick" );
		NETVAR( alternate_sorting, bool, "CBaseEntity", "m_bAlternateSorting" );
		NETVAR( model_index_overrides, void*, "CBaseEntity", "m_nModelIndexOverrides" );
		NETVAR( movetype, int, "CBaseEntity", "movetype" );

		void get_bone_position( std::uint32_t bone_index, vector* position, qangle* angles );

		bool is_player( );
	};
} // namespace sdk

#endif // SKELETONS_CX_C_BASE_ENTITY_HPP
