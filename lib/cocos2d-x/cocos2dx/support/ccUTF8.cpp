/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 Copyright (c) 2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "ccUTF8.h"
#include "platform/CCCommon.h"
#include "../external/ConvertUTF/ConvertUTF.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
#include "platform/android/jni/JniHelper.h"
#endif

/** source code from ConvertUTF.c */

/*===--- ConvertUTF.c - Universal Character Names conversions ---------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 *===------------------------------------------------------------------------=*/
/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------
 
 Conversions between UTF32, UTF-16, and UTF-8. Source code file.
 Author: Mark E. Davis, 1994.
 Rev History: Rick McGowan, fixes & updates May 2001.
 Sept 2001: fixed const & error conditions per
 mods suggested by S. Parent & A. Lillich.
 June 2002: Tim Dodd added detection and handling of incomplete
 source sequences, enhanced error detection, added casts
 to eliminate compiler warnings.
 July 2003: slight mods to back out aggressive FFFE detection.
 Jan 2004: updated switches in from-UTF8 conversions.
 Oct 2004: updated to use UNI_MAX_LEGAL_UTF32 in UTF-32 conversions.
 
 See the header file "ConvertUTF.h" for complete documentation.
 
 ------------------------------------------------------------------------ */


#ifdef CVTUTF_DEBUG
#include <stdio.h>
#endif


/** source codes from ConvertUTF.h */

/*===--- ConvertUTF.h - Universal Character Names conversions ---------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is distributed under the University of Illinois Open Source
 * License. See LICENSE.TXT for details.
 *
 *==------------------------------------------------------------------------==*/
/*
 * Copyright 2001-2004 Unicode, Inc.
 *
 * Disclaimer
 *
 * This source code is provided as is by Unicode, Inc. No claims are
 * made as to fitness for any particular purpose. No warranties of any
 * kind are expressed or implied. The recipient agrees to determine
 * applicability of information provided. If this file has been
 * purchased on magnetic or optical media from Unicode, Inc., the
 * sole remedy for any claim will be exchange of defective media
 * within 90 days of receipt.
 *
 * Limitations on Rights to Redistribute This Code
 *
 * Unicode, Inc. hereby grants the right to freely use the information
 * supplied in this file in the creation of products supporting the
 * Unicode Standard, and to make copies of this file in any form
 * for internal or external distribution as long as this notice
 * remains attached.
 */

/* ---------------------------------------------------------------------
 
 Conversions between UTF32, UTF-16, and UTF-8.  Header file.
 
 Several funtions are included here, forming a complete set of
 conversions between the three formats.  UTF-7 is not included
 here, but is handled in a separate source file.
 
 Each of these routines takes pointers to input buffers and output
 buffers.  The input buffers are const.
 
 Each routine converts the text between *sourceStart and sourceEnd,
 putting the result into the buffer between *targetStart and
 targetEnd. Note: the end pointers are *after* the last item: e.g.
 *(sourceEnd - 1) is the last item.
 
 The return result indicates whether the conversion was successful,
 and if not, whether the problem was in the source or target buffers.
 (Only the first encountered problem is indicated.)
 
 After the conversion, *sourceStart and *targetStart are both
 updated to point to the end of last text successfully converted in
 the respective buffers.
 
 Input parameters:
 sourceStart - pointer to a pointer to the source buffer.
 The contents of this are modified on return so that
 it points at the next thing to be converted.
 targetStart - similarly, pointer to pointer to the target buffer.
 sourceEnd, targetEnd - respectively pointers to the ends of the
 two buffers, for overflow checking only.
 
 These conversion functions take a ConversionFlags argument. When this
 flag is set to strict, both irregular sequences and isolated surrogates
 will cause an error.  When the flag is set to lenient, both irregular
 sequences and isolated surrogates are converted.
 
 Whether the flag is strict or lenient, all illegal sequences will cause
 an error return. This includes sequences such as: <F4 90 80 80>, <C0 80>,
 or <A0> in UTF-8, and values above 0x10FFFF in UTF-32. Conformant code
 must check for illegal sequences.
 
 When the flag is set to lenient, characters over 0x10FFFF are converted
 to the replacement character; otherwise (when the flag is set to strict)
 they constitute an error.
 
 Output parameters:
 The value "sourceIllegal" is returned from some routines if the input
 sequence is malformed.  When "sourceIllegal" is returned, the source
 value will point to the illegal value that caused the problem. E.g.,
 in UTF-8 when a sequence is malformed, it points to the start of the
 malformed sequence.
 
 Author: Mark E. Davis, 1994.
 Rev History: Rick McGowan, fixes & updates May 2001.
 Fixes & updates, Sept 2001.
 
 ------------------------------------------------------------------------ */

