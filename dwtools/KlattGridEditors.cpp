/* KlattGridEditors.cpp
 *
 * Copyright (C) 2009-2019 David Weenink, 2021 Paul Boersma
 *
 * This code is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 * This code is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this work. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * djmw 20090123
 * djmw 20090128 Remove source menu from formant grid editor.
 * djmw 20090420 dbEditor
 * djmw 20090527 Protect FormantGridEditor against empty FormantGrids.
 * djmw 20110304 Thing_new
 */

#include "KlattGridEditors.h"
#include "EditorM.h"

static void KlattGrid_Editor_defaultPlay (KlattGrid me, double tmin, double tmax) {
	my options -> xmin = tmin;
	my options-> xmax = tmax;
	KlattGrid_playSpecial (me);
}

/************************** KlattGrid_RealTierEditor *********************************/

Thing_implement (KlattGrid_RealTierEditor, RealTierEditor, 0);

static void menu_cb_KlattGridHelp (KlattGrid_RealTierEditor, EDITOR_ARGS_DIRECT) {
	Melder_help (U"KlattGrid");
}

void structKlattGrid_RealTierEditor :: v_createHelpMenuItems (EditorMenu menu) {
	KlattGrid_RealTierEditor_Parent :: v_createHelpMenuItems (menu);
	EditorMenu_addCommand (menu, U"KlattGrid help", 0, menu_cb_KlattGridHelp);
}

void structKlattGrid_RealTierEditor :: v_play (double startTime, double endTime) {
	KlattGrid_Editor_defaultPlay (klattgrid, startTime, endTime);
}

void KlattGrid_RealTierEditor_init (KlattGrid_RealTierEditor me, autoKlattGrid_RealTierArea area, conststring32 title, KlattGrid klattgrid) {
	my klattgrid = klattgrid;
	RealTierEditor_init (me, area.move(), autoSoundArea(), title, false);
}

/************************** KlattGrid_PitchTierEditor *********************************/

Thing_implement (KlattGrid_PitchTierEditor, KlattGrid_RealTierEditor, 0);

static void menu_cb_KlattGrid_PitchTierEditorHelp (KlattGrid_PitchTierEditor, EDITOR_ARGS_DIRECT) {
	Melder_help (U"PitchTierEditor");
}

static void menu_cb_PitchTierHelp (KlattGrid_PitchTierEditor, EDITOR_ARGS_DIRECT) {
	Melder_help (U"PitchTier");
}

void structKlattGrid_PitchTierEditor :: v_createHelpMenuItems (EditorMenu menu) {
	EditorMenu_addCommand (menu, U"PitchTierEditor help", 0, menu_cb_KlattGrid_PitchTierEditorHelp);
	EditorMenu_addCommand (menu, U"PitchTier help", 0, menu_cb_PitchTierHelp);
}

autoKlattGrid_PitchTierEditor KlattGrid_PitchTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_PitchTierEditor me = Thing_new (KlattGrid_PitchTierEditor);
		const PitchTier pitchTier = klattgrid -> phonation -> pitch.get();
		autoKlattGrid_PitchTierArea area = KlattGrid_PitchTierArea_create (me.get(), pitchTier);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid pitch window not created.");
	}
}

/************************** KlattGrid_IntensityTierEditor *********************************/

Thing_implement (KlattGrid_IntensityTierEditor, KlattGrid_RealTierEditor, 0);

static void menu_cb_IntensityTierHelp (KlattGrid_IntensityTierEditor, EDITOR_ARGS_DIRECT) {
	Melder_help (U"IntensityTier");
}

void structKlattGrid_IntensityTierEditor :: v_createHelpMenuItems (EditorMenu menu) {
	KlattGrid_IntensityTierEditor_Parent :: v_createHelpMenuItems (menu);
	EditorMenu_addCommand (menu, U"IntensityTier help", 0, menu_cb_IntensityTierHelp);
}

void KlattGrid_IntensityTierEditor_init (KlattGrid_IntensityTierEditor me, autoKlattGrid_IntensityTierArea area, conststring32 title, KlattGrid klattgrid) {
	KlattGrid_RealTierEditor_init (me, area.move(), title, klattgrid);
}

/************************** KlattGrid_DecibelTierEditor *********************************/

