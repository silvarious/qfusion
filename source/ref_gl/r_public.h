/*
Copyright (C) 2002-2007 Victor Luchits

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
#ifndef __R_PUBLIC_H__
#define __R_PUBLIC_H__

#include "../cgame/ref.h"

#define REF_API_VERSION 1

struct mempool_s;
struct cinematics_s;

typedef struct mempool_s mempool_t;
typedef struct cinematics_s cinematics_t;

//
// these are the functions exported by the refresh module
//
typedef struct
{
	// halts the application or drops to console
	void ( *Com_Error )( com_error_code_t code, const char *format, ... );

	// console messages
	void ( *Com_Printf )( const char *format, ... );
	void ( *Com_DPrintf )( const char *format, ... );

	// console variable interaction
	cvar_t *( *Cvar_Get )( const char *name, const char *value, int flags );
	cvar_t *( *Cvar_Set )( const char *name, const char *value );
	cvar_t *( *Cvar_ForceSet )( const char *name, const char *value );      // will return 0 0 if not found
	void ( *Cvar_SetValue )( const char *name, float value );
	float ( *Cvar_Value )( const char *name );
	const char *( *Cvar_String )( const char *name );

	int ( *Cmd_Argc )( void );
	char *( *Cmd_Argv )( int arg );
	char *( *Cmd_Args )( void );        // concatenation of all argv >= 1
	void ( *Cmd_AddCommand )( const char *name, void ( *cmd )( void ) );
	void ( *Cmd_RemoveCommand )( const char *cmd_name );
	void ( *Cmd_ExecuteText )( int exec_when, const char *text );
	void ( *Cmd_Execute )( void );
	void ( *Cmd_SetCompletionFunc )( const char *cmd_name, char **( *completion_func )( const char *partial ) );

	unsigned int ( *Sys_Milliseconds )( void );
	quint64 ( *Sys_Microseconds )( void );

	unsigned int (* Hash_BlockChecksum )( const qbyte * data, size_t len );
	unsigned int (* Hash_SuperFastHash )( const qbyte * data, size_t len, unsigned int seed );

	int ( *FS_FOpenFile )( const char *filename, int *filenum, int mode );
	int ( *FS_FOpenAbsoluteFile )( const char *filename, int *filenum, int mode );
	int ( *FS_Read )( void *buffer, size_t len, int file );
	int ( *FS_Write )( const void *buffer, size_t len, int file );
	int ( *FS_Printf )( int file, const char *format, ... );
	int ( *FS_Tell )( int file );
	int ( *FS_Seek )( int file, int offset, int whence );
	int ( *FS_Eof )( int file );
	int ( *FS_Flush )( int file );
	void ( *FS_FCloseFile )( int file );
	qboolean ( *FS_RemoveFile )( const char *filename );
	int ( *FS_GetFileList )( const char *dir, const char *extension, char *buf, size_t bufsize, int start, int end );
	int ( *FS_GetGameDirectoryList )( char *buf, size_t bufsize );
	const char *( *FS_FirstExtension )( const char *filename, const char *extensions[], int num_extensions );
	qboolean ( *FS_MoveFile )( const char *src, const char *dst );
	qboolean ( *FS_IsUrl )( const char *url );
	time_t ( *FS_FileMTime )( const char *filename );
	qboolean ( *FS_RemoveDirectory )( const char *dirname );
	const char * ( *FS_GameDirectory )( void );
	const char * ( *FS_WriteDirectory )( void );

	cinematics_t *( *CIN_Open )( const char *name, unsigned int start_time, qboolean loop, qboolean audio );
	qboolean ( *CIN_NeedNextFrame )( cinematics_t *cin, unsigned int curtime );
	qbyte *( *CIN_ReadNextFrame )( cinematics_t *cin, int *width, int *height, int *aspect_numerator, int *aspect_denominator, qboolean *redraw );
	void ( *CIN_Close )( cinematics_t *cin );

	mempool_t *( *Mem_AllocPool )( mempool_t *parent, const char *name, const char *filename, int fileline );
	void ( *Mem_FreePool )( mempool_t **pool, const char *filename, int fileline );
	void ( *Mem_EmptyPool )( mempool_t *pool, const char *filename, int fileline );
	void *( *Mem_AllocExt )( mempool_t *pool, size_t size, size_t alignment, int z, const char *filename, int fileline );
	void ( *Mem_Free )( void *data, const char *filename, int fileline );
	void *( *Mem_Realloc )( void *data, size_t size, const char *filename, int fileline );
	size_t ( *Mem_PoolTotalSize )( mempool_t *pool );
} ref_import_t;

typedef struct
{
	// if API is different, the dll cannot be used
	int			( *API )( void );

	rserr_t		( *Init )( const char *applicationName, const char *screenshotsPrefix,
					void *hinstance, void *wndproc, void *parenthWnd, 
					int x, int y, int width, int height, int displayFrequency,
					qboolean fullScreen, qboolean wideScreen, qboolean verbose );
	rserr_t		( *SetMode )( int x, int y, int width, int height, int displayFrequency,
					qboolean fullScreen, qboolean wideScreen );
	void		( *Shutdown )( qboolean verbose );

	// All data that will be used in a level should be
	// registered before rendering any frames to prevent disk hits,
	// but they can still be registered at a later time
	// if necessary.
	//
	// EndRegistration will free any remaining data that wasn't registered.
	// Any model_s, shader_s and skinfile_s pointers from before 
	// the BeginRegistration are no longer valid after EndRegistration.
	void		( *BeginRegistration )( void );
	void		( *EndRegistration )( void );

	void		( *ModelBounds )( const struct model_s *model, vec3_t mins, vec3_t maxs );
	void		( *ModelFrameBounds )( const struct model_s *model, int frame, vec3_t mins, vec3_t maxs );

	void		( *RegisterWorldModel )( const char *model, const dvis_t *pvsData );
	struct model_s *( *RegisterModel )( const char *name );
	struct shader_s *( *RegisterPic )( const char *name );
	struct shader_s *( *RegisterRawPic )( const char *name, int width, int height, qbyte *data );
	struct shader_s *( *RegisterLevelshot )( const char *name, struct shader_s *defaultShader, qboolean *matchesDefault );
	struct shader_s *( *RegisterSkin )( const char *name );
	struct skinfile_s *( *RegisterSkinFile )( const char *name );
	struct shader_s *( *RegisterVideo )( const char *name );

	void		( *RemapShader )( const char *from, const char *to, int timeOffset );
	void		( *GetShaderDimensions )( const struct shader_s *shader, int *width, int *height );

	void		( *ClearScene )( void );
	void		( *AddEntityToScene )( const entity_t *ent );
	void		( *AddLightToScene )( const vec3_t org, float intensity, float r, float g, float b );
	void		( *AddPolyToScene )( const poly_t *poly );
	void		( *AddLightStyleToScene )( int style, float r, float g, float b );
	void		( *RenderScene )( const refdef_t *fd );

	void		( *DrawStretchPic )( int x, int y, int w, int h, float s1, float t1, float s2, float t2, 
								 const float *color, const struct shader_s *shader );
	void		( *DrawRotatedStretchPic )( int x, int y, int w, int h, float s1, float t1, float s2, float t2, 
								 float angle, const vec4_t color, const struct shader_s *shader );
	void		( *DrawStretchRaw )( int x, int y, int w, int h, int cols, int rows, qbyte *data );
	void		( *DrawStretchPoly )( const poly_t *poly, float x_offset, float y_offset );
	void		( *SetScissorRegion )( int x, int y, int w, int h );
	void		( *GetScissorRegion )( int *x, int *y, int *w, int *h );

	void		( *SetCustomColor )( int num, int r, int g, int b );
	void		( *LightForOrigin )( const vec3_t origin, vec3_t dir, vec4_t ambient, vec4_t diffuse, float radius );

	qboolean	( *LerpTag )( orientation_t *orient, const struct model_s *mod, int oldframe, int frame, float lerpfrac,
						  const char *name );

	int			( *SkeletalGetNumBones )( const struct model_s *mod, int *numFrames );
	int			( *SkeletalGetBoneInfo )( const struct model_s *mod, int bone, char *name, size_t name_size, int *flags );
	void		( *SkeletalGetBonePose )( const struct model_s *mod, int bone, int frame, bonepose_t *bonepose );

	int			( *GetClippedFragments )( const vec3_t origin, float radius, vec3_t axis[3], int maxfverts, vec3_t *fverts, 
									  int maxfragments, fragment_t *fragments );

	void		( *TransformVectorToScreen )( const refdef_t *rd, const vec3_t in, vec2_t out );

	void		( *BeginFrame )( float cameraSeparation, qboolean forceClear );
	void		( *EndFrame )( void );
	const char *( *SpeedsMessage )( char *out, size_t size );

	void		( *BeginAviDemo )( void );
	void		( *WriteAviFrame )( int frame, qboolean scissor );
	void		( *StopAviDemo )( void );

	void		( *AppActivate )( qboolean active, qboolean destroy );
} ref_export_t;

typedef ref_export_t *(*GetRefAPI_t)(const ref_import_t *imports);

#ifdef REF_HARD_LINKED
#ifdef __cplusplus
extern "C" {
#endif
	ref_export_t *GetRefAPI( ref_import_t *import );
#ifdef __cplusplus
}
#endif
#endif

#endif /*__R_PUBLIC_H__*/
