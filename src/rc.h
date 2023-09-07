/*-------------------------------------------------------------------------
 *
 * rc.h
 *	  return code for wheelib
 *
 * Portions Copyright (c) 2023, yuesong-feng 冯岳松
 *
 *
 * IDENTIFICATION
 *	  src/rc.h
 *
 *
 * NOTES
 *	  return code
 *
 *-------------------------------------------------------------------------
 */
#ifndef RC_H
#define RC_H

typedef int RC;

#define RC_SUCCESS 0
#define RC_FAIL -1

#define SUCCESS(code) ((code) == RC_SUCCESS)

// file and directory
#define RC_FILE_EXIST -2      // file or dir exist
#define RC_FILE_NOT_EXIST -3  // file and dir do not exist
#define RC_FILE_CREATE_FAIL -4
#define RC_DIR_EXIST -5      // dir exist
#define RC_DIR_NOT_EXIST -6  // dir not exist
#define RC_DIR_CREATE_FAIL -7

#endif
