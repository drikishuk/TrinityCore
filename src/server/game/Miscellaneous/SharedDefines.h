/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITY_SHAREDDEFINES_H
#define TRINITY_SHAREDDEFINES_H

#include "Define.h"
#include "DetourNavMesh.h"

float const GROUND_HEIGHT_TOLERANCE = 0.05f; // Extra tolerance to z position to check if it is in air or on ground.
constexpr float Z_OFFSET_FIND_HEIGHT = 1.5f;

enum OriginsNerfSpells : uint32
{
    ORIGINS_NERF_GENERIC = 200000,
    ORIGINS_NERF_WARRIOR_ARMS,
    ORIGINS_NERF_WARRIOR_FURY,
    ORIGINS_NERF_WARRIOR_PROTECTION,
    ORIGINS_NERF_PALADIN_RETRIBUTION,
    ORIGINS_NERF_PALADIN_PROTECTION,
    ORIGINS_NERF_PALADIN_HOLY,
    ORIGINS_NERF_HUNTER_MARKSMANSHIP,
    ORIGINS_NERF_HUNTER_BEAST_MASTERY,
    ORIGINS_NERF_HUNTER_SURVIVAL,
    ORIGINS_NERF_ROGUE_SUBTLETY,
    ORIGINS_NERF_ROGUE_ASSASINATION,
    ORIGINS_NERF_ROGUE_COMBAT,
    ORIGINS_NERF_PRIEST_SHADOW,
    ORIGINS_NERF_PRIEST_HOLY,
    ORIGINS_NERF_PRIEST_DISCIPLINE,
    ORIGINS_NERF_DK_BLOOD,
    ORIGINS_NERF_DK_FROST,
    ORIGINS_NERF_DK_UNHOLY,
    ORIGINS_NERF_SHAMAN_ENHANCEMENT,
    ORIGINS_NERF_SHAMAN_ELEMENTAL,
    ORIGINS_NERF_SHAMAN_RESTORATION,
    ORIGINS_NERF_MAGE_FROST,
    ORIGINS_NERF_MAGE_FIRE,
    ORIGINS_NERF_MAGE_ARCANE,
    ORIGINS_NERF_WARLOCK_DESTRUCTION,
    ORIGINS_NERF_WARLOCK_AFFLICTION,
    ORIGINS_NERF_WARLOCK_DEMONOLOGY,
    ORIGINS_NERF_DRUID_BALANCE,
    ORIGINS_NERF_DRUID_FERAL,
    ORIGINS_NERF_DRUID_RESTORATION
};

constexpr uint32 ORIGINS_NERF_SPELLS_BEGIN = 200000;
constexpr uint32 ORIGINS_NERF_SPELLS_END = 200031;

enum SpellEffIndex : uint8
{
    EFFECT_0 = 0,
    EFFECT_1 = 1,
    EFFECT_2 = 2
};

enum class SpellTargetIndex : uint8
{
    TargetA = 0,
    TargetB = 1
};

// used in script definitions
#define EFFECT_FIRST_FOUND 254
#define EFFECT_ALL 255

// loot modes for creatures and gameobjects, bitmask!
enum LootModes
{
    LOOT_MODE_DEFAULT                  = 0x1,
    LOOT_MODE_HARD_MODE_1              = 0x2,
    LOOT_MODE_HARD_MODE_2              = 0x4,
    LOOT_MODE_HARD_MODE_3              = 0x8,
    LOOT_MODE_HARD_MODE_4              = 0x10,
    LOOT_MODE_JUNK_FISH                = 0x8000
};

enum Expansions
{
    EXPANSION_CLASSIC                  = 0,
    EXPANSION_THE_BURNING_CRUSADE      = 1,
    EXPANSION_WRATH_OF_THE_LICH_KING   = 2,
    EXPANSION_CATACLYSM                = 3,
    MAX_EXPANSIONS                     = 4
};

enum Gender
{
    GENDER_MALE                        = 0,
    GENDER_FEMALE                      = 1,
    GENDER_NONE                        = 2
};

// Race value is index in ChrRaces.dbc
enum Races
{
    RACE_NONE               = 0,
    RACE_HUMAN              = 1,
    RACE_ORC                = 2,
    RACE_DWARF              = 3,
    RACE_NIGHTELF           = 4,
    RACE_UNDEAD_PLAYER      = 5,
    RACE_TAUREN             = 6,
    RACE_GNOME              = 7,
    RACE_TROLL              = 8,
    RACE_GOBLIN             = 9,
    RACE_BLOODELF           = 10,
    RACE_DRAENEI            = 11,
    //RACE_FEL_ORC            = 12,
    //RACE_NAGA               = 13,
    //RACE_BROKEN             = 14,
    //RACE_SKELETON           = 15,
    //RACE_VRYKUL             = 16,
    //RACE_TUSKARR            = 17,
    //RACE_FOREST_TROLL       = 18,
    //RACE_TAUNKA             = 19,
    //RACE_NORTHREND_SKELETON = 20,
    //RACE_ICE_TROLL          = 21,
    RACE_WORGEN             = 22,
    //RACE_GILNEAN            = 23
};

// max+1 for player race
#define MAX_RACES         23

#define RACEMASK_ALL_PLAYABLE \
    ((1<<(RACE_HUMAN-1))   |(1<<(RACE_ORC-1))          |(1<<(RACE_DWARF-1))   | \
     (1<<(RACE_NIGHTELF-1))|(1<<(RACE_UNDEAD_PLAYER-1))|(1<<(RACE_TAUREN-1))  | \
     (1<<(RACE_GNOME-1))   |(1<<(RACE_TROLL-1))        |(1<<(RACE_BLOODELF-1))| \
     (1<<(RACE_DRAENEI-1)) |(1<<(RACE_GOBLIN-1))       |(1<<(RACE_WORGEN-1)))

#define RACEMASK_ALLIANCE \
    ((1<<(RACE_HUMAN-1)) | (1<<(RACE_DWARF-1)) | (1<<(RACE_NIGHTELF-1)) | \
     (1<<(RACE_GNOME-1)) | (1<<(RACE_DRAENEI-1)) | (1<<(RACE_WORGEN-1)))

#define RACEMASK_HORDE RACEMASK_ALL_PLAYABLE & ~RACEMASK_ALLIANCE

// Class value is index in ChrClasses.dbc
enum Classes
{
    CLASS_NONE          = 0,
    CLASS_WARRIOR       = 1,
    CLASS_PALADIN       = 2,
    CLASS_HUNTER        = 3,
    CLASS_ROGUE         = 4,
    CLASS_PRIEST        = 5,
    CLASS_DEATH_KNIGHT  = 6,
    CLASS_SHAMAN        = 7,
    CLASS_MAGE          = 8,
    CLASS_WARLOCK       = 9,
    //CLASS_UNK           = 10,
    CLASS_DRUID         = 11
};

// max+1 for player class
#define MAX_CLASSES       12

#define CLASSMASK_ALL_PLAYABLE \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1)) | \
    (1<<(CLASS_DEATH_KNIGHT-1)))

// valid classes for creature_template.unit_class
enum UnitClass
{
    UNIT_CLASS_WARRIOR                  = 1,
    UNIT_CLASS_PALADIN                  = 2,
    UNIT_CLASS_ROGUE                    = 4,
    UNIT_CLASS_MAGE                     = 8
};

#define CLASSMASK_ALL_CREATURES ((1<<(UNIT_CLASS_WARRIOR-1)) | (1<<(UNIT_CLASS_PALADIN-1)) | (1<<(UNIT_CLASS_ROGUE-1)) | (1<<(UNIT_CLASS_MAGE-1)))

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))

#define PLAYER_MAX_BATTLEGROUND_QUEUES 2

enum ReputationRank
{
    REP_HATED       = 0,
    REP_HOSTILE     = 1,
    REP_UNFRIENDLY  = 2,
    REP_NEUTRAL     = 3,
    REP_FRIENDLY    = 4,
    REP_HONORED     = 5,
    REP_REVERED     = 6,
    REP_EXALTED     = 7
};

enum FactionTemplates
{
    FACTION_NONE                        = 0,
    FACTION_CREATURE                    = 7,
    FACTION_ESCORTEE_A_NEUTRAL_PASSIVE  = 10,
    FACTION_MONSTER                     = 14,
    FACTION_MONSTER_2                   = 16,
    FACTION_TROLL_BLOODSCALP            = 28,
    FACTION_PREY                        = 31,
    FACTION_ESCORTEE_H_NEUTRAL_PASSIVE  = 33,
    FACTION_FRIENDLY                    = 35,
    FACTION_TROLL_FROSTMANE             = 37,
    FACTION_OGRE                        = 45,
    FACTION_ORC_DRAGONMAW               = 62,
    FACTION_HORDE_GENERIC               = 83,
    FACTION_ALLIANCE_GENERIC            = 84,
    FACTION_DEMON                       = 90,
    FACTION_ELEMENTAL                   = 91,
    FACTION_DRAGONFLIGHT_BLACK          = 103,
    FACTION_ESCORTEE_N_NEUTRAL_PASSIVE  = 113,
    FACTION_ENEMY                       = 168,
    FACTION_ESCORTEE_A_NEUTRAL_ACTIVE   = 231,
    FACTION_ESCORTEE_H_NEUTRAL_ACTIVE   = 232,
    FACTION_ESCORTEE_N_NEUTRAL_ACTIVE   = 250,
    FACTION_ESCORTEE_N_FRIEND_PASSIVE   = 290,
    FACTION_TITAN                       = 415,
    FACTION_ESCORTEE_N_FRIEND_ACTIVE    = 495,
    FACTION_RATCHET                     = 637,
    FACTION_GOBLIN_DARK_IRON_BAR_PATRON = 736,
    FACTION_DARK_IRON_DWARVES           = 754,
    FACTION_ESCORTEE_A_PASSIVE          = 774,
    FACTION_ESCORTEE_H_PASSIVE          = 775,
    FACTION_UNDEAD_SCOURGE              = 974,
    FACTION_GUILD                       = 1168,
    FACTION_EARTHEN_RING                = 1726,
    FACTION_ALLIANCE_GENERIC_WG         = 1732,
    FACTION_HORDE_GENERIC_WG            = 1735,
    FACTION_ARAKKOA                     = 1738,
    FACTION_ASHTONGUE_DEATHSWORN        = 1820,
    FACTION_FLAYER_HUNTER               = 1840,
    FACTION_MONSTER_SPAR_BUDDY          = 1868,
    FACTION_ESCORTEE_N_ACTIVE           = 1986,
    FACTION_ESCORTEE_H_ACTIVE           = 2046,
    FACTION_UNDEAD_SCOURGE_2            = 2068,
    FACTION_UNDEAD_SCOURGE_3            = 2084,
    FACTION_SCARLET_CRUSADE             = 2089,
    FACTION_SCARLET_CRUSADE_2           = 2096
};

#define MIN_REPUTATION_RANK (REP_HATED)
#define MAX_REPUTATION_RANK 8

#define MAX_SPILLOVER_FACTIONS 5

enum MoneyConstants
{
    COPPER = 1,
    SILVER = COPPER*100,
    GOLD   = SILVER*100
};

enum Stats
{
    STAT_STRENGTH                      = 0,
    STAT_AGILITY                       = 1,
    STAT_STAMINA                       = 2,
    STAT_INTELLECT                     = 3,
    STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

enum Powers
{
    POWER_MANA                          = 0,
    POWER_RAGE                          = 1,
    POWER_FOCUS                         = 2,
    POWER_ENERGY                        = 3,
    POWER_UNUSED                        = 4,
    POWER_RUNE                          = 5,
    POWER_RUNIC_POWER                   = 6,
    POWER_SOUL_SHARDS                   = 7,
    POWER_ECLIPSE                       = 8,
    POWER_HOLY_POWER                    = 9,
    POWER_ALTERNATE_POWER               = 10,           // Used in some quests
    MAX_POWERS                          = 11,
    POWER_ALL                           = 127,          // default for class?
    POWER_HEALTH                        = 0xFFFFFFFE    // (-2 as signed value)
};

#define MAX_POWERS_PER_CLASS                5
#define UNIT_HEALTH_REGENERATION_INTERVAL   2 * IN_MILLISECONDS
#define PLAYER_POWER_UPDATE_INTERVAL        2 * IN_MILLISECONDS
#define UNIT_POWER_UPDATE_INTERVAL          1 * IN_MILLISECONDS

enum SpellSchools
{
    SPELL_SCHOOL_NORMAL                 = 0,
    SPELL_SCHOOL_HOLY                   = 1,
    SPELL_SCHOOL_FIRE                   = 2,
    SPELL_SCHOOL_NATURE                 = 3,
    SPELL_SCHOOL_FROST                  = 4,
    SPELL_SCHOOL_SHADOW                 = 5,
    SPELL_SCHOOL_ARCANE                 = 6,
    MAX_SPELL_SCHOOL                    = 7
};

enum SpellSchoolMask : uint32
{
    SPELL_SCHOOL_MASK_NONE    = 0x00,                       // not exist
    SPELL_SCHOOL_MASK_NORMAL  = (1 << SPELL_SCHOOL_NORMAL), // PHYSICAL (Armor)
    SPELL_SCHOOL_MASK_HOLY    = (1 << SPELL_SCHOOL_HOLY),
    SPELL_SCHOOL_MASK_FIRE    = (1 << SPELL_SCHOOL_FIRE),
    SPELL_SCHOOL_MASK_NATURE  = (1 << SPELL_SCHOOL_NATURE),
    SPELL_SCHOOL_MASK_FROST   = (1 << SPELL_SCHOOL_FROST),
    SPELL_SCHOOL_MASK_SHADOW  = (1 << SPELL_SCHOOL_SHADOW),
    SPELL_SCHOOL_MASK_ARCANE  = (1 << SPELL_SCHOOL_ARCANE),

    // unions

    // 124, not include normal and holy damage
    SPELL_SCHOOL_MASK_SPELL   = (SPELL_SCHOOL_MASK_FIRE   |
                                  SPELL_SCHOOL_MASK_NATURE | SPELL_SCHOOL_MASK_FROST  |
                                  SPELL_SCHOOL_MASK_SHADOW | SPELL_SCHOOL_MASK_ARCANE),
    // 126
    SPELL_SCHOOL_MASK_MAGIC   = (SPELL_SCHOOL_MASK_HOLY | SPELL_SCHOOL_MASK_SPELL),