//#ifndef LLVM_SUPPORT_CONVERTUTF_H
//#define LLVM_SUPPORT_CONVERTUTF_H

#include <stddef.h>   /* ptrdiff_t */
/* ---------------------------------------------------------------------
 The following 4 definitions are compiler-specific.
 The C standard does not guarantee that wchar_t has at least
 16 bits, so wchar_t is no less portable than unsigned short!
 All should be unsigned values to avoid sign extension during
 bit mask & shift operations.
 ------------------------------------------------------------------------ */

typedef unsigned int    UTF32;  /* at least 32 bits */
typedef unsigned short  UTF16;  /* at least 16 bits */
typedef unsigned char   UTF8;   /* typically 8 bits */
typedef unsigned char   Boolean; /* 0 or 1 */

/* Some fundamental constants *在 ConvertUTF.h */
//#define UNI_REPLACEMENT_CHAR (UTF32)0x0000FFFD
//#define UNI_MAX_BMP (UTF32)0x0000FFFF
//#define UNI_MAX_UTF16 (UTF32)0x0010FFFF
//#define UNI_MAX_UTF32 (UTF32)0x7FFFFFFF
//#define UNI_MAX_LEGAL_UTF32 (UTF32)0x0010FFFF
//
//#define UNI_MAX_UTF8_BYTES_PER_CODE_POINT 4
//
//#define UNI_UTF16_BYTE_ORDER_MARK_NATIVE  0xFEFF
//#define UNI_UTF16_BYTE_ORDER_MARK_SWAPPED 0xFFFE

//typedef enum {
//    conversionOK,           /* conversion successful */
//    sourceExhausted,        /* partial character in source, but hit end */
//    targetExhausted,        /* insuff. room in target for conversion */
//    sourceIllegal           /* source sequence is illegal/malformed */
//} ConversionResult;
//
//typedef enum {
//    strictConversion = 0,
//    lenientConversion
//} ConversionFlags;

/* This is for C++ and does no harm in C */
//#ifdef __cplusplus
//extern "C" {
//#endif




// ConversionResult ConvertUTF8toUTF16 (
//                                      const UTF8** sourceStart, const UTF8* sourceEnd,
//                                      UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

// ConversionResult ConvertUTF8toUTF32 (
//                                      const UTF8** sourceStart, const UTF8* sourceEnd,
//                                      UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

// ConversionResult ConvertUTF16toUTF8 (
//                                      const UTF16** sourceStart, const UTF16* sourceEnd,
//                                      UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

// ConversionResult ConvertUTF32toUTF8 (
//                                      const UTF32** sourceStart, const UTF32* sourceEnd,
//                                      UTF8** targetStart, UTF8* targetEnd, ConversionFlags flags);

// ConversionResult ConvertUTF16toUTF32 (
//                                       const UTF16** sourceStart, const UTF16* sourceEnd,
//                                       UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags);

// ConversionResult ConvertUTF32toUTF16 (
//                                       const UTF32** sourceStart, const UTF32* sourceEnd,
//                                       UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags);

// Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd);

// Boolean isLegalUTF8String(const UTF8 **source, const UTF8 *sourceEnd);

// unsigned getNumBytesForUTF8(UTF8 firstByte);

// int getUTF8StringLength(const UTF8* utf8, int max);
    
//#ifdef __cplusplus
//}

/*************************************************************************/
/* Below are LLVM-specific wrappers of the functions above. */

//#include "llvm/ADT/ArrayRef.h"
//#include "llvm/ADT/StringRef.h"

#include <vector>
#include <string>


//#endif

/* --------------------------------------------------------------------- */

//#endif


static const int halfShift  = 10; /* used for shifting by 10 bits */

static const UTF32 halfBase = 0x0010000UL;
static const UTF32 halfMask = 0x3FFUL;

