#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "funcs.h"
#include "parse.h"
#include "signatures.h"
#include "sizes.h"
#include "types.h"

static bool isModifier(const char);
static bool isNotFunc(const char);
static char *parseFunc(Parse *);
static ArgType parseType(char *);
static bool isValid(ArgType, ArgType);
static void reset(Parse *);
static void error(Parse *);
static char *clearSpace(char *);
static void backup(ArgVal *, const Sig *, int);
static bool toF(char *, ArgVal *);
static bool toI(char *, ArgVal *);
static bool parseArg(ArgVal *, ArgType, ArgType, char *);

#define SET(n, x) (n | x)
#define HAS(n, x) ((bool)(n & x))
#define TRUTH(x) ((x) != 0)
#define OTHER(x) (HAS(x, ARG_OTHER))
#define SIGNED(x) (HAS(x, ARG_SIGNED))
#define ALPHA(x) (HAS(x, ARG_ALPHA))
#define NUM(x) (HAS(x, ARG_NUMBER))
#define FLOAT(x) (HAS(x, ARG_FLOATING))

static bool
isModifier(const char c) {
  return (c == '.' || c == ':');
}

static bool
isNotFunc(const char c) {
  return ((int)c < 0 || (int)c >= SIZE_FS);
}

static char *
parseFunc(Parse *e) {
  char f1  = '\0';
  char f2  = '\0';
  char *s  = e->head;
  ArgVal a = {0};
  const Sig *g = NULL;
  if (*s != '\0')                   { f1 = *s; s++; }
  if (*s != '\0' && isModifier(*s)) { f2 = *s; s++; }
  e->head = s;
  f1 -= (int)'A';
  if (isNotFunc(f1))  { a.i = F_UNKNOWN;         g = &SIG_PURE[SIG_NULL_POS]; }
  else if (f2 == '.') { a.i = F_PERIOD[(int)f1]; g = &SIG_PERIOD[(int)f1]; }
  else if (f2 == ':') { a.i = F_COLON[(int)f1];  g = &SIG_COLON[(int)f1]; }
  else                { a.i = F_PURE[(int)f1];   g = &SIG_PURE[(int)f1]; }
  e->args[0] = a;
  e->sig = g;
  return e->head;
}

static ArgType
parseType(char *s) {
  ArgType t = ARG_NIL;
  for (; *s != '\0' ; s++) {
    t =
      *s == '-'        ? SET(t, ARG_SIGNED)   :
      *s == '.'        ? SET(t, ARG_FLOATING) :
      isdigit((int)*s) ? SET(t, ARG_NUMBER)   :
      isalpha((int)*s) ? SET(t, ARG_ALPHA)    : SET(t, ARG_OTHER);
  }
  return t;
}


static bool
isValid(ArgType tx, ArgType tg) {
  return
    tx == ARG_NIL && tg != ARG_NIL                     ? false :
    tx == tg || tx == ARG_ANY                          ? true  :
    OTHER(tg)                                          ? false :
    (SIGNED(tg) && tx == ARG_UFLOAT) || tx == ARG_UINT ? false :
    ALPHA(tg) && tg != ARG_TEXT                        ? false :
    NUM(tg) && tx == ARG_TEXT                          ? false :
    ALPHA(tg) && NUM(tx)                               ? false : true;    
}

static void
reset(Parse *e) {
  e->head = e->buf;
  e->args[0].i = F_BLANK;
  e->buf[strcspn(e->buf, "\n")] = '\0';
}

static void
error(Parse *e) {
  e->args[0].i = F_ERROR;
}

static char *
clearSpace(char *s) {
  while (*s != '\0' && isspace((int)*s)) { s++; }
  return s;
}

static void
backup(ArgVal *as, const Sig *g, int n) {
  as[n+1] = g->defaults[n - g->required];
}

static bool
toF(char *s, ArgVal *a) {
  return (sscanf(s, "%f", &a->f) != 0);
}

static bool
toI(char *s, ArgVal *a) {
  return (sscanf(s, "%d", &a->i) != 0);
}

static bool
parseArg(ArgVal *a, ArgType tx, ArgType tg, char *s) {
  bool ok = 
    FLOAT(tg) && !FLOAT(tx) && tx != ARG_ANY ? toF(s, a) :
    FLOAT(tx)                                ? toF(s, a) :
    NUM(tx)                                  ? toI(s, a) : TRUTH(a->s = s);
  if (FLOAT(tg) && !FLOAT(tx) && tx != ARG_ANY) { a->i = floorf(a->f); }
  return ok;
}

void
parse(Parse *e) {
  unsigned int n = 0;
  char *s = NULL;
  char *t = NULL;
  ArgType tg = ARG_NIL;
  ArgVal *as = e->args;
  const Sig *g = NULL;
  reset(e);
  e->head = clearSpace(e->head);
  s = e->head;
  if (*s == '\0' || *s == '#') { return; }
  s = parseFunc(e);
  if (as[0].i == F_UNKNOWN) { return; }
  g = e->sig;
  t = strtok(s, " \t");
  for (; n < g->count || t != NULL; n++) {
    if (n >= SIZE_ARGS)                          { error(e); return; }
    if (n >= g->count)                           { error(e); return; }
    if (t == NULL && n < g->required)            { error(e); return; }
    if (t == NULL)                               { backup(as, g, n); continue; }
    tg = parseType(t);
    if (! isValid(g->args[n], tg))               { error(e); return; }
    if (! parseArg(&as[n+1], g->args[n], tg, t)) { error(e); return; }
    t = strtok(NULL, " \t");
  }
}