    // 127
    SPELL_SCHOOL_MASK_ALL     = (SPELL_SCHOOL_MASK_NORMAL | SPELL_SCHOOL_MASK_MAGIC)
};

inline SpellSchools GetFirstSchoolInMask(SpellSchoolMask mask)
{
    for (int i = 0; i < MAX_SPELL_SCHOOL; ++i)
        if (mask & (1 << i))
            return SpellSchools(i);

    return SPELL_SCHOOL_NORMAL;
}

enum ItemQualities : uint8
{
    ITEM_QUALITY_POOR                  = 0,                 //GREY
    ITEM_QUALITY_NORMAL                = 1,                 //WHITE
    ITEM_QUALITY_UNCOMMON              = 2,                 //GREEN
    ITEM_QUALITY_RARE                  = 3,                 //BLUE
    ITEM_QUALITY_EPIC                  = 4,                 //PURPLE
    ITEM_QUALITY_LEGENDARY             = 5,                 //ORANGE
    ITEM_QUALITY_ARTIFACT              = 6,                 //LIGHT YELLOW
    ITEM_QUALITY_HEIRLOOM              = 7
};

#define MAX_ITEM_QUALITY                 8

enum SpellCategory
{
    SPELL_CATEGORY_FOOD             = 11,
    SPELL_CATEGORY_DRINK            = 59
};

enum SpellVisualKit
{
    SPELL_VISUAL_KIT_FOOD           = 406,
    SPELL_VISUAL_KIT_DRINK          = 438
};

enum WorgenRacialSpells
{
    SPELL_RUNNING_WILD_LEARN        = 94098,
    SPELL_TWO_FORMS_RACIAL          = 68996,
    SPELL_ALTERED_FORM_RACIAL       = 97709
};

enum SpiritOfRedemptionSpells
{
    SPELL_SPIRIT_OF_REDEMPTION_IMMUNITY = 62371,
    SPELL_UNTRANSFORM_HERO              = 25100
};

const uint32 ItemQualityColors[MAX_ITEM_QUALITY] =
{
    0xff9d9d9d,        //GREY
    0xffffffff,        //WHITE
    0xff1eff00,        //GREEN
    0xff0070dd,        //BLUE
    0xffa335ee,        //PURPLE
    0xffff8000,        //ORANGE
    0xffe6cc80,        //LIGHT YELLOW
    0xffe6cc80         //LIGHT YELLOW
};

// ***********************************
// Spell Attributes definitions
// ***********************************

enum SpellAttr0 : uint32
{
    SPELL_ATTR0_PROC_FAILURE_BURNS_CHARGE                           = 0x00000001, // TITLE Proc Failure Burns Charge
    SPELL_ATTR0_USES_RANGED_SLOT                                    = 0x00000002, // Uses Ranged Slot DESCRIPTION Use ammo, ranged attack range modifiers, ranged haste, etc.
    SPELL_ATTR0_ON_NEXT_SWING_NO_DAMAGE                             = 0x00000004, // On Next Swing (No Damage) DESCRIPTION Both "on next swing" attributes have identical handling in server & client
    SPELL_ATTR0_DO_NOT_LOG_IMMUNE_MISSES                            = 0x00000008, // Do Not Log Immune Misses (client only)
    SPELL_ATTR0_IS_ABILITY                                          = 0x00000010, // Is Ability DESCRIPTION Cannot be reflected, not affected by cast speed modifiers, etc.
    SPELL_ATTR0_IS_TRADESKILL                                       = 0x00000020, // Is Tradeskill DESCRIPTION Displayed in recipe list, not affected by cast speed modifiers
    SPELL_ATTR0_PASSIVE                                             = 0x00000040, // Passive DESCRIPTION Spell is automatically cast on self by core
    SPELL_ATTR0_DO_NOT_DISPLAY_SPELLBOOK_AURA_ICON_COMBAT_LOG       = 0x00000080, // Do Not Display (Spellbook, Aura Icon, Combat Log) (client only) DESCRIPTION Not visible in spellbook or aura bar
    SPELL_ATTR0_DO_NOT_LOG                                          = 0x00000100, // Do Not Log (client only) DESCRIPTION Spell will not appear in combat logs
    SPELL_ATTR0_HELD_ITEM_ONLY                                      = 0x00000200, // Held Item Only (client only) DESCRIPTION Client will automatically select main-hand item as cast target
    SPELL_ATTR0_ON_NEXT_SWING                                       = 0x00000400, // On Next Swing DESCRIPTION Both "on next swing" attributes have identical handling in server & client
    SPELL_ATTR0_WEARER_CASTS_PROC_TRIGGER                           = 0x00000800, // TITLE Wearer Casts Proc Trigger DESCRIPTION Just a marker attribute to show auras that trigger another spell (either directly or with a script)
    SPELL_ATTR0_SERVER_ONLY                                         = 0x00001000, // Server Only
    SPELL_ATTR0_ALLOW_ITEM_SPELL_IN_PVP                             = 0x00002000, // Allow Item Spell In PvP
    SPELL_ATTR0_ONLY_INDOORS                                        = 0x00004000, // Only Indoors
    SPELL_ATTR0_ONLY_OUTDOORS                                       = 0x00008000, // Only Outdoors
    SPELL_ATTR0_NOT_SHAPESHIFTED                                    = 0x00010000, // Not Shapeshifted
    SPELL_ATTR0_ONLY_STEALTHED                                      = 0x00020000, // Only Stealthed
    SPELL_ATTR0_DO_NOT_SHEATH                                       = 0x00040000, // Do Not Sheath (client only)
    SPELL_ATTR0_SCALES_WITH_CREATURE_LEVEL                          = 0x00080000, // Scales w/ Creature Level DESCRIPTION For non-player casts, scale impact and power cost with caster's level
    SPELL_ATTR0_CANCELS_AUTO_ATTACK_COMBAT                          = 0x00100000, // Cancels Auto Attack Combat DESCRIPTION After casting this, the current auto-attack will be interrupted
    SPELL_ATTR0_NO_ACTIVE_DEFENSE                                   = 0x00200000, // No Active Defense DESCRIPTION Spell cannot be dodged, parried or blocked
    SPELL_ATTR0_TRACK_TARGET_IN_CAST_PLAYER_ONLY                    = 0x00400000, // Track Target in Cast (Player Only) (client only)
    SPELL_ATTR0_ALLOW_CAST_WHILE_DEAD                               = 0x00800000, // Allow Cast While Dead DESCRIPTION Spells without this flag cannot be cast by dead units in non-triggered contexts
    SPELL_ATTR0_ALLOW_WHILE_MOUNTED                                 = 0x01000000, // Allow While Mounted
    SPELL_ATTR0_COOLDOWN_ON_EVENT                                   = 0x02000000, // Cooldown On Event DESCRIPTION Spell is unusable while already active, and cooldown does not begin until the effects have worn off
    SPELL_ATTR0_AURA_IS_DEBUFF                                      = 0x04000000, // Aura Is Debuff DESCRIPTION Forces the spell to be treated as a negative spell
    SPELL_ATTR0_ALLOW_WHILE_SITTING                                 = 0x08000000, // Allow While Sitting
    SPELL_ATTR0_NOT_IN_COMBAT_ONLY_PEACEFUL                         = 0x10000000, // Not In Combat (Only Peaceful)
    SPELL_ATTR0_NO_IMMUNITIES                                       = 0x20000000, // No Immunities DESCRIPTION Allows spell to pierce invulnerability, unless the invulnerability spell also has this attribute
    SPELL_ATTR0_HEARTBEAT_RESIST                                    = 0x40000000, // Heartbeat Resist DESCRIPTION Periodically re-rolls against resistance to potentially expire aura early
    SPELL_ATTR0_NO_AURA_CANCEL                                      = 0x80000000  // No Aura Cancel DESCRIPTION Prevents the player from voluntarily canceling a positive aura
};

// EnumUtils: DESCRIBE THIS
enum SpellAttr1 : uint32
{
    SPELL_ATTR1_DISMISS_PET_FIRST                                   = 0x00000001, // Dismiss Pet First DESCRIPTION Without this attribute, summoning spells will fail if caster already has a pet
    SPELL_ATTR1_USE_ALL_MANA                                        = 0x00000002, // Use All Mana DESCRIPTION Ignores listed power cost and drains entire pool instead
    SPELL_ATTR1_IS_CHANNELLED                                       = 0x00000004, // Is Channelled DESCRIPTION Both "channeled" attributes have identical handling in server & client
    SPELL_ATTR1_NO_REDIRECTION                                      = 0x00000008, // No Redirection DESCRIPTION Spell will not be attracted by SPELL_MAGNET auras (Grounding Totem)
    SPELL_ATTR1_NO_SKILL_INCREASE                                   = 0x00000010, // No Skill Increase
    SPELL_ATTR1_ALLOW_WHILE_STEALTHED                               = 0x00000020, // Allow While Stealthed
    SPELL_ATTR1_IS_SELF_CHANNELLED                                  = 0x00000040, // Is Self Channelled DESCRIPTION Both "channeled" attributes have identical handling in server & client
    SPELL_ATTR1_NO_REFLECTION                                       = 0x00000080, // No Reflection DESCRIPTION Spell will pierce through Spell Reflection and similar
    SPELL_ATTR1_ONLY_PEACEFUL_TARGETS                               = 0x00000100, // Only Peaceful Targets DESCRIPTION Target cannot be in combat
    SPELL_ATTR1_INITIATES_COMBAT_ENABLES_AUTO_ATTACK                = 0x00000200, // Initiates Combat (Enables Auto-Attack) (client only) DESCRIPTION Caster will begin auto-attacking the target on cast
    SPELL_ATTR1_NO_THREAT                                           = 0x00000400, // No Threat DESCRIPTION Also does not cause target to engage
    SPELL_ATTR1_AURA_UNIQUE                                         = 0x00000800, // Aura Unique DESCRIPTION Aura will not refresh its duration when recast
    SPELL_ATTR1_FAILURE_BREAKS_STEALTH                              = 0x00001000, // Failure Breaks Stealth
    SPELL_ATTR1_TOGGLE_FAR_SIGHT                                    = 0x00002000, // Toggle Far Sight (client only)
    SPELL_ATTR1_TRACK_TARGET_IN_CHANNEL                             = 0x00004000, // Track Target in Channel DESCRIPTION While channeling, adjust facing to face target
    SPELL_ATTR1_IMMUNITY_PURGES_EFFECT                              = 0x00008000, // Immunity Purges Effect DESCRIPTION For immunity spells, cancel all auras that this spell would make you immune to when the spell is applied
    SPELL_ATTR1_IMMUNITY_TO_HOSTILE_AND_FRIENDLY_EFFECTS            = 0x00010000, /*WRONG IMPL*/ // Immunity to Hostile & Friendly Effects DESCRIPTION Will not pierce Divine Shield, Ice Block and other full invulnerabilities
    SPELL_ATTR1_NO_AUTOCAST_AI                                      = 0x00020000, // No AutoCast (AI)
    SPELL_ATTR1_PREVENTS_ANIM                                       = 0x00040000, /*NYI*/ // Prevents Anim DESCRIPTION Auras apply UNIT_FLAG_PREVENT_EMOTES_FROM_CHAT_TEXT
    SPELL_ATTR1_EXCLUDE_CASTER                                      = 0x00080000, // Exclude Caster
    SPELL_ATTR1_FINISHING_MOVE_DAMAGE                               = 0x00100000, // Finishing Move - Damage
    SPELL_ATTR1_THREAT_ONLY_ON_MISS                                 = 0x00200000, /*NYI*/ // Threat only on Miss
    SPELL_ATTR1_FINISHING_MOVE_DURATION                             = 0x00400000, // Finishing Move - Duration
    SPELL_ATTR1_IGNORE_OWNERS_DEATH                                 = 0x00800000, /*NYI*/ // Ignore Owner's Death
    SPELL_ATTR1_SPECIAL_SKILLUP                                     = 0x01000000, // Special Skillup
    SPELL_ATTR1_AURA_STAYS_AFTER_COMBAT                             = 0x02000000, // Aura Stays After Combat
    SPELL_ATTR1_REQUIRE_ALL_TARGETS                                 = 0x04000000, // TITLE Require All Targets
    SPELL_ATTR1_DISCOUNT_POWER_ON_MISS                              = 0x08000000, // Discount Power On Miss
    SPELL_ATTR1_NO_AURA_ICON                                        = 0x10000000, // No Aura Icon (client only)
    SPELL_ATTR1_NAME_IN_CHANNEL_BAR                                 = 0x20000000, // Name in Channel Bar (client only)
    SPELL_ATTR1_DISPEL_ALL_STACKS                                   = 0x40000000, // Dispel All Stacks
    SPELL_ATTR1_CAST_WHEN_LEARNED                                   = 0x80000000  // Cast When Learned
};

enum SpellAttr2 : uint32
{
    SPELL_ATTR2_ALLOW_DEAD_TARGET                                   = 0x00000001, // TITLE Allow Dead Target
    SPELL_ATTR2_NO_SHAPESHIFT_UI                                    = 0x00000002, // TITLE No shapeshift UI (client only) DESCRIPTION Does not replace action bar when shapeshifted
    SPELL_ATTR2_IGNORE_LINE_OF_SIGHT                                = 0x00000004, // TITLE Ignore Line of Sight
    SPELL_ATTR2_ALLOW_LOW_LEVEL_BUFF                                = 0x00000008, // TITLE Allow Low Level Buff
    SPELL_ATTR2_USE_SHAPESHIFT_BAR                                  = 0x00000010, // TITLE Use Shapeshift Bar (client only)
    SPELL_ATTR2_AUTO_REPEAT                                         = 0x00000020, // TITLE Auto Repeat
    SPELL_ATTR2_CANNOT_CAST_ON_TAPPED                               = 0x00000040, // TITLE Cannot cast on tapped DESCRIPTION Can only target untapped units, or those tapped by caster
    SPELL_ATTR2_DO_NOT_REPORT_SPELL_FAILURE                         = 0x00000080, // TITLE Do Not Report Spell Failure
    SPELL_ATTR2_INCLUDE_IN_ADVANCED_COMBAT_LOG                      = 0x00000100, // TITLE Include In Advanced Combat Log (client only) DESCRIPTION Determines whether to include this aura in list of auras in SMSG_ENCOUNTER_START
    SPELL_ATTR2_ALWAYS_CAST_AS_UNIT                                 = 0x00000200, /*NYI, UNK*/ // TITLE Always Cast As Unit
    SPELL_ATTR2_SPECIAL_TAMING_FLAG                                 = 0x00000400, // TITLE Special Taming Flag DESCRIPTION Related to taming?
    SPELL_ATTR2_NO_TARGET_PER_SECOND_COSTS                          = 0x00000800, // TITLE No Target Per-Second Costs
    SPELL_ATTR2_CHAIN_FROM_CASTER                                   = 0x00001000, // TITLE Chain From Caster
    SPELL_ATTR2_ENCHANT_OWN_ITEM_ONLY                               = 0x00002000, // TITLE Enchant own item only
    SPELL_ATTR2_ALLOW_WHILE_INVISIBLE                               = 0x00004000, // TITLE Allow While Invisible
    SPELL_ATTR2_DO_NOT_CONSUME_IF_GAINED_DURING_CAST                = 0x00008000, // TITLE Do Not Consume if Gained During Cast
    SPELL_ATTR2_NO_ACTIVE_PETS                                      = 0x00010000, // TITLE No Active Pets
    SPELL_ATTR2_DO_NOT_RESET_COMBAT_TIMERS                          = 0x00020000, // TITLE Do Not Reset Combat Timers DESCRIPTION Does not reset melee/ranged autoattack timer on cast
    SPELL_ATTR2_NO_JUMP_WHILE_CAST_PENDING                          = 0x00040000, // TITLE No Jump While Cast Pending (client only)
    SPELL_ATTR2_ALLOW_WHILE_NOT_SHAPESHIFTED_CASTER_FORM            = 0x00080000, // TITLE Allow While Not Shapeshifted (caster form) DESCRIPTION Even if Stances are nonzero, allow spell to be cast outside of shapeshift (though not in a different shapeshift)
    SPELL_ATTR2_INITIATE_COMBAT_POST_CAST_ENABLES_AUTO_ATTACK       = 0x00100000, // TITLE Initiate Combat Post-Cast (Enables Auto-Attack)
    SPELL_ATTR2_FAIL_ON_ALL_TARGETS_IMMUNE                          = 0x00200000, // TITLE Fail on all targets immune DESCRIPTION Causes BG flags to be dropped if combined with ATTR1_DISPEL_AURAS_ON_IMMUNITY
    SPELL_ATTR2_NO_INITIAL_THREAT                                   = 0x00400000, // TITLE No Initial Threat
    SPELL_ATTR2_PROC_COOLDOWN_ON_FAILURE                            = 0x00800000, // TITLE Proc Cooldown On Failure
    SPELL_ATTR2_ITEM_CAST_WITH_OWNER_SKILL                          = 0x01000000, // TITLE Item Cast With Owner Skill
    SPELL_ATTR2_DONT_BLOCK_MANA_REGEN                               = 0x02000000, // TITLE Don't Block Mana Regen
    SPELL_ATTR2_NO_SCHOOL_IMMUNITIES                                = 0x04000000, // TITLE No School Immunities DESCRIPTION Allow aura to be applied despite target being immune to new aura applications
    SPELL_ATTR2_IGNORE_WEAPONSKILL                                  = 0x08000000, // TITLE Ignore Weaponskill
    SPELL_ATTR2_NOT_AN_ACTION                                       = 0x10000000, // TITLE Not an Action
    SPELL_ATTR2_CANT_CRIT                                           = 0x20000000, // TITLE Can't Crit
    SPELL_ATTR2_ACTIVE_THREAT                                       = 0x40000000, // TITLE Active Threat
    SPELL_ATTR2_RETAIN_ITEM_CAST                                    = 0x80000000  // TITLE Retain Item Cast DESCRIPTION passes m_CastItem to triggered spells
};

enum SpellAttr3 : uint32
{
    SPELL_ATTR3_PVP_ENABLING                                        = 0x00000001, // TITLE PvP Enabling
    SPELL_ATTR3_NO_PROC_EQUIP_REQUIREMENT                           = 0x00000002, // TITLE No Proc Equip Requirement DESCRIPTION Ignores subclass mask check when checking proc
    SPELL_ATTR3_NO_CASTING_BAR_TEXT                                 = 0x00000004, // TITLE No Casting Bar Text
    SPELL_ATTR3_COMPLETELY_BLOCKED                                  = 0x00000008, // TITLE Completely Blocked
    SPELL_ATTR3_NO_RES_TIMER                                        = 0x00000010, // TITLE No Res Timer
    SPELL_ATTR3_NO_DURABILITY_LOSS                                  = 0x00000020, // TITLE No Durability Loss
    SPELL_ATTR3_NO_AVOIDANCE                                        = 0x00000040, // TITLE No Avoidance
    SPELL_ATTR3_DOT_STACKING_RULE                                   = 0x00000080, // TITLE DoT Stacking Rule DESCRIPTION Stack separately for each caster
    SPELL_ATTR3_ONLY_ON_PLAYER                                      = 0x00000100, // TITLE Only On Player
    SPELL_ATTR3_NOT_A_PROC                                          = 0x00000200, // TITLE Not a Proc DESCRIPTION Without this attribute, any triggered spell will be unable to trigger other auras' procs
    SPELL_ATTR3_REQUIRES_MAIN_HAND_WEAPON                           = 0x00000400, // TITLE Requires Main-Hand Weapon
    SPELL_ATTR3_ONLY_BATTLEGROUNDS                                  = 0x00000800, // TITLE Only Battlegrounds
    SPELL_ATTR3_ONLY_ON_GHOSTS                                      = 0x00001000, // TITLE Only On Ghosts
    SPELL_ATTR3_HIDE_CHANNEL_BAR                                    = 0x00002000, // TITLE Hide Channel Bar (client only)
    SPELL_ATTR3_HIDE_IN_RAID_FILTER                                 = 0x00004000, // TITLE Hide In Raid Filter (client only)
    SPELL_ATTR3_NORMAL_RANGED_ATTACK                                = 0x00008000, // TITLE Normal Ranged Attack DESCRIPTION Auto Shoot, Shoot, Throw - ranged normal attack attribute?
    SPELL_ATTR3_SUPPRESS_CASTER_PROCS                               = 0x00010000, // TITLE Suppress Caster Procs
    SPELL_ATTR3_SUPPRESS_TARGET_PROCS                               = 0x00020000, // TITLE Suppress Target Procs
    SPELL_ATTR3_ALWAYS_HIT                                          = 0x00040000, // TITLE Always Hit DESCRIPTION Spell cannot miss, or be dodged/parried/blocked
    SPELL_ATTR3_INSTANT_TARGET_PROCS                                = 0x00080000, // TITLE Instant Target Procs DESCRIPTION Proc events are triggered before spell batching processes the spell hit on target
    SPELL_ATTR3_ALLOW_AURA_WHILE_DEAD                               = 0x00100000, // TITLE Allow Aura While Dead
    SPELL_ATTR3_ONLY_PROC_OUTDOORS                                  = 0x00200000, // TITLE Only Proc Outdoors
    SPELL_ATTR3_DO_NOT_TRIGGER_TARGET_STAND                         = 0x00400000, // TITLE Do Not Trigger Target Stand
    SPELL_ATTR3_NO_DAMAGE_HISTORY                                   = 0x00800000, /*NYI, no damage history implementation*/ // TITLE No Damage History
    SPELL_ATTR3_REQUIRES_OFF_HAND_WEAPON                            = 0x01000000, // TITLE Requires Off-Hand Weapon
    SPELL_ATTR3_TREAT_AS_PERIODIC                                   = 0x02000000, // TITLE Treat As Periodic
    SPELL_ATTR3_CAN_PROC_FROM_PROCS                                 = 0x04000000, // TITLE Can Proc From Procs
    SPELL_ATTR3_ONLY_PROC_ON_CASTER                                 = 0x08000000, // TITLE Only Proc on Caster
    SPELL_ATTR3_IGNORE_CASTER_AND_TARGET_RESTRICTIONS               = 0x10000000, /*NYI*/ // TITLE Ignore Caster & Target Restrictions
    SPELL_ATTR3_IGNORE_CASTER_MODIFIERS                             = 0x20000000, // TITLE Ignore Caster Modifiers
    SPELL_ATTR3_DO_NOT_DISPLAY_RANGE                                = 0x40000000, // TITLE Do Not Display Range (client only)
    SPELL_ATTR3_NOT_ON_AOE_IMMUNE                                   = 0x80000000  /*NYI, no aoe immunity implementation*/ // TITLE Not On AOE Immune
};

enum SpellAttr4 : uint32
{
    SPELL_ATTR4_NO_CAST_LOG                                         = 0x00000001, // TITLE No Cast Log
    SPELL_ATTR4_CLASS_TRIGGER_ONLY_ON_TARGET                        = 0x00000002, // TITLE Class Trigger Only On Target
    SPELL_ATTR4_AURA_EXPIRES_OFFLINE                                = 0x00000004, // TITLE Aura Expires Offline DESCRIPTION Debuffs (except Resurrection Sickness) will automatically do this
    SPELL_ATTR4_NO_HELPFUL_THREAT                                   = 0x00000008, // TITLE No Helpful Threat
    SPELL_ATTR4_NO_HARMFUL_THREAT                                   = 0x00000010, // TITLE No Harmful Threat
    SPELL_ATTR4_ALLOW_CLIENT_TARGETING                              = 0x00000020, // TITLE Allow Client Targeting DESCRIPTION Allows client to send spell targets for this spell. Applies only to pet spells, without this attribute CMSG_PET_ACTION is sent instead of CMSG_PET_CAST_SPELL
    SPELL_ATTR4_CANNOT_BE_STOLEN                                    = 0x00000040, // TITLE Cannot Be Stolen
    SPELL_ATTR4_ALLOW_CAST_WHILE_CASTING                            = 0x00000080, // TITLE Allow Cast While Casting DESCRIPTION Ignores already in-progress cast and still casts
    SPELL_ATTR4_IGNORE_DAMAGE_TAKEN_MODIFIERS                       = 0x00000100, // TITLE Ignore Damage Taken Modifiers
    SPELL_ATTR4_COMBAT_FEEDBACK_WHEN_USABLE                         = 0x00000200, // TITLE Combat Feedback When Usable (client only)
    SPELL_ATTR4_WEAPON_SPEED_COST_SCALING                           = 0x00000400, // TITLE Weapon Speed Cost Scaling DESCRIPTION Adds 10 to power cost for each 1s of weapon speed
    SPELL_ATTR4_NO_PARTIAL_IMMUNITY                                 = 0x00000800, // TITLE No Partial Immunity
    SPELL_ATTR4_AURA_IS_BUFF                                        = 0x00001000, // TITLE Aura Is Buff
    SPELL_ATTR4_DO_NOT_LOG_CASTER                                   = 0x00002000, // TITLE Do Not Log Caster
    SPELL_ATTR4_REACTIVE_DAMAGE_PROC                                = 0x00004000, // TITLE Reactive Damage Proc DESCRIPTION Damage from spells with this attribute doesn't break auras that normally break on damage taken
    SPELL_ATTR4_NOT_IN_SPELLBOOK                                    = 0x00008000, // TITLE Not In Spellbook
    SPELL_ATTR4_NOT_IN_ARENA_OR_RATED_BATTLEGROUND                  = 0x00010000, // TITLE Not In Arena or Rated Battleground DESCRIPTION Makes spell unusable despite CD <= 10min
    SPELL_ATTR4_IGNORE_DEFAULT_ARENA_RESTRICTIONS                   = 0x00020000, // TITLE Ignore Default Arena Restrictions DESCRIPTION Makes spell usable despite CD > 10min
    SPELL_ATTR4_BOUNCY_CHAIN_MISSILES                               = 0x00040000, // TITLE Bouncy Chain Missiles DESCRIPTION Hits area targets over time instead of all at once
    SPELL_ATTR4_ALLOW_PROC_WHILE_SITTING                            = 0x00080000, // TITLE Allow Proc While Sitting
    SPELL_ATTR4_AURA_NEVER_BOUNCES                                  = 0x00100000, // TITLE Aura Never Bounces
    SPELL_ATTR4_ALLOW_ENTERING_ARENA                                = 0x00200000, // TITLE Allow Entering Arena
    SPELL_ATTR4_PROC_SUPPRESS_SWING_ANIM                            = 0x00400000, // TITLE Proc Suppress Swing Anim
    SPELL_ATTR4_SUPPRESS_WEAPON_PROCS                               = 0x00800000, // TITLE Suppress Weapon Procs
    SPELL_ATTR4_AUTO_RANGED_COMBAT                                  = 0x01000000, // TITLE Auto Ranged Combat
    SPELL_ATTR4_OWNER_POWER_SCALING                                 = 0x02000000, // TITLE Owner Power Scaling
    SPELL_ATTR4_ONLY_FLYING_AREAS                                   = 0x04000000, // TITLE Only Flying Areas
    SPELL_ATTR4_FORCE_DISPLAY_CASTBAR                               = 0x08000000, // TITLE Force Display Castbar
    SPELL_ATTR4_IGNORE_COMBAT_TIMER                                 = 0x10000000, // TITLE Ignore Combat Timer
    SPELL_ATTR4_AURA_BOUNCE_FAILS_SPELL                             = 0x20000000, // TITLE Aura Bounce Fails Spell
    SPELL_ATTR4_OBSOLETE                                            = 0x40000000, // TITLE Obsolete
    SPELL_ATTR4_USE_FACING_FROM_SPELL                               = 0x80000000  // TITLE Use Facing From Spell
};

enum SpellAttr5 : uint32
{
    SPELL_ATTR5_ALLOW_ACTIONS_DURING_CHANNEL                        = 0x00000001, // TITLE Allow Actions During Channel
    SPELL_ATTR5_NO_REAGENT_COST_WITH_AURA                           = 0x00000002, // TITLE No Reagent Cost With Aura
    SPELL_ATTR5_REMOVE_ENTERING_ARENA                               = 0x00000004, // TITLE Remove Entering Arena DESCRIPTION Force this aura to be removed on entering arena, regardless of other properties
    SPELL_ATTR5_ALLOW_WHILE_STUNNED                                 = 0x00000008, // TITLE Allow While Stunned
    SPELL_ATTR5_TRIGGERS_CHANNELING                                 = 0x00000010, // TITLE Triggers Channeling
    SPELL_ATTR5_LIMIT_N                                             = 0x00000020, // TITLE Limit N DESCRIPTION Remove previous application to another unit if applied
    SPELL_ATTR5_IGNORE_AREA_EFFECT_PVP_CHECK                        = 0x00000040, // TITLE Ignore Area Effect PvP Check
    SPELL_ATTR5_NOT_ON_PLAYER                                       = 0x00000080, // TITLE Not On Player
    SPELL_ATTR5_NOT_ON_PLAYER_CONTROLLED_NPC                        = 0x00000100, // TITLE Not On Player Controlled NPC
    SPELL_ATTR5_EXTRA_INITIAL_PERIOD                                = 0x00000200, // TITLE Extra Initial Period DESCRIPTION Immediately do periodic tick on apply
    SPELL_ATTR5_DO_NOT_DISPLAY_DURATION                             = 0x00000400, // TITLE Do Not Display Duration
    SPELL_ATTR5_IMPLIED_TARGETING                                   = 0x00000800, // TITLE Implied Targeting (client only)
    SPELL_ATTR5_MELEE_CHAIN_TARGETING                               = 0x00001000, // TITLE Melee Chain Targeting
    SPELL_ATTR5_SPELL_HASTE_AFFECTS_PERIODIC                        = 0x00002000, // TITLE Spell Haste Affects Periodic
    SPELL_ATTR5_NOT_AVAILABLE_WHILE_CHARMED                         = 0x00004000, // TITLE Not Available While Charmed
    SPELL_ATTR5_TREAT_AS_AREA_EFFECT                                = 0x00008000, // TITLE Treat as Area Effect
    SPELL_ATTR5_AURA_AFFECTS_NOT_JUST_REQ_EQUIPPED_ITEM             = 0x00010000, // TITLE Aura Affects Not Just Req. Equipped Item
    SPELL_ATTR5_ALLOW_WHILE_FLEEING                                 = 0x00020000, // TITLE Allow While Fleeing
    SPELL_ATTR5_ALLOW_WHILE_CONFUSED                                = 0x00040000, // TITLE Allow While Confused
    SPELL_ATTR5_AI_DOESNT_FACE_TARGET                               = 0x00080000, // TITLE AI Doesn't Face Target
    SPELL_ATTR5_DO_NOT_ATTEMPT_A_PET_RESUMMON_WHEN_DISMOUNTING      = 0x00100000, /*NYI*/ // TITLE Do Not Attempt a Pet Resummon When Dismounting
    SPELL_ATTR5_IGNORE_TARGET_REQUIREMENTS                          = 0x00200000, /*NYI*/ // TITLE Ignore Target Requirements
    SPELL_ATTR5_NOT_ON_TRIVIAL                                      = 0x00400000, /*NYI*/ // TITLE Not On Trivial
    SPELL_ATTR5_NO_PARTIAL_RESISTS                                  = 0x00800000, /*NYI*/ // TITLE No Partial Resists
    SPELL_ATTR5_IGNORE_CASTER_REQUIREMENTS                          = 0x01000000, /*NYI*/ // TITLE Ignore Caster Requirements
    SPELL_ATTR5_ALWAYS_LINE_OF_SIGHT                                = 0x02000000, // TITLE Always Line of Sight
    SPELL_ATTR5_ALWAYS_AOE_LINE_OF_SIGHT                            = 0x04000000, // TITLE Always AOE Line of Sight DESCRIPTION Requires line of sight between caster and target in addition to between dest and target
    SPELL_ATTR5_NO_CASTER_AURA_ICON                                 = 0x08000000, // TITLE No Caster Aura Icon (client only)
    SPELL_ATTR5_NO_TARGET_AURA_ICON                                 = 0x10000000, // TITLE No Target Aura Icon (client only)
    SPELL_ATTR5_AURA_UNIQUE_PER_CASTER                              = 0x20000000, // TITLE Aura Unique Per Caster
    SPELL_ATTR5_ALWAYS_SHOW_GROUND_TEXTURE                          = 0x40000000, // TITLE Always Show Ground Texture
    SPELL_ATTR5_ADD_MELEE_HIT_RATING                                = 0x80000000  /*NYI*/ // TITLE Add Melee Hit Rating
};

enum SpellAttr6 : uint32
{
    SPELL_ATTR6_NO_COOLDOWN_ON_TOOLTIP                              = 0x00000001, // TITLE No Cooldown On Tooltip (client only)
    SPELL_ATTR6_DO_NOT_RESET_COOLDOWN_IN_ARENA                      = 0x00000002, // TITLE Do Not Reset Cooldown In Arena
    SPELL_ATTR6_NOT_AN_ATTACK                                       = 0x00000004, /*NYI*/ // TITLE Not an Attack
    SPELL_ATTR6_CAN_ASSIST_IMMUNE_PC                                = 0x00000008, // TITLE Can Assist Immune PC
    SPELL_ATTR6_IGNORE_FOR_MOD_TIME_RATE                            = 0x00000010, /*NYI, time rate not implemented*/ // TITLE Ignore For Mod Time Rate
    SPELL_ATTR6_DO_NOT_CONSUME_RESOURCES                            = 0x00000020, // TITLE Do Not Consume Resources
    SPELL_ATTR6_FLOATING_COMBAT_TEXT_ON_CAST                        = 0x00000040, // TITLE Floating Combat Text On Cast (client only)
    SPELL_ATTR6_AURA_IS_WEAPON_PROC                                 = 0x00000080, // TITLE Aura Is Weapon Proc
    SPELL_ATTR6_DO_NOT_CHAIN_TO_CROWD_CONTROLLED_TARGETS            = 0x00000100, // TITLE Do Not Chain To Crowd-Controlled Targets DESCRIPTION Implicit targeting (chaining and area targeting) will not impact crowd controlled targets
    SPELL_ATTR6_ALLOW_ON_CHARMED_TARGETS                            = 0x00000200, /*NYI*/ // TITLE Allow On Charmed Targets
    SPELL_ATTR6_NO_AURA_LOG                                         = 0x00000400, // TITLE No Aura Log
    SPELL_ATTR6_NOT_IN_RAID_INSTANCES                               = 0x00000800, // TITLE Not In Raid Instances
    SPELL_ATTR6_ALLOW_WHILE_RIDING_VEHICLE                          = 0x00001000, // TITLE Allow While Riding Vehicle
    SPELL_ATTR6_IGNORE_PHASE_SHIFT                                  = 0x00002000, // TITLE Ignore Phase Shift
    SPELL_ATTR6_AI_PRIMARY_RANGED_ATTACK                            = 0x00004000, /*NYI*/ // TITLE AI Primary Ranged Attack
    SPELL_ATTR6_NO_PUSHBACK                                         = 0x00008000, // TITLE No Pushback
    SPELL_ATTR6_NO_JUMP_PATHING                                     = 0x00010000, /*NYI*/ // TITLE No Jump Pathing
    SPELL_ATTR6_ALLOW_EQUIP_WHILE_CASTING                           = 0x00020000, // TITLE Allow Equip While Casting
    SPELL_ATTR6_ORIGINATE_FROM_CONTROLLER                           = 0x00040000, // TITLE Originate From Controller DESCRIPTION Client will prevent casting if not possessed, charmer will be caster for all intents and purposes
    SPELL_ATTR6_DELAY_COMBAT_TIMER_DURING_CAST                      = 0x00080000, // TITLE Delay Combat Timer During Cast
    SPELL_ATTR6_AURA_ICON_ONLY_FOR_CASTER_LIMIT_10                  = 0x00100000, // TITLE Aura Icon Only For Caster (Limit 10) (client only)
    SPELL_ATTR6_SHOW_MECHANIC_AS_COMBAT_TEXT                        = 0x00200000, // TITLE Show Mechanic as Combat Text (client only)
    SPELL_ATTR6_ABSORB_CANNOT_BE_IGNORE                             = 0x00400000, // TITLE Absorb Cannot Be Ignore
    SPELL_ATTR6_TAPS_IMMEDIATELY                                    = 0x00800000, // TITLE Taps immediately
    SPELL_ATTR6_CAN_TARGET_UNTARGETABLE                             = 0x01000000, // TITLE Can Target Untargetable
    SPELL_ATTR6_DOESNT_RESET_SWING_TIMER_IF_INSTANT                 = 0x02000000, // TITLE Doesn't Reset Swing Timer if Instant
    SPELL_ATTR6_VEHICLE_IMMUNITY_CATEGORY                           = 0x04000000, /*NYI*/ // TITLE Vehicle Immunity Category
    SPELL_ATTR6_IGNORE_HEALING_MODIFIERS                            = 0x08000000, // TITLE Ignore Healing Modifiers DESCRIPTION This prevents certain healing modifiers from applying - see implementation if you really care about details
    SPELL_ATTR6_DO_NOT_AUTO_SELECT_TARGET_WITH_INITIATES_COMBAT     = 0x10000000, // TITLE Do Not Auto Select Target with Initiates Combat (client only)
    SPELL_ATTR6_IGNORE_CASTER_DAMAGE_MODIFIERS                      = 0x20000000, // TITLE Ignore Caster Damage Modifiers DESCRIPTION This prevents certain damage modifiers from applying - see implementation if you really care about details
    SPELL_ATTR6_DISABLE_TIED_EFFECT_POINTS                          = 0x40000000, /*NYI*/ // TITLE Disable Tied Effect Points
    SPELL_ATTR6_NO_CATEGORY_COOLDOWN_MODS                           = 0x80000000  // TITLE No Category Cooldown Mods
};

enum SpellAttr7
{
    SPELL_ATTR7_UNK0                             = 0x00000001, //  0 Shaman's new spells (Call of the ...), Feign Death.
    SPELL_ATTR7_IGNORE_DURATION_MODS             = 0x00000002, //  1 Duration is not affected by duration modifiers
    SPELL_ATTR7_REACTIVATE_AT_RESURRECT          = 0x00000004, //  2 Paladin's auras and 65607 only.
    SPELL_ATTR7_IS_CHEAT_SPELL                   = 0x00000008, //  3 Cannot cast if caster doesn't have UnitFlag2 & UNIT_FLAG2_ALLOW_CHEAT_SPELLS
    SPELL_ATTR7_UNK4                             = 0x00000010, //  4 Only 47883 (Soulstone Resurrection) and test spell.
    SPELL_ATTR7_SUMMON_TOTEM                     = 0x00000020, //  5 Only Shaman totems.
    SPELL_ATTR7_NO_PUSHBACK_ON_DAMAGE            = 0x00000040, //  6 Does not cause spell pushback on damage
    SPELL_ATTR7_UNK7                             = 0x00000080, //  7 66218 (Launch) spell.
    SPELL_ATTR7_HORDE_ONLY                       = 0x00000100, //  8 Teleports, mounts and other spells.
    SPELL_ATTR7_ALLIANCE_ONLY                    = 0x00000200, //  9 Teleports, mounts and other spells.
    SPELL_ATTR7_DISPEL_CHARGES                   = 0x00000400, // 10 Dispel and Spellsteal individual charges instead of whole aura.
    SPELL_ATTR7_INTERRUPT_ONLY_NONPLAYER         = 0x00000800, // 11 Only non-player casts interrupt, though Feral Charge - Bear has it.
    SPELL_ATTR7_SILENCE_ONLY_NONPLAYER           = 0x00001000, // 12 Not set in 3.2.2a.
    SPELL_ATTR7_CAN_ALWAYS_BE_INTERRUPTED        = 0x00002000, // 13 Can always be interrupted, even if caster is immune
    SPELL_ATTR7_UNK14                            = 0x00004000, // 14 Only 52150 (Raise Dead - Pet) spell.
    SPELL_ATTR7_UNK15                            = 0x00008000, // 15 Exorcism. Usable on players? 100% crit chance on undead and demons?
    SPELL_ATTR7_HIDDEN_IN_SPELLBOOK_WHEN_LEARNED = 0x00010000, // 16 After learning these spells become hidden in spellbook (but are visible when not learned for low level characters)
    SPELL_ATTR7_UNK17                            = 0x00020000, // 17 Only 27965 (Suicide) spell.
    SPELL_ATTR7_HAS_CHARGE_EFFECT                = 0x00040000, // 18 Only spells that have Charge among effects.
    SPELL_ATTR7_ZONE_TELEPORT                    = 0x00080000, // 19 Teleports to specific zones.
    SPELL_ATTR7_UNK20                            = 0x00100000, // 20 Blink, Divine Shield, Ice Block
    SPELL_ATTR7_UNK21                            = 0x00200000, // 21 Not set
    SPELL_ATTR7_UNK22                            = 0x00400000, // 22
    SPELL_ATTR7_CANT_DODGE                       = 0x00800000, // 23 No Attack Dodge
    SPELL_ATTR7_CANT_PARRY                       = 0x01000000, // 24 No Attack Parry
    SPELL_ATTR7_CANT_MISS                        = 0x02000000, // 25 No Attack Miss
    SPELL_ATTR7_UNK26                            = 0x04000000, // 26
    SPELL_ATTR7_UNK27                            = 0x08000000, // 27 Not set
    SPELL_ATTR7_CONSOLIDATED_RAID_BUFF           = 0x10000000, // 28 May be collapsed in raid buff frame (clientside attribute)
    SPELL_ATTR7_UNK29                            = 0x20000000, // 29 only 69028, 71237
    SPELL_ATTR7_UNK30                            = 0x40000000, // 30 Burning Determination, Divine Sacrifice, Earth Shield, Prayer of Mending
    SPELL_ATTR7_CLIENT_INDICATOR                 = 0x80000000
};

enum SpellAttr8
{
    SPELL_ATTR8_CANT_BLOCK                       = 0x00000001, //  0 No Attack Block
    SPELL_ATTR8_UNK1                             = 0x00000002, //  1
    SPELL_ATTR8_UNK2                             = 0x00000004, //  2
    SPELL_ATTR8_UNK3                             = 0x00000008, //  3
    SPELL_ATTR8_UNK4                             = 0x00000010, //  4
    SPELL_ATTR8_UNK5                             = 0x00000020, //  5
    SPELL_ATTR8_UNK6                             = 0x00000040, //  6
    SPELL_ATTR8_UNK7                             = 0x00000080, //  7
    SPELL_ATTR8_AFFECT_PARTY_AND_RAID            = 0x00000100, //  8 Nearly all spells have "all party and raid" in description
    SPELL_ATTR8_PERIODIC_CAN_CRIT                = 0x00000200, //  9 Periodic Can Crit
    SPELL_ATTR8_NAME_CHANGED_DURING_TRANSFORM    = 0x00000400, // 10 according to wowhead comments, name changes, title remains
    SPELL_ATTR8_UNK11                            = 0x00000800, // 11
    SPELL_ATTR8_AURA_SEND_AMOUNT                 = 0x00001000, // 12 Aura must have flag AFLAG_ANY_EFFECT_AMOUNT_SENT to send amount
    SPELL_ATTR8_UNK13                            = 0x00002000, // 13
    SPELL_ATTR8_UNK14                            = 0x00004000, // 14
    SPELL_ATTR8_WATER_MOUNT                      = 0x00008000, // 15 only one River Boat used in Thousand Needles
    SPELL_ATTR8_UNK16                            = 0x00010000, // 16
    SPELL_ATTR8_HASTE_AFFECTS_DURATION           = 0x00020000, // 17 Haste Affects Duration
    SPELL_ATTR8_REMEMBER_SPELLS                  = 0x00040000, // 18 at some point in time, these auras remember spells and allow to cast them later
    SPELL_ATTR8_USE_COMBO_POINTS_ON_ANY_TARGET   = 0x00080000, // 19 allows to consume combo points from dead targets
    SPELL_ATTR8_ARMOR_SPECIALIZATION             = 0x00100000, // 20
    SPELL_ATTR8_UNK21                            = 0x00200000, // 21
    SPELL_ATTR8_MELEE_HASTE_AFFECTS_PERIODIC     = 0x00400000, // 22 Melee Haste Affects Periodic
    SPELL_ATTR8_BATTLE_RESURRECTION              = 0x00800000, // 23 Used to limit the Amount of Resurrections in Boss Encounters
    SPELL_ATTR8_HEAL_PREDICTION                  = 0x01000000, // 24 Displays a predicted health amount on the targets frame
    SPELL_ATTR8_UNK25                            = 0x02000000, // 25
    SPELL_ATTR8_RAID_MARKER                      = 0x04000000, // 26 probably spell no need learn to cast
    SPELL_ATTR8_AI_FACE_TARGET                   = 0x08000000, // 27 AI Face Target
    SPELL_ATTR8_NOT_IN_BG_OR_ARENA               = 0x10000000, // 28 not allow to cast or deactivate currently active effect, not sure about Fast Track
    SPELL_ATTR8_MASTERY_SPECIALIZATION           = 0x20000000, // 29
    SPELL_ATTR8_UNK30                            = 0x40000000, // 30
    SPELL_ATTR8_ATTACK_IGNORE_IMMUNE_TO_PC_FLAG  = 0x80000000  // 31 Do not check UNIT_FLAG_IMMUNE_TO_PC in IsValidAttackTarget
};

enum SpellAttr9
{
    SPELL_ATTR9_UNK0                             = 0x00000001, //  0
    SPELL_ATTR9_UNK1                             = 0x00000002, //  1
    SPELL_ATTR9_RESTRICTED_FLIGHT_AREA           = 0x00000004, //  2 Dalaran and Wintergrasp flight area auras have it
    SPELL_ATTR9_UNK3                             = 0x00000008, //  3
    SPELL_ATTR9_SPECIAL_DELAY_CALCULATION        = 0x00000010, //  4
    SPELL_ATTR9_SUMMON_PLAYER_TOTEM              = 0x00000020, //  5
    SPELL_ATTR9_UNK6                             = 0x00000040, //  6
    SPELL_ATTR9_UNK7                             = 0x00000080, //  7
    SPELL_ATTR9_AIMED_SHOT                       = 0x00000100, //  8
    SPELL_ATTR9_NOT_USABLE_IN_ARENA              = 0x00000200, //  9 Cannot be used in arenas
    SPELL_ATTR9_UNK10                            = 0x00000400, // 10
    SPELL_ATTR9_UNK11                            = 0x00000800, // 11
    SPELL_ATTR9_UNK12                            = 0x00001000, // 12
    SPELL_ATTR9_SLAM                             = 0x00002000, // 13
    SPELL_ATTR9_USABLE_IN_RATED_BATTLEGROUNDS    = 0x00004000, // 14 Can be used in Rated Battlegrounds
    SPELL_ATTR9_UNK15                            = 0x00008000, // 15
    SPELL_ATTR9_UNK16                            = 0x00010000, // 16
    SPELL_ATTR9_UNK17                            = 0x00020000, // 17
    SPELL_ATTR9_UNK18                            = 0x00040000, // 18
    SPELL_ATTR9_ALLOW_DARK_SIMULACRUM            = 0x00080000, // 19 Allow Dark Simulacrum
    SPELL_ATTR9_UNK20                            = 0x00100000, // 20
    SPELL_ATTR9_UNK21                            = 0x00200000, // 21
    SPELL_ATTR9_UNK22                            = 0x00400000, // 22
    SPELL_ATTR9_UNK23                            = 0x00800000, // 23
    SPELL_ATTR9_UNK24                            = 0x01000000, // 24
    SPELL_ATTR9_UNK25                            = 0x02000000, // 25
    SPELL_ATTR9_UNK26                            = 0x04000000, // 26
    SPELL_ATTR9_UNK27                            = 0x08000000, // 27
    SPELL_ATTR9_UNK28                            = 0x10000000, // 28
    SPELL_ATTR9_UNK29                            = 0x20000000, // 29
    SPELL_ATTR9_UNK30                            = 0x40000000, // 30
    SPELL_ATTR9_UNK31                            = 0x80000000  // 31
};

enum SpellAttr10
{
    SPELL_ATTR10_BYPASS_VISIBILITY_CHECK          = 0x00000001, //  0 Bypass Visibility Check
    SPELL_ATTR10_IGNORE_POSITIVE_DAMAGE_TAKEN_MODS = 0x00000002, //  1 Ignore Positive Damage Taken Modifiers
    SPELL_ATTR10_USES_RANGED_SLOT                 = 0x00000004, //  2 Uses Ranged Slot (Cosmetic Only)
    SPELL_ATTR10_DONT_LOG_FULL_OVERHEAL           = 0x00000008, //  3 Do Not Log Full Overheal
    SPELL_ATTR10_WATER_SPOUT                      = 0x00000010, //  4 NPC Knockback - ignore doors
    SPELL_ATTR10_FORCE_NONBINARY_RESISTANCE       = 0x00000020, //  5 Force Non-Binary Resistance
    SPELL_ATTR10_NO_SUMMON_LOG                    = 0x00000040, //  6 No Summon Log
    SPELL_ATTR10_TELEPORT_PLAYER                  = 0x00000080, //  7 Ignore instance lock and farm limit on teleport
    SPELL_ATTR10_AREA_EFFECTS_USE_TARGET_RADIUS   = 0x00000100, //  8 Area Effects Use Target Radius
    SPELL_ATTR10_CHARGE_USE_ABSOLUTE_SPEED        = 0x00000200, //  9 Charge/JumpCharge - Use Absolute Speed
    SPELL_ATTR10_PROC_COOLDOWN_PER_TARGET         = 0x00000400, // 10 Proc cooldown on a per target basis
    SPELL_ATTR10_HERB_GATHERING_MINING            = 0x00000800, // 11 Lock chest at precast
    SPELL_ATTR10_USE_SPELL_BASE_LEVEL_FOR_SCALING = 0x00001000, // 12 Use Spell Base Level For Scaling
    SPELL_ATTR10_RESET_COOLDOWN_ON_ENCOUNTER_END  = 0x00002000, // 13 Reset cooldown upon ending an encounter
    SPELL_ATTR10_ROLLING_PERIODIC                 = 0x00004000, // 14 Rolling Periodic
    SPELL_ATTR10_SPELLBOOK_HIDDEN_UNTIL_OVERRIDEN = 0x00008000, // 15 Spellbook Hidden Until Overridden
    SPELL_ATTR10_DEFEND_AGAINST_FRIENDLY_CAST     = 0x00010000, // 16 Defend Against Friendly Cast
    SPELL_ATTR10_ALLOW_DEFENSE_WHILE_CASTING      = 0x00020000, // 17 Allow Defense While Casting
    SPELL_ATTR10_ALLOW_DEFENSE_WHILE_CHANNELING   = 0x00040000, // 18 Allow Defense While Channeling
    SPELL_ATTR10_ALLOW_FATAL_DUEL_DAMAGE          = 0x00080000, // 19 Allow Fatal Duel Damage
    SPELL_ATTR10_MULTI_CLICK_GROUND_TARGETING     = 0x00100000, // 20 Multi-Click Ground Targeting
    SPELL_ATTR10_AOE_CAN_HIT_SUMMONED_INVIS       = 0x00200000, // 21 AoE Can Hit Summoned Invis
    SPELL_ATTR10_ALLOW_WHILE_STUNNED_BY_HORROR    = 0x00400000, // 22 Allow While Stunned By Horror Mechanic
    SPELL_ATTR10_VISIBLE_ONLY_TO_CASTER           = 0x00800000, // 23 Visible only to caster (conversations only)
    SPELL_ATTR10_UPDATE_PASSIVES_ON_APPLY_REMOVE  = 0x01000000, // 24 Update Passives on Apply/Remove
    SPELL_ATTR10_NORMAL_MELEE_ATTACK              = 0x02000000, // 25 Normal Melee Attack
    SPELL_ATTR10_IGNORE_FEIGN_DEATH               = 0x04000000, // 26 Ignore Feign Death
    SPELL_ATTR10_CASTER_DEATH_CANCELS_PERSISTENT_AREA_AURAS = 0x08000000, // 27 Caster Death Cancels Persistent Area Auras
    SPELL_ATTR10_DO_NOT_LOG_ABSORB                = 0x10000000, // 28 Do Not Log Absorb
    SPELL_ATTR10_MOUNT_NOT_AT_ACCOUNT_LEVEL       = 0x20000000, // 29 This Mount is NOT at the account level
    SPELL_ATTR10_PREVENT_CLIENT_CAST_CANCEL       = 0x40000000, // 30 Prevent Client Cast Cancel
    SPELL_ATTR10_ENFORCE_FACTING_ON_PRIMARY_TARGET = 0x80000000  // 31 Enforce Facing on Primary Target Only
};

#define MIN_TALENT_SPEC         0
#define MAX_TALENT_SPEC         1
#define MIN_TALENT_SPECS        1
#define MAX_TALENT_SPECS        2
#define MAX_GLYPH_SLOT_INDEX    9
#define REQ_PRIMARY_TREE_TALENTS 31

// Custom values
enum SpellClickUserTypes
{
    SPELL_CLICK_USER_ANY = 0,
    SPELL_CLICK_USER_FRIEND = 1,
    SPELL_CLICK_USER_RAID = 2,
    SPELL_CLICK_USER_PARTY = 3,
    SPELL_CLICK_USER_MAX = 4
};

enum SpellClickCastFlags
{
    NPC_CLICK_CAST_CASTER_CLICKER       = 0x01,
    NPC_CLICK_CAST_TARGET_CLICKER       = 0x02,
    NPC_CLICK_CAST_ORIG_CASTER_OWNER    = 0x04
};

enum SheathTypes
{
    SHEATHETYPE_NONE                   = 0,
    SHEATHETYPE_MAINHAND               = 1,
    SHEATHETYPE_OFFHAND                = 2,
    SHEATHETYPE_LARGEWEAPONLEFT        = 3,
    SHEATHETYPE_LARGEWEAPONRIGHT       = 4,
    SHEATHETYPE_HIPWEAPONLEFT          = 5,
    SHEATHETYPE_HIPWEAPONRIGHT         = 6,
    SHEATHETYPE_SHIELD                 = 7
};

#define MAX_SHEATHETYPE                  8

enum CharacterFlags
{
    CHARACTER_FLAG_NONE                 = 0x00000000,
    CHARACTER_FLAG_UNK1                 = 0x00000001,
    CHARACTER_FLAG_UNK2                 = 0x00000002,
    CHARACTER_FLAG_LOCKED_FOR_TRANSFER  = 0x00000004,
    CHARACTER_FLAG_UNK4                 = 0x00000008,
    CHARACTER_FLAG_UNK5                 = 0x00000010,
    CHARACTER_FLAG_UNK6                 = 0x00000020,
    CHARACTER_FLAG_UNK7                 = 0x00000040,
    CHARACTER_FLAG_UNK8                 = 0x00000080,
    CHARACTER_FLAG_UNK9                 = 0x00000100,
    CHARACTER_FLAG_UNK10                = 0x00000200,
    CHARACTER_FLAG_HIDE_HELM            = 0x00000400,
    CHARACTER_FLAG_HIDE_CLOAK           = 0x00000800,
    CHARACTER_FLAG_UNK13                = 0x00001000,
    CHARACTER_FLAG_GHOST                = 0x00002000,
    CHARACTER_FLAG_RENAME               = 0x00004000,
    CHARACTER_FLAG_UNK16                = 0x00008000,
    CHARACTER_FLAG_UNK17                = 0x00010000,
    CHARACTER_FLAG_UNK18                = 0x00020000,
    CHARACTER_FLAG_UNK19                = 0x00040000,
    CHARACTER_FLAG_UNK20                = 0x00080000,
    CHARACTER_FLAG_UNK21                = 0x00100000,
    CHARACTER_FLAG_UNK22                = 0x00200000,
    CHARACTER_FLAG_UNK23                = 0x00400000,
    CHARACTER_FLAG_UNK24                = 0x00800000,
    CHARACTER_FLAG_LOCKED_BY_BILLING    = 0x01000000,
    CHARACTER_FLAG_DECLINED             = 0x02000000,
    CHARACTER_FLAG_UNK27                = 0x04000000,
    CHARACTER_FLAG_UNK28                = 0x08000000,
    CHARACTER_FLAG_UNK29                = 0x10000000,
    CHARACTER_FLAG_UNK30                = 0x20000000,
    CHARACTER_FLAG_UNK31                = 0x40000000,
    CHARACTER_FLAG_UNK32                = 0x80000000
};

enum CharacterCustomizeFlags
{
    CHAR_CUSTOMIZE_FLAG_NONE            = 0x00000000,
    CHAR_CUSTOMIZE_FLAG_CUSTOMIZE       = 0x00000001,       // name, gender, etc...
    CHAR_CUSTOMIZE_FLAG_FACTION         = 0x00010000,       // name, gender, faction, etc...
    CHAR_CUSTOMIZE_FLAG_RACE            = 0x00100000        // name, gender, race, etc...
};

enum CharacterSlot
{
    SLOT_HEAD                          = 0,
    SLOT_NECK                          = 1,
    SLOT_SHOULDERS                     = 2,
    SLOT_SHIRT                         = 3,
    SLOT_CHEST                         = 4,
    SLOT_WAIST                         = 5,
    SLOT_LEGS                          = 6,
    SLOT_FEET                          = 7,
    SLOT_WRISTS                        = 8,
    SLOT_HANDS                         = 9,
    SLOT_FINGER1                       = 10,
    SLOT_FINGER2                       = 11,
    SLOT_TRINKET1                      = 12,
    SLOT_TRINKET2                      = 13,
    SLOT_BACK                          = 14,
    SLOT_MAIN_HAND                     = 15,
    SLOT_OFF_HAND                      = 16,
    SLOT_RANGED                        = 17,
    SLOT_TABARD                        = 18,
    SLOT_EMPTY                         = 19
};

enum Language
{
    LANG_UNIVERSAL      = 0,
    LANG_ORCISH         = 1,
    LANG_DARNASSIAN     = 2,
    LANG_TAURAHE        = 3,
    LANG_DWARVISH       = 6,
    LANG_COMMON         = 7,
    LANG_DEMONIC        = 8,
    LANG_TITAN          = 9,
    LANG_THALASSIAN     = 10,
    LANG_DRACONIC       = 11,
    LANG_KALIMAG        = 12,
    LANG_GNOMISH        = 13,
    LANG_TROLL          = 14,
    LANG_GUTTERSPEAK    = 33,
    LANG_DRAENEI        = 35,
    LANG_ZOMBIE         = 36,
    LANG_GNOMISH_BINARY = 37,
    LANG_GOBLIN_BINARY  = 38,
    LANG_WORGEN         = 39,
    LANG_GOBLIN         = 40,
    LANG_ADDON          = 0xFFFFFFFF                        // used by addons, in 2.4.0 not exist, replaced by messagetype?
};

#define LANGUAGES_COUNT   21

enum TeamId : uint32
{
    TEAM_ALLIANCE = 0,
    TEAM_HORDE,
    TEAM_NEUTRAL
};

enum Team
{
    HORDE               = 67,
    ALLIANCE            = 469,
    //TEAM_STEAMWHEEDLE_CARTEL = 169,                       // not used in code
    //TEAM_ALLIANCE_FORCES     = 891,
    //TEAM_HORDE_FORCES        = 892,
    //TEAM_SANCTUARY           = 936,
    //TEAM_OUTLAND             = 980,
    TEAM_OTHER               = 0                            // if ReputationListId > 0 && Flags != FACTION_FLAG_TEAM_HEADER
};

enum SpellEffects : uint32
{
    SPELL_EFFECT_INSTAKILL                          = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE                      = 2,
    SPELL_EFFECT_DUMMY                              = 3,
    SPELL_EFFECT_PORTAL_TELEPORT                    = 4, // Unused (4.3.4)
    SPELL_EFFECT_TELEPORT_UNITS                     = 5,
    SPELL_EFFECT_APPLY_AURA                         = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE               = 7,
    SPELL_EFFECT_POWER_DRAIN                        = 8,
    SPELL_EFFECT_HEALTH_LEECH                       = 9,
    SPELL_EFFECT_HEAL                               = 10,
    SPELL_EFFECT_BIND                               = 11,
    SPELL_EFFECT_PORTAL                             = 12,
    SPELL_EFFECT_RITUAL_BASE                        = 13, // Unused (4.3.4)
    SPELL_EFFECT_RITUAL_SPECIALIZE                  = 14, // Unused (4.3.4)
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL             = 15, // Unused (4.3.4)
    SPELL_EFFECT_QUEST_COMPLETE                     = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL             = 17,
    SPELL_EFFECT_RESURRECT                          = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS                  = 19,
    SPELL_EFFECT_DODGE                              = 20,
    SPELL_EFFECT_EVADE                              = 21,
    SPELL_EFFECT_PARRY                              = 22,
    SPELL_EFFECT_BLOCK                              = 23,
    SPELL_EFFECT_CREATE_ITEM                        = 24,
    SPELL_EFFECT_WEAPON                             = 25,
    SPELL_EFFECT_DEFENSE                            = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA               = 27,
    SPELL_EFFECT_SUMMON                             = 28,
    SPELL_EFFECT_LEAP                               = 29,
    SPELL_EFFECT_ENERGIZE                           = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE              = 31,
    SPELL_EFFECT_TRIGGER_MISSILE                    = 32,
    SPELL_EFFECT_OPEN_LOCK                          = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM                 = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY              = 35,
    SPELL_EFFECT_LEARN_SPELL                        = 36,
    SPELL_EFFECT_SPELL_DEFENSE                      = 37,
    SPELL_EFFECT_DISPEL                             = 38,
    SPELL_EFFECT_LANGUAGE                           = 39,
    SPELL_EFFECT_DUAL_WIELD                         = 40,
    SPELL_EFFECT_JUMP                               = 41,
    SPELL_EFFECT_JUMP_DEST                          = 42,
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER         = 43,
    SPELL_EFFECT_SKILL_STEP                         = 44,
    SPELL_EFFECT_PLAY_MOVIE                         = 45,
    SPELL_EFFECT_SPAWN                              = 46,
    SPELL_EFFECT_TRADE_SKILL                        = 47,
    SPELL_EFFECT_STEALTH                            = 48,
    SPELL_EFFECT_DETECT                             = 49,
    SPELL_EFFECT_TRANS_DOOR                         = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT                 = 51, // Unused (4.3.4)
    SPELL_EFFECT_GUARANTEE_HIT                      = 52, // Unused (4.3.4)
    SPELL_EFFECT_ENCHANT_ITEM                       = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY             = 54,
    SPELL_EFFECT_TAMECREATURE                       = 55,
    SPELL_EFFECT_SUMMON_PET                         = 56,
    SPELL_EFFECT_LEARN_PET_SPELL                    = 57,
    SPELL_EFFECT_WEAPON_DAMAGE                      = 58,
    SPELL_EFFECT_CREATE_RANDOM_ITEM                 = 59,
    SPELL_EFFECT_PROFICIENCY                        = 60,
    SPELL_EFFECT_SEND_EVENT                         = 61,
    SPELL_EFFECT_POWER_BURN                         = 62,
    SPELL_EFFECT_THREAT                             = 63,
    SPELL_EFFECT_TRIGGER_SPELL                      = 64,
    SPELL_EFFECT_APPLY_AREA_AURA_RAID               = 65,
    SPELL_EFFECT_CREATE_MANA_GEM                    = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH                    = 67,
    SPELL_EFFECT_INTERRUPT_CAST                     = 68,
    SPELL_EFFECT_DISTRACT                           = 69,
    SPELL_EFFECT_PULL                               = 70,
    SPELL_EFFECT_PICKPOCKET                         = 71,
    SPELL_EFFECT_ADD_FARSIGHT                       = 72,
    SPELL_EFFECT_UNTRAIN_TALENTS                    = 73,
    SPELL_EFFECT_APPLY_GLYPH                        = 74,
    SPELL_EFFECT_HEAL_MECHANICAL                    = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD                 = 76,
    SPELL_EFFECT_SCRIPT_EFFECT                      = 77,
    SPELL_EFFECT_ATTACK                             = 78,
    SPELL_EFFECT_SANCTUARY                          = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS                   = 80,
    SPELL_EFFECT_CREATE_HOUSE                       = 81,
    SPELL_EFFECT_BIND_SIGHT                         = 82,
    SPELL_EFFECT_DUEL                               = 83,
    SPELL_EFFECT_STUCK                              = 84,
    SPELL_EFFECT_SUMMON_PLAYER                      = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT                    = 86,
    SPELL_EFFECT_GAMEOBJECT_DAMAGE                  = 87,
    SPELL_EFFECT_GAMEOBJECT_REPAIR                  = 88,
    SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE   = 89,
    SPELL_EFFECT_KILL_CREDIT                        = 90,
    SPELL_EFFECT_THREAT_ALL                         = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM                  = 92,
    SPELL_EFFECT_FORCE_DESELECT                     = 93,
    SPELL_EFFECT_SELF_RESURRECT                     = 94,
    SPELL_EFFECT_SKINNING                           = 95,
    SPELL_EFFECT_CHARGE                             = 96,
    SPELL_EFFECT_CAST_BUTTON                        = 97,
    SPELL_EFFECT_KNOCK_BACK                         = 98,
    SPELL_EFFECT_DISENCHANT                         = 99,
    SPELL_EFFECT_INEBRIATE                          = 100,
    SPELL_EFFECT_FEED_PET                           = 101,
    SPELL_EFFECT_DISMISS_PET                        = 102,
    SPELL_EFFECT_REPUTATION                         = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1                = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2                = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3                = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4                = 107,
    SPELL_EFFECT_DISPEL_MECHANIC                    = 108,
    SPELL_EFFECT_RESURRECT_PET                      = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS                 = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE                  = 111,
    SPELL_EFFECT_112                                = 112,
    SPELL_EFFECT_RESURRECT_NEW                      = 113,
    SPELL_EFFECT_ATTACK_ME                          = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT              = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE                 = 116,
    SPELL_EFFECT_SPIRIT_HEAL                        = 117,
    SPELL_EFFECT_SKILL                              = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET                = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD                 = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG              = 121,
    SPELL_EFFECT_122                                = 122, // Unused (4.3.4)
    SPELL_EFFECT_SEND_TAXI                          = 123,
    SPELL_EFFECT_PULL_TOWARDS                       = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT              = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF              = 126,
    SPELL_EFFECT_PROSPECTING                        = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND             = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY              = 129,
    SPELL_EFFECT_REDIRECT_THREAT                    = 130,
    SPELL_EFFECT_PLAY_SOUND                         = 131,
    SPELL_EFFECT_PLAY_MUSIC                         = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION             = 133,
    SPELL_EFFECT_KILL_CREDIT2                       = 134,
    SPELL_EFFECT_CALL_PET                           = 135,
    SPELL_EFFECT_HEAL_PCT                           = 136,
    SPELL_EFFECT_ENERGIZE_PCT                       = 137,
    SPELL_EFFECT_LEAP_BACK                          = 138,
    SPELL_EFFECT_CLEAR_QUEST                        = 139,
    SPELL_EFFECT_FORCE_CAST                         = 140,
    SPELL_EFFECT_FORCE_CAST_WITH_VALUE              = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE           = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER              = 143,
    SPELL_EFFECT_KNOCK_BACK_DEST                    = 144,
    SPELL_EFFECT_PULL_TOWARDS_DEST                  = 145,
    SPELL_EFFECT_ACTIVATE_RUNE                      = 146,
    SPELL_EFFECT_QUEST_FAIL                         = 147,
    SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE   = 148,
    SPELL_EFFECT_CHARGE_DEST                        = 149,
    SPELL_EFFECT_QUEST_START                        = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2                    = 151,
    SPELL_EFFECT_SUMMON_RAF_FRIEND                  = 152,
    SPELL_EFFECT_CREATE_TAMED_PET                   = 153,
    SPELL_EFFECT_DISCOVER_TAXI                      = 154,
    SPELL_EFFECT_TITAN_GRIP                         = 155,
    SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC             = 156,
    SPELL_EFFECT_CREATE_ITEM_2                      = 157,
    SPELL_EFFECT_MILLING                            = 158,
    SPELL_EFFECT_ALLOW_RENAME_PET                   = 159,
    SPELL_EFFECT_FORCE_CAST_2                       = 160,
    SPELL_EFFECT_TALENT_SPEC_COUNT                  = 161,
    SPELL_EFFECT_TALENT_SPEC_SELECT                 = 162,
    SPELL_EFFECT_163                                = 163, // Unused (4.3.4)
    SPELL_EFFECT_REMOVE_AURA                        = 164,
    SPELL_EFFECT_DAMAGE_FROM_MAX_HEALTH_PCT         = 165,
    SPELL_EFFECT_GIVE_CURRENCY                      = 166,
    SPELL_EFFECT_UPDATE_PLAYER_PHASE                = 167,
    SPELL_EFFECT_ALLOW_CONTROL_PET                  = 168,
    SPELL_EFFECT_DESTROY_ITEM                       = 169,
    SPELL_EFFECT_UPDATE_ZONE_AURAS_AND_PHASES       = 170,
    SPELL_EFFECT_SUMMON_PERSONAL_GAMEOBJECT         = 171, // Summons gamebject
    SPELL_EFFECT_RESURRECT_WITH_AURA                = 172,
    SPELL_EFFECT_UNLOCK_GUILD_VAULT_TAB             = 173, // Guild tab unlocked (guild perk)
    SPELL_EFFECT_APPLY_AURA_2                       = 174,
    SPELL_EFFECT_175                                = 175, // Unused (4.3.4)
    SPELL_EFFECT_SANCTUARY_2                        = 176, // Some kind of sanctuary effect (Vanish)
    SPELL_EFFECT_177                                = 177,
    SPELL_EFFECT_178                                = 178, // Unused (4.3.4)
    SPELL_EFFECT_CREATE_AREATRIGGER                 = 179,
    SPELL_EFFECT_UPDATE_AREATRIGGER                 = 180, // Unused (4.3.4)
    SPELL_EFFECT_REMOVE_TALENT                      = 181, // Unused (4.3.4)
    SPELL_EFFECT_182                                = 182,
    TOTAL_SPELL_EFFECTS                             = 183,
};

enum SpellCastResult
{
    SPELL_FAILED_SUCCESS                        = 0,
    SPELL_FAILED_AFFECTING_COMBAT               = 1,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH         = 2,
    SPELL_FAILED_ALREADY_AT_FULL_MANA           = 3,
    SPELL_FAILED_ALREADY_AT_FULL_POWER          = 4,
    SPELL_FAILED_ALREADY_BEING_TAMED            = 5,
    SPELL_FAILED_ALREADY_HAVE_CHARM             = 6,
    SPELL_FAILED_ALREADY_HAVE_SUMMON            = 7,
    SPELL_FAILED_ALREADY_HAVE_PET               = 8,
    SPELL_FAILED_ALREADY_OPEN                   = 9,
    SPELL_FAILED_AURA_BOUNCED                   = 10,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED          = 11,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS           = 12,
    SPELL_FAILED_BAD_TARGETS                    = 13,
    SPELL_FAILED_CANT_BE_CHARMED                = 14,
    SPELL_FAILED_CANT_BE_DISENCHANTED           = 15,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL     = 16,
    SPELL_FAILED_CANT_BE_MILLED                 = 17,
    SPELL_FAILED_CANT_BE_PROSPECTED             = 18,
    SPELL_FAILED_CANT_CAST_ON_TAPPED            = 19,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE      = 20,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED      = 21,
    SPELL_FAILED_CANT_STEALTH                   = 22,
    SPELL_FAILED_CASTER_AURASTATE               = 23,
    SPELL_FAILED_CASTER_DEAD                    = 24,
    SPELL_FAILED_CHARMED                        = 25,
    SPELL_FAILED_CHEST_IN_USE                   = 26,
    SPELL_FAILED_CONFUSED                       = 27,
    SPELL_FAILED_DONT_REPORT                    = 28,
    SPELL_FAILED_EQUIPPED_ITEM                  = 29,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS            = 30,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND   = 31,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND    = 32,
    SPELL_FAILED_ERROR                          = 33,
    SPELL_FAILED_FALLING                        = 34,
    SPELL_FAILED_FIZZLE                         = 35,
    SPELL_FAILED_FLEEING                        = 36,
    SPELL_FAILED_FOOD_LOWLEVEL                  = 37,
    SPELL_FAILED_HIGHLEVEL                      = 38,
    SPELL_FAILED_HUNGER_SATIATED                = 39,
    SPELL_FAILED_IMMUNE                         = 40,
    SPELL_FAILED_INCORRECT_AREA                 = 41,
    SPELL_FAILED_INTERRUPTED                    = 42,
    SPELL_FAILED_INTERRUPTED_COMBAT             = 43,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED         = 44,
    SPELL_FAILED_ITEM_GONE                      = 45,
    SPELL_FAILED_ITEM_NOT_FOUND                 = 46,
    SPELL_FAILED_ITEM_NOT_READY                 = 47,
    SPELL_FAILED_LEVEL_REQUIREMENT              = 48,
    SPELL_FAILED_LINE_OF_SIGHT                  = 49,
    SPELL_FAILED_LOWLEVEL                       = 50,
    SPELL_FAILED_LOW_CASTLEVEL                  = 51,
    SPELL_FAILED_MAINHAND_EMPTY                 = 52,
    SPELL_FAILED_MOVING                         = 53,
    SPELL_FAILED_NEED_AMMO                      = 54,
    SPELL_FAILED_NEED_AMMO_POUCH                = 55,
    SPELL_FAILED_NEED_EXOTIC_AMMO               = 56,
    SPELL_FAILED_NEED_MORE_ITEMS                = 57,
    SPELL_FAILED_NOPATH                         = 58,
    SPELL_FAILED_NOT_BEHIND                     = 59,
    SPELL_FAILED_NOT_FISHABLE                   = 60,
    SPELL_FAILED_NOT_FLYING                     = 61,
    SPELL_FAILED_NOT_HERE                       = 62,
    SPELL_FAILED_NOT_INFRONT                    = 63,
    SPELL_FAILED_NOT_IN_CONTROL                 = 64,
    SPELL_FAILED_NOT_KNOWN                      = 65,
    SPELL_FAILED_NOT_MOUNTED                    = 66,
    SPELL_FAILED_NOT_ON_TAXI                    = 67,
    SPELL_FAILED_NOT_ON_TRANSPORT               = 68,
    SPELL_FAILED_NOT_READY                      = 69,
    SPELL_FAILED_NOT_SHAPESHIFT                 = 70,
    SPELL_FAILED_NOT_STANDING                   = 71,
    SPELL_FAILED_NOT_TRADEABLE                  = 72,
    SPELL_FAILED_NOT_TRADING                    = 73,
    SPELL_FAILED_NOT_UNSHEATHED                 = 74,
    SPELL_FAILED_NOT_WHILE_GHOST                = 75,
    SPELL_FAILED_NOT_WHILE_LOOTING              = 76,
    SPELL_FAILED_NO_AMMO                        = 77,
    SPELL_FAILED_NO_CHARGES_REMAIN              = 78,
    SPELL_FAILED_NO_CHAMPION                    = 79,
    SPELL_FAILED_NO_COMBO_POINTS                = 80,
    SPELL_FAILED_NO_DUELING                     = 81,
    SPELL_FAILED_NO_ENDURANCE                   = 82,
    SPELL_FAILED_NO_FISH                        = 83,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED    = 84,
    SPELL_FAILED_NO_MOUNTS_ALLOWED              = 85,
    SPELL_FAILED_NO_PET                         = 86,
    SPELL_FAILED_NO_POWER                       = 87,
    SPELL_FAILED_NOTHING_TO_DISPEL              = 88,
    SPELL_FAILED_NOTHING_TO_STEAL               = 89,
    SPELL_FAILED_ONLY_ABOVEWATER                = 90,
    SPELL_FAILED_ONLY_DAYTIME                   = 91,
    SPELL_FAILED_ONLY_INDOORS                   = 92,
    SPELL_FAILED_ONLY_MOUNTED                   = 93,
    SPELL_FAILED_ONLY_NIGHTTIME                 = 94,
    SPELL_FAILED_ONLY_OUTDOORS                  = 95,
    SPELL_FAILED_ONLY_SHAPESHIFT                = 96,
    SPELL_FAILED_ONLY_STEALTHED                 = 97,
    SPELL_FAILED_ONLY_UNDERWATER                = 98,
    SPELL_FAILED_OUT_OF_RANGE                   = 99,
    SPELL_FAILED_PACIFIED                       = 100,
    SPELL_FAILED_POSSESSED                      = 101,
    SPELL_FAILED_REAGENTS                       = 102,
    SPELL_FAILED_REQUIRES_AREA                  = 103,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS           = 104,
    SPELL_FAILED_ROOTED                         = 105,
    SPELL_FAILED_SILENCED                       = 106,
    SPELL_FAILED_SPELL_IN_PROGRESS              = 107,
    SPELL_FAILED_SPELL_LEARNED                  = 108,
    SPELL_FAILED_SPELL_UNAVAILABLE              = 109,
    SPELL_FAILED_STUNNED                        = 110,
    SPELL_FAILED_TARGETS_DEAD                   = 111,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT        = 112,
    SPELL_FAILED_TARGET_AURASTATE               = 113,
    SPELL_FAILED_TARGET_DUELING                 = 114,
    SPELL_FAILED_TARGET_ENEMY                   = 115,
    SPELL_FAILED_TARGET_ENRAGED                 = 116,
    SPELL_FAILED_TARGET_FRIENDLY                = 117,
    SPELL_FAILED_TARGET_IN_COMBAT               = 118,
    SPELL_FAILED_TARGET_IS_PLAYER               = 119,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED    = 120,
    SPELL_FAILED_TARGET_NOT_DEAD                = 121,
    SPELL_FAILED_TARGET_NOT_IN_PARTY            = 122,
    SPELL_FAILED_TARGET_NOT_LOOTED              = 123,
    SPELL_FAILED_TARGET_NOT_PLAYER              = 124,
    SPELL_FAILED_TARGET_NO_POCKETS              = 125,
    SPELL_FAILED_TARGET_NO_WEAPONS              = 126,
    SPELL_FAILED_TARGET_NO_RANGED_WEAPONS       = 127,
    SPELL_FAILED_TARGET_UNSKINNABLE             = 128,
    SPELL_FAILED_THIRST_SATIATED                = 129,
    SPELL_FAILED_TOO_CLOSE                      = 130,
    SPELL_FAILED_TOO_MANY_OF_ITEM               = 131,
    SPELL_FAILED_TOTEM_CATEGORY                 = 132,
    SPELL_FAILED_TOTEMS                         = 133,
    SPELL_FAILED_TRY_AGAIN                      = 134,
    SPELL_FAILED_UNIT_NOT_BEHIND                = 135,
    SPELL_FAILED_UNIT_NOT_INFRONT               = 136,
    SPELL_FAILED_VISION_OBSCURED                = 137,
    SPELL_FAILED_WRONG_PET_FOOD                 = 138,
    SPELL_FAILED_NOT_WHILE_FATIGUED             = 139,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE         = 140,
    SPELL_FAILED_NOT_WHILE_TRADING              = 141,
    SPELL_FAILED_TARGET_NOT_IN_RAID             = 142,
    SPELL_FAILED_TARGET_FREEFORALL              = 143,
    SPELL_FAILED_NO_EDIBLE_CORPSES              = 144,
    SPELL_FAILED_ONLY_BATTLEGROUNDS             = 145,
    SPELL_FAILED_TARGET_NOT_GHOST               = 146,
    SPELL_FAILED_TRANSFORM_UNUSABLE             = 147,
    SPELL_FAILED_WRONG_WEATHER                  = 148,
    SPELL_FAILED_DAMAGE_IMMUNE                  = 149,
    SPELL_FAILED_PREVENTED_BY_MECHANIC          = 150,
    SPELL_FAILED_PLAY_TIME                      = 151,
    SPELL_FAILED_REPUTATION                     = 152,
    SPELL_FAILED_MIN_SKILL                      = 153,
    SPELL_FAILED_NOT_IN_RATED_BATTLEGROUND      = 154,
    SPELL_FAILED_NOT_ON_SHAPESHIFT              = 155,
    SPELL_FAILED_NOT_ON_STEALTHED               = 156,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE           = 157,
    SPELL_FAILED_NOT_ON_MOUNTED                 = 158,
    SPELL_FAILED_TOO_SHALLOW                    = 159,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY        = 160,
    SPELL_FAILED_TARGET_IS_TRIVIAL              = 161,
    SPELL_FAILED_BM_OR_INVISGOD                 = 162,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT      = 163,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT     = 164,
    SPELL_FAILED_NOT_IDLE                       = 165,
    SPELL_FAILED_NOT_INACTIVE                   = 166,
    SPELL_FAILED_PARTIAL_PLAYTIME               = 167,
    SPELL_FAILED_NO_PLAYTIME                    = 168,
    SPELL_FAILED_NOT_IN_BATTLEGROUND            = 169,
    SPELL_FAILED_NOT_IN_RAID_INSTANCE           = 170,
    SPELL_FAILED_ONLY_IN_ARENA                  = 171,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 172,
    SPELL_FAILED_ON_USE_ENCHANT                 = 173,
    SPELL_FAILED_NOT_ON_GROUND                  = 174,
    SPELL_FAILED_CUSTOM_ERROR                   = 175,
    SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW         = 176,
    SPELL_FAILED_TOO_MANY_SOCKETS               = 177,
    SPELL_FAILED_INVALID_GLYPH                  = 178,
    SPELL_FAILED_UNIQUE_GLYPH                   = 179,
    SPELL_FAILED_GLYPH_SOCKET_LOCKED            = 180,
    SPELL_FAILED_NO_VALID_TARGETS               = 181,
    SPELL_FAILED_ITEM_AT_MAX_CHARGES            = 182,
    SPELL_FAILED_NOT_IN_BARBERSHOP              = 183,
    SPELL_FAILED_FISHING_TOO_LOW                = 184,
    SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW      = 185,
    SPELL_FAILED_SUMMON_PENDING                 = 186,
    SPELL_FAILED_MAX_SOCKETS                    = 187,
    SPELL_FAILED_PET_CAN_RENAME                 = 188,
    SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED   = 189,
    SPELL_FAILED_NO_ACTIONS                     = 190,
    SPELL_FAILED_CURRENCY_WEIGHT_MISMATCH       = 191,
    SPELL_FAILED_WEIGHT_NOT_ENOUGH              = 192,
    SPELL_FAILED_WEIGHT_TOO_MUCH                = 193,
    SPELL_FAILED_NO_VACANT_SEAT                 = 194,
    SPELL_FAILED_NO_LIQUID                      = 195,
    SPELL_FAILED_ONLY_NOT_SWIMMING              = 196,
    SPELL_FAILED_BY_NOT_MOVING                  = 197,
    SPELL_FAILED_IN_COMBAT_RES_LIMIT_REACHED    = 198,
    SPELL_FAILED_NOT_IN_ARENA                   = 199,
    SPELL_FAILED_TARGET_NOT_GROUNDED            = 200,
    SPELL_FAILED_EXCEEDED_WEEKLY_USAGE          = 201,
    SPELL_FAILED_NOT_IN_LFG_DUNGEON             = 202,
    SPELL_FAILED_UNKNOWN                        = 254, // custom value, default case
    SPELL_CAST_OK                               = 255, // custom value, must not be sent to client
};

enum SpellCustomErrors
{
    SPELL_CUSTOM_ERROR_NONE                             =  0,
    SPELL_CUSTOM_ERROR_CUSTOM_MSG                       =  1, // Something bad happened, and we want to display a custom message!
    SPELL_CUSTOM_ERROR_ALEX_BROKE_QUEST                 =  2, // Alex broke your quest! Thank him later!
    SPELL_CUSTOM_ERROR_NEED_HELPLESS_VILLAGER           =  3, // This spell may only be used on Helpless Wintergarde Villagers that have not been rescued.
    SPELL_CUSTOM_ERROR_NEED_WARSONG_DISGUISE            =  4, // Requires that you be wearing the Warsong Orc Disguise.
    SPELL_CUSTOM_ERROR_REQUIRES_PLAGUE_WAGON            =  5, // You must be closer to a plague wagon in order to drop off your 7th Legion Siege Engineer.
    SPELL_CUSTOM_ERROR_CANT_TARGET_FRIENDLY_NONPARTY    =  6, // You cannot target friendly units outside your party.
    SPELL_CUSTOM_ERROR_NEED_CHILL_NYMPH                 =  7, // You must target a weakened chill nymph.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_ENKILAH               =  8, // The Imbued Scourge Shroud will only work when equipped in the Temple City of En'kilah.
    SPELL_CUSTOM_ERROR_REQUIRES_CORPSE_DUST             =  9, // Requires Corpse Dust
    SPELL_CUSTOM_ERROR_CANT_SUMMON_GARGOYLE             = 10, // You cannot summon another gargoyle yet.
    SPELL_CUSTOM_ERROR_NEED_CORPSE_DUST_IF_NO_TARGET    = 11, // Requires Corpse Dust if the target is not dead and humanoid.
    SPELL_CUSTOM_ERROR_MUST_BE_AT_SHATTERHORN           = 12, // Can only be placed near Shatterhorn
    SPELL_CUSTOM_ERROR_MUST_TARGET_PROTO_DRAKE_EGG      = 13, // You must first select a Proto-Drake Egg.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_TREE            = 14, // You must be close to a marked tree.
    SPELL_CUSTOM_ERROR_MUST_TARGET_TURKEY               = 15, // You must target a Fjord Turkey.
    SPELL_CUSTOM_ERROR_MUST_TARGET_HAWK                 = 16, // You must target a Fjord Hawk.
    SPELL_CUSTOM_ERROR_TOO_FAR_FROM_BOUY                = 17, // You are too far from the bouy.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_OIL_SLICK       = 18, // Must be used near an oil slick.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_BOUY            = 19, // You must be closer to the buoy!
    SPELL_CUSTOM_ERROR_WYRMREST_VANQUISHER              = 20, // You may only call for the aid of a Wyrmrest Vanquisher in Wyrmrest Temple, The Dragon Wastes, Galakrond's Rest or The Wicked Coil.
    SPELL_CUSTOM_ERROR_MUST_TARGET_ICE_HEART_JORMUNGAR  = 21, // That can only be used on a Ice Heart Jormungar Spawn.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_SINKHOLE        = 22, // You must be closer to a sinkhole to use your map.
    SPELL_CUSTOM_ERROR_REQUIRES_HAROLD_LANE             = 23, // You may only call down a stampede on Harold Lane.
    SPELL_CUSTOM_ERROR_REQUIRES_GAMMOTH_MAGNATAUR       = 24, // You may only use the Pouch of Crushed Bloodspore on Gammothra or other magnataur in the Bloodspore Plains and Gammoth.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_RESURRECTION_CHAMBER  = 25, // Requires the magmawyrm resurrection chamber in the back of the Maw of Neltharion.
    SPELL_CUSTOM_ERROR_CANT_CALL_WINTERGARDE_HERE       = 26, // You may only call down a Wintergarde Gryphon in Wintergarde Keep or the Carrion Fields.
    SPELL_CUSTOM_ERROR_MUST_TARGET_WILHELM              = 27, // What are you doing? Only aim that thing at Wilhelm!
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH                = 28, // Not enough health!
    SPELL_CUSTOM_ERROR_NO_NEARBY_CORPSES                = 29, // There are no nearby corpses to use
    SPELL_CUSTOM_ERROR_TOO_MANY_GHOULS                  = 30, // You've created enough ghouls. Return to Gothik the Harvester at Death's Breach.
    SPELL_CUSTOM_ERROR_GO_FURTHER_FROM_SUNDERED_SHARD   = 31, // Your companion does not want to come here.  Go further from the Sundered Shard.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_CAT_FORM              = 32, // Must be in Cat Form
    SPELL_CUSTOM_ERROR_MUST_BE_DEATH_KNIGHT             = 33, // Only Death Knights may enter Ebon Hold.
    SPELL_CUSTOM_ERROR_MUST_BE_IN_FERAL_FORM            = 34, // Must be in Cat Form, Bear Form, or Dire Bear Form
    SPELL_CUSTOM_ERROR_MUST_BE_NEAR_HELPLESS_VILLAGER   = 35, // You must be within range of a Helpless Wintergarde Villager.
    SPELL_CUSTOM_ERROR_CANT_TARGET_ELEMENTAL_MECHANICAL = 36, // You cannot target an elemental or mechanical corpse.
    SPELL_CUSTOM_ERROR_MUST_HAVE_USED_DALARAN_CRYSTAL   = 37, // This teleport crystal cannot be used until the teleport crystal in Dalaran has been used at least once.
    SPELL_CUSTOM_ERROR_YOU_ALREADY_HOLD_SOMETHING       = 38, // You are already holding something in your hand. You must throw the creature in your hand before picking up another.
    SPELL_CUSTOM_ERROR_YOU_DONT_HOLD_ANYTHING           = 39, // You don't have anything to throw! Find a Vargul and use Gymer Grab to pick one up!
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_VALDURAN        = 40, // Bouldercrag's War Horn can only be used within 10 yards of Valduran the Stormborn.
    SPELL_CUSTOM_ERROR_NO_PASSENGER                     = 41, // You are not carrying a passenger. There is nobody to drop off.
    SPELL_CUSTOM_ERROR_CANT_BUILD_MORE_VEHICLES         = 42, // You cannot build any more siege vehicles.
    SPELL_CUSTOM_ERROR_ALREADY_CARRYING_CRUSADER        = 43, // You are already carrying a captured Argent Crusader. You must return to the Argent Vanguard infirmary and drop off your passenger before you may pick up another.
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_ROOTED             = 44, // You can't do that while rooted.
    SPELL_CUSTOM_ERROR_REQUIRES_NEARBY_TARGET           = 45, // Requires a nearby target.
    SPELL_CUSTOM_ERROR_NOTHING_TO_DISCOVER              = 46, // Nothing left to discover.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_TARGETS               = 47, // No targets close enough to bluff.
    SPELL_CUSTOM_ERROR_CONSTRUCT_TOO_FAR                = 48, // Your Iron Rune Construct is out of range.
    SPELL_CUSTOM_ERROR_REQUIRES_GRAND_MASTER_ENGINEER   = 49, // Requires Grand Master Engineer
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_MOUNT              = 50, // You can't use that mount.
    SPELL_CUSTOM_ERROR_NOONE_TO_EJECT                   = 51, // There is nobody to eject!
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_BOUND             = 52, // The target must be bound to you.
    SPELL_CUSTOM_ERROR_TARGET_MUST_BE_UNDEAD            = 53, // Target must be undead.
    SPELL_CUSTOM_ERROR_TARGET_TOO_FAR                   = 54, // You have no target or your target is too far away.
    SPELL_CUSTOM_ERROR_MISSING_DARK_MATTER              = 55, // Missing Reagents: Dark Matter
    SPELL_CUSTOM_ERROR_CANT_USE_THAT_ITEM               = 56, // You can't use that item
    SPELL_CUSTOM_ERROR_CANT_DO_WHILE_CYCYLONED          = 57, // You can't do that while Cycloned
    SPELL_CUSTOM_ERROR_TARGET_HAS_SCROLL                = 58, // Target is already affected by a scroll
    SPELL_CUSTOM_ERROR_POISON_TOO_STRONG                = 59, // That anti-venom is not strong enough to dispel that poison
    SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED         = 60, // You must have a lance equipped.
    SPELL_CUSTOM_ERROR_MUST_BE_CLOSE_TO_MAIDEN          = 61, // You must be near the Maiden of Winter's Breath Lake.
    SPELL_CUSTOM_ERROR_LEARNED_EVERYTHING               = 62, // You have learned everything from that book
    SPELL_CUSTOM_ERROR_PET_IS_DEAD                      = 63, // Your pet is dead
    SPELL_CUSTOM_ERROR_NO_VALID_TARGETS                 = 64, // There are no valid targets within range.
    SPELL_CUSTOM_ERROR_GM_ONLY                          = 65, // Only GMs may use that. Your account has been reported for investigation.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_58                = 66, // You must reach level 58 to use this portal.
    SPELL_CUSTOM_ERROR_AT_HONOR_CAP                     = 67, // You already have the maximum amount of honor.
    SPELL_CUSTOM_ERROR_HAVE_HOT_ROD                     = 68, // You already have a Hot Rod.
    SPELL_CUSTOM_ERROR_PARTYGOER_MORE_BUBBLY            = 69, // This partygoer wants some more bubbly
    SPELL_CUSTOM_ERROR_PARTYGOER_NEED_BUCKET            = 70, // This partygoer needs a bucket!
    SPELL_CUSTOM_ERROR_PARTYGOER_WANT_TO_DANCE          = 71, // This partygoer wants to dance with you.
    SPELL_CUSTOM_ERROR_PARTYGOER_WANT_FIREWORKS         = 72, // This partygoer wants to see some fireworks.
    SPELL_CUSTOM_ERROR_PARTYGOER_WANT_APPETIZER         = 73, // This partygoer wants some more hors d'oeuvres.
    SPELL_CUSTOM_ERROR_GOBLIN_BATTERY_DEPLETED          = 74, // The Goblin All-In-1-Der Belt's battery is depleted.
    SPELL_CUSTOM_ERROR_MUST_HAVE_DEMONIC_CIRCLE         = 75, // You must have a demonic circle active.
    SPELL_CUSTOM_ERROR_AT_MAX_RAGE                      = 76, // You already have maximum rage
    SPELL_CUSTOM_ERROR_REQUIRES_350_ENGINEERING         = 77, // Requires Engineering (350)
    SPELL_CUSTOM_ERROR_SOUL_BELONGS_TO_LICH_KING        = 78, // Your soul belongs to the Lich King
    SPELL_CUSTOM_ERROR_ATTENDANT_HAS_PONY               = 79, // Your attendant already has an Argent Pony
    SPELL_CUSTOM_ERROR_GOBLIN_STARTING_MISSION          = 80, // First, Overload the Defective Generator, Activate the Leaky Stove, and Drop a Cigar on the Flammable Bed.
    SPELL_CUSTOM_ERROR_GASBOT_ALREADY_SENT              = 81, // You've already sent in the Gasbot and destroyed headquarters!
    SPELL_CUSTOM_ERROR_GOBLIN_IS_PARTIED_OUT            = 82, // This goblin is all partied out!
    SPELL_CUSTOM_ERROR_MUST_HAVE_FIRE_TOTEM             = 83, // You must have a Fire Totem active.
    SPELL_CUSTOM_ERROR_CANT_TARGET_VAMPIRES             = 84, // You may not bite other vampires.
    SPELL_CUSTOM_ERROR_PET_ALREADY_AT_YOUR_LEVEL        = 85, // Your pet is already at your level.
    SPELL_CUSTOM_ERROR_MISSING_ITEM_REQUIREMENS         = 86, // You do not meet the level requirements for this item.
    SPELL_CUSTOM_ERROR_TOO_MANY_ABOMINATIONS            = 87, // There are too many Mutated Abominations.
    SPELL_CUSTOM_ERROR_ALL_POTIONS_USED                 = 88, // The potions have all been depleted by Professor Putricide.
    SPELL_CUSTOM_ERROR_DEFEATED_ENOUGH_ALREADY          = 89, // You have already defeated enough of them.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_65                = 90, // Requires level 65
    SPELL_CUSTOM_ERROR_DESTROYED_KTC_OIL_PLATFORM       = 91, // You have already destroyed the KTC Oil Platform.
    SPELL_CUSTOM_ERROR_LAUNCHED_ENOUGH_CAGES            = 92, // You have already launched enough cages.
    SPELL_CUSTOM_ERROR_REQUIRES_BOOSTER_ROCKETS         = 93, // Requires Single-Stage Booster Rockets. Return to Hobart Grapplehammer to get more.
    SPELL_CUSTOM_ERROR_ENOUGH_WILD_CLUCKERS             = 94, // You have already captured enough wild cluckers.
    SPELL_CUSTOM_ERROR_REQUIRES_CONTROL_FIREWORKS       = 95, // Requires Remote Control Fireworks. Return to Hobart Grapplehammer to get more.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_RECRUITS           = 96, // You already have the max number of recruits.
    SPELL_CUSTOM_ERROR_MAX_NUMBER_OF_VOLUNTEERS         = 97, // You already have the max number of volunteers.
    SPELL_CUSTOM_ERROR_FROSTMOURNE_RENDERED_RESURRECT   = 98, // Frostmourne has rendered you unable to resurrect.
    SPELL_CUSTOM_ERROR_CANT_MOUNT_WITH_SHAPESHIFT       = 99, // You can't mount while affected by that shapeshift.
    SPELL_CUSTOM_ERROR_FAWNS_ALREADY_FOLLOWING          = 100, // Three fawns are already following you!
    SPELL_CUSTOM_ERROR_ALREADY_HAVE_RIVER_BOAT          = 101, // You already have a River Boat.
    SPELL_CUSTOM_ERROR_NO_ACTIVE_ENCHANTMENT            = 102, // You have no active enchantment to unleash.
    SPELL_CUSTOM_ERROR_ENOUGH_HIGHBOURNE_SOULS          = 103, // You have bound enough Highborne souls. Return to Arcanist Valdurian.
    SPELL_CUSTOM_ERROR_ATLEAST_40YD_FROM_OIL_DRILLING   = 104, // You must be at least 40 yards away from all other Oil Drilling Rigs.
    SPELL_CUSTOM_ERROR_ABOVE_ENSLAVED_PEARL_MINER       = 106, // You must be above the Enslaved Pearl Miner.
    SPELL_CUSTOM_ERROR_MUST_TARGET_CORPSE_SPECIAL_1     = 107, // You must target the corpse of a Seabrush Terrapin, Scourgut Remora, or Spinescale Hammerhead.
    SPELL_CUSTOM_ERROR_SLAGHAMMER_ALREADY_PRISONER      = 108, // Ambassador Slaghammer is already your prisoner.
    SPELL_CUSTOM_ERROR_REQUIRE_ATTUNED_LOCATION_1       = 109, // Requires a location that is attuned with the Naz'jar Battlemaiden.
    SPELL_CUSTOM_ERROR_NEED_TO_FREE_DRAKE_FIRST         = 110, // Free the Drake from the net first!
    SPELL_CUSTOM_ERROR_DRAGONMAW_ALLIES_ALREADY_FOLLOW  = 111, // You already have three Dragonmaw allies following you.
    SPELL_CUSTOM_ERROR_REQUIRE_OPPOSABLE_THUMBS         = 112, // Requires Opposable Thumbs.
    SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH_2              = 113, // Not enough health
    SPELL_CUSTOM_ERROR_ENOUGH_FORSAKEN_TROOPERS         = 114, // You already have enough Forsaken Troopers.
    SPELL_CUSTOM_ERROR_CANNOT_JUMP_TO_BOULDER           = 115, // You cannot jump to another boulder yet.
    SPELL_CUSTOM_ERROR_SKILL_TOO_HIGH                   = 116, // Skill too high.
    SPELL_CUSTOM_ERROR_ALREADY_6_SURVIVORS_RESCUED      = 117, // You have already rescued 6 Survivors.
    SPELL_CUSTOM_ERROR_MUST_FACE_SHIPS_FROM_BALLOON     = 118, // You need to be facing the ships from the rescue balloon.
    SPELL_CUSTOM_ERROR_CANNOT_SUPERVISE_MORE_CULTISTS   = 119, // You cannot supervise more than 5 Arrested Cultists at a time.
    SPELL_CUSTOM_ERROR_REQUIRES_LEVEL_85                = 120, // You must reach level 85 to use this portal.
    SPELL_CUSTOM_ERROR_MUST_BE_BELOW_35_HEALTH          = 121, // Your target must be below 35% health.
    SPELL_CUSTOM_ERROR_MUST_SELECT_TALENT_SPECIAL       = 122, // You must select a talent specialization first.
    SPELL_CUSTOM_ERROR_TOO_WISE_AND_POWERFUL            = 123, // You are too wise and powerful to gain any benefit from that item.
    SPELL_CUSTOM_ERROR_TOO_CLOSE_ARGENT_LIGHTWELL       = 124, // You are within 10 yards of another Argent Lightwell.
    SPELL_CUSTOM_ERROR_NOT_WHILE_SHAPESHIFTED           = 125, // You can't do that while shapeshifted.
    SPELL_CUSTOM_ERROR_MANA_GEM_IN_BANK                 = 126, // You already have a Mana Gem in your bank.
    SPELL_CUSTOM_ERROR_FLAME_SHOCK_NOT_ACTIVE           = 127, // You must have at least one Flame Shock active.
    SPELL_CUSTOM_ERROR_CANT_TRANSFORM                   = 128, // You cannot transform right now
    SPELL_CUSTOM_ERROR_PET_MUST_BE_ATTACKING            = 129, // Your pet must be attacking a target.
    SPELL_CUSTOM_ERROR_GNOMISH_ENGINEERING              = 130, // Requires Gnomish Engineering
    SPELL_CUSTOM_ERROR_GOBLIN_ENGINEERING               = 131, // Requires Goblin Engineering
    SPELL_CUSTOM_ERROR_NO_TARGET                        = 132, // You have no target.
    SPELL_CUSTOM_ERROR_PET_OUT_OF_RANGE                 = 133, // Your Pet is out of range of the target.
    SPELL_CUSTOM_ERROR_HOLDING_FLAG                     = 134, // You can't do that while holding the flag.
    SPELL_CUSTOM_ERROR_TARGET_HOLDING_FLAG              = 135, // You can't do that to targets holding the flag.
    SPELL_CUSTOM_ERROR_PORTAL_NOT_OPEN                  = 136, // The portal is not yet open. Continue helping the druids at the Sanctuary of Malorne.
    SPELL_CUSTOM_ERROR_AGGRA_AIR_TOTEM                  = 137, // You need to be closer to Aggra's Air Totem, in the west.
    SPELL_CUSTOM_ERROR_AGGRA_WATER_TOTEM                = 138, // You need to be closer to Aggra's Water Totem, in the north.
    SPELL_CUSTOM_ERROR_AGGRA_EARTH_TOTEM                = 139, // You need to be closer to Aggra's Earth Totem, in the east.
    SPELL_CUSTOM_ERROR_AGGRA_FIRE_TOTEM                 = 140, // You need to be closer to Aggra's Fire Totem, near Thrall.
    SPELL_CUSTOM_ERROR_TARGET_HAS_STARTDUST_2           = 148, // Target is already affected by Stardust No. 2.
    SPELL_CUSTOM_ERROR_ELEMENTIUM_GEM_CLUSTERS          = 149  // You cannot deconstruct Elementium Gem Clusters while collecting them!
};

enum StealthType
{
    STEALTH_GENERAL     = 0,
    STEALTH_TRAP        = 1,