Thing_implement (KlattGrid_DecibelTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_DecibelTierEditor KlattGrid_DecibelTierEditor_create (conststring32 title, KlattGrid klattgrid, IntensityTier decibelTier) {
	try {
		autoKlattGrid_DecibelTierEditor me = Thing_new (KlattGrid_DecibelTierEditor);
		autoKlattGrid_DecibelTierArea area = KlattGrid_DecibelTierArea_create (me.get(), decibelTier);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid decibel window not created.");
	}
}

/************************** KlattGrid_VoicingAmplitudeTierEditor *********************************/

Thing_implement (KlattGrid_VoicingAmplitudeTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_VoicingAmplitudeTierEditor KlattGrid_VoicingAmplitudeTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_VoicingAmplitudeTierEditor me = Thing_new (KlattGrid_VoicingAmplitudeTierEditor);
		const IntensityTier voicingAmplitude = klattgrid -> phonation -> voicingAmplitude.get();
		autoKlattGrid_VoicingAmplitudeTierArea area = KlattGrid_VoicingAmplitudeTierArea_create (me.get(), voicingAmplitude);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid voicing amplitude window not created.");
	}
}

/************************** KlattGrid_AspirationAmplitudeTierEditor *********************************/

Thing_implement (KlattGrid_AspirationAmplitudeTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_AspirationAmplitudeTierEditor KlattGrid_AspirationAmplitudeTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_AspirationAmplitudeTierEditor me = Thing_new (KlattGrid_AspirationAmplitudeTierEditor);
		const IntensityTier aspirationAmplitude = klattgrid -> phonation -> aspirationAmplitude.get();
		autoKlattGrid_AspirationAmplitudeTierArea area = KlattGrid_AspirationAmplitudeTierArea_create (me.get(), aspirationAmplitude);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid aspiration amplitude window not created.");
	}
}

/************************** KlattGrid_BreathinessAmplitudeTierEditor *********************************/

Thing_implement (KlattGrid_BreathinessAmplitudeTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_BreathinessAmplitudeTierEditor KlattGrid_BreathinessAmplitudeTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_BreathinessAmplitudeTierEditor me = Thing_new (KlattGrid_BreathinessAmplitudeTierEditor);
		const IntensityTier breathinessAmplitude = klattgrid -> phonation -> breathinessAmplitude.get();
		autoKlattGrid_BreathinessAmplitudeTierArea area = KlattGrid_BreathinessAmplitudeTierArea_create (me.get(), breathinessAmplitude);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid breathiness amplitude window not created.");
	}
}

/************************** KlattGrid_SpectralTiltTierEditor *********************************/

Thing_implement (KlattGrid_SpectralTiltTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_SpectralTiltTierEditor KlattGrid_SpectralTiltTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_SpectralTiltTierEditor me = Thing_new (KlattGrid_SpectralTiltTierEditor);
		const IntensityTier spectralTilt = klattgrid -> phonation -> spectralTilt.get();
		autoKlattGrid_SpectralTiltTierArea area = KlattGrid_SpectralTiltTierArea_create (me.get(), spectralTilt);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid spectral tilt window not created.");
	}
}

/************************** KlattGrid_FricationBypassTierEditor *********************************/

Thing_implement (KlattGrid_FricationBypassTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_FricationBypassTierEditor KlattGrid_FricationBypassTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_FricationBypassTierEditor me = Thing_new (KlattGrid_FricationBypassTierEditor);
		const IntensityTier bypass = klattgrid -> frication -> bypass.get();
		autoKlattGrid_FricationBypassTierArea area = KlattGrid_FricationBypassTierArea_create (me.get(), bypass);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid frication bypass window not created.");
	}
}

/************************** KlattGrid_FricationAmplitudeTierEditor *********************************/

Thing_implement (KlattGrid_FricationAmplitudeTierEditor, KlattGrid_IntensityTierEditor, 0);

autoKlattGrid_FricationAmplitudeTierEditor KlattGrid_FricationAmplitudeTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_FricationAmplitudeTierEditor me = Thing_new (KlattGrid_FricationAmplitudeTierEditor);
		const IntensityTier fricationAmplitude = klattgrid -> frication -> fricationAmplitude.get();
		autoKlattGrid_FricationAmplitudeTierArea area = KlattGrid_FricationAmplitudeTierArea_create (me.get(), fricationAmplitude);
		KlattGrid_IntensityTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid frication amplitude window not created.");
	}
}

/************************** KlattGrid_OpenPhaseTierEditor *********************************/

Thing_implement (KlattGrid_OpenPhaseTierEditor, KlattGrid_RealTierEditor, 0);

autoKlattGrid_OpenPhaseTierEditor KlattGrid_OpenPhaseTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_OpenPhaseTierEditor me = Thing_new (KlattGrid_OpenPhaseTierEditor);
		const RealTier openPhase = klattgrid -> phonation -> openPhase.get();
		autoKlattGrid_OpenPhaseTierArea area = KlattGrid_OpenPhaseTierArea_create (me.get(), openPhase);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid open phase window not created.");
	}
}

