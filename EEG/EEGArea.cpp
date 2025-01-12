/* EEGArea.cpp
 *
 * Copyright (C) 2022 Paul Boersma
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

#include "EEGArea.h"

Thing_implement (EEGArea, SoundArea, 0);

#include "Prefs_define.h"
#include "EEGArea_prefs.h"
#include "Prefs_install.h"
#include "EEGArea_prefs.h"
#include "Prefs_copyToInstance.h"
#include "EEGArea_prefs.h"

conststring32 structEEGArea :: v_getChannelName (integer channelNumber) {
	Melder_assert (our eeg);
	return our eeg -> channelNames [channelNumber].get();
}

/* End of file EEGArea.cpp */