    TOTAL_STEALTH_TYPES = 2
};

enum InvisibilityType
{
    INVISIBILITY_GENERAL     =  0,
    INVISIBILITY_UNK1        =  1,
    INVISIBILITY_UNK2        =  2,
    INVISIBILITY_TRAP        =  3,
    INVISIBILITY_UNK4        =  4,
    INVISIBILITY_UNK5        =  5,
    INVISIBILITY_DRUNK       =  6,
    INVISIBILITY_UNK7        =  7,
    INVISIBILITY_UNK8        =  8,
    INVISIBILITY_UNK9        =  9,
    INVISIBILITY_UNK10       = 10,
    INVISIBILITY_UNK11       = 11,
    INVISIBILITY_UNK12       = 12,
    INVISIBILITY_TRA13       = 13,
    INVISIBILITY_UNK14       = 14,
    INVISIBILITY_UNK15       = 15,
    INVISIBILITY_UNK16       = 16,
    INVISIBILITY_UNK17       = 17,
    INVISIBILITY_UNK18       = 18,
    INVISIBILITY_UNK19       = 19,
    INVISIBILITY_UNK20       = 20,
    INVISIBILITY_UNK21       = 21,
    INVISIBILITY_UNK22       = 22,
    INVISIBILITY_TRA23       = 23,
    INVISIBILITY_UNK24       = 24,
    INVISIBILITY_UNK25       = 25,
    INVISIBILITY_UNK26       = 26,
    INVISIBILITY_UNK27       = 27,
    INVISIBILITY_UNK28       = 28,
    INVISIBILITY_UNK29       = 29,
    INVISIBILITY_UNK30       = 30,
    INVISIBILITY_UNK31       = 31,
    INVISIBILITY_UNK32       = 32,
    INVISIBILITY_UNK33       = 33,
    INVISIBILITY_UNK34       = 34,
    INVISIBILITY_UNK35       = 35,
    INVISIBILITY_UNK36       = 36,
    INVISIBILITY_UNK37       = 37,

