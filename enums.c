#include <string.h>

#include "enums.h"

#define STREQ(s1, s2) (strcmp(s1, s2) == 0)

/* make all of these FNV-1 hashes or something instead */

int
toI(char *s) {
  return
    s == NULL                ? ENUM_OFF              :
    STREQ(s, "off")          ? ENUM_OFF              :
    STREQ(s, "no")           ? ENUM_OFF              :
    STREQ(s, "on")           ? ENUM_ON               :
    STREQ(s, "yes")          ? ENUM_ON               :
    STREQ(s, "fixed")        ? ENUM_ON               :
    STREQ(s, "flat")         ? ENUM_FLAT             :
    STREQ(s, "silence")      ? ENUM_FLAT             :
    STREQ(s, "sin")          ? ENUM_SINE             :
    STREQ(s, "sine")         ? ENUM_SINE             :
    STREQ(s, "rsin")         ? ENUM_SINE        * -1 :
    STREQ(s, "rsine")        ? ENUM_SINE        * -1 :
    STREQ(s, "sq")           ? ENUM_SQUARE           :
    STREQ(s, "square")       ? ENUM_SQUARE           :
    STREQ(s, "rsq")          ? ENUM_SQUARE      * -1 :
    STREQ(s, "rsquare")      ? ENUM_SQUARE      * -1 :
    STREQ(s, "tri")          ? ENUM_TRIANGLE         :
    STREQ(s, "triangle")     ? ENUM_TRIANGLE         :
    STREQ(s, "rtri")         ? ENUM_TRIANGLE    * -1 :
    STREQ(s, "rtriangle")    ? ENUM_TRIANGLE    * -1 :
    STREQ(s, "saw")          ? ENUM_RAMP             :
    STREQ(s, "ramp")         ? ENUM_RAMP             :
    STREQ(s, "rsaw")         ? ENUM_RAMP        * -1 :
    STREQ(s, "rramp")        ? ENUM_RAMP        * -1 :
    STREQ(s, "exp")          ? ENUM_EXPONENTIAL      :
    STREQ(s, "exponential")  ? ENUM_EXPONENTIAL      :
    STREQ(s, "rexp")         ? ENUM_EXPONENTIAL * -1 :
    STREQ(s, "rexponential") ? ENUM_EXPONENTIAL * -1 :
    STREQ(s, "log")          ? ENUM_EXPONENTIAL      :
    STREQ(s, "logarithmic")  ? ENUM_EXPONENTIAL      :
    STREQ(s, "rlog")         ? ENUM_LOGARITHMIC * -1 :
    STREQ(s, "rlogarithmic") ? ENUM_LOGARITHMIC * -1 :
    STREQ(s, "rand")         ? ENUM_LOGARITHMIC      :
    STREQ(s, "random")       ? ENUM_LOGARITHMIC      :
    STREQ(s, "noise")        ? ENUM_SINE             :
    STREQ(s, "mod")          ? ENUM_MOD              :
    STREQ(s, "mix")          ? ENUM_MIX              :
    STREQ(s, "sync")         ? ENUM_SYNC             :
    STREQ(s, "amp")          ? ENUM_AMP              : ENUM_UNKNOWN;
}