#define UNI_SUR_HIGH_START  (UTF32)0xD800
#define UNI_SUR_HIGH_END    (UTF32)0xDBFF
#define UNI_SUR_LOW_START   (UTF32)0xDC00
#define UNI_SUR_LOW_END     (UTF32)0xDFFF
#define false      0
#define true        1

/* --------------------------------------------------------------------- */

/*
 * Index into the table below with the first byte of a UTF-8 sequence to
 * get the number of trailing bytes that are supposed to follow it.
 * Note that *legal* UTF-8 values can't have 4 or 5-bytes. The table is
 * left as-is for anyone who may want to do such conversion, which was
 * allowed in earlier algorithms.
 */
static const char trailingBytesForUTF8[256] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

/*
 * Magic values subtracted from a buffer value during UTF8 conversion.
 * This table contains as many values as there might be trailing bytes
 * in a UTF-8 sequence.
 */
static const UTF32 offsetsFromUTF8[6] = { 0x00000000UL, 0x00003080UL, 0x000E2080UL,
    0x03C82080UL, 0xFA082080UL, 0x82082080UL };

/*
 * Once the bits are split out into bytes of UTF-8, this is a mask OR-ed
 * into the first byte, depending on how many bytes follow.  There are
 * as many entries in this table as there are UTF-8 sequence types.
 * (I.e., one byte sequence, two byte... etc.). Remember that sequencs
 * for *legal* UTF-8 will be 4 or fewer bytes total.
 */
static const UTF8 firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

/* --------------------------------------------------------------------- */

/* The interface converts a whole buffer to avoid function-call overhead.
 * Constants have been gathered. Loops & conditionals have been removed as
 * much as possible for efficiency, in favor of drop-through switches.
 * (See "Note A" at the bottom of the file for equivalent code.)
 * If your compiler supports it, the "isLegalUTF8" call can be turned
 * into an inline function.
 */


/* --------------------------------------------------------------------- */

// ConversionResult ConvertUTF32toUTF16 (
//                                       const UTF32** sourceStart, const UTF32* sourceEnd,
//                                       UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
//     ConversionResult result = conversionOK;
//     const UTF32* source = *sourceStart;
//     UTF16* target = *targetStart;
//     while (source < sourceEnd) {
//         UTF32 ch;
//         if (target >= targetEnd) {
//             result = targetExhausted; break;
//         }
//         ch = *source++;
//         if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
//             /* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
//             if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
//                 if (flags == strictConversion) {
//                     --source; /* return to the illegal value itself */
//                     result = sourceIllegal;
//                     break;
//                 } else {
//                     *target++ = UNI_REPLACEMENT_CHAR;
//                 }
//             } else {
//                 *target++ = (UTF16)ch; /* normal case */
//             }
//         } else if (ch > UNI_MAX_LEGAL_UTF32) {
//             if (flags == strictConversion) {
//                 result = sourceIllegal;
//             } else {
//                 *target++ = UNI_REPLACEMENT_CHAR;
//             }
//         } else {
//             /* target is a character in range 0xFFFF - 0x10FFFF. */
//             if (target + 1 >= targetEnd) {
//                 --source; /* Back up source pointer! */
//                 result = targetExhausted; break;
//             }
//             ch -= halfBase;
//             *target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
//             *target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
//         }
//     }
//     *sourceStart = source;
//     *targetStart = target;
//     return result;
// }

/* --------------------------------------------------------------------- */

// ConversionResult ConvertUTF16toUTF32 (
//                                       const UTF16** sourceStart, const UTF16* sourceEnd,
//                                       UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
//     ConversionResult result = conversionOK;
//     const UTF16* source = *sourceStart;
//     UTF32* target = *targetStart;
//     UTF32 ch, ch2;
//     while (source < sourceEnd) {
//         const UTF16* oldSource = source; 
//         ch = *source++;

//         if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END) {

//             if (source < sourceEnd) {
//                 ch2 = *source;
//                 if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END) {
//                     ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
//                     + (ch2 - UNI_SUR_LOW_START) + halfBase;
//                     ++source;
//                 } else if (flags == strictConversion) {
//                     --source; 
//                     result = sourceIllegal;
//                     break;
//                 }
//             } else { 
//                 --source;
//                 result = sourceExhausted;
//                 break;
//             }
//         } else if (flags == strictConversion) {
            