    TOTAL_INVISIBILITY_TYPES = 38
};

enum ServerSideVisibilityType
{
    SERVERSIDE_VISIBILITY_GM          = 0,
    SERVERSIDE_VISIBILITY_GHOST       = 1,

    TOTAL_SERVERSIDE_VISIBILITY_TYPES = 2
};

enum GhostVisibilityType
{
    GHOST_VISIBILITY_ALIVE = 0x1,
    GHOST_VISIBILITY_GHOST = 0x2
};

// Spell aura states
enum AuraStateType
{   // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_NONE                         = 0,            // C   |
    AURA_STATE_DEFENSE                      = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT        = 2,            // CcT |
    AURA_STATE_BERSERKING                   = 3,            // C T |
    AURA_STATE_FROZEN                       = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT                    = 5,            // C   |
    //AURA_STATE_UNKNOWN6                   = 6,            //     | not used
    AURA_STATE_HUNTER_PARRY                 = 7,            // C   |
    //AURA_STATE_UNKNOWN7                   = 7,            //  c  | creature cheap shot / focused bursts spells
    //AURA_STATE_UNKNOWN8                   = 8,            //    t| test spells
    //AURA_STATE_UNKNOWN9                   = 9,            //     |
    AURA_STATE_WARRIOR_VICTORY_RUSH         = 10,           // C   | warrior victory rush
    //AURA_STATE_UNKNOWN11                  = 11,           // C  t| 60348 - Maelstrom Ready!, test spells
    AURA_STATE_FAERIE_FIRE                  = 12,           //  c t|
    AURA_STATE_HEALTHLESS_35_PERCENT        = 13,           // C T |
    AURA_STATE_CONFLAGRATE                  = 14,           //   T |
    AURA_STATE_SWIFTMEND                    = 15,           //   T |
    AURA_STATE_DEADLY_POISON                = 16,           //   T |
    AURA_STATE_ENRAGE                       = 17,           // C   |
    AURA_STATE_BLEEDING                     = 18,           //    T|
    AURA_STATE_UNKNOWN19                    = 19,           //     |
    AURA_STATE_ALLOW_SPEC_CHANGE_BG         = 20,           //  c  |
    //AURA_STATE_UNKNOWN21                  = 21,           //     | not used
    AURA_STATE_UNKNOWN22                    = 22,           // C  t| varius spells (63884, 50240)
    AURA_STATE_HEALTH_ABOVE_75_PERCENT      = 23            // C   |
};

#define PER_CASTER_AURA_STATE_MASK (\
    (1<<(AURA_STATE_CONFLAGRATE-1))|(1<<(AURA_STATE_DEADLY_POISON-1)))

// Spell mechanics
enum Mechanics : uint32
{
    MECHANIC_NONE             = 0,
    MECHANIC_CHARM            = 1,
    MECHANIC_DISORIENTED      = 2,
    MECHANIC_DISARM           = 3,
    MECHANIC_DISTRACT         = 4,
    MECHANIC_FEAR             = 5,
    MECHANIC_GRIP             = 6,
    MECHANIC_ROOT             = 7,
    MECHANIC_SLOW_ATTACK      = 8,
    MECHANIC_SILENCE          = 9,
    MECHANIC_SLEEP            = 10,
    MECHANIC_SNARE            = 11,
    MECHANIC_STUN             = 12,
    MECHANIC_FREEZE           = 13,
    MECHANIC_KNOCKOUT         = 14,
    MECHANIC_BLEED            = 15,
    MECHANIC_BANDAGE          = 16,
    MECHANIC_POLYMORPH        = 17,
    MECHANIC_BANISH           = 18,
    MECHANIC_SHIELD           = 19,
    MECHANIC_SHACKLE          = 20,
    MECHANIC_MOUNT            = 21,
    MECHANIC_INFECTED         = 22,
    MECHANIC_TURN             = 23,
    MECHANIC_HORROR           = 24,
    MECHANIC_INVULNERABILITY  = 25,
    MECHANIC_INTERRUPT        = 26,
    MECHANIC_DAZE             = 27,
    MECHANIC_DISCOVERY        = 28,
    MECHANIC_IMMUNE_SHIELD    = 29,                         // Divine (Blessing) Shield/Protection and Ice Block
    MECHANIC_SAPPED           = 30,
    MECHANIC_ENRAGED          = 31,
    MECHANIC_WOUNDED          = 32,
    MAX_MECHANIC              = 33
};

// Used for spell 42292 Immune Movement Impairment and Loss of Control (0x49967ca6)
#define IMMUNE_TO_MOVEMENT_IMPAIRMENT_AND_LOSS_CONTROL_MASK (\
    (1<<MECHANIC_CHARM)|(1<<MECHANIC_DISORIENTED)|(1<<MECHANIC_FEAR)| \
    (1<<MECHANIC_ROOT)|(1<<MECHANIC_SLEEP)|(1<<MECHANIC_SNARE)| \
    (1<<MECHANIC_STUN)|(1<<MECHANIC_FREEZE)|(1<<MECHANIC_SILENCE)|(1<<MECHANIC_DISARM)|(1<<MECHANIC_KNOCKOUT)| \
    (1<<MECHANIC_POLYMORPH)|(1<<MECHANIC_BANISH)|(1<<MECHANIC_SHACKLE)| \
    (1<<MECHANIC_TURN)|(1<<MECHANIC_HORROR)|(1<<MECHANIC_DAZE)| \
    (1<<MECHANIC_SAPPED))

// Spell dispel type
enum DispelType
{
    DISPEL_NONE         = 0,
    DISPEL_MAGIC        = 1,
    DISPEL_CURSE        = 2,
    DISPEL_DISEASE      = 3,
    DISPEL_POISON       = 4,
    DISPEL_STEALTH      = 5,
    DISPEL_INVISIBILITY = 6,
    DISPEL_ALL          = 7,
    DISPEL_SPE_NPC_ONLY = 8,
    DISPEL_ENRAGE       = 9,
    DISPEL_ZG_TICKET    = 10,
    DESPEL_OLD_UNUSED   = 11
};

#define DISPEL_ALL_MASK ((1<<DISPEL_MAGIC) | (1<<DISPEL_CURSE) | (1<<DISPEL_DISEASE) | (1<<DISPEL_POISON))

//To all Immune system, if target has immunes,
//some spell that related to ImmuneToDispel or ImmuneToSchool or ImmuneToDamage type can't cast to it,
//some spell_effects that related to ImmuneToEffect<effect>(only this effect in the spell) can't cast to it,
//some aura(related to Mechanics or ImmuneToState<aura>) can't apply to it.
enum SpellImmunity
{
    IMMUNITY_EFFECT                = 0,                     // enum SpellEffects
    IMMUNITY_STATE                 = 1,                     // enum AuraType
    IMMUNITY_SCHOOL                = 2,                     // enum SpellSchoolMask
    IMMUNITY_DAMAGE                = 3,                     // enum SpellSchoolMask
    IMMUNITY_DISPEL                = 4,                     // enum DispelType
    IMMUNITY_MECHANIC              = 5,                     // enum Mechanics
    IMMUNITY_ID                    = 6,

    MAX_SPELL_IMMUNITY
};

// target enum name consist of:
// TARGET_[OBJECT_TYPE]_[REFERENCE_TYPE(skipped for caster)]_[SELECTION_TYPE(skipped for default)]_[additional specifiers(friendly, BACK_LEFT, etc.]
enum Targets
{
    TARGET_UNIT_CASTER                          = 1,
    TARGET_UNIT_NEARBY_ENEMY                    = 2,
    TARGET_UNIT_NEARBY_ALLY                     = 3,
    TARGET_UNIT_NEARBY_PARTY                    = 4,
    TARGET_UNIT_PET                             = 5,
    TARGET_UNIT_TARGET_ENEMY                    = 6,
    TARGET_UNIT_SRC_AREA_ENTRY                  = 7,
    TARGET_UNIT_DEST_AREA_ENTRY                 = 8,
    TARGET_DEST_HOME                            = 9,
    TARGET_UNIT_SRC_AREA_UNK_11                 = 11,
    TARGET_UNIT_SRC_AREA_ENEMY                  = 15,
    TARGET_UNIT_DEST_AREA_ENEMY                 = 16,
    TARGET_DEST_DB                              = 17,
    TARGET_DEST_CASTER                          = 18,
    TARGET_UNIT_CASTER_AREA_PARTY               = 20,
    TARGET_UNIT_TARGET_ALLY                     = 21,
    TARGET_SRC_CASTER                           = 22,
    TARGET_GAMEOBJECT_TARGET                    = 23,
    TARGET_UNIT_CONE_ENEMY_24                   = 24,
    TARGET_UNIT_TARGET_ANY                      = 25,
    TARGET_GAMEOBJECT_ITEM_TARGET               = 26,
    TARGET_UNIT_MASTER                          = 27,
    TARGET_DEST_DYNOBJ_ENEMY                    = 28,
    TARGET_DEST_DYNOBJ_ALLY                     = 29,
    TARGET_UNIT_SRC_AREA_ALLY                   = 30,
    TARGET_UNIT_DEST_AREA_ALLY                  = 31,
    TARGET_DEST_CASTER_SUMMON                   = 32, // front left, doesn't use radius
    TARGET_UNIT_SRC_AREA_PARTY                  = 33,
    TARGET_UNIT_DEST_AREA_PARTY                 = 34,
    TARGET_UNIT_TARGET_PARTY                    = 35,
    TARGET_DEST_CASTER_UNK_36                   = 36,
    TARGET_UNIT_LASTTARGET_AREA_PARTY           = 37,
    TARGET_UNIT_NEARBY_ENTRY                    = 38,
    TARGET_DEST_CASTER_FISHING                  = 39,
    TARGET_GAMEOBJECT_NEARBY_ENTRY              = 40,
    TARGET_DEST_CASTER_FRONT_RIGHT              = 41,
    TARGET_DEST_CASTER_BACK_RIGHT               = 42,
    TARGET_DEST_CASTER_BACK_LEFT                = 43,
    TARGET_DEST_CASTER_FRONT_LEFT               = 44,
    TARGET_UNIT_TARGET_CHAINHEAL_ALLY           = 45,
    TARGET_DEST_NEARBY_ENTRY                    = 46,
    TARGET_DEST_CASTER_FRONT                    = 47,
    TARGET_DEST_CASTER_BACK                     = 48,
    TARGET_DEST_CASTER_RIGHT                    = 49,
    TARGET_DEST_CASTER_LEFT                     = 50,
    TARGET_GAMEOBJECT_SRC_AREA                  = 51,
    TARGET_GAMEOBJECT_DEST_AREA                 = 52,
    TARGET_DEST_TARGET_ENEMY                    = 53,
    TARGET_UNIT_CONE_180_DEG_ENEMY              = 54, // Defaults to 180 if ConeDegrees is not set
    TARGET_DEST_CASTER_FRONT_LEAP               = 55, // for a leap spell
    TARGET_UNIT_CASTER_AREA_RAID                = 56,
    TARGET_UNIT_TARGET_RAID                     = 57,
    TARGET_UNIT_NEARBY_RAID                     = 58,
    TARGET_UNIT_CONE_ALLY                       = 59,
    TARGET_UNIT_CONE_ENTRY                      = 60,
    TARGET_UNIT_TARGET_AREA_RAID_CLASS          = 61,
    TARGET_DEST_CASTER_GROUND                   = 62,
    TARGET_DEST_TARGET_ANY                      = 63,
    TARGET_DEST_TARGET_FRONT                    = 64,
    TARGET_DEST_TARGET_BACK                     = 65,
    TARGET_DEST_TARGET_RIGHT                    = 66,
    TARGET_DEST_TARGET_LEFT                     = 67,
    TARGET_DEST_TARGET_FRONT_RIGHT              = 68,
    TARGET_DEST_TARGET_BACK_RIGHT               = 69,
    TARGET_DEST_TARGET_BACK_LEFT                = 70,
    TARGET_DEST_TARGET_FRONT_LEFT               = 71,
    TARGET_DEST_CASTER_RANDOM                   = 72,
    TARGET_DEST_CASTER_RADIUS                   = 73,
    TARGET_DEST_TARGET_RANDOM                   = 74,
    TARGET_DEST_TARGET_RADIUS                   = 75,
    TARGET_DEST_CHANNEL_TARGET                  = 76,
    TARGET_UNIT_CHANNEL_TARGET                  = 77,
    TARGET_DEST_DEST_FRONT                      = 78,
    TARGET_DEST_DEST_BACK                       = 79,
    TARGET_DEST_DEST_RIGHT                      = 80,
    TARGET_DEST_DEST_LEFT                       = 81,
    TARGET_DEST_DEST_FRONT_RIGHT                = 82,
    TARGET_DEST_DEST_BACK_RIGHT                 = 83,
    TARGET_DEST_DEST_BACK_LEFT                  = 84,
    TARGET_DEST_DEST_FRONT_LEFT                 = 85,
    TARGET_DEST_DEST_RANDOM                     = 86,
    TARGET_DEST_DEST                            = 87,
    TARGET_DEST_DYNOBJ_NONE                     = 88,
    TARGET_DEST_TRAJ                            = 89,
    TARGET_UNIT_TARGET_MINIPET                  = 90,
    TARGET_DEST_DEST_RADIUS                     = 91,
    TARGET_UNIT_SUMMONER                        = 92,
    TARGET_CORPSE_SRC_AREA_ENEMY                = 93, // NYI
    TARGET_UNIT_VEHICLE                         = 94,
    TARGET_UNIT_TARGET_PASSENGER                = 95,
    TARGET_UNIT_PASSENGER_0                     = 96,
    TARGET_UNIT_PASSENGER_1                     = 97,
    TARGET_UNIT_PASSENGER_2                     = 98,
    TARGET_UNIT_PASSENGER_3                     = 99,
    TARGET_UNIT_PASSENGER_4                     = 100,
    TARGET_UNIT_PASSENGER_5                     = 101,
    TARGET_UNIT_PASSENGER_6                     = 102,
    TARGET_UNIT_PASSENGER_7                     = 103,
    TARGET_UNIT_CONE_CASTER_TO_DEST_ENEMY       = 104,
    TARGET_UNIT_CASTER_AND_PASSENGERS           = 105,
    TARGET_DEST_CHANNEL_CASTER                  = 106,
    TARGET_DEST_NEARBY_ENTRY_2                  = 107,
    TARGET_GAMEOBJECT_CONE_CASTER_TO_DEST_ENEMY = 108,
    TARGET_GAMEOBJECT_CONE_CASTER_TO_DEST_ALLY  = 109,
    TARGET_UNIT_CONE_CASTER_TO_DEST_ENTRY       = 110, // 1 spell
    TARGET_UNK_111                              = 111,
    TARGET_DEST_TARGET_ANY_2                    = 112, // 1 Spell
    TARGET_UNK_113                              = 113,
    TARGET_UNK_114                              = 114,
    TARGET_UNK_115                              = 115,
    TARGET_UNK_116                              = 116,
    TARGET_UNK_117                              = 117,
    TARGET_UNIT_TARGET_ALLY_OR_RAID             = 118, // If target is in your party or raid, all party and raid members will be affected
    TARGET_CORPSE_SRC_AREA_RAID                 = 119,
    TARGET_UNIT_CASTER_AND_SUMMONS              = 120,
    TARGET_CORPSE_TARGET_ALLY                   = 121,
    TARGET_UNIT_AREA_THREAT_LIST                = 122,
    TARGET_UNIT_AREA_TAP_LIST                   = 123,
    TARGET_UNIT_TARGET_TAP_LIST                 = 124,
    TARGET_DEST_CASTER_GROUND_2                 = 125, // 1 spell in 4.3.4
    TARGET_UNIT_AREA_ENEMY                      = 126, // 1 spell in 4.3.4 (checked up until 8.3.0)
    TARGET_UNK_127                              = 127,
    TOTAL_SPELL_TARGETS
};

enum SpellMissInfo : uint8
{
    SPELL_MISS_NONE                    = 0,
    SPELL_MISS_MISS                    = 1,
    SPELL_MISS_RESIST                  = 2,
    SPELL_MISS_DODGE                   = 3,
    SPELL_MISS_PARRY                   = 4,
    SPELL_MISS_BLOCK                   = 5,
    SPELL_MISS_EVADE                   = 6,
    SPELL_MISS_IMMUNE                  = 7,
    SPELL_MISS_IMMUNE2                 = 8, // one of these 2 is MISS_TEMPIMMUNE
    SPELL_MISS_DEFLECT                 = 9,
    SPELL_MISS_ABSORB                  = 10,
    SPELL_MISS_REFLECT                 = 11
};

enum SpellHitType
{
    SPELL_HIT_TYPE_CRIT_DEBUG           = 0x01,
    SPELL_HIT_TYPE_CRIT                 = 0x02,
    SPELL_HIT_TYPE_HIT_DEBUG            = 0x04,
    SPELL_HIT_TYPE_SPLIT                = 0x08,
    SPELL_HIT_TYPE_VICTIM_IS_ATTACKER   = 0x10,
    SPELL_HIT_TYPE_ATTACK_TABLE_DEBUG   = 0x20
};

enum SpellDmgClass
{
    SPELL_DAMAGE_CLASS_NONE     = 0,
    SPELL_DAMAGE_CLASS_MAGIC    = 1,
    SPELL_DAMAGE_CLASS_MELEE    = 2,
    SPELL_DAMAGE_CLASS_RANGED   = 3
};

enum SpellPreventionType
{
    SPELL_PREVENTION_TYPE_NONE          = 0,
    SPELL_PREVENTION_TYPE_SILENCE       = 1,
    SPELL_PREVENTION_TYPE_PACIFY        = 2,
    SPELL_PREVENTION_TYPE_UNK           = 3, // Only a few spells have this, but most of the should be interruptable.
    SPELL_PREVENTION_TYPE_NO_ACTIONS    = 4
};

enum GameobjectTypes
{
    GAMEOBJECT_TYPE_DOOR                   = 0,
    GAMEOBJECT_TYPE_BUTTON                 = 1,
    GAMEOBJECT_TYPE_QUESTGIVER             = 2,
    GAMEOBJECT_TYPE_CHEST                  = 3,
    GAMEOBJECT_TYPE_BINDER                 = 4,
    GAMEOBJECT_TYPE_GENERIC                = 5,
    GAMEOBJECT_TYPE_TRAP                   = 6,
    GAMEOBJECT_TYPE_CHAIR                  = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
    GAMEOBJECT_TYPE_TEXT                   = 9,
    GAMEOBJECT_TYPE_GOOBER                 = 10,
    GAMEOBJECT_TYPE_TRANSPORT              = 11,
    GAMEOBJECT_TYPE_AREADAMAGE             = 12,
    GAMEOBJECT_TYPE_CAMERA                 = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
    GAMEOBJECT_TYPE_FISHINGNODE            = 17,
    GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
    GAMEOBJECT_TYPE_MAILBOX                = 19,
    GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
    GAMEOBJECT_TYPE_GUARDPOST              = 21,
    GAMEOBJECT_TYPE_SPELLCASTER            = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
    GAMEOBJECT_TYPE_FLAGSTAND              = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
    GAMEOBJECT_TYPE_FLAGDROP               = 26,
    GAMEOBJECT_TYPE_MINI_GAME              = 27,
    GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
    GAMEOBJECT_TYPE_GUILD_BANK             = 34,
    GAMEOBJECT_TYPE_TRAPDOOR               = 35
};

#define MAX_GAMEOBJECT_TYPE                  36             // sending to client this or greater value can crash client.
#define MAX_GAMEOBJECT_DATA                  32             // Max number of uint32 vars in gameobject_template data field

enum GameObjectFlags
{
    GO_FLAG_IN_USE          = 0x00000001,                   // disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   // require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   // cannot interact (condition to interact - requires GO_DYNFLAG_LO_ACTIVATE to enable interaction clientside)
    GO_FLAG_TRANSPORT       = 0x00000008,                   // any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_NOT_SELECTABLE  = 0x00000010,                   // not selectable even in GM mode
    GO_FLAG_NODESPAWN       = 0x00000020,                   // never despawn, typically for doors, they just change state
    GO_FLAG_AI_OBSTACLE     = 0x00000040,                   // makes the client register the object in something called AIObstacleMgr, unknown what it does
    GO_FLAG_FREEZE_ANIMATION = 0x00000080,
    GO_FLAG_DAMAGED         = 0x00000200,
    GO_FLAG_DESTROYED       = 0x00000400
};

enum GameObjectDynamicLowFlags : uint16
{
    GO_DYNFLAG_LO_ACTIVATE          = 0x01,                 // enables interaction with GO
    GO_DYNFLAG_LO_ANIMATE           = 0x02,                 // possibly more distinct animation of GO
    GO_DYNFLAG_LO_NO_INTERACT       = 0x04,                 // appears to disable interaction (not fully verified)
    GO_DYNFLAG_LO_SPARKLE           = 0x08,                 // makes GO sparkle
    GO_DYNFLAG_LO_STOPPED           = 0x10,                 // Transport is stopped
    GO_DYNFLAG_LO_INVERTED_MOVEMENT = 0x40,                 // GAMEOBJECT_TYPE_TRANSPORT only
};

// client side GO show states
enum GOState : uint8
{
    GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
    GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
    GO_STATE_ACTIVE_ALTERNATIVE = 2,                        // show in world as used in alt way and not reset (closed door open by cannon fire)
    GO_STATE_TRANSPORT_ACTIVE   = 24,                       // transport exclusive: transport may always move
    GO_STATE_TRANSPORT_STOPPED  = 25                        // transport exclusive: transport is going to stop at provided stop frame
};

#define MAX_GO_STATE 3
#define MAX_GO_STATE_TRANSPORT_STOP_FRAMES 9

enum GameObjectDestructibleState
{
    GO_DESTRUCTIBLE_INTACT      = 0,
    GO_DESTRUCTIBLE_DAMAGED     = 1,
    GO_DESTRUCTIBLE_DESTROYED   = 2,
    GO_DESTRUCTIBLE_REBUILDING  = 3
};

