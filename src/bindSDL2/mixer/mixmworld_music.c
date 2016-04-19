/*
 * mixmworld_music.c
 *
 *  Created on: 2016.4.18
 *      Author: MapleLeaf
 */

/*
 * @file	mixmworld_music.c
 * @author  MapleLeaf
 * @date	2016.4.18
 * @brief
 * 
 */

#include <mixmworld_music.h>

#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

Mix_Music **_mixm_Music_PointList;
char **_mixm_Music_NameList;
char *ConstString(const char *in){
	char *out=(char *)malloc(strlen(in)+1);
	return strcpy(out,in);
}
	
int mixm_Music_Init(int chunkSize){
	if(chunkSize<=0)
		chunkSize = 512;

	Mix_Init(MIX_INIT_MP3|MIX_INIT_FLAC|MIX_INIT_OGG|MIX_INIT_MOD);
	if (
			!Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 4 /*MIX_DEFAULT_CHANNELS*/, chunkSize)
			&&\
	!_mixm_Music_NameList&&!_mixm_Music_PointList){
		_mixm_Music_PointList = (Mix_Music **)calloc(sizeof (Mix_Music *),USHRT_MAX);
		_mixm_Music_NameList = (char **)calloc(sizeof (char *),USHRT_MAX);
		atexit(mixm_Music_Quit);
		return 0;
	}
	return -1;
}

int mixm_Music_InitEx(int frequency, Uint16 format, int channels, int chunksize){
	if (!Mix_OpenAudio(frequency, format, channels, chunksize)&&\
	!_mixm_Music_NameList&&!_mixm_Music_PointList){
		_mixm_Music_PointList = (Mix_Music **)calloc(sizeof (Mix_Music *),USHRT_MAX);
		_mixm_Music_NameList = (char **)calloc(sizeof (char *),USHRT_MAX);
		atexit(mixm_Music_Quit);
		return 0;
	}
	return -1;
}

void mixm_Music_Quit(void){
	free(_mixm_Music_NameList);
	free(_mixm_Music_PointList);
	Mix_Quit();
}

int mixm_Music_Load(ID id,const char *fname){
	if (_mixm_Music_PointList[id])
		return 1;
	if ((_mixm_Music_PointList[id] = Mix_LoadMUS(fname))==NULL)
		return -1;
	_mixm_Music_NameList[id] = ConstString(fname);
	return 0;
}

int mixm_Music_Set(ID id,const char *fname){
	if (_mixm_Music_PointList[id])
		mixm_Music_Del(id);
	if (!(_mixm_Music_PointList[id] = Mix_LoadMUS(fname)))
		return -1;
	_mixm_Music_NameList[id] = ConstString(fname);
	return 0;
}

int mixm_Music_Del(ID id){
	if (!_mixm_Music_PointList[id])
		return 1;
	Mix_FreeMusic(_mixm_Music_PointList[id]);
	free(_mixm_Music_NameList[id]);
	_mixm_Music_NameList[id]=NULL;
	_mixm_Music_PointList[id]=NULL;
	return 0;
}

const char* mixm_Music_GetNameofID(ID id){
	return _mixm_Music_NameList[id];
}

int mixm_Music_Play(ID id,int loop){
	if (!_mixm_Music_PointList[id])
		return 1;
	Mix_PlayMusic(_mixm_Music_PointList[id],loop);
	return 0;
}

int mixm_Music_Pause(ID id){
	Mix_PauseMusic();
	return 0;
}

int mixm_Music_Resume(ID id){
	Mix_ResumeMusic();
	return 0;
}

int mixm_Music_Rewind(ID id){
	Mix_RewindMusic();
	return 0;
}

