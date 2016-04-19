/*
 * mixmworld_music.h
 *
 *  Created on: 2016.4.17
 *      Author: yami
 */

/*
 * @file	mixmworld_music.h
 * @author	yami
 * @date	2016.4.17
 * @brief
 * 
 * @updataer MapleLeaf
 * @date	2016.4.18
 */

#ifndef INCLUDE_MIXMWORLD_MUSIC_H_
#define INCLUDE_MIXMWORLD_MUSIC_H_


#include <mixmworld.h>

char *ConstString(const char *in);

#define NORMAL_CHUNK_SIZE 2048


typedef unsigned short ID;

int mixm_Music_Init(int chunkSize);
int mixm_Music_InitEx(int frequency, uint16_t format, int channels, int chunksize);
void mixm_Music_Quit(void);

int mixm_Music_Load(ID id,const char *fname);
int mixm_Music_Set(ID id,const char *fname);
int mixm_Music_Del(ID id);

const char* mixm_Music_GetNameofID(ID id);

//Because Mixer Music can't play more music in one time
//so id on function of pause,resume and rewind can't use.
int mixm_Music_Play(ID id,int loop);
int mixm_Music_Pause(ID id);
int mixm_Music_Resume(ID id);
int mixm_Music_Rewind(ID id);


#endif /* INCLUDE_MIXMWORLD_MUSIC_H_ */
