/* See LICENSE file for copyright and license details. */


#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 30;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
// Bar :
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 22;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
// Fonts :
static const char *fonts[] = 
{
/* System Fonts : */
"JetBrains Mono:style=Bold:size=12:antialias=true:autohint=true",
//"Fantasque Sans Mono:style=Bold:size=12:antialias=true:autohint=true",
//"monospace:style=Bold:size=10:antialias=true:autohint=true"
/* Emoji & Icon Fonts : */
"JoyPixels:size=10:antialias=true:autohint=true",
"Font Awesome 6 Free-Solid-900:pixelsize=20",
"fontawesome:pixelsize=14",
"Font Awesome 6 Free-Regular-400:pixelsize=14",
"Font Awesome 6 Brands-Regular-400:pixelsize=14",
"Font Awesome 6 Free Solid:pixelsize=14",
"Font Awesome 6 Brands:pixelsize=14",
"Material Design Icons-Regular:pixelsize=20:antialias=true:autohint=true",
"Sanskrit2003:pixelsize=20:antialias=true:autohint=true",
/* Nerd Fonts : */
"JetBrainsMono Nerd Font:style=Bold:size=20:antialias=true:autohint=true",
//"FantasqueSansMono Nerd Font:style=Bold:size=12:antialias=true:autohint=true",
//"Roboto Mono for Powerline:pixelsize=14:antialias=true:autohint=true",
//"SauceCodePro Nerd Font Mono:weight=bold:pixelsize=10:antialias=true:hinting=true",
};


/* Theme */
#include "themes/gruvbox.h"

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "cmus", NULL };
const char *spcmd3[] = {"pavucontrol", NULL };
const char *spcmd4[] = {"st", "-n", "spvol", "-g", "144x41", "-e", "pulsemixer", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"pavucontrol",   spcmd3},
	{"spvol",       spcmd4},
};


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	  [SchemeNorm] = { col_3, col_1, col_2 },
	  [SchemeSel]  = { col_4, col_1, col_4 },
	  [SchemeStatus]  = { col_3, col_1, col_1 }, // Statusbar right {text,background,not used but cannot be empty}
	  [SchemeTagsSel]  = { col_1, col_4, col_4 }, // Tagbar left selected {text,background,not used but cannot be empty}
    [SchemeTagsNorm]  = { col_3, col_1, col_1 }, // Tagbar left unselected {text,background,not used but cannot be empty}
    [SchemeInfoSel]  = { col_4, col_1, col_4 }, // infobar middle  selected {text,background,not used but cannot be empty}
    [SchemeInfoNorm]  = { col_3, col_1, col_1 }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "󰲠","󰲢","󰲤","󰲦","󰲨","󰲪"};
// static const char *tags[] = { "󰎤","󰎧","󰎪","󰎭","󰎱","󰎳"};
// static const char *tags[] = { "󰎤 : 󰞷", "󰎧 : 󰨞", "󰎪 : 󰀶", "󰎭 : 󰈹", "󰎱 : 󱓥", "󰎳 : 󰏆", "󰎶 : 󰈦", "󰎹 : 󰓓", "󰎼 : 󰒓","󰽽 : 󰣨" };
// Underline Tags :
static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall = 0;	/* 1 to show underline on all tags, 0 for just the active ones */

// Rules :
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "firefox", NULL,     NULL,           1 << 3,    0,          0,          -1,        -1 },
	{ "obsidian", NULL,     NULL,           1 << 4,    0,          0,          -1,        -1 },
	{ "Code", NULL,     NULL,           2,    0,          0,          -1,        -1 },
	{ "Pcmanfm", NULL,     NULL,           1 << 2,    0,          0,          -1,        -1 },
	{ "kitty",      NULL,     NULL,       0,         0,          1,           0,        -1 },
  // Scratch Pads
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
 	{ NULL,		  "spterm",	NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "pavucontrol",	NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,		  "spvol",	NULL,		SPTAG(3),		1,			 -1 },

};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "󱗼 = Tiled",      tile },    /* first entry is default */
	{ "󱗼 = Floating",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	// fibonacci
	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
 	// grid :
 	{ "HHH",      grid },
	// bstack
	{ "󱗼 = Bstack",      bstack },
	{ "===",      bstackhoriz },
 	// centermaster : 
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ NULL,       NULL },
};

