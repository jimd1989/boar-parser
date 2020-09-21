#include <ctype.h>
#include <err.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../constants/funcs.h"
#include "../constants/sizes.h"
#include "alphabets.h"
#include "parse.h"
#include "signatures.h"
#include "types.h"

static bool isModifier(const char);
static bool isNotFunc(const char);
static bool isBlank(const char);
static char *parseFunc(Parse *);
static ArgType parseType(char *);
static bool isValid(ArgType, ArgType);
static void error(Parse *);
static char *clearSpace(char *);
static bool isUnknown(ArgVal *as);
static bool isAny(Sig);
static void backup(ArgVal *, const Sig *, int);
static bool toF(char *, ArgVal *);
static bool toI(char *, ArgVal *);
static bool toS(char *, ArgVal *);
static bool parseArg(ArgVal *, ArgType, ArgType, char *);

#define SET(n, x) (n | x)               /* Engage an ArgFlag         */
#define HAS(n, x) ((bool)(n & x))       /* Check if ArgFlag is set   */
#define NUM(x) (HAS(x, ARG_NUMBER))     /* Arg contains numerals?    */
#define FLOAT(x) (HAS(x, ARG_FLOATING)) /* Arg is floating point?   */
#define SIGNED(x) (HAS(x, ARG_SIGNED))  /* Arg is signed?            */
#define ALPHA(x) (HAS(x, ARG_ALPHA))    /* Arg contains text?        */
#define OTHER(x) (HAS(x, ARG_OTHER))    /* Arg contains other input? */

static bool
isModifier(const char c) {

/* Check if function token references the A. or A: alphabets. */  

  return (c == '.' || c == ':');
}

static bool
isNotFunc(const char c) {

/* Check if function token is within its valid range. */

  return ((int)c < 0 || (int)c >= SIZE_FS);
}

static bool
isBlank(const char c) {

/* Check if function token is blank or a comment. */

  return (c == '\0' || c == '#');
}

static char *
parseFunc(Parse *p) {

/* Get the Fn enum of the first token in the input line. Assign it to the first
 * index of `args`. Fetch the corresponding signature. Leave `head` at the first
 * char after the token, which precludes the need for a space to precede the
 * first argument. */

  char f1  = '\0';
  char f2  = '\0';
  char *s  = p->head;
  ArgVal a = {0};
  const Sig *g = NULL;

  if (*s != '\0')                   { f1 = *s; s++; }
  if (*s != '\0' && isModifier(*s)) { f2 = *s; s++; }
  p->head = s;
  f1 -= (int)'A';
  if (isNotFunc(f1))  { a.i = F_UNKNOWN;         g = &SIG_PURE[SIG_NULL_POS]; }
  else if (f2 == '.') { a.i = F_PERIOD[(int)f1]; g = &SIG_PERIOD[(int)f1]; }
  else if (f2 == ':') { a.i = F_COLON[(int)f1];  g = &SIG_COLON[(int)f1]; }
  else                { a.i = F_PURE[(int)f1];   g = &SIG_PURE[(int)f1]; }
  p->args[0] = a;
  p->sig = g;

  return p->head;
}