//             if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END) {
//                 --source;
//                 result = sourceIllegal;
//                 break;
//             }
//         }
//         if (target >= targetEnd) {
//             source = oldSource; 
//             result = targetExhausted; break;
//         }
//         *target++ = ch;
//     }
//     *sourceStart = source;
//     *targetStart = target;
// #ifdef CVTUTF_DEBUG
//     if (result == sourceIllegal) {
//         fprintf(stderr, "ConvertUTF16toUTF32 illegal seq 0x%04x,%04x\n", ch, ch2);
//         fflush(stderr);
//     }
// #endif
//     return result;
// }




/* --------------------------------------------------------------------- */

/*
 * Exported function to return whether a UTF-8 sequence is legal or not.
 * This is not used here; it's just exported.
 */
// Boolean isLegalUTF8Sequence(const UTF8 *source, const UTF8 *sourceEnd) {
//     int length = trailingBytesForUTF8[*source]+1;
//     if (length > sourceEnd - source) {
//         return false;
//     }
//     return isLegalUTF8(source, length);
// }

/* --------------------------------------------------------------------- */

/*
 * Exported function to return the total number of bytes in a codepoint
 * represented in UTF-8, given the value of the first byte.
 */
// unsigned getNumBytesForUTF8(UTF8 first) {
//     return trailingBytesForUTF8[first] + 1;
// }

// int getUTF8StringLength(const UTF8* utf8)
// {
//     size_t len = strlen((const char*)utf8);
//     if (len == 0)
//         return 0;

//     const UTF8** source = &utf8;
//     const UTF8* sourceEnd = utf8 + len;
//     int ret = 0;
//     while (*source != sourceEnd) {
//         int length = trailingBytesForUTF8[**source] + 1;
//         if (length > sourceEnd - *source || !isLegalUTF8(*source, length))
//             return 0;
//         *source += length;
//         ++ret;
//     }
//     return ret;
// }


/* --------------------------------------------------------------------- */


/* --------------------------------------------------------------------- */

// ConversionResult ConvertUTF8toUTF16 (
//                                      const UTF8** sourceStart, const UTF8* sourceEnd,
//                                      UTF16** targetStart, UTF16* targetEnd, ConversionFlags flags) {
//     ConversionResult result = conversionOK;
//     const UTF8* source = *sourceStart;
//     UTF16* target = *targetStart;
//     while (source < sourceEnd) {
//         UTF32 ch = 0;
//         unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
//         if (extraBytesToRead >= sourceEnd - source) {
//             result = sourceExhausted; break;
//         }
//         /* Do this check whether lenient or strict */
//         if (!isLegalUTF8(source, extraBytesToRead+1)) {
//             result = sourceIllegal;
//             break;
//         }
//         /*
//          * The cases all fall through. See "Note A" below.
//          */
//         switch (extraBytesToRead) {
//             case 5: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
//             case 4: ch += *source++; ch <<= 6; /* remember, illegal UTF-8 */
//             case 3: ch += *source++; ch <<= 6;
//             case 2: ch += *source++; ch <<= 6;
//             case 1: ch += *source++; ch <<= 6;
//             case 0: ch += *source++;
//         }
//         ch -= offsetsFromUTF8[extraBytesToRead];
        
//         if (target >= targetEnd) {
//             source -= (extraBytesToRead+1); /* Back up source pointer! */
//             result = targetExhausted; break;
//         }
//         if (ch <= UNI_MAX_BMP) { /* Target is a character <= 0xFFFF */
//             /* UTF-16 surrogate values are illegal in UTF-32 */
//             if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
//                 if (flags == strictConversion) {
//                     source -= (extraBytesToRead+1); /* return to the illegal value itself */
//                     result = sourceIllegal;
//                     break;
//                 } else {
//                     *target++ = UNI_REPLACEMENT_CHAR;
//                 }
//             } else {
//                 *target++ = (UTF16)ch; /* normal case */
//             }
//         } else if (ch > UNI_MAX_UTF16) {
//             if (flags == strictConversion) {
//                 result = sourceIllegal;
//                 source -= (extraBytesToRead+1); /* return to the start */
//                 break; /* Bail out; shouldn't continue */
//             } else {
//                 *target++ = UNI_REPLACEMENT_CHAR;
//             }
//         } else {
//             /* target is a character in range 0xFFFF - 0x10FFFF. */
//             if (target + 1 >= targetEnd) {
//                 source -= (extraBytesToRead+1); /* Back up source pointer! */
//                 result = targetExhausted; break;
//             }
//             ch -= halfBase;
//             *target++ = (UTF16)((ch >> halfShift) + UNI_SUR_HIGH_START);
//             *target++ = (UTF16)((ch & halfMask) + UNI_SUR_LOW_START);
//         }
//     }
//     *sourceStart = source;
//     *targetStart = target;
//     return result;
// }