// EmotesText.dbc
enum TextEmotes
{
    TEXT_EMOTE_AGREE                = 1,
    TEXT_EMOTE_AMAZE                = 2,
    TEXT_EMOTE_ANGRY                = 3,
    TEXT_EMOTE_APOLOGIZE            = 4,
    TEXT_EMOTE_APPLAUD              = 5,
    TEXT_EMOTE_BASHFUL              = 6,
    TEXT_EMOTE_BECKON               = 7,
    TEXT_EMOTE_BEG                  = 8,
    TEXT_EMOTE_BITE                 = 9,
    TEXT_EMOTE_BLEED                = 10,
    TEXT_EMOTE_BLINK                = 11,
    TEXT_EMOTE_BLUSH                = 12,
    TEXT_EMOTE_BONK                 = 13,
    TEXT_EMOTE_BORED                = 14,
    TEXT_EMOTE_BOUNCE               = 15,
    TEXT_EMOTE_BRB                  = 16,
    TEXT_EMOTE_BOW                  = 17,
    TEXT_EMOTE_BURP                 = 18,
    TEXT_EMOTE_BYE                  = 19,
    TEXT_EMOTE_CACKLE               = 20,
    TEXT_EMOTE_CHEER                = 21,
    TEXT_EMOTE_CHICKEN              = 22,
    TEXT_EMOTE_CHUCKLE              = 23,
    TEXT_EMOTE_CLAP                 = 24,
    TEXT_EMOTE_CONFUSED             = 25,
    TEXT_EMOTE_CONGRATULATE         = 26,
    TEXT_EMOTE_COUGH                = 27,
    TEXT_EMOTE_COWER                = 28,
    TEXT_EMOTE_CRACK                = 29,
    TEXT_EMOTE_CRINGE               = 30,
    TEXT_EMOTE_CRY                  = 31,
    TEXT_EMOTE_CURIOUS              = 32,
    TEXT_EMOTE_CURTSEY              = 33,
    TEXT_EMOTE_DANCE                = 34,
    TEXT_EMOTE_DRINK                = 35,
    TEXT_EMOTE_DROOL                = 36,
    TEXT_EMOTE_EAT                  = 37,
    TEXT_EMOTE_EYE                  = 38,
    TEXT_EMOTE_FART                 = 39,
    TEXT_EMOTE_FIDGET               = 40,
    TEXT_EMOTE_FLEX                 = 41,
    TEXT_EMOTE_FROWN                = 42,
    TEXT_EMOTE_GASP                 = 43,
    TEXT_EMOTE_GAZE                 = 44,
    TEXT_EMOTE_GIGGLE               = 45,
    TEXT_EMOTE_GLARE                = 46,
    TEXT_EMOTE_GLOAT                = 47,
    TEXT_EMOTE_GREET                = 48,
    TEXT_EMOTE_GRIN                 = 49,
    TEXT_EMOTE_GROAN                = 50,
    TEXT_EMOTE_GROVEL               = 51,
    TEXT_EMOTE_GUFFAW               = 52,
    TEXT_EMOTE_HAIL                 = 53,
    TEXT_EMOTE_HAPPY                = 54,
    TEXT_EMOTE_HELLO                = 55,
    TEXT_EMOTE_HUG                  = 56,
    TEXT_EMOTE_HUNGRY               = 57,
    TEXT_EMOTE_KISS                 = 58,
    TEXT_EMOTE_KNEEL                = 59,
    TEXT_EMOTE_LAUGH                = 60,
    TEXT_EMOTE_LAYDOWN              = 61,
    TEXT_EMOTE_MESSAGE              = 62,
    TEXT_EMOTE_MOAN                 = 63,
    TEXT_EMOTE_MOON                 = 64,
    TEXT_EMOTE_MOURN                = 65,
    TEXT_EMOTE_NO                   = 66,
    TEXT_EMOTE_NOD                  = 67,
    TEXT_EMOTE_NOSEPICK             = 68,
    TEXT_EMOTE_PANIC                = 69,
    TEXT_EMOTE_PEER                 = 70,
    TEXT_EMOTE_PLEAD                = 71,
    TEXT_EMOTE_POINT                = 72,
    TEXT_EMOTE_POKE                 = 73,
    TEXT_EMOTE_PRAY                 = 74,
    TEXT_EMOTE_ROAR                 = 75,
    TEXT_EMOTE_ROFL                 = 76,
    TEXT_EMOTE_RUDE                 = 77,
    TEXT_EMOTE_SALUTE               = 78,
    TEXT_EMOTE_SCRATCH              = 79,
    TEXT_EMOTE_SEXY                 = 80,
    TEXT_EMOTE_SHAKE                = 81,
    TEXT_EMOTE_SHOUT                = 82,
    TEXT_EMOTE_SHRUG                = 83,
    TEXT_EMOTE_SHY                  = 84,
    TEXT_EMOTE_SIGH                 = 85,
    TEXT_EMOTE_SIT                  = 86,
    TEXT_EMOTE_SLEEP                = 87,
    TEXT_EMOTE_SNARL                = 88,
    TEXT_EMOTE_SPIT                 = 89,
    TEXT_EMOTE_STARE                = 90,
    TEXT_EMOTE_SURPRISED            = 91,
    TEXT_EMOTE_SURRENDER            = 92,
    TEXT_EMOTE_TALK                 = 93,
    TEXT_EMOTE_TALKEX               = 94,
    TEXT_EMOTE_TALKQ                = 95,
    TEXT_EMOTE_TAP                  = 96,
    TEXT_EMOTE_THANK                = 97,
    TEXT_EMOTE_THREATEN             = 98,
    TEXT_EMOTE_TIRED                = 99,
    TEXT_EMOTE_VICTORY              = 100,
    TEXT_EMOTE_WAVE                 = 101,
    TEXT_EMOTE_WELCOME              = 102,
    TEXT_EMOTE_WHINE                = 103,
    TEXT_EMOTE_WHISTLE              = 104,
    TEXT_EMOTE_WORK                 = 105,
    TEXT_EMOTE_YAWN                 = 106,
    TEXT_EMOTE_BOGGLE               = 107,
    TEXT_EMOTE_CALM                 = 108,
    TEXT_EMOTE_COLD                 = 109,
    TEXT_EMOTE_COMFORT              = 110,
    TEXT_EMOTE_CUDDLE               = 111,
    TEXT_EMOTE_DUCK                 = 112,
    TEXT_EMOTE_INSULT               = 113,
    TEXT_EMOTE_INTRODUCE            = 114,
    TEXT_EMOTE_JK                   = 115,
    TEXT_EMOTE_LICK                 = 116,
    TEXT_EMOTE_LISTEN               = 117,
    TEXT_EMOTE_LOST                 = 118,
    TEXT_EMOTE_MOCK                 = 119,
    TEXT_EMOTE_PONDER               = 120,
    TEXT_EMOTE_POUNCE               = 121,
    TEXT_EMOTE_PRAISE               = 122,
    TEXT_EMOTE_PURR                 = 123,
    TEXT_EMOTE_PUZZLE               = 124,
    TEXT_EMOTE_RAISE                = 125,
    TEXT_EMOTE_READY                = 126,
    TEXT_EMOTE_SHIMMY               = 127,
    TEXT_EMOTE_SHIVER               = 128,
    TEXT_EMOTE_SHOO                 = 129,
    TEXT_EMOTE_SLAP                 = 130,
    TEXT_EMOTE_SMIRK                = 131,
    TEXT_EMOTE_SNIFF                = 132,
    TEXT_EMOTE_SNUB                 = 133,
    TEXT_EMOTE_SOOTHE               = 134,
    TEXT_EMOTE_STINK                = 135,
    TEXT_EMOTE_TAUNT                = 136,
    TEXT_EMOTE_TEASE                = 137,
    TEXT_EMOTE_THIRSTY              = 138,
    TEXT_EMOTE_VETO                 = 139,
    TEXT_EMOTE_SNICKER              = 140,
    TEXT_EMOTE_STAND                = 141,
    TEXT_EMOTE_TICKLE               = 142,
    TEXT_EMOTE_VIOLIN               = 143,
    TEXT_EMOTE_SMILE                = 163,
    TEXT_EMOTE_RASP                 = 183,
    TEXT_EMOTE_PITY                 = 203,
    TEXT_EMOTE_GROWL                = 204,
    TEXT_EMOTE_BARK                 = 205,
    TEXT_EMOTE_SCARED               = 223,
    TEXT_EMOTE_FLOP                 = 224,
    TEXT_EMOTE_LOVE                 = 225,
    TEXT_EMOTE_MOO                  = 226,
    TEXT_EMOTE_COMMEND              = 243,
    TEXT_EMOTE_TRAIN                = 264,
    TEXT_EMOTE_HELPME               = 303,
    TEXT_EMOTE_INCOMING             = 304,
    TEXT_EMOTE_CHARGE               = 305,
    TEXT_EMOTE_FLEE                 = 306,
    TEXT_EMOTE_ATTACKMYTARGET       = 307,
    TEXT_EMOTE_OOM                  = 323,
    TEXT_EMOTE_FOLLOW               = 324,
    TEXT_EMOTE_WAIT                 = 325,
    TEXT_EMOTE_HEALME               = 326,
    TEXT_EMOTE_OPENFIRE             = 327,
    TEXT_EMOTE_FLIRT                = 328,
    TEXT_EMOTE_JOKE                 = 329,
    TEXT_EMOTE_GOLFCLAP             = 343,
    TEXT_EMOTE_WINK                 = 363,
    TEXT_EMOTE_PAT                  = 364,
    TEXT_EMOTE_SERIOUS              = 365,
    TEXT_EMOTE_MOUNT_SPECIAL        = 366,
    TEXT_EMOTE_GOODLUCK             = 367,
    TEXT_EMOTE_BLAME                = 368,
    TEXT_EMOTE_BLANK                = 369,
    TEXT_EMOTE_BRANDISH             = 370,
    TEXT_EMOTE_BREATH               = 371,
    TEXT_EMOTE_DISAGREE             = 372,
    TEXT_EMOTE_DOUBT                = 373,
    TEXT_EMOTE_EMBARRASS            = 374,
    TEXT_EMOTE_ENCOURAGE            = 375,
    TEXT_EMOTE_ENEMY                = 376,
    TEXT_EMOTE_EYEBROW              = 377,
    TEXT_EMOTE_TOAST                = 378,
    TEXT_EMOTE_FAIL                 = 379,
    TEXT_EMOTE_HIGHFIVE             = 380,
    TEXT_EMOTE_ABSENT               = 381,
    TEXT_EMOTE_ARM                  = 382,
    TEXT_EMOTE_AWE                  = 383,
    TEXT_EMOTE_BACKPACK             = 384,
    TEXT_EMOTE_BADFEELING           = 385,
    TEXT_EMOTE_CHALLENGE            = 386,
    TEXT_EMOTE_CHUG                 = 387,
    TEXT_EMOTE_DING                 = 389,
    TEXT_EMOTE_FACEPALM             = 390,
    TEXT_EMOTE_FAINT                = 391,
    TEXT_EMOTE_GO                   = 392,
    TEXT_EMOTE_GOING                = 393,
    TEXT_EMOTE_GLOWER               = 394,
    TEXT_EMOTE_HEADACHE             = 395,
    TEXT_EMOTE_HICCUP               = 396,
    TEXT_EMOTE_HISS                 = 398,
    TEXT_EMOTE_HOLDHAND             = 399,
    TEXT_EMOTE_HURRY                = 401,
    TEXT_EMOTE_IDEA                 = 402,
    TEXT_EMOTE_JEALOUS              = 403,
    TEXT_EMOTE_LUCK                 = 404,
    TEXT_EMOTE_MAP                  = 405,
    TEXT_EMOTE_MERCY                = 406,
    TEXT_EMOTE_MUTTER               = 407,
    TEXT_EMOTE_NERVOUS              = 408,
    TEXT_EMOTE_OFFER                = 409,
    TEXT_EMOTE_PET                  = 410,
    TEXT_EMOTE_PINCH                = 411,
    TEXT_EMOTE_PROUD                = 413,
    TEXT_EMOTE_PROMISE              = 414,
    TEXT_EMOTE_PULSE                = 415,
    TEXT_EMOTE_PUNCH                = 416,
    TEXT_EMOTE_POUT                 = 417,
    TEXT_EMOTE_REGRET               = 418,
    TEXT_EMOTE_REVENGE              = 420,
    TEXT_EMOTE_ROLLEYES             = 421,
    TEXT_EMOTE_RUFFLE               = 422,
    TEXT_EMOTE_SAD                  = 423,
    TEXT_EMOTE_SCOFF                = 424,
    TEXT_EMOTE_SCOLD                = 425,
    TEXT_EMOTE_SCOWL                = 426,
    TEXT_EMOTE_SEARCH               = 427,
    TEXT_EMOTE_SHAKEFIST            = 428,
    TEXT_EMOTE_SHIFTY               = 429,
    TEXT_EMOTE_SHUDDER              = 430,
    TEXT_EMOTE_SIGNAL               = 431,
    TEXT_EMOTE_SILENCE              = 432,
    TEXT_EMOTE_SING                 = 433,
    TEXT_EMOTE_SMACK                = 434,
    TEXT_EMOTE_SNEAK                = 435,
    TEXT_EMOTE_SNEEZE               = 436,
    TEXT_EMOTE_SNORT                = 437,
    TEXT_EMOTE_SQUEAL               = 438,
    TEXT_EMOTE_STOPATTACK           = 439,
    TEXT_EMOTE_SUSPICIOUS           = 440,
    TEXT_EMOTE_THINK                = 441,
    TEXT_EMOTE_TRUCE                = 442,
    TEXT_EMOTE_TWIDDLE              = 443,
    TEXT_EMOTE_WARN                 = 444,
    TEXT_EMOTE_SNAP                 = 445,
    TEXT_EMOTE_CHARM                = 446,
    TEXT_EMOTE_COVEREARS            = 447,
    TEXT_EMOTE_CROSSARMS            = 448,
    TEXT_EMOTE_LOOK                 = 449,
    TEXT_EMOTE_OBJECT               = 450,
    TEXT_EMOTE_SWEAT                = 451,
    TEXT_EMOTE_YW                   = 453,
    TEXT_EMOTE_READ                 = 456
};

// Emotes.dbc
enum Emote
{
    EMOTE_ONESHOT_NONE                  = 0,
    EMOTE_ONESHOT_TALK                  = 1,
    EMOTE_ONESHOT_BOW                   = 2,
    EMOTE_ONESHOT_WAVE                  = 3,
    EMOTE_ONESHOT_CHEER                 = 4,
    EMOTE_ONESHOT_EXCLAMATION           = 5,
    EMOTE_ONESHOT_QUESTION              = 6,
    EMOTE_ONESHOT_EAT                   = 7,
    EMOTE_STATE_DANCE                   = 10,
    EMOTE_ONESHOT_LAUGH                 = 11,
    EMOTE_STATE_SLEEP                   = 12,
    EMOTE_STATE_SIT                     = 13,
    EMOTE_ONESHOT_RUDE                  = 14,
    EMOTE_ONESHOT_ROAR                  = 15,
    EMOTE_ONESHOT_KNEEL                 = 16,
    EMOTE_ONESHOT_KISS                  = 17,
    EMOTE_ONESHOT_CRY                   = 18,
    EMOTE_ONESHOT_CHICKEN               = 19,
    EMOTE_ONESHOT_BEG                   = 20,
    EMOTE_ONESHOT_APPLAUD               = 21,
    EMOTE_ONESHOT_SHOUT                 = 22,
    EMOTE_ONESHOT_FLEX                  = 23,
    EMOTE_ONESHOT_SHY                   = 24,
    EMOTE_ONESHOT_POINT                 = 25,
    EMOTE_STATE_STAND                   = 26,
    EMOTE_STATE_READY_UNARMED           = 27,
    EMOTE_STATE_WORK_SHEATHED           = 28,
    EMOTE_STATE_POINT                   = 29,
    EMOTE_STATE_NONE                    = 30,
    EMOTE_ONESHOT_WOUND                 = 33,
    EMOTE_ONESHOT_WOUND_CRITICAL        = 34,
    EMOTE_ONESHOT_ATTACK_UNARMED        = 35,
    EMOTE_ONESHOT_ATTACK1H              = 36,
    EMOTE_ONESHOT_ATTACK2HTIGHT         = 37,
    EMOTE_ONESHOT_ATTACK2H_LOOSE        = 38,
    EMOTE_ONESHOT_PARRY_UNARMED         = 39,
    EMOTE_ONESHOT_PARRY_SHIELD          = 43,
    EMOTE_ONESHOT_READY_UNARMED         = 44,
    EMOTE_ONESHOT_READY1H               = 45,
    EMOTE_ONESHOT_READY_BOW             = 48,
    EMOTE_ONESHOT_SPELL_PRECAST         = 50,
    EMOTE_ONESHOT_SPELL_CAST            = 51,
    EMOTE_ONESHOT_BATTLE_ROAR           = 53,
    EMOTE_ONESHOT_SPECIALATTACK1H       = 54,
    EMOTE_ONESHOT_KICK                  = 60,
    EMOTE_ONESHOT_ATTACK_THROWN         = 61,
    EMOTE_STATE_STUN                    = 64,
    EMOTE_STATE_DEAD                    = 65,
    EMOTE_ONESHOT_SALUTE                = 66,
    EMOTE_STATE_KNEEL                   = 68,
    EMOTE_STATE_USE_STANDING            = 69,
    EMOTE_ONESHOT_WAVE_NO_SHEATHE       = 70,
    EMOTE_ONESHOT_CHEER_NO_SHEATHE      = 71,
    EMOTE_ONESHOT_EAT_NO_SHEATHE        = 92,
    EMOTE_STATE_STUN_NO_SHEATHE         = 93,
    EMOTE_ONESHOT_DANCE                 = 94,
    EMOTE_ONESHOT_SALUTE_NO_SHEATH      = 113,
    EMOTE_STATE_USE_STANDING_NO_SHEATHE = 133,
    EMOTE_ONESHOT_LAUGH_NO_SHEATHE      = 153,
    EMOTE_STATE_WORK                    = 173,
    EMOTE_STATE_SPELL_PRECAST           = 193,
    EMOTE_ONESHOT_READY_RIFLE           = 213,
    EMOTE_STATE_READY_RIFLE             = 214,
    EMOTE_STATE_WORK_MINING             = 233,
    EMOTE_STATE_WORK_CHOPWOOD           = 234,
    EMOTE_STATE_APPLAUD                 = 253,
    EMOTE_ONESHOT_LIFTOFF               = 254,
    EMOTE_ONESHOT_YES                   = 273,
    EMOTE_ONESHOT_NO                    = 274,
    EMOTE_ONESHOT_TRAIN                 = 275,
    EMOTE_ONESHOT_LAND                  = 293,
    EMOTE_STATE_AT_EASE                 = 313,
    EMOTE_STATE_READY1H                 = 333,
    EMOTE_STATE_SPELL_KNEEL_START       = 353,
    EMOTE_STATE_SUBMERGED               = 373,
    EMOTE_ONESHOT_SUBMERGE              = 374,
    EMOTE_STATE_READY2H                 = 375,
    EMOTE_STATE_READY_BOW               = 376,
    EMOTE_ONESHOT_MOUNT_SPECIAL         = 377,
    EMOTE_STATE_TALK                    = 378,
    EMOTE_STATE_FISHING                 = 379,
    EMOTE_ONESHOT_FISHING               = 380,
    EMOTE_ONESHOT_LOOT                  = 381,
    EMOTE_STATE_WHIRLWIND               = 382,
    EMOTE_STATE_DROWNED                 = 383,
    EMOTE_STATE_HOLD_BOW                = 384,
    EMOTE_STATE_HOLD_RIFLE              = 385,
    EMOTE_STATE_HOLD_THROWN             = 386,
    EMOTE_ONESHOT_DROWN                 = 387,
    EMOTE_ONESHOT_STOMP                 = 388,
    EMOTE_ONESHOT_ATTACK_OFF            = 389,
    EMOTE_ONESHOT_ATTACK_OFF_PIERCE     = 390,
    EMOTE_STATE_ROAR                    = 391,
    EMOTE_STATE_LAUGH                   = 392,
    EMOTE_ONESHOT_CREATURE_SPECIAL      = 393,
    EMOTE_ONESHOT_JUMPLANDRUN           = 394,
    EMOTE_ONESHOT_JUMPEND               = 395,
    EMOTE_ONESHOT_TALK_NO_SHEATHE       = 396,
    EMOTE_ONESHOT_POINT_NO_SHEATHE      = 397,
    EMOTE_STATE_CANNIBALIZE             = 398,
    EMOTE_ONESHOT_JUMPSTART             = 399,
    EMOTE_STATE_DANCESPECIAL            = 400,
    EMOTE_ONESHOT_DANCESPECIAL          = 401,
    EMOTE_ONESHOT_CUSTOM_SPELL_01       = 402,
    EMOTE_ONESHOT_CUSTOM_SPELL_02       = 403,
    EMOTE_ONESHOT_CUSTOM_SPELL_03       = 404,
    EMOTE_ONESHOT_CUSTOM_SPELL_04       = 405,
    EMOTE_ONESHOT_CUSTOM_SPELL_05       = 406,
    EMOTE_ONESHOT_CUSTOM_SPELL_06       = 407,
    EMOTE_ONESHOT_CUSTOM_SPELL_07       = 408,
    EMOTE_ONESHOT_CUSTOM_SPELL_08       = 409,
    EMOTE_ONESHOT_CUSTOM_SPELL_09       = 410,
    EMOTE_ONESHOT_CUSTOM_SPELL_10       = 411,
    EMOTE_STATE_EXCLAIM                 = 412,
    EMOTE_STATE_DANCE_CUSTOM            = 413,
    EMOTE_STATE_SIT_CHAIR_MED           = 415,
    EMOTE_STATE_CUSTOM_SPELL_01         = 416,
    EMOTE_STATE_CUSTOM_SPELL_02         = 417,
    EMOTE_STATE_EAT                     = 418,
    EMOTE_STATE_CUSTOM_SPELL_04         = 419,
    EMOTE_STATE_CUSTOM_SPELL_03         = 420,
    EMOTE_STATE_CUSTOM_SPELL_05         = 421,
    EMOTE_STATE_SPELLEFFECT_HOLD        = 422,
    EMOTE_STATE_EAT_NO_SHEATHE          = 423,
    EMOTE_STATE_MOUNT                   = 424,
    EMOTE_STATE_READY2HL                = 425,
    EMOTE_STATE_SIT_CHAIR_HIGH          = 426,
    EMOTE_STATE_FALL                    = 427,
    EMOTE_STATE_LOOT                    = 428,
    EMOTE_STATE_SUBMERGED_NEW           = 429,
    EMOTE_ONESHOT_COWER                 = 430,
    EMOTE_STATE_COWER                   = 431,
    EMOTE_ONESHOT_USE_STANDING          = 432,
    EMOTE_STATE_STEALTH_STAND           = 433,
    EMOTE_ONESHOT_OMNICAST_GHOUL        = 434,
    EMOTE_ONESHOT_ATTACK_BOW            = 435,
    EMOTE_ONESHOT_ATTACK_RIFLE          = 436,
    EMOTE_STATE_SWIM_IDLE               = 437,
    EMOTE_STATE_ATTACK_UNARMED          = 438,
    EMOTE_ONESHOT_SPELL_CAST_W_SOUND    = 439,
    EMOTE_ONESHOT_DODGE                 = 440,
    EMOTE_ONESHOT_PARRY1H               = 441,
    EMOTE_ONESHOT_PARRY2H               = 442,
    EMOTE_ONESHOT_PARRY2HL              = 443,
    EMOTE_STATE_FLYFALL                 = 444,
    EMOTE_ONESHOT_FLYDEATH              = 445,
    EMOTE_STATE_FLY_FALL                = 446,
    EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN   = 447,
    EMOTE_ONESHOT_FLY_SIT_GROUND_UP     = 448,
    EMOTE_ONESHOT_EMERGE                = 449,
    EMOTE_ONESHOT_DRAGON_SPIT           = 450,
    EMOTE_STATE_SPECIAL_UNARMED         = 451,
    EMOTE_ONESHOT_FLYGRAB               = 452,
    EMOTE_STATE_FLYGRABCLOSED           = 453,
    EMOTE_ONESHOT_FLYGRABTHROWN         = 454,
    EMOTE_STATE_FLY_SIT_GROUND          = 455,
    EMOTE_STATE_WALK_BACKWARDS          = 456,
    EMOTE_ONESHOT_FLYTALK               = 457,
    EMOTE_ONESHOT_FLYATTACK1H           = 458,
    EMOTE_STATE_CUSTOM_SPELL_08         = 459,
    EMOTE_ONESHOT_FLY_DRAGON_SPIT       = 460,
    EMOTE_STATE_SIT_CHAIR_LOW           = 461,
    EMOTE_ONESHOT_STUN                  = 462,
    EMOTE_ONESHOT_SPELL_CAST_OMNI       = 463,
    EMOTE_STATE_READY_THROWN            = 465,
    EMOTE_ONESHOT_WORK_CHOPWOOD         = 466,
    EMOTE_ONESHOT_WORK_MINING           = 467,
    EMOTE_STATE_SPELL_CHANNEL_OMNI      = 468,
    EMOTE_STATE_SPELL_CHANNEL_DIRECTED  = 469,
    EMOTE_STAND_STATE_NONE              = 470,
    EMOTE_STATE_READYJOUST              = 471,
    EMOTE_STATE_STRANGULATE             = 473,
    EMOTE_STATE_READY_SPELL_OMNI        = 474,
    EMOTE_STATE_HOLD_JOUST              = 475,
    EMOTE_ONESHOT_CRY_JAINA             = 476,
    EMOTE_ONESHOT_SPECIAL_UNARMED       = 477,
    EMOTE_STATE_DANCE_NOSHEATHE         = 478,
    EMOTE_ONESHOT_SNIFF                 = 479,
    EMOTE_ONESHOT_DRAGONSTOMP           = 480,
    EMOTE_ONESHOT_KNOCKDOWN             = 482,
    EMOTE_STATE_READ                    = 483,
    EMOTE_ONESHOT_FLYEMOTETALK          = 485,
    EMOTE_STATE_READ_ALLOWMOVEMENT      = 492,
    EMOTE_STATE_READY1H_ALLOW_MOVEMENT  = 505,
    EMOTE_STATE_READY2H_ALLOW_MOVEMENT  = 506,
    EMOTE_ONESHOT_OPEN                  = 517,
    EMOTE_STATE_READ_CHRISTMAS          = 518
};

