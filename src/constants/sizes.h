#pragma once

/* Various sizes and bounds used by boar and boari alike. Think carefully before
 * changing any of these values, especially if it may increase a number's byte
 * count. SIZE_ENVS and SIZE_OSCS should not be greater than 255, for instance,
 * as they are only represented by one byte in boar messages. */

#define SIZE_ARGS 5   /* max token count, including func             */
#define SIZE_ENUMS 38 /* number of text token→int enums defined      */
#define SIZE_ENVS 16  /* number of envelopes available               */
#define SIZE_HEAD 6   /* size of output header                       */
#define SIZE_FS 58    /* size of valid func alphabet                 */
#define SIZE_IN 4096  /* max boari input line size                   */
#define SIZE_OUT 512  /* max boari output line size (and boar input) */
#define SIZE_OSCS 16  /* number of oscillators available             */