// /* --------------------------------------------------------------------- */

// ConversionResult ConvertUTF8toUTF32 (
//                                      const UTF8** sourceStart, const UTF8* sourceEnd,
//                                      UTF32** targetStart, UTF32* targetEnd, ConversionFlags flags) {
//     ConversionResult result = conversionOK;
//     const UTF8* source = *sourceStart;
//     UTF32* target = *targetStart;
//     while (source < sourceEnd) {
//         UTF32 ch = 0;
//         unsigned short extraBytesToRead = trailingBytesForUTF8[*source];
//         if (extraBytesToRead >= sourceEnd - source) {
//             result = sourceExhausted; break;
//         }
//         /* Do this check whether lenient or strict */
//         if (!isLegalUTF8(source, extraBytesToRead+1)) {
//             result = sourceIllegal;
//             break;
//         }
//         /*
//          * The cases all fall through. See "Note A" below.
//          */
//         switch (extraBytesToRead) {
//             case 5: ch += *source++; ch <<= 6;
//             case 4: ch += *source++; ch <<= 6;
//             case 3: ch += *source++; ch <<= 6;
//             case 2: ch += *source++; ch <<= 6;
//             case 1: ch += *source++; ch <<= 6;
//             case 0: ch += *source++;
//         }
//         ch -= offsetsFromUTF8[extraBytesToRead];
        
//         if (target >= targetEnd) {
//             source -= (extraBytesToRead+1); /* Back up the source pointer! */
//             result = targetExhausted; break;
//         }
//         if (ch <= UNI_MAX_LEGAL_UTF32) {
//             /*
//              * UTF-16 surrogate values are illegal in UTF-32, and anything
//              * over Plane 17 (> 0x10FFFF) is illegal.
//              */
//             if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) {
//                 if (flags == strictConversion) {
//                     source -= (extraBytesToRead+1); /* return to the illegal value itself */
//                     result = sourceIllegal;
//                     break;
//                 } else {
//                     *target++ = UNI_REPLACEMENT_CHAR;
//                 }
//             } else {
//                 *target++ = ch;
//             }
//         } else { /* i.e., ch > UNI_MAX_LEGAL_UTF32 */
//             result = sourceIllegal;
//             *target++ = UNI_REPLACEMENT_CHAR;
//         }
//     }
//     *sourceStart = source;
//     *targetStart = target;
//     return result;
// }

/* ---------------------------------------------------------------------
 
 Note A.
 The fall-through switches in UTF-8 reading code save a
 temp variable, some decrements & conditionals.  The switches
 are equivalent to the following loop:
 {
 int tmpBytesToRead = extraBytesToRead+1;
 do {
 ch += *source++;
 --tmpBytesToRead;
 if (tmpBytesToRead) ch <<= 6;
 } while (tmpBytesToRead > 0);
 }
 In UTF-8 writing code, the switches on "bytesToWrite" are
 similarly unrolled loops.
 
 --------------------------------------------------------------------- */

/** Source codes from ConvertUTFWrapper.cpp */

//===-- ConvertUTFWrapper.cpp - Wrap ConvertUTF.h with clang data types -----===
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//#include "ConvertUTF.h"
//#include "llvm/Support/SwapByteOrder.h"
#include <string>
#include <vector>
#include <stdint.h>  // uint16_t
#include <assert.h>
#include <memory.h>

typedef std::basic_string<unsigned short> CCWideString;


NS_CC_BEGIN


namespace StringUtils {
    

    /*
     * @str:    the string to search through.
     * @c:        the character to not look for.
     *
     * Return value: the index of the last character that is not c.
     * */
    unsigned int getIndexOfLastNotChar16(const std::vector<char16_t>& str, char16_t c)
    {
        int len = static_cast<int>(str.size());
        
        int i = len - 1;
        for (; i >= 0; --i)
            if (str[i] != c) return i;
        
        return i;
    }
    
