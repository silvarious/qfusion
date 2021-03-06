/*
Copyright (C) 1997-2001 Id Software, Inc.

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

#include "../client/client.h"
#include "x11.h"

x11display_t x11display;

static int VID_WndProc( x11display_t *wnd, int ev, int p1, int p2 )
{
	x11display = *wnd;
	return 0;
}

/*
* VID_Sys_Init
*/
int VID_Sys_Init( int x, int y, int width, int height, int displayFrequency,
	void *parentWindow, qboolean fullScreen, qboolean wideScreen, qboolean verbose )
{
	x11display.dpy = NULL;

	return re.Init( APPLICATION, APP_SCREENSHOTS_PREFIX,
		NULL, &VID_WndProc, parentWindow, 
		x, y, width, height, displayFrequency,
		fullScreen, wideScreen, verbose );
}

/*
* VID_Front_f
*/
void VID_Front_f( void )
{
}

/*
* VID_UpdateWindowPosAndSize
*/
void VID_UpdateWindowPosAndSize( int x, int y )
{
}

/*
* VID_EnableAltTab
*/
void VID_EnableAltTab( qboolean enable )
{
}

/*
* VID_GetWindowHandle - The sound module may require the handle when using Window's directsound
*/
void *VID_GetWindowHandle( void )
{
	return ( void * )NULL;
}

/*
* VID_EnableWinKeys
*/
void VID_EnableWinKeys( qboolean enable )
{
}

/*
* _NET_WM_STATE_DEMANDS_ATTENTION
*
* Tell Window-Manager that application demands user attention
*/
static void _NET_WM_STATE_DEMANDS_ATTENTION( void )
{
	XEvent xev;
	Atom wm_state;
	Atom wm_demandsAttention;

	if( !x11display.dpy ) {
		return;
	}

	wm_state = XInternAtom( x11display.dpy, "_NET_WM_STATE", False );
	wm_demandsAttention = XInternAtom( x11display.dpy, "_NET_WM_STATE_DEMANDS_ATTENTION", False );

	memset(&xev, 0, sizeof(xev));
	xev.type = ClientMessage;
	xev.xclient.window = x11display.win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = 1;
	xev.xclient.data.l[1] = wm_demandsAttention;

	XSendEvent( x11display.dpy, DefaultRootWindow( x11display.dpy ), False,
		SubstructureNotifyMask, &xev );
}

/*
** VID_FlashWindow
*
* Sends a flash message to inactive window
*/
void VID_FlashWindow( int count )
{
	if( x11display.dpy ) {
		_NET_WM_STATE_DEMANDS_ATTENTION();
	}
}

/*
** VID_GetDisplaySize
*/
qboolean VID_GetDisplaySize( int *width, int *height )
{
	Display *dpy = XOpenDisplay( NULL );
	if( dpy ) {
		int scr = DefaultScreen( dpy );

		*width = DisplayWidth( dpy, scr );
		*height = DisplayHeight( dpy, scr );
		
		XCloseDisplay( dpy );

		return qtrue;
	}

	return qfalse;
}

/*
* Sys_GetClipboardData
*
* Orginally from EzQuake
* There should be a smarter place to put this
*/
char *Sys_GetClipboardData( qboolean primary )
{
	Window win;
	Atom type;
	int format, ret;
	unsigned long nitems, bytes_after, bytes_left;
	unsigned char *data;
	char *buffer;
	Atom atom;

	if( !x11display.dpy )
		return NULL;

	if( primary )
	{
		atom = XInternAtom( x11display.dpy, "PRIMARY", True );
	}
	else
	{
		atom = XInternAtom( x11display.dpy, "CLIPBOARD", True );
	}
	if( atom == None )
		return NULL;

	win = XGetSelectionOwner( x11display.dpy, atom );
	if( win == None )
		return NULL;

	XConvertSelection( x11display.dpy, atom, XA_STRING, atom, win, CurrentTime );
	XFlush( x11display.dpy );

	XGetWindowProperty( x11display.dpy, win, atom, 0, 0, False, AnyPropertyType, &type, &format, &nitems, &bytes_left,
		&data );
	if( bytes_left <= 0 )
		return NULL;

	ret = XGetWindowProperty( x11display.dpy, win, atom, 0, bytes_left, False, AnyPropertyType, &type,
		&format, &nitems, &bytes_after, &data );
	if( ret == Success )
	{
		buffer = Q_malloc( bytes_left + 1 );
		Q_strncpyz( buffer, (char *)data, bytes_left + 1 );
	}
	else
	{
		buffer = NULL;
	}

	XFree( data );

	return buffer;
}

/*
* Sys_SetClipboardData
*/
qboolean Sys_SetClipboardData( char *data )
{
	return qfalse;
}

/*
* Sys_FreeClipboardData
*/
void Sys_FreeClipboardData( char *data )
{
	Q_free( data );
}