/************************** KlattGrid_CollisionPhaseTierEditor *********************************/

Thing_implement (KlattGrid_CollisionPhaseTierEditor, KlattGrid_RealTierEditor, 0);

autoKlattGrid_CollisionPhaseTierEditor KlattGrid_CollisionPhaseTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_CollisionPhaseTierEditor me = Thing_new (KlattGrid_CollisionPhaseTierEditor);
		const RealTier collisionPhase = klattgrid -> phonation -> collisionPhase.get();
		autoKlattGrid_CollisionPhaseTierArea area = KlattGrid_CollisionPhaseTierArea_create (me.get(), collisionPhase);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid collision phase window not created.");
	}
}

/************************** KlattGrid_Power1TierEditor *********************************/

Thing_implement (KlattGrid_Power1TierEditor, KlattGrid_RealTierEditor, 0);

autoKlattGrid_Power1TierEditor KlattGrid_Power1TierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_Power1TierEditor me = Thing_new (KlattGrid_Power1TierEditor);
		const RealTier power1 = klattgrid -> phonation -> power1.get();
		autoKlattGrid_Power1TierArea area = KlattGrid_Power1TierArea_create (me.get(), power1);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid power1 window not created.");
	}
}

/************************** KlattGrid_Power2TierEditor *********************************/

Thing_implement (KlattGrid_Power2TierEditor, KlattGrid_RealTierEditor, 0);

autoKlattGrid_Power2TierEditor KlattGrid_Power2TierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_Power2TierEditor me = Thing_new (KlattGrid_Power2TierEditor);
		const RealTier power2 = klattgrid -> phonation -> power2.get();
		autoKlattGrid_Power2TierArea area = KlattGrid_Power2TierArea_create (me.get(), power2);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid power2 window not created.");
	}
}

/************************** KlattGrid_FlutterTierEditor *********************************/

Thing_implement (KlattGrid_FlutterTierEditor, KlattGrid_RealTierEditor, 0);

autoKlattGrid_FlutterTierEditor KlattGrid_FlutterTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_FlutterTierEditor me = Thing_new (KlattGrid_FlutterTierEditor);
		const RealTier flutter = klattgrid -> phonation -> flutter.get();
		autoKlattGrid_FlutterTierArea area = KlattGrid_FlutterTierArea_create (me.get(), flutter);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid flutter window not created.");
	}
}

/************************** KlattGrid_DoublePulsingTierEditor *********************************/

Thing_implement (KlattGrid_DoublePulsingTierEditor, KlattGrid_RealTierEditor, 0);

autoKlattGrid_DoublePulsingTierEditor KlattGrid_DoublePulsingTierEditor_create (conststring32 title, KlattGrid klattgrid) {
	try {
		autoKlattGrid_DoublePulsingTierEditor me = Thing_new (KlattGrid_DoublePulsingTierEditor);
		const RealTier doublePulsing = klattgrid -> phonation -> doublePulsing.get();
		autoKlattGrid_DoublePulsingTierArea area = KlattGrid_DoublePulsingTierArea_create (me.get(), doublePulsing);
		KlattGrid_RealTierEditor_init (me.get(), area.move(), title, klattgrid);
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid double pulsing window not created.");
	}
}

/************************** KlattGrid_FormantGridEditor *********************************/

Thing_implement (KlattGrid_FormantGridEditor, FormantGridEditor, 0);

static bool FormantGrid_isEmpty (FormantGrid me) {
	return my formants.size == 0 || my bandwidths.size == 0;
}

void structKlattGrid_FormantGridEditor :: v_play (double startTime, double endTime) {
	KlattGrid_Editor_defaultPlay (klattgrid, startTime, endTime);
}

autoKlattGrid_FormantGridEditor KlattGrid_FormantGridEditor_create (conststring32 title, KlattGrid data, kKlattGridFormantType formantType) {
	try {
		Melder_assert (data);
		autoFormantGrid* fg = KlattGrid_getAddressOfFormantGrid (data, formantType);
		Melder_require (! FormantGrid_isEmpty (fg -> get()),
			U"Cannot edit an empty formant grid.");
		
		autoKlattGrid_FormantGridEditor me = Thing_new (KlattGrid_FormantGridEditor);
		my klattgrid = data;
		FormantGridEditor_init (me.get(), title, fg->get());
		return me;
	} catch (MelderError) {
		Melder_throw (U"KlattGrid formant window not created.");
	}
}

/* End of file KlattGridEditors.cpp */