static ArgType
parseType(char *s) {

/* Return the ArgType of the current parameter token by engaging its constituent
 * ArgFlags. */

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

/* Check if a given ArgType `tg` matches an expected ArgType `tx`. */

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
error(Parse *p) {

/* Set the first value of `args` to indicate an error. Is checked outside the
 * parse function and printed accordingly. */

  p->args[0].i = F_ERROR;
}

static char *
clearSpace(char *s) {

/* Eat up any whitespace before the function token. */

  while (*s != '\0' && isspace((int)*s)) { s++; }

  return s;
}

static bool
isUnknown(ArgVal *as) {

/* Check if the function token provided corresponds to an actual defined boar
 * procedure. */

  return (as[0].i == F_UNKNOWN);
}

static bool
isAny(Sig g) {

/* Check if a Sig allows for any and all input. */

  return (g.count == 1 && g.args[0] == ARG_ANY);
}

static void
backup(ArgVal *as, const Sig *g, int n) {

/* If no token is provided in the user input, fall back upon the default value
 * offered by the Sig. */ 
  
  as[n+1] = g->defaults[n - g->required];
}

static bool
toF(char *s, ArgVal *a) {

/* Parse a token into an ArgVal's float slot. */

  return (sscanf(s, "%f", &a->f) != 0);
}

static bool
toI(char *s, ArgVal *a) {

/* Parse a token into an ArgVal's int slot. */

  return (sscanf(s, "%d", &a->i) != 0);
}

static bool
toS(char *s, ArgVal *a) {

/* Render a string into lowercase and pass it into an ArgVal's string slot. */  

  char *c = s;

  while (*c != '\0') { *c = (char)tolower(*c); c++; }
  a->s = s;

  return true;
}

static bool
parseArg(ArgVal *a, ArgType tx, ArgType tg, char *s) {

/* Compare a given arg `tg` against its expected type `tx`, and parse it into
 * an ArgVal accordingly. Some degree of type coercion is possible here. */

  bool ok = 
    FLOAT(tg) && !FLOAT(tx) && tx != ARG_ANY ? toF(s, a) :
    FLOAT(tx)                                ? toF(s, a) :
    NUM(tx)                                  ? toI(s, a) : toS(s, a);

  if (FLOAT(tg) && !FLOAT(tx) && tx != ARG_ANY) { a->i = floorf(a->f); }

  return ok;
}

void
resetParse(Parse *p) {

/* Strip the newline from user input. Point `head` back to the start of `buf`.
 * Assume input it blank. Run in the main loop before each instance of parse(),
 * but not invoked during recursive parse() calls. */

  p->buf[strcspn(p->buf, "\n")] = '\0';
  p->head = p->buf;
  p->args[0].i = F_BLANK;
}

bool
parse(Parse *p) {

/* The main parsing loop. Parse the Fn enum, split tokens on whitespace, and
 * parse every one of them into `args`. Returns a simple boolean to indicate
 * success/failure, but more advanced error handling can be facilitated by
 * examining the enum value in first index of `args`, which contains specific
 * error codes. */

  int n = 0;
  char *s, *t = NULL;
  ArgType tg = ARG_NIL;
  ArgVal *as = p->args;
  const Sig *g = NULL;

  p->head = clearSpace(p->head);
  s = p->head;
  if (isBlank(*s))                               { return true; }
  s = parseFunc(p);
  if (isUnknown(as))                             { return false; }
  g = p->sig;
  if (isAny(*g))                                 { as[1].s = s; return true; }
  t = strtok(s, " \t");
  for (; n < g->count || t != NULL; n++) {
    if (n >= SIZE_ARGS)                          { error(p); return false; }
    if (n >= g->count)                           { error(p); return false; }
    if (t == NULL && n < g->required)            { error(p); return false; }
    if (t == NULL)                               { backup(as, g, n); continue; }
    tg = parseType(t);
    if (! isValid(g->args[n], tg))               { error(p); return false; }
    if (! parseArg(&as[n+1], g->args[n], tg, t)) { error(p); return false; }
    t = strtok(NULL, " \t");
  }

  return true;
}

void
showParseError(Parse *p) {

/* Provide specific reasons for parse failure. Run outside of parse(). */

  switch(p->args[0].i) {
    case F_ERROR:
      warnx("expected %s", showSignature(*p->sig, p->buf));
      break;
    case F_UNKNOWN:
      warnx("unknown function");
      break;
  }
}

Parse
makeParse(char *buf) {

/* Assign a buffer to a Parse object and return it. */

  Parse p = {0};

  p.buf = buf;
  p.head = p.buf;
  p.sig = &SIG_PURE[SIG_NULL_POS];

  return p;
}
