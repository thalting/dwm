/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 2;        /* border pixel of windows */
static unsigned int gappx     = 0;        /* gaps between windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static int focusonwheel       = 0;
static int vertpad            = 0;        /* vertical padding of bar */
static int sidepad            = 0;        /* horizontal padding of bar */
static int user_bh            = 2;        /* 2 is the default spacing around the bar's font */
static char font[]            = "monospace:size=10";
static const char *fonts[]    = { font };

static char dark[]            = "#0c0c0d";
static char light[]           = "#d8d8d8";

static const char *colors[][3]      = {
    /*                      fg     bg    border   */
    [SchemeNorm]        = { light, dark, dark },
    [SchemeSel]         = { light, dark, light },

    [SchemeStatus]      = { light, dark, dark },
    [SchemeTagsSel]     = { dark,  light, dark },
    [SchemeTagsNorm]    = { light, dark, dark },
    [SchemeInfoSel]     = { light, dark, dark },
    [SchemeInfoNorm]    = { light, dark, dark }
};

/* tagging */
static const char *tags[] = { "α", "β", "γ", "δ", "ε", "ϛ", "ζ", "η", "θ", "ι" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Xev",      NULL,       NULL,       1 << 8,       0,           -1 }
};

/* layout(s) */
static float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
        { "font",               STRING,  &font },
        { "dark",               STRING,  &dark },
        { "light",              STRING,  &light },
        { "gappx",              INTEGER,  &gappx },
        { "vertpad",            INTEGER,  &vertpad },
        { "sidepad",            INTEGER,  &sidepad },
        { "focusonwheel",       INTEGER,  &focusonwheel },
        { "user_bh",            INTEGER,  &user_bh },
        { "borderpx",           INTEGER, &borderpx },
        { "snap",               INTEGER, &snap },
        { "showbar",            INTEGER, &showbar },
        { "topbar",             INTEGER, &topbar },
        { "nmaster",            INTEGER, &nmaster },
        { "resizehints",        INTEGER, &resizehints },
        { "mfact",              FLOAT,   &mfact },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
    setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
    view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
    view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
    toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
    tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
    toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
    tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum           function */
    { "focusstack",     focusstack },
    { "setmfact",       setmfact },
    { "togglebar",      togglebar },
    { "incnmaster",     incnmaster },
    { "togglefloating", togglefloating },
    { "focusmon",       focusmon },
    { "tagmon",         tagmon },
    { "zoom",           zoom },
    { "view",           view },
    { "viewall",        viewall },
    { "viewex",         viewex },
    { "toggleview",     view },
    { "toggleviewex",   toggleviewex },
    { "tag",            tag },
    { "tagall",         tagall },
    { "tagex",          tagex },
    { "toggletag",      tag },
    { "toggletagex",    toggletagex },
    { "killclient",     killclient },
    { "quit",           quit },
    { "setlayout",      setlayout },
    { "setlayoutex",    setlayoutex },
};