    /*
     * @str:    the string to trim
     * @index:    the index to start trimming from.
     *
     * Trims str st str=[0, index) after the operation.
     *
     * Return value: the trimmed string.
     * */
    static void trimUTF16VectorFromIndex(std::vector<char16_t>& str, int index)
    {
        int size = static_cast<int>(str.size());
        if (index >= size || index < 0)
            return;
        
        str.erase(str.begin() + index, str.begin() + size);
    }
    
    /*
     * @ch is the unicode character whitespace?
     *
     * Reference: http://en.wikipedia.org/wiki/Whitespace_character#Unicode
     *
     * Return value: weather the character is a whitespace character.
     * */
    bool isUnicodeSpace(char16_t ch)
    {
        return  (ch >= 0x0009 && ch <= 0x000D) || ch == 0x0020 || ch == 0x0085 || ch == 0x00A0 || ch == 0x1680
        || (ch >= 0x2000 && ch <= 0x200A) || ch == 0x2028 || ch == 0x2029 || ch == 0x202F
        ||  ch == 0x205F || ch == 0x3000;
    }
    
    bool isCJKUnicode(char16_t ch)
    {
        return (ch >= 0x4E00 && ch <= 0x9FBF)   // CJK Unified Ideographs
        || (ch >= 0x2E80 && ch <= 0x2FDF)   // CJK Radicals Supplement & Kangxi Radicals
        || (ch >= 0x2FF0 && ch <= 0x30FF)   // Ideographic Description Characters, CJK Symbols and Punctuation & Japanese
        || (ch >= 0x3100 && ch <= 0x31BF)   // Korean
        || (ch >= 0xAC00 && ch <= 0xD7AF)   // Hangul Syllables
        || (ch >= 0xF900 && ch <= 0xFAFF)   // CJK Compatibility Ideographs
        || (ch >= 0xFE30 && ch <= 0xFE4F)   // CJK Compatibility Forms
        || (ch >= 0x31C0 && ch <= 0x4DFF);  // Other exiensions
    }
    
    void trimUTF16Vector(std::vector<char16_t>& str)
    {
        int len = static_cast<int>(str.size());
        
        if ( len <= 0 )
            return;
        
        int last_index = len - 1;
        
        // Only start trimming if the last character is whitespace..
        if (isUnicodeSpace(str[last_index]))
        {
            for (int i = last_index - 1; i >= 0; --i)
            {
                if (isUnicodeSpace(str[i]))
                    last_index = i;
                else
                    break;
            }
            
            trimUTF16VectorFromIndex(str, last_index);
        }
    }
    
    bool UTF8ToUTF16(const std::string& utf8, std::u16string& outUtf16)
    {
        if (utf8.empty())
        {
            outUtf16.clear();
            return true;
        }
        
        bool ret = false;
        
        const size_t utf16Bytes = (utf8.length()+1) * sizeof(char16_t);
        char16_t* utf16 = (char16_t*)malloc(utf16Bytes);
        memset(utf16, 0, utf16Bytes);
        
        char* utf16ptr = reinterpret_cast<char*>(utf16);
        const UTF8* error = nullptr;
        
        if (llvm::ConvertUTF8toWide(2, utf8, utf16ptr, error))
        {
            outUtf16 = utf16;
            ret = true;
        }
        
        free(utf16);
        
        return ret;
    }
    
    bool UTF16ToUTF8(const std::u16string& utf16, std::string& outUtf8)
    {
        if (utf16.empty())
        {
            outUtf8.clear();
            return true;
        }
        
        return llvm::convertUTF16ToUTF8String(utf16, outUtf8);
    }
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string getStringUTFCharsJNI(JNIEnv* env, jstring srcjStr, bool* ret)
    {
        std::string utf8Str;
        const unsigned short * unicodeChar = ( const unsigned short *)env->GetStringChars(srcjStr, nullptr);
        size_t unicodeCharLength = env->GetStringLength(srcjStr);
        const std::u16string unicodeStr((const char16_t *)unicodeChar, unicodeCharLength);
        bool flag = UTF16ToUTF8(unicodeStr, utf8Str);
        
        if (ret)
        {
            *ret = flag;
        }
        
        if (!flag)
        {
            utf8Str = "";
        }
        env->ReleaseStringChars(srcjStr, unicodeChar);
        return utf8Str;
    }
    