// AnimationData.dbc
enum Anim
{
    ANIM_STAND                             = 0,
    ANIM_DEATH                             = 1,
    ANIM_SPELL                             = 2,
    ANIM_STOP                              = 3,
    ANIM_WALK                              = 4,
    ANIM_RUN                               = 5,
    ANIM_DEAD                              = 6,
    ANIM_RISE                              = 7,
    ANIM_STAND_WOUND                       = 8,
    ANIM_COMBAT_WOUND                      = 9,
    ANIM_COMBAT_CRITICAL                   = 10,
    ANIM_SHUFFLE_LEFT                      = 11,
    ANIM_SHUFFLE_RIGHT                     = 12,
    ANIM_WALK_BACKWARDS                    = 13,
    ANIM_STUN                              = 14,
    ANIM_HANDS_CLOSED                      = 15,
    ANIM_ATTACK_UNARMED                    = 16,
    ANIM_ATTACK1H                          = 17,
    ANIM_ATTACK2H                          = 18,
    ANIM_ATTACK2HL                         = 19,
    ANIM_PARRY_UNARMED                     = 20,
    ANIM_PARRY1H                           = 21,
    ANIM_PARRY2H                           = 22,
    ANIM_PARRY2HL                          = 23,
    ANIM_SHIELD_BLOCK                      = 24,
    ANIM_READY_UNARMED                     = 25,
    ANIM_READY1H                           = 26,
    ANIM_READY2H                           = 27,
    ANIM_READY2HL                          = 28,
    ANIM_READY_BOW                         = 29,
    ANIM_DODGE                             = 30,
    ANIM_SPELL_PRECAST                     = 31,
    ANIM_SPELL_CAST                        = 32,
    ANIM_SPELL_CAST_AREA                   = 33,
    ANIM_NPC_WELCOME                       = 34,
    ANIM_NPC_GOODBYE                       = 35,
    ANIM_BLOCK                             = 36,
    ANIM_JUMP_START                        = 37,
    ANIM_JUMP                              = 38,
    ANIM_JUMP_END                          = 39,
    ANIM_FALL                              = 40,
    ANIM_SWIM_IDLE                         = 41,
    ANIM_SWIM                              = 42,
    ANIM_SWIM_LEFT                         = 43,
    ANIM_SWIM_RIGHT                        = 44,
    ANIM_SWIM_BACKWARDS                    = 45,
    ANIM_ATTACK_BOW                        = 46,
    ANIM_FIRE_BOW                          = 47,
    ANIM_READY_RIFLE                       = 48,
    ANIM_ATTACK_RIFLE                      = 49,
    ANIM_LOOT                              = 50,
    ANIM_READY_SPELL_DIRECTED              = 51,
    ANIM_READY_SPELL_OMNI                  = 52,
    ANIM_SPELL_CAST_DIRECTED               = 53,
    ANIM_SPELL_CAST_OMNI                   = 54,
    ANIM_BATTLE_ROAR                       = 55,
    ANIM_READY_ABILITY                     = 56,
    ANIM_SPECIAL1H                         = 57,
    ANIM_SPECIAL2H                         = 58,
    ANIM_SHIELD_BASH                       = 59,
    ANIM_EMOTE_TALK                        = 60,
    ANIM_EMOTE_EAT                         = 61,
    ANIM_EMOTE_WORK                        = 62,
    ANIM_EMOTE_USE_STANDING                = 63,
    ANIM_EMOTE_TALK_EXCLAMATION            = 64,
    ANIM_EMOTE_TALK_QUESTION               = 65,
    ANIM_EMOTE_BOW                         = 66,
    ANIM_EMOTE_WAVE                        = 67,
    ANIM_EMOTE_CHEER                       = 68,
    ANIM_EMOTE_DANCE                       = 69,
    ANIM_EMOTE_LAUGH                       = 70,
    ANIM_EMOTE_SLEEP                       = 71,
    ANIM_EMOTE_SIT_GROUND                  = 72,
    ANIM_EMOTE_RUDE                        = 73,
    ANIM_EMOTE_ROAR                        = 74,
    ANIM_EMOTE_KNEEL                       = 75,
    ANIM_EMOTE_KISS                        = 76,
    ANIM_EMOTE_CRY                         = 77,
    ANIM_EMOTE_CHICKEN                     = 78,
    ANIM_EMOTE_BEG                         = 79,
    ANIM_EMOTE_APPLAUD                     = 80,
    ANIM_EMOTE_SHOUT                       = 81,
    ANIM_EMOTE_FLEX                        = 82,
    ANIM_EMOTE_SHY                         = 83,
    ANIM_EMOTE_POINT                       = 84,
    ANIM_ATTACK1H_PIERCE                   = 85,
    ANIM_ATTACK2H_LOOSE_PIERCE             = 86,
    ANIM_ATTACK_OFF                        = 87,
    ANIM_ATTACK_OFF_PIERCE                 = 88,
    ANIM_SHEATHE                           = 89,
    ANIM_HIP_SHEATHE                       = 90,
    ANIM_MOUNT                             = 91,
    ANIM_RUN_RIGHT                         = 92,
    ANIM_RUN_LEFT                          = 93,
    ANIM_MOUNT_SPECIAL                     = 94,
    ANIM_KICK                              = 95,
    ANIM_SIT_GROUND_DOWN                   = 96,
    ANIM_SIT_GROUND                        = 97,
    ANIM_SIT_GROUND_UP                     = 98,
    ANIM_SLEEP_DOWN                        = 99,
    ANIM_SLEEP                             = 100,
    ANIM_SLEEP_UP                          = 101,
    ANIM_SIT_CHAIR_LOW                     = 102,
    ANIM_SIT_CHAIR_MED                     = 103,
    ANIM_SIT_CHAIR_HIGH                    = 104,
    ANIM_LOAD_BOW                          = 105,
    ANIM_LOAD_RIFLE                        = 106,
    ANIM_ATTACK_THROWN                     = 107,
    ANIM_READY_THROWN                      = 108,
    ANIM_HOLD_BOW                          = 109,
    ANIM_HOLD_RIFLE                        = 110,
    ANIM_HOLD_THROWN                       = 111,
    ANIM_LOAD_THROWN                       = 112,
    ANIM_EMOTE_SALUTE                      = 113,
    ANIM_KNEEL_START                       = 114,
    ANIM_KNEEL_LOOP                        = 115,
    ANIM_KNEEL_END                         = 116,
    ANIM_ATTACK_UNARMED_OFF                = 117,
    ANIM_SPECIAL_UNARMED                   = 118,
    ANIM_STEALTH_WALK                      = 119,
    ANIM_STEALTH_STAND                     = 120,
    ANIM_KNOCKDOWN                         = 121,
    ANIM_EATING_LOOP                       = 122,
    ANIM_USE_STANDING_LOOP                 = 123,
    ANIM_CHANNEL_CAST_DIRECTED             = 124,
    ANIM_CHANNEL_CAST_OMNI                 = 125,
    ANIM_WHIRLWIND                         = 126,
    ANIM_BIRTH                             = 127,
    ANIM_USE_STANDING_START                = 128,
    ANIM_USE_STANDING_END                  = 129,
    ANIM_CREATURE_SPECIAL                  = 130,
    ANIM_DROWN                             = 131,
    ANIM_DROWNED                           = 132,
    ANIM_FISHING_CAST                      = 133,
    ANIM_FISHING_LOOP                      = 134,
    ANIM_FLY                               = 135,
    ANIM_EMOTE_WORK_NO_SHEATHE             = 136,
    ANIM_EMOTE_STUN_NO_SHEATHE             = 137,
    ANIM_EMOTE_USE_STANDING_NO_SHEATHE     = 138,
    ANIM_SPELL_SLEEP_DOWN                  = 139,
    ANIM_SPELL_KNEEL_START                 = 140,
    ANIM_SPELL_KNEEL_LOOP                  = 141,
    ANIM_SPELL_KNEEL_END                   = 142,
    ANIM_SPRINT                            = 143,
    ANIM_IN_FIGHT                          = 144,
    ANIM_SPAWN                             = 145,
    ANIM_CLOSE                             = 146,
    ANIM_CLOSED                            = 147,
    ANIM_OPEN                              = 148,
    ANIM_OPENED                            = 149,
    ANIM_DESTROY                           = 150,
    ANIM_DESTROYED                         = 151,
    ANIM_REBUILD                           = 152,
    ANIM_CUSTOM_0                          = 153,
    ANIM_CUSTOM_1                          = 154,
    ANIM_CUSTOM_2                          = 155,
    ANIM_CUSTOM_3                          = 156,
    ANIM_DESPAWN                           = 157,
    ANIM_HOLD                              = 158,
    ANIM_DECAY                             = 159,
    ANIM_BOW_PULL                          = 160,
    ANIM_BOW_RELEASE                       = 161,
    ANIM_SHIP_START                        = 162,
    ANIM_SHIP_MOVING                       = 163,
    ANIM_SHIP_STOP                         = 164,
    ANIM_GROUP_ARROW                       = 165,
    ANIM_ARROW                             = 166,
    ANIM_CORPSE_ARROW                      = 167,
    ANIM_GUIDE_ARROW                       = 168,
    ANIM_SWAY                              = 169,
    ANIM_DRUID_CAT_POUNCE                  = 170,
    ANIM_DRUID_CAT_RIP                     = 171,
    ANIM_DRUID_CAT_RAKE                    = 172,
    ANIM_DRUID_CAT_RAVAGE                  = 173,
    ANIM_DRUID_CAT_CLAW                    = 174,
    ANIM_DRUID_CAT_COWER                   = 175,
    ANIM_DRUID_BEAR_SWIPE                  = 176,
    ANIM_DRUID_BEAR_BITE                   = 177,
    ANIM_DRUID_BEAR_MAUL                   = 178,
    ANIM_DRUID_BEAR_BASH                   = 179,
    ANIM_DRAGON_TAIL                       = 180,
    ANIM_DRAGON_STOMP                      = 181,
    ANIM_DRAGON_SPIT                       = 182,
    ANIM_DRAGON_SPIT_HOVER                 = 183,
    ANIM_DRAGON_SPIT_FLY                   = 184,
    ANIM_EMOTE_YES                         = 185,
    ANIM_EMOTE_NO                          = 186,
    ANIM_JUMP_LAND_RUN                     = 187,
    ANIM_LOOT_HOLD                         = 188,
    ANIM_LOOT_UP                           = 189,
    ANIM_STAND_HIGH                        = 190,
    ANIM_IMPACT                            = 191,
    ANIM_LIFTOFF                           = 192,
    ANIM_HOVER                             = 193,
    ANIM_SUCCUBUS_ENTICE                   = 194,
    ANIM_EMOTE_TRAIN                       = 195,
    ANIM_EMOTE_DEAD                        = 196,
    ANIM_EMOTE_DANCE_ONCE                  = 197,
    ANIM_DEFLECT                           = 198,
    ANIM_EMOTE_EAT_NO_SHEATHE              = 199,
    ANIM_LAND                              = 200,
    ANIM_SUBMERGE                          = 201,
    ANIM_SUBMERGED                         = 202,
    ANIM_CANNIBALIZE                       = 203,
    ANIM_ARROW_BIRTH                       = 204,
    ANIM_GROUP_ARROW_BIRTH                 = 205,
    ANIM_CORPSE_ARROW_BIRTH                = 206,
    ANIM_GUIDE_ARROW_BIRTH                 = 207,
    ANIM_EMOTE_TALK_NO_SHEATHE             = 208,
    ANIM_EMOTE_POINT_NO_SHEATHE            = 209,
    ANIM_EMOTE_SALUTE_NO_SHEATHE           = 210,
    ANIM_EMOTE_DANCE_SPECIAL               = 211,
    ANIM_MUTILATE                          = 212,
    ANIM_CUSTOM_SPELL_01                   = 213,
    ANIM_CUSTOM_SPELL_02                   = 214,
    ANIM_CUSTOM_SPELL_03                   = 215,
    ANIM_CUSTOM_SPELL_04                   = 216,
    ANIM_CUSTOM_SPELL_05                   = 217,
    ANIM_CUSTOM_SPELL_06                   = 218,
    ANIM_CUSTOM_SPELL_07                   = 219,
    ANIM_CUSTOM_SPELL_08                   = 220,
    ANIM_CUSTOM_SPELL_09                   = 221,
    ANIM_CUSTOM_SPELL_10                   = 222,
    ANIM_STEALTH_RUN                       = 223,
    ANIM_EMERGE                            = 224,
    ANIM_COWER                             = 225,
    ANIM_GRAB                              = 226,
    ANIM_GRAB_CLOSED                       = 227,
    ANIM_GRAB_THROWN                       = 228,
    ANIM_FLY_STAND                         = 229,
    ANIM_FLY_DEATH                         = 230,
    ANIM_FLY_SPELL                         = 231,
    ANIM_FLY_STOP                          = 232,
    ANIM_FLY_WALK                          = 233,
    ANIM_FLY_RUN                           = 234,
    ANIM_FLY_DEAD                          = 235,
    ANIM_FLY_RISE                          = 236,
    ANIM_FLY_STAND_WOUND                   = 237,
    ANIM_FLY_COMBAT_WOUND                  = 238,
    ANIM_FLY_COMBAT_CRITICAL               = 239,
    ANIM_FLY_SHUFFLE_LEFT                  = 240,
    ANIM_FLY_SHUFFLE_RIGHT                 = 241,
    ANIM_FLY_WALK_BACKWARDS                = 242,
    ANIM_FLY_STUN                          = 243,
    ANIM_FLY_HANDS_CLOSED                  = 244,
    ANIM_FLY_ATTACK_UNARMED                = 245,
    ANIM_FLY_ATTACK1H                      = 246,
    ANIM_FLY_ATTACK2H                      = 247,
    ANIM_FLY_ATTACK2HL                     = 248,
    ANIM_FLY_PARRY_UNARMED                 = 249,
    ANIM_FLY_PARRY1H                       = 250,
    ANIM_FLY_PARRY2H                       = 251,
    ANIM_FLY_PARRY2HL                      = 252,
    ANIM_FLY_SHIELD_BLOCK                  = 253,
    ANIM_FLY_READY_UNARMED                 = 254,
    ANIM_FLY_READY1H                       = 255,
    ANIM_FLY_READY2H                       = 256,
    ANIM_FLY_READY2HL                      = 257,
    ANIM_FLY_READY_BOW                     = 258,
    ANIM_FLY_DODGE                         = 259,
    ANIM_FLY_SPELL_PRECAST                 = 260,
    ANIM_FLY_SPELL_CAST                    = 261,
    ANIM_FLY_SPELL_CAST_AREA               = 262,
    ANIM_FLY_NPC_WELCOME                   = 263,
    ANIM_FLY_NPC_GOODBYE                   = 264,
    ANIM_FLY_BLOCK                         = 265,
    ANIM_FLY_JUMP_START                    = 266,
    ANIM_FLY_JUMP                          = 267,
    ANIM_FLY_JUMP_END                      = 268,
    ANIM_FLY_FALL                          = 269,
    ANIM_FLY_SWIM_IDLE                     = 270,
    ANIM_FLY_SWIM                          = 271,
    ANIM_FLY_SWIM_LEFT                     = 272,
    ANIM_FLY_SWIM_RIGHT                    = 273,
    ANIM_FLY_SWIM_BACKWARDS                = 274,
    ANIM_FLY_ATTACK_BOW                    = 275,
    ANIM_FLY_FIRE_BOW                      = 276,
    ANIM_FLY_READY_RIFLE                   = 277,
    ANIM_FLY_ATTACK_RIFLE                  = 278,
    ANIM_FLY_LOOT                          = 279,
    ANIM_FLY_READY_SPELL_DIRECTED          = 280,
    ANIM_FLY_READY_SPELL_OMNI              = 281,
    ANIM_FLY_SPELL_CAST_DIRECTED           = 282,
    ANIM_FLY_SPELL_CAST_OMNI               = 283,
    ANIM_FLY_SPELL_BATTLE_ROAR             = 284,
    ANIM_FLY_READY_ABILITY                 = 285,
    ANIM_FLY_SPECIAL1H                     = 286,
    ANIM_FLY_SPECIAL2H                     = 287,
    ANIM_FLY_SHIELD_BASH                   = 288,
    ANIM_FLY_EMOTE_TALK                    = 289,
    ANIM_FLY_EMOTE_EAT                     = 290,
    ANIM_FLY_EMOTE_WORK                    = 291,
    ANIM_FLY_USE_STANDING                  = 292,
    ANIM_FLY_EMOTE_TALK_EXCLAMATION        = 293,
    ANIM_FLY_EMOTE_TALK_QUESTION           = 294,
    ANIM_FLY_EMOTE_BOW                     = 295,
    ANIM_FLY_EMOTE_WAVE                    = 296,
    ANIM_FLY_EMOTE_CHEER                   = 297,
    ANIM_FLY_EMOTE_DANCE                   = 298,
    ANIM_FLY_EMOTE_LAUGH                   = 299,
    ANIM_FLY_EMOTE_SLEEP                   = 300,
    ANIM_FLY_EMOTE_SIT_GROUND              = 301,
    ANIM_FLY_EMOTE_RUDE                    = 302,
    ANIM_FLY_EMOTE_ROAR                    = 303,
    ANIM_FLY_EMOTE_KNEEL                   = 304,
    ANIM_FLY_EMOTE_KISS                    = 305,
    ANIM_FLY_EMOTE_CRY                     = 306,
    ANIM_FLY_EMOTE_CHICKEN                 = 307,
    ANIM_FLY_EMOTE_BEG                     = 308,
    ANIM_FLY_EMOTE_APPLAUD                 = 309,
    ANIM_FLY_EMOTE_SHOUT                   = 310,
    ANIM_FLY_EMOTE_FLEX                    = 311,
    ANIM_FLY_EMOTE_SHY                     = 312,
    ANIM_FLY_EMOTE_POINT                   = 313,
    ANIM_FLY_ATTACK1H_PIERCE               = 314,
    ANIM_FLY_ATTACK2H_LOOSE_PIERCE         = 315,
    ANIM_FLY_ATTACK_OFF                    = 316,
    ANIM_FLY_ATTACK_OFF_PIERCE             = 317,
    ANIM_FLY_SHEATH                        = 318,
    ANIM_FLY_HIP_SHEATH                    = 319,
    ANIM_FLY_MOUNT                         = 320,
    ANIM_FLY_RUN_RIGHT                     = 321,
    ANIM_FLY_RUN_LEFT                      = 322,
    ANIM_FLY_MOUNT_SPECIAL                 = 323,
    ANIM_FLY_KICK                          = 324,
    ANIM_FLY_SIT_GROUND_DOWN               = 325,
    ANIM_FLY_SIT_GROUND                    = 326,
    ANIM_FLY_SIT_GROUND_UP                 = 327,
    ANIM_FLY_SLEEP_DOWN                    = 328,
    ANIM_FLY_SLEEP                         = 329,
    ANIM_FLY_SLEEP_UP                      = 330,
    ANIM_FLY_SIT_CHAIR_LOW                 = 331,
    ANIM_FLY_SIT_CHAIR_MED                 = 332,
    ANIM_FLY_SIT_CHAIR_HIGH                = 333,
    ANIM_FLY_LOAD_BOW                      = 334,
    ANIM_FLY_LOAD_RIFLE                    = 335,
    ANIM_FLY_ATTACK_THROWN                 = 336,
    ANIM_FLY_READY_THROWN                  = 337,
    ANIM_FLY_HOLD_BOW                      = 338,
    ANIM_FLY_HOLD_RIFLE                    = 339,
    ANIM_FLY_HOLD_THROWN                   = 340,
    ANIM_FLY_LOAD_THROWN                   = 341,
    ANIM_FLY_EMOTE_SALUTE                  = 342,
    ANIM_FLY_KNEEL_START                   = 343,
    ANIM_FLY_KNEEL_LOOP                    = 344,
    ANIM_FLY_KNEEL_END                     = 345,
    ANIM_FLY_ATTACK_UNARMED_OFF            = 346,
    ANIM_FLY_SPECIAL_UNARMED               = 347,
    ANIM_FLY_STEALTH_WALK                  = 348,
    ANIM_FLY_STEALTH_STAND                 = 349,
    ANIM_FLY_KNOCKDOWN                     = 350,
    ANIM_FLY_EATING_LOOP                   = 351,
    ANIM_FLY_USE_STANDING_LOOP             = 352,
    ANIM_FLY_CHANNEL_CAST_DIRECTED         = 353,
    ANIM_FLY_CHANNEL_CAST_OMNI             = 354,
    ANIM_FLY_WHIRLWIND                     = 355,
    ANIM_FLY_BIRTH                         = 356,
    ANIM_FLY_USE_STANDING_START            = 357,
    ANIM_FLY_USE_STANDING_END              = 358,
    ANIM_FLY_CREATURE_SPECIAL              = 359,
    ANIM_FLY_DROWN                         = 360,
    ANIM_FLY_DROWNED                       = 361,
    ANIM_FLY_FISHING_CAST                  = 362,
    ANIM_FLY_FISHING_LOOP                  = 363,
    ANIM_FLY_FLY                           = 364,
    ANIM_FLY_EMOTE_WORK_NO_SHEATHE         = 365,
    ANIM_FLY_EMOTE_STUN_NO_SHEATHE         = 366,
    ANIM_FLY_EMOTE_USE_STANDING_NO_SHEATHE = 367,
    ANIM_FLY_SPELL_SLEEP_DOWN              = 368,
    ANIM_FLY_SPELL_KNEEL_START             = 369,
    ANIM_FLY_SPELL_KNEEL_LOOP              = 370,
    ANIM_FLY_SPELL_KNEEL_END               = 371,
    ANIM_FLY_SPRINT                        = 372,
    ANIM_FLY_IN_FLIGHT                     = 373,
    ANIM_FLY_SPAWN                         = 374,
    ANIM_FLY_CLOSE                         = 375,
    ANIM_FLY_CLOSED                        = 376,
    ANIM_FLY_OPEN                          = 377,
    ANIM_FLY_OPENED                        = 378,
    ANIM_FLY_DESTROY                       = 379,
    ANIM_FLY_DESTROYED                     = 380,
    ANIM_FLY_REBUILD                       = 381,
    ANIM_FLY_CUSTOM_0                      = 382,
    ANIM_FLY_CUSTOM_1                      = 383,
    ANIM_FLY_CUSTOM_2                      = 384,
    ANIM_FLY_CUSTOM_3                      = 385,
    ANIM_FLY_DESPAWN                       = 386,
    ANIM_FLY_HOLD                          = 387,
    ANIM_FLY_DECAY                         = 388,
    ANIM_FLY_BOW_PULL                      = 389,
    ANIM_FLY_BOW_RELEASE                   = 390,
    ANIM_FLY_SHIP_START                    = 391,
    ANIM_FLY_SHIP_MOVING                   = 392,
    ANIM_FLY_SHIP_STOP                     = 393,
    ANIM_FLY_GROUP_ARROW                   = 394,
    ANIM_FLY_ARROW                         = 395,
    ANIM_FLY_CORPSE_ARROW                  = 396,
    ANIM_FLY_GUIDE_ARROW                   = 397,
    ANIM_FLY_SWAY                          = 398,
    ANIM_FLY_DRUID_CAT_POUNCE              = 399,
    ANIM_FLY_DRUID_CAT_RIP                 = 400,
    ANIM_FLY_DRUID_CAT_RAKE                = 401,
    ANIM_FLY_DRUID_CAT_RAVAGE              = 402,
    ANIM_FLY_DRUID_CAT_CLAW                = 403,
    ANIM_FLY_DRUID_CAT_COWER               = 404,
    ANIM_FLY_DRUID_BEAR_SWIPE              = 405,
    ANIM_FLY_DRUID_BEAR_BITE               = 406,
    ANIM_FLY_DRUID_BEAR_MAUL               = 407,
    ANIM_FLY_DRUID_BEAR_BASH               = 408,
    ANIM_FLY_DRAGON_TAIL                   = 409,
    ANIM_FLY_DRAGON_STOMP                  = 410,
    ANIM_FLY_DRAGON_SPIT                   = 411,
    ANIM_FLY_DRAGON_SPIT_HOVER             = 412,
    ANIM_FLY_DRAGON_SPIT_FLY               = 413,
    ANIM_FLY_EMOTE_YES                     = 414,
    ANIM_FLY_EMOTE_NO                      = 415,
    ANIM_FLY_JUMP_LAND_RUN                 = 416,
    ANIM_FLY_LOOT_HOLD                     = 417,
    ANIM_FLY_LOOT_UP                       = 418,
    ANIM_FLY_STAND_HIGH                    = 419,
    ANIM_FLY_IMPACT                        = 420,
    ANIM_FLY_LIFTOFF                       = 421,
    ANIM_FLY_HOVER                         = 422,
    ANIM_FLY_SUCCUBUS_ENTICE               = 423,
    ANIM_FLY_EMOTE_TRAIN                   = 424,
    ANIM_FLY_EMOTE_DEAD                    = 425,
    ANIM_FLY_EMOTE_DANCE_ONCE              = 426,
    ANIM_FLY_DEFLECT                       = 427,
    ANIM_FLY_EMOTE_EAT_NO_SHEATHE          = 428,
    ANIM_FLY_LAND                          = 429,
    ANIM_FLY_SUBMERGE                      = 430,
    ANIM_FLY_SUBMERGED                     = 431,
    ANIM_FLY_CANNIBALIZE                   = 432,
    ANIM_FLY_ARROW_BIRTH                   = 433,
    ANIM_FLY_GROUP_ARROW_BIRTH             = 434,
    ANIM_FLY_CORPSE_ARROW_BIRTH            = 435,
    ANIM_FLY_GUIDE_ARROW_BIRTH             = 436,
    ANIM_FLY_EMOTE_TALK_NO_SHEATHE         = 437,
    ANIM_FLY_EMOTE_POINT_NO_SHEATHE        = 438,
    ANIM_FLY_EMOTE_SALUTE_NO_SHEATHE       = 439,
    ANIM_FLY_EMOTE_DANCE_SPECIAL           = 440,
    ANIM_FLY_MUTILATE                      = 441,
    ANIM_FLY_CUSTOM_SPELL_01               = 442,
    ANIM_FLY_CUSTOM_SPELL_02               = 443,
    ANIM_FLY_CUSTOM_SPELL_03               = 444,
    ANIM_FLY_CUSTOM_SPELL_04               = 445,
    ANIM_FLY_CUSTOM_SPELL_05               = 446,
    ANIM_FLY_CUSTOM_SPELL_06               = 447,
    ANIM_FLY_CUSTOM_SPELL_07               = 448,
    ANIM_FLY_CUSTOM_SPELL_08               = 449,
    ANIM_FLY_CUSTOM_SPELL_09               = 450,
    ANIM_FLY_CUSTOM_SPELL_10               = 451,
    ANIM_FLY_STEALTH_RUN                   = 452,
    ANIM_FLY_EMERGE                        = 453,
    ANIM_FLY_COWER                         = 454,
    ANIM_FLY_GRAB                          = 455,
    ANIM_FLY_GRAB_CLOSED                   = 456,
    ANIM_FLY_GRAB_THROWN                   = 457,
    ANIM_TO_FLY                            = 458,
    ANIM_TO_HOVER                          = 459,
    ANIM_TO_GROUND                         = 460,
    ANIM_FLY_TO_FLY                        = 461,
    ANIM_FLY_TO_HOVER                      = 462,
    ANIM_FLY_TO_GROUND                     = 463,
    ANIM_SETTLE                            = 464,
    ANIM_FLY_SETTLE                        = 465,
    ANIM_DEATH_START                       = 466,
    ANIM_DEATH_LOOP                        = 467,
    ANIM_DEATH_END                         = 468,
    ANIM_FLY_DEATH_START                   = 469,
    ANIM_FLY_DEATH_LOOP                    = 470,
    ANIM_FLY_DEATH_END                     = 471,
    ANIM_DEATH_END_HOLD                    = 472,
    ANIM_FLY_DEATH_END_HOLD                = 473,
    ANIM_STRANGULATE                       = 474,
    ANIM_FLY_STRANGULATE                   = 475,
    ANIM_READY_JOUST                       = 476,
    ANIM_LOAD_JOUST                        = 477,
    ANIM_HOLD_JOUST                        = 478,
    ANIM_FLY_READY_JOUST                   = 479,
    ANIM_FLY_LOAD_JOUST                    = 480,
    ANIM_FLY_HOLD_JOUST                    = 481,
    ANIM_ATTACK_JOUST                      = 482,
    ANIM_FLY_ATTACK_JOUST                  = 483,
    ANIM_RECLINED_MOUNT                    = 484,
    ANIM_FLY_RECLINED_MOUNT                = 485,
    ANIM_TO_ALTERED                        = 486,
    ANIM_FROM_ALTERED                      = 487,
    ANIM_FLY_TO_ALTERED                    = 488,
    ANIM_FLY_FROM_ALTERED                  = 489,
    ANIM_IN_STOCKS                         = 490,
    ANIM_FLY_IN_STOCKS                     = 491,
    ANIM_VEHICLE_GRAB                      = 492,
    ANIM_VEHICLE_THROW                     = 493,
    ANIM_FLY_VEHICLE_GRAB                  = 494,
    ANIM_FLY_VEHICLE_THROW                 = 495,
    ANIM_TO_ALTERED_POST_SWAP              = 496,
    ANIM_FROM_ALTERED_POST_SWAP            = 497,
    ANIM_FLY_TO_ALTERED_POST_SWAP          = 498,
    ANIM_FLY_FROM_ALTERED_POST_SWAP        = 499,
    ANIM_RECLINED_MOUNT_PASSENGER          = 500,
    ANIM_FLY_RECLINED_MOUNT_PASSENGER      = 501,
    ANIM_CARRY2H                           = 502,
    ANIM_CARRIED2H                         = 503,
    ANIM_FLY_CARRY2H                       = 504,
    ANIM_FLY_CARRIED2H                     = 505,
    ANIM_EMOTE_SNIFF                       = 506,
    ANIM_EMOTE_FLY_SNIFF                   = 507,
    ANIM_ATTACK_FIST1H                     = 508,
    ANIM_FLY_ATTACK_FIST1H                 = 509,
    ANIM_ATTACK_FIST_1H_OFF                = 510,
    ANIM_FLY_ATTACK_FIST_1H_OFF            = 511,
    ANIM_PARRY_FIST1H                      = 512,
    ANIM_FLY_PARRY_FIST1H                  = 513,
    ANIM_READY_FIST1H                      = 514,
    ANIM_FLY_READY_FIST1H                  = 515,
    ANIM_SPECIAL_FIST1H                    = 516,
    ANIM_FLY_SPECIAL_FIST1H                = 517,
    ANIM_EMOTE_READ_START                  = 518,
    ANIM_FLY_EMOTE_READ_START              = 519,
    ANIM_EMOTE_READ_LOOP                   = 520,
    ANIM_FLY_EMOTE_READ_LOOP               = 521,
    ANIM_EMOTE_READ_END                    = 522,
    ANIM_FLY_EMOTE_READ_END                = 523,
    ANIM_SWIM_RUN                          = 524,
    ANIM_FLY_SWIM_RUN                      = 525,
    ANIM_SWIM_WALK                         = 526,
    ANIM_FLY_SWIM_WALK                     = 527,
    ANIM_SWIM_WALK_BACKWARDS               = 528,
    ANIM_FLY_SWIM_WALK_BACKWARDS           = 529,
    ANIM_SWIM_SPRINT                       = 530,
    ANIM_FLY_SWIM_SPRINT                   = 531,
    ANIM_MOUNT_SWIM_IDLE                   = 532,
    ANIM_FLY_MOUNT_SWIM_IDLE               = 533,
    ANIM_MOUNT_SWIM_BACKWARDS              = 534,
    ANIM_FLY_MOUNT_SWIM_BACKWARDS          = 535,
    ANIM_MOUNT_SWIM_LEFT                   = 536,
    ANIM_FLY_MOUNT_SWIM_LEFT               = 537,
    ANIM_MOUNT_SWIM_RIGHT                  = 538,
    ANIM_FLY_MOUNT_SWIM_RIGHT              = 539,
    ANIM_MOUNT_SWIM_RUN                    = 540,
    ANIM_FLY_MOUNT_SWIM_RUN                = 541,
    ANIM_MOUNT_SWIM_SPRINT                 = 542,
    ANIM_FLY_MOUNT_SWIM_SPRINT             = 543,
    ANIM_MOUNT_SWIM_WALK                   = 544,
    ANIM_FLY_MOUNT_SWIM_WALK               = 545,
    ANIM_MOUNT_SWIM_WALK_BACKWARDS         = 546,
    ANIM_FLY_MOUNT_SWIM_WALK_BACKWARDS     = 547,
    ANIM_MOUNT_FLIGHT_IDLE                 = 548,
    ANIM_FLY_MOUNT_FLIGHT_IDLE             = 549,
    ANIM_MOUNT_FLIGHT_BACKWARDS            = 550,
    ANIM_FLY_MOUNT_FLIGHT_BACKWARDS        = 551,
    ANIM_MOUNT_FLIGHT_LEFT                 = 552,
    ANIM_FLY_MOUNT_FLIGHT_LEFT             = 553,
    ANIM_MOUNT_FLIGHT_RIGHT                = 554,
    ANIM_FLY_MOUNT_FLIGHT_RIGHT            = 555,
    ANIM_MOUNT_FLIGHT_RUN                  = 556,
    ANIM_FLY_MOUNT_FLIGHT_RUN              = 557,
    ANIM_MOUNT_FLIGHT_SPRINT               = 558,
    ANIM_FLY_MOUNT_FLIGHT_SPRINT           = 559,
    ANIM_MOUNT_FLIGHT_WALK                 = 560,
    ANIM_FLY_MOUNT_FLIGHT_WALK             = 561,
    ANIM_MOUNT_FLIGHT_WALK_BACKWARDS       = 562,
    ANIM_FLY_MOUNT_FLIGHT_WALK_BACKWARDS   = 563,
    ANIM_MOUNT_FLIGHT_START                = 564,
    ANIM_FLY_MOUNT_FLIGHT_START            = 565,
    ANIM_MOUNT_SWIM_START                  = 566,
    ANIM_FLY_MOUNT_SWIM_START              = 567,
    ANIM_MOUNT_SWIM_LAND                   = 568,
    ANIM_FLY_MOUNT_SWIM_LAND               = 569,
    ANIM_MOUNT_SWIM_LAND_RUN               = 570,
    ANIM_FLY_MOUNT_SWIM_LAND_RUN           = 571,
    ANIM_MOUNT_FLIGHT_LAND                 = 572,
    ANIM_FLY_MOUNT_FLIGHT_LAND             = 573,
    ANIM_MOUNT_FLIGHT_LAND_RUN             = 574,
    ANIM_FLY_MOUNT_FLIGHT_LAND_RUN         = 575,
    ANIM_READY_BLOW_DART                   = 576,
    ANIM_FLY_READY_BLOW_DART               = 577,
    ANIM_LOAD_BLOW_DART                    = 578,
    ANIM_FLY_LOAD_BLOW_DART                = 579,
    ANIM_HOLD_BLOW_DART                    = 580,
    ANIM_FLY_HOLD_BLOW_DART                = 581,
    ANIM_ATTACK_BLOW_DART                  = 582,
    ANIM_FLY_ATTACK_BLOW_DART              = 583,
    ANIM_CARRIAGE_MOUNT                    = 584,
    ANIM_FLY_CARRIAGE_MOUNT                = 585,
    ANIM_CARRIAGE_PASSENGER_MOUNT          = 586,
    ANIM_FLY_CARRIAGE_PASSENGER_MOUNT      = 587,
    ANIM_CARRIAGE_MOUNT_ATTACK             = 588,
    ANIM_FLY_CARRIAGE_MOUNT_ATTACK         = 589,
    ANIM_BARTENDER_STAND                   = 590,
    ANIM_FLY_BARTENDER_STAND               = 591,
    ANIM_BARTENDER_WALK                    = 592,
    ANIM_FLY_BARTENDER_WALK                = 593,
    ANIM_BARTENDER_RUN                     = 594,
    ANIM_FLY_BARTENDER_RUN                 = 595,
    ANIM_BARTENDER_SHUFFLE_LEFT            = 596,
    ANIM_FLY_BARTENDER_SHUFFLE_LEFT        = 597,
    ANIM_BARTENDER_SHUFFLE_RIGHT           = 598,
    ANIM_FLY_BARTENDER_SHUFFLE_RIGHT       = 599,
    ANIM_BARTENDER_EMOTE_TALK              = 600,
    ANIM_FLY_BARTENDER_EMOTE_TALK          = 601,
    ANIM_BARTENDER_EMOTE_POINT             = 602,
    ANIM_FLY_BARTENDER_EMOTE_POINT         = 603,
    ANIM_BARMAID_STAND                     = 604,
    ANIM_FLY_BARMAID_STAND                 = 605,
    ANIM_BARMAID_WALK                      = 606,
    ANIM_FLY_BARMAID_WALK                  = 607,
    ANIM_BARMAID_RUN                       = 608,
    ANIM_FLY_BARMAID_RUN                   = 609,
    ANIM_BARMAID_SHUFFLE_LEFT              = 610,
    ANIM_FLY_BARMAID_SHUFFLE_LEFT          = 611,
    ANIM_BARMAID_SHUFFLE_RIGHT             = 612,
    ANIM_FLY_BARMAID_SHUFFLE_RIGHT         = 613,
    ANIM_BARMAID_EMOTE_TALK                = 614,
    ANIM_FLY_BARMAID_EMOTE_TALK            = 615,
    ANIM_BARMAID_EMOTE_POINT               = 616,
    ANIM_FLY_BARMAID_EMOTE_POINT           = 617,
    ANIM_MOUNT_SELF_IDLE                   = 618,
    ANIM_FLY_MOUNT_SELF_IDLE               = 619,
    ANIM_MOUNT_SELF_WALK                   = 620,
    ANIM_FLY_MOUNT_SELF_WALK               = 621,
    ANIM_MOUNT_SELF_RUN                    = 622,
    ANIM_FLY_MOUNT_SELF_RUN                = 623,
    ANIM_MOUNT_SELF_SPRINT                 = 624,
    ANIM_FLY_MOUNT_SELF_SPRINT             = 625,
    ANIM_MOUNT_SELF_RUN_LEFT               = 626,
    ANIM_FLY_MOUNT_SELF_RUN_LEFT           = 627,
    ANIM_MOUNT_SELF_RUN_RIGHT              = 628,
    ANIM_FLY_MOUNT_SELF_RUN_RIGHT          = 629,
    ANIM_MOUNT_SELF_SHUFFLE_LEFT           = 630,
    ANIM_FLY_MOUNT_SELF_SHUFFLE_LEFT       = 631,
    ANIM_MOUNT_SELF_SHUFFLE_RIGHT          = 632,
    ANIM_FLY_MOUNT_SELF_SHUFFLE_RIGHT      = 633,
    ANIM_MOUNT_SELF_WALK_BACKWARDS         = 634,
    ANIM_FLY_MOUNT_SELF_WALK_BACKWARDS     = 635,
    ANIM_MOUNT_SELF_SPECIAL                = 636,
    ANIM_FLY_MOUNT_SELF_SPECIAL            = 637,
    ANIM_MOUNT_SELF_JUMP                   = 638,
    ANIM_FLY_MOUNT_SELF_JUMP               = 639,
    ANIM_MOUNT_SELF_JUMP_START             = 640,
    ANIM_FLY_MOUNT_SELF_JUMP_START         = 641,
    ANIM_MOUNT_SELF_JUMP_END               = 642,
    ANIM_FLY_MOUNT_SELF_JUMP_END           = 643,
    ANIM_MOUNT_SELF_JUMP_LAND_RUN          = 644,
    ANIM_FLY_MOUNT_SELF_JUMP_LAND_RUN      = 645,
    ANIM_MOUNT_SELF_START                  = 646,
    ANIM_FLY_MOUNT_SELF_START              = 647,
    ANIM_MOUNT_SELF_FALL                   = 648,
    ANIM_FLY_MOUNT_SELF_FALL               = 649,
    ANIM_STORMSTRIKE                       = 650,
    ANIM_FLY_STORMSTRIKE                   = 651,
    ANIM_READY_JOUST_NO_SHEATHE            = 652,
    ANIM_FLY_READY_JOUST_NO_SHEATHE        = 653,
    ANIM_SLAM                              = 654,
    ANIM_FLY_SLAM                          = 655,
    ANIM_DEATH_STRIKE                      = 656,
    ANIM_FLY_DEATH_STRIKE                  = 657,
    ANIM_SWIM_ATTACK_UNARMED               = 658,
    ANIM_FLY_SWIM_ATTACK_UNARMED           = 659
};

enum LockKeyType
{
    LOCK_KEY_NONE  = 0,
    LOCK_KEY_ITEM  = 1,
    LOCK_KEY_SKILL = 2,
    LOCK_KEY_SPELL = 3
};

enum LockType
{
    LOCKTYPE_PICKLOCK              = 1,
    LOCKTYPE_HERBALISM             = 2,
    LOCKTYPE_MINING                = 3,
    LOCKTYPE_DISARM_TRAP           = 4,
    LOCKTYPE_OPEN                  = 5,
    LOCKTYPE_TREASURE              = 6,
    LOCKTYPE_CALCIFIED_ELVEN_GEMS  = 7,
    LOCKTYPE_CLOSE                 = 8,
    LOCKTYPE_ARM_TRAP              = 9,
    LOCKTYPE_QUICK_OPEN            = 10,
    LOCKTYPE_QUICK_CLOSE           = 11,
    LOCKTYPE_OPEN_TINKERING        = 12,
    LOCKTYPE_OPEN_KNEELING         = 13,
    LOCKTYPE_OPEN_ATTACKING        = 14,
    LOCKTYPE_GAHZRIDIAN            = 15,
    LOCKTYPE_BLASTING              = 16,
    LOCKTYPE_SLOW_OPEN             = 17,
    LOCKTYPE_SLOW_CLOSE            = 18,
    LOCKTYPE_FISHING               = 19,
    LOCKTYPE_INSCRIPTION           = 20,
    LOCKTYPE_OPEN_FROM_VEHICLE     = 21,
    LOCKTYPE_ARCHAEOLOGY           = 22,
};

// this is important type for npcs!
enum TrainerType
{
    TRAINER_TYPE_CLASS             = 0,
};

// CreatureType.dbc
enum CreatureType
{
    CREATURE_TYPE_BEAST            = 1,
    CREATURE_TYPE_DRAGONKIN        = 2,
    CREATURE_TYPE_DEMON            = 3,
    CREATURE_TYPE_ELEMENTAL        = 4,
    CREATURE_TYPE_GIANT            = 5,
    CREATURE_TYPE_UNDEAD           = 6,
    CREATURE_TYPE_HUMANOID         = 7,
    CREATURE_TYPE_CRITTER          = 8,
    CREATURE_TYPE_MECHANICAL       = 9,
    CREATURE_TYPE_NOT_SPECIFIED    = 10,
    CREATURE_TYPE_TOTEM            = 11,
    CREATURE_TYPE_NON_COMBAT_PET   = 12,
    CREATURE_TYPE_GAS_CLOUD        = 13
};

