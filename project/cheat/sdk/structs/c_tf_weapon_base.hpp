#ifndef SKELETONS_CX_C_TF_WEAPON_BASE_HPP
#define SKELETONS_CX_C_TF_WEAPON_BASE_HPP

#include "../enums/weapon_stat_trak_module_type.hpp"
#include "c_base_combat_weapon.hpp"
#include "c_econ_entity.hpp"
#include "c_game_event_listener.hpp"
#include "c_tf_weapon_info.hpp"
#include "i_has_owner.hpp"
#include "../enums/weapon_strange_type.hpp

namespace sdk
{
	struct c_tf_weapon_base : public c_econ_entity, public c_base_combat_weapon, public i_has_owner, public c_game_event_listener {
	public:
		NETVAR( lowered, bool, "CTFWeaponBase", "m_bLowered" );
		NETVAR( reload_mode, int, "CTFWeaponBase", "m_iReloadMode" );
		NETVAR( reset_parity, bool, "CTFWeaponBase", "m_bResetParity" );
		NETVAR( reloaded_through_anim_event, bool, "CTFWeaponBase", "m_bReloadedThroughAnimEvent" );
		NETVAR( disguise_weapon, bool, "CTFWeaponBase", "m_bDisguiseWeapon" );
		NETVAR( last_crit_check_time, float, "CTFWeaponBase", "m_flLastCritCheckTime" );
		NETVAR( reload_prior_next_fire, float, "CTFWeaponBase", "m_flReloadPriorNextFire" );
		NETVAR( last_fire_time, float, "CTFWeaponBase", "m_flLastFireTime" );
		NETVAR( effect_bar_regen_time, float, "CTFWeaponBase", "m_flEffectBarRegenTime" );
		NETVAR( observed_crit_chance, float, "CTFWeaponBase", "m_flObservedCritChance" );
		NETVAR( energy, float, "CTFWeaponBase", "m_flEnergy" );
		NETVAR( extra_wearable, c_base_handle, "CTFWeaponBase", "m_hExtraWearable" );
		NETVAR( extra_wearable_view_model, c_base_handle, "CTFWeaponBase", "m_hExtraWearableViewModel" );
		NETVAR( being_repurposed_for_taunt, bool, "CTFWeaponBase", "m_bBeingRepurposedForTaunt" );
		NETVAR( kill_combo_class, int, "CTFWeaponBase", "m_nKillComboClass" );
		NETVAR( kill_combo_count, int, "CTFWeaponBase", "m_nKillComboCount" );
		NETVAR( inspect_anim_end_time, float, "CTFWeaponBase", "m_flInspectAnimEndTime" );
		NETVAR( inspect_stage, int, "CTFWeaponBase", "m_nInspectStage" );
		NETVAR( consecutive_shots, int, "CTFWeaponBase", "m_iConsecutiveShots" );

		int weapon_mode;
		c_tf_weapon_info* weapon_info;
		bool in_attack;
		bool in_attack2;
		bool current_attack_is_crit;
		bool current_crit_is_random;
		bool current_attack_is_during_demo_charge;

		weapon_strange_type strange_type;
		weapon_stat_trak_module_type stat_trak_module_type;

		int alt_fire_hint;

		int reload_start_clip_amount;

		float crit_time;
		int last_crit_check_frame;
		int current_seed;
		float last_rapid_fire_crit_check_time;
	};
} // namespace sdk

#endif // SKELETONS_CX_C_TF_WEAPON_BASE_HPP