    jstring newStringUTFJNI(JNIEnv* env, std::string utf8Str, bool* ret)
    {
        std::u16string utf16Str;
        bool flag = cocos2d::StringUtils::UTF8ToUTF16(utf8Str, utf16Str);
        
        if (ret)
        {
            *ret = flag;
        }
        
        if(!flag)
        {
            utf16Str.clear();
        }
        jstring stringText = env->NewString((const jchar*)utf16Str.data(), utf16Str.length());
        return stringText;
    }
#endif
    
    std::vector<char16_t> getChar16VectorFromUTF16String(const std::u16string& utf16)
    {
        std::vector<char16_t> ret;
        size_t len = utf16.length();
        ret.reserve(len);
        for (size_t i = 0; i < len; ++i)
        {
            ret.push_back(utf16[i]);
        }
        return ret;
    }
    
    long getCharacterCountInUTF8String(const std::string& utf8)
    {
        return getUTF8StringLength((const UTF8*)utf8.c_str());
    }
    
} //namespace StringUtils {

/////////////////////////////
/////////////////////////////
/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cc_wcslen(const unsigned short* str)
{
    if (str == nullptr)
        return -1;
    int i=0;
    while(*str++) i++;
    return i;
}

void cc_utf8_trim_ws(std::vector<unsigned short>* str)
{
    if (str == nullptr)
        return;
    // unsigned short and char16_t are both 2 bytes
    std::vector<char16_t>* ret = reinterpret_cast<std::vector<char16_t>*>(str);
    StringUtils::trimUTF16Vector(*ret);
}

bool isspace_unicode(unsigned short ch)
{
    return StringUtils::isUnicodeSpace(ch);
}


bool iscjk_unicode(unsigned short ch)
{
    return StringUtils::isCJKUnicode(ch);
}


long cc_utf8_strlen (const char * p, int max)
{
    CC_UNUSED_PARAM(max);
    if (p == nullptr)
        return -1;
    return StringUtils::getCharacterCountInUTF8String(p);
}

unsigned int cc_utf8_find_last_not_char(std::vector<unsigned short>& str, unsigned short c)
{
    int len = static_cast<int>(str.size());
    
    int i = len - 1;
    for (; i >= 0; --i)
        if (str[i] != c) return i;
    
    return i;
}


std::vector<unsigned short> cc_utf16_vec_from_utf16_str(const unsigned short* str)
{
    std::vector<unsigned short> str_new;
    
    if (str == nullptr)
        return str_new;
    
    int len = cc_wcslen(str);
    
    for (int i = 0; i < len; ++i)
    {
        str_new.push_back(str[i]);
    }
    return str_new;
}



char * cc_utf16_to_utf8 (const unsigned short  *str,
                  int             len,
                  long            *items_read,
                  long            *items_written)
{
    if (str == nullptr)
        return nullptr;
    
    
    std::u16string utf16;
    int utf16Len = len < 0 ? cc_wcslen(str) : len;
    
    for (int i = 0; i < utf16Len; ++i)
    {
        utf16.push_back(str[i]);
    }
    
    char* ret = nullptr;
    std::string outUtf8;
    bool succeed = StringUtils::UTF16ToUTF8(utf16, outUtf8);
    
    if (succeed)
    {
        ret = new char[outUtf8.length() + 1];
        ret[outUtf8.length()] = '\0';
        memcpy(ret, outUtf8.data(), outUtf8.length());
    }
    
    return ret;
}


unsigned short* cc_utf8_to_utf16(const char* utf8, int* outUTF16CharacterCount /*= NULL*/)
{
    if (utf8 == NULL)
        return NULL;
    
    unsigned short* ret = NULL;
    
    std::string utf8Str = utf8;
    
    const size_t utf16Size = utf8Str.length()+1;
    unsigned short* utf16 = new unsigned short[utf16Size];
    memset(utf16, 0, utf16Size * sizeof(unsigned short));
    
    char* utf16ptr = reinterpret_cast<char*>(utf16);
    const UTF8* error = NULL;
    
    if (utf8Str.empty() || llvm::ConvertUTF8toWide(2, utf8Str, utf16ptr, error))
    {
        ret = utf16;
        if (outUTF16CharacterCount)
        {
            *outUTF16CharacterCount = cc_wcslen(ret);
        }
    }
    else
    {
        delete [] utf16;
    }
    
    return ret;
}

NS_CC_END