uint32 const CREATURE_TYPEMASK_DEMON_OR_UNDEAD = (1 << (CREATURE_TYPE_DEMON-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD = (1 << (CREATURE_TYPE_HUMANOID-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_MECHANICAL_OR_ELEMENTAL = (1 << (CREATURE_TYPE_MECHANICAL-1)) | (1 << (CREATURE_TYPE_ELEMENTAL-1));

// CreatureFamily.dbc
enum CreatureFamily
{
    CREATURE_FAMILY_NONE                = 0,
    CREATURE_FAMILY_WOLF                = 1,
    CREATURE_FAMILY_CAT                 = 2,
    CREATURE_FAMILY_SPIDER              = 3,
    CREATURE_FAMILY_BEAR                = 4,
    CREATURE_FAMILY_BOAR                = 5,
    CREATURE_FAMILY_CROCOLISK           = 6,
    CREATURE_FAMILY_CARRION_BIRD        = 7,
    CREATURE_FAMILY_CRAB                = 8,
    CREATURE_FAMILY_GORILLA             = 9,
    CREATURE_FAMILY_HORSE_CUSTOM        = 10,   // Does not exist in DBC but used for horse like beasts in DB
    CREATURE_FAMILY_RAPTOR              = 11,
    CREATURE_FAMILY_TALLSTRIDER         = 12,
    CREATURE_FAMILY_FELHUNTER           = 15,
    CREATURE_FAMILY_VOIDWALKER          = 16,
    CREATURE_FAMILY_SUCCUBUS            = 17,
    CREATURE_FAMILY_DOOMGUARD           = 19,
    CREATURE_FAMILY_SCORPID             = 20,
    CREATURE_FAMILY_TURTLE              = 21,
    CREATURE_FAMILY_IMP                 = 23,
    CREATURE_FAMILY_BAT                 = 24,
    CREATURE_FAMILY_HYENA               = 25,
    CREATURE_FAMILY_BIRD_OF_PREY        = 26,
    CREATURE_FAMILY_WIND_SERPENT        = 27,
    CREATURE_FAMILY_REMOTE_CONTROL      = 28,
    CREATURE_FAMILY_FELGUARD            = 29,
    CREATURE_FAMILY_DRAGONHAWK          = 30,
    CREATURE_FAMILY_RAVAGER             = 31,
    CREATURE_FAMILY_WARP_STALKER        = 32,
    CREATURE_FAMILY_SPOREBAT            = 33,
    CREATURE_FAMILY_NETHER_RAY          = 34,
    CREATURE_FAMILY_SERPENT             = 35,
    CREATURE_FAMILY_MOTH                = 37,
    CREATURE_FAMILY_CHIMAERA            = 38,
    CREATURE_FAMILY_DEVILSAUR           = 39,
    CREATURE_FAMILY_GHOUL               = 40,
    CREATURE_FAMILY_SILITHID            = 41,
    CREATURE_FAMILY_WORM                = 42,
    CREATURE_FAMILY_RHINO               = 43,
    CREATURE_FAMILY_WASP                = 44,
    CREATURE_FAMILY_CORE_HOUND          = 45,
    CREATURE_FAMILY_SPIRIT_BEAST        = 46,
    CREATURE_FAMILY_WATER_ELEMENTAL     = 49,
    CREATURE_FAMILY_FOX                 = 50,
    CREATURE_FAMILY_MONKEY              = 51,
    CREATURE_FAMILY_DOG                 = 52,
    CREATURE_FAMILY_BEETLE              = 53,
    CREATURE_FAMILY_SHALE_SPIDER        = 55,
    CREATURE_FAMILY_ZOMBIE              = 56,
    CREATURE_FAMILY_BEETLE_OLD          = 57,
    CREATURE_FAMILY_SILITHID_2          = 59,
    CREATURE_FAMILY_WASP_2              = 66,
    CREATURE_FAMILY_HYDRA               = 68,
};

enum CreatureTypeFlags
{
    CREATURE_TYPE_FLAG_TAMEABLE_PET                         = 0x00000001,   // Makes the mob tameable (must also be a beast and have family set)
    CREATURE_TYPE_FLAG_GHOST_VISIBLE                        = 0x00000002,   // Creature are also visible for not alive player. Allow gossip interaction if npcflag allow?
    CREATURE_TYPE_FLAG_BOSS_MOB                             = 0x00000004,   // Changes creature's visible level to "??" in the creature's portrait - Immune Knockback.
    CREATURE_TYPE_FLAG_DO_NOT_PLAY_WOUND_PARRY_ANIMATION    = 0x00000008,
    CREATURE_TYPE_FLAG_HIDE_FACTION_TOOLTIP                 = 0x00000010,
    CREATURE_TYPEFLAGS_UNK5                                 = 0x00000020,   // Sound related
    CREATURE_TYPE_FLAG_SPELL_ATTACKABLE                     = 0x00000040,
    CREATURE_TYPE_FLAG_CAN_INTERACT_WHILE_DEAD              = 0x00000080,   // Player can interact with the creature if its dead (not player dead)
    CREATURE_TYPE_FLAG_HERB_SKINNING_SKILL                  = 0x00000100,   // Can be looted by herbalist
    CREATURE_TYPE_FLAG_MINING_SKINNING_SKILL                = 0x00000200,   // Can be looted by miner
    CREATURE_TYPE_FLAG_DO_NOT_LOG_DEATH                     = 0x00000400,   // Death event will not show up in combat log
    CREATURE_TYPE_FLAG_MOUNTED_COMBAT_ALLOWED               = 0x00000800,   // Creature can remain mounted when entering combat
    CREATURE_TYPE_FLAG_CAN_ASSIST                           = 0x00001000,   // ? Can aid any player in combat if in range?
    CREATURE_TYPE_FLAG_IS_PET_BAR_USED                      = 0x00002000,
    CREATURE_TYPE_FLAG_MASK_UID                             = 0x00004000,
    CREATURE_TYPE_FLAG_ENGINEERING_SKINNING_SKILL           = 0x00008000,   // Can be looted by engineer
    CREATURE_TYPE_FLAG_EXOTIC_PET                           = 0x00010000,   // Can be tamed by hunter as exotic pet
    CREATURE_TYPE_FLAG_USE_DEFAULT_COLLISION_BOX            = 0x00020000,   // Collision related. (always using default collision box?)
    CREATURE_TYPE_FLAG_IS_SIEGE_WEAPON                      = 0x00040000,
    CREATURE_TYPE_FLAG_CAN_COLLIDE_WITH_MISSILES            = 0x00080000,   // Projectiles can collide with this creature - interacts with TARGET_DEST_TRAJ
    CREATURE_TYPE_FLAG_HIDE_NAME_PLATE                      = 0x00100000,
    CREATURE_TYPE_FLAG_DO_NOT_PLAY_MOUNTED_ANIMATIONS       = 0x00200000,
    CREATURE_TYPE_FLAG_IS_LINK_ALL                          = 0x00400000,
    CREATURE_TYPE_FLAG_INTERACT_ONLY_WITH_CREATOR           = 0x00800000,
    CREATURE_TYPE_FLAG_DO_NOT_PLAY_UNIT_EVENT_SOUNDS        = 0x01000000,
    CREATURE_TYPE_FLAG_HAS_NO_SHADOW_BLOB                   = 0x02000000,
    CREATURE_TYPE_FLAG_TREAT_AS_RAID_UNIT                   = 0x04000000,   //! Creature can be targeted by spells that require target to be in caster's party/raid
    CREATURE_TYPE_FLAG_FORCE_GOSSIP                         = 0x08000000,   // Allows the creature to display a single gossip option.
    CREATURE_TYPE_FLAG_DO_NOT_SHEATHE                       = 0x10000000,
    CREATURE_TYPE_FLAG_DO_NOT_TARGET_ON_INTERACTION         = 0x20000000,
    CREATURE_TYPE_FLAG_DO_NOT_RENDER_OBJECT_NAME            = 0x40000000,
    CREATURE_TYPE_FLAG_UNIT_IS_QUEST_BOSS                   = 0x80000000    // Not verified
};

enum CreatureTypeFlags2
{
    CREATURE_TYPEFLAGS_2_UNK1           = 0x00000001,
    CREATURE_TYPEFLAGS_2_UNK2           = 0x00000002,
    CREATURE_TYPEFLAGS_2_UNK3           = 0x00000004,
    CREATURE_TYPEFLAGS_2_UNK4           = 0x00000008,
    CREATURE_TYPEFLAGS_2_UNK5           = 0x00000010,
    CREATURE_TYPEFLAGS_2_UNK6           = 0x00000020,
    CREATURE_TYPEFLAGS_2_UNK7           = 0x00000040,
    CREATURE_TYPEFLAGS_2_UNK8           = 0x00000080
};

enum CreatureEliteType
{
    CREATURE_ELITE_NORMAL          = 0,
    CREATURE_ELITE_ELITE           = 1,
    CREATURE_ELITE_RAREELITE       = 2,
    CREATURE_ELITE_WORLDBOSS       = 3,
    CREATURE_ELITE_RARE            = 4,
    CREATURE_UNKNOWN               = 5                      // found in 2.2.3 for 2 mobs
};

// values based at Holidays.dbc
enum HolidayIds : uint32
{
    HOLIDAY_NONE                     = 0,

    HOLIDAY_FIREWORKS_SPECTACULAR    = 62,
    HOLIDAY_FEAST_OF_WINTER_VEIL     = 141,
    HOLIDAY_NOBLEGARDEN              = 181,
    HOLIDAY_CHILDRENS_WEEK           = 201,
    HOLIDAY_CALL_TO_ARMS_AV          = 283,
    HOLIDAY_CALL_TO_ARMS_WS          = 284,
    HOLIDAY_CALL_TO_ARMS_AB          = 285,
    HOLIDAY_FISHING_EXTRAVAGANZA     = 301,
    HOLIDAY_HARVEST_FESTIVAL         = 321,
    HOLIDAY_HALLOWS_END              = 324,
    HOLIDAY_LUNAR_FESTIVAL           = 327,
    // HOLIDAY_LOVE_IS_IN_THE_AIR    = 335, unused/duplicated
    HOLIDAY_FIRE_FESTIVAL            = 341,
    HOLIDAY_CALL_TO_ARMS_EY          = 353,
    HOLIDAY_BREWFEST                 = 372,
    HOLIDAY_DARKMOON_FAIRE_ELWYNN    = 374,
    HOLIDAY_DARKMOON_FAIRE_THUNDER   = 375,
    HOLIDAY_DARKMOON_FAIRE_SHATTRATH = 376,
    HOLIDAY_PIRATES_DAY              = 398,
    HOLIDAY_CALL_TO_ARMS_SA          = 400,
    HOLIDAY_PILGRIMS_BOUNTY          = 404,
    HOLIDAY_WOTLK_LAUNCH             = 406,
    HOLIDAY_DAY_OF_DEAD              = 409,
    HOLIDAY_CALL_TO_ARMS_IC          = 420,
    HOLIDAY_LOVE_IS_IN_THE_AIR       = 423,
    HOLIDAY_KALU_AK_FISHING_DERBY    = 424,
    HOLIDAY_CALL_TO_ARMS_BFG         = 435,
    HOLIDAY_CALL_TO_ARMS_TP          = 436,
    HOLIDAY_RATED_BG_15_VS_15        = 442,
    HOLIDAY_RATED_BG_25_VS_25        = 443,
    HOLIDAY_ANNIVERSARY_7_YEARS      = 467,
    HOLIDAY_DARKMOON_FAIRE_TEROKKAR  = 479,
    HOLIDAY_ANNIVERSARY_8_YEARS      = 484
};

enum QuestType
{
    QUEST_TYPE_TURNIN               = 0,
    QUEST_TYPE_WITH_MAX_LEVEL       = 1,
    QUEST_TYPE_NORMAL               = 2,
    MAX_DB_ALLOWED_QUEST_TYPES      = 3,

    // values used in quest menu packets
    QUEST_TYPE_IN_PROGRESS          = 4,
    QUEST_TYPE_TASK_IN_PROGRESS     = 5
};

// values based at QuestInfo.dbc
enum QuestInfo
{
    QUEST_INFO_GROUP        = 1,
    QUEST_INFO_CLASS        = 21,
    QUEST_INFO_PVP          = 41,
    QUEST_INFO_RAID         = 62,
    QUEST_INFO_DUNGEON      = 81,
    QUEST_INFO_WORLD_EVENT  = 82,
    QUEST_INFO_LEGENDARY    = 83,
    QUEST_INFO_ESCORT       = 84,
    QUEST_INFO_HEROIC       = 85,
    QUEST_INFO_RAID_10      = 88,
    QUEST_INFO_RAID_25      = 89
};

// values based at QuestSort.dbc
enum QuestSort
{
    QUEST_SORT_EPIC                = 1,
    QUEST_SORT_WAILING_CAVERNS_OLD = 21,
    QUEST_SORT_SEASONAL            = 22,
    QUEST_SORT_UNDERCITY_OLD       = 23,
    QUEST_SORT_HERBALISM           = 24,
    QUEST_SORT_BATTLEGROUNDS       = 25,
    QUEST_SORT_ULDAMN_OLD          = 41,
    QUEST_SORT_WARLOCK             = 61,
    QUEST_SORT_WARRIOR             = 81,
    QUEST_SORT_SHAMAN              = 82,
    QUEST_SORT_FISHING             = 101,
    QUEST_SORT_BLACKSMITHING       = 121,
    QUEST_SORT_PALADIN             = 141,
    QUEST_SORT_MAGE                = 161,
    QUEST_SORT_ROGUE               = 162,
    QUEST_SORT_ALCHEMY             = 181,
    QUEST_SORT_LEATHERWORKING      = 182,
    QUEST_SORT_ENGINEERING         = 201,
    QUEST_SORT_TREASURE_MAP        = 221,
    QUEST_SORT_SUNKEN_TEMPLE_OLD   = 241,
    QUEST_SORT_HUNTER              = 261,
    QUEST_SORT_PRIEST              = 262,
    QUEST_SORT_DRUID               = 263,
    QUEST_SORT_TAILORING           = 264,
    QUEST_SORT_SPECIAL             = 284,
    QUEST_SORT_COOKING             = 304,
    QUEST_SORT_FIRST_AID           = 324,
    QUEST_SORT_LEGENDARY           = 344,
    QUEST_SORT_DARKMOON_FAIRE      = 364,
    QUEST_SORT_AHN_QIRAJ_WAR       = 365,
    QUEST_SORT_LUNAR_FESTIVAL      = 366,
    QUEST_SORT_REPUTATION          = 367,
    QUEST_SORT_INVASION            = 368,
    QUEST_SORT_MIDSUMMER           = 369,
    QUEST_SORT_BREWFEST            = 370,
    QUEST_SORT_INSCRIPTION         = 371,
    QUEST_SORT_DEATH_KNIGHT        = 372,
    QUEST_SORT_JEWELCRAFTING       = 373,
    QUEST_SORT_NOBLEGARDEN         = 374,
    QUEST_SORT_PILGRIMS_BOUNTY     = 375,
    QUEST_SORT_LOVE_IS_IN_THE_AIR  = 376,
    QUEST_SORT_ARCHAEOLOGY         = 377,
    QUEST_SORT_CHILDRENS_WEEK      = 378,
    QUEST_SORT_FIRELANDS_INVASION  = 379,
    QUEST_SORT_ZANDALARI           = 380,
    QUEST_SORT_ELEMENTAL_BONDS     = 381
};

inline uint8 ClassByQuestSort(int32 QuestSort)
{
    switch (QuestSort)
    {
        case QUEST_SORT_WARLOCK:        return CLASS_WARLOCK;
        case QUEST_SORT_WARRIOR:        return CLASS_WARRIOR;
        case QUEST_SORT_SHAMAN:         return CLASS_SHAMAN;
        case QUEST_SORT_PALADIN:        return CLASS_PALADIN;
        case QUEST_SORT_MAGE:           return CLASS_MAGE;
        case QUEST_SORT_ROGUE:          return CLASS_ROGUE;
        case QUEST_SORT_HUNTER:         return CLASS_HUNTER;
        case QUEST_SORT_PRIEST:         return CLASS_PRIEST;
        case QUEST_SORT_DRUID:          return CLASS_DRUID;
        case QUEST_SORT_DEATH_KNIGHT:   return CLASS_DEATH_KNIGHT;
    }
    return 0;
}

enum SkillType
{
    SKILL_NONE                     = 0,

    SKILL_FROST                    = 6,
    SKILL_FIRE                     = 8,
    SKILL_ARMS                     = 26,
    SKILL_COMBAT                   = 38,
    SKILL_SUBTLETY                 = 39,
    SKILL_SWORDS                   = 43,
    SKILL_AXES                     = 44,
    SKILL_BOWS                     = 45,
    SKILL_GUNS                     = 46,
    SKILL_BEAST_MASTERY            = 50,
    SKILL_SURVIVAL                 = 51,
    SKILL_MACES                    = 54,
    SKILL_2H_SWORDS                = 55,
    SKILL_HOLY                     = 56,
    SKILL_SHADOW                   = 78,
    SKILL_DEFENSE                  = 95,
    SKILL_LANG_COMMON              = 98,
    SKILL_RACIAL_DWARVEN           = 101,
    SKILL_LANG_ORCISH              = 109,
    SKILL_LANG_DWARVEN             = 111,
    SKILL_LANG_DARNASSIAN          = 113,
    SKILL_LANG_TAURAHE             = 115,
    SKILL_DUAL_WIELD               = 118,
    SKILL_RACIAL_TAUREN            = 124,
    SKILL_ORC_RACIAL               = 125,
    SKILL_RACIAL_NIGHT_ELF         = 126,
    SKILL_FIRST_AID                = 129,
    SKILL_FERAL_COMBAT             = 134,
    SKILL_STAVES                   = 136,
    SKILL_LANG_THALASSIAN          = 137,
    SKILL_LANG_DRACONIC            = 138,
    SKILL_LANG_DEMON_TONGUE        = 139,
    SKILL_LANG_TITAN               = 140,
    SKILL_LANG_OLD_TONGUE          = 141,
    SKILL_SURVIVAL2                = 142,
    SKILL_RIDING_HORSE             = 148,
    SKILL_RIDING_WOLF              = 149,
    SKILL_RIDING_TIGER             = 150,
    SKILL_RIDING_RAM               = 152,
    SKILL_SWIMING                  = 155,
    SKILL_2H_MACES                 = 160,
    SKILL_UNARMED                  = 162,
    SKILL_MARKSMANSHIP             = 163,
    SKILL_BLACKSMITHING            = 164,
    SKILL_LEATHERWORKING           = 165,
    SKILL_ALCHEMY                  = 171,
    SKILL_2H_AXES                  = 172,
    SKILL_DAGGERS                  = 173,
    SKILL_THROWN                   = 176,
    SKILL_HERBALISM                = 182,
    SKILL_GENERIC_DND              = 183,
    SKILL_RETRIBUTION              = 184,
    SKILL_COOKING                  = 185,
    SKILL_MINING                   = 186,
    SKILL_PET_IMP                  = 188,
    SKILL_PET_FELHUNTER            = 189,
    SKILL_TAILORING                = 197,
    SKILL_ENGINEERING              = 202,
    SKILL_PET_SPIDER               = 203,
    SKILL_PET_VOIDWALKER           = 204,
    SKILL_PET_SUCCUBUS             = 205,
    SKILL_PET_INFERNAL             = 206,
    SKILL_PET_DOOMGUARD            = 207,
    SKILL_PET_WOLF                 = 208,
    SKILL_PET_CAT                  = 209,
    SKILL_PET_BEAR                 = 210,
    SKILL_PET_BOAR                 = 211,
    SKILL_PET_CROCILISK            = 212,
    SKILL_PET_CARRION_BIRD         = 213,
    SKILL_PET_CRAB                 = 214,
    SKILL_PET_GORILLA              = 215,
    SKILL_PET_RAPTOR               = 217,
    SKILL_PET_TALLSTRIDER          = 218,
    SKILL_RACIAL_UNDED             = 220,
    SKILL_CROSSBOWS                = 226,
    SKILL_WANDS                    = 228,
    SKILL_POLEARMS                 = 229,
    SKILL_PET_SCORPID              = 236,
    SKILL_ARCANE                   = 237,
    SKILL_PET_TURTLE               = 251,
    SKILL_ASSASSINATION            = 253,
    SKILL_FURY                     = 256,
    SKILL_PROTECTION               = 257,
    SKILL_PROTECTION2              = 267,
    SKILL_PET_TALENTS              = 270,
    SKILL_PLATE_MAIL               = 293,
    SKILL_LANG_GNOMISH             = 313,
    SKILL_LANG_TROLL               = 315,
    SKILL_ENCHANTING               = 333,
    SKILL_DEMONOLOGY               = 354,
    SKILL_AFFLICTION               = 355,
    SKILL_FISHING                  = 356,
    SKILL_ENHANCEMENT              = 373,
    SKILL_RESTORATION              = 374,
    SKILL_ELEMENTAL_COMBAT         = 375,
    SKILL_SKINNING                 = 393,
    SKILL_MAIL                     = 413,
    SKILL_LEATHER                  = 414,
    SKILL_CLOTH                    = 415,
    SKILL_SHIELD                   = 433,
    SKILL_FIST_WEAPONS             = 473,
    SKILL_RIDING_RAPTOR            = 533,
    SKILL_RIDING_MECHANOSTRIDER    = 553,
    SKILL_RIDING_UNDEAD_HORSE      = 554,
    SKILL_RESTORATION2             = 573,
    SKILL_BALANCE                  = 574,
    SKILL_DESTRUCTION              = 593,
    SKILL_HOLY2                    = 594,
    SKILL_DISCIPLINE               = 613,
    SKILL_LOCKPICKING              = 633,
    SKILL_PET_BAT                  = 653,
    SKILL_PET_HYENA                = 654,
    SKILL_PET_BIRD_OF_PREY         = 655,
    SKILL_PET_WIND_SERPENT         = 656,
    SKILL_LANG_GUTTERSPEAK         = 673,
    SKILL_RIDING_KODO              = 713,
    SKILL_RACIAL_TROLL             = 733,
    SKILL_RACIAL_GNOME             = 753,
    SKILL_RACIAL_HUMAN             = 754,
    SKILL_JEWELCRAFTING            = 755,
    SKILL_RACIAL_BLOODELF          = 756,
    SKILL_PET_EVENT_RC             = 758,   // SkillCategory = -1
    SKILL_LANG_DRAENEI             = 759,
    SKILL_RACIAL_DRAENEI           = 760,
    SKILL_PET_FELGUARD             = 761,
    SKILL_RIDING                   = 762,
    SKILL_PET_DRAGONHAWK           = 763,
    SKILL_PET_NETHER_RAY           = 764,
    SKILL_PET_SPOREBAT             = 765,
    SKILL_PET_WARP_STALKER         = 766,
    SKILL_PET_RAVAGER              = 767,
    SKILL_PET_SERPENT              = 768,
    SKILL_INTERNAL                 = 769,
    SKILL_DK_BLOOD                 = 770,
    SKILL_DK_FROST                 = 771,
    SKILL_DK_UNHOLY                = 772,
    SKILL_INSCRIPTION              = 773,
    SKILL_PET_MOTH                 = 775,
    SKILL_RUNEFORGING              = 776,
    SKILL_MOUNTS                   = 777,
    SKILL_COMPANIONS               = 778,
    SKILL_PET_EXOTIC_CHIMAERA      = 780,
    SKILL_PET_EXOTIC_DEVILSAUR     = 781,
    SKILL_PET_GHOUL                = 782,
    SKILL_PET_EXOTIC_SILITHID      = 783,
    SKILL_PET_EXOTIC_WORM          = 784,
    SKILL_PET_WASP                 = 785,
    SKILL_PET_EXOTIC_RHINO         = 786,
    SKILL_PET_EXOTIC_CORE_HOUND    = 787,
    SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788,
    SKILL_RACIAL_WORGEN            = 789,
    SKILL_RACIAL_GOBLIN            = 790,
    SKILL_LANG_WORGEN              = 791,
    SKILL_LANG_GOBLIN              = 792,
    SKILL_ARCHAEOLOGY              = 794,
    SKILL_GENERAL_HUNTER           = 795,
    SKILL_GENERAL_DEATH_KNIGHT     = 796,
    SKILL_GENERAL_ROGUE            = 797,
    SKILL_GENERAL_DRUID            = 798,
    SKILL_GENERAL_MAGE             = 799,
    SKILL_GENERAL_PALADIN          = 800,
    SKILL_GENERAL_SHAMAN           = 801,
    SKILL_GENERAL_WARLOCK          = 802,
    SKILL_GENERAL_WARRIOR          = 803,
    SKILL_GENERAL_PRIEST           = 804,
    SKILL_PET_WATER_ELEMENTAL      = 805,
    SKILL_PET_FOX                  = 808,
    SKILL_ALL_GLYPHS               = 810,
    SKILL_PET_DOG                  = 811,
    SKILL_PET_MONKEY               = 815,
    SKILL_PET_SHALE_SPIDER         = 817,
    SKILL_PET_BEETLE               = 818,
    SKILL_ALL_GUILD_PERKS          = 821,
    SKILL_PET_HYDRA                = 824
};

#define MAX_SKILL_TYPE               825

inline SkillType SkillByLockType(LockType locktype)
{
    switch (locktype)
    {
        case LOCKTYPE_PICKLOCK:    return SKILL_LOCKPICKING;
        case LOCKTYPE_HERBALISM:   return SKILL_HERBALISM;
        case LOCKTYPE_MINING:      return SKILL_MINING;
        case LOCKTYPE_FISHING:     return SKILL_FISHING;
        case LOCKTYPE_INSCRIPTION: return SKILL_INSCRIPTION;
        case LOCKTYPE_ARCHAEOLOGY: return SKILL_ARCHAEOLOGY;
        default: break;
    }
    return SKILL_NONE;
}

inline uint32 SkillByQuestSort(int32 QuestSort)
{
    switch (QuestSort)
    {
        case QUEST_SORT_HERBALISM:      return SKILL_HERBALISM;
        case QUEST_SORT_FISHING:        return SKILL_FISHING;
        case QUEST_SORT_BLACKSMITHING:  return SKILL_BLACKSMITHING;
        case QUEST_SORT_ALCHEMY:        return SKILL_ALCHEMY;
        case QUEST_SORT_LEATHERWORKING: return SKILL_LEATHERWORKING;
        case QUEST_SORT_ENGINEERING:    return SKILL_ENGINEERING;
        case QUEST_SORT_TAILORING:      return SKILL_TAILORING;
        case QUEST_SORT_COOKING:        return SKILL_COOKING;
        case QUEST_SORT_FIRST_AID:      return SKILL_FIRST_AID;
        case QUEST_SORT_JEWELCRAFTING:  return SKILL_JEWELCRAFTING;
        case QUEST_SORT_INSCRIPTION:    return SKILL_INSCRIPTION;
        case QUEST_SORT_ARCHAEOLOGY:    return SKILL_ARCHAEOLOGY;
    }
    return 0;
}

enum SkillCategory
{
    SKILL_CATEGORY_UNK1          = 0,
    SKILL_CATEGORY_ATTRIBUTES    = 5,
    SKILL_CATEGORY_WEAPON        = 6,
    SKILL_CATEGORY_CLASS         = 7,
    SKILL_CATEGORY_ARMOR         = 8,
    SKILL_CATEGORY_SECONDARY     = 9,                       // secondary professions
    SKILL_CATEGORY_LANGUAGES     = 10,
    SKILL_CATEGORY_PROFESSION    = 11,                      // primary professions
    SKILL_CATEGORY_GENERIC       = 12
};

enum TotemCategory
{
    TC_SKINNING_SKIFE_OLD          = 1,
    TC_EARTH_TOTEM                 = 2,
    TC_AIR_TOTEM                   = 3,
    TC_FIRE_TOTEM                  = 4,
    TC_WATER_TOTEM                 = 5,
    TC_COPPER_ROD                  = 6,
    TC_SILVER_ROD                  = 7,
    TC_GOLDEN_ROD                  = 8,
    TC_TRUESILVER_ROD              = 9,
    TC_ARCANITE_ROD                = 10,
    TC_MINING_PICK_OLD             = 11,
    TC_PHILOSOPHERS_STONE          = 12,
    TC_BLACKSMITH_HAMMER_OLD       = 13,
    TC_ARCLIGHT_SPANNER            = 14,
    TC_GYROMATIC_MA                = 15,
    TC_MASTER_TOTEM                = 21,
    TC_FEL_IRON_ROD                = 41,
    TC_ADAMANTITE_ROD              = 62,
    TC_ETERNIUM_ROD                = 63,
    TC_HOLLOW_QUILL                = 81,
    TC_RUNED_AZURITE_ROD           = 101,
    TC_VIRTUOSO_INKING_SET         = 121,
    TC_DRUMS                       = 141,
    TC_GNOMISH_ARMY_KNIFE          = 161,
    TC_BLACKSMITH_HAMMER           = 162,
    TC_MINING_PICK                 = 165,
    TC_SKINNING_KNIFE              = 166,
    TC_HAMMER_PICK                 = 167,
    TC_BLADED_PICKAXE              = 168,
    TC_FLINT_AND_TINDER            = 169,
    TC_RUNED_COBALT_ROD            = 189,
    TC_RUNED_TITANIUM_ROD          = 190,
    TC_RUNED_ELEMENTIUM_ROD        = 209,
    TC_HIGH_POWERED_BOLT_GUN       = 210,
};

enum UnitDynFlags
{
    UNIT_DYNFLAG_NONE                       = 0x0000,
    UNIT_DYNFLAG_LOOTABLE                   = 0x0001,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0002,
    UNIT_DYNFLAG_TAPPED                     = 0x0004,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0008,       // Lua_UnitIsTappedByPlayer
    UNIT_DYNFLAG_SPECIALINFO                = 0x0010,
    UNIT_DYNFLAG_DEAD                       = 0x0020,
    UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0040,
    UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0080        // Lua_UnitIsTappedByAllThreatList
};

enum CorpseDynFlags
{
    CORPSE_DYNFLAG_LOOTABLE        = 0x0001
};

#define PLAYER_CORPSE_LOOT_ENTRY 1

enum WeatherType
{
    WEATHER_TYPE_FINE       = 0,
    WEATHER_TYPE_RAIN       = 1,
    WEATHER_TYPE_SNOW       = 2,
    WEATHER_TYPE_STORM      = 3,
    WEATHER_TYPE_THUNDERS   = 86,
    WEATHER_TYPE_BLACKRAIN  = 90
};

#define MAX_WEATHER_TYPE 4

enum ChatMsg
{
    CHAT_MSG_ADDON                              = 0xFFFFFFFF, // -1
    CHAT_MSG_SYSTEM                             = 0x00,
    CHAT_MSG_SAY                                = 0x01,
    CHAT_MSG_PARTY                              = 0x02,
    CHAT_MSG_RAID                               = 0x03,
    CHAT_MSG_GUILD                              = 0x04,
    CHAT_MSG_OFFICER                            = 0x05,
    CHAT_MSG_YELL                               = 0x06,
    CHAT_MSG_WHISPER                            = 0x07,
    CHAT_MSG_WHISPER_FOREIGN                    = 0x08,
    CHAT_MSG_WHISPER_INFORM                     = 0x09,
    CHAT_MSG_EMOTE                              = 0x0A,
    CHAT_MSG_TEXT_EMOTE                         = 0x0B,
    CHAT_MSG_MONSTER_SAY                        = 0x0C,
    CHAT_MSG_MONSTER_PARTY                      = 0x0D,
    CHAT_MSG_MONSTER_YELL                       = 0x0E,
    CHAT_MSG_MONSTER_WHISPER                    = 0x0F,
    CHAT_MSG_MONSTER_EMOTE                      = 0x10,
    CHAT_MSG_CHANNEL                            = 0x11,
    CHAT_MSG_CHANNEL_JOIN                       = 0x12,
    CHAT_MSG_CHANNEL_LEAVE                      = 0x13,
    CHAT_MSG_CHANNEL_LIST                       = 0x14,
    CHAT_MSG_CHANNEL_NOTICE                     = 0x15,
    CHAT_MSG_CHANNEL_NOTICE_USER                = 0x16,
    CHAT_MSG_AFK                                = 0x17,
    CHAT_MSG_DND                                = 0x18,
    CHAT_MSG_IGNORED                            = 0x19,
    CHAT_MSG_SKILL                              = 0x1A,
    CHAT_MSG_LOOT                               = 0x1B,
    CHAT_MSG_MONEY                              = 0x1C,
    CHAT_MSG_OPENING                            = 0x1D,
    CHAT_MSG_TRADESKILLS                        = 0x1E,
    CHAT_MSG_PET_INFO                           = 0x1F,
    CHAT_MSG_COMBAT_MISC_INFO                   = 0x20,
    CHAT_MSG_COMBAT_XP_GAIN                     = 0x21,
    CHAT_MSG_COMBAT_HONOR_GAIN                  = 0x22,
    CHAT_MSG_COMBAT_FACTION_CHANGE              = 0x23,
    CHAT_MSG_BG_SYSTEM_NEUTRAL                  = 0x24,
    CHAT_MSG_BG_SYSTEM_ALLIANCE                 = 0x25,
    CHAT_MSG_BG_SYSTEM_HORDE                    = 0x26,
    CHAT_MSG_RAID_LEADER                        = 0x27,
    CHAT_MSG_RAID_WARNING                       = 0x28,
    CHAT_MSG_RAID_BOSS_EMOTE                    = 0x29,
    CHAT_MSG_RAID_BOSS_WHISPER                  = 0x2A,
    CHAT_MSG_FILTERED                           = 0x2B,
    CHAT_MSG_BATTLEGROUND                       = 0x2C,
    CHAT_MSG_BATTLEGROUND_LEADER                = 0x2D,
    CHAT_MSG_RESTRICTED                         = 0x2E,
    CHAT_MSG_BATTLENET                          = 0x2F,
    CHAT_MSG_ACHIEVEMENT                        = 0x30,
    CHAT_MSG_GUILD_ACHIEVEMENT                  = 0x31,
    CHAT_MSG_ARENA_POINTS                       = 0x32,
    CHAT_MSG_PARTY_LEADER                       = 0x33,
    CHAT_MSG_TARGETICONS                        = 0x34,
    CHAT_MSG_BN_WHISPER                         = 0x35,
    CHAT_MSG_BN_WHISPER_INFORM                  = 0x36,
    CHAT_MSG_BN_CONVERSATION                    = 0x37,
    CHAT_MSG_BN_CONVERSATION_NOTICE             = 0x38,
    CHAT_MSG_BN_CONVERSATION_LIST               = 0x39,
    CHAT_MSG_BN_INLINE_TOAST_ALERT              = 0x3A,
    CHAT_MSG_BN_INLINE_TOAST_BROADCAST          = 0x3B,
    CHAT_MSG_BN_INLINE_TOAST_BROADCAST_INFORM   = 0x3C,
    CHAT_MSG_BN_INLINE_TOAST_CONVERSATION       = 0x3D,
    CHAT_MSG_BN_WHISPER_PLAYER_OFFLINE          = 0x3E,
    CHAT_MSG_COMBAT_GUILD_XP_GAIN               = 0x3F,
    CHAT_MSG_CURRENCY                           = 0x40
};

#define MAX_CHAT_MSG_TYPE 0x41

enum ChatLinkColors
{
    CHAT_LINK_COLOR_TRADE       = 0xffffd000,   // orange
    CHAT_LINK_COLOR_TALENT      = 0xff4e96f7,   // blue
    CHAT_LINK_COLOR_SPELL       = 0xff71d5ff,   // bright blue
    CHAT_LINK_COLOR_ENCHANT     = 0xffffd000,   // orange
    CHAT_LINK_COLOR_ACHIEVEMENT = 0xffffff00,
    CHAT_LINK_COLOR_GLYPH       = 0xff66bbff
};

// Values from ItemPetFood (power of (value-1) used for compare with CreatureFamilyEntry.petDietMask
enum PetDiet
{
    PET_DIET_MEAT     = 1,
    PET_DIET_FISH     = 2,
    PET_DIET_CHEESE   = 3,
    PET_DIET_BREAD    = 4,
    PET_DIET_FUNGAS   = 5,
    PET_DIET_FRUIT    = 6,
    PET_DIET_RAW_MEAT = 7,
    PET_DIET_RAW_FISH = 8
};

#define MAX_PET_DIET 9

enum PetTameFailureReason
{
    PET_TAME_FAILURE_UNKNOWN                = 0,
    PET_TAME_FAILURE_CREATURE_NOT_FOUND     = 1,
    PET_TAME_FAILURE_TOO_MANY_PETS          = 2,
    PET_TAME_FAILURE_CREATURE_CONTROLLED    = 3,
    PET_TAME_FAILURE_NOT_TAMEABLE           = 4,
    PET_TAME_FAILURE_ACTIVE_SUMMON          = 5,
    PET_TAME_FAILURE_CANNOT_TAME_CREATURES  = 6,
    PET_TAME_FAILURE_NO_PET_TO_SUMMON       = 7,
    PET_TAME_FAILURE_INTERNAL_PET_ERROR     = 8,
    PET_TAME_FAILURE_TOO_HIGH_LEVEL         = 9,
    PET_TAME_FAILURE_DEAD_PET               = 10,
    PET_TAME_FAILURE_PET_NOT_DEAD           = 11,
    PET_TAME_FAILURE_CANNOT_TAME_EXOTIC     = 12,
    PET_TAME_FAILURE_SLOT_LOCKED            = 13
};

#define CHAIN_SPELL_JUMP_RADIUS 8

enum GuildLogs
{
    GUILD_BANKLOG_MAX_RECORDS   = 25,
    GUILD_EVENTLOG_MAX_RECORDS  = 100,
    GUILD_NEWSLOG_MAX_RECORDS   = 250
};

enum AiReaction
{
    AI_REACTION_ALERT    = 0,                               // pre-aggro (used in client packet handler)
    AI_REACTION_FRIENDLY = 1,                               // (NOT used in client packet handler)
    AI_REACTION_HOSTILE  = 2,                               // sent on every attack, triggers aggro sound (used in client packet handler)
    AI_REACTION_AFRAID   = 3,                               // seen for polymorph (when AI not in control of self?) (NOT used in client packet handler)
    AI_REACTION_DESTROY  = 4                                // used on object destroy (NOT used in client packet handler)
};

// Diminishing Returns Types
enum DiminishingReturnsType
{
    DRTYPE_NONE         = 0,                                // this spell is not diminished, but may have limited it's duration to 10s
    DRTYPE_PLAYER       = 1,                                // this spell is diminished only when applied on players
    DRTYPE_ALL          = 2                                 // this spell is diminished in every case
};

// Diminishing Return Groups
enum DiminishingGroup : uint16
{
    DIMINISHING_NONE                = 0,
    DIMINISHING_BANISH              = 1,
    DIMINISHING_CHARGE              = 2,
    DIMINISHING_OPENING_STUN        = 3, // Cheap Shot and Pounce
    DIMINISHING_CONTROLLED_STUN     = 4,
    DIMINISHING_CONTROLLED_ROOT     = 5,
    DIMINISHING_CYCLONE             = 6,
    DIMINISHING_DISARM              = 7,
    DIMINISHING_DISORIENT           = 8, // Several spells where name cant be generalized.
    DIMINISHING_ENTRAPMENT          = 9,
    DIMINISHING_FEAR                = 10,
    DIMINISHING_HORROR              = 11,
    DIMINISHING_MIND_CONTROL        = 12,
    DIMINISHING_ROOT                = 13,
    DIMINISHING_STUN                = 14,
    DIMINISHING_SCATTER_SHOT        = 15,
    DIMINISHING_SILENCE             = 16,
    DIMINISHING_SLEEP               = 17,
    DIMINISHING_TAUNT               = 18,
    DIMINISHING_LIMITONLY           = 19,
    DIMINISHING_DRAGONS_BREATH      = 20,

    DIMINISHING_MAX
};

enum SummonCategory
{
    SUMMON_CATEGORY_WILD        = 0,
    SUMMON_CATEGORY_ALLY        = 1,
    SUMMON_CATEGORY_PET         = 2,
    SUMMON_CATEGORY_PUPPET      = 3,
    SUMMON_CATEGORY_VEHICLE     = 4,
    SUMMON_CATEGORY_UNK         = 5  // as of patch 3.3.5a only Bone Spike in Icecrown Citadel
                                     // uses this category
};

enum class SummonTitle : int32
{
    None                = 0,
    Pet                 = 1,
    Guardian            = 2,
    Minion              = 3,
    Totem               = 4,
    Companion           = 5,
    Runeblade           = 6,
    Construct           = 7,
    Opponent            = 8,    // Related to phases and DK prequest line (3.3.5a)
    Vehicle             = 9,
    Mount               = 10,   // Oculus and Argent Tournament vehicles (3.3.5a)
    Lightwell           = 11,
    Butler              = 12,
    aka                 = 13
};

enum SummonSlot
{
    SUMMON_SLOT_PET         = 0,
    SUMMON_SLOT_TOTEM_FIRE  = 1,
    SUMMON_SLOT_TOTEM_EARTH = 2,
    SUMMON_SLOT_TOTEM_WATER = 3,
    SUMMON_SLOT_TOTEM_AIR   = 4,
    SUMMON_SLOT_MINIPET     = 5,
    SUMMON_SLOT_QUEST       = 6,

    MAX_SUMMON_SLOT
};

#define MAX_TOTEM_SLOT      5
#define MAX_GAMEOBJECT_SLOT 4

enum EventId
{
    EVENT_CHARGE            = 1003,
    EVENT_JUMP              = 1004,

    /// Special charge event which is used for charge spells that have explicit targets
    /// and had a path already generated - using it in PointMovementGenerator will not
    /// create a new spline and launch it
    EVENT_CHARGE_PREPATH    = 1005,

    EVENT_FACE              = 1006,
    EVENT_VEHICLE_BOARD     = 1007,
    EVENT_VEHICLE_EXIT      = 1008
};

enum ResponseCodes
{
    RESPONSE_SUCCESS                                       = 0,
    RESPONSE_FAILURE                                       = 1,
    RESPONSE_CANCELLED                                     = 2,
    RESPONSE_DISCONNECTED                                  = 3,
    RESPONSE_FAILED_TO_CONNECT                             = 4,
    RESPONSE_CONNECTED                                     = 5,
    RESPONSE_VERSION_MISMATCH                              = 6,

    CSTATUS_CONNECTING                                     = 7,
    CSTATUS_NEGOTIATING_SECURITY                           = 8,
    CSTATUS_NEGOTIATION_COMPLETE                           = 9,
    CSTATUS_NEGOTIATION_FAILED                             = 10,
    CSTATUS_AUTHENTICATING                                 = 11,

    AUTH_OK                                                = 12,
    AUTH_FAILED                                            = 13,
    AUTH_REJECT                                            = 14,
    AUTH_BAD_SERVER_PROOF                                  = 15,
    AUTH_UNAVAILABLE                                       = 16,
    AUTH_SYSTEM_ERROR                                      = 17,
    AUTH_BILLING_ERROR                                     = 18,
    AUTH_BILLING_EXPIRED                                   = 19,
    AUTH_VERSION_MISMATCH                                  = 20,
    AUTH_UNKNOWN_ACCOUNT                                   = 21,
    AUTH_INCORRECT_PASSWORD                                = 22,
    AUTH_SESSION_EXPIRED                                   = 23,
    AUTH_SERVER_SHUTTING_DOWN                              = 24,
    AUTH_ALREADY_LOGGING_IN                                = 25,
    AUTH_LOGIN_SERVER_NOT_FOUND                            = 26,
    AUTH_WAIT_QUEUE                                        = 27,
    AUTH_BANNED                                            = 28,
    AUTH_ALREADY_ONLINE                                    = 29,
    AUTH_NO_TIME                                           = 30,
    AUTH_DB_BUSY                                           = 31,
    AUTH_SUSPENDED                                         = 32,
    AUTH_PARENTAL_CONTROL                                  = 33,
    AUTH_LOCKED_ENFORCED                                   = 34,

    REALM_LIST_IN_PROGRESS                                 = 35,
    REALM_LIST_SUCCESS                                     = 36,
    REALM_LIST_FAILED                                      = 37,
    REALM_LIST_INVALID                                     = 38,
    REALM_LIST_REALM_NOT_FOUND                             = 39,

    ACCOUNT_CREATE_IN_PROGRESS                             = 40,
    ACCOUNT_CREATE_SUCCESS                                 = 41,
    ACCOUNT_CREATE_FAILED                                  = 42,

    CHAR_LIST_RETRIEVING                                   = 43,
    CHAR_LIST_RETRIEVED                                    = 44,
    CHAR_LIST_FAILED                                       = 45,

    CHAR_CREATE_IN_PROGRESS                                = 46,
    CHAR_CREATE_SUCCESS                                    = 47,
    CHAR_CREATE_ERROR                                      = 48,
    CHAR_CREATE_FAILED                                     = 49,
    CHAR_CREATE_NAME_IN_USE                                = 50,
    CHAR_CREATE_DISABLED                                   = 51,
    CHAR_CREATE_PVP_TEAMS_VIOLATION                        = 52,
    CHAR_CREATE_SERVER_LIMIT                               = 53,
    CHAR_CREATE_ACCOUNT_LIMIT                              = 54,
    CHAR_CREATE_SERVER_QUEUE                               = 55,
    CHAR_CREATE_ONLY_EXISTING                              = 56,
    CHAR_CREATE_EXPANSION                                  = 57,
    CHAR_CREATE_EXPANSION_CLASS                            = 58,
    CHAR_CREATE_LEVEL_REQUIREMENT                          = 59,
    CHAR_CREATE_UNIQUE_CLASS_LIMIT                         = 60,
    CHAR_CREATE_CHARACTER_IN_GUILD                         = 61,
    CHAR_CREATE_RESTRICTED_RACECLASS                       = 62,
    CHAR_CREATE_CHARACTER_CHOOSE_RACE                      = 63,
    CHAR_CREATE_CHARACTER_ARENA_LEADER                     = 64,
    CHAR_CREATE_CHARACTER_DELETE_MAIL                      = 65,
    CHAR_CREATE_CHARACTER_SWAP_FACTION                     = 66,
    CHAR_CREATE_CHARACTER_RACE_ONLY                        = 67,
    CHAR_CREATE_CHARACTER_GOLD_LIMIT                       = 68,
    CHAR_CREATE_FORCE_LOGIN                                = 69,

    CHAR_DELETE_IN_PROGRESS                                = 70,
    CHAR_DELETE_SUCCESS                                    = 71,
    CHAR_DELETE_FAILED                                     = 72,
    CHAR_DELETE_FAILED_LOCKED_FOR_TRANSFER                 = 73,
    CHAR_DELETE_FAILED_GUILD_LEADER                        = 74,
    CHAR_DELETE_FAILED_ARENA_CAPTAIN                       = 75,
    CHAR_DELETE_FAILED_HAS_HEIRLOOM_OR_MAIL                = 76,

    CHAR_LOGIN_IN_PROGRESS                                 = 77,
    CHAR_LOGIN_SUCCESS                                     = 78,
    CHAR_LOGIN_NO_WORLD                                    = 79,
    CHAR_LOGIN_DUPLICATE_CHARACTER                         = 80,
    CHAR_LOGIN_NO_INSTANCES                                = 81,
    CHAR_LOGIN_FAILED                                      = 82,
    CHAR_LOGIN_DISABLED                                    = 83,
    CHAR_LOGIN_NO_CHARACTER                                = 84,
    CHAR_LOGIN_LOCKED_FOR_TRANSFER                         = 85,
    CHAR_LOGIN_LOCKED_BY_BILLING                           = 86,
    CHAR_LOGIN_LOCKED_BY_MOBILE_AH                         = 87,
    CHAR_LOGIN_TEMPORARY_GM_LOCK                           = 88,

    CHAR_NAME_SUCCESS                                      = 89,
    CHAR_NAME_FAILURE                                      = 90,
    CHAR_NAME_NO_NAME                                      = 91,
    CHAR_NAME_TOO_SHORT                                    = 92,
    CHAR_NAME_TOO_LONG                                     = 93,
    CHAR_NAME_INVALID_CHARACTER                            = 94,
    CHAR_NAME_MIXED_LANGUAGES                              = 95,
    CHAR_NAME_PROFANE                                      = 96,
    CHAR_NAME_RESERVED                                     = 97,
    CHAR_NAME_INVALID_APOSTROPHE                           = 98,
    CHAR_NAME_MULTIPLE_APOSTROPHES                         = 99,
    CHAR_NAME_THREE_CONSECUTIVE                            = 100,
    CHAR_NAME_INVALID_SPACE                                = 101,
    CHAR_NAME_CONSECUTIVE_SPACES                           = 102,
    CHAR_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS        = 103,
    CHAR_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END = 104,
    CHAR_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME            = 105,
};

/// Ban function modes
enum BanMode
{
    BAN_ACCOUNT,
    BAN_CHARACTER,
    BAN_IP
};

/// Ban function return codes
enum BanReturn
{
    BAN_SUCCESS,
    BAN_SYNTAX_ERROR,
    BAN_NOTFOUND,
    BAN_EXISTS
};

enum BattlegroundTeamId
{
    BG_TEAM_HORDE       = 0, // Battleground: Horde,    Arena: Green
    BG_TEAM_ALLIANCE    = 1, // Battleground: Alliance, Arena: Gold
    BG_TEAM_NEUTRAL     = 2  // Battleground: Neutral,  Arena: None
};

#define BG_TEAMS_COUNT  2

// indexes of BattlemasterList.dbc
enum BattlegroundTypeId : uint32
{
    BATTLEGROUND_TYPE_NONE      = 0,   // None
    BATTLEGROUND_AV             = 1,   // Alterac Valley
    BATTLEGROUND_WS             = 2,   // Warsong Gulch
    BATTLEGROUND_AB             = 3,   // Arathi Basin
    BATTLEGROUND_NA             = 4,   // Nagrand Arena
    BATTLEGROUND_BE             = 5,   // Blade's Edge Arena
    BATTLEGROUND_AA             = 6,   // All Arenas
    BATTLEGROUND_EY             = 7,   // Eye of the Storm
    BATTLEGROUND_RL             = 8,   // Ruins of Lordaernon
    BATTLEGROUND_SA             = 9,   // Strand of the Ancients
    BATTLEGROUND_DS             = 10,  // Dalaran Sewers
    BATTLEGROUND_RV             = 11,  // Ring of Valor
    BATTLEGROUND_IC             = 30,  // Isle of Conquest
    BATTLEGROUND_RB             = 32,  // Random Battleground
    BATTLEGROUND_RATED_10_VS_10 = 100, // Rated BG 10 vs 10
    BATTLEGROUND_RATED_15_VS_15 = 101, // Rated BG 15 vs 15
    BATTLEGROUND_RATED_25_VS_25 = 102, // Rated BG 25 vs 25
    BATTLEGROUND_TP             = 108, // Twin Peaks
    BATTLEGROUND_BFG            = 120, // Battle For Gilneas
    // 441 = "Icecrown Citadel"
    // 443 = "The Ruby Sanctum"
    // 656 = "Rated Eye of the Storm"
};

#define MAX_BATTLEGROUND_TYPE_ID 121

enum MailResponseType
{
    MAIL_SEND               = 0,
    MAIL_MONEY_TAKEN        = 1,
    MAIL_ITEM_TAKEN         = 2,
    MAIL_RETURNED_TO_SENDER = 3,
    MAIL_DELETED            = 4,
    MAIL_MADE_PERMANENT     = 5
};

enum MailResponseResult
{
    MAIL_OK                            = 0,
    MAIL_ERR_EQUIP_ERROR               = 1,
    MAIL_ERR_CANNOT_SEND_TO_SELF       = 2,
    MAIL_ERR_NOT_ENOUGH_MONEY          = 3,
    MAIL_ERR_RECIPIENT_NOT_FOUND       = 4,
    MAIL_ERR_NOT_YOUR_TEAM             = 5,
    MAIL_ERR_INTERNAL_ERROR            = 6,
    MAIL_ERR_DISABLED_FOR_TRIAL_ACC    = 14,
    MAIL_ERR_RECIPIENT_CAP_REACHED     = 15,
    MAIL_ERR_CANT_SEND_WRAPPED_COD     = 16,
    MAIL_ERR_MAIL_AND_CHAT_SUSPENDED   = 17,
    MAIL_ERR_TOO_MANY_ATTACHMENTS      = 18,
    MAIL_ERR_MAIL_ATTACHMENT_INVALID   = 19,
    MAIL_ERR_ITEM_HAS_EXPIRED          = 21
};

enum SpellFamilyNames
{
    SPELLFAMILY_GENERIC     = 0,
    SPELLFAMILY_UNK1        = 1,                            // events, holidays
    // 2 - unused
    SPELLFAMILY_MAGE        = 3,
    SPELLFAMILY_WARRIOR     = 4,
    SPELLFAMILY_WARLOCK     = 5,
    SPELLFAMILY_PRIEST      = 6,
    SPELLFAMILY_DRUID       = 7,
    SPELLFAMILY_ROGUE       = 8,
    SPELLFAMILY_HUNTER      = 9,
    SPELLFAMILY_PALADIN     = 10,
    SPELLFAMILY_SHAMAN      = 11,
    SPELLFAMILY_UNK2        = 12,                           // 2 spells (silence resistance)
    SPELLFAMILY_POTION      = 13,
    // 14 - unused
    SPELLFAMILY_DEATHKNIGHT = 15,
    // 16 - unused
    SPELLFAMILY_PET         = 17,
    SPELLFAMILY_UNK3        = 50,
};

enum TradeStatus
{
    TRADE_STATUS_INITIATED              = 0,
    // 1 - Related to EVENT_PLAYER_MONEY
    TRADE_STATUS_NOT_ON_TAPLIST         = 2,           // Related to trading soulbound loot items
    TRADE_STATUS_YOU_LOGOUT             = 3,
    TRADE_STATUS_IGNORE_YOU             = 4,
    TRADE_STATUS_TARGET_DEAD            = 5,
    TRADE_STATUS_TRADE_ACCEPT           = 6,
    TRADE_STATUS_TARGET_LOGOUT          = 7,
    // 8 - nonexistent
    TRADE_STATUS_TRADE_COMPLETE         = 9,
    TRADE_STATUS_TRIAL_ACCOUNT          = 10, // Trial accounts can not perform that action
    // 11 - nonexistent
    TRADE_STATUS_BEGIN_TRADE            = 12,
    TRADE_STATUS_YOU_DEAD               = 13,
    // 14 - nonexistent
    // 15 - nonexistent
    TRADE_STATUS_TARGET_TO_FAR          = 16,
    TRADE_STATUS_NO_TARGET              = 17,
    TRADE_STATUS_BUSY_2                 = 18,
    TRADE_STATUS_CURRENCY_NOT_TRADABLE  = 19, // new 4.x
    TRADE_STATUS_WRONG_FACTION          = 20,
    TRADE_STATUS_BUSY                   = 21,
    TRADE_STATUS_STATE_CHANGED          = 22,
    TRADE_STATUS_TRADE_CANCELED         = 23,
    TRADE_STATUS_CURRENCY               = 24, // new 4.x
    TRADE_STATUS_UNACCEPTED             = 25,
    TRADE_STATUS_WRONG_REALM            = 26, // You can only trade conjured items... (cross realm BG related).
    TRADE_STATUS_YOU_STUNNED            = 27,
    // 28 - nonexistent
    TRADE_STATUS_TARGET_STUNNED         = 29,
    // 30 - nonexistent
    TRADE_STATUS_FAILED                 = 31
};

enum XPColorChar : uint8
{
    XP_RED,
    XP_ORANGE,
    XP_YELLOW,
    XP_GREEN,
    XP_GRAY
};

enum RemoveMethod : uint8
{
    GROUP_REMOVEMETHOD_DEFAULT  = 0,
    GROUP_REMOVEMETHOD_KICK     = 1,
    GROUP_REMOVEMETHOD_LEAVE    = 2,
    GROUP_REMOVEMETHOD_KICK_LFG = 3
};

enum ActivateTaxiReply
{
    ERR_TAXIOK                      = 0,
    ERR_TAXIUNSPECIFIEDSERVERERROR  = 1,
    ERR_TAXINOSUCHPATH              = 2,
    ERR_TAXINOTENOUGHMONEY          = 3,
    ERR_TAXITOOFARAWAY              = 4,
    ERR_TAXINOVENDORNEARBY          = 5,
    ERR_TAXINOTVISITED              = 6,
    ERR_TAXIPLAYERBUSY              = 7,
    ERR_TAXIPLAYERALREADYMOUNTED    = 8,
    ERR_TAXIPLAYERSHAPESHIFTED      = 9,
    ERR_TAXIPLAYERMOVING            = 10,
    ERR_TAXISAMENODE                = 11,
    ERR_TAXINOTSTANDING             = 12
};

enum ProfessionUI
{
    MAX_PRIMARY_PROFESSIONS = 2,
    MAX_SECONDARY_SKILLS = 5
};

enum DuelCompleteType : uint8
{
    DUEL_INTERRUPTED = 0,
    DUEL_WON         = 1,
    DUEL_FLED        = 2
};

// handle the queue types and bg types separately to enable joining queue for different sized arenas at the same time
enum BattlegroundQueueTypeId
{
    BATTLEGROUND_QUEUE_NONE     = 0,
    BATTLEGROUND_QUEUE_AV       = 1,
    BATTLEGROUND_QUEUE_WS       = 2,
    BATTLEGROUND_QUEUE_AB       = 3,
    BATTLEGROUND_QUEUE_EY       = 4,
    BATTLEGROUND_QUEUE_SA       = 5,
    BATTLEGROUND_QUEUE_IC       = 6,
    BATTLEGROUND_QUEUE_TP       = 7,
    BATTLEGROUND_QUEUE_BFG      = 8,
    BATTLEGROUND_QUEUE_RB       = 9,
    BATTLEGROUND_QUEUE_2v2      = 10,
    BATTLEGROUND_QUEUE_3v3      = 11,
    BATTLEGROUND_QUEUE_5v5      = 12,
    MAX_BATTLEGROUND_QUEUE_TYPES
};

enum GroupJoinBattlegroundResult
{
    ERR_BATTLEGROUND_NONE                           = 0,
    ERR_GROUP_JOIN_BATTLEGROUND_DESERTERS           = 2,        // You cannot join the battleground yet because you or one of your party members is flagged as a Deserter.
    ERR_ARENA_TEAM_PARTY_SIZE                       = 3,        // Incorrect party size for this arena.
    ERR_BATTLEGROUND_TOO_MANY_QUEUES                = 4,        // You can only be queued for 2 battles at once
    ERR_BATTLEGROUND_CANNOT_QUEUE_FOR_RATED         = 5,        // You cannot queue for a rated match while queued for other battles
    ERR_BATTLEDGROUND_QUEUED_FOR_RATED              = 6,        // You cannot queue for another battle while queued for a rated arena match
    ERR_BATTLEGROUND_TEAM_LEFT_QUEUE                = 7,        // Your team has left the arena queue
    ERR_BATTLEGROUND_NOT_IN_BATTLEGROUND            = 8,        // You can't do that in a battleground.
    ERR_BATTLEGROUND_JOIN_XP_GAIN                   = 9,        // wtf, doesn't exist in client...
    ERR_BATTLEGROUND_JOIN_RANGE_INDEX               = 10,       // Cannot join the queue unless all members of your party are in the same battleground level range.
    ERR_BATTLEGROUND_JOIN_TIMED_OUT                 = 11,       // %s was unavailable to join the queue. (uint64 guid exist in client cache)
    //ERR_BATTLEGROUND_JOIN_TIMED_OUT               = 12,       // same as 11
    //ERR_BATTLEGROUND_TEAM_LEFT_QUEUE              = 13,       // same as 7
    ERR_LFG_CANT_USE_BATTLEGROUND                   = 14,       // You cannot queue for a battleground or arena while using the dungeon system.
    ERR_IN_RANDOM_BG                                = 15,       // Can't do that while in a Random Battleground queue.
    ERR_IN_NON_RANDOM_BG                            = 16,       // Can't queue for Random Battleground while in another Battleground queue.
    ERR_BG_DEVELOPER_ONLY                           = 17,
    ERR_BATTLEGROUND_INVITATION_DECLINED            = 18,
    ERR_MEETING_STONE_NOT_FOUND                     = 19,
    ERR_WARGAME_REQUEST_FAILURE                     = 20,
    ERR_BATTLEFIELD_TEAM_PARTY_SIZE                 = 22,
    ERR_NOT_ON_TOURNAMENT_REALM                     = 23,
    ERR_BATTLEGROUND_PLAYERS_FROM_DIFFERENT_REALMS  = 24,
    ERR_REMOVE_FROM_PVP_QUEUE_GRANT_LEVEL           = 33,
    ERR_REMOVE_FROM_PVP_QUEUE_FACTION_CHANGE        = 34,
    ERR_BATTLEGROUND_JOIN_FAILED                    = 35,
    ERR_BATTLEGROUND_DUPE_QUEUE                     = 43
};

enum PetNameInvalidReason
{
    // custom, not send
    PET_NAME_SUCCESS                                        = 0,

    PET_NAME_INVALID                                        = 1,
    PET_NAME_NO_NAME                                        = 2,
    PET_NAME_TOO_SHORT                                      = 3,
    PET_NAME_TOO_LONG                                       = 4,
    PET_NAME_MIXED_LANGUAGES                                = 6,
    PET_NAME_PROFANE                                        = 7,
    PET_NAME_RESERVED                                       = 8,
    PET_NAME_THREE_CONSECUTIVE                              = 11,
    PET_NAME_INVALID_SPACE                                  = 12,
    PET_NAME_CONSECUTIVE_SPACES                             = 13,
    PET_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS          = 14,
    PET_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END   = 15,
    PET_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME              = 16
};

enum DungeonStatusFlag
{
    DUNGEON_STATUSFLAG_NORMAL = 0x01,
    DUNGEON_STATUSFLAG_HEROIC = 0x02,

    RAID_STATUSFLAG_10MAN_NORMAL = 0x01,
    RAID_STATUSFLAG_25MAN_NORMAL = 0x02,
    RAID_STATUSFLAG_10MAN_HEROIC = 0x04,
    RAID_STATUSFLAG_25MAN_HEROIC = 0x08
};

#define VOID_STORAGE_UNLOCK       100*GOLD
#define VOID_STORAGE_STORE_ITEM   25*GOLD
#define VOID_STORAGE_MAX_DEPOSIT  9
#define VOID_STORAGE_MAX_WITHDRAW 9
#define VOID_STORAGE_MAX_SLOT     80

enum VoidTransferError
{
    VOID_TRANSFER_ERROR_NO_ERROR          = 0,
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_1  = 1,
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_2  = 2,
    VOID_TRANSFER_ERROR_FULL              = 3,
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_3  = 4,
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_4  = 5,
    VOID_TRANSFER_ERROR_NOT_ENOUGH_MONEY  = 6,
    VOID_TRANSFER_ERROR_INVENTORY_FULL    = 7,
    VOID_TRANSFER_ERROR_INTERNAL_ERROR_5  = 8,
    VOID_TRANSFER_ERROR_TRANSFER_UNKNOWN  = 9,
};

#define CURRENCY_PRECISION 100

enum PartyResult
{
    ERR_PARTY_RESULT_OK                 = 0,
    ERR_BAD_PLAYER_NAME_S               = 1,
    ERR_TARGET_NOT_IN_GROUP_S           = 2,
    ERR_TARGET_NOT_IN_INSTANCE_S        = 3,
    ERR_GROUP_FULL                      = 4,
    ERR_ALREADY_IN_GROUP_S              = 5,
    ERR_NOT_IN_GROUP                    = 6,
    ERR_NOT_LEADER                      = 7,
    ERR_PLAYER_WRONG_FACTION            = 8,
    ERR_IGNORING_YOU_S                  = 9,
    ERR_LFG_PENDING                     = 12,
    ERR_INVITE_RESTRICTED               = 13,
    ERR_GROUP_SWAP_FAILED               = 14,               // if (PartyOperation == PARTY_OP_SWAP) ERR_GROUP_SWAP_FAILED else ERR_INVITE_IN_COMBAT
    ERR_INVITE_UNKNOWN_REALM            = 15,
    ERR_INVITE_NO_PARTY_SERVER          = 16,
    ERR_INVITE_PARTY_BUSY               = 17,
    ERR_PARTY_TARGET_AMBIGUOUS          = 18,
    ERR_PARTY_LFG_INVITE_RAID_LOCKED    = 19,
    ERR_PARTY_LFG_BOOT_LIMIT            = 20,
    ERR_PARTY_LFG_BOOT_COOLDOWN_S       = 21,
    ERR_PARTY_LFG_BOOT_IN_PROGRESS      = 22,
    ERR_PARTY_LFG_BOOT_TOO_FEW_PLAYERS  = 23,
    ERR_PARTY_LFG_BOOT_NOT_ELIGIBLE_S   = 24,
    ERR_RAID_DISALLOWED_BY_LEVEL        = 25,
    ERR_PARTY_LFG_BOOT_IN_COMBAT        = 26,
    ERR_VOTE_KICK_REASON_NEEDED         = 27,
    ERR_PARTY_LFG_BOOT_DUNGEON_COMPLETE = 28,
    ERR_PARTY_LFG_BOOT_LOOT_ROLLS       = 29,
    ERR_PARTY_LFG_TELEPORT_IN_COMBAT    = 30
};

enum DiminishingLevels
{
    DIMINISHING_LEVEL_1             = 0,
    DIMINISHING_LEVEL_2             = 1,
    DIMINISHING_LEVEL_3             = 2,
    DIMINISHING_LEVEL_IMMUNE        = 3,
    DIMINISHING_LEVEL_4             = 3,
    DIMINISHING_LEVEL_TAUNT_IMMUNE  = 4
};

enum WeaponAttackType : uint8
{
    BASE_ATTACK   = 0,
    OFF_ATTACK    = 1,
    RANGED_ATTACK = 2,
    MAX_ATTACK
};

enum CharterTypes
{
    CHARTER_TYPE_NONE = 0,
    CHARTER_TYPE_ANY = 10,

    GUILD_CHARTER_TYPE = 9,
    ARENA_TEAM_CHARTER_2v2_TYPE = 2,
    ARENA_TEAM_CHARTER_3v3_TYPE = 3,
    ARENA_TEAM_CHARTER_5v5_TYPE = 5
};

enum LineOfSightChecks
{
    LINEOFSIGHT_CHECK_VMAP      = 0x1, // check static floor layout data
    LINEOFSIGHT_CHECK_GOBJECT   = 0x2, // check dynamic game object data

    LINEOFSIGHT_ALL_CHECKS      = (LINEOFSIGHT_CHECK_VMAP | LINEOFSIGHT_CHECK_GOBJECT)
};

enum ContentLevels : uint8
{
    CONTENT_1_60    = 0,
    CONTENT_61_70   = 1,
    CONTENT_71_80   = 2,
    CONTENT_81_85   = 3,
    MAX_CONTENT
};

enum UpdateCollisionHeightReason : uint8
{
    UPDATE_COLLISION_HEIGHT_MOUNT = 0,
    UPDATE_COLLISION_HEIGHT_SCALE = 1
};

enum class MountResult : uint32
{
    InvalidMountee = 0,
    TooFarAway     = 1,
    AlreadyMounted = 2,
    NotMountable   = 3,
    NotYourPet     = 4,
    Other          = 5,
    Looting        = 6,
    RaceCantMount  = 7,
    Shapeshifted   = 8,
    ForcedDismount = 9,
    Ok             = 10 // never sent
};

enum AreaId : uint32
{
    AREA_WINTERGRASP                = 4197,
    AREA_THE_SUNKEN_RING            = 4538,
    AREA_THE_BROKEN_TEMPLATE        = 4539,
    AREA_WINTERGRASP_FORTRESS       = 4575,
    AREA_THE_CHILLED_QUAGMIRE       = 4589,
    AREA_WESTPARK_WORKSHOP          = 4611,
    AREA_EASTPARK_WORKSHOP          = 4612,
    AREA_TOLBARAD                   = 5095
};

enum WorldState : uint32
{
    WS_CURRENT_PVP_SEASON_ID                = 3191,
    WS_PREVIOUS_PVP_SEASON_ID               = 3901,

    WS_TEAM_IN_INSTANCE_ALLIANCE            = 4485,
    WS_TEAM_IN_INSTANCE_HORDE               = 4486,

    WS_BATTLEFIELD_WG_VEHICLE_H             = 3490,
    WS_BATTLEFIELD_WG_MAX_VEHICLE_H         = 3491,
    WS_BATTLEFIELD_WG_VEHICLE_A             = 3680,
    WS_BATTLEFIELD_WG_MAX_VEHICLE_A         = 3681,
    WS_BATTLEFIELD_WG_WORKSHOP_K_W          = 3698,
    WS_BATTLEFIELD_WG_WORKSHOP_K_E          = 3699,
    WS_BATTLEFIELD_WG_WORKSHOP_NW           = 3700,
    WS_BATTLEFIELD_WG_WORKSHOP_NE           = 3701,
    WS_BATTLEFIELD_WG_WORKSHOP_SW           = 3702,
    WS_BATTLEFIELD_WG_WORKSHOP_SE           = 3703,
    WS_BATTLEFIELD_WG_SHOW_TIME_BATTLE_END  = 3710,
    WS_BATTLEFIELD_WG_TIME_BATTLE_END       = 3781,
    WS_BATTLEFIELD_WG_SHOW_TIME_NEXT_BATTLE = 3801,
    WS_BATTLEFIELD_WG_DEFENDER              = 3802,
    WS_BATTLEFIELD_WG_ATTACKER              = 3803,
    WS_BATTLEFIELD_WG_ATTACKED_H            = 4022,
    WS_BATTLEFIELD_WG_ATTACKED_A            = 4023,
    WS_BATTLEFIELD_WG_DEFENDED_H            = 4024,
    WS_BATTLEFIELD_WG_DEFENDED_A            = 4025,
    WS_BATTLEFIELD_WG_TIME_NEXT_BATTLE      = 4354,

        WS_BATTLEFIELD_TB_ALLIANCE_CONTROLS_SHOW  = 5385,
    WS_BATTLEFIELD_TB_HORDE_CONTROLS_SHOW     = 5384,
    WS_BATTLEFIELD_TB_ALLIANCE_ATTACKING_SHOW = 5546,
    WS_BATTLEFIELD_TB_HORDE_ATTACKING_SHOW    = 5547,

    WS_BATTLEFIELD_TB_BUILDINGS_CAPTURED      = 5348,
    WS_BATTLEFIELD_TB_BUILDINGS_CAPTURED_SHOW = 5349,
    WS_BATTLEFIELD_TB_TOWERS_DESTROYED        = 5347,
    WS_BATTLEFIELD_TB_TOWERS_DESTROYED_SHOW   = 5350,

    WS_BATTLEFIELD_TB_FACTION_CONTROLLING = 5334, // 1 -> Alliance, 2 -> Horde

    WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE      = 5332,
    WS_BATTLEFIELD_TB_TIME_NEXT_BATTLE_SHOW = 5387,
    WS_BATTLEFIELD_TB_TIME_BATTLE_END       = 5333,
    WS_BATTLEFIELD_TB_TIME_BATTLE_END_SHOW  = 5346,

    WS_BATTLEFIELD_TB_STATE_PREPARATIONS = 5684,
    WS_BATTLEFIELD_TB_STATE_BATTLE       = 5344,

    WS_BATTLEFIELD_TB_KEEP_HORDE    = 5469,
    WS_BATTLEFIELD_TB_KEEP_ALLIANCE = 5470,

    WS_BATTLEFIELD_TB_GARRISON_HORDE_CONTROLLED    = 5418,
    WS_BATTLEFIELD_TB_GARRISON_HORDE_CAPTURING     = 5419,
    WS_BATTLEFIELD_TB_GARRISON_NEUTRAL             = 5420, // unused
    WS_BATTLEFIELD_TB_GARRISON_ALLIANCE_CAPTURING  = 5421,
    WS_BATTLEFIELD_TB_GARRISON_ALLIANCE_CONTROLLED = 5422,

    WS_BATTLEFIELD_TB_VIGIL_HORDE_CONTROLLED    = 5423,
    WS_BATTLEFIELD_TB_VIGIL_HORDE_CAPTURING     = 5424,
    WS_BATTLEFIELD_TB_VIGIL_NEUTRAL             = 5425, // unused
    WS_BATTLEFIELD_TB_VIGIL_ALLIANCE_CAPTURING  = 5426,
    WS_BATTLEFIELD_TB_VIGIL_ALLIANCE_CONTROLLED = 5427,

    WS_BATTLEFIELD_TB_SLAGWORKS_HORDE_CONTROLLED    = 5428,
    WS_BATTLEFIELD_TB_SLAGWORKS_HORDE_CAPTURING     = 5429,
    WS_BATTLEFIELD_TB_SLAGWORKS_NEUTRAL             = 5430, // unused
    WS_BATTLEFIELD_TB_SLAGWORKS_ALLIANCE_CAPTURING  = 5431,
    WS_BATTLEFIELD_TB_SLAGWORKS_ALLIANCE_CONTROLLED = 5432,

    WS_BATTLEFIELD_TB_WEST_INTACT_HORDE      = 5433,
    WS_BATTLEFIELD_TB_WEST_DAMAGED_HORDE     = 5434,
    WS_BATTLEFIELD_TB_WEST_DESTROYED_NEUTRAL = 5435,
    WS_BATTLEFIELD_TB_WEST_INTACT_ALLIANCE   = 5436,
    WS_BATTLEFIELD_TB_WEST_DAMAGED_ALLIANCE  = 5437,
    WS_BATTLEFIELD_TB_WEST_INTACT_NEUTRAL    = 5453, // unused
    WS_BATTLEFIELD_TB_WEST_DAMAGED_NEUTRAL   = 5454, // unused

    WS_BATTLEFIELD_TB_SOUTH_INTACT_HORDE      = 5438,
    WS_BATTLEFIELD_TB_SOUTH_DAMAGED_HORDE     = 5439,
    WS_BATTLEFIELD_TB_SOUTH_DESTROYED_NEUTRAL = 5440,
    WS_BATTLEFIELD_TB_SOUTH_INTACT_ALLIANCE   = 5441,
    WS_BATTLEFIELD_TB_SOUTH_DAMAGED_ALLIANCE  = 5442,
    WS_BATTLEFIELD_TB_SOUTH_INTACT_NEUTRAL    = 5455, // unused
    WS_BATTLEFIELD_TB_SOUTH_DAMAGED_NEUTRAL   = 5456, // unused

    WS_BATTLEFIELD_TB_EAST_INTACT_HORDE      = 5443,
    WS_BATTLEFIELD_TB_EAST_DAMAGED_HORDE     = 5444,
    WS_BATTLEFIELD_TB_EAST_DESTROYED_NEUTRAL = 5445,
    WS_BATTLEFIELD_TB_EAST_INTACT_ALLIANCE   = 5446,
    WS_BATTLEFIELD_TB_EAST_DAMAGED_ALLIANCE  = 5447,
    WS_BATTLEFIELD_TB_EAST_INTACT_NEUTRAL    = 5451,
    WS_BATTLEFIELD_TB_EAST_DAMAGED_NEUTRAL   = 5452
};

enum class PursuingType : uint8
{
    Follow      = 0,
    Chase       = 1,
    Formation   = 2,
    Max         = 3
};


enum RaidGroupReason
{
    RAID_GROUP_ERR_NONE                 = 0,
    RAID_GROUP_ERR_LOWLEVEL             = 1, // "You are too low level to enter this instance."
    RAID_GROUP_ERR_ONLY                 = 2, // "You must be in a raid group to enter this instance."
    RAID_GROUP_ERR_FULL                 = 3, // "The instance is full."
    RAID_GROUP_ERR_REQUIREMENTS_UNMATCH = 4  // "You do not meet the requirements to enter this instance."
};

enum class SummonRaidMemberValidateReasonCode : int32
{
    None                = 0,
    RealmMismatch       = 1,
    RaidLocked          = 2,
    MapConditionFailed  = 3,
    DeadOrGhost         = 4,
    Offline             = 5
};

#define MAX_CREATURE_SPELL_DATA_SLOT 4

#endif