/* key definitions */
//#define MODKEY Mod1Mask // ALT key
#define MODKEY Mod4Mask		// Win key
#define TAGKEYS(KEY,TAG) \
	{1, {{MODKEY, KEY}},								view,           {.ui = 1 << TAG} },	\
	{1, {{MODKEY|ControlMask, KEY}},					toggleview,     {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ShiftMask, KEY}},						tag,            {.ui = 1 << TAG} }, \
	{1, {{MODKEY|ControlMask|ShiftMask, KEY}},			toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *rofi[] = {"/home/kvl/.local/bin/launcher", NULL }; 
static const char *termcmd[]  = { "kitty", NULL };
static const char *firefox[]  = { "firefox", NULL };
static const char *code[]  = { "vscode", NULL };
static const char *pcmanfm[]  = { "pcmanfm", NULL };
static const char *lf[]  = { "kitty", "-e", "lfub", NULL };
static const char *news[]  = { "kitty", "-e", "newsboat", NULL };
// static const char *zen[]  = {}; 
// static const char *bar[]  = { "dwmbar-colored", NULL}; 


#include "movestack.c"
static Keychord keychords[] = {
	/* modifier                     key        function        argument */
  {2, {{ MODKEY,XK_r},{0, XK_r}},      spawn,          {.v = rofi } },
  {2, {{ MODKEY,XK_r},{0, XK_w}},      spawn,          {.v = firefox } },
  {2, {{ MODKEY,XK_r},{0, XK_c}},      spawn,          {.v = code } },
  {2, {{ MODKEY|ShiftMask, XK_r},{0, XK_f}},      spawn,          {.v = pcmanfm } },
  {2, {{ MODKEY,XK_r},{0, XK_f}},      spawn,          {.v = lf } },
  {2, {{ MODKEY,XK_r},{0, XK_Return}}, spawn,          {.v = termcmd } },
  {2, {{ MODKEY,XK_s},{0, XK_Return}},  	   togglescratch,  {.ui = 0 } },
  {2, {{ MODKEY,XK_s},{0, XK_space}},	   togglescratch,  {.ui = 1 } },
  {2, {{ MODKEY,XK_s},{0, XK_a}},	   togglescratch,  {.ui = 3 } },
  {2, {{ MODKEY,XK_s},{0, XK_p}},	   togglescratch,  {.ui = 2 } },
  {1, {{ MODKEY,                       XK_a}},      togglebar,      {0} },
  {1, {{ MODKEY,                       XK_b}},      spawn, SHCMD("pkill dwmbar-colored && xsetroot -name ' ' ") },
  {1, {{ MODKEY|ShiftMask,             XK_b}},      spawn, SHCMD("dwmbar-colored") },
	// focusstack :
  {1, {{ MODKEY,                       XK_j}},      focusstack,     {.i = +1 } },
  {1, {{ MODKEY,                       XK_k}},      focusstack,     {.i = -1 } },
  {1, {{ MODKEY|ShiftMask,             XK_j}},      movestack,      {.i = +1 } },
  {1, {{ MODKEY|ShiftMask,             XK_k}},      movestack,      {.i = -1 } },
  {1, {{ MODKEY,                       XK_i}},      incnmaster,     {.i = +1 } },
  {1, {{ MODKEY,                       XK_d}},      incnmaster,     {.i = -1 } },
  {1, {{ MODKEY,                       XK_h}},      setmfact,       {.f = -0.05} },
  {1, {{ MODKEY,                       XK_l}},      setmfact,       {.f = +0.05} },
  {1, {{ MODKEY|ShiftMask,             XK_Tab}},    zoom,           {0} },
  {1, {{ MODKEY,                       XK_Tab}},    view,           {0} },
  {1, {{ MODKEY,                       XK_c}},      killclient,     {0} },
  {1, {{ MODKEY,                       XK_t}},      setlayout,      {.v = &layouts[0]} },
	// { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
  // {1, {{ MODKEY,                       XK_m}},      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },	
	// { MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
  // {1, {{ MODKEY,                       XK_g}},      setlayout,      {.v = &layouts[5]} },
	// bottomstack :
  {1, {{ MODKEY|ShiftMask,                       XK_t}},      setlayout,      {.v = &layouts[6]} },
  // {1, {{ MODKEY,                       XK_o}},      setlayout,      {.v = &layouts[7]} },
  // {1, {{ MODKEY,                       XK_n}},      setlayout,      {.v = &layouts[8]} },
  // {1, {{ MODKEY|ShiftMask,             XK_n}},      setlayout,      {.v = &layouts[9]} },
	// cyclelayout :
  {1, {{ ControlMask,					XK_comma}},  cyclelayout,    {.i = -1 } },
  {1, {{ ControlMask,           		XK_period}}, cyclelayout,    {.i = +1 } },
  {1, {{ MODKEY,                       XK_space}},  setlayout,      {0} },
  {1, {{ MODKEY|ShiftMask,             XK_space}},  togglefloating, {0} },
  {1, {{ MODKEY,                       XK_agrave}}, view,           {.ui = ~0 } },
  {1, {{ MODKEY|ShiftMask,             XK_agrave}}, tag,            {.ui = ~0 } },
  {1, {{ MODKEY,                       XK_comma}},  focusmon,       {.i = -1 } },
  {1, {{ MODKEY,                       XK_semicolon}}, focusmon,    {.i = +1 } },
  {1, {{ MODKEY|ShiftMask,             XK_comma}},  tagmon,         {.i = -1 } },
  {1, {{ MODKEY|ShiftMask,             XK_semicolon}}, tagmon,      {.i = +1 } },
	TAGKEYS(			XK_1,		0)
 	TAGKEYS(			XK_2,		1)
	TAGKEYS(			XK_3,		2)
	TAGKEYS(			XK_4,		3)
	TAGKEYS(			XK_5,		4)
	TAGKEYS(			XK_6,		5)
	// TAGKEYS(			XK_7,		6)
	// TAGKEYS(			XK_8,		7)
	// TAGKEYS(			XK_9,		8)
	{1, {{MODKEY|ShiftMask, XK_q}},					quit,           {1} },
  {1,{{ MODKEY|ControlMask|ShiftMask, XK_q}},      quit,           {0} }, 

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
