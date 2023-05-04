#pragma once
#include "Melodie.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Melodie createMelodie(char* titlu, char* artist, int durata) {
	Melodie m;
	int nrC = (int) strlen(titlu)+1;
	m.titlu = malloc( nrC* sizeof(char));
	strcpy_s(m.titlu, nrC, titlu);

	nrC = (int) strlen(artist) + 1;
	m.artist = malloc(nrC* sizeof(char));
	strcpy_s(m.artist, nrC, artist);

	m.durata = durata;
	return m;
}

void destroyMelodie(Melodie* m) {
	free(m->titlu);
	free(m->artist);
	/*m->titlu[0] = '\0';
	m->artist[0] = '\0';*/
	m->durata = -1;
}

Melodie copyMelodie(Melodie m) {
	return createMelodie(m.titlu, m.artist, m.durata);
}
int valideazaMelodie(Melodie m) {
	if (strlen(m.titlu) == 0)
		return 0;
	if (strlen(m.artist) == 0)
		return 0;
	if (m.durata<0 || m.durata > 180)
		return 0;
	return 1;
}

void testCreateDestroy() {
	Melodie m = createMelodie("Child in Time", "Deep Purple", 23);

	assert(strcmp(m.titlu, "Child in Time") == 0);
	assert(strcmp(m.artist, "Deep Purple") == 0);
	assert(m.durata==23);

	destroyMelodie(&m);
	

}

void testValideaza() {
	Melodie m1 = createMelodie("", "Deep Purple", 23);
	assert(valideazaMelodie(m1) == 0);

	Melodie m2 = createMelodie("ABC", "", 23);
	assert(valideazaMelodie(m2) == 0);

	Melodie m3 = createMelodie("Child in Time", "Deep Purple", -8);
	assert(valideazaMelodie(m3) == 0);

	Melodie m4 = createMelodie("Child in Time", "Deep Purple", 188);
	assert(valideazaMelodie(m4) == 0);

	Melodie m5 = createMelodie("Child in Time", "Deep Purple", 48);
	assert(valideazaMelodie(m5) == 1);

	destroyMelodie(&m1);
	destroyMelodie(&m2);
	destroyMelodie(&m3);
	destroyMelodie(&m4);
	destroyMelodie(&m5);


}