/*
 * bootloader.h
 *
 *  Created on: 12 Aug 2015
 *      Author: Steve
 */

#ifndef SOURCES_BOOTLOADER_H_
#define SOURCES_BOOTLOADER_H_

void nmain();

void BL_Erase();
void BL_Flash(char filename[]);

#ifdef __cplusplus
	extern "C" {
#endif
	void BL_CheckForUserApp();
	void mainentry();
#ifdef __cplusplus
	}
#endif


#endif /* SOURCES_BOOTLOADER_H_ */
